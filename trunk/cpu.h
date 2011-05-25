#ifndef CPU_H
#define CPU_H

// DEFINES
#define CONFIG_STACKSIZE (2 * 1024 * 1024)

#ifndef _GNU_SOURCE
#define _GNU_SOURCE

#endif


// INCLUDES
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
	static int getcpuid();
	
	// get the number of CPUs that have been booted
	inline static int getNumOfBootedCPUs() {
		return counter;
	}

	static O_Stream *getStream();

	static O_Stream *stream;

	// Konstruktor
	CPU() {
		counter++;
	}
	
	// Destruktor
	~CPU() {
		counter--;
	}

	inline static sigset_t *getMask(int cpuid) {
		return cpus[cpuid]->mask;
	}


	int id;				// CPU-ID
	void (*fn)(void);
private:
	void *stack_begin;	// Stack-Beginn
	void *stack_end; 	// Stack-Ende
	int pid;			// Processor-ID = Thread-ID

	sigset_t *mask;

	static bool cpus_booted;
	static CPU **cpus;
	static unsigned int counter;		// counter for #(CPUs)
	static int trampolinfkt(void *);
};

#endif
