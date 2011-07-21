#ifndef __schedule_include__
#define __schedule_include__

#include "dispatch.h"
#include "../queue.h"
#include "../cpu.h"
#include "entrant.h"
#include "idleapp.h"

class Scheduler : public Dispatcher {

public:
	// Konstruktor
	Scheduler();
	// Starten des Schedulings. Diese Methode setzt das Scheduling in Gang, indem der erste Prozess
	// von der Ready-Liste entfernt und aktiviert wird. In MPStuBS muss diese Methode auf jeder CPU
	// einmal aufgerufen werden, um auf dem jeweiligen Prozessor den ersten Prozess einzulasten
	void schedule();
	// Anmelden eines Prozesses zum Scheduling
	void ready(Entrant &that, int);
	// Selbstbeenden des aktuellen Prozesses
	void exit(Entrant *);
	// Beenden eines beliebigen Prozesses
	void kill(Entrant &that);
	// Ausloesen eines Prozesswechsels
	void resume();
	void resume(Entrant *);
	void resume(Entrant *, Entrant *);

	// Setzt einen dedizierten Idle-Thread fuer die entsprechende CPU
//	void set_idle_thread(int cpuid, Entrant *thread);
	// Legt den aktuellen Prozessor schlafen, solange keine Prozesse vorhanden sind
//	void sleep_until_IRQ();

//	bool isCpuIdle();
//	bool isReadylistEmpty();
	
	void setCPUQueue(int cpuid, Queue *q);

private:
    Scheduler (const Scheduler &copy); // Verhindere Kopieren

	void sched_enqueue(Entrant *, int);

	Entrant *sched_dequeue(int);


	void init_readylist();
	
	bool *idle;

//	Queue **readylist;	// TODO ASPECT SLICE
};

#endif
