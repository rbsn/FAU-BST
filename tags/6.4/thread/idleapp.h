#ifndef __idleapp_include__
#define __idleapp_include__

#include "entrant.h"
#include "../color.h"
#include "../o_stream.h"

class IdleApp : public Entrant {

private:
    IdleApp(const IdleApp &copy); // Verhindere Kopieren

public:
//	Application() {}	// ADDED: Standardkonstruktor, da sonst Compiler-Fehler
// Konstruktor
	IdleApp(void *tos) : Entrant(tos) {}

    //Enthaelt den Code der Anwendung
    void action();
};

#endif
