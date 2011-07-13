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
	int cpuid = Coroutine::getCPUofActive();
	return life[cpuid];
}

// Mit dieser Methode wird die Koroutine first im Life-Pointer des aktuellen Prozessors vermerkt
// und gestartet
void Dispatcher::go(Coroutine &first) {
	// Da noch in keinem Koroutinen, kann einfach cpuid ausgelesen werden uber CPU-Stack
	int cpuid = CPU::getcpuid();
	CPU::activeThread[cpuid] = first.stackaddr_begin;
	
	life[cpuid] = &first;
	first.cpu = cpuid;
	first.go();
}

// Diese Methode setzt den Life-Pointer des aktuellen Prozessors auf next und fuehrt einen
// Koroutinenwechsel vom alten zum neuen Life-Pointer durch
void Dispatcher::dispatch(Coroutine &next, int cpuid) {
	Coroutine *old = life[cpuid];
	life[cpuid] = &next;
	next.cpu = cpuid;
	// Nach Resume (Koroutinenwechsel) wird Stackanfangsadresse der neuen Koroutine eingetragen 
	CPU::activeThread[cpuid] = next.stackaddr_begin;
	
	old->resume(next);
}

Coroutine* Dispatcher::getLifePointer(int cpuid) {
	return life[cpuid];
}
