#ifndef __TIP_H_
#define __TIP_H_

//INCLUDES
#include "cpu.h"
#include "defines.h"
#include "irq.h"
#include "o_stream.h"
#include "queue.h"
#include "remit.h"

// Trap/ Interrupt Propagation
class TIP {

public:
	// Default constructor
	TIP();
	// Destructor
	~TIP();

	// FLIH, signal is received and first handling is done
	static void tip_start(int);
//	static void tip_defer(Remit *);	// provision of SLIH
	static void tip_unban(Remit *);	// release of deferred SLIH
	static void tip_clear(sigset_t *);		// propagate SLIH, if any

	
	/*
	inline static void set_handler(Remit *r, int sig) {
		handler[sig] = r;
	}

	inline static Remit *get_handler(int sig) {
		return handler[sig];
	}
*/
	// Default signalhandling-function: just an output
	inline static void panic() {
		O_Stream my_stream;
		my_stream << "Default signalhandling function." << endl;
	}

private:
	// Array of pointers on signalhandler-objects (=remit)
	//static Remit **handler;
};

#endif
