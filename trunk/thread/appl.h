// $Date: 2009-09-22 15:20:27 +0200 (Tue, 22 Sep 2009) $, $Revision: 2221 $, $Author: benjamin $
// kate: encoding ISO-8859-15;
// vim: set fileencoding=latin-9:
// -*- mode: c; coding: latin-9 -*- 


#ifndef __application_include__
#define __application_include__

/*! \file
 *  \brief Enthaelt die Klasse Application 
 */

#include "../cpu.h"
#include "coroutine.h"
#include "../gotoxy.h"
#include "dispatch.h"


/*! \brief Die Klasse Application definiert die einzige Anwendung von OO-Stubs.
 */
class Application : public Coroutine {

private:
    Application(const Application &copy); // Verhindere Kopieren

public:
//	Application() {}	// ADDED: Standardkonstruktor, da sonst Compiler-Fehler
// Konstruktor
	Application(void *tos) : Coroutine(tos) { }

    //Enthaelt den Code der Anwendung
    void action();
};

#endif
