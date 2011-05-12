#include "hal.h"

// maxcpus vom Benutzer vorgegeben
int start_cpus(void (*fn)(void), int maxcpus) {
	int res = CPU::boot_cpus(fn, maxcpus);

	return res;

}


int getcpuid() {
	unsigned int cpuid = 0;
	syscall(318, &cpuid, NULL, NULL);

	return cpuid;
}

int getcpuidopt() {
	int addr;
	return CPU::cpu_stack(&addr);
}

