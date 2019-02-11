/*
 * DC_Motor.h
 *
 *  Created on: Nov 29, 2018
 *      Author: chang
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

typedef struct DC_Motor DC_Motor;

struct DC_Motor {

	unsigned int count;
	double gearRatio;
	double k[3]; //kp,kd,ki;
	double position;

	bool pid;
};

void DC_Motor_init(DC_Motor * motor, double gR, double ks[3]);
void SetMode(DC_Motor * motor, bool PositionControl);
void SetZero(DC_Motor * motor);
void SetGoal(DC_Motor * motor);
void GetPos(DC_Motor * motor);
void UpdatePos(DC_Motor * motor);

// Working functions

void Run(DC_Motor * motor,)

#endif /* DC_MOTOR_H_ */
