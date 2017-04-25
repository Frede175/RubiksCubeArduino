// Cube.h
#pragma once
#ifndef _CUBE_h
#define _CUBE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "MCPStepper.h"
#include "Constants.h"
#include "Servo.h"

enum Sides_T {
	SIDE_F, SIDE_B,
	SIDE_L, SIDE_R,
	SIDE_U, SIDE_D
};

enum Moves_T {
	F, F2, FI, B, B2, BI, L, L2, LI, R, R2, RI, U, U2, UI, D, D2, DI
};




class Cube {
public:

	Cube();
	Cube(MCPStepper * stepperF, MCPStepper * stepperL, MCPStepper * stepperB, MCPStepper * stepperR, Servo * servoFB, Servo * servoRL, Servo * servoDoorA, Servo * servoDoorB);

	void MakeMove(Moves_T move);

	void GrabCube();

	void ReleaseCube();


	void ScanCube(int scan);
	

	
	
private:
	MCPStepper * stepperF;
	MCPStepper * stepperL;
	MCPStepper * stepperB;
	MCPStepper * stepperR;
	Servo * servoFB;
	Servo * servoRL;
	Servo * servoDoorA;
	Servo * servoDoorB;
	
	 //Dir is relavative to the first stepper entered.
	void turnSteppersSync(MCPStepper * stepper1, MCPStepper * stepper2, int dir, bool overturn = true);

	/*
	* dir is 0 for -90, 1 for 90, 2 for 180
	*/
	void turnStepper(MCPStepper * stepper, int dir, bool overturn = true);

	void moveServo(Servo * servo, int pos);

	Sides_T getSide(Moves_T move);

	/*
	 * dir is 0 for -90, 1 for 90, 2 for 180
	 */
	int getDir(Moves_T move);

	Sides_T sides[6];
};


#endif

