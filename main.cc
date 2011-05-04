#include "hal.h"
#include <iostream>
//#include <stdlibc>


using namespace std;

int main() {


	long numCPUs = getOnlineCPUs();

	if(numCPUs == -1) {
		cerr << "Error: getOnlineCPUs" << endl;
		return -1;
	}

	return 0;

}


// Freigabe Stacks? -> munmap
