#include "msp.h"                        // Device header
 
int main()
{
		//PWM
		 	
		TIMER_A0->CTL |= TIMER_A_CTL_SSEL__SMCLK |//SELECIONA O CLOCK P/ O TIMER
										 TIMER_A_CTL_ID_3|//DIVIDE O CLOCK POR 8
										 TIMER_A_CTL_MC__UP;
		TIMER_A0->EX0 |= TIMER_A_EX0_TAIDEX_5;//DIVIDE O CLOCK POR 6	
		TIMER_A0->CCR[0] = 500;
		TIMER_A0->CCR[1] = 250;
		//TIMER_A0->CCR[2] = 250;
		TIMER_A0->CCTL[1] |= 6 << TIMER_A_CCTLN_OUTMOD_OFS;// | TIMER_A_CCTLN_CCIE;
		//TIMER_A0->CCTL[2] |= 2 << TIMER_A_CCTLN_OUTMOD_OFS;
		
		P2->SEL0 |= BIT4|BIT5;
		P2->SEL1 &= ~(BIT4|BIT5);
		P2->DIR |= BIT4|BIT5;
		
		//serial
		EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_SWRST | 
											 EUSCI_A_CTLW0_SSEL__SMCLK ;//ESCOLHE O CLOCK
		EUSCI_A0->MCTLW |= EUSCI_A_MCTLW_OS16 |//OS16 = 1 
											 10 << EUSCI_A_MCTLW_BRF_OFS | // UCBRF ARMAZENA O INTEIRO
											 0xD6 << EUSCI_A_MCTLW_BRS_OFS; // UCBRS ARMAZENA UM VALOR SEGUNDO A TABELA DO REFERENCE 
		EUSCI_A0->BRW = 1;
		EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_SWRST;
		
		P1->SEL0 |= BIT2 | BIT3;//SELECIONA AF PARA O PINO 1.2
		P1->SEL1 &= ~BIT2 | BIT3;//SELECIONA AF PARA O PINO 1.3
		
		char menos = '-' ;
		while(1)
		{
			while(!(EUSCI_A0->IFG & EUSCI_A_IFG_RXIFG));
			EUSCI_A0->IFG &= ~(EUSCI_A_IFG_RXIFG);
			
			switch(EUSCI_A0->RXBUF)
			{
				case '-':
					TIMER_A0->CCTL[1] |= 9 << TIMER_A_CCTLN_OUTMOD_OFS;
					
					break;
				
				case '+':
					break;	
				
				default:
					break;
				
					
			}
		}
		
}
