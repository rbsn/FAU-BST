#ifndef __CPU_H
#define __CPU_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif


// INCLUDES
#include "defines.h"
#include "irq.h"
#include "o_stream.h"
#include "queue.h"
#include "remit.h"
#include "thread/scheduler.h"
//#include "thread/coroutine.h"
#include "tip.h"
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

	// Default constructor
	CPU() {		num_of_cpus++;	}
	// Default destructor
	~CPU() {	
		num_of_cpus--;	
	/*	
		delete CPU::queue[getcpuid()];
		delete CPU::stream[getcpuid()];

		if(num_of_cpus == 0) {
			delete[] CPU::stream;
			delete[] CPU::queue;
			delete[] CPU::cpus;
		}
	*/	
	}

	inline static sigset_t *getMask(int cpuid) {
		return &(cpus[cpuid]->mask);
	}

	// Returns the thread-ID of the CPU with commited cpu-ID
	inline static int getTID(int cpuid) {
		return cpus[cpuid]->tid;
	}

	int id;				// cpu-ID
	
	void (*fn)(void);

	Queue *q;
	
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
	
	// Gets the TIP level of a CPU
	inline static int getLevel(int cpuid) {		return cpus[cpuid]->level; 	} 

	// Increments the TIP level of a CPU 
	inline static void incrLevel(int cpuid) { 	cpus[cpuid]->level += 1; 	}
	
	// Decrements the TIP level of a CPU
	inline static void decrLevel(int cpuid) { 	cpus[cpuid]->level -= 1; 	}


	static void **activeThread;		// Queue fuer aktives Objekt der CPU

	// O_Stream for output  -  every CPU uses this Output-Stream	 
	static O_Stream **stream;
/*
#ifdef Fliessband
	// Queue to store pending SLIHs	 -	every CPU got one itself
	static Queue **queue;
	
	inline static bool getFlag_SLIH(int cpuid) {	return cpus[cpuid]->flag_SLIH;	}

	inline static void flipFlag_SLIH(int cpuid) {	cpus[cpuid]->flag_SLIH = not(cpus[cpuid]->flag_SLIH); }
#else 
	// Queue to store pending SLIHs	 -  one queue for specified CPU
	static Queue *queue;

	static bool flag_SLIH;
#endif
*/
private:
	void *stack_begin;	// begin of the stack
	void *stack_end; 	// end of the stack
	
	int tid;			// thread-ID = process-ID
	
	// counter for #(CPUs)
	static unsigned int num_of_cpus;

	sigset_t mask;

	// boolean that shows if CPUs were already booted
	static bool booted; 
	static CPU **cpus;

	static void queue_init(int);		// initialize SLIH-Queue
	static void setSchedulerQueue(int);	// initialize Thread-Queue and tell Scheduler about that fact, oder so :{
	static void signal_choice(CPU *);
	static int trampoline(void *);

	// Array for #(SIGNALs), the result of the index represents the CPU that has to handle that signal
 	static int *signalProcessOrder;

	// TIP-Level
	//	* level=1 : only one critical section active
	// 	* level=n : another critical sections active
	int level;
//#ifdef Fliessband
//	bool flag_SLIH;
//#endif
};

#endif
