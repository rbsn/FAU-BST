#include "idleapp.h"

// Konstruktor

void IdleApp::action () {
	O_Stream idlestream;
	int counter = 0;

	while(1) {
		idlestream << /*gotoxy(cid * 2, 100) << color(color::FG_BLACK + cid, color::BG_WHITE - cid, color::OFF) <<*/ "Idle " << cid << " on CPU " << cpu << ": "<< counter++ << endl;
		for(volatile int i = 0; i < 40000000; i++) {

		}
	}
}

