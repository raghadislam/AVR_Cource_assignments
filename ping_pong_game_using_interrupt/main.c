/*
 * main.c
 *
 *  Created on: Sep 6, 2023
 *      Author: Raghad Islam
 */

#include "../ATmega32_CTOS/SERVICE/STDTypes.h"
#include "../ATmega32_CTOS/SERVICE/errorState.h"

#include "../ATmega32_CTOS/MCAL/DIO/DIO_int.h"

#include "../ATmega32_CTOS/MCAL/EXTI/EXTI_config.h"
#include "../ATmega32_CTOS/MCAL/EXTI/EXTI_int.h"

#include "../ATmega32_CTOS/MCAL/GIE/GIE_int.h"
#include "../ATmega32_CTOS/MCAL/ADC/ADC_int.h"

#include <util/delay.h>



void INT0_ISR(void);
void INT1_ISR(void);

u8 Global_u8Turn = 1, Global_u8win1=1 , Global_u8win2=1;;

u8 Global_u8Score1 = 0, Global_u8Score2 = 0, Global_u8AnotherRound = 0, Global_u8ShouwScore = 0, Global_u8Choose=0; ;


extern EXTI_t EXTI_AstrEXTIConfig[3];

int main()
{

	u8 Ball[] = {
	  0x00, 0x0E,0x1F,0x1F,0x1F,0x1F,0x0E,0x00
	};

	DIO_enuInit();
	LCD_enuInit();


	EXTI_enuInit(EXTI_AstrEXTIConfig);
	EXIT_enuINT0SetCallBack(&INT0_ISR);
	EXIT_enuINT1SetCallBack(&INT1_ISR);

	GIE_viodEnable();

	LCD_enuCreatChar(Ball,1,0);
	LCD_enuGoto(1,0);
	LCD_enuSendCommand(0x06);


	while(1)
	{

		Global_u8AnotherRound = 0, Global_u8ShouwScore = 0 ,Global_u8Choose=0 ;
		if(Global_u8Turn){
			LCD_enuSendCommand(0x06);

			for(u8 Local_u8Iter=0; Local_u8Iter<16; Local_u8Iter+=3){
				Global_u8win1=1;

				if((Local_u8Iter&1)==0){
					LCD_enuGoto(2,0+Local_u8Iter);
					LCD_enuSendChar(0);
				}
				else{
					LCD_enuGoto(1,0+Local_u8Iter);
					LCD_enuSendChar(0);
				}
				_delay_ms(200);
			}
			if(Global_u8win1){
				LCD_enuClearDisplay();
				LCD_enuDisplayString("Player 1 won !..");
				Global_u8Score1++;
				_delay_ms(500);
				LCD_enuClearDisplay();
				LCD_enuDisplayString("show score   or ");
				LCD_enuGoto(2,3);
				LCD_enuDisplayString("another round");
				Global_u8Choose=1;
				while(Global_u8AnotherRound == 0 && Global_u8ShouwScore == 0 );
				if(Global_u8ShouwScore)
				{
					LCD_enuClearDisplay();
					LCD_enuDisplayString("     ");
					LCD_enuWriteNumber(Global_u8Score1);
					LCD_enuDisplayString("  -  ");
					LCD_enuWriteNumber(Global_u8Score2);
					LCD_enuGoto(2,0);

					if(Global_u8Score1>Global_u8Score2)
					{
						LCD_enuDisplayString("Congrats player1! ");
					}
					else if(Global_u8Score1<Global_u8Score2) {
						LCD_enuDisplayString("Congrats player1! ");
					}
					else {
						LCD_enuDisplayString("  It's a tie ! ");
					}
					while(1);

				}
				Global_u8AnotherRound = 0, Global_u8ShouwScore = 0 ;
			}
			else Global_u8win1 = 1;
		}
		else
		{
			LCD_enuSendCommand(0x04);

			for(int Local_u8Iter=0; Local_u8Iter<16; Local_u8Iter+=3)
			{
				Global_u8win2=1;


				if((Local_u8Iter&1)==0){
					LCD_enuGoto(2,15-Local_u8Iter);
					LCD_enuSendChar(0);

				}
				else{
					LCD_enuGoto(1,15-Local_u8Iter);
					LCD_enuSendChar(0);

				}
				_delay_ms(200);

			}

			if(Global_u8win2){
				LCD_enuClearDisplay();
				LCD_enuSendCommand(0x06);
				LCD_enuDisplayString("Player 2 won !..");
				Global_u8Score2++;
				_delay_ms(500);
				LCD_enuClearDisplay();
				LCD_enuDisplayString("show score   or ");
				LCD_enuGoto(2,3);
				LCD_enuDisplayString("another round");
				Global_u8Choose=1;
				while(Global_u8AnotherRound == 0 && Global_u8ShouwScore == 0 );
				if(Global_u8ShouwScore)
				{
					LCD_enuClearDisplay();
					LCD_enuDisplayString("     ");
					LCD_enuWriteNumber(Global_u8Score1);
					LCD_enuDisplayString("  -  ");
					LCD_enuWriteNumber(Global_u8Score2);
					LCD_enuGoto(2,0);
					if(Global_u8Score1>Global_u8Score2)
					{
						LCD_enuDisplayString("Congrats player2! ");
					}
					else if(Global_u8Score1<Global_u8Score2) {
						LCD_enuDisplayString("Congrats player2! ");
					}
					else {
						LCD_enuDisplayString("  It's a tie !");
					}

					while(1);

				}
				Global_u8AnotherRound = 0, Global_u8ShouwScore = 0 ;

			}
			else Global_u8win2 =1;
		}

		Global_u8Turn = !Global_u8Turn;
		LCD_enuClearDisplay();

	}
	return 0;
}

void INT0_ISR(void)
{
	if(Global_u8Choose)
	{
		Global_u8AnotherRound =1;
	}
	Global_u8win1=0;
}

void INT1_ISR(void)
{
	if(Global_u8Choose)
	{
		Global_u8ShouwScore =1;
	}
	Global_u8win2=0;
}

