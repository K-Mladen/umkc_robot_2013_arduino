/***************************************
 * Main Arduino robot functions
 * UMKC Robot Team 2013
 * Sarah Withee, Eric Gonzalez
 * Created: February 16, 2013
 * Modified: April 5, 2013
 ***************************************/

/***************************************
 * Pin outs
 ***************************************/
// Digital pins
const byte motor1Dir = 	22;
const byte motor2Dir = 	23;
const byte motor3Dir = 	24;
const byte motor4Dir = 	25;
//const byte LCDOut = 	18;

// PWM pins
const byte motor1PWM = 	4;
const byte motor2PWM = 	5;
const byte motor3PWM = 	6;
const byte motor4PWM = 	7;

// Analog pins
// removed as they're not connected


/***************************************
 * includes
 ***************************************/
#include <Servo.h>
#include <ros.h>
#include <std_msgs/Int16.h>
#include "LCDScreen.h"
#include "Motors.h"
//#include "IRSensors.h"


/***************************************
 * ROS variables
 ***************************************/
ros::NodeHandle nh;

// Listen to motherboard
void lmotor_catch(const std_msgs::Int16& message);    
void rmotor_catch(const std_msgs::Int16& message);    
ros::Subscriber<std_msgs::Int16> listenLMotor("lmotor_cmd", &lmotor_catch);
ros::Subscriber<std_msgs::Int16> listenRMotor("rmotor_cmd", &rmotor_catch);

// Talk to motherboard
std_msgs::Int16 lEnc;
std_msgs::Int16 rEnc;
ros::Publisher pubLWheel("lwheel", &lEnc);
ros::Publisher pubRWheel("rwheel", &rEnc);

/***************************************
 * Other variables
 ***************************************/
// Objects
static Motors motors;
LCDScreen lcd;
Servo shoulder;
Servo elbow;
// Variables
int lmotor_speed = 0;
int rmotor_speed = 0;
boolean updatedSpeed = false;
boolean updatedEncoder = false;
boolean direction = true;
int encoder1;
int encoder2;
int encoder3;
int encoder4;
int currentTime;
int oldTime;


/***************************************
 * ROS Motor message catching
 ***************************************/
void lmotor_catch(const std_msgs::Int16& message) {    
	// Caught motor speed message, save and set to future update
	lmotor_speed = message.data;
	updatedSpeed = true;
}  
void rmotor_catch(const std_msgs::Int16& message) {    
	// Caught motor speed message, save and set to future update
	rmotor_speed = message.data;
	updatedSpeed = true;
}

/***************************************
 * Arduino set
 ***************************************/
void setup() {
	shoulder.attach(8);
	elbow.attach(9);
	delay(50);
	shoulder.write(170);
	elbow.write(50);

	encoder1 = 0;
	encoder2 = 0;
	encoder3 = 0;
	encoder4 = 0;
	
//	attachInterrupt(0, enc1Interrupt, RISING);
	attachInterrupt(1, enc2Interrupt, RISING);
	attachInterrupt(2, enc3Interrupt, RISING);
//	attachInterrupt(3, enc4Interrupt, RISING);
	// Start at 0, in case any of the interrupts increase it immediately
	encoder1 = 0;
	encoder2 = 0;
	encoder3 = 0;
	encoder4 = 0;
	
	nh.initNode();
	nh.subscribe(listenLMotor);
	nh.subscribe(listenRMotor);
	nh.advertise(pubRWheel);
	nh.advertise(pubLWheel);
	
	oldTime = millis();
	// Has to stay at 19200 for screen to function correctly
	Serial1.begin(19200);   // LCD
	lcd.init();
	lcd.clear();
	lcd.backlight(true);
	lcd.on(true);
}

/***************************************
 * Arduino loop
 ***************************************/
void loop() {
	//shoulder.write(180);	

	// Check with ROS to find any new messages
	nh.spinOnce();
	
	if(updatedSpeed) {
		motors.setLMotorSpeed(lmotor_speed);
		motors.setRMotorSpeed(rmotor_speed);
		updatedSpeed = false;
	}
	
	currentTime = millis();
	if(currentTime - oldTime > 50) {
	//if(updatedEncoder) {
		lEnc.data = encoder2;
		rEnc.data = encoder3;
		pubLWheel.publish( &lEnc );
		pubRWheel.publish( &rEnc );
		updatedEncoder = false;
		oldTime = millis();
	}
	
	String msg;
	msg = "Encoder L: ";
	msg += lEnc.data;
	lcd.print(msg, 1);
	msg = "Encoder R: ";
	msg += rEnc.data;
	lcd.print(msg, 2);
	
       
}

void enc1Interrupt() {
	if(motors.getLMotorDir())
		encoder1++;
	else
		encoder1--;
}

void enc2Interrupt() {
	if(motors.getLMotorDir())
		encoder2++;
	else
		encoder2--;
}

void enc3Interrupt() {
	if(motors.getRMotorDir())
		encoder3++;
	else
		encoder3--;
}

void enc4Interrupt() {
	if(motors.getLMotorDir())
		encoder4++;
	else
		encoder4--;
}

