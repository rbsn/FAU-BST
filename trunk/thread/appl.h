#ifndef __application_include__
#define __application_include__

// INCLUDES
#include "../cpu.h"
#include "../color.h"		// Zum Setzen von Farb- und Attributeigenschaften
#include "../gotoxy.h"		// Zum Setzen der Cursorposition
#include "coroutine.h"
#include "dispatch.h"


class Application : public Coroutine {

private:
    Application(const Application &copy); // Verhindere Kopieren

public:
	// Konstruktor
	Application(void *tos) : Coroutine(tos) { }

    //Enthaelt den Code der Anwendung
    void action();
};

#endif
