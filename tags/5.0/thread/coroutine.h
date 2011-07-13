#ifndef __Coroutine_include__
#define __Coroutine_include__

#include "toc.h"

class Coroutine {

private:
	toc regs;
	static int numCoroutines;
	bool killed;

public:
//	Coroutine() {}  // ADDED: Standardkonstruktor, da sonst Compiler-Fehler

	// Konstruktor
	Coroutine(void *tos);

	// Stackpointer auf Stackanfang der Koroutine
	void *stackaddr_begin;

	int cid;
	// Aktiviert die erste Korouting auf einem Prozessor
	void go();
	// Wechsel von der aktuell laufenden Koroutine zur naechsten
	void resume(Coroutine &next);
	// Methode, die als Koroutine ausgefuehrt werden soll
	virtual void action()=0;

	// Setzen des Kill-Flags. Prozess wechselt in den Zustand sterbend
	void set_kill_flag();
	// Zuruecksetzen des Kill-Flags. Prozess ist damit gestorben
	void reset_kill_flag();
	// Abfragen des Kill-Flags. Nachschauen, ob der Prozess gerade stirbt
	bool dying();

	int cpu;
	
	// Gets the CPU-ID of active running thread, -1 on error
	static int getCPUofActive();

};
	// Funktion zum Starten einer Koroutine
	void kickoff(Coroutine *object);
	

#endif
