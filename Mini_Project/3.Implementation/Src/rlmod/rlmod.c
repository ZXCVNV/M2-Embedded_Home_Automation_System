/* 
=============================================================================== 
This module takes input in the following format 
#<MODULE NO.>&<FUNCTION>* 
================================================================================
Functions
0=Off
1=On
2=Test
3=Alarm On
4=Alarm Off
================================================================================= 
PIN CONNECTIONS=>  
GREEN LED: PORTB0 
BLUE LED: PORTB1 
RED LED: PORTB2 
RELAY:  PORTB3 
UART RX: PORTD0 
UART TX: PORTD1 
==================================================================================  
*/ 
#include<avr/io.h> 
#include"UART.h" 
#include<util/delay.h>  
#define red PB2  //Red Led Pin 
#define green PB0 //Green Led Pin 
#define blue PB1 //Blue Led Pin 
#define relay PB3 //Relay Pin  
uint8_t stat=0;  
void devswit( uint8_t did,uint8_t onoff) //first argument is device id ie. red green blue or relay and second argument is on or off command 
{ 
if(onoff==1) 
{ 
PORTB|=(1<<did); 
} 
else if(onoff==0) 
{ 
PORTB&=~(1<<did); 
} 
}  
void dev_tst()  //TEST SUBROUTINE 
{ 
devswit(relay,0); 
devswit(green,0); 
devswit(blue,0); 
devswit(red,0); 
_delay_ms(5000); 
devswit(red,1); 
_delay_ms(5000); 
devswit(red,0); 
devswit(green,1); 
_delay_ms(5000); 
devswit(green,0); 
devswit(blue,1); 
_delay_ms(5000); 
devswit(blue,0); 
devswit(relay,1); 
_delay_ms(5000); 
devswit(relay,0); 
devswit(relay,0); 
devswit(green,0); 
devswit(blue,0); 
devswit(red,0); 
_delay_ms(5000); 
loads(); 
}  
void loads() 
{ 
if( stat==0) 
{ 
devswit(relay,0); 
devswit(green,0); 
devswit(blue,0); 
devswit(red,1); 
} 
else if(stat==1) 
{ 
devswit(relay,1); 
devswit(green,1); 
devswit(blue,0); 
devswit(red,0); 
} 
else 
{ 
devswit(green,1); 
devswit(blue,1); 
devswit(red,1); 
} 
}  
void sys_alm(uint8_t alm_stat)  //ACTIVATES AND DEACTIVATES ALARM MODE/CONTROL SIGNAL
{ 
switch (alm_stat) 
{ 
case 1: devswit(relay,0); 
  devswit(green,0); 
  devswit(blue,1); 
  break; 
case 0: loads(); 
  break; 
} 
}   
void actuate(uint8_t mswit) //this function performs the selected action if the module name matches or if the system commands are entered (4&5) 
{ 
switch(mswit) 
{ 
case '0':stat=0; 
  loads(); 
  break;  
case '1':stat=1; 
  loads(); 
  break;  
case '2': dev_tst(); 
  break;  
case '3': sys_alm(0); 
  break;  
case '4': sys_alm(1); 
  break; 
default:break; 
} 
}  
void main() 
{ 
devswit(relay,0); 
devswit(blue,1); 
DDRB=0xFF; 
UART_init(); 
uint8_t cx,fn=9; 
_delay_ms(5000); 
loads(); 
devswit(blue,0); 
while(1) 
{ 
cx=UART_rx(); 
if(cx=='#') 
{ 
cx=UART_rx(); 
if(cx=='6'||cx=='Z') //number denotes the module number
{ 
cx=UART_rx(); 
if(cx=='&') 
{ 
fn=UART_rx(); 
} 
} 
cx=UART_rx(); 
while(cx!='*') 
{ 
cx=UART_rx(); 
} 
actuate(fn); 
fn=9; 
} 
} 
}
