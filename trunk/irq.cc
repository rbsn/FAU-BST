#include "irq.h"


// Signalhandler fuer IRQs installieren, ununterbrechbare Ausfuehrung des Signalhandlers
void IRQ::installHandler(int sig, void (*signalhandler)(int)) {
		
	struct sigaction sa;
	sa.sa_handler = signalhandler;	// Signalhandler zuweisen
	sa.sa_flags = SA_RESTART;		

	sigfillset(&sa.sa_mask);		// Alle Signale auf 1, daher sind alle ausgeschlossen

	// Aktion (= Signalhandler) fuer sigaction struct festlegen
	if( sigaction(sig, &sa, NULL) == -1) {
		std::cerr << "[IRQ] Error @ Sigaction" << std::endl;
	} 
}

// IRQs bzw. Signale zulassen
// welche Signale werden von CPU angenommen (vgl. Interrupt Description Table im APIC)
void IRQ::unlockIRQ(sigset_t *mask) {
	
	// alle Signale auf 1 werden aus current mask entfernt (SIG_UNBLOCK) und damit zugelassen
	if( syscall(SYS_rt_sigprocmask, SIG_UNBLOCK, mask, NULL, 8) == -1) {
		perror("[IRQ_unlock] Error @ rt_sigprocmask");
	}
} 

// IRQs bzw. Signale nicht zulassen
// welche Signale werden von CPU NICHT angenommen (vgl. Interrupt Description Table im APIC)
void IRQ::lockIRQ(sigset_t *mask) {

	// alle Signale auf 1 werden in current mask aufgenommen (SIG_BLOCK) und damit geblockt
	if(	syscall(SYS_rt_sigprocmask, SIG_BLOCK, mask, NULL, 8) == -1) {
		perror("[IRQ_lock] Error @ rt_sigprocmask");
	}
}

// InterProzessorInterrupt der aufrufenden CPU an cpu_id
void IRQ::sendIPI(int cpuid, int sig) {
	
	if( syscall(SYS_tgkill, getpid(), CPU::getTID(cpuid), sig) == -1) {
		perror("[IRQ] Error @ tgkill");
	}
}

