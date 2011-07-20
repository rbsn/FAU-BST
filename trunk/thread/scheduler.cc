/* INCLUDES */
#include "scheduler.h"
#include <stdlib.h>
#include "../o_stream.h"

extern IdleApp *idleapps[4];

// Konstruktor
Scheduler::Scheduler() {
	// Every CPU has one ReadyList
	//readylist = new Queue *[_SC_NPROCESSORS_ONLN];		// TODO ASPECT
	init_readylist();
	// Every CPU has one idle-Thread
	idle = new bool[_SC_NPROCESSORS_ONLN];

}

void Scheduler::init_readylist() {
	
}

void Scheduler::sched_enqueue(Entrant *e, int cpuid) {
//	readylist[cpuid]->enqueue(e);
}

Entrant *Scheduler::sched_dequeue(int cpuid) {
//	return (Entrant *) readylist[cpuid]->dequeue();
	return 0;
}

// Readylist-Queue an CPU binden (dies findet in cpu.cc statt)
void Scheduler::setCPUQueue(int cpuid, Queue *q) {
	
//	readylist[cpuid] = q;
}

// Anmelden eines Prozesses zum Scheduling
void Scheduler::ready(Entrant &that, int cpuid) {
	//readylist[cpuid]->enqueue(&that);
	sched_enqueue(&that, cpuid);
}


// Starten des Schedulings. Diese Methode setzt das Scheduling in Gang, indem der erste Prozess
// von der Ready-Liste entfernt und aktiviert wird. In MPStuBS muss diese Methode auf jeder CPU
// einmal aufgerufen werden, um auf dem jeweiligen Prozessor den ersten Prozess einzulasten
void Scheduler::schedule() {
	int cpuid = CPU::getcpuid();
		
	//Entrant *tmp = (Entrant *)readylist[cpuid]->dequeue();
	Entrant *tmp = sched_dequeue(cpuid);


	//Falls noch keine Koroutinen verfuegbar -> idle
	if(tmp == 0) {
		idle[cpuid] = true;
		go(*idleapps[cpuid]); 
	} else { 
		idle[cpuid] = false;
		go(*tmp);
	}
}

// Selbstbeenden des aktuellen Prozesses
// => Nicht ans Ende der Liste wieder eintragen
void Scheduler::exit(Entrant *self) {
	int cpuid = Coroutine::getCPUofActive();
	//Entrant *tmp = (Entrant *)readylist[cpuid]->dequeue();
	Entrant *tmp = sched_dequeue(cpuid);

	if(tmp == 0) {
		//keine App mehr in Ready-Liste => gehe idle
		idle[cpuid] = true;
		dispatch(*idleapps[cpuid], cpuid); 
	} else {
		idle[cpuid] = false;
		dispatch(*tmp, cpuid);
	}
}
// Ausloesen eines Prozesswechsels (preemptive)
void Scheduler::resume() {
	Entrant *e = (Entrant *)active();
	resume(e);
}

// Manuelles Ausloesen mit resume(this); (cooperative)
void Scheduler::resume(Entrant *self) {
	int cpuid = Coroutine::getCPUofActive();

	//Entrant *tmp = (Entrant *)readylist[cpuid]->dequeue();
	Entrant *tmp = sched_dequeue(cpuid);

	// keine ausfuehrbare Coroutine mehr vorhanden
	if(tmp == 0) {
		return;
	} else {
//		readylist[cpuid]->enqueue(self);
		sched_enqueue(self, cpuid);
		idle[cpuid] = false;
		dispatch(*tmp, cpuid);
	}
}
