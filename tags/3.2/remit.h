#ifndef __REMIT_H_
#define __REMIT_H_


//INCLUDES
#include "chain.h"

// Represents a signalhandler-object that can be queued 
class Remit : public Chain {

public:
	// Default constructor
	Remit(void (*fkt)()) {
		work = fkt;
	}
	// Destructor
	~Remit();
	
	// signalhandling-function 
	void (*work)();

private:

};

#endif
