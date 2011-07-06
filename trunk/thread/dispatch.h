#ifndef __dispatch_include__
#define __dispatch_include__

#include "coroutine.h"
#include "../cpu.h"

class Dispatcher {

public:
	// Konstruktor
	Dispatcher();
	// Hiermit kann abgefragt werden, welche Koroutine gerade im Besitz des aktuellen Prozessors ist
	Coroutine *active();
	// Mit dieser Methode wird die Koroutine first im Life-Pointer des aktuellen Prozessors vermerkt
	// und gestartet
	void go(Coroutine &first);
	// Diese Methode setzt den Life-Pointer des aktuellen Prozessors auf next und fuehrt einen
	// Koroutinenwechsel vom alten zum neuen Life-Pointer durch
	void dispatch(Coroutine &next, int);

	Coroutine* getLifePointer(int cpu);
private:
    Dispatcher(const Dispatcher &copy); // Verhindere Kopieren

	Coroutine **life;
};

#endif
