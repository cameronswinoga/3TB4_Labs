/*
* Helpers file for useful functions
*/

#include "helpers.h"

extern __IO INTURUPT_DATA Inturupt_Data;

__IO PID_STRUCTURE PID_Structure;

void PID_Setup(double *setpoint, double *input, double *output, double Kp, double Ki, double Kd, bool reverse) {
	PID_Structure.setpoint = setpoint;
	PID_Structure.input = input;
	PID_Structure.output = output;
	PID_Structure.Kp = Kp;
	PID_Structure.Ki = Ki;
	PID_Structure.Kd = Kd;
	PID_Structure.err = 0;
	PID_Structure.errSum = 0;
	PID_Structure.inputLast = 0;
	
	PID_Structure.outputReverse = (reverse ? -1 : 1);
}

void PID_Update() {
	PID_Structure.err = *PID_Structure.setpoint - *PID_Structure.input;
	PID_Structure.errSum += PID_Structure.err;
	
	
	double P = PID_Structure.outputReverse * PID_Structure.Kp * (PID_Structure.err);
	double I = PID_Structure.outputReverse * PID_Structure.Ki * (PID_Structure.errSum);
	double D = PID_Structure.outputReverse * PID_Structure.Kd * (*PID_Structure.input - PID_Structure.inputLast);
	
	*PID_Structure.output = (P + I + D);
	PID_Structure.inputLast = *PID_Structure.input;
}

/*
* Generate a random number between LOW and HIGH
*/
int Rand_Int(int LOW, int HIGH) {
	while (RNG_GetFlagStatus(RNG_FLAG_DRDY) == RESET)
		;
	
	return map(RNG_GetRandomNumber(), 0, UINT32_MAX, LOW, HIGH);
}

/*
* Delay for `time` ms
*/
void Delay(__IO uint32_t time) {
	Inturupt_Data.DelayCounter = time;

	while (Inturupt_Data.DelayCounter != 0); // Wait for SysTick to decrement
}

/*
* Map a value `input` from in_min-in_max to out_min-out_max
* as per the formula (X-A)/(B-A) * (D-C) + C
*/
float map(float input, float in_min, float in_max, float out_min, float out_max) {
	return (input - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/*
* Method to wait for the user to press the onboard input button.
* Blocking.
*/
void WaitForUserButton(void) {
	Inturupt_Data.UBPressed = false;
	while (!Inturupt_Data.UBPressed)
		;
	Inturupt_Data.UBPressed = false;
}


/*
* Saturate an input to two bounded values
*/
double saturate(double input, double lower_bound, double upper_bound) {
	if (input < lower_bound)
		return lower_bound;
	else if (input > upper_bound)
		return upper_bound;
	return input;
}

/*
* Set the timer value according to the duty cycle wanted
*/
void setPWMDuty(float duty) {
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	uint16_t CCR1_Val = 699*duty;
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);
}
