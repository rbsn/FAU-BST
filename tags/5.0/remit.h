#ifndef __REMIT_H_
#define __REMIT_H_


//INCLUDES
#include "chain.h"

#include "o_stream.h"

// Represents a signalhandler-object that can be queued 
class Remit : public Chain {

public:
	// Default constructor
	Remit(void (*fkt)()) {
		work = fkt;
	}
	// Destructor
	~Remit();

	void blabla() {
		O_Stream mystream;
		mystream << "blabla\n" << endl;
	}

	// signalhandling-function 
	void (*work)();

private:

};

#endif
