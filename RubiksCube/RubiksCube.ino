/*
 Name:		RubiksCube.ino
 Created:	3/17/2017 10:25:05 AM
 Author:	fsr19
*/



#include <Stepper.h>
#include <Adafruit_MCP23017.h>
#include "MCPStepper.h"

Adafruit_MCP23017 mcp;
MCPStepper stepper1(200, 0, 1, 2, 3);
MCPStepper stepper2(200, 4, 5, 6, 7);
MCPStepper stepper3(200, 8, 9, 10, 11);
MCPStepper stepper4(200, 12, 13, 14, 15);

// the setup function runs once when you press reset or power the board
void setup() {
	mcp.begin();
	TWBR = 12; //Increase speed of the clock on the chip
	//mcp.pinMode(0, OUTPUT);
	
	stepper1.setMCP(mcp);
	stepper2.setMCP(mcp);
	stepper3.setMCP(mcp);
	stepper4.setMCP(mcp);

	stepper1.setSpeed(10);
	stepper2.setSpeed(10);
	stepper3.setSpeed(10);
	stepper4.setSpeed(10);
	
	
}

// the loop function runs over and over again until power down or reset
void loop() {
	
	stepper1.step(1);
	stepper2.step(1);
	stepper3.step(1);
	stepper4.step(1);
	delay(10);
}
