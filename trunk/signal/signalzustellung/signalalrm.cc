#include "signalalrm.h"

// Standard-Konstruktor
SignalALRM::SignalALRM() {

}

// Destruktor
SignalALRM::~SignalALRM() {

}


void SignalALRM::handle(int signal) {

	TIP::tip_start(signal);
}
