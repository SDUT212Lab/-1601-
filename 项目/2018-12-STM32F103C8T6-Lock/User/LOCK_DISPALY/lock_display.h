#ifndef _LOCK_DISPLAY_H
#define _LOCK_DISPLAY_H
/*ͷ�ļ�*/
#include "stm32f10x.h"
#include "fyu43t4827.h"
#include "matrix_key.h"

/*��������*/
void Lock_Dispaly(void);

#define LOCK_OK					15
#define LOCK_BACKSPACE	10
#define LOCK_CANCEL			14
#define LOCK_START			13
#define PASSWORD				212666

#endif

