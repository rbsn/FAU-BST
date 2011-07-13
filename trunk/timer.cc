#include "timer.h"
#include <iostream>

// Standard-Konstruktor
Timer::Timer() {

	struct itimerval time;
	
	struct timeval inital;
	struct timeval current;
	inital.tv_sec = 0;
	current.tv_sec = 0;
//	inital.tv_usec = 100000;	// 100000 Mikrosekunden = 100 Millisekunden
//	current.tv_usec = 100000;	// 100 Millisekunden >)(D
	inital.tv_usec = 200000;	// 500 Millisekunden 
	current.tv_usec = 200000;	//   ---- ' ' ----
	time.it_value = current;
	time.it_interval = inital; 
	
	if(setitimer(ITIMER_REAL, &time, NULL) == -1) {
		perror("[Timer] error @ setitimer");
	}

//	std::cerr << "TIMER" << std::endl;
}

// Destruktor
Timer::~Timer() { }
