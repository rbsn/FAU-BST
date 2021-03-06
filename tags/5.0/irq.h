#ifndef __IRQ_H_
#define __IRQ_H_

// DEFINES

// INCLUDES
#include "cpu.h"
#include <errno.h>
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/syscall.h>

class IRQ {

public:
	// Signalhandler fuer IRQs installieren, ununterbrechbare Ausfuehrung des Signalhandlers
	static void installHandler(int sig, void (*signalhandler)(int)); 
	
	// IRQs bzw. Signale zulassen
	// welche Signale werden von CPU angenommen (vgl. Interrupt Description Table im APIC)
	static void unlockIRQ(sigset_t *mask);
	
	// IRQs bzw. Signale nicht zulassen
	// welche Signale werden von CPU NICHT angenommen (vgl. Interrupt Description Table im APIC)
	static void lockIRQ(sigset_t *mask);
	
	// InterProzessorInterrupt
	static void sendIPI(int cpuID, int sig);

private:

};


#endif

