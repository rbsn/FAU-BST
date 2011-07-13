/* INCLUDES */
#include "scheduler.h"
#include <stdlib.h>
#include "../o_stream.h"

extern IdleApp *idleapps[4];

// Konstruktor
Scheduler::Scheduler() {
	// Every CPU has one ReadyList
	readylist = new Queue *[_SC_NPROCESSORS_ONLN];
	// Every CPU has one idle-Thread
	idle = new bool[_SC_NPROCESSORS_ONLN];

}

// Readylist-Queue an CPU binden (dies findet in cpu.cc statt)
void Scheduler::setCPUQueue(int cpuid, Queue *q) {
	
	readylist[cpuid] = q;
}

// Anmelden eines Prozesses zum Scheduling
void Scheduler::ready(Entrant &that, int cpuid) {
//	that.reset_kill_flag();
//	O_Stream mystream;
	//mystream << "Putting in readylist " << endl;
	readylist[cpuid]->enqueue(&that);
//	int bits = 0;
//	for (unsigned int i=0; i < CPU::getNumberOfBootedCPUs(); i++) {
//		if (idle[i]) {
//			bits = bits | (1 << i);
//		}
//	}
//	IRQ::sendIPI(bits, Plugbox::assassin);
}


// Starten des Schedulings. Diese Methode setzt das Scheduling in Gang, indem der erste Prozess
// von der Ready-Liste entfernt und aktiviert wird. In MPStuBS muss diese Methode auf jeder CPU
// einmal aufgerufen werden, um auf dem jeweiligen Prozessor den ersten Prozess einzulasten
void Scheduler::schedule() {
	int cpuid = CPU::getcpuid();
		
//	O_Stream mystream;
//	mystream << "CPU: " << cpuid << endl;
	Entrant *tmp = (Entrant *)readylist[cpuid]->dequeue();
	
	//Falls noch keine Koroutinen verfuegbar -> idle
	if(tmp == 0) {
		//	cpu.disable_int();
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
	//int cpuid = self->cpu;
	//int cpuid = sched_getcpu();
	int cpuid = Coroutine::getCPUofActive();
	Entrant *tmp = (Entrant *)readylist[cpuid]->dequeue();

	if(tmp == 0) {
		//keine App mehr in Ready-Liste => gehe idle
//		DBG << "[scheduler-exit] no app in ready-list" << endl;
		idle[cpuid] = true;
		dispatch(*idleapps[cpuid], cpuid); 
	} else {
//		if(tmp->dying()) {
//			tmp->reset_kill_flag(); 	//tmp nicht neu einfuegen in readylist. Damit ist tmp gestorben
//			exit(); // Erneuter Aufruf bis Koroutine gefunden wurde, die eingelastet werden kann
//		} else {
			idle[cpuid] = false;
			dispatch(*tmp, cpuid);
//		}
	}
}
/*
// Beenden eines beliebigen Prozesses
void Scheduler::kill(Entrant &that) {
	if(!readylist.remove(&that)) {
		//Falls bereits aktiv auf anderem Prozessor
		that.set_kill_flag();
		for (unsigned int i=0; i < CPU::getNumberOfBootedCPUs(); i++) {
			if (that.cid  == getLifePointer(i)->cid) {
				//int bits = (1 << i);
				int cpu = i;
				//DBG << "CPU-Bits: " << bits << " i: " << i << " cid: " 
				//	<< that.cid << " LPcid: " << getLifePointer(i)->cid << endl;
				IRQ::sendIPI(bits, Plugbox::assassin);
				return;
			}
		}
	}
}
*/
// Ausloesen eines Prozesswechsels (preemptive)
void Scheduler::resume() {
	Entrant *e = (Entrant *)active();
	resume(e);
}

// Manuelles Ausloesen mit resume(this); (cooperative)
void Scheduler::resume(Entrant *self) {
	//int cpuid = self->cpu;
	//int cpuid = sched_getcpu();
	int cpuid = Coroutine::getCPUofActive();

	Entrant *tmp = (Entrant *)readylist[cpuid]->dequeue();

	// keine ausfuehrbare Coroutine mehr vorhanden
	if(tmp == 0) {
	//	mystream << "no resume" << endl;
//		DBG << "[scheduler] no app in ready-list" << endl;
		// Aktive Coroutine darf weiterlaufen
//		if(!aktiv->dying()) return;
//		else {
		//	cpu.disable_int();
			//idle[cpuid] = true;
			//dispatch(*idleapps[cpuid], cpuid); //sonst idle
			return;
//		}
	} else {
	//	mystream << "resume" << endl;
		//	DBG << "[" << active()->cid << "] New Entrant: " << tmp->cid << endl;
		//	if(tmp->dying()) {
		//		tmp->reset_kill_flag(); 	//tmp nicht neu einfuegen in readylist. Damit ist tmp gestorben
		//		resume(); 		//andere Koroutine starten
		//	} else {
				readylist[cpuid]->enqueue(self);
				idle[cpuid] = false;
				dispatch(*tmp, cpuid);
		//	}
	}
}
	
/*	
// Setzt einen dedizierten Idle-Thread fuer die entsprechende CPU
void Scheduler::set_idle_thread(int cpuid, Entrant *thread) {
	// TODO
	
}

bool Scheduler::isReadylistEmpty() {
	return readylist.isEmpty();
}

// Legt den aktuellen Prozessor schlafen, solange keine Prozesse vorhanden sind
void Scheduler::sleep_until_IRQ() {
	// TODO

}

bool Scheduler::isCpuIdle() {
	return idle[cpuid];
}
*/
