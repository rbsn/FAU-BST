#include "coroutine.h"
#include <iostream>

int Coroutine::numCoroutines = 0;

// Konstruktor
Coroutine::Coroutine(void *tos) {
	cid = numCoroutines++;
	killed = false;
	toc_settle(&regs, tos, kickoff, this);
}

// Aktiviert die erste Koroutine auf einem Prozessor
void Coroutine::go() {
	toc_go(&regs);
}

// Wechsel von der aktuell laufenden Koroutine zur naechsten
void Coroutine::resume(Coroutine &next) {
	toc_switch(&regs, &next.regs);
}

// Setzen des Kill-Flags. Prozess wechselt in den Zustand sterbend
void Coroutine::set_kill_flag() {
	killed = true;
}

// Zuruecksetzen des Kill-Flags. Prozess ist damit gestorben
void Coroutine::reset_kill_flag() {
	killed = false;
}

// Abfragen des Kill-Flags. Nachschauen, ob der Prozess gerade stirbt
bool Coroutine::dying() {
	return killed;
}

