#ifndef __TIP_H_
#define __TIP_H_

//INCLUDES
#include "cpu.h"
#include "defines.h"
#include "irq.h"
#include "o_stream.h"
#include "queue.h"
#include "remit.h"
#include <signal.h>

// Trap - Interrupt Propagation
class TIP {

public:
	// Default constructor
	TIP() { }
	// Destructor
	~TIP() { }

	// FLIH, signal is received and first handling is done
	static void tip_start(int);
	
	static void tip_clear(sigset_t *mask);		// propagate SLIH if there's any
	
	static void tip_unban(Remit *);				// execute SLIH

	
	// Array of pointers on signalhandler-objects, i.e. remit-objects
	static Remit **handler;
	
	// Sets a signalhandler-object to the handler
	inline static void set_handler(Remit *rem, int sig) {
		handler[sig] = rem;
	}

	// Gets a signalhandler-object from the handler
	inline static Remit *get_handler(int sig) {
		return handler[sig];
	}

	// Default signalhandler-function: just an output
	static void panic();

	static void sig_usr1();

	static void sig_cont();

	static void sig_alrm();
private:
	
};

#endif
