#include "tip.h"

// Default signalhandler-function: just an output
void TIP::panic() {
	O_Stream *my_stream = CPU::stream[CPU::getcpuid()];
	*my_stream << "CPU " << CPU::getcpuid() << ": Default signalhandler." << endl;
}

void TIP::sig_usr1() {
	O_Stream *my_stream = CPU::stream[CPU::getcpuid()];
	*my_stream << "SIGUSR1  " << CPU::getcpuid() << " Level: " << CPU::getLevel(CPU::getcpuid()) << /*"\n" <<*/ endl;
	//IRQ::sendIPI(0, SIGCONT);
}

void TIP::sig_cont() {
	O_Stream *my_stream = CPU::stream[CPU::getcpuid()];
	*my_stream << "SIGCONT  " << CPU::getcpuid() << " Level: " << CPU::getLevel(CPU::getcpuid()) << /*"\n" <<*/ endl;

	for(volatile int i = 0; i < 10000; ++i) {
	}

}

void TIP::sig_alrm() {
	O_Stream *my_stream = CPU::stream[CPU::getcpuid()];
	
	if(CPU::getcpuid() == CPU::getSignalCounter(SIGALRM)) {
		*my_stream << "SIGALRM  " << CPU::getcpuid() << " Level: " << CPU::getLevel(CPU::getcpuid()) << /*"\n" <<*/ endl;
		CPU::incrSignalCounter(SIGALRM);
	} else {
		*my_stream << "Ich (" << CPU::getcpuid() << ") sende an (" << CPU::getSignalCounter(SIGALRM) << ")." << endl;
		IRQ::sendIPI(CPU::getSignalCounter(SIGALRM), SIGALRM);
//		IRQ::sendIPI(0, SIGUSR1);
	}
}

void TIP::tip_start(int sig) {	

	// Increment of TIP level
	int id = CPU::getcpuid();

	CPU::incrLevel(id);

	//signale freigeben
	// Registersicherung NICHT  notwendig
	//TODO: SYNCHR
	

	sigset_t mask = *CPU::getMask(id);
	// Durch Sperren des aktiven Signals wird dieses nicht erneut eingelocht
	if(sigdelset(&mask, sig) == -1) {
		perror("[TIP] Error @ sigdelset");		return;
	}

	// Rrrremit in die Warteschlange einfuegen.
	CPU::queue[id]->enqueue(get_handler(sig));
	

	if(CPU::getLevel(id) == 1) { 
		while (!(CPU::queue[id]->isEmpty())) {
			// Signale wieder freigeben mit Ausnahme des Aktiven
			IRQ::unlockIRQ(&mask);
			tip_clear(&mask);
			// Signale wieder sperren (ALLE)
			IRQ::lockIRQ(&mask);
		}
	}

	// Decrement of TIP level
	CPU::decrLevel(id);


	// TODO
	// ??? Evtl. Signale wieder sperren ???

}



// porpagate SLIH if there's any
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

// execute SLIH
void TIP::tip_unban(Remit *item) {
	(item->work)();
}
