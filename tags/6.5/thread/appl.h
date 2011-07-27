#ifndef __application_include__
#define __application_include__

// INCLUDES
#include "../cpu.h"
#include "entrant.h"


class Application : public Entrant {

private:
    Application(const Application &copy); // Verhindere Kopieren

public:
	// Konstruktor
	Application(void *tos) : Entrant(tos) { }

    //Enthaelt den Code der Anwendung
    void action();
};

#endif
