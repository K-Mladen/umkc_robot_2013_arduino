/***************************************
 * Arduino LCD screen functions
 * UMKC Robot Team 2013
 * Sarah Withee
 * February 16, 2013
 ***************************************/

// Arduino stuff
#ifndef LCDScreen_h
#define LCDScreen_h
// include types & constants of Wiring core API
#include "WProgram.h"

class LCDScreen{
private:
	String line1, line2, line3, line4;

public:
	LCDScreen() {
		Serial1.begin(19200);
		clear();
		line1 = line2 = line3 = line4 = "";
	}

	void clear() {
		Serial1.write(12);  // clear screen
		delay(10);
		Serial1.write(128); // Move to Row 0 Col 0
	}

	void backlight(boolean val) {
		if(val)
			Serial1.write(17);
		else
			Serial1.write(18);
	}

	void print(String msg, int line=0) {
		switch(line) {
			case 1: Serial1.write(128); break;
			case 2: Serial1.write(148); break;
			case 3: Serial1.write(168); break;
			case 4: Serial1.write(188); break;
		}
		Serial1.print(msg);
	}
};
#endif
