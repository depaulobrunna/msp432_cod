#include "msp.h"

void TA1_0_IRQHandler(void);

volatile uint8_t pos = 0;

//uint16_t duty[11] =  {6250,6174,5882,4327,3125,1923,970,368,76,0};

//const uint16_t duty[21] =  {31250,31164,30869,30306,29412,28125,26401,24226,21635,18719,15625,12531,9615,7024,4849,3125,1838,944,381,86,0};

//const uint16_t duty[16] =  {624,621,610,587,551,499,432,353,271,192,125,73,37,14,3,0};

//const uint8_t duty[16] =  {250,249,244,235,221,200,173,142,108,77,50,29,15,6,1,0};
const uint16_t duty[6] =  {125,118,87,39,7,0};

int main()
{
    //PWM
		 	
		TIMER_A0->CTL |= TIMER_A_CTL_SSEL__SMCLK |//SELECIONA O CLOCK P/ O TIMER
										 TIMER_A_CTL_ID_3|//DIVIDE O CLOCK POR 8
                     TIMER_A_CTL_MC__UP;//Up mode: Timer counts up to TAxCCR0
		TIMER_A0->EX0 |= TIMER_A_EX0_TAIDEX_5;//DIVIDE O CLOCK POR 6	
		TIMER_A0->CCTL[1] |= TIMER_A_CCTLN_OUTMOD_6;
	
		TIMER_A0->CCR[0] = 125;//CONTA ATÉ:

		TIMER_A0->CCR[1] = 0;//COMEÇA DE:

		
		//timer a1
		TIMER_A1->CTL |= TIMER_A_CTL_SSEL__SMCLK |//SELECIONA O CLOCK P/ O TIMER
            			 TIMER_A_CTL_ID_3|//DIVIDE O CLOCK POR 8
                         TIMER_A_CTL_MC__UP;//Up mode: Timer counts up to TAxCCR0
		TIMER_A1->EX0 |= TIMER_A_EX0_TAIDEX_5;//DIVIDE O CLOCK POR 6
		
		TIMER_A1->CCTL[0] |= TIMER_A_CCTLN_CCIE;
		
		TIMER_A1->CCR[0] = 12500;//CONTA ATÉ:

		//TIMER_A1->CCR[1] = 0;//COMEÇA DE:

		
		NVIC_EnableIRQ(TA1_0_IRQn);
		
		P2->SEL0 |= BIT4;
		P2->SEL1 &= ~(BIT4);
		P2->DIR |= BIT4;
		
    while(1);
}

void TA1_0_IRQHandler(void)
{
  
	TIMER_A1->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
	TIMER_A0->CCR[1] = duty[pos++];
	if(pos > 6)
	{
	    pos = 0;
			TIMER_A0->CCTL[1] ^= BIT7;
	}
	

}
