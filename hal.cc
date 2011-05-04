
#include "hal.h"


int boot_cpus(void (*fn)(void), int maxcpus) {
	int pid;

	// allocating a CPU set
	cpusetp = CPU_ALLOC(maxcpus);
	if(cpusetp == NULL) {
		cerr << "Error: CPU_ALLOC" << endl;
		return ENOMEM;
	}

	CPU_ZERO(cpusetp);

	for(int i = 0; i < maxcpus; ++i) {

			// Stackreservierung
			// Beschreibung TODO
			void *stack = mmap(NULL, 4096, PROT_EXEC | PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_GROWSDOWN, -1, sysconf(_SC_PAGE_SIZE));

			if (stack == -1) return errno;

			// Create child-process
			// description TODO
			if((pid = clone(fn, stack[4095], CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_THREAD, NULL)) == -1) {
				return errno;
			}
			
			// Set a process's CPU affinity mask
			// description TODO
			if(-1 == sched_setaffinity(pid, sizeof()

			// getcpu oder anders?
	}

}


long getOnlineCPUs() {
	// Get the number of processorcs currently online
	return sysconf(_SC_NPROCESSORS_ONLN);
}
