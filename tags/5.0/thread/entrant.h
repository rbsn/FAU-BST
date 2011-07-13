#ifndef __entrant_include__
#define __entrant_include__

#include "../chain.h"
#include "coroutine.h"

class Entrant : public Chain, public Coroutine {

public:
	// Der Entrant Konstruktor gibt nur den Parameter tos an den Coroutinen Konstruktor weiter
	Entrant(void *tos) : Coroutine(tos) { }
	
};
#endif
