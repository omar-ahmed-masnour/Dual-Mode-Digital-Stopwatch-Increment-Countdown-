#include <avr/io.h>
#include <avr/interrupt.h>
#include<avr/delay.h>
unsigned char PAUSED=0;
unsigned char HOURS=0;
unsigned char MINUTES=0;
unsigned char SECONDS=0;
unsigned char count_down=0;
unsigned char BUZZER=0;
void display_time()
{
	//display seconds
	PORTA &= (~ 0X3F); //disable all segment enables
	PORTC = (PORTC & 0XF0) |(SECONDS % 10); // display smaller seconds segment
	PORTA |= (1<< PA5);// enable the smaller seconds segment
	_delay_us(100);

	PORTA &= (~ 0X3F); //disable all segment enables
	PORTC = (PORTC & 0XF0) |(SECONDS / 10);  // display bigger seconds segment
	PORTA |= (1<< PA4);// enable the bigger seconds segment
	_delay_us(100);

	//DISPLAY MINUTES

	PORTA &= (~ 0X3F); //disable all segment enables
	PORTC = (PORTC & 0XF0) |(MINUTES % 10);  // display bigger 	MINUTES segment
	PORTA |= (1<< PA3);// enable the bigger MINUTES segment
	_delay_us(100);

	PORTA &= (~ 0X3F); //disable all segment enables
	PORTC = (PORTC & 0XF0) |(MINUTES / 10);  // display bigger MINUTES segment
	PORTA |= (1<< PA2);// enable the bigger MINUTES segment
	_delay_us(100);


	//DISPLAY HOURS

	PORTA &= (~ 0X3F); //disable all segment enables
	PORTC = (PORTC & 0XF0) |(HOURS % 10);  // display bigger HOURS segment
	PORTA |= (1<< PA1);// enable the bigger HOURS segment
	_delay_us(100);

	PORTA &= (~ 0X3F); //disable all segment enables
	PORTC = (PORTC & 0XF0) |(HOURS / 10);  // display bigger HOURS segment
	PORTA |= (1<< PA0);// enable the bigger HOURS segment
	_delay_us(100);

}

ISR(TIMER1_COMPA_vect)
{
	if(count_down==0)
	{
		if(PAUSED==0)
		{
			SECONDS ++;
			if(SECONDS==60)
			{
				SECONDS=0;
				MINUTES++;
			}

			if(MINUTES==60)
			{
				MINUTES=0;
				HOURS++;
			}

		}
	}

	else
	{
		if(PAUSED==0)
		{
			if(SECONDS)
			{
				SECONDS--;
			}
			else if(MINUTES)
			{
				MINUTES --;
				SECONDS =59;
			}
			else if(HOURS)
			{
				HOURS--;
				MINUTES =59;
			}
			else if(BUZZER ==1)
			{
				PORTD |= (1<<PD0);
			}

		}
	}


}


void Timer1_Init_CTC_Mode()
{
	TCNT1 = 0;    // Set Timer initial value of 16 bits to 0

	OCR1A  = 15625; // Set Compare Value

	TIMSK |= (1<<OCIE1A); // Enable Timer1A Compare Interrupt
	TCCR1B =  (1<<WGM12) | (1<<CS12) | (1<< CS10);
	TCCR1A = (1<<FOC1A);
	SREG |= (1<<7);
}

ISR(INT0_vect)
{
	HOURS=0;
	MINUTES=0;
	SECONDS=0;
}

void INT0_Iint()
{
	DDRD &= ~(1<<PD2);
	PORTD |= (1<<PD2);
	GICR |= (1<<INT0);
	MCUCR|=(1<<ISC01);
	SREG |= (1<<7);
}

ISR(INT1_vect)
{
	PAUSED=1;
}

void INT1_Init()
{
	DDRD &= ~ (1<<PD3);
	GICR|= (1<<INT1);
	MCUCR |= (1<<ISC11) | (1<<ISC10);
	SREG |= (1<<7);
	GIFR |= (1<<INTF1);
}

ISR(INT2_vect)
{
	PAUSED =0;
}

void INT2_Init()
{
	DDRB &= ~(1<<PB2);
	PORTB |= (1<<PB2);
	GICR |= (1<<INT2);
	MCUCSR|=(1<<ISC2);
	SREG |= (1<<7);
}

int main()
{
	Timer1_Init_CTC_Mode();
	INT0_Iint();
	INT1_Init();
	INT2_Init();
	unsigned char h_inc_pressed=0;
	unsigned char h_dec_pressed=0;
	unsigned char min_inc_pressed=0;
	unsigned char min_dec_pressed=0;
	unsigned char sec_inc_pressed=0;
	unsigned char sec_dec_pressed=0;
	unsigned char toggle_pressed=0;


	DDRC |= 0X0F; // output on the decoder
	DDRA|= 0X3F; // the enables of the segments
	DDRB &= ~((1<<PB0)|(1<<PB1)|(1<<PB3)|(1<<PB4)|(1<<PB5)|(1<<PB6)); // inputs
	PORTB |=  (1<<PB0)|(1<<PB1)|(1<<PB3)|(1<<PB4)|(1<<PB5)|(1<<PB6);  // enable pull-ups
	DDRD |=  (1<<PD0) | (1<<PD4) | (1<<PD5); // 2 LEDs and buzzer as output
	DDRB &= ~(1<<PB7); //toggle button
	PORTB |= (1<<PB7);// internal pull up of said button

	PAUSED=0;


	/************* toggle button conditions ***********************************/

	while(1)
	{
		if( !(PINB & (1<<PB7))  )
		{
			if(toggle_pressed==0)
			{
				toggle_pressed=1;
				if(count_down==0)
				{
					count_down =1;

					if(PAUSED==1)
					{
						BUZZER =1;
					}
				}
				else
				{
					count_down =0;
					PORTD &= ~ (1<<PD0);
					BUZZER=0;
				}
			}
		}

		else
		{
			toggle_pressed=0;
		}



		/********************COUNT DOWN/UP *************************************/



		if(count_down ==0)
		{
			PORTD &=  ~(1<<PD5);
			PORTD|= (1<<PD4);
		}
		else
		{
			PORTD &=  ~(1<<PD4);
			PORTD|= (1<<PD5);
		}

		/***************************************************************************/
		/***************************************************************************/
		/***************************************************************************/
		/***************************************************************************/

		if( !(PINB & (1<<PB1))  )  // if hour increment is pressed
		{
			if(h_inc_pressed==0)
			{
				h_inc_pressed=1;
				HOURS ++;
			}
		}

		else
		{
			h_inc_pressed=0;
		}


		/****************************************************/

		if( !(PINB & (1<<PB0))  )  // if hour decrement is pressed
		{
			if(h_dec_pressed==0)
			{
				h_dec_pressed=1;
				if(HOURS!=0)
				{
					HOURS --;
				}

			}
		}

		else
		{
			h_dec_pressed=0;
		}

		/*****************************************************/

		if( !(PINB & (1<<PB4))  )  // if minutes increment is pressed
		{
			if(min_inc_pressed==0)
			{
				min_inc_pressed=1;
				if(MINUTES < 59)
				{
					MINUTES ++;
				}

			}
		}

		else
		{
			min_inc_pressed=0;
		}

		/****************************************************/

		if( !(PINB & (1<<PB3))  )  // if min decrement is pressed
		{
			if(min_dec_pressed==0)
			{
				min_dec_pressed=1;
				if(MINUTES!=0)
				{
					MINUTES --;
				}

			}
		}

		else
		{
			min_dec_pressed=0;
		}


		/*****************************************************/

		if( !(PINB & (1<<PB6))  )  // if seconds increment is pressed
		{
			if(sec_inc_pressed==0)
			{
				sec_inc_pressed=1;
				if(SECONDS <59 )
				{
					SECONDS ++;
				}

			}
		}

		else
		{
			sec_inc_pressed=0;
		}

		/****************************************************/

		if( !(PINB & (1<<PB5))  )  // if seconds decrement is pressed
		{
			if(sec_dec_pressed==0)
			{
				sec_dec_pressed=1;
				if(SECONDS!=0)
				{
					SECONDS --;
				}

			}
		}

		else
		{
			sec_dec_pressed=0;
		}





		display_time();
	}

}
