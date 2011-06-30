#include "spinlock.h"

//static volatile int owner;

Spinlock::Spinlock() {
	__sync_lock_release( &isLocked );
}

void Spinlock::lock() {
	//int i = 0;
	
	while( __sync_lock_test_and_set( &isLocked, 1 ) ) { 
		//i++; 
		//if(i == 1000) {
		//	volatile int tip = organizer.active()->cid;
		//	break;
		//}
	}

	
	// owner = organizer.active()->cid;	

}

void Spinlock::unlock() {
	__sync_lock_release( &isLocked );
}
