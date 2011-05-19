#include "o_stream.h"
#include "cpu.h"
#include <errno.h>
#include <iostream>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

// For Random!
#include <stdlib.h>
#include <time.h>

//extern O_Stream *stream;

using namespace std;

void hello(void) {
	O_Stream my_stream;// = *CPU::getStream();
	//unsigned int cpuid = CPU::getcpuid();	
	
	
	
	int num;
  	/* initialize random seed: */
  	srand ( time(NULL) );
  	/* generate random number: */
 	num = rand() * (-1);

	// Ausgabe
	for(int i = 0 ; i < 3; i++) {
		//my_stream << "Hello" << endl;
		my_stream << "Dezimal " << dec << num << endl;
		my_stream << "Binaer " << bin << num << endl;
		my_stream << "Octal " << oct << num << endl;
		my_stream << "Hexadezimal " << hex << num << endl;
		// generate a new random number
		num = rand() * (-1);
		
		for(volatile int j = 0; j < 500000000; j++);
//		for(volatile int j = 0; j < 500000; j++);
	}
	
	if(0 != syscall(SYS_tgkill, (int)getpid(), (int)getpid(), (int)SIGUSR2)) {
		perror("syscall");
	}
}

// Signalhandler
void sighandler(int sig) {
}

int main() {
	struct sigaction sa;
	sa.sa_handler = sighandler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);

	sigaction(SIGUSR2, &sa, NULL);

	//int threads = sysconf(_SC_NPROCESSORS_ONLN);
	int threads = 1;

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

	// TODO Freigabe von allokierten Variablen? -> VALGRIND

}
// Freigabe Stacks? -> munmap
