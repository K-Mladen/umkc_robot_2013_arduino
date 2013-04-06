/***************************************
 * Arduino Sharp IR sensor code
 * UMKC Robot Team 2013
 * Sarah Withee
 * Started: February 16, 2013
 * Updated: March 27, 2013
 ***************************************/
// Arduino stuff
#ifndef IRSensors_h
#define IRSensors_h
// include types & constants of Wiring core API
// WProgram.h for Arduino < 1.0, Arduino.h for Arduino >= 1.0
#include "WProgram.h"


class IRSensor {
private:
	int thePin;
public:
	/*
	long IR1Dist[5];
	IRSensor() {
	IR1Dist = {0.0, 0.0, 0.0, 0.0, 0.0};
	}}
	*/
	void init(int pin) {
		thePin = pin;		
	}  
	long getDistanceCM() {
		//lcd.print("IRSensor:       getIRDistanceCM", 1);
		// Distance (cm) = 2076/(SensorValue - 11)
		long val = analogRead(thePin);
		
		return 2076/(val-11);
	}
	
	long getDistanceIn() {
		//lcd.print("IRSensor:       getIRDistanceIn", 1);
		// Distance (inches) = 2076/(SensorValue - 11)/2.54 (cm per in)
		long val = analogRead(thePin);
		
		return 2076/(val-11)/2.54;
	}  

	long getDistanceRaw() {
		//lcd.print("IRSensor:       getIRDistanceIn", 1);
		// Distance (inches) = 2076/(SensorValue - 11)/2.54 (cm per in)
		long val = analogRead(thePin);
		
		return val;
	}  
};
#endif
