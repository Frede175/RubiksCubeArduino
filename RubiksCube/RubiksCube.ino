/*
 Name:		RubiksCube.ino
 Created:	3/17/2017 10:25:05 AM
 Author:	fsr19
*/




#include <Stepper.h>
#include <Servo.h>
#include <Adafruit_MCP23017.h>
#include "MCPStepper.h"
#include "Cube.h"
#include "Constants.h"


Adafruit_MCP23017 mcp;
MCPStepper stepperF(constants::NUMBER_OF_STEPS, constants::STEPPERF_PIN3, constants::STEPPERF_PIN4, constants::STEPPERF_PIN1, constants::STEPPERF_PIN2), 
		   stepperL(constants::NUMBER_OF_STEPS, constants::STEPPERL_PIN3, constants::STEPPERL_PIN4, constants::STEPPERL_PIN1, constants::STEPPERL_PIN2),
		   stepperB(constants::NUMBER_OF_STEPS, constants::STEPPERB_PIN1, constants::STEPPERB_PIN2, constants::STEPPERB_PIN3, constants::STEPPERB_PIN4), 
		   stepperR(constants::NUMBER_OF_STEPS, constants::STEPPERR_PIN1, constants::STEPPERR_PIN2, constants::STEPPERR_PIN3, constants::STEPPERR_PIN4);
Servo servoFB, servoRL, servoDoorA, servoDoorB;

Cube cube;

bool hasSerial = false;
String command;

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	mcp.begin();
	TWBR = 12; //Increase speed of the clock on the MCP chip
	stepperL.setMCP(mcp); stepperF.setMCP(mcp); stepperB.setMCP(mcp); stepperR.setMCP(mcp);
	stepperF.setSpeed(constants::STEPPER_SPEED); stepperL.setSpeed(constants::STEPPER_SPEED); stepperB.setSpeed(constants::STEPPER_SPEED); stepperR.setSpeed(constants::STEPPER_SPEED);

	servoFB.attach(constants::SERVO_FB_PIN);
	servoRL.attach(constants::SERVO_RL_PIN);
	servoDoorA.attach(constants::SERVO_DOORA_PIN);
	servoDoorB.attach(constants::SERVO_DOORB_PIN);

	cube = Cube(&stepperF, &stepperL, &stepperB, &stepperR, &servoFB, &servoRL, &servoDoorA, &servoDoorB);
}

// the loop function runs over and over again until power down or reset
void loop() {
	if (hasSerial) {
		hasSerial = false;
		if (command == "STOP") {
			while (1) {
				if (hasSerial) {
					if (command == "RESUME") break;
				}
			}
		} else if (command.charAt(0) == 'M') {
			int temp = (command.substring(1, (command.length() - 1))).toInt();
			cube.MakeMove(Moves_T(temp));
		} else if (command.charAt(0) == 'S') {
			int temp = (command.substring(1, (command.length() - 1))).toInt();
			cube.ScanCube(temp);
		}
	}

}

/*
 *	This is called when new serial data is comming in.
 */
void serialEvent() {
	command = Serial.readStringUntil('\n');
	hasSerial = true;
}
