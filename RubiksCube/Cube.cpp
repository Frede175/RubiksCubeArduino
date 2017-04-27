// 
// 
// 

#include "Cube.h"



Cube::Cube() {
}

Cube::Cube(MCPStepper * stepperF, MCPStepper * stepperL, MCPStepper * stepperB, MCPStepper * stepperR, Servo * servoFB, Servo * servoRL, Servo * servoDoorA, Servo * servoDoorB) {
	this->stepperF = stepperF;
	this->stepperL = stepperL;
	this->stepperB = stepperB;
	this->stepperR = stepperR;
	this->servoFB = servoFB;
	this->servoRL = servoRL;
	this->servoDoorA = servoDoorA;
	this->servoDoorB = servoDoorB;


	moveServo(servoDoorA, constants::SERVO_DOOR_CLOSED_POS);
	moveServo(servoDoorB, constants::SERVO_DOOR_CLOSED_POS);

	moveServo(servoFB, constants::SERVO_OUT_POS);
	moveServo(servoRL, constants::SERVO_OUT_POS);


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

	//Check if steppers are rotated correct. A stepper blocks another arm is the step number is NUMBER_OF_STEPS/4 (50) or NUMBER_OF_STEPS - NUMBER_OF_STEPS/4 (150)
	if (sideIndex == SIDE_F || sideIndex == SIDE_B ) {
		bool r = false, l = false;
		if (stepperR->getStepNumber() == constants::NUMBER_OF_STEPS / 4 || stepperR->getStepNumber() == constants::NUMBER_OF_STEPS - constants::NUMBER_OF_STEPS / 4) r = true;
		if (stepperL->getStepNumber() == constants::NUMBER_OF_STEPS / 4 || stepperL->getStepNumber() == constants::NUMBER_OF_STEPS - constants::NUMBER_OF_STEPS / 4) l = true;
		if (r || l) {
			servoRL->write(constants::SERVO_OUT_POS);
			if (r && l) {
				turnSteppersSync(stepperL, stepperR, 0, false); //Dir is not important
			} else if (r) {
				turnStepper(stepperR, 0, false);
			} else { //l
				turnStepper(stepperL, 0, false);
			}
			servoRL->write(constants::SERVO_IN_POS);
		}
		
	} else { //SIDES: SIDE_L, SIDE_R. This also takes care of rotation if one of the sides is top or bottom
		bool f = false, b = false;
		if (stepperF->getStepNumber() == constants::NUMBER_OF_STEPS / 4 || stepperF->getStepNumber() == constants::NUMBER_OF_STEPS - constants::NUMBER_OF_STEPS / 4) f = true;
		if (stepperB->getStepNumber() == constants::NUMBER_OF_STEPS / 4 || stepperB->getStepNumber() == constants::NUMBER_OF_STEPS - constants::NUMBER_OF_STEPS / 4) b = true;
		if (f || b) {
			servoFB->write(constants::SERVO_OUT_POS);
			if (f && b) {
				turnSteppersSync(stepperF, stepperB, 0, false); //Dir is not important
			} else if (f) {
				turnStepper(stepperF, 0, false);
			} else { //b
				turnStepper(stepperB, 0, false);
			}
			servoFB->write(constants::SERVO_IN_POS);
		}
	}

		
	if (sideIndex >= SIDE_U) { //The face is on the top or bottom of the cube (SIDES: SIDE_T, SIDE_D)
		//Rotate the side that need to be turned to one of the side where there is a stepper.
		//If index is 4 side is on top else side is on bottom. 
		//Rotating the face that need to be turned to the front stepper:

		servoFB->write(constants::SERVO_OUT_POS);

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

		servoFB->write(constants::SERVO_IN_POS);

		sideIndex = Sides_T(SIDE_F);
		//Now that the stepperes have moved, the arm is rotated wrong:
		servoRL->write(constants::SERVO_OUT_POS);
		turnSteppersSync(stepperL, stepperR, 0, false); //Dir is not relavent here.
		servoRL->write(constants::SERVO_IN_POS);
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


	Serial.println("DONE");
}

void Cube::GrabCube() {

	//TODO decide with steppers need to crab:
	servoFB->write(constants::SERVO_IN_POS);
	delay(constants::DELAY_SERVO);
	
	//open the doors:

	for (int i = constants::SERVO_DOOR_CLOSED_POS; i < constants::SERVO_DOOR_OPEN_POS; i++) {
		servoDoorA->write(i);
		servoDoorB->write(i);
	}

	delay(constants::DELAY_SERVO);

	servoRL->write(constants::SERVO_IN_POS);

	delay(constants::DELAY_SERVO);
}

void Cube::ScanCube(int scan) {

	//scan is form 0...5

	switch (scan) {

	case 0:
		//First scan rotate the arms so the camera can see the hole cube.
		servoFB->write(constants::SERVO_OUT_POS);
		turnSteppersSync(stepperF, stepperB, 0, false);
		servoFB->write(constants::SERVO_IN_POS);
		servoRL->write(constants::SERVO_OUT_POS);
		break;
	case 1:
		servoRL->write(constants::SERVO_IN_POS);
		servoFB->write(constants::SERVO_OUT_POS);
		//turnSteppersSync(stepperF, stepperB, 0, false);
		turnSteppersSync(stepperL, stepperR, 0, false);
		break;
	case 2:
		turnSteppersSync(stepperL, stepperR, 0, false);
		servoFB->write(constants::SERVO_IN_POS);
		servoRL->write(constants::SERVO_OUT_POS);
		break;
	case 3:
		turnSteppersSync(stepperF, stepperB, 0, false);
		turnSteppersSync(stepperL, stepperR, 0, false);
		servoRL->write(constants::SERVO_IN_POS);
		moveServo(servoFB, constants::SERVO_OUT_POS);
		break;
	case 4:
		turnSteppersSync(stepperL, stepperR, 0, false);
		turnSteppersSync(stepperF, stepperB, 0, false);
		moveServo(servoFB, constants::SERVO_IN_POS);
		moveServo(servoRL, constants::SERVO_OUT_POS);
		break;
	case 5:
		moveServo(servoRL, constants::SERVO_IN_POS);
		moveServo(servoFB, constants::SERVO_OUT_POS);
		turnSteppersSync(stepperL, stepperR, 0, false);
		break;
	}

	Serial.println("DONE");

}

void Cube::turnStepper(MCPStepper * stepper, int dir, bool overturn) {
	int stepsLeft = dir > 1 ? 100 : 50;
	dir = dir > 0 ? 1 : -1;

	if (overturn) stepsLeft += constants::STEPPER_OVERTURN_AMOUNT;

	while (stepsLeft > 0) {
		stepper->step(dir);
		stepsLeft--;
		if (overturn && stepsLeft == 0) {
			overturn = false;
			dir *= -1;
			stepsLeft += constants::STEPPER_OVERTURN_AMOUNT;
		}
	}
	delay(constants::DELAY_STEPPER);
}

void Cube::moveServo(Servo * servo, int pos) {
	servo->write(pos);
	delay(constants::DELAY_SERVO);
}

void Cube::turnSteppersSync(MCPStepper * stepper1, MCPStepper * stepper2, int dir, bool overturn) {
	int stepsLeft = dir > 1 ? 100 : 50;
	dir = dir > 0 ? 1 : -1;

	if (overturn) stepsLeft += constants::STEPPER_OVERTURN_AMOUNT;

	while (stepsLeft > 0) {
		stepper1->step(dir);
		stepper2->step(dir * -1);
		stepsLeft--;
		if (overturn && stepsLeft == 0) {
			overturn = false;
			dir *= -1;
			stepsLeft += constants::STEPPER_OVERTURN_AMOUNT;
		}
	}
	delay(constants::DELAY_STEPPER);
}

Sides_T Cube::getSide(Moves_T move) {
	return Sides_T(move / 3);
}

int Cube::getDir(Moves_T move) {
	return move % 3;
}
