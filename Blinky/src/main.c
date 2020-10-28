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

void delayMs(int delay);
void SysclcokInit(void);

int main(void)
{

	SysclcokInit();
	RCC->APB2ENR = (1UL << 4); //GPIOC portları aktif edildi.

	GPIOC->CRH |= (1UL << 20);  //GPIOC portu 2MHz olarak ayarlandı.
	GPIOC->CRH &= ~(3UL << 22); // GPIOC Portu output olarak set edildi.

	for(;;){
		GPIOC->ODR = (1UL << 13);
		delayMs(1000);
		GPIOC->ODR &= ~(1UL << 13);
		delayMs(1000);
	}
}

void delayMs(int delay){
	int i;
	for (; delay >0; delay--){
		for(i=0; i<7200; i++);
	}
}

void SysclcokInit(void){

	FLASH->ACR  |= 0b010; /* FLASH_ACR_LATENCY: 2 wait states */

	PWR->CR = (7U << 5U);
	PWR->CSR &= ~(1 << 2);

	RCC->CR &= 0X00000001U; //HSI enabled
		while(!(RCC->CR & 0X00000002)); //Wiating for HSI ready.

	RCC->CFGR = 0x00000000U; //PLL, PLLXTPRE, PLLMUL[3:0],MCO, USB reset.
	RCC->CFGR = (7UL << 24U); //MCO[3:0] 111 PLLCLK divided 2 36Mhz.
	RCC->CFGR |= 0x00000000U; //PLLXTPRE HSE 1
	RCC->CFGR |= (1UL << 16U); //PLLSRC hse
	RCC->CFGR |= (7UL << 18U); //PLLmux *9
	RCC->CFGR |= 0x00000000U;  /* ADC prescaler is 6 */
	RCC->CFGR |= 0x00000000U; //APB2 not divided 72Mhz.
	RCC->CFGR |= (4U << 8U); //APB1 prescaler PLLCLK1 /2 36Mhz
	RCC->CFGR |= 0x00000000U; /* AHB prescaler is 1 */

	RCC->CR = 0x00010000U; //HSE enabled
		while(!(RCC->CR & 0x00020000U)); //waiting for HSE ready.

	RCC->CR |= RCC_CR_PLLON; //PLLON
		while(!(RCC->CR & 0x02000000U)); //PLLry flag wait

	RCC->CFGR &= ~0x00000003; /* clear */

	RCC->CFGR |= RCC_CFGR_SW_PLL;   /* SYSCLK is PLL */
		while(!(RCC->CFGR & 0x00000008U));

	//RCC->CIR = 0xFFFFFFFFU; //Clear all interrupt;



}
