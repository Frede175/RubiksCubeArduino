// Cube.h

#ifndef _CUBE_h
#define _CUBE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

enum Sides_T {
	F,
	B,
	L,
	R,
	U,
	D
};

enum Moves_T {
	F, F2, FI, B, B2, BI, L, L2, LI, R, R2, RI, U, U2, UI, D, D2, DI
};


class Cube {
public:
	Cube();

	void MakeMove(Moves_T move);



private:
	Sides_T sides[6];
};



#endif

