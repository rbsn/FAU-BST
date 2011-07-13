#include "dispatch.h"
#include "../cpu.h"
#include "sched.h"
#include <iostream>
#include "../gotoxy.h"
#include "coroutine.h"

// Konstruktor
Dispatcher::Dispatcher() {
	life = new Coroutine *[_SC_NPROCESSORS_ONLN];
}

// Hiermit kann abgefragt werden, welche Koroutine gerade im Besitz des aktuellen Prozessors ist
Coroutine * Dispatcher::active() {
//	int cpuid = sched_getcpu();
	int cpuid = Coroutine::getCPUofActive();
	std::cerr << "CPUID dispatcher " << cpuid << std::endl;
//	O_Stream my_stream;
//	my_stream <</* gotoxy(0,0) <<*/ "cpuid: " << cpuid << endl;
	return life[cpuid];	// TODO
}

// Mit dieser Methode wird die Koroutine first im Life-Pointer des aktuellen Prozessors vermerkt
// und gestartet
void Dispatcher::go(Coroutine &first) {
	//int cpuid = sched_getcpu();

	// 
	int cpuid = CPU::getcpuid();
	CPU::activeThread[cpuid] = first.stackaddr_begin;
	
	life[cpuid] = &first;
	first.cpu = cpuid;
	first.go();
}

// Diese Methode setzt den Life-Pointer des aktuellen Prozessors auf next und fuehrt einen
// Koroutinenwechsel vom alten zum neuen Life-Pointer durch
void Dispatcher::dispatch(Coroutine &next, int cpuid) {
//	int cpuid = CPU::getcpuid();
	Coroutine *old = life[cpuid];
	life[cpuid] = &next;
	next.cpu = cpuid;
//	std::cerr << "CPU ID of Coroutine with stackptr " << old->stackaddr_begin << " is: " << old->cpu << std::endl; 
	// Nach Resume (Koroutinenwechsel) wird Stackanfangsadresse der neuen Koroutine eingetragen 
	CPU::activeThread[cpuid] = next.stackaddr_begin;
	
	old->resume(next);
}

Coroutine* Dispatcher::getLifePointer(int cpuid) {
	return life[cpuid];
}
