#ifndef __HELPERS_H
#define __HELPERS_H

#include "main.h"
#include "stdbool.h"
#include "stm32f429i_discovery.h"
#include "stm32f4xx.h"
#include <stdio.h>

typedef struct {
	__IO double *setpoint;
	__IO double *input;
	__IO double *output;
	__IO double  Kp;
	__IO double  Ki;
	__IO double  Kd;
	__IO double  err;
	__IO double  errSum;
	__IO double  inputLast;
	__IO int8_t outputReverse;
} PID_STRUCTURE;

void PID_Setup(double *, double *, double *, double, double, double, bool);
void PID_Update(void);
void Delay(__IO uint32_t time);
int		Rand_Int(int, int);
float   map(float, float, float, float, float);
void	WaitForUserButton(void);
double  saturate(double, double, double);
void	setPWMDuty(float);
double  getTemperature(void);
uint8_t Can_Send_Msg(uint8_t *, uint8_t);
uint8_t Can_Receive_Msg(uint8_t *);

#endif /* __HELPERS_H */
