#ifndef __SIGNALCONT_H_
#define __SIGNALCONT_H_


//INCLUDES
#include "../../tip.h"

class SignalCONT {

public:
	// Standard-Konstruktor
	SignalCONT();
	// Destruktor
	~SignalCONT();

	static void handle(int signal);

private:

};

#endif
