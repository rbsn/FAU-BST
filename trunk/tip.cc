#include "tip.h"
/*
Remit ** TIP::handler;
Remit * defaultRemit;
*/
// Default constructor
TIP::TIP() {
/*	handler = new Remit *[256];

	// Signalhandler with a default signalhandling-function
	defaultRemit = new Remit(panic);

	for(int i = 0; i < NUM_OF_SIGNAL-1; i++) {
		set_handler(defaultRemit, i);
	}
*/
}


// Destruktor
TIP::~TIP() {
}


void TIP::tip_start(int sig) {	
	// Increment of TIP level
	CPU::incrLevel(CPU::getcpuid());

	//signale freigeben
	// Registersicherung NICHT  notwendig
	//TODO: SYNCHRO


	sigset_t mask = *CPU::getMask(CPU::getcpuid());
	// Durch Sperren des aktiven Signals wird dieses nicht erneut eingelocht
	if(sigdelset(&mask, sig) == -1) {
		perror("[TIP] Error @ sigdelset");		return;
	}

	// Rrrremit in die Warteschlange einfuegen.
	//CPU::getQueue()->enqueue(get_handler(sig));
	

	if(CPU::getLevel(CPU::getcpuid()) == 1) { 
		while (!(CPU::queue[CPU::getcpuid()]->isEmpty())) {
			// Signale wieder freigeben mit Ausnahme des Aktiven
			IRQ::unlockIRQ(&mask);
			tip_clear(&mask);
			// Signale wieder sperren (ALLE)
			IRQ::lockIRQ(&mask);
		}
	}

	// Decrement of TIP level
	CPU::decrLevel(CPU::getcpuid());


	// TODO
	// ??? Evtl. Signale wieder sperren ???

}



// 
void TIP::tip_clear(sigset_t *mask) {
	Remit *next;
	do { 
		// Signale wieder sperren mit Ausnahme des AKTIven
		IRQ::lockIRQ(mask);
		
		if((next = (Remit *) CPU::queue[CPU::getcpuid()]->dequeue())) {
				IRQ::unlockIRQ(mask);
				tip_unban(next);
		} else IRQ::unlockIRQ(mask);
	} while (next != 0);
}

void TIP::tip_unban(Remit *item) {
	// SLIH
	(item->work)();
}
