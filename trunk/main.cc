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


using namespace std;

// Signalhandler zum behandeln der Signale
void sighandler(int sig) {
	
	O_Stream my_stream;

	switch(sig) {
		case SIGUSR1:	my_stream << "SIGUSR1  " << CPU::getcpuid() << "\n" << endl;
						break;
		
		case SIGCONT:	my_stream << "SIGCONT  " << CPU::getcpuid() << "\n" << endl;
						break;
						
		case SIGALRM:	my_stream << "SIGALRM  " << CPU::getcpuid() << "\n" << endl;
						IRQ::sendIPI(getpid(), SIGCONT);
						break;
		
		default:		break;
	}
}

void hello(void) {
	// Stream zum Ausgeben
	O_Stream my_stream;
	
	int id = CPU::getcpuid();	// CPU-ID
	int pid = getpid();			// PID
	
	my_stream << "PID: " << pid << endl;

	// For random output
	int number;
  	srand ( time(NULL) );		// initialize random seed
 	// number = rand();			// generate random number
	number = 31;

	// Output
	for(int i = 0 ; i < 100; i++) {
	//	my_stream << "Hello " << id << endl;
		my_stream << "Dezimal " << dec << number << endl;
		my_stream << "Binaer " << bin << number << endl;
		my_stream << "Octal " << oct << number << endl;
		my_stream << "Hexadezimal " << hex << number << endl;
		//number = rand();		// generate a new random number
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


int main(int argc, char **argv) {
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

	// Signalhandler installieren, bei Eintritt eines der angegebenen Signale wird Signalbehandlung ausgefuehrt
	IRQ::installHandler(SIGUSR1, sighandler, 1);
	IRQ::installHandler(SIGCONT, sighandler, 1);
	IRQ::installHandler(SIGALRM, sighandler, 1);
	// CPUs starten
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
