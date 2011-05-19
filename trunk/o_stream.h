// $Date: 2009-11-19 16:49:44 +0100 (Thu, 19 Nov 2009) $, $Revision: 2342 $, $Author: benjamin $
// kate: encoding ISO-8859-15;
// vim: set fileencoding=latin-9:
// -*- mode: c; coding: latin-9 -*- 

/*! \file 
 *  \brief Hier ist die Klasse O_Stream implementiert. 
 *  Neben der Klasse O_Stream sind hier auch die Manipulatoren hex, dec, oct 
 *  und bin fuer die Wahl der Basis bei der Zahlendarstellung, sowie endl    
 *  fuer den Zeilenumbruch \b deklariert. 
 *  
 *  \par Manipulatoren
 *  Um bei der Textformatierung mit Hilfe der Klasse O_Stream das Zahlensystem
 *  bequem waehlen und Zeilenumbrueche einfuegen zu koennen, sollen sogenannte
 *  Manipulatoren definiert werden. 
 *  Der Ausdruck <b>kout << "a = " << dec << a << " ist hexadezimal " << hex << a << endl;</b>
 *  soll dann beispielsweise den Wert der Variablen a erst in dezimaler und 
 *  dann in hexadezimaler Schreibweise formatieren und zum Schluss einen
 *  Zeilenumbruch anfuegen. 
 *  
 *  Die gewuenschten Eigenschaften koennen realisiert werden, wenn hex, dec,
 *  oct, bin und endl als Funktionen (d.h. nicht als Methoden der Klasse 
 *  O_Stream) definiert werden, die als Parameter und Rueckgabewert jeweils 
 *  eine Referenz auf ein O_Stream Objekt erhalten bzw. liefern. Durch diese
 *  Signatur wird bei dem genannten Ausdruck der bereits erwaehnte Operator
 *  O_Strea
 *  nur noch die als Parameter angegebene Funktion ausfuehren muss.
 *  
 *  \par Anmerkung
 *  Der Manipulatorbegriff wurde dem Buch 
 *  <a href="http://ivs.cs.uni-magdeburg.de/bs/service/buecher/cc.shtml#Stroustrup">"Bjarne Stroustrup: The C++ Programming Language"</a> entnommen.
 *  Dort finden sich auch weitergehende Erlaeuterungen dazu.  
 */

#ifndef __o_stream_include__
#define __o_stream_include__


/*! \brief Die Aufgaben der Klasse O_Stream entsprechen im Wesentlichen denen der 
 *  Klasse ostream der bekannten C++ IO-Streams-Bibliothek.
 * 
 *  Da die Methode Stringbuffer::put(char) der Basisklasse Stringbuffer recht
 *  unbequem ist, wenn die zusammenzustellenden Texte nicht nur aus einzelnen
 *  Zeichen, sondern auch aus Zahlen, oder selbst wieder aus Zeichenketten
 *  bestehen, werden in der Klasse O_Stream Moeglichkeiten zum Zusammenstellen
 *  verschiedener Datentypen realisiert. In Anlehnung an die bekannten
 *  Ausgabeoperatoren der C++ IO-Streams-Bibliothek wird dazu der
 *  Shift-Operator operator<< verwendet.
 * 
 *  Darueberhinaus soll es moeglich sein, fuer die Darstellung ganzer Zahlen
 *  zwischen dem Dezimal-, dem Binaer- dem Oktal- und dem Hexadezimalsystem zu
 *  waehlen. Beachtet dabei bitte die uebliche Darstellung negativer Zahlen: Im
 *  Dezimalsystem mit fuehrendem Minuszeichen, im Oktal- und Hexadezimalsystem
 *  ohne Minuszeichen, sondern genau so wie sie im Maschinenwort stehen.
 *  (Intel-CPUs verwenden intern das 2er-Komplement fuer negative Zahlen.  -1
 *  ist Hexadeziamal also FFFFFFFF und Oktal 37777777777.) 
 * 
 *  Die oeffentlichen Methoden/Operatoren von O_Stream liefern jeweils eine 
 *  Referenz auf ihr eigenes O_Stream Objekt zurueck. Dadurch ist es moeglich, 
 *  in einem Ausdruck mehrere der Operatoren zu verwenden, z. B. 
 *  <b>kout << "a = " << a</b>;
 * 
 *  Zur Zeit wird die Darstellung von Zeichen, Zeichenketten und ganzen Zahlen
 *  unterstuetzt. Ein weiterer << Operator erlaubt die Verwendung von
 *  Manipulatoren.
 */

#include "cpu.h"
#include <string>

using namespace std;

class O_Stream {
/* Hier muesst ihr selbst Code vervollstaendigen */         

private:
  //  O_Stream(const O_Stream &copy); // Verhindere Kopieren
    
    // Fuer vorzeichenunbehaftete Variablen
    void decimal(unsigned long ival);
    void dec2bin(unsigned long ival);
    void dec2oct(unsigned long ival);
    void dec2hex(unsigned long ival);
    
    // Fuer vorzeichenbehaftete Variablen
    void decimal(long ival);
    void dec2bin(long ival);
    void dec2oct(long ival);
    void dec2hex(long ival);

   // string *buf;
   // int *bufpos;
   string *buf;
   int bufpos;

public:
	// public methods
	// Konstruktor
	O_Stream();
	// Destruktor
	~O_Stream();
	// Leert den Puffer
//	void flush();
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

	// public attributes
	// Basis des zur Anzeige verwendeten Zahlensystems (z.B. 2, 8, 10, 16)
	int base;
/* Hier muesst ihr selbst Code vervollstaendigen */     
};

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

