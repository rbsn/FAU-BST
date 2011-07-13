#ifndef __SIGNALUSR1_H_
#define __SIGNALUSR1_H_


//INCLUDES
#include "../../tip.h"

class SignalUSR1 {

public:
	// Standard-Konstruktor
	SignalUSR1();
	// Destruktor
	~SignalUSR1();

	static void handle(int signal);
private:

};

#endif
