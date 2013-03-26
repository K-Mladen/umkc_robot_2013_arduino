/***************************************
 * Main Arduino robot functions
 * UMKC Robot Team 2013
 * Sarah Withee, Eric Gonzales
 * February 16, 2013
 ***************************************/

/***************************************
 * Pin outs
 ***************************************/
// Digital pins
const byte motor1Dir = 	2;
const byte motor2Dir = 	4;
const byte LCDOut = 	18;

// PWM pins
const byte motor1PWM = 	3;
const byte motor2PWM = 	5;

// Analog pins
const byte motor1Cur = 	0;	// A0
const byte motor2Cur = 	1;	// A1
const byte pinIR1 = 	2;		// A2


/***************************************
 * includes
 ***************************************/
#include <ros.h>
#include <capstone/Wall.h>
#include <std_msgs/String.h>
#include "LCDScreen.h"
#include "Motors.h"
#include "IRSensors.h"
void message_catch(const capstone::Wall& message);


/***************************************
 * ROS variables
 ***************************************/
ros::NodeHandle nh;
char* passoff;
enum fields { direction, angle, speed };
// Listen to motherboard
ros::Subscriber<capstone::Wall> listen("arduino_motors_write", &message_catch);
std_msgs::String out_msg;
// Talk to motherboard
ros::Publisher talker("arduino_motors_read", &out_msg);

/***************************************
 * Other variables
 ***************************************/
Motors motors;


void message_catch(const capstone::Wall& message) {    
	//caught a message. save it some where and then pass it back.
	passoff = message.data;
	// this isn't right. might need to use strings
	//  if ((sizeof(passoff) / sizeof(char)) != message.size) {
	//    strcpy(passoff, "CAP --> Error in message :: message not expected size.\n");
	//  }
}  


/***************************************
 * Arduino set
 ***************************************/
void setup() {

	// Keep some vars to help keep track of some stuff
	boolean dir;   // default forward;
	unsigned int spd;  // default no speed; 

	dir = true;
	spd = 0;  

	// Speed controls
	pinMode(motor1PWM, OUTPUT);
	pinMode(motor2PWM, OUTPUT);
	// Direction controls
	pinMode(motor1Dir, OUTPUT);
	pinMode(motor2Dir, OUTPUT);
	// Current goes up/down (?) if resistance to motor goes up
	pinMode(motor1Cur, INPUT);
	pinMode(motor2Cur, INPUT);

	nh.initNode();
	nh.subscribe(listen);
	nh.advertise(talker);
}

/***************************************
 * Arduino loop
 ***************************************/
void loop() {
	nh.spinOnce();
	// after spinOnce, the message has been received and copied.
	//   can now parse and create a string message to print.

	char build_msg[256];
	strcpy(build_msg, "CAP --> UI :: ");  
	switch (passoff[direction]) {
		case 'f': {
			strcat(build_msg, "forward, ");
			motors.forward();
			break;
		}
		case 'l': {
			strcat(build_msg, "pivot left, ");
			// insert left funciton here
			break;
		}  
		case 'b': {
			strcat(build_msg, "backward, ");
			motors.backward();
			break;
		}
		case 'r': {
			strcat(build_msg, "pivot right, ");
			// insert right funciton ehre
			break;
		}  
		case 'q': {
			strcat(build_msg, "guide left, ");
			break;
		}
		case 'e': {
			strcat(build_msg, "guide right, ");
			break;
		}
		case 'x': {
			strcat(build_msg, "all stop");
			motors.stop();
			break;
		}
		default: {
			strcat(build_msg, "no input");
			break;
		}
	}
	out_msg.data = build_msg;
	talker.publish( &out_msg );
	passoff = NULL;
	delay(100);
}
