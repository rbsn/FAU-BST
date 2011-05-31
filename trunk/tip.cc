#include "tip.h"
Remit *defaultRemit;

// Standard-Konstruktor
TIP::TIP() {
//	Remit defaultRemit(panic);
	defaultRemit = new Remit(panic);

	for(int i = 0; i < NUM_OF_SIGNAL-1; i++) {
		set_handler(defaultRemit, i);
	}
}

// Destruktor
TIP::~TIP() {

}

void TIP::panic() {
	O_Stream my_stream;
	my_stream << "'N Signal, du Looser!" << endl;
}

void TIP::tip_entry(int sig) {
	level++;
	//signale freigeben
	//register sichern???

	// TODO:Spezifische start-fkt von remit obj
	tip_start(sig);		// invoke associated FLIH

	tip_check();		// fall into SLIH check

}

void TIP::tip_start(int sig) {
	//TODO: SYNCHRO

	// Rrrremit in die Warteschlange einfuegen.
	queue.enqueue(get_handler(sig));
}

void TIP::tip_check() {
	if(level == 1) { 
		while (!queue.isEmpty()) {
			tip_clear();
		}
	}

	level--;
}

void TIP::tip_clear() {
	Remit *next;
	do { 
		if((next = (Remit *)queue.dequeue()))
				tip_unban(next); 
	} while (next != 0);
}

void TIP::tip_unban(Remit *item) {
	(item->work)();
}
