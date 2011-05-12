#ifndef CPU_H
#define CPU_H

// DEFINES
#define CONFIG_STACKSIZE (64 * 1024)

#ifndef _GNU_SOURCE
#define _GNU_SOURCE

#endif


// INCLUDES

#include <unistd.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <sched.h>
#include <errno.h>
#include "o_stream.h"

class O_Stream;

class CPU {

public:
	static int boot_cpus(void (*fn)(void), int maxcpus);
	static int getcpuid();
	static int getNumOfBootedCPUs();
	static O_Stream *getStream();

	static O_Stream *stream;

	CPU() {
		counter++;
	}

	int id;			// CPU-ID
	void (*fn)(void);
private:
	void *stack_begin;	// Stack-Beginn
	void *stack_end; 	// Stack-Ende
	int pid;		// Processor-ID = Thread-ID
	
	static bool cpus_booted;
	static CPU **cpus;
	static unsigned int counter;
	static int trampolinfkt(void *);
};

#endif
