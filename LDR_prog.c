
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Err_Type.h"
#include "Map.h"
#include "DIO_interface.h"

#include "ADC_interface.h"
#include "ADC_prv.h"
#include "ADC_cfg.h"
#include "LDR_interface.h"

#include "LDR_prv.h"
#include "LDR_cfg.h"








// Define ADC resolution constants
    	#define ADC_RES_EIGHT_BITS   256UL
    	#define ADC_RES_TEN_BITS     1024UL




  uint16 copy_u16Reading;// to save analog value
uint8 LDR_GetLightLevel(LDR_Config_t* copy_LDR_obj,sint8 *Local_u8LightLevel)
{
	  uint8 Local_u8Errorstate=OK;
	  uint16 Local_u16Digital;// to save digital value comming from ADC
	  uint32 ADC_u8RES;    // To save ADC resulution

  if((copy_LDR_obj!=NULL) && (Local_u8LightLevel !=NULL))
  {
	  // Determine the ADC resolution value based on the config file
	         #if ADC_u8RESOLUTION == EIGHT_BITS
	             ADC_u8RES = ADC_RES_EIGHT_BITS;
	         #elif ADC_u8RESOLUTION == TEN_BITS
	             ADC_u8RES = ADC_RES_TEN_BITS;
	         #else
	             // Handle invalid resolution case
	 #error    "ERROR configuration"
	         #endif

	         Local_u16Digital = ADC_u16GetChannelReading(copy_LDR_obj->LDR_CH);

	 /*save the result in Temp_Reading variable using derefrencing */

	         copy_u16Reading = (uint16)(((uint32)Local_u16Digital * copy_LDR_obj->Max_volt) / ADC_u8RES);
    /*second method using Map Library*/
	        // copy_u16Reading =(uint16)Map(0,ADC_u8RES,1000,3571,(sint32)(Local_u16Digital));
	         /*I diveded the light intensity into 10 levels 257mv each */

	         *Local_u8LightLevel=(sint8)(((sint32)copy_u16Reading-1000)/257);


	      //  *Local_u8LightLevel=(uint8)Map(1000,3571,1,10,(sint32)copy_u16Reading);

  }
  else
  {
	  return NULL_PTR;
  }
  return Local_u8Errorstate;

}
