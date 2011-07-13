#ifndef __GOTOXY_H_
#define __GOTOXY_H_


//INCLUDES

class gotoxy {

public:
	// Standard-Konstruktor
	gotoxy(int x, int y) {
		this->x = x;
		this->y = y;
	}
	// Destruktor
	~gotoxy() {}
	
	int x;
	int y;
private:
	
};

#endif
