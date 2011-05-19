#include "cpu.h"

CPU ** CPU::cpus;
// Initial Value
unsigned int CPU::counter = 0;


using namespace std;

// maxcpus vom Benutzer vorgegeben
int CPU::boot_cpus(void (*fn)(void), int maxcpus) {
	// Get the number of processorcs currently online
	int cpus_online = sysconf(_SC_NPROCESSORS_ONLN);

	// #(CPUs, die gebooted werden) = min{maxcpus, cpus_online}
	if(maxcpus > cpus_online) {
		cout << "You want to use " << maxcpus << " CPUs but there are only " << cpus_online << " CPUs available." << endl << endl;
		maxcpus = cpus_online;
	}

	// Array von Zeigern auf maxcpus CPU-Objekte
	CPU::cpus = new CPU *[maxcpus]; 

	for(int i = 0; i < maxcpus; ++i) {
	
		cpus[i] = new CPU();
		cpus[i]->fn = fn;
		cpus[i]->id = i;

		// Stackreservierung mit mmap
		cpus[i]->stack_begin = mmap( NULL, CONFIG_STACKSIZE, PROT_EXEC | PROT_READ | PROT_WRITE, 
								MAP_PRIVATE | MAP_ANONYMOUS | MAP_GROWSDOWN, -1, sysconf(_SC_PAGE_SIZE) );
		if ( cpus[i]->stack_begin == MAP_FAILED ) {
			perror("Error @ mmap");
			return errno;
		}

		cpus[i]->stack_end = ((char *) cpus[i]->stack_begin) + CONFIG_STACKSIZE - sizeof(char *);
		

		// Create child-process mit clone
		cpus[i]->pid = clone( CPU::trampolinfkt , cpus[i]->stack_end, 
						CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_THREAD, cpus[i] );
		if ( cpus[i]->pid == -1) {
			perror("Error @ clone");
			return errno;
		}

		//cout << "TID (Thread ID) of thread" << i << ": TID " << gettid() << endl;
		cout << "PID (Process ID) of thread" << i << ": PID " << getpid() << endl;
		cout << "PPID (Process ID of the parent) of thread" << i << ": PPID " << getppid() << endl;

	}

	// TODO: Return-Value?
	return cpus[0]->pid;

}

int CPU::trampolinfkt(void *p) {
	
	CPU *cpu = (CPU *) p; 

	cpu_set_t cpusetp;
	CPU_ZERO(&cpusetp);
	CPU_SET(cpu->id, &cpusetp);
	
	// Set a process's CPU affinity mask
	if(-1 == sched_setaffinity(0, sizeof(cpusetp), &cpusetp)) {
		return errno;
	}

	cpu->fn();
	
	// TODO: Return-Value?
	return 0;
}


// Get the ID of the currently running CPU
int CPU::getCPUID() {
	// Beliebige Variable auf den Stack legen und den Stackpointer auslesen
	int addr;

	for(unsigned int i = 0; i < counter; i++) {
		if( (&addr <= cpus[i]->stack_end) && (&addr >= cpus[i]->stack_begin) ) 
			
			return i;
	}

	return -1;
}
