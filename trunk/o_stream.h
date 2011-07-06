#ifndef __o_stream_include__
#define __o_stream_include__

#define SIZE_ARRAY 32

#include <stdio.h>
#include <string>
#include "gotoxy.h"
#include "color.h"

using namespace std;

class O_Stream {

private:
   O_Stream(const O_Stream &copy); // Verhindere Kopieren
    
   string *buf;

public:
	// Konstruktor
	O_Stream();
	// Destruktor
	~O_Stream(); 
	// Stellt ein einzelnes Zeichen dar
	O_Stream & operator<< (char c);
	O_Stream & operator<< (unsigned char c);
	// Darstellung einer nullterminierten Zeichenkette
	O_Stream & operator<< (const char *string);
	O_Stream & operator<< (string&);
	// Darstellung ganzer Zahlen im Zahlensystem zur Basis base
	O_Stream & operator<< (short ival);
	O_Stream & operator<< (unsigned short ival);
	O_Stream & operator<< (int ival);
	O_Stream & operator<< (unsigned int ival);
	O_Stream & operator<< (long ival);
	O_Stream & operator<< (unsigned long ival);
	// Darstellung eines Zeigers als hexadezimale ganze Zahl
	O_Stream & operator<< (void *ptr);
	// Aufruf einer Manipulatorfunktion
	O_Stream & operator<< (O_Stream &(*f)(O_Stream &));

	// Aufruf eines clear-Konstruktors, um den Screen zu loeschen und den Cursor auf (0,0) zu setzen
	//O_stream & operator<< (clear cl);
	// Aufruf einer colour-Konstruktors, um Farbattribute zu setzen
	O_Stream & operator<< (color co);
	// Aufruf eines gotoxy-Konstruktors, um die Cursorposition auf (x,y) zu setzen
	O_Stream & operator<< (gotoxy g); 
	
	// Basis des zur Anzeige verwendeten Zahlensystems (z.B. 2, 8, 10, 16)
	int base;
};

// Cleart den Screen
O_Stream& clear (O_Stream &os);
// Fuegt einen Zeilenumbruch in die Ausgabe ein
O_Stream& endl (O_Stream &os);
// Waehlt das binaere Zahlensystem aus
O_Stream& bin (O_Stream &os);
 // Waehlt das oktale Zahlensystem aus
O_Stream& oct (O_Stream &os);
// Waehlt das dezimale Zahlensystem aus
O_Stream& dec (O_Stream &os);
// Waehlt das Hexadezimale Zahlensystem aus
O_Stream& hex (O_Stream &os);

#endif
