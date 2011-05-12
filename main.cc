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

	unsigned int cpuid = getcpuidopt();	
	for(int i = 0 ; i < 5; i++) {
		cout << "[CPU_" << cpuid << "] Hallo Welt " << i << "! PID: " << (int) getpid() << endl;
		for(volatile int j = 0; j < 500000000; j++);
	}
	
	cout << "[CPU_" << cpuid << "] Finished." << SYS_tgkill << endl;
	
	if(0 != syscall(SYS_tgkill, (int)getpid(), (int)getpid(), (int)SIGUSR2)) {
		perror("syscall");
	}
}

void sigs(int sig) {
}

int main() {
	struct sigaction sa;
	sa.sa_handler = sigs;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);

	sigaction(SIGUSR2, &sa, NULL);

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

	cerr << "[GF] cpus booted. Going to sleep" << endl;

	for(int i = 0; i < threads; i++) {
		if(-1 == sigsuspend(&mask)) perror("[GF] sigsuspend");

		cerr << "[GF] a thread returned..." << endl;
	}

	cerr << "[GF] shutdown." << endl;

	return 0;

}


// Freigabe Stacks? -> munmap
