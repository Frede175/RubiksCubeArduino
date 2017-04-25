#pragma once
#ifndef CONSTANTS_T
#define CONSTANTS_T

namespace constants {
	const int NUMBER_OF_STEPS = 200;

	const int STEPPER_SPEED = 10;

	const int STEPPERF_PIN1 = 0;
	const int STEPPERF_PIN2 = 1;
	const int STEPPERF_PIN3 = 2;
	const int STEPPERF_PIN4 = 3;

	const int STEPPERL_PIN1 = 4;
	const int STEPPERL_PIN2 = 5;
	const int STEPPERL_PIN3 = 6;
	const int STEPPERL_PIN4 = 7;

	const int STEPPERB_PIN1 = 8;
	const int STEPPERB_PIN2 = 9;
	const int STEPPERB_PIN3 = 10;
	const int STEPPERB_PIN4 = 11;

	const int STEPPERR_PIN1 = 12;
	const int STEPPERR_PIN2 = 13;
	const int STEPPERR_PIN3 = 14;
	const int STEPPERR_PIN4 = 15;

	const int SERVO_FB_PIN = 3;
	const int SERVO_RL_PIN = 5;

	const int SERVO_DOORA_PIN = 6;
	const int SERVO_DOORB_PIN = 9;

	const int SERVO_IN_POS = 100;
	const int SERVO_OUT_POS = 50;

	const int SERVO_DOOR_OPEN_POS = 100;
	const int SERVO_DOOR_CLOSED_POS = 50;

	const int DELAY_STEPPER = 50; //ms
	const int DELAY_SERVO = 50; //ms

	const int STEPPER_OVERTURN_AMOUNT = 5;
}



#endif // !CONSTANTS_T
