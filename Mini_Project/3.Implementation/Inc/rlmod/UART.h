#ifndef UART_H_
#define UART_H_


/************************************************************************* 
For initializing UART for Tx-Rx @8Mhz, 9600bps, 8 bit transmission,1 stop bit
*************************************************************************/

void UART_init()
{
UBRRH=0;
UBRRL=51;
UCSRC=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
UCSRB=(1<<RXEN)|(1<<TXEN);
}

/************************************************************************* 
For Transmitting one byte of data via PD0
Use: UART_tx(data_byte);
*************************************************************************/

void UART_tx(uint8_t tx)
{
UDR=tx;
while(!(UCSRA&(1<<UDRE)));
}

/************************************************************************* 
For Receiving one byte of data via PD1
Use: unsigned char var=UART_rx();
*************************************************************************/

unsigned char UART_rx()
{
while((UCSRA&(1<<RXC))==0);
return(UDR);
}

/************************************************************************* 
For Transmitting string via PD1
Use: UART_txs(string[]);
*************************************************************************/

void UART_txs(uint8_t s[])
{
unsigned int a=0;
while(s[a]!='\0')
{
UART_tx(s[a]);
a++;
}
}
void UART_txsl(uint8_t s[],uint8_t k)
{
unsigned int a=0;
while(a<k)
{
UART_tx(s[a]);
a++;
}
}
#endif
