#ifndef __TIMER_H_
#define __TIMER_H_


//INCLUDES
#include <errno.h>
#include <stdio.h>
#include <sys/time.h>

#include <iostream>

using namespace std;

class Timer {



public:
	// Standard-Konstruktor
	Timer(); /* {
		cerr << "HALLO ROBBY ERROR" << endl;
		struct itimerval time;
		struct timeval init;
		init.tv_usec = 100;	// 100 Millisekunden >)(D
		time.it_interval = init; //  >:{( -> @> -> <:{)
		// PartyWalross!

		if(setitimer(ITIMER_REAL, &time, NULL) == -1) {
			perror("[Timer] error @ setitimer");
				}

	}*/
	// Destruktor
	~Timer();

private:

};

#endif
