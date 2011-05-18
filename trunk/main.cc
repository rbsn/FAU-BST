#include "cpu.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
//#include <stdlibc>

//extern O_Stream *stream;

using namespace std;

void hello(void) {
	O_Stream my_stream;// = *CPU::getStream();
	unsigned int cpuid = CPU::getcpuid();	
/*
	char buf[2];
	buf[0] = '0' + cpuid;
	buf[1] = '\n';

	write(STDERR_FILENO, buf, 2);
*/	
	for(int i = 0 ; i < 5; i++) {
		//stream << "[CPU_" << cpuid << "] Hallo Welt " << i << "! PID: " << (int) getpid() << endl;
		my_stream << "Hello" << endl;
		for(volatile int j = 0; j < 500000000; j++);
//		for(volatile int j = 0; j < 500000; j++);
	}
	
//	cout << "[CPU_" << cpuid << "] Finished." << SYS_tgkill << endl;
	
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

	CPU::boot_cpus(hello, threads);

//	cerr << "[GF] cpus booted. Going to sleep" << endl;

	for(int i = 0; i < threads; i++) {
		sigsuspend(&mask);

//		cerr << "[GF] a thread returned..." << endl;
	}

//	cerr << "[GF] shutdown." << endl;

	return 0;

}


// Freigabe Stacks? -> munmap
