#ifndef _USER_PIDCALCULAT
#define _USER_PIDCALCULAT

#include "stm32f10x.h"
typedef  struct
{
	float Kp;
	float Ki;
	float Kd;
	float Ep;
	float Ei;
	float Ed;
	float Last_Ed;
}PID_TypeDef;

float PID_Calculate(PID_TypeDef PID_Struct);
#endif
