#include "cpu.h"

int * CPU::signalProcessOrder;
CPU ** CPU::cpus;
O_Stream * CPU::stream;
bool CPU::cpus_booted = false;

unsigned int CPU::num_of_cpus = 0;		// initial value for number of CPUs

// DEFINES
#ifndef OPTION
#define OPTION 5
/* Description of the different options:
	1:	SIGCONT and SIGUSR1 are activated for every CPU, so these signals will be treated by every CPU
	2:	SIGCONT and SIGUSR1 are activated only for one predefined CPU, so these signals will be treated by only this CPU
	3:	SIGALRM is activated only for one CPU, so this signal will be treated in Round-Robin procedure
	4:	SIGUSR1 will be treated like option 1, SIGCONT will be treated like option 2
	5:	SIGUSR1 will be treated like option 1, SIGCONT will be treated like option 2, SIGALRM will be treated like option 3
*/
#endif


using namespace std;

// maxcpus vom Benutzer vorgegeben
int CPU::boot_cpus(void (*fn)(void), int maxcpus) {


// CPUs already booted?
	if(cpus_booted) return -1;
	else cpus_booted = true;

	// Get the number of processors currently online
	int cpus_online = sysconf(_SC_NPROCESSORS_ONLN);

	// #(CPUs that will be booted) = min{maxcpus, cpus_online}
	if(maxcpus > cpus_online) {
		cout << "You want to use " << maxcpus << " CPUs but there are only " << cpus_online << " CPUs available." << endl << endl;
		maxcpus = cpus_online;
	}

	// Initialize the array for #(SIGNALs), first CPU that will handle an incoming signal will be CPU_0
	CPU::signalProcessOrder = new int[NUM_OF_SIGNAL];
	for(int i = 0; i < NUM_OF_SIGNAL; ++i) {
		signalProcessOrder[i] = 0;	
	}

	// Array of pointers on maxcpus CPU-objects
	CPU::cpus = new CPU *[maxcpus]; 
	
	for(int i = 0; i < maxcpus; ++i) {
	
		cpus[i] = new CPU();
		cpus[i]->fn = fn;
		cpus[i]->id = i;

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

O_Stream *CPU::getStream() {
	return CPU::stream;
}

int CPU::trampoline(void *p) {

	CPU *cpu = (CPU *) p; 

	cpu_set_t cpusetp;
	CPU_ZERO(&cpusetp);
	CPU_SET(cpu->id, &cpusetp);

	sigset_t mask;
	sigfillset(&mask);

	// Alle Signale blockieren
	IRQ::lockIRQ(&mask); 	

	sigemptyset(&mask);

#if (OPTION == 1 || OPTION == 4 || OPTION == 5)
	if(-1 == sigaddset(&mask, SIGUSR1)) {
		perror("[CPU] sigaddset");
		return errno;
	}
	#if( OPTION == 1)
	if(-1 == sigaddset(&mask, SIGCONT)) {
		perror("[CPU] sigaddset");
		return errno;
	}
	#endif
	IRQ::unlockIRQ(&mask);
#endif

#if (OPTION == 2 || OPTION == 4 || OPTION == 5)
	// Laeuft nur auf CPU 1
	if(cpu->id == 5) {
			#if (OPTION == 2)
			if(-1 == sigaddset(&mask, SIGUSR1)) {
					perror("[CPU] sigaddset");
					return errno;
			}
			#endif
			if(-1 == sigaddset(&mask, SIGCONT)) {
					perror("[CPU] sigaddset");
					return errno;
			}
		IRQ::unlockIRQ(&mask);
	}
#endif

#if (OPTION == 3 || OPTION == 5)
	//if(cpu->id == 0) {
			if(-1 == sigaddset(&mask, SIGALRM)) {
					perror("[CPU] sigaddset");
					return errno;
			}

			IRQ::unlockIRQ(&mask);
	//}
#endif

	// Set a process's CPU affinity mask
	if(-1 == sched_setaffinity(0, sizeof(cpusetp), &cpusetp)) {
		return errno;
	}
	
	cpu->fn();
	
	// TODO: Return-Value?
	return 0;
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
