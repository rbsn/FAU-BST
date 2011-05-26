#include "cpu.h"

CPU ** CPU::cpus;
O_Stream * CPU::stream;
bool CPU::cpus_booted;
// Initial Value
unsigned int CPU::counter = 0;

// DEFINES
#ifndef OPTION
#define OPTION 5
#endif

/* Beschreibung der Optionen:
	1:	SIGCONT und SIGUSR1 sind fuer jede CPU freigeschalten, werden von jeder behandelt
	2:	SIGCONT und SIGUSR1 sind nur fuer eine vorher festgelegte CPU freigeschalten, werden von dieser behandelt
	3:	SIGALRM ist nur fuer eine CPU freigeschalten, wird im Round-Robin-Verfahren behandelt
	4:	SIGUSR1 wie Option 1, SIGCONT wie Option 2
	5:	SIGUSR1 wie Option 1, SIGCONT wie Option 2, SIGALRM wie Option 3
*/


using namespace std;

// maxcpus vom Benutzer vorgegeben
int CPU::boot_cpus(void (*fn)(void), int maxcpus) {
	// CPUs already booted?
	if(cpus_booted) return -1;
	else cpus_booted = true;

	// Get the number of processorcs currently online
	int cpus_online = sysconf(_SC_NPROCESSORS_ONLN);

	// #(CPUs, die gebooted werden) = min{maxcpus, cpus_online}
	if(maxcpus > cpus_online) {
		cout << "You want to use " << maxcpus << " CPUs but there are only " << cpus_online << " CPUs available." << endl << endl;
		maxcpus = cpus_online;
	}

	// Array von Zeigern auf maxcpus CPU-Objekte
	CPU::cpus = new CPU *[maxcpus]; //After: counter = maxcpus
	

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
		cpus[i]->pid = clone(CPU::trampolinfkt , cpus[i]->stack_end, 
							CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_THREAD, cpus[i]);
		if ( cpus[i]->pid == -1 ) {
			perror("[CPU] Error @ clone");
			return errno;
		}
			
	}

	// TODO: Return-Value?
	return cpus[0]->pid;

}

O_Stream *CPU::getStream() {
	return CPU::stream;
}

int CPU::trampolinfkt(void *p) {

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
	if(cpu->id == 6) {
			if(-1 == sigaddset(&mask, SIGALRM)) {
					perror("[CPU] sigaddset");
					return errno;
			}

			IRQ::unlockIRQ(&mask);
	}
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

	for(unsigned int i = 0; i < counter; i++) {
		if( (&addr <= cpus[i]->stack_end) && (&addr >= cpus[i]->stack_begin) ) 
			return i;
	}

	return -1;
}
