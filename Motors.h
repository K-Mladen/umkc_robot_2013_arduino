/***************************************
 * Arduino motor controller code
 * UMKC Robot Team 2013
 * Sarah Withee
 * Started: February 16, 2013
 * Updated: March 27, 2013
 ***************************************/

// Arduino stuff
#ifndef Motors_h
#define Motors_h
// include types & constants of Wiring core API
// WProgram.h for Arduino < 1.0, Arduino.h for Arduino >= 1.0
//#include "WProgram.h"

boolean dir;

class Motors { 
private:
	byte motor1Dir;
	byte motor2Dir;
	byte motor1PWM;
	byte motor2PWM;
	byte motor1Cur;
	byte motor2Cur;
// Keep some vars to help keep track of some stuff
	// Now a part of 
	//boolean dir;   // default forward;

public:
	// Setup pin outs and stuff
	Motors() {
		dir = true;
		motor1Dir = 23;
		motor2Dir = 24;
		motor1PWM = 4;
		motor2PWM = 5;
		motor1Cur = 0;
		motor2Cur = 1;

		// Speed controls
		pinMode(motor1PWM, OUTPUT);
		pinMode(motor2PWM, OUTPUT);
		// Direction controls
		pinMode(motor1Dir, OUTPUT);
		pinMode(motor2Dir, OUTPUT);
		// Current goes up/down (?) if resistance to motor goes up
		pinMode(motor1Cur, INPUT);
		pinMode(motor2Cur, INPUT);
	}


	void forward(int spd = 255) {
		dir = true;

		//sendMsg("This is forward()! We're moving--watch out!");
		//out_msg.data = "this is forward()! we're moving -- watch out.";
		//talker.publish( &out_msg );
		digitalWrite(motor1Dir, HIGH);
		digitalWrite(motor2Dir, LOW);
		analogWrite(motor1PWM, spd);
		analogWrite(motor2PWM, spd);
	}

	void backward(int spd = 255) {
		dir = false;

		digitalWrite(motor1Dir, LOW);
		digitalWrite(motor2Dir, HIGH);
		analogWrite(motor1PWM, spd);
		analogWrite(motor2PWM, spd);
	}

	void rotateLeft(int spd = 255) {
		// Rotates in place to the left
		
	}
	
	void rotateRight(int spd = 255) {
		// Rotates in place to the right
	}
	
	void turnLeft(int spd = 255, int direction = 180) {
		// Turns forward and left
		
	}
	
	void turnRight(int spd = 255, int direction = 180) {
		// Turns forward and right
		
	}

	void stop() {
		analogWrite(motor1PWM, 0);
		analogWrite(motor2PWM, 0);
	}

	void forceStop() {
		// Stop, but if you swap DIR pin, you forceibly stop the motors
		if(dir) {
			// Going forward, set to opposite direction
			digitalWrite(motor1Dir, LOW);
			digitalWrite(motor2Dir, HIGH);
			analogWrite(motor1PWM, 0);
			analogWrite(motor2PWM, 0);
		} else {
			// Going backward, set to opposite direction
			digitalWrite(motor1Dir, HIGH);
			digitalWrite(motor2Dir, LOW);
			analogWrite(motor1PWM, 0);
			analogWrite(motor2PWM, 0);
		}          
	}
};

#endif
