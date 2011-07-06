#ifndef __chain_include__
#define __chain_include__

/*  Verkettungszeiger zum Einfuegen eines Objektes in eine einfach verkettete Liste.
 *  
 *  Die Klasse Chain stellt einen Verkettungszeiger auf ein weiteres 
 *  Chain Element zur Verfuegung und ist damit Basis aller Klassen, deren
 *  Instanzen in Listen (Queue Objekten) verwaltet werden sollen. 
 */ 
class Chain {

private:
//    Chain(const Chain &copy); // Verhindere Kopieren

public:
    Chain() {}
    
	// next gibt das naechste Chain Element der Liste an. 
    // Wenn kein naechstes Element existiert, sollte next ein Nullzeiger sein.
    Chain* next;
};

#endif

