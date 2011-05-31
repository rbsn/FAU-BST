#ifndef __CPU_H
#define __CPU_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif


// INCLUDES
#include "defines.h"
#include "irq.h"
#include "o_stream.h"
#include <errno.h>
#include <iostream>
#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <unistd.h>


class O_Stream;

class CPU {

public:
	static int boot_cpus(void (*fn)(void), int maxcpus);
	
	// Returns the CPU-ID on success, -1 on error
	static int getcpuid();
	
	// Returns the number of CPUs that have been booted
	inline static int getNumOfBootedCPUs() { 	return num_of_cpus;		}

	static O_Stream *getStream();

	static O_Stream *stream;

	// Default constructor
	CPU() {		num_of_cpus++;	}
	// Default destructor
	~CPU() {	num_of_cpus--;	}


	inline static sigset_t *getMask(int cpuid) {
		return cpus[cpuid]->mask;
	}

	// Returns the thread-ID of the CPU with commited cpu-ID
	inline static int getTID(int cpuid) {
		return cpus[cpuid]->tid;
	}

	int id;				// cpu-ID
	
	void (*fn)(void);
	
	// Gets the CPU that has to handle the commited signal
	inline static int getSignalCounter(int signal) {
		return signalProcessOrder[signal];
	}
	
	// Sets the CPU that has to handle the commited signal
	inline static void setSignalCounter(int signal, int cpuid) {
		signalProcessOrder[signal] = cpuid;
	}

	// Increments the CPU that has to handle the commited signal (used for Round-Robin procedure)
	inline static void incrSignalCounter(int signal) {
		setSignalCounter(signal, (getSignalCounter(signal) + 1) % getNumOfBootedCPUs());
	}
	

private:
	void *stack_begin;	// begin of the stack
	void *stack_end; 	// end of the stack
	
	int tid;			// thread-ID = process-ID
	
	// counter for #(CPUs)
	static unsigned int num_of_cpus;

	sigset_t *mask;

	static bool cpus_booted; 
	static CPU **cpus;

	static int trampoline(void *);

	// Array for #(SIGNALs), the result of the index represents the CPU that has to handle that signal
 	static int *signalProcessOrder;
};

#endif
