#ifndef __REMIT_H_
#define __REMIT_H_


//INCLUDES
#include "chain.h"

// Jenes Objekt, welches in der Waitsnake zu stehen vermag
class Remit : public Chain {

public:
	// Standard-Konstruktor
	Remit(void (*fkt)()) {
		work = fkt;
	}
	// Destruktor
	~Remit();

	void (*work)();

private:

};

#endif
