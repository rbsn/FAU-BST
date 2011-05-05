#include "hal.h"
#include <iostream>
//#include <stdlibc>


using namespace std;

void hello(void) {
	while(1) {
		
		cout << "Hallo Welt!"<< endl;

	}
}



int main() {

	CPU::boot_cpus(hello, sysconf(_SC_NPROCESSORS_ONLN));

	// Waitpid noch einstellen!!

	return 0;

}


// Freigabe Stacks? -> munmap
