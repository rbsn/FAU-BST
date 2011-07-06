#include "o_stream.h"

// Konstruktor
O_Stream::O_Stream() {
	base = 10;				// Default: Dezimalbasis
	buf = new string("");

//	string s1 = "\033[5;33;40m";
//	write(STDOUT_FILENO, s1.c_str(), s1.length());
}

// Destruktor
O_Stream::~O_Stream() {
	delete buf;
}


O_Stream& O_Stream::operator<< (char c) {
	
	if(c == '\n') {
		if ( write(STDOUT_FILENO, buf->c_str(), buf->length()) == -1 ) {
			perror("[O_Stream] Error @ write");
		}

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
	return operator<<(s.c_str());
}

O_Stream& O_Stream::operator<< (short ival) {
	return operator<<((long) ival);
}

O_Stream& O_Stream::operator<< (unsigned short ival) {
	return operator<<((unsigned long) ival);;
}

O_Stream& O_Stream::operator<< (int ival) {
	return operator<<((long) ival);
}

O_Stream& O_Stream::operator<< (unsigned int ival) {
	return operator<<((unsigned long) ival);
}

O_Stream& O_Stream::operator<< (long ival) {
	
	if(ival == 0) {
		return operator<<('0');
	}

	if(ival < 0) {
		operator<<('-');
		ival = -ival;
	}
	
	char tmp[SIZE_ARRAY];	

	int i = 0;
	int modulo;

	for(i = 0; ival != 0; ival /= base) {
		modulo = ival % base;
		if(modulo < 10) {
			tmp[++i] = '0' + modulo;
		} else {
			tmp[++i] = 'A' + (modulo - 10);
		}
	}

	while( i > 0 ) {
		operator<<(tmp[i--]);
	}

	return *this;
}

O_Stream& O_Stream::operator<< (unsigned long ival) {
	
	if(ival == 0) {
		return operator<<('0');
	}
	
	char tmp[SIZE_ARRAY];

	int i = 0;
	int modulo;
	
	for(i = 0; ival != 0; ival /= base) {
		modulo = ival % base;
		if(modulo < 10) {
			tmp[++i] = '0' + modulo;
		} else {
			tmp[++i] = 'A' + (modulo - 10);
		}
	}

	while( i > 0 ) { 
		operator<<(tmp[i--]);
	}

	return *this;
}

// Darstellung eines Zeigers als hexadezimale ganze Zahl
O_Stream& O_Stream::operator<< (void *ptr) {

	int tmpbase = base;
	base = 16;
	operator<< ( (long) ptr);
	base = tmpbase;

	return *this;
}

// Aufruf einer Manipulatorfunktion
O_Stream & O_Stream::operator<< ( O_Stream &(*f)(O_Stream &) ) {
	return (*f) (*this);
}

O_Stream & O_Stream::operator<< ( gotoxy g) {
	return *this<< "\033[" << g.x << ";" << g.y << "H";
}

// Go To X and Y
/*
O_Stream & gotoxy(int x, int y, O_Stream &os) {
	string s1 = "\033[";
	s1 += x;
	s1 += ";";
	s1 += y;
	s1 += "H";
	os<<(s1.c_str());
	return os;
}
*/
// Fuegt einen Zeilenumbruch in die Ausgabe ein
O_Stream & endl (O_Stream &os) {
	os << '\n';			return os;
}

// Waehlt das binaere Zahlensystem aus
O_Stream & bin (O_Stream &os) {
	os.base = 2;		return os;
}

 // Waehlt das oktale Zahlensystem aus
O_Stream & oct (O_Stream &os) {
	os.base = 8;		return os;
}

// Waehlt das dezimale Zahlensystem aus
O_Stream & dec (O_Stream &os) {
	os.base = 10;		return os;
}

// Waehlt das Hexadezimale Zahlensystem aus
O_Stream & hex (O_Stream &os) {
	os.base = 16;		return os;
}
