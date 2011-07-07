/* INCLUDES */
#include "appl.h"
#include "../color.h"		// Zum Setzen von Farb- und Attributeigenschaften
#include "../gotoxy.h"		// Zum Setzen der Cursorposition
#include "scheduler.h"
#include <iostream>
#include <sched.h>

/* GLOBALE VARIABLEN */

extern Application *apps[8];
extern Scheduler scheduler;

void Application::action () {
	//O_Stream *my_stream = CPU::stream[cpu];
	O_Stream *my_stream = CPU::stream[sched_getcpu()];
	int count = 0;
//	O_Stream my_stream;
	while(1) {	
		*my_stream << /*gotoxy(cid * 2, 100) << */color(color::FG_BLACK + cid, color::BG_WHITE - cid, color::OFF) << "Hi " << cid << " on CPU " << cpu << ": "<<count++ << endl;
//		std::cerr << "HI " << cpu << std::endl;
		//kill(getpid(), SIGCONT);
		for(volatile int i = 0; i < 90000000; i++) {

		}
//		if(count == 30 && cid == 0) scheduler.exit(this);
//		if(count == 120 && cid == 4) scheduler.exit(this);
//		if(count % 50 != 0) continue;
//		if(cid == 0) std::cerr << hex << apps[4] << std::endl;
//		if(cid < 4) scheduler.resume(this);
//		else scheduler.resume(this);
		
	}
	
}

