#include "dispatch.h"
#include <iostream>
// Konstruktor
Dispatcher::Dispatcher() {
	life = new Coroutine*[CPU::getNumOfBootedCPUs()];
}

// Hiermit kann abgefragt werden, welche Koroutine gerade im Besitz des aktuellen Prozessors ist
Coroutine * Dispatcher::active() {
	int cpuid = CPU::getcpuid();
	return life[cpuid];	// TODO
}

// Mit dieser Methode wird die Koroutine first im Life-Pointer des aktuellen Prozessors vermerkt
// und gestartet
void Dispatcher::go(Coroutine &first) {
	int cpuid = CPU::getcpuid();
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
	old->resume(next);
}

Coroutine* Dispatcher::getLifePointer(int cpuid) {
	return life[cpuid];
}
