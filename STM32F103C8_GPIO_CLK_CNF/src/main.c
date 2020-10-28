/**
  ******************************************************************************
  * @file    main.c
  * @author  DemboraG
  * @version V1.0
  * @date    02-Oct-2020
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f1xx.h"
void delaMs(int delay);

int main(void)
{
	RCC->CR = (1UL << 16); //HSEON değerini 1 yaptık. Harici oscilator devrede.
		while(!(RCC->CR & (1UL << 17))); //HSERDY flag 1 olana kadar 6 döngü beliyoruz.

	RCC->CFGR = (7UL << 18); //PLL çarpanı 9 olarak ayarlandı. PLL on yapılmadan önce ayarlanması gerektiği belirtilmiş.

	RCC->CR |= (1UL << 24); //PLLON PLL clock aktif edildi.

	RCC->CFGR &= ~(1<<7); //AHB prescaler dvider 1 olarak ayarlandı.
	RCC->CFGR &= ~(1<<13); //APB2 prescaler divider 1  oarak ayarlandı.
	RCC->CFGR |= 0X00000001u; // System Clock Switch HSE olarak ayarlandı.
	RCC->CIR |= (3UL<<19); //PLL ve HSE kesmelerini kaldırdık.

	RCC->APB2ENR = (3UL << 3); //GPIOB ve GPIOC portları aktif edildi.

	GPIOC->CRH &= ~(3UL << 22); // GPIOC Portu output olarak set edildi.
	GPIOC->CRH |= (1UL << 21); //  GPIOC portu 10MHz olarak ayarlandı.

	while(1){
		GPIOC->ODR = (1<< 13);
		delaMs(100);
		GPIOC->ODR &= ~(1<<13);
		delaMs(100);
	}
}

void delaMs(int delay){
	int i;
	for(;delay > 0; --delay){
		for(i=0; i<3195; i++);
	}
}
