#include "msp.h"                        // Device header

void EUSCIB0_IRQHandler(void);

uint8_t RXData0 = 0;

int main(void)
{
	
	

	//led test
	P2->DIR |= BIT0;//direciona como saida  e armazena em P2->DIR
  P2->OUT &= ~BIT0;//ZERA OS BITS
	// Configure Pins for I2C
	P1->SEL0 |= BIT6 | BIT7;                // I2C pins

	// Enable global interrupt
	__enable_irq();

	// Enable eUSCIB0 interrupt in NVIC module
	NVIC_EnableIRQ(EUSCIB0_IRQn);

	// Configure USCI_B0 for I2C mode
	EUSCI_B0->CTLW0 |= EUSCI_A_CTLW0_SWRST; // Software reset enabled
	EUSCI_B0->CTLW0 = EUSCI_A_CTLW0_SWRST | // Remain in reset
										EUSCI_B_CTLW0_MODE_3;           // I2C slave mode, SMCLK
	EUSCI_B0->I2COA0 = 0x43 << EUSCI_B_I2COA0_I2COA0_OFS | // own address is 0x43               // SLAVE0 own address is 0x0A
										 EUSCI_B_I2COA2_OAEN;            // Enable slave own address 0
	EUSCI_B0->CTLW0 &= ~EUSCI_A_CTLW0_SWRST; // clear reset register

	EUSCI_B0->IE |=  EUSCI_B_IE_RXIE0;     // Enable receive interrupts
					

	
}

// I2C interrupt service routine
void EUSCIB0_IRQHandler(void)
{  
	if (EUSCI_B0->IFG & EUSCI_B_IFG_RXIFG0)
	{
		EUSCI_B0->IFG &= ~EUSCI_B_IFG_RXIFG0;
		RXData0 = EUSCI_B0->RXBUF;
	}
	P2->OUT |= BIT0; 
}
