#include "user_pidcalculate.h"



float PID_Calculate(PID_TypeDef PID_Struct)
{
	float es; //º∆À„ ‰≥ˆ÷µ
	
	es = PID_Struct.Kp*PID_Struct.Ep + PID_Struct.Ki*PID_Struct.Ei+PID_Struct.Kd*PID_Struct.Ed+500;
	
	return es;
}

