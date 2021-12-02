/* 
===================================================================================== ====== 
Touch + GLCD remote controller Module 
===================================================================================== ====== 
Port/Pin Configurations  
Data Output Port: PORT B  
Control Pins: PORT D 
E =PD2 
RW =PD3 
RS =PD4 
C1 =PD5 
C2 =PD6 
R =PD7  
TOUCH CONTROLLER : PORT A 
X=PA0 
X-=PA1 
Y-=PA2 
Y=PA3
===================================================================================== ======= 
OUTGOING FUNCTION CALLS  
2= Time Date Query 
4= Switch On a Module 
5= Switch off a Module 
3= Update Remote module   
===================================================================================== ====== 
*/   
#include<avr/io.h> 
#include<util/delay.h> 
#include<avr/pgmspace.h> 
#include"GLCD.h" 
#include"TOUCH.h" 
#include"UART.h"   
uint8_t tdt[10],page;  
//=================================================================================== =========================================  
uint8_t touch_react() 
{ 
vl=0; 
butn_no(); 
if(page==0)//lock screen 
{ 
if(vl==73) 
{ 
p_lok(1); 
_delay_ms(5000); 
p_lok(0); 
home(); 
return vl; 
} 
else return 0; 
} 
else if(page==1)//home screen 
{ 
if(vl==10) 
{ 
p_udx(1,1); 
_delay_ms(5000); 
p_udx(0,1); 
page=2; 
c_m(); 
return vl; 
} 
else if(vl==30) 
{ 
p_udx(1,3); 
_delay_ms(5000); 
sys_s(0,3); 
c_m(); 
return vl; 
} 
else if(vl==50) 
{ 
p_udx(1,5); 
_delay_ms(5000); 
p_udx(0,5); 
abt(); 
return vl; 
} 
else if(vl==73) 
{ 
p_lok(1); 
_delay_ms(5000); 
p_lok(0); 
lok(); 
return vl; 
} 
else return 0; 
} 
else if(page==2)//control menu 1 
{ 
if(vl==10) 
{ 
p_onn(1,1); 
_delay_ms(5000); 
p_onn(0,1); 
UART_txs("#0&4&1"); 
return vl; 
} 
else if(vl==30) 
{ 
p_onn(1,3); 
_delay_ms(5000); 
p_onn(0,3); 
UART_txs("#0&4&2"); 
return vl; 
} 
else if(vl==50) 
{ 
p_onn(1,5); 
_delay_ms(5000); 
p_onn(0,5); 
UART_txs("#0&4&6"); 
return vl; 
} 
else if(vl==11) 
{ 
p_off(1,1); 
_delay_ms(5000); 
p_off(0,1); 
UART_txs("#0&5&1"); 
return vl; 
} 
else if(vl==31) 
{ 
p_off(1,3); 
_delay_ms(5000); 
p_off(0,3); 
UART_txs("#0&5&2"); 
return vl; 
} 
else if(vl==51) 
{ 
p_off(1,5); 
_delay_ms(5000); 
p_off(0,5); 
UART_txs("#0&5&6"); 
return vl; 
} 
else if(vl==70) 
{ 
p_home(1); 
_delay_ms(5000); 
p_home(0); 
home(); 
return vl; 
} 
else if(vl==72) 
{ 
p_fwd(1); 
_delay_ms(5000); 
p_fwd(0); 
page=3; 
c_m(); 
return vl; 
} 
else if(vl==73) 
{ 
p_lok(1); 
_delay_ms(5000); 
p_lok(0); 
lok(); 
return vl; 
} 
else return 0; 
} 
else if(page==3)// control menu 2 
{ 
if(vl==20) 
{ 
p_onn(1,2); 
_delay_ms(5000); 
p_onn(0,2); 
UART_txs("#0&4&3"); 
return vl; 
} 
else if(vl==40) 
{ 
p_onn(1,4); 
_delay_ms(5000); 
p_onn(0,4); 
UART_txs("#0&4&4"); 
return vl; 
} 
else if(vl==60) 
{ 
p_onn(1,6); 
_delay_ms(5000); 
p_onn(0,6); 
UART_txs("#0&4&5"); 
return vl; 
} 
else if(vl==21) 
{ 
p_off(1,2); 
_delay_ms(5000); 
p_off(0,2); 
UART_txs("#0&5&3"); 
return vl; 
} 
else if(vl==41) 
{ 
p_off(1,4); 
_delay_ms(5000); 
p_off(0,4); 
UART_txs("#0&5&4"); 
return vl; 
} 
else if(vl==61) 
{ 
p_off(1,6); 
_delay_ms(5000); 
p_off(0,6); 
UART_txs("#0&5&5"); 
return vl; 
} 
else if(vl==70) 
{ 
p_home(1); 
_delay_ms(5000); 
p_home(0); 
home(); 
return vl; 
} 
else if(vl==71) 
{ 
p_bkw(1); 
_delay_ms(5000); 
p_bkw(0); 
page=2; 
c_m(); 
return vl; 
} 
else if(vl==73) 
{ 
p_lok(1); 
_delay_ms(5000); 
p_lok(0); 
lok(); 
return vl; 
} 
else return 0; 
} 
else if(page==4)//system menu 
{ 
if(vl==20) 
{ 
p_udx(1,2); 
_delay_ms(5000); 
p_udx(0,2); 
UART_txs("#0&2*"); 
return vl; 
} 
else if(vl==40) 
{ 
p_udx(1,4); 
_delay_ms(5000); 
p_udx(0,4); 
UART_txs("#0&7*"); 
return vl; 
} 
else if(vl==60) 
{ 
p_udx(1,6); 
_delay_ms(5000); 
p_udx(0,6); 
UART_txs("#0&3*"); 
return vl; 
} 
else if(vl==70) 
{ 
p_home(1); 
_delay_ms(5000); 
p_home(0); 
home(); 
return vl; 
} 
else if(vl==73) 
{ 
p_lok(1); 
_delay_ms(5000); 
p_lok(0); 
lok(); 
return vl; 
} 
else return 0; 
} 
else if(page==5)//date time page 
{ 
if(vl==70) 
{ 
p_home(1); 
_delay_ms(5000); 
p_home(0); 
home(); 
return vl; 
} 
else if(vl==73) 
{ 
p_lok(1); 
_delay_ms(5000); 
p_lok(0); 
lok(); 
return vl; 
} 
} 
else if(page==6)//about page 
{ 
if(vl==70) 
{ 
p_home(1); 
_delay_ms(5000); 
p_home(0); 
home(); 
return vl; 
} 
else if(vl==73) 
{ 
p_lok(1); 
_delay_ms(5000); 
p_lok(0); 
lok(); 
return vl; 
} 
else return 0; 
} 
else return 0; 
}  
//=================================================================================== ========================================= 
void c_m() 
{ 
l_clr(); 
if(page==2) 
{ 
put_s("PORCH LIGHT",1,0); 
p_onn(0,1); 
p_off(0,1); 
put_s("POST LAMP",3,0); 
p_onn(0,3); 
p_off(0,3); 
put_s("GARAGE LIGHT",5,0); 
p_onn(0,5); 
p_off(0,5); 
p_fwd(0); 
} 
else if(page==3) 
{ 
put_s("STAIRS LIGHT",2,0); 
p_onn(0,2); 
p_off(0,2); 
put_s("HALL LIGHTS",4,0); 
p_onn(0,4); 
p_off(0,4); 
put_s("WATER PUMP",6,0); 
p_onn(0,6); 
p_off(0,6); 
p_bkw(0); 
} 
p_home(0); 
p_lok(0); 
while(1) 
{ 
while(touch_react()==0); 
} 
} 
//=================================================================================== ========================================= 
void sys_s() 
{ 
l_clr(); 
page=4; 
put_s("ALARM OFF",2,0); 
p_udx(0,2); 
put_s("TEST ALL",4,0); 
p_udx(0,4); 
put_s("SHUTDOWN",6,0); 
p_udx(0,6); 
p_home(0); 
p_lok(0); 
p_bkw(0); 
while(1) 
{ 
while(touch_react()==0); 
} 
}    
//=================================================================================== ========================================= 
void lok() 
{ 
sbi(PORTC,5); 
l_clr(); 
page=0; 
primg(z); 
p_lok(0); 
while(touch_react()==0); 
} 
//=================================================================================== ========================================= 
void home() 
{ 
cbi(PORTC,5); 
page=1; 
l_clr(); 
put_s("CONTROLS",1,0); 
p_udx(0,1); 
put_s("SYSTEM",3,0); 
p_udx(0,3); 
put_s("ABOUT",5,0); 
p_udx(0,5); 
p_lok(0); 
while(touch_react()==0); 
} 
//=================================================================================== ========================================= 
void abt() 
{ 
l_clr(); 
page=6; 
put_s("AUTOMATION SYSTEM",0,5);  
put_s("THIS PROJECT IS MADE",1,0); 
put_s("AT EFY Lab ",2,0); 
put_s("THANK YOU",6,30); 
p_home(0); 
while(touch_react()==0); 
} 
//=================================================================================== ========================================= 
void main() 
{ 
DDRC|=(1<<PC5); 
GLCD_init(); 
UART_init(); 
lok(); 
}
