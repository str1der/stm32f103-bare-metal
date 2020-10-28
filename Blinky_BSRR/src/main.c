	/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f1xx.h"

void delayMs(int delay);

int main(void)
{
	RCC->APB2ENR = 0X10;

	GPIOC->CRH = 0X244444;


	for(;;){
		GPIOC->BSRR = 0X2000;
		delayMs(100);
		GPIOC->ODR = 0X20000000;
		delayMs(100);
	}
}

void delayMs(int delay){
	int i;
	for (; delay >0; delay--){
		for(i=0; i<3195; i++);
	}
}
