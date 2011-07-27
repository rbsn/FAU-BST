#include "spinlock.h"

Spinlock::Spinlock() {
	__sync_lock_release( &isLocked );
}

void Spinlock::lock() {
	//while( __sync_lock_test_and_set( &isLocked, 1 ) ) { }	
}

void Spinlock::unlock() {
	__sync_lock_release( &isLocked );
}
