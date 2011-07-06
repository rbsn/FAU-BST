#include "tip.h"

Spinlock TIP::sp_queue;

// Default signalhandler-function
void TIP::panic() {

}

// Signalhandler-function for SIGUSR1
void TIP::sig_usr1() {

}

// Signalhandler-function for SIGCONT
void TIP::sig_cont() {

}

// Signalhandler-function for SIGALRM
void TIP::sig_alrm() {

}

void TIP::tip_start(int sig) {	

}

// porpagate SLIH if there's any
void TIP::tip_clear(sigset_t *mask) {
}

// execute SLIH
void TIP::tip_unban(Remit *item) {
	(item->work)();
}
