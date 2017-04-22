/*
 Name:		RubiksCube.ino
 Created:	3/17/2017 10:25:05 AM
 Author:	fsr19
*/




#include <Stepper.h>
#include <Servo.h>
#include <Adafruit_MCP23017.h>
#include "MCPStepper.h"
//#include "Cube.h"

#define NUMBER_OF_STEPS 200

#define stepperSpeed 10

#define stepperFPin1 0
#define stepperFPin2 1
#define stepperFPin3 2
#define stepperFPin4 3

#define stepperLPin1 4
#define stepperLPin2 5
#define stepperLPin3 6
#define stepperLPin4 7

#define stepperBPin1 8
#define stepperBPin2 9
#define stepperBPin3 10
#define stepperBPin4 11

#define stepperRPin1 12
#define stepperRPin2 13
#define stepperRPin3 14
#define stepperRPin4 15

Adafruit_MCP23017 mcp;
MCPStepper stepperF(NUMBER_OF_STEPS, stepperFPin1, stepperFPin2, stepperFPin3, stepperFPin4), stepperL(NUMBER_OF_STEPS, stepperLPin1, stepperLPin2, stepperLPin3, stepperLPin4),
		   stepperB(NUMBER_OF_STEPS, stepperBPin1, stepperBPin2, stepperBPin3, stepperBPin4), stepperR(NUMBER_OF_STEPS, stepperRPin1, stepperRPin2, stepperRPin3, stepperRPin4);
Servo servoFB, servoRL;

//Cube cube;

// the setup function runs once when you press reset or power the board
void setup() {
	mcp.begin();
	TWBR = 12; //Increase speed of the clock on the chip
	stepperF.setMCP(mcp); stepperL.setMCP(mcp); stepperB.setMCP(mcp); stepperR.setMCP(mcp);
	stepperF.setSpeed(stepperSpeed); stepperL.setSpeed(stepperSpeed); stepperB.setSpeed(stepperSpeed); stepperR.setSpeed(stepperSpeed);

	//cube = Cube(&stepperF, &stepperL, &stepperB, &stepperR);
}

// the loop function runs over and over again until power down or reset
void loop() {
	
}
