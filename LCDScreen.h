/***************************************
 * Arduino LCD screen functions
 * UMKC Robot Team 2013
 * Sarah Withee
 * Started: February 16, 2013
 * Updated: April 5, 2013
 ***************************************/

// Arduino stuff
#ifndef LCDScreen_h
#define LCDScreen_h
// include types & constants of Wiring core API
// WProgram.h for Arduino < 1.0, Arduino.h for Arduino >= 1.0
#include "WProgram.h"

class LCDScreen{
private:
	String line1, line2, line3, line4;

public:
	void init() {
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

        void on(boolean val) {
            if(val)
          //    Serial1.write(22);   // Cursor off, blink off
          //    Serial1.write(23);   // Cursor off, blink on
          //    Serial1.write(24);   // Cursor on, blink off
              Serial1.write(25);   // Cursor on, blink on
            else
              Serial1.write(21);
      }


	void print(String msg, int line=0) {
            switch(line) {
              case 0:
              case 1: Serial1.write(128); break;
              case 2: Serial1.write(148); break;
              //case 3: Serial1.write(168); break;
              //case 4: Serial1.write(188); break;
            }
            Serial1.print(msg);
	}
};
#endif
