/* INCLUDES */
#include "appl.h"
#include <iostream>

/* GLOBALE VARIABLEN */

extern Application *apps[8];
extern Dispatcher dispatcher;

void Application::action () {
	O_Stream *my_stream = CPU::stream[cpu];
	int count = 0;
//	O_Stream my_stream;
	while(1) {	
		*my_stream << gotoxy(cid * 2, 100) << color(color::FG_BLACK + cid, color::BG_WHITE - cid, color::OFF) << "Hi " << cid << " on CPU " << cpu << ": "<<count++ << endl;
//		std::cerr << "HI " << cpu << std::endl;
		for(volatile int i = 0; i < 40000000; i++) {

		}
		if(count % 50 != 0) continue;
//		if(cid == 0) std::cerr << hex << apps[4] << std::endl;
		if(cid < 4) dispatcher.dispatch(*apps[cid + 4], cpu);
		else dispatcher.dispatch(*apps[cid - 4], cpu);
		
	}
	
}

