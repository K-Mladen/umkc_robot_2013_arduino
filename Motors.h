/***************************************
 * Arduino motor controller code
 * UMKC Robot Team 2013
 * Sarah Withee
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
		// Direction control
		pinMode(motor1Dir, OUTPUT);
		pinMode(motor2Dir, OUTPUT);
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

        boolean getLMotorDir() {
          return lDir;
        }
        boolean getRMotorDir() {
          return rDir;
        }

/*
        Old functions:
        They work, but no longer used
*********        
        
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
        */
};

#endif
