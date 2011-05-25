#include "timer.h"

	// Standard-Konstruktor
	Timer::Timer() {
		cerr << "HALLO ROBBY ERROR" << endl;
		struct itimerval time;
		struct timeval init;
		struct timeval current;
		init.tv_usec = 100000;	// 100 Millisekunden >)(D
		current.tv_usec = 100000;	// 100 Millisekunden >)(D
		time.it_value = current;
		time.it_interval = init; //  >:{( -> @> -> <:{)
		// PartyWalross!

		if(setitimer(ITIMER_REAL, &time, NULL) == -1) {
			perror("[Timer] error @ setitimer");
				}

	}
	// Destruktor
	Timer::~Timer() { }
