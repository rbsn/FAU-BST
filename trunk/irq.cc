#include "irq.h"


// Signalhandler fuer IRQs installieren
// Option = 1: x
// Option = 2: y
// Option = 3: z
void IRQ::installHandler(int sig, void (*signalhandler)(int), int option) {
		
	struct sigaction sa;
	sa.sa_handler = signalhandler;	// Signalhandler zuweisen
	sa.sa_flags = SA_RESTART;		

	sigemptyset(&sa.sa_mask);		// Alle Signale auf 0, daher sind alle zugelassen

	// Aktion (= Signalhandler) fuer sigaction struct festlegen
	if( sigaction(sig, &sa, NULL) == -1) {
		std::cerr << "[IRQ] Error @ Sigaction" << std::endl;
	} 
}

// IRQs bzw. Signale zulassen
void IRQ::addIRQ(int sig) {
	// Geblockt: in Maske auf 1
	
	sigset_t mask; 		
	sigemptyset(&mask); 	// Alle Signale auf 0
	sigaddset(&mask, sig);	// Signal auf 1, alle anderen noch auf 0

	// alle Signale auf 1 werden aus current mask entfernt (SIG_UNBLOCK) und damit zugelassen
	if( syscall(SYS_rt_sigprocmask, SIG_UNBLOCK, &mask, NULL, 4) == -1) {
		perror("[IRQ] Error @ rt_sigprocmask");
	}
} 

// IRQs bzw. Signale nicht zulassen
void IRQ::delIRQ(int sig) {
	
	sigset_t mask; 	
	sigemptyset(&mask);		// Alle Signale auf 0
	sigaddset(&mask, sig);	// Signal auf 1, alle anderen noch auf 0

	// alle Signale auf 1 werden in current mask aufgenommen (SIG_BLOCK) und damit geblockt
	if(	syscall(SYS_rt_sigprocmask, SIG_BLOCK, &mask, NULL, 4) == -1) {
		perror("[IRQ] Error @ rt_sigprocmask");
	}
}

// InterProzessorInterrupt
void IRQ::sendIPI(int cpu_id, int sig) {
	
	if( syscall(SYS_tgkill, cpu_id, cpu_id, sig) == -1) {
		perror("[IRQ] Error @ tgkill");
	}
}

