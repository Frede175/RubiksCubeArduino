// 
// 
// 

#include "Cube.h"



Cube::Cube() {
}

Cube::Cube(MCPStepper * stepperF, MCPStepper * stepperL, MCPStepper * stepperB, MCPStepper * stepperR) {
	this->stepperF = stepperF;
	this->stepperL = stepperL;
	this->stepperB = stepperB;
	this->stepperR = stepperR;

	for (int i = 0; i < 6; i++) {
		sides[i] = Sides_T(i);
	}

}

void Cube::MakeMove(Moves_T move) {
	Sides_T side = getSide(move);
	int dir = getDir(move);

	Sides_T sideIndex;
	//Check if the side that need to be move is at one of the steppers:
	for (int s = 0; s < 6; s++) {
		if (sides[s] == side) {
			sideIndex = Sides_T(s);
			break;
		}
	}

	if (sideIndex >= 4) {
		//Rotate the side that need to be turned to one of the side where there is a stepper.
		//If index is 4 side is on top else side is on bottom. 
		//Rotating the face that need to be turned to the front stepper:
		if (sideIndex == SIDE_U) {
			turnSteppersSync(stepperL, stepperR, 1);
			Sides_T temp = sides[0];
			Sides_T temp1;
			sides[0] = side;
			temp1 = sides[5];
			sides[5] = temp;
			temp = sides[1];
			sides[1] = temp1;
			sides[4] = temp1;
		} else {
			turnSteppersSync(stepperL, stepperR, 0);
			Sides_T temp = sides[1];
			Sides_T temp1;
			sides[1] = side;
			temp1 = sides[5];
			sides[5] = temp;
			temp = sides[0];
			sides[0] = temp1;
			sides[4] = temp1;
		}
		sideIndex = Sides_T(SIDE_F);
	}

	//Now rotate the side that needs to rotated:
	switch (sideIndex) {
	case SIDE_F:
		turnStepper(stepperF, dir);
		break;
	case SIDE_B:
		turnStepper(stepperB, dir);
		break;
	case SIDE_L:
		turnStepper(stepperL, dir);
		break;
	case SIDE_R:
		turnStepper(stepperR, dir);
		break;
	}


}

void Cube::turnStepper(MCPStepper * stepper, int dir) {
	Serial.println("Turned Called");

	int stepsLeft = dir > 1 ? 100 : 50;
	dir = dir > 0 ? 1 : -1;

	while (stepsLeft > 0) {
		stepper->step(dir);
		stepsLeft--;
	}
}

void Cube::turnSteppersSync(MCPStepper * stepper1, MCPStepper * stepper2, int dir) {
	int stepsLeft = dir > 1 ? 100 : 50;
	dir = dir > 0 ? 1 : -1;

	while (stepsLeft > 0) {
		stepper1->step(dir);
		stepper2->step(dir * -1);
		stepsLeft--;
	}
}

Sides_T Cube::getSide(Moves_T move) {
	return Sides_T(move / 3);
}

int Cube::getDir(Moves_T move) {
	return move % 3;
}
