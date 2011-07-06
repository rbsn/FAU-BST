// INCLUDES
#include "cpu.h"
#include "irq.h"
#include "o_stream.h"
#ifdef CONFIG_SIGALRM
#include "signal/signalzustellung/signalalrm.h"
#endif
#ifdef CONFIG_SIGCONT
#include "signal/signalzustellung/signalcont.h"
#endif
#ifdef CONFIG_SIGUSR1
#include "signal/signalzustellung/signalusr1.h"
#endif
#include "timer.h"
#include "tip.h"
#include <errno.h>
#include <iostream>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#include "gotoxy.h"

// For Random!
#include <stdlib.h>
#include <time.h>


using namespace std;

// Signalhandler zum behandeln der Signale
void sighandler(int sig) {
	
}

void hello(void) {
	// Stream zum Ausgeben
	O_Stream *my_stream = CPU::stream[CPU::getcpuid()];
//	Gotoxy *my_stream = new Gotoxy();
	
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
	/*
		*my_stream << gotoxy(100,100) << "Hello " << id << endl;
		*my_stream << "Dezimal " << dec << number << endl;
		*my_stream << "Binaer " << bin << number << endl;
		*my_stream << "Octal " << oct << number << endl;
		*my_stream << "Hexadezimal " << hex << number << endl;
		//number = rand();		// generate a new random number
		
		if(id > 5) {
				//my_stream << "signals rule the world  " << id << endl;
				if(0 != syscall(SYS_tgkill, (int)getpid(), (int)getpid(), (int)SIGCONT)) {
						perror("syscall");
				}

		}
		*/
		for(volatile int j = 0; j < 500000000; j++);
		if(id == 2) {
		kill(getpid(), SIGCONT);
		} 
		if(id == 3) {
			kill(getpid(), SIGUSR1);
		}
	
	}
	
	if(0 != syscall(SYS_tgkill, (int)getpid(), (int)getpid(), (int)SIGUSR2)) {
		perror("syscall");
	}
	*my_stream << "Diese Ausgabe darf _NICHT_ erscheinen! " << id << endl;
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


#ifdef CONFIG_SIGALRM
	IRQ::installHandler(SIGALRM, SignalALRM::handle);
#endif
#ifdef CONFIG_SIGCONT
	IRQ::installHandler(SIGCONT, SignalCONT::handle);
#endif
#ifdef CONFIG_SIGUSR1
	IRQ::installHandler(SIGUSR1, SignalUSR1::handle);
#endif

//#ifdef Zusteller
	IRQ::installHandler(SIGHUP, TIP::tip_start);
//#endif

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
