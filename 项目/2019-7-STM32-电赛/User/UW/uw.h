#ifndef _UW_H
#define _UW_H

#include "sys.h"

#define uint unsigned int
#define TRIG_Send  PAout(6)
#define ECHO_Reci  PAin(7)

void CH_SR04_Init(void);
float Senor_Using(void);


#endif
