#include "msp.h"                        // Device header
void reciver(uint8_t sm,uint8_t rw,uint8_t nbyte);
uint8_t RXData0 = 0;
int main()
{
	//ATIVAÇÃO P/ PROTOCOLO I2C(SLAVE MODE)
	EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_SWRST|
										 3 << EUSCI_B_CTLW0_MODE_OFS| // SETA UCMODE COMO 11(i2c mode)
										 EUSCI_B_CTLW0_SYNC|
										 EUSCI_B_CTLW0_SSEL__SMCLK|
										 0 << EUSCI_B_CTLW0_A10_OFS; // own adress is a 7bit-adress
	
											 
	EUSCI_B0->I2COA0 = 0x43 << EUSCI_B_I2COA0_I2COA0_OFS | // own address is 0x43
										 EUSCI_B_I2COA2_OAEN; // ENABLE OWN ADRESS
	EUSCI_B0->BRW = SystemCoreClock/100000;
	EUSCI_B0->CTLW0 &= ~EUSCI_B_CTLW0_SWRST;
	 
 	
	//config de pinos I/O
	P1->SEL0 |= BIT6|BIT7; // P1.6(SDA) & P1.7(SCL)
	P1->DIR &= ~(BIT6|BIT7); // P1.6 & P1.7 INPUT
	P1->REN |= BIT6|BIT7; // P1.6 & P1.7 PULLUP E PULLDOWN ENABLE
	P1->OUT |= BIT6|BIT7; // P1.6 & P1.7 PULLUP
	
	//LED TESTE
	P2->DIR |= BIT0|BIT1|BIT2; // direciona como saida  e armazena em P2->DIR
  P2->OUT &= ~(BIT0|BIT1|BIT2); // ZERA OS BITS
	// P2.0(RED) P2.1(GREEN) P2.2(BLUE)
	P3->DIR |= BIT5;
	P3->OUT &= ~BIT5;
	while(1)
	{
		reciver(0,0,1);
		if(!(EUSCI_B0->IFG & EUSCI_B_IFG_RXIFG0))//flag para o RXbuffer
		{
			EUSCI_B0->IFG &= ~EUSCI_B_IFG_RXIFG0;//LIMPA A FLAG
			switch(EUSCI_B0->RXBUF)//CHECA DE O BUFFER DE RECPÇÃO
			{
				case 0:
					P2->OUT |= BIT0;//(red)
					break;
				default:
					RXData0 = EUSCI_B0->RXBUF; 
					P2->OUT |= BIT1;//(green)
					break;
			}
		}
		
	}
}
void reciver(uint8_t sm,uint8_t rw,uint8_t nbyte)
{
	EUSCI_B0->CTLW0 |= sm << EUSCI_B_CTLW0_MST_OFS| // slave mode select
										 rw << EUSCI_B_CTLW0_TR|// slave mode reciver(READ|WRITE = READ)
										 EUSCI_B_CTLW0_TXACK; // SETA O ACK
	EUSCI_B0->STATW = nbyte << EUSCI_B_STATW_BCNT_OFS; // NUMEROS DE BYTES
	//EUSCI_B0->ADDRX |= madress << EUSCI_B_ADDRX_ADDRX0;//ENDEREÇO MESTRE	
	
	//EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TXSTT;//START BIT
	
	//while(!(EUSCI_B0->CTLW0 & ~EUSCI_B_CTLW0_TXNACK)); // ESPERA O ACK SER 0
	P3->OUT ^= BIT5;//(LEDA)
	//while(!(EUSCI_B0->CTLW0 & ~EUSCI_B_CTLW0_TXACK)); // ESPERA O NACK SER SETADO(?)
}
