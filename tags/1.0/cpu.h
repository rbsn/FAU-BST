#ifndef CPU_H
#define CPU_H

// DEFINES
#define CONFIG_STACKSIZE (2 * 1024 * 1024)		// Size of the Stack

#ifndef _GNU_SOURCE
#define _GNU_SOURCE

#endif


// INCLUDES
#include <errno.h>
#include <iostream>
#include <sched.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <sys/types.h> // Remove!! TODO
#include <stdio.h>
#include <unistd.h>

class CPU {

public:
	static int boot_cpus(void (*fn)(void), int maxcpus);
	static int getCPUID();
	
	// get the number of CPUs that are booted
	inline static int getNumOfBootedCPUs() {
		return counter;
	}

	// Konstruktor
	CPU() { 
		counter++;
	}

	// Destruktor
	~CPU() { 
		counter--;
	}

	int id;				// CPU-ID
	void (*fn)(void);
private:
	void *stack_begin;	// Stack-Beginn
	void *stack_end; 	// Stack-Ende
	int pid;			// Processor-ID = Thread-ID

	static CPU **cpus;

	static unsigned int counter;	// counter for #(CPUs)
	
	static int trampolinfkt(void *);
};

#endif
