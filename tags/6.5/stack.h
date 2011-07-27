#ifndef __STACK_H__
#define __STACK_H__

//INCLUDES
#include "thread/appl.h"


class Stack {

public:
	static void *megastack;
	static Application *apps[CONFIG_APPS]; 

	static void *allocate_stack() ;

	static void create_apps(int anzahl) ;
	
};

#endif
