 /**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

//USART2_TX : PA2 Port


#include "stm32f1xx.h"


void SysclcokInit(void);
void USART1_init(void);
void USART_write(char ch);
void delayMs(int delay);


int main(void)
{



	SysclcokInit();

	RCC->APB2ENR |= 0x00000004; //GPIOA ve GPIOD port clock enabled.

	GPIOA->CRH 	 = 0x00000000; // Clear port conf
	GPIOA->CRH  |= (0x3U << (4U)); //PA9 portu TX için alternatif fonksiyon push pull olarak ayarlandı.

	GPIOA->CRH  |= (0x2U << (6U)); //PA9 AF push/pull


	USART1_init();

	//SystemInit();



	while(1){
		USART_write('G');
		USART_write('o');
		USART_write(' ');
		USART_write('T');
		USART_write('o');
		USART_write(' ');
		USART_write('H');
		USART_write('e');
		USART_write('l');
		USART_write('l');

		USART_write('\n');

		delayMs(100);

	}

}

void SysclcokInit(void){

	FLASH->ACR  |= 0b010; /* FLASH_ACR_LATENCY: 2 wait states */

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

void USART1_init(void){
	RCC->APB2ENR |= 0x00000001; //AFIO Aktif edildi.

	RCC->APB2ENR |= 0x00004000; //Usart1 aktif edildi.

	USART1->BRR  = 0x1D4C;
	USART1->CR1 = 0x0008;
	USART1->CR1 |= 0x2000;
	USART1->CR2 = 0x00000000;
	USART1->CR3 = 0x00000000;
}

void USART_write(char ch){
	while(!(USART1->SR & 0x0080)){}
	USART1->DR = (ch);
}

void delayMs(int delay){
	int i;
	for (; delay >0; delay--){
		for(i=0; i<7200; i++);
	}
}
