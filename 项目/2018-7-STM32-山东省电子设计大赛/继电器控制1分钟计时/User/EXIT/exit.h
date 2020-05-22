#ifndef _EXIT_H
#define _EXIT_H

#include "stm32f10x.h"


/**
*º¯Êý¶¨Òå
**/
void MyNVIC_Init(void);
void EXIT_PB6_Init(FunctionalState Flag);
void EXIT_PB7_Init(FunctionalState Flag);
void EXIT_PB8_Init(FunctionalState Flag);
void Print_Menu(void);
#endif
