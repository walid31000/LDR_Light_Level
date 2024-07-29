/*
 * main.c
 *Test LDR Driver :project read light level
 *  Created on: 27 Jul 2024
 *      Author: Walid
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>
#include "Map.h"
#include "Err_Type.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "CLCD_interface.h"

#include "ADC_interface.h"
#include "LED_interface.h"

#include "LDR_interface.h"

extern   uint16 copy_u16Reading;// to save analog value
void main(void)
{
	/*Initilization*/

	PORT_voidIint();
	ADC_voidInit();
	CLCD_voidInit();
	sint8 Local_u8LightLevel;

	LDR_Config_t LDR_OBJECT={ADC0_SINGLE_ENDED,5000};
	Led_config_t LED_RED={DIO_PORTB,DIO_PIN0,ACT_HIGH};

	while(1)
	{

		LDR_GetLightLevel(&LDR_OBJECT,&Local_u8LightLevel);
		// Ensure light level is within the range 1-10
		if (Local_u8LightLevel > 10)
		{
			Local_u8LightLevel = 10;
		}
		else if (Local_u8LightLevel < 1)
		{
			Local_u8LightLevel = 1;
		}

		if(Local_u8LightLevel>5)

		{

			CLCD_u8SendStringAtPos(0,0,"Level=");
			CLCD_voidSendNumber(Local_u8LightLevel);
			CLCD_u8SendString(" Morning");

			CLCD_u8SendStringAtPos(0,1,"Analog=");

			CLCD_voidSendNumber(copy_u16Reading);

			//DIO_u8SetPinValue(DIO_PORTB,DIO_PIN0,DIO_PIN_LOW);
			LED_u8SetOFF(&LED_RED);//Turn Off Red Led
			_delay_ms(200);

		}
		else
		{
			//DIO_u8SetPinValue(DIO_PORTB,DIO_PIN0,DIO_PIN_HIGH);
			LED_u8SetON(&LED_RED);//Turn ON Red Led
			CLCD_u8SendStringAtPos(0,0,"Level=");
			CLCD_voidSendNumber(Local_u8LightLevel);//display light level
			CLCD_u8SendString(" Evening");
			CLCD_u8SendStringAtPos(0,1,"Analog=");

			CLCD_voidSendNumber(copy_u16Reading);//display analog value



			_delay_ms(200);

		}

	}




}
