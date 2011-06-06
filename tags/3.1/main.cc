// INCLUDES
#include "cpu.h"
#include "irq.h"
#include "o_stream.h"
#include "timer.h"
#include "tip.h"
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
	
/*	O_Stream *my_stream = CPU::stream[CPU::getcpuid()]; //getStream();
	//O_Stream my_stream;

	switch(sig) {
		case SIGUSR1:	
						*my_stream << "SIGUSR1  " << CPU::getcpuid() <<  endl;
						//IRQ::sendIPI( 3 , SIGUSR2 );
						break;
		
		case SIGCONT:	*my_stream << "SIGCONT  " << CPU::getcpuid() <<  endl;
						break;
						
		case SIGALRM:	if(CPU::getcpuid() == CPU::getSignalCounter(SIGALRM)) {
							*my_stream << "SIGALRM  " << CPU::getcpuid() <<  endl;
							CPU::incrSignalCounter(SIGALRM);
						} else {
							*my_stream << "Ich (" << CPU::getcpuid() << ") sende an (" << CPU::getSignalCounter(SIGALRM) << ")." << endl;
							IRQ::sendIPI(CPU::getSignalCounter(SIGALRM), SIGALRM);
						}
						
						//my_stream << "SIGALRM  " << CPU::getSignalCounter(SIGALRM) << "\n" << endl;


						break;
		
		default:		// Diese Meldung duerfte NICHT ausgegeben werden! Andere Signale als die drei 
						// obigen duerfen nicht durchkommen!
						*my_stream << "Es kam Signal: " << sig << endl; 
						break;
	}*/
}

void hello(void) {
	// Stream zum Ausgeben
	O_Stream *my_stream = CPU::stream[CPU::getcpuid()];
	
	int id = CPU::getcpuid();	// CPU-ID
	/*
	int pid = getpid();			// PID
	int tid = CPU::getTID(id);	// TID
	
	my_stream << "ID: " << id << ", PID: " << pid << ", TID: " << tid << endl;
	*/

	// For random output
	int number;
  	srand ( time(NULL) );		// initialize random seed
 	// number = rand();			// generate random number
	number = 31;

	// Output
	//for(int i = 0 ; i < 1; i++) {
	while(1) {
	
	//	my_stream << "Hello " << id << endl;
	//	my_stream << "Dezimal " << dec << number << endl;
	//	my_stream << "Binaer " << bin << number << endl;
	//	my_stream << "Octal " << oct << number << endl;
	//	my_stream << "Hexadezimal " << hex << number << endl;
		//number = rand();		// generate a new random number
		/*
		if(id > 5) {
				//my_stream << "signals rule the world  " << id << endl;
				if(0 != syscall(SYS_tgkill, (int)getpid(), (int)getpid(), (int)SIGCONT)) {
						perror("syscall");
				}

		}
		*/
		for(volatile int j = 0; j < 500000000; j++);
		//if(id == 1) {
		kill(getpid(), SIGCONT);
		//} 
		if(id == 2) {
		kill(getpid(), SIGUSR1);
		}
	
	}
	
	if(0 != syscall(SYS_tgkill, (int)getpid(), (int)getpid(), (int)SIGUSR2)) {
		perror("syscall");
	}
	my_stream << "Diese Ausgabe darf _NICHT_ erscheinen! " << id << endl;
}


int main(int argc, char **argv) {
	struct sigaction sa;
	sa.sa_handler = sighandler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);

	sigaction(SIGUSR2, &sa, NULL);

	//int threads = sysconf(_SC_NPROCESSORS_ONLN);
	int threads = 16;

	sigset_t mask;
	sigfillset(&mask);
	
	//cout << "Godfather's PID: " << getpid() << endl;

	if(-1 == sigdelset(&mask, SIGUSR2)) {
		perror("[MAIN] sigdelset");
		return errno;
	}
	if(-1 == sigdelset(&mask, SIGINT)) {
		perror("[MAIN] sigdelset");
		return errno;
	}

	// Signalhandler installieren, bei Eintritt eines der angegebenen Signale wird Signalbehandlung ausgefuehrt
	/*IRQ::installHandler(SIGUSR1, sighandler);
	IRQ::installHandler(SIGCONT, sighandler);
	IRQ::installHandler(SIGALRM, sighandler);
	
*/


	IRQ::installHandler(SIGUSR1, TIP::tip_start);
	IRQ::installHandler(SIGCONT, TIP::tip_start);
	IRQ::installHandler(SIGALRM, TIP::tip_start);


	// CPUs starten
	CPU::boot_cpus(hello, threads);
	
	Timer alarm;
	
//	cerr << "[GF] cpus booted. Going to sleep" << endl;

	for(int i = 0; i < threads; i++) {
		sigsuspend(&mask);

		cerr << "[GF] a thread returned..." << endl;
	}	

	cerr << "[GF] shutdown." << endl;

	// TODO Freigabe von allokierten Variablen? -> VALGRIND

}
// Freigabe Stacks? -> munmap
