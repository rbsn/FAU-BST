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
#include "thread/appl.h"
#include "thread/dispatch.h"

// For Random!
#include <stdlib.h>
#include <time.h>

static unsigned char app1stack[CONFIG_APPSTACKSIZE];
static unsigned char app2stack[CONFIG_APPSTACKSIZE];
static unsigned char app3stack[CONFIG_APPSTACKSIZE];
static unsigned char app4stack[CONFIG_APPSTACKSIZE];
static unsigned char app5stack[CONFIG_APPSTACKSIZE];
static unsigned char app6stack[CONFIG_APPSTACKSIZE];
static unsigned char app7stack[CONFIG_APPSTACKSIZE];
static unsigned char app8stack[CONFIG_APPSTACKSIZE];

Application app1(&app1stack[CONFIG_APPSTACKSIZE]);
Application app2(&app2stack[CONFIG_APPSTACKSIZE]);
Application app3(&app3stack[CONFIG_APPSTACKSIZE]);
Application app4(&app4stack[CONFIG_APPSTACKSIZE]);
Application app5(&app5stack[CONFIG_APPSTACKSIZE]);
Application app6(&app6stack[CONFIG_APPSTACKSIZE]);
Application app7(&app7stack[CONFIG_APPSTACKSIZE]);
Application app8(&app8stack[CONFIG_APPSTACKSIZE]);

Application *apps[8];

Dispatcher dispatcher;

using namespace std;

// Signalhandler zum behandeln der Signale
void sighandler(int sig) {
	
}

void hello(void) {
	// Stream zum Ausgeben
	O_Stream *my_stream = CPU::stream[CPU::getcpuid()];
	
	int id = CPU::getcpuid();	// CPU-ID
//	if(id == 0) std::cerr << " MAIN" << hex << apps[4] << std::endl;

	// FIXME: Bevor die Applikationen losrennen, wird der Screen gecleart;

	*my_stream << clear;

	dispatcher.go(*apps[id]);	

	while(1) {
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

//	int threads = sysconf(_SC_NPROCESSORS_ONLN);
	int threads = 4;

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
	apps[0] = &app1;
	apps[1] = &app2;
	apps[2] = &app3;
	apps[3] = &app4;
	apps[4] = &app5;
	apps[5] = &app6;
	apps[6] = &app7;
	apps[7] = &app8;


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
