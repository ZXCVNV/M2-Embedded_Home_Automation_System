#ifndef TOUCH_H_
#define TOUCH_H_

#define sbi(var, mask)   ((var) |= (uint8_t)(1 << mask))

#define cbi(var, mask)   ((var) &= (uint8_t)~(1 << mask))

uint16_t  l;// xlow register

uint16_t  h;// xhigh register

uint16_t  l1;// ylow register

uint16_t  h1;// yhigh register

uint8_t  vl=0;

void read_x(void)

{

	DDRC = 0b00110010;

	sbi(PORTC, 1);
	cbi(PORTC, 4);	
	_delay_us(100);
	ADMUX = (1 << MUX1);
	ADCSRA = (1 << ADEN)|(1 << ADSC)|(1<<ADPS2)|(1<<ADPS1);
while(ADCSRA & (1 << ADSC));
	l = ADCL;

	h = ADCH & 0x03;
	h = h << 8;

	h = h + l;

}



void read_y(void)
{
	DDRC = 0b00101100;

	sbi(PORTC, 3);
	cbi(PORTC, 2);

	_delay_us(100);
	ADMUX = (1 << MUX2);
	ADCSRA = (1 << ADEN)|(1 << ADSC)|(1<<ADPS2)|(1<<ADPS1);

	while(ADCSRA & (1 << ADSC));
	l1 = ADCL;
	
	h1 = ADCH & 0x03;
	h1 = h1 << 8;

	h1 = h1 + l1;
}

uint8_t butn_no()
{
uint8_t cc=10;
read_x();
read_y();
while(h<80 && h1<10)
{
read_x();
read_y();
_delay_ms(100);
}
while(cc>0)
{
read_x();
read_y();
cc--;
}
if(h>=241 && h<=265 && h1>=88 && h1<=109)
{vl=10;}
else if(h>=221 && h<=251 && h1>=110 && h1<=128)
{vl=20;}
else if(h>=200 && h<=230 && h1>=129 && h1<=140)
{vl=30;}
else if(h>=185 && h<=214 && h1>=140 && h1<=155)
{vl=40;}
else if(h>=165 && h<=188 && h1>=160 && h1<=175)
{vl=50;}
else if(h>=150 && h<=175 && h1>=180 && h1<=195)
{vl=60;}
else if(h>=271 && h<=292 && h1>=78 && h1<=93)
{vl=11;}
else if(h>=260 && h<=281 && h1>=93 && h1<=112)
{vl=21;}
else if(h>=241 && h<=257 && h1>=112 && h1<=130)
{vl=31;}
else if(h>=220 && h<=238 && h1>=130 && h1<=146)
{vl=41;}
else if(h>=196 && h<=220 && h1>=145 && h1<=161)
{vl=51;}
else if(h>=176 && h<=191 && h1>=160 && h1<=175)
{vl=61;}
else if(h>=90 && h<=104 && h1>=265 && h1<=285)
{vl=70;}
else if(h>=94 && h<=119 && h1>=235 && h1<=253)
{vl=71;}
else if(h>=115 && h<=138 && h1>=203 && h1<=220)
{vl=72;}
else if(h>=131 && h<=160 && h1>=184 && h1<=195)
{vl=73;}
else if(h>=318 && h<=340 && h1>=60 && h1<=76)
{vl=04;}
}

#endif
