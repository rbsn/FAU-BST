#include "toc.h"

// TOC_SETTLE: bereitet den Kontext der Koroutine fuer den ersten
//             Aufruf vor.
void toc_settle (struct toc* regs, void* tos, void (*kickoff)(Coroutine*), Coroutine* object) {
	int *adr = (int *)tos;

	*(--adr) = (int)object;
	*(--adr) = 0;
	*(--adr) = (int)kickoff;	
	
	regs->esp = adr; //angepasster StackPointer
}
