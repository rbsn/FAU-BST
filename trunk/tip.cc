#include "tip.h"

Spinlock TIP::sp_queue;

// Default signalhandler-function: just an output
void TIP::panic() {
//	O_Stream *my_stream = CPU::stream[CPU::getcpuid()];
//	*my_stream << "CPU " << CPU::getcpuid() << ": Default signalhandler." << endl;
}

void TIP::sig_usr1() {
//	O_Stream *my_stream = CPU::stream[CPU::getcpuid()];
//	*my_stream << "SIGUSR1  " << CPU::getcpuid() <<  endl;
	//IRQ::sendIPI(0, SIGCONT);
}

void TIP::sig_cont() {
//	O_Stream *my_stream = CPU::stream[CPU::getcpuid()];
//	*my_stream << "SIGCONT  " << CPU::getcpuid() << endl;

//	for(volatile int i = 0; i < 10000; ++i) {
//	}

}



void TIP::sig_alrm() {
//	O_Stream *my_stream = CPU::stream[CPU::getcpuid()];
//	*my_stream << "SIGALRM  " << CPU::getcpuid() << endl; 
}

void TIP::tip_start(int sig) {	
	// Increment of TIP level
/*	int id = CPU::getcpuid();
	O_Stream *my_stream = CPU::stream[id];

	//CPU::incrLevel(id);
	//signale freigeben
	// Registersicherung NICHT  notwendig
	//TODO: SYNCHR

	sigset_t mask = *CPU::getMask(id);
	// Durch Sperren des aktiven Signals wird dieses nicht erneut eingelocht
//	if(sigdelset(&mask, sig) == -1) {
//		perror("[TIP] Error @ sigdelset");		return;
//	}

#ifdef Fliessband
	// Rrrremit in die Warteschlange einfuegen.
	CPU::queue[id]->enqueue(get_handler(sig));
#else
	// SIGHUP doesn't need to be handled. This is the notifier for the SLIH-CPU.
	if(sig != SIGHUP) {
		sp_queue.lock();	
		CPU::queue->enqueue(get_handler(sig));
		sp_queue.unlock();
	}
#endif

#ifdef Fliessband
	if(CPU::getFlag_SLIH(id) == false) { 
		CPU::flipFlag_SLIH(id);
		while (!(CPU::queue[id]->isEmpty())) {

#else
	if(id == CONFIG_TIPCPU) {
		// If SLIH-CPU was interrupted by another FLIH it must not do the SLIH stuff.
		if(CPU::flag_SLIH == false) {
		CPU::flag_SLIH = true;
		sp_queue.lock();
		while (!(CPU::queue->isEmpty())) {
			sp_queue.unlock();
#endif		
			// Signale wieder freigeben mit Ausnahme des Aktiven
			IRQ::unlockIRQ(&mask);
			tip_clear(&mask);
			// Signale wieder sperren (ALLE)
			IRQ::lockIRQ(&mask);
#ifdef Zusteller
			sp_queue.lock();
#endif
		}
#ifdef Zusteller
			sp_queue.unlock();
#endif

		}

#ifdef Zusteller
	} else {
//	if(CPU::getLevel(id) == 1) {
		*my_stream << "[" << id << "] sending SIGHUP to " << CONFIG_TIPCPU << ". Sig: " << sig << endl;
		IRQ::sendIPI(CONFIG_TIPCPU, SIGHUP);
//	}
	}
#endif

	// Decrement of TIP level
	//CPU::decrLevel(id);
#ifdef Fliessband
	CPU::flipFlag_SLIH(id);
#else
	CPU::flag_SLIH = false;
#endif
*/
	// TODO
	// ??? Evtl. Signale wieder sperren ???

}



// porpagate SLIH if there's any
void TIP::tip_clear(sigset_t *mask) {
/*	Remit *next;
	do { 
		// Signale wieder sperren mit Ausnahme des AKTIven
		IRQ::lockIRQ(mask);
#ifdef Fliessband
		if((next = (Remit *) CPU::queue[CPU::getcpuid()]->dequeue())) {
#else
		sp_queue.lock();
		if((next = (Remit *) CPU::queue->dequeue())) {
			sp_queue.unlock();
		
#endif
				IRQ::unlockIRQ(mask);
				tip_unban(next);
		} else {
#ifdef Zusteller
			sp_queue.unlock();
#endif
			IRQ::unlockIRQ(mask);
		}

	} while (next != 0);*/
}

// execute SLIH
void TIP::tip_unban(Remit *item) {
	(item->work)();
}
