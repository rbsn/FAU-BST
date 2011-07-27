#include "dispatch.h"
#include "../cpu.h"
#include "sched.h"
#include <iostream>
#include "../gotoxy.h"
#include "coroutine.h"

// Konstruktor
Dispatcher::Dispatcher() {
#ifdef CONFIG_SimpleStack
	life = new Coroutine *[_SC_NPROCESSORS_ONLN];
#endif
}

// Hiermit kann abgefragt werden, welche Koroutine gerade im Besitz des aktuellen Prozessors ist
Coroutine * Dispatcher::active() {
#ifdef CONFIG_SimpleStack
	int cpuid = Coroutine::getCPUofActive();
	return life[cpuid];
#else
	return Coroutine::getActiveCoroutine();
#endif
}

// Mit dieser Methode wird die Koroutine first im Life-Pointer des aktuellen Prozessors vermerkt
// und gestartet
void Dispatcher::go(Coroutine &first) {
	// Da noch in keinem Koroutinen, kann einfach cpuid ausgelesen werden uber CPU-Stack
	int cpuid = CPU::getcpuid();
	CPU::activeThread[cpuid] = first.stackaddr_begin;
	
#ifdef CONFIG_SimpleStack
	life[cpuid] = &first;
#endif
	first.cpu = cpuid;
	first.go();
}

// Diese Methode setzt den Life-Pointer des aktuellen Prozessors auf next und fuehrt einen
// Koroutinenwechsel vom alten zum neuen Life-Pointer durch
void Dispatcher::dispatch(Coroutine &next, int cpuid) {
	Coroutine *old = active();

#ifdef CONFIG_SimpleStack
	life[cpuid] = &next;
#endif
	next.cpu = cpuid;
	// Nach Resume (Koroutinenwechsel) wird Stackanfangsadresse der neuen Koroutine eingetragen 
	CPU::activeThread[cpuid] = next.stackaddr_begin;
	
	old->resume(next);
}

Coroutine* Dispatcher::getLifePointer(int cpuid) {
	return life[cpuid];
}
