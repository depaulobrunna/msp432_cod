#include "stm32f4xx.h"                  // Device header

char i = 'U';
int main(){
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;//HABILITA O CLOCK DA PORTA A
		GPIOA->MODER |= GPIO_MODER_MODER2_1 | GPIO_MODER_MODER3_1;// PA9 tx & PA10 rx COMO AF
    GPIOA-> AFR[1] |= 7 << 4 | 7 << 8 ;//seta a porta A como alternate function
		GPIOA->PUPDR |= GPIO_PUPDR_PUPD9_0 | GPIO_PUPDR_PUPD10_0;//seta como pull up
		GPIOA->OSPEEDR |= 3 << GPIO_OSPEEDR_OSPEED9_Pos | 3 << GPIO_OSPEEDR_OSPEED10_Pos ; // velocidade como 50MHz
		GPIOA->OTYPER &= ~GPIO_OTYPER_OT_9;
		GPIOA->OTYPER &= ~GPIO_OTYPER_OT_10;

		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;//HABILITA O CLOCK DA USART
    USART1->CR1 |= USART_CR1_UE | USART_CR1_RE | USART_CR1_TE;//HABILITA A USART & HABILITA TRANSMISSAO DA USART
//    USART2->CR2 |= USART_CR2_CLKEN;//seta o clock da usart (mas nao precisou)
		
		USART1->BRR = SystemCoreClock/115200;//seta o baud ratE		
	
	while(1)
	{
		while(!(USART1->SR & USART_SR_RXNE));
		USART1->SR &= ~USART_SR_RXNE;
		i = USART1->DR;
		USART1->DR = i;
		while(!(USART1->SR & USART_SR_TC));
		USART1->SR &= ~USART_SR_TC;
	}
		
}
	