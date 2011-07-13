#include "signalusr1.h"

// Standard-Konstruktor
SignalUSR1::SignalUSR1() {

}

// Destruktor
SignalUSR1::~SignalUSR1() {

}


void SignalUSR1::handle(int signal) {

	TIP::tip_start(signal);	

}
