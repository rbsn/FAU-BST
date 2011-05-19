// $Date: 2009-08-11 16:57:46 +0200 (Tue, 11 Aug 2009) $, $Revision: 2208 $, $Author: benjamin $
// kate: encoding ISO-8859-15;
// vim: set fileencoding=latin-9:
// -*- mode: c; coding: latin-9 -*- 

#include "o_stream.h"
#include <iostream>
#include <errno.h>
#include <stdio.h>

O_Stream::O_Stream() {
	base = 10;	// Default-Wert, Dezimalbasis
//	buf = new string[CPU::getNumOfBootedCPUs()];
//	bufpos = new int[CPU::getNumOfBootedCPUs()];
	buf = new string("");
	bufpos = 0;
}

O_Stream::~O_Stream() {

}

O_Stream& O_Stream::operator<< (char c) {
	
	if(c == '\n') {
		write(STDOUT_FILENO, buf->c_str(), buf->length());
		buf->clear();
	}

	*buf += c;
	
	return *this;
}

O_Stream& O_Stream::operator<< (unsigned char c) {
	return operator<<((char) c);
}

O_Stream& O_Stream::operator<< (const char *string) {
	for(int i = 0; string[i] != '\0'; i++) {
		operator<<(string[i]);
	}
	return *this;
}

O_Stream& O_Stream::operator<< (std::string &s) {
	return operator<<(s.c_str());    //TODO Fuer Zahlenkonvertierung auch!!!!
}

O_Stream& O_Stream::operator<< (short ival) {
	if(base == 10) {
		// Dezimalsystem: Bei negativen Werten fuehrendes Minus-Zeichen	
		if(ival < 0) {
			//put('-');
			ival = -ival;
		}

		decimal( (long) ival);
	} else if (base == 2) {
		dec2bin( (long) ival);
	} else if (base == 8) {
		dec2oct( (long) ival);
	} else if (base == 16) {
		dec2hex( (long) ival);
	}
	return *this;
}

O_Stream& O_Stream::operator<< (unsigned short ival) {
	if (base == 10) {
		decimal( (unsigned long) ival);
	} else if (base == 2) { 
		dec2bin( (unsigned long) ival);
	} else if (base == 8) {
		dec2oct( (unsigned long) ival);
	} else if (base == 16) {
		dec2hex( (unsigned long) ival);
	}
	return *this;
}

O_Stream& O_Stream::operator<< (int ival) {
	if(base == 10) {
		// Dezimalsystem: Bei negativen Werten fuehrendes Minus-Zeichen	
		if(ival < 0) {
			//put('-');
			ival = -ival;
		}

		decimal( (long) ival);
	} else if (base == 2) { 
		dec2bin( (long) ival);
	} else if (base == 8) {
		dec2oct( (long) ival);
	} else if (base == 16) {
		dec2hex( (long) ival);
	}
	return *this;
}

O_Stream& O_Stream::operator<< (unsigned int ival) {
	if (base == 10) {
		decimal( (unsigned long) ival);
	} else if (base == 2) { 
		dec2bin( (unsigned long) ival);
	} else if (base == 8) {
		dec2oct( (unsigned long) ival);
	} else if (base == 16) {
		dec2hex( (unsigned long) ival);
	}
	return *this;
}

O_Stream& O_Stream::operator<< (long ival) {
	if(base == 10) {
		// Dezimalsystem: Bei negativen Werten fuehrendes Minus-Zeichen	
		if(ival < 0) {
			//put('-');
			ival = -ival;
		}
	
		decimal( (long) ival);
	} else if (base == 2) { 
		dec2bin( (long) ival);
	} else if (base == 8) {
		dec2oct( (long) ival);
	} else if (base == 16) {
		dec2hex( (long) ival);
	}
	return *this;
}

O_Stream& O_Stream::operator<< (unsigned long ival) {
	if (base == 10) {
		decimal( (unsigned long) ival);
	} else if (base == 2) { 
		dec2bin( (unsigned long) ival);
	} else if (base == 8) {
		dec2oct( (unsigned long) ival);
	} else if (base == 16) {
		dec2hex( (unsigned long) ival);
	}
	return *this;
}

O_Stream& O_Stream::operator<< (void *ptr) {

	int tmpbase = base;
	base = 16;
	operator<< ( (long) ptr); //Pointer zu long casten, dann in HEX umwandeln und ausgeben
	base = tmpbase;

	return *this;
}

O_Stream & O_Stream::operator<< ( O_Stream &(*f)(O_Stream &) ) {
	return (*f) (*this);
}

O_Stream& endl (O_Stream &os) {
	os << '\n';
	//os.flush();
	return os;
}

O_Stream & bin (O_Stream &os) {
	os.base = 2;	
	return os;
}

O_Stream & oct (O_Stream &os) {
	os.base = 8;
	return os;
}

O_Stream & dec (O_Stream &os) {
	os.base = 10;
	return os;
}

O_Stream & hex (O_Stream &os) {
	os.base = 16;
	return os;
}

void O_Stream::decimal(unsigned long ival) {
	if(ival == 0) { 
		//put('0' + ival);
	} else {
		char string[10]; // Maximal 10 Zeichen wegen 16 Bit bei Long

		// Char-Wert fuer entsprechenden Long-Wert berechnen
		int i = 0;
		while(ival != 0) {
			string[i++] = '0' + (ival % 10);
			ival /= 10;
		}
		// Ausgabe in den Puffer
		while(i > 0); //put(string[--i]);
	}
}

void O_Stream::dec2bin(unsigned long ival) {
	char result[32];			// Ergebnisfeld
	int i = 0; int k = 0;			// Laufvariablen
	for(k = 0; k < 32; k++) result[k] = '0';// Default: alle Bits auf '0'

	while(ival != 0) {
		result[i++] = '0' + ival % 2;
		ival /= 2;
	}
	// Neuen Wert von k bestimmen, um Arbeit zu sparen
	if( k/2 >= i ) k = 16;
	if( k/2 >= i ) k = 8;

	// Ausgabe in den Puffer
	while(k > 0); //put(result[--k]);
}	

void O_Stream::dec2oct(unsigned long ival) {
	char result[12];			// Ergebnisfeld
	int i = 0; int k = 0;			// Laufvariablen
	for(k = 0; k < 12; k++) result[k] = '0';// Default: alle Bits auf '0'

	while (ival != 0) {
		result[i++] = '0' + ival % 8;
		ival = ival / 8;
	}
	// Neuen Wert von k bestimmen, um Arbeit zu sparen
	if( k/2 >= i ) k = 6;
	if( k/2 >= i ) k = 3;

	// Ausgabe in den Puffer
	while(k > 0); //put(result[--k]);
}

void O_Stream::dec2hex(unsigned long ival) {
	char result[8];				// Ergebnisfeld
	int i = 0; int k = 0;			// Laufvariablen
	for(k = 0; k < 8; k++) result[k] = '0';	// Default: alle Bits auf '0'

	int modulo = 0;
	
	while (ival != 0) {
		modulo = ival % 16;
		
		if(modulo < 10) {
			result[i++] = '0' + modulo;
		} else {
			result[i++] = 'A' + (modulo - 10);
		}
		ival = ival / 16;
	}
	// Neuen Wert von k bestimmen, um Arbeit zu sparen
	if( k/2 >= i ) k = 4;
	if( k/2 >= i ) k = 2;
	
	// Ausgabe in den Puffer
	while(k > 0); //put(result[--k]);
}

void O_Stream::decimal(long ival) {
	if(ival == 0) {
		//put('0' + ival);
	} else {
		char string[10]; // Maximal 10 Zeichen wegen 16 Bit bei Long
		
		// Char-Wert fuer entsprechenden Long-Wert berechnen
		int i = 0;
		while(ival != 0) {
			string[i++] = '0' + (ival % 10);
			ival /= 10;
		}
		// Ausgabe in den Puffer
		while(i > 0); //put(string[--i]);
	}
}

void O_Stream::dec2bin(long ival) {
	char result[32];			// Ergebnisfeld
	int i = 0; int j = 1; int k = 0;	// Laufvariablen
	for(k = 0; k < 32; k++) result[k] = '0';// Default: alle Bits auf '0'

	if(ival < 0) {
		ival = -ival;
		j = 0; 	// Kennzeichen, dass die Zahl negativ ist
	}
	
	while(ival != 0) {
		result[i++] = '0' + ival % 2;
		ival /= 2;
	}

	// Neuen Wert von k bestimmen, um Arbeit zu sparen
	if( k/2 >= i ) k = 16;
	if( k/2 >= i ) k = 8;

	if(j == 0) {	// Zahl ist negativ
		// Bits invertieren
		while (j < k) {
			if(result[j] == '0') result[j++] = '1';
			else result[j++] = '0';
		}
		// Bits + 1
		j = 0;
		while(j < k) {
			if(result[j] == '1') result[j++] = '0';
			else {
				result[j++] = '1';
				break;
			}
		}
	}		
	// Ausgabe in den Puffer
	while(k > 0); //put(result[--k]);
}	

void O_Stream::dec2oct(long ival) {
	char result[12];			// Ergebnisfeld
	int i = 0; int k = 0;			// Laufvariablen
	for(k = 0; k < 12; k++) result[k] = '0';// Default: alle Bits auf '0'

	if(ival >= 0) {		// Zahl ist positiv
		while (ival != 0) {
			result[i++] = '0' + ival % 8;
			ival = ival / 8;
		}

		// Neuen Wert von k bestimmen, um Arbeit zu sparen
		if( k/2 >= i ) k = 6;
		if( k/2 >= i ) k = 3;

	} else {		// Zahl ist negativ
		ival = -ival;
		
		char tmp[32];				// Binaeres Ergebnisfeld
		int j = 0; int l = 0;			// Laufvariablen
		for(j = 0; j < 32; j++) tmp[j] = '0';	// Default: alle Bits auf '0'

		while(ival != 0) {
			tmp[l++] = '0' + ival % 2;
			ival /= 2;
		}

		// Neuen Wert von j und k bestimmen, um Arbeit zu sparen
		if( j/2 >= l ) { j = 16;	k = 6; }
		if( j/2 >= l ) { j = 8;		k = 3; }

		// Bits invertieren
		while (i < j) {
			if(tmp[i] == '0') tmp[i++] = '1';
			else tmp[i++] = '0';
		}
		// Bits + 1
		i = 0;
		while(i < j) {
			if(tmp[i] == '1') tmp[i++] = '0';
			else {
				tmp[i++] = '1';
				break;
			}
		}

		// Umrechnen in Oktalzahl
		int ptnz = 1;
		int octal = 0;

		i = 0; l = 0;
		while(i < k) {
			// 3 Stellen Binaer = 1 Stelle Oktal
			while(ptnz <= 4) {
				if(tmp[l++] == '0') {
					ptnz *= 2;
				} else {
					octal = octal + ptnz;
					ptnz *= 2;
				}
			}

			result[i++] = '0' + octal;

			// Zuruecksetzen von modulo und ptnz auf Ausgangswerte
			octal = 0;
			ptnz = 1;
		}
	}		
	// Ausgabe in den Puffer
	while(k > 0); //put(result[--k]);
}

void O_Stream::dec2hex(long ival) {
	char result[8];				// Ergebnisfeld
	int i = 0; int k = 0;			// Laufvariablen
	for(k = 0; k < 8; k++) result[k] = '0';	// Default: alle Bits auf '0'

	if(ival >= 0) {		// Zahl ist positiv
		int modulo = 0;
		
		while (ival != 0) {
			modulo = ival % 16;
			
			if(modulo < 10) {
				result[i++] = '0' + modulo;
			} else {
				result[i++] = 'A' + (modulo - 10);
			}

			ival = ival / 16;
		}

		// Neuen Wert von k bestimmen, um Arbeit zu sparen
		if( k/2 >= i ) k = 4;
		if( k/2 >= i ) k = 2;

	} else {		// Zahl ist negativ
		
		ival = -ival;
		
		char tmp[32];				// Binaeres Ergebnisfeld
		int j = 0; int l = 0;			// Laufvariablen
		for(j = 0; j < 32; j++) tmp[j] = '0';	// Default: alle Bits auf '0'

		while(ival != 0) {
			tmp[l++] = '0' + ival % 2;
			ival /= 2;
		}

		// Neuen Wert von j und k bestimmen, um Arbeit zu sparen
		if( j/2 >= l ) { j = 16;	k = 4; }
		if( j/2 >= l ) { j = 8;		k = 2; }

		// Bits invertieren
		while (i < j) {
			if(tmp[i] == '0') tmp[i++] = '1';
			else tmp[i++] = '0';
		}
		// Bits + 1
		i = 0;
		while(i < j) {
			if(tmp[i] == '1') tmp[i++] = '0';
			else {
				tmp[i++] = '1';
				break;
			}
		}

		// Umrechnen in Hexadezimalzahl
		int ptnz = 1;
		int modulo = 0;

		i = 0; l = 0;
		while(i < k) {
			// 4 Stellen Binaer = 1 Stelle Hexadezimal
			while(ptnz <= 8) {
				if(tmp[l++] == '0') {
					ptnz *= 2;
				} else {
					modulo = modulo + ptnz;
					ptnz *= 2;
				}
			}
			
			if(modulo < 10) {
				result[i++] = '0' + modulo;
			} else {
				result[i++] = 'A' + (modulo - 10);
			}

			// Zuruecksetzen von modulo und ptnz auf Ausgangswerte
			modulo = 0;
			ptnz = 1;
		}
	}		
	// Ausgabe in den Puffer
	while(k > 0); //put(result[--k]);
}
