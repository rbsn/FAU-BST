#ifndef __IRQ_H_
#define __IRQ_H_


// INCLUDES
#include <errno.h>
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/syscall.h>


class IRQ {

public:
	// Signalhandler fuer IRQs installieren
	// Option = 1: x
	// Option = 2: y
	// Option = 3: z
	static void installHandler(int sig, void (*signalhandler)(int), int option); 
	// IRQs bzw. Signale zulassen
	static void addIRQ(int sig);
	// IRQs bzw. Signale nicht zulassen
	static void delIRQ(int sig);
	
	// InterProzessorInterrupt
	static void sendIPI(int cpuID, int sig);

private:



};


#endif

