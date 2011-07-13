#include "signalalrm.h"
#include <stdlib.h>

// Standard-Konstruktor
SignalALRM::SignalALRM() {

}

// Destruktor
SignalALRM::~SignalALRM() {

}


void SignalALRM::handle(int signal) {
	TIP::tip_start(signal);
}
