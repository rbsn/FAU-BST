#include "coroutine.h"
#include "../cpu.h"
#include "../defines.h"

int Coroutine::numCoroutines = 0;

// Konstruktor
Coroutine::Coroutine(void *tos) {
	cid = numCoroutines++;
	killed = false;

	// Stackbeginnadresse der Koroutine eintragen
	stackaddr_begin = tos;
	
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

int Coroutine::getCPUofActive() {
	int addr = 0;

	for(int i = 0; i < CPU::getNumOfBootedCPUs(); ++i) {
		if( ((int *) CPU::activeThread[i] - sizeof(int *) >= &addr) && 
			((int *) (CPU::activeThread[i] - CONFIG_APPSTACKSIZE) <= &addr) ) {
			
			return i;
		}
	}

	return -1;
}

Coroutine * Coroutine::getActiveCoroutine() {
	// Stacklokale Variable anlegen
	int sp = 0;
	int sb, *pd;

	// Unteres Stackende ist Pointeradresse mit unteren 16 bits '1'
	// weil 2^17 = 128 * 1024 Byte

	sb = (int)(&sp) | 0xfff;

//	std::cerr << "SP: " << &sp << "SB: " << std::hex << sb << std::endl;

	pd = (int *)(sb - (sizeof(char*)-1) ) ;

//	std::cerr << "PD: " << pd << " Coroutine*: " << *pd << std::endl;

	return (Coroutine *) *pd;
}
