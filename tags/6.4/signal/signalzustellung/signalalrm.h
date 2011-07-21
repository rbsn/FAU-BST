#ifndef __SIGNALALRM_H_
#define __SIGNALALRM_H_


//INCLUDES
#include "../../tip.h"

class SignalALRM {

public:
	// Standard-Konstruktor
	SignalALRM();
	// Destruktor
	~SignalALRM();

	static void handle(int signal);
private:

};

#endif
