#include "signalcont.h"

// Standard-Konstruktor
SignalCONT::SignalCONT() {

}

// Destruktor
SignalCONT::~SignalCONT() {

}


void SignalCONT::handle(int signal) {
	TIP::tip_start(signal);
}
