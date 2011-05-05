#ifndef CPU_H
#define CPU_H


#define CONFIG_STACKSIZE (64 * 1024)

class CPU {

public:
	static int boot_cpus(void (*fn)(void), int maxcpus);
	
	CPU() {
		
	}

	int id;			// CPU-ID
	void (*fn)(void);
private:
	void *stack_begin;	// Stack-Beginn
	void *stack_end; 	// Stack-Ende
	int pid;		// Processor-ID = Thread-ID

	static CPU **cpus;
};

#endif
