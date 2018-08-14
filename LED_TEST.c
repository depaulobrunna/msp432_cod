#include "msp.h"                        // Device header
uint32_t i;
int main()
{
	P2->DIR |= BIT0|BIT1|BIT2;//direciona como saida  e armazena em P2->DIR
  P2->OUT &=~(BIT0|BIT1|BIT2);//ZERA OS BITS
	P2->OUT |=BIT0;
    
    while(1)
		{
        for(i=0;i<100000;i++);
        P2->OUT ^=BIT0|BIT1;
        for(i=0;i<100000;i++);
        P2->OUT ^=BIT1|BIT2;
        for(i=0;i<100000;i++);
        P2->OUT ^=BIT2|BIT0;
    }
}
