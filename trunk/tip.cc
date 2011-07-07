#include "tip.h"
#include "thread/scheduler.h"
#include "o_stream.h"
#include "color.h"
#include <stdlib.h>
#include <sched.h>

Spinlock TIP::sp_queue;
extern Scheduler scheduler;

// Default signalhandler-function
void TIP::panic() {
  O_Stream *my_stream = CPU::stream[CPU::getcpuid()];
  *my_stream << "SIGPANIC  " << CPU::getcpuid() << endl;

}

// Signalhandler-function for SIGUSR1
void TIP::sig_usr1() {
  O_Stream *my_stream = CPU::stream[CPU::getcpuid()];
  *my_stream << "SIGUSR1  " << CPU::getcpuid() << endl;

}

// Signalhandler-function for SIGCONT
void TIP::sig_cont() {
  O_Stream *my_stream = CPU::stream[CPU::getcpuid()];
  *my_stream << "SIGCONT  " << CPU::getcpuid() << endl;
}

// Signalhandler-function for SIGALRM
void TIP::sig_alrm() {

	O_Stream mystream;
  	//O_Stream *my_stream = CPU::stream[sched_getcpu()];

	mystream << "SIGALRM" << endl;
	scheduler.resume();
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
