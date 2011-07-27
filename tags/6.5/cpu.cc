#include "cpu.h"
#include "gotoxy.h"

int * CPU::signalProcessOrder;
CPU ** CPU::cpus;
void ** CPU::activeThread;
O_Stream ** CPU::stream;
Remit ** TIP::handler;

bool CPU::booted = false;			// FALSE :	CPUs haven't been booted yet

unsigned int CPU::num_of_cpus = 0;	// 0: 	Still no CPUs has been created

extern Scheduler scheduler;

using namespace std;


// maxcpus given by the user 
int CPU::boot_cpus(void (*fn)(void), int maxcpus) { 

	// CPUs already have been booted?
	if(booted) { 
		cerr << "[CPU] Error: 		The CPUs already have been booted." << endl << endl;
		return -1;
	} else { booted = true; }

	// Get the number of processors currently online
	int cpus_online = sysconf(_SC_NPROCESSORS_ONLN);

	// #(CPUs that will be booted) = min{maxcpus, cpus_online}
	if(maxcpus > cpus_online) {
		cerr << "[CPU] Warning: 	You want to boot " << maxcpus << " CPUs but there are only " << cpus_online << " CPUs available." << endl << endl;
		maxcpus = cpus_online;
	}


	// Initialize the array for #(SIGNALs), first CPU that will handle an incoming signal will be CPU_0
	CPU::signalProcessOrder = new int[NUM_OF_SIGNAL];
	for(int i = 0; i < NUM_OF_SIGNAL; ++i) {
		signalProcessOrder[i] = 0;	
	}

	TIP::handler = new Remit *[NUM_OF_SIGNAL];
	
	Remit *defaultHandler = new Remit(TIP::panic);
	for(int i = 0; i < NUM_OF_SIGNAL; ++i) {
		TIP::set_handler(defaultHandler, i);
	}

	Remit *usr1 = new Remit(TIP::sig_usr1);
	TIP::set_handler(usr1, SIGUSR1);
	Remit *cont = new Remit(TIP::sig_cont);
	TIP::set_handler(cont, SIGCONT);
	Remit *alrm = new Remit(TIP::sig_alrm);
	TIP::set_handler(alrm, SIGALRM);



	// Array of pointers on maxcpus Stream-Objects
	CPU::stream = new O_Stream *[maxcpus];
	// Array of pointers on maxcpus CPU-Objects
	CPU::cpus = new CPU *[maxcpus]; 
	// Array of pointers on maxcpus Active Thread-Objects
	CPU::activeThread = new void *[maxcpus];

	CPU::queue_init(maxcpus);

	for(int i = 0; i < maxcpus; ++i) {


		cpus[i] = new CPU();				// Create every single CPU
		cpus[i]->fn = fn;				
		cpus[i]->id = i;
		CPU::stream[i] = new O_Stream();	// Create an o_stream for every single CPU

//		*CPU::stream[i] << "TEST:  " << i << endl;
		
		CPU::setSchedulerQueue(i);

		// Stackreservierung mit mmap
		cpus[i]->stack_begin = mmap(NULL, CONFIG_STACKSIZE, PROT_EXEC | PROT_READ | PROT_WRITE, 
								MAP_PRIVATE | MAP_ANONYMOUS | MAP_GROWSDOWN, -1, sysconf(_SC_PAGE_SIZE));
		if ( cpus[i]->stack_begin == MAP_FAILED ) {
			perror("[CPU] Error @ mmap");
			return errno;
		}

		cpus[i]->stack_end = ((char *) cpus[i]->stack_begin) + CONFIG_STACKSIZE - sizeof(char *);
		

		// Create child-process mit clone
		cpus[i]->tid = clone(CPU::trampoline , cpus[i]->stack_end, 
							CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_THREAD, cpus[i]);
		if ( cpus[i]->tid == -1 ) {
			perror("[CPU] Error @ clone");
			return errno;
		}
			
	}

	// TODO: Return-Value?
	return cpus[0]->tid;

}


int CPU::trampoline(void *p) {
	
	CPU *cpu = (CPU *) p; 

	cpu_set_t cpusetp;
	CPU_ZERO(&cpusetp);
	CPU_SET(cpu->id, &cpusetp);

	sigfillset(&cpu->mask);

	// Default: Block every signal on every single CPU
	IRQ::lockIRQ(&cpu->mask); 	
	
	sigemptyset(&cpu->mask);

	// Signalverteilungen werden festgelegt
	CPU::signal_choice(cpu);	


	IRQ::unlockIRQ(&cpu->mask);

	// Set a process's CPU affinity mask
	if(-1 == sched_setaffinity(0, sizeof(cpusetp), &cpusetp)) {
		return errno;
	}
	
	cpu->fn();
	
	// TODO: Return-Value?
	return 0;
}

void CPU::signal_choice(CPU *cpu) {

}

void CPU::queue_init(int maxcpus) {

}


void CPU::setSchedulerQueue(int cpuid) {
// TODO ASPECT
//	cpus[cpuid]->q = new Queue();					//Create ReadyList for Scheduler
//	scheduler.setCPUQueue(cpuid, cpus[cpuid]->q);	//Tell Scheduler about Queue
}

int CPU::getcpuid() {
	// Put an arbitrary variable on the stack and readout the stackpointer
	int addr;

	for(unsigned int i = 0; i < num_of_cpus; i++) {
		if( (&addr <= cpus[i]->stack_end) && (&addr >= cpus[i]->stack_begin) ) 
			return i;
	}

	return -1;
}

void CPU::preemption_lock() {
	// Atomic bit set ( 0 XOR 1 = 1)
	__sync_fetch_and_xor(&preemptive_flag, 1);
}

void CPU::preemption_unlock() {
	// Atomic bit unset ( 1 XOR 1 = 0)
	__sync_fetch_and_xor(&preemptive_flag, 1);

	if(preempted != 0) {	// Any pending?
		Entrant *tmp = preempted;
		preempted = 0;
		scheduler.resume((Entrant *)scheduler.active(), tmp); // Dispatch deferred Entrant
	}
}

void CPU::defer_entrant(Entrant *e) {
	preempted = e;
}

bool CPU::isPreemptionLocked() {
	return preemptive_flag;
}

bool CPU::isDeferred() {
	if(preempted != 0) return true;
	return false;
}
