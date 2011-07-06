#ifndef __COLOUR_H_
#define __COLOUR_H_

//INCLUDES

class color {

public:
	// possible foreground colors
	enum FG_COLOR {
		FG_BLACK 	= 30,		// Black
		FG_RED		= 31,		// Red
		FG_GREEN	= 32,		// Green
		FG_YELLOW	= 33,		// Yellow
		FG_BLUE		= 34,		// Blue
		FG_MAGENTA	= 35,		// Magenta
		FG_CYAN		= 36,		// Cyan
		FG_WHITE	= 37		// White
	};

	// possible background colors
	enum BG_COLOR {
		BG_BLACK 	= 40,		// Black
		BG_RED		= 41,		// Red
		BG_GREEN	= 42,		// Green
		BG_YELLOW	= 43,		// Yellow
		BG_BLUE		= 44,		// Blue
		BG_MAGENTA	= 45,		// Magenta
		BG_CYAN		= 46,		// Cyan
		BG_WHITE	= 47		// White
	};

	// possible attributs
	enum ATTR {
		OFF 		= 0,		// All attributes off
		BOLD		= 1,		// Bold on 
		UNDERSCORE	= 4,		// Underscore (on monochrome display adapter only) 
		BLINK		= 5,		// Blink on
		REVERSE		= 7,		// Reverse video on
		CONCEALED	= 8			// Concealed on
	};

	// constructor
	color(int fgc, int bgc, int attr = 0) {
		// save the foreground color ffg
		foreground = fgc;
		// save the background color bgc
		background = bgc;
		// set cursor (not) blinking
		attribute = attr;
	}

	// destructor
	~color() {	}

	// foreground color
	int foreground;
	// background color
	int background;
	// (not) blinking cursor
	bool attribute;

private:

};

#endif	// __COLOUR_H_
