#include "cpu.h"

CPU ** CPU::cpus;
unsigned int CPU::counter = 0;

// maxcpus vom Benutzer vorgegeben
int CPU::boot_cpus(void (*fn)(void), int maxcpus) {
	// Get the number of processorcs currently online
	int cpu_count = sysconf(_SC_NPROCESSORS_ONLN);
	if(maxcpus > cpu_count) 
		maxcpus = cpu_count;

	CPU::cpus = new CPU *[maxcpus]; 
	

	for(int i = 0; i < maxcpus; ++i) {
	
		cpus[i] = new CPU();
		cpus[i]->fn = fn;
		cpus[i]->id = i;

		// Stackreservierung
		cpus[i]->stack_begin = mmap(NULL, CONFIG_STACKSIZE, PROT_EXEC | PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_GROWSDOWN, -1, sysconf(_SC_PAGE_SIZE));
		if (cpus[i]->stack_begin == (void *)-1) return errno;
		cpus[i]->stack_end = ((char *) cpus[i]->stack_begin) + CONFIG_STACKSIZE - sizeof(char *);
		

		// Create child-process
		if((cpus[i]->pid = clone(CPU::trampolinfkt , cpus[i]->stack_end, CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_THREAD, cpus[i])) == -1) {
			return errno;
		}
			
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

int CPU::cpu_stack(int *addr) {
	for(unsigned int i = 0; i < counter; i++) {
		if(addr <= cpus[i]->stack_end && addr >= cpus[i]->stack_begin) return i;
	}
	return -1;
}

