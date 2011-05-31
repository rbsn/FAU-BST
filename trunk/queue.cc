// $Date: 2009-09-22 15:20:27 +0200 (Tue, 22 Sep 2009) $, $Revision: 2221 $, $Author: benjamin $
// kate: encoding ISO-8859-15;
// vim: set fileencoding=latin-9:
// -*- mode: c; coding: latin-9 -*-

#include "queue.h"


// ENQUEUE: Das angegebene Element wird an das Ende der Liste angefuegt.
void Queue::enqueue (Chain* item) { 
    item->next = 0;       // Das neue Element besitzt noch keinen Nachfolger.
    *tail = item;         // Das Element an das Ende der Liste anfuegen
    tail = &(item->next); // und den tail Zeiger aktualisieren.
}

// Ueberprueft, ob die Queue leer ist
// -> Zum Ueberpruefen, ob relay noch einmal ausgefuehrt werden muss
bool Queue::isEmpty() {
	if(head == 0) return true;
	else return false;
}

// DEQUEUE: Liefert das erste Element der Liste und entfernt es gleichzeitig
//          aus dieser. Wenn die Liste gar kein Element enthaelt, wird der
//          Null-Zeiger zurueckgeliefert.
Chain* Queue::dequeue () {
    Chain* item;
    item = head;                // Der head Zeiger bezeichnet das erste Element.
    if (item) {					// oder Null, wenn die Liste leer ist.
            head = item->next;  // Das erste Element aus der Liste ausklinken.
        if (!head)              // Wenn die Liste nun leer ist, muss der tail
            tail = &head;       // Zeiger wieder auf den head verweisen.
        else                    // sonst nur noch
            item->next = 0;     // den Eintrag ueber den Nachfolger loeschen.
    }
    return item;
}

// REMOVE: Sucht das angegebene Element in der Liste und entfernt es.
bool Queue::remove (Chain* item) {
    Chain* cur;
    if (head) {
        cur = head;            // Die Suche beginnt am Kopf der Liste.
        if (item == cur) {     // Wenn das erste Element bereits das gesuchte
            dequeue();         // ist, genuegt dequeue zum Entfernen.
            return true;
        }else {
            while (cur->next && item != cur->next) { // Suchen, bis das Ende der
                cur = cur->next;                     // Liste erreicht oder das
            }                                        // naechste Element das
                                                     // gesuchte ist.
            if (cur->next) {
                cur->next = item->next;   // Das Element aus der Liste ausklinken.
                item->next = 0;      // Den Eintrag ueber den Nachfolger loeschen.

                if (!cur->next)           // Wenn cur jetzt keinen Nachfolger hat,
                    tail = &(cur->next);    // muss tail aktualisiert werden.
				return true;
            }
        }
        return false;
    } else {
        return false;
    }
}
