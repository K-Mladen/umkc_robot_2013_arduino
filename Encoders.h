/***************************************
 * Encoder functions
 * UMKC Robot Team 2013
 * Sarah Withee
 * Started: March 27, 2013
 * Updated: March 27, 2013
 ***************************************/
// Arduino stuff
#ifndef Encoders_h
#define Encoders_h
  // include types & constants of Wiring core API
// WProgram.h for Arduino < 1.0, Arduino.h for Arduino >= 1.0
//#include "WProgram.h"

class Encoders {

    // Global vars
    //boolean dir;  // Forward = true
    int encoder1;
    int encoder2;
    int encoder3;
    int encoder4;
    
    //Motors motors;
    
    void enc1Interrupt() {
      if(direction)
        encoder1++;
      else
        encoder1--;
    }
    void enc2Interrupt() {
      if(direction)
        encoder2++;
      else
        encoder2--;
    }
    void enc3Interrupt() {
      if(direction)
        encoder3++;
      else
        encoder3--;
    }
    void enc4Interrupt() {
      if(direction)
        encoder4++;
      else
        encoder4--;
    }
    

}
#endif
