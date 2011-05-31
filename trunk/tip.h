#ifndef __TIP_H_
#define __TIP_H_


//INCLUDES
#include "defines.h"
#include "o_stream.h"
#include "queue.h"
#include "remit.h"

// Trap/ Interrupt Propagation
class TIP {

public:
	// Standard-Konstruktor
	TIP();
	// Destruktor
	~TIP();

	void tip_entry(int);		// come here upon signal 
	void tip_start(int);		// start of FLIH, also: prototype
	void tip_defer(Remit *);	// provision of SLIH
	void tip_unban(Remit *);	// release of deferred SLIH
	void tip_check();		// propagate SLIH, if allowed
	void tip_clear();		// propagate SLIH, if any

	void set_handler(Remit *r, int sig) {
		handler[sig] = r;
	}

	Remit *get_handler(int sig) {
		return handler[sig];
	}

	static void panic();			// Panic function. Default signalhandler

private:
	Remit *handler[NUM_OF_SIGNAL];
	int level;

	Queue queue;
};

#endif
