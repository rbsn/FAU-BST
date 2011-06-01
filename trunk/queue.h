#ifndef __queue_include__
#define __queue_include__

#include "chain.h"

/* Die Klasse Queue realisiert eine einfach verkettete Liste von 
 * (sinnvollerweise spezialisierten) Chain Objekten.
 *  
 *  Die Implementierung ist etwas trickreich (siehe Vorlesung). tail verweist
 *  naemlich nicht, wie oft ueblich, auf das letzte Element der Liste, sondern 
 *  auf den next Zeiger des letzten Elements, bzw., solange die Liste noch leer
 *  ist, auf den head Zeiger der Liste. Dadurch muss beim Einfuegen eines 
 *  Elements an die Liste nicht ueberprueft werden, ob bereits Elemente in ihr 
 *  enthalten sind. Beim Entfernen von Elementen kann auf die Fallunterscheidung
 *  allerdings nicht verzichtet werden.
 */
class Queue {

private:
    Queue(const Queue &copy); // Verhindere Kopieren
	volatile int counter;

protected:
    Chain* head;
    Chain** tail;

public:
    // Der Konstruktor initialisiert die Liste als leere Liste
    Queue () { head = 0; tail = &head; counter=0; }

    // Das Listenelement item wird an das Ende der Liste angefuegt.
    void enqueue (Chain* item);
    
	// Liefert das erste Element der Liste und entfernt es gleichzeitig
    Chain* dequeue ();
    
	// Mit dieser Methode kann das angegebene Element item  aus der Liste entfernt werden, 
	// unabhaengig von seiner Position dort.
    bool remove (Chain* item);

	// Gibt an, ob die Liste leer ist
	bool isEmpty();
};

#endif
