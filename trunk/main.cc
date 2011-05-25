// INCLUDES
#include "cpu.h"
#include "irq.h"
#include "o_stream.h"
#include "timer.h"
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

// Signalhandler
void sighandler(int sig) {
	
	O_Stream my_stream;

	switch(sig) {
		case SIGUSR1:	
			my_stream << "SIGUSR1  " << CPU::getcpuid() << "\n" << endl;
			break;

		case SIGCONT:
			my_stream << "SIGCONT  " << CPU::getcpuid() << "\n" << endl;
			break;
						
		case SIGALRM:
			my_stream << "SIGALRM  " << CPU::getcpuid() << "\n" << endl;
			IRQ::sendIPI(getpid(), SIGCONT);
			break;
		default:		break;
	}

}
void hello(void) {
			
	O_Stream my_stream;// = *CPU::getStream();
	//unsigned int cpuid = CPU::getcpuid();	
	
	my_stream << "PID: " << getpid()<< endl;

	int id = CPU::getcpuid();	
	
	int num;
  	/* initialize random seed: */
  	srand ( time(NULL) );
  	/* generate random number: */
 	num = rand();

	// Ausgabe
	for(int i = 0 ; i < 100; i++) {
	//	my_stream << "Hello " << id << endl;
		//my_stream << "Dezimal " << dec << num << endl;
		//my_stream << "Binaer " << bin << num << endl;
		//my_stream << "Octal " << oct << num << endl;
		//my_stream << "Hexadezimal " << hex << num << endl;
		// generate a new random number
		//num = rand() * (-1);
	/*	
		if(id > 5) {
				my_stream << "signals rule the world  " << id << endl;
				if(0 != syscall(SYS_tgkill, (int)getpid(), (int)getpid(), (int)SIGCONT)) {
						perror("syscall");
				}

		}
	*/
	//	kill(getpid(), SIGCONT);
	//	kill(getpid(), SIGUSR1);
		//kill(getpid(), SIGALRM);
	
		for(volatile int j = 0; j < 500000000; j++);
//		for(volatile int j = 0; j < 500000; j++);
	}
	
	if(0 != syscall(SYS_tgkill, (int)getpid(), (int)getpid(), (int)SIGUSR2)) {
		perror("syscall");
	}
}


int main() {
	struct sigaction sa;
	sa.sa_handler = sighandler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);

	sigaction(SIGUSR2, &sa, NULL);

	//int threads = sysconf(_SC_NPROCESSORS_ONLN);
	int threads = 8;

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

	IRQ::installHandler(SIGUSR1, sighandler, 1);
	IRQ::installHandler(SIGCONT, sighandler, 1);
	IRQ::installHandler(SIGALRM, sighandler, 1);
	CPU::boot_cpus(hello, threads);

	Timer alarm;
	
//	cerr << "[GF] cpus booted. Going to sleep" << endl;

	for(int i = 0; i < threads; i++) {
		sigsuspend(&mask);

//		cerr << "[GF] a thread returned..." << endl;
	}

//	cerr << "[GF] shutdown." << endl;

	// TODO Freigabe von allokierten Variablen? -> VALGRIND

}
// Freigabe Stacks? -> munmap
