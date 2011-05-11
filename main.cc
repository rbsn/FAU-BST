#include "hal.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
//#include <stdlibc>


using namespace std;

void hello(void) {
//while(1){
	unsigned int cpuid = getcpuidopt();	
for(int i = 0 ; i < 5; i++) {
	cout << "[CPU_" << cpuid << "] Hallo Welt " << i << "! PID: " << (int) getpid() << endl;
	int sleeping = cpuid + 1;
	sleep(sleeping);
}
	cout << "[CPU_" << cpuid << "] Finished." << SYS_tgkill << endl;
	if(0 != syscall(SYS_tkill, (int)getpid(), (int)SIGUSR2)) {
		perror("syscall");
	}
//}
}



int main() {
	int threads = sysconf(_SC_NPROCESSORS_ONLN);

	sigset_t mask;

	sigfillset(&mask);
	
	cout << "Godfather's PID: " << getpid() << endl;

	if(-1 == sigdelset(&mask, SIGUSR2)) {
		perror("sigdelset");
		return errno;
	}
	if(-1 == sigdelset(&mask, SIGINT)) {
		perror("sigdelset");
		return errno;
	}

	start_cpus(hello, threads);

	cout << "[GF] cpus booted. Going to sleep" << endl;

	for(int i = 0; i < threads; i++) {
		if(-1 == sigsuspend(&mask)) perror("[GF] sigsuspend");

		cout << "[GF] a thread returned..." << endl;
	}

	cout << "[GF] shutdown." << endl;

	return 0;

}


// Freigabe Stacks? -> munmap
