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

	RCC->APB2ENR = 0X00000000; //APB2ENR restlendi.
	RCC->APB2ENR |= 0x00000001; //AFIO Aktif edildi.
	RCC->APB2ENR |= (7UL << 3); //GPIOC ve GPIOB portlarının clock aktif edildi.

	GPIOC->CRH |= (2UL << 20); //GPIOC_PIN_13 2MHz olarak ayarlandı.
	GPIOC->CRH &= ~(3UL << 22); //GPIOC_PIN_13 Output olarak ayarlandı.


	AFIO->MAPR = 0X00000000; //AFIO_MAPR Restlendi.
	AFIO->MAPR |= (2UL << 24); //SWJ_CFG[2:0] "010" JTAG-DP Disabled and SW-DP Enabled olarak ayarlandı.

	GPIOB->CRL = 0X00000000;
	GPIOB->CRL |= 0X00002000;

	GPIOB->ODR |= 0X00000000;



	while(1){
		if(GPIOB->IDR & 0x00000008){
			GPIOC->BSRR = (1UL << 13);
		}else{
			GPIOC->BSRR = (1UL << 29);
		}

	}
}
