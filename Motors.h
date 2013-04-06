/***************************************
 * Arduino motor controller code
 * UMKC Robot Team 2013
 * Sarah Withee
 * Created: February 16, 2013
 * Modified: April 6, 2013
 ***************************************/

// Arduino stuff
#ifndef Motors_h
#define Motors_h
// include types & constants of Wiring core API
#include "WProgram.h"

class Motors { 
private:
	// Keep some vars to help keep track of some stuff
	boolean lDir, rDir;   // default forward;
	int lSpeed, rSpeed;
public:
	// Setup pin outs and stuff
	Motors() {
		// Speed controls
		pinMode(motor1PWM, OUTPUT);
		pinMode(motor2PWM, OUTPUT);
		pinMode(motor3PWM, OUTPUT);
		pinMode(motor4PWM, OUTPUT);
		// Direction control
		pinMode(motor1Dir, OUTPUT);
		pinMode(motor2Dir, OUTPUT);
		pinMode(motor3Dir, OUTPUT);
		pinMode(motor4Dir, OUTPUT);
		// Current goes up/down (?) if resistance to motor goes up
		//pinMode(motor1Cur, INPUT);
		//pinMode(motor2Cur, INPUT);
		
		lDir = true;
		rDir = true;
		lSpeed = 0;
		rSpeed = 0;
	
	}

        void setLMotorSpeed(int speed) {
		// Left motor is connected to controller motor 2
		if(speed > 255) speed = 255;
		if(speed < -255) speed = -255;
		if(speed >= 0) {
			digitalWrite(motor2Dir, HIGH);
			//direction = true;
			lDir = true;
		}
		else {
			digitalWrite(motor2Dir, LOW);
			//direction = false;
			lDir = false;
		}
		lSpeed = abs(speed);
		analogWrite(motor2PWM, lSpeed);
        }
        
        void setRMotorSpeed(int speed) {
		// Right motor is connected to controller motor 1
			if(speed >= 0) {
				digitalWrite(motor1Dir, HIGH);
				//direction = true;
				rDir = true;
			}
			else {
				digitalWrite(motor1Dir, LOW);
				//direction = false;
				rDir = false;
			}
			rSpeed = abs(speed);
			analogWrite(motor1PWM, rSpeed);
        }

        void armStartDown(int speed = 255) {
			// Set to motor 3
			digitalWrite(motor3Dir, LOW);
			analogWrite(motor3PWM, speed);
        }
        void armStartUp(int speed = 255) {
			// Set to motor 3
			digitalWrite(motor3Dir, HIGH);
			analogWrite(motor3PWM, speed);
        }
        void armStop() {
			digitalWrite(motor3Dir, HIGH);
			analogWrite(motor3PWM, 0);
        }
        void magnet(boolean setOn) {
		// Set to motor 4
		digitalWrite(motor4Dir, HIGH);
		if(setOn)
			analogWrite(motor4PWM, 255);
		else
			analogWrite(motor4PWM, 0);
        }

        boolean getLMotorDir() {
          return lDir;
        }
        boolean getRMotorDir() {
          return rDir;
        }
};

#endif
