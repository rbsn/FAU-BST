#ifndef __toc_include__
#define __toc_include__

struct toc {
    void *ebx;
    void *esi;
    void *edi;
    void *ebp;
    void *esp;
};

class Coroutine;

// Diese Funktion laedt die Prozessorregister mit den Inhalten der Struktur regs
void toc_settle(struct toc *, void *, void(*)(Coroutine*), Coroutine*);

extern "C" {
	
	void toc_go (struct toc *regs);
	void toc_switch (struct toc *regs_now, struct toc *reg_then);
}
#endif

