#include "hal.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
//#include <stdlibc>


using namespace std;

void hello(void) {
	while(1) {
		unsigned int cpuid = getcpuid();	
		cout << "[CPU_" << cpuid << "] Hallo Welt!"<< endl;
		int sleeping = cpuid + 1;
		sleep(sleeping);
	}
}



int main() {
	int status;

	pid_t pid = start_cpus(hello, sysconf(_SC_NPROCESSORS_ONLN));

	// FIXME
	// wait for the child wohse process ID is equal to the value of pid
	pid_t w = waitpid(pid, &status, WUNTRACED | WCONTINUED);
	if (w == -1) { 
		cerr << "waitpid" << endl;
		return -1;
	}
	return 0;

}


// Freigabe Stacks? -> munmap
