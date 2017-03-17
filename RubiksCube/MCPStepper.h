// MCPStepper.h

#ifndef _MCPSTEPPER_h
#define _MCPSTEPPER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
	#include <Adafruit_MCP23017.h>
#else
	#include "WProgram.h"
#endif


#endif


class MCPStepper {
public:
	// constructors:
	MCPStepper(int number_of_steps, int motor_pin_1, int motor_pin_2);
	MCPStepper(int number_of_steps, int motor_pin_1, int motor_pin_2,
		int motor_pin_3, int motor_pin_4);
	MCPStepper(int number_of_steps, int motor_pin_1, int motor_pin_2,
		int motor_pin_3, int motor_pin_4,
		int motor_pin_5);

	// speed setter method:
	void setSpeed(long whatSpeed);

	// mover method:
	void step(int number_of_steps);
	void setMCP(Adafruit_MCP23017 mcp);

	int version(void);

private:
	void stepMotor(int this_step);
	Adafruit_MCP23017 mcp;
	boolean hasMCP;
	boolean isPinModeSet;
	int direction;            // Direction of rotation
	unsigned long step_delay; // delay between steps, in ms, based on speed
	int number_of_steps;      // total number of steps this motor can take
	int pin_count;            // how many pins are in use.
	int step_number;          // which step the motor is on

							  // motor pin numbers:
	int motor_pin_1;
	int motor_pin_2;
	int motor_pin_3;
	int motor_pin_4;
	int motor_pin_5;          // Only 5 phase motor

	unsigned long last_step_time; // time stamp in us of when the last step was taken
	void _digitalWrite(uint8_t pin, uint8_t value);
	void _pinMode(uint8_t pin, uint8_t value);
};
