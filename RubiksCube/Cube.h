// Cube.h
#pragma once
#ifndef _CUBE_h
#define _CUBE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
	#include "MCPStepper.h"

#else
	#include "WProgram.h"
#endif




class Cube {
public:

	enum Sides_T {
		SIDE_F, SIDE_B,
		SIDE_L, SIDE_R,
		SIDE_U, SIDE_D
	};

	enum Moves_T {
		F, F2, FI, B, B2, BI, L, L2, LI, R, R2, RI, U, U2, UI, D, D2, DI
	};

	



	Cube();
	Cube(MCPStepper * stepperF, MCPStepper * stepperL, MCPStepper * stepperB, MCPStepper * stepperR);

	void MakeMove(Moves_T move);



private:
	MCPStepper * stepperF;
	MCPStepper * stepperL;
	MCPStepper * stepperB;
	MCPStepper * stepperR;
	void turnStepper(int stepper, int dir);
	void turnSteppersSync(int stepper1, int stepper2, int dir);

	Sides_T sides[6];
};


#endif

