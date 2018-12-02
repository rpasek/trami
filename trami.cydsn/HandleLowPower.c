/******************************************************************************
* Project Name		: PSoC_4_BLE_CapSense_Slider_LED
* File Name			: HandleLowPower.c
* Version 			: 1.0
* Device Used		: CY8C4247LQI-BL483
* Software Used		: PSoC Creator 4.2
* Compiler    		: ARM GCC 5.4.1
* Related Hardware	: CY8CKIT-042-BLE Bluetooth Low Energy Pioneer Kit 
******************************************************************************
* Copyright (2018), Cypress Semiconductor Corporation. All rights reserved.
*******************************************************************************
* This software, including source code, documentation and related materials
* (“Software”), is owned by Cypress Semiconductor Corporation or one of its
* subsidiaries (“Cypress”) and is protected by and subject to worldwide patent
* protection (United States and foreign), United States copyright laws and
* international treaty provisions. Therefore, you may use this Software only
* as provided in the license agreement accompanying the software package from
* which you obtained this Software (“EULA”).
*
* If no EULA applies, Cypress hereby grants you a personal, nonexclusive,
* non-transferable license to copy, modify, and compile the Software source
* code solely for use in connection with Cypress’s integrated circuit products.
* Any reproduction, modification, translation, compilation, or representation
* of this Software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, 
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED 
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress 
* reserves the right to make changes to the Software without notice. Cypress 
* does not assume any liability arising out of the application or use of the 
* Software or any product or circuit described in the Software. Cypress does 
* not authorize its products for use in any products where a malfunction or 
* failure of the Cypress product may reasonably be expected to result in 
* significant property damage, injury or death (“High Risk Product”). By 
* including Cypress’s product in a High Risk Product, the manufacturer of such 
* system or application assumes all risk of such use and in doing so agrees to 
* indemnify Cypress against all liability.
*******************************************************************************/
#include <main.h>

extern uint8 shut_down_led;
/*******************************************************************************
* Function Name: HandleLowPowerMode
********************************************************************************
* Summary:
*        This function puts the BLESS in deep sleep mode and CPU to sleep mode. 
* System will resume from here when it wakes from user button press.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void HandleLowPowerMode(void)
{
	#ifdef ENABLE_LOW_POWER_MODE
		/* Local variable to store the status of BLESS Hardware block */
		CYBLE_LP_MODE_T sleepMode;
		CYBLE_BLESS_STATE_T blessState;
		
		#ifdef CAPSENSE_ENABLED
		/* Put CapSense to Sleep*/
		CapSense_Sleep();
		#endif
		
		/* Put BLESS into Deep Sleep and check the return status */
		sleepMode = CyBle_EnterLPM(CYBLE_BLESS_DEEPSLEEP);
		
		/* Disable global interrupt to prevent changes from any other interrupt ISR */
		CyGlobalIntDisable;
	
		/* Check the Status of BLESS */
		blessState = CyBle_GetBleSsState();

		if(sleepMode == CYBLE_BLESS_DEEPSLEEP)
		{
		    /* If the ECO has started or the BLESS can go to Deep Sleep, then place CPU 
			* to Deep Sleep */
			if(blessState == CYBLE_BLESS_STATE_ECO_ON || blessState == CYBLE_BLESS_STATE_DEEPSLEEP)
		    {
				if(shut_down_led)
				{
					/* Put PrISM modules to sleep */
					PrISM_1_Sleep();
					PrISM_2_Sleep();
					
					/* Place CPU to Deep sleep only when the RGB PrISM module is not 
					* active (indicated by flag 'shut_down_led'). 
					* If RGB PrISM is active, then the CPU should only be placed in 
					* Sleep to allow the PrISM to function and control the color 
					* and Intensity */
			        CySysPmDeepSleep();
					
					/* After system wakes up, wake up the PrISM modules*/
					PrISM_1_Wakeup();
					PrISM_2_Wakeup();
				}
				else
				{
					/* If the system is controlling RGB LED, then PrISM needs to be running. 
					* Put CPU to sleep only */
					CySysClkWriteImoFreq(IMO_FREQUENCY_3MHZ);
					CySysPmSleep();
					CySysClkWriteImoFreq(IMO_FREQUENCY_12MHZ);

				}
		 	}
		}
		else
		{
		    if(blessState != CYBLE_BLESS_STATE_EVENT_CLOSE)
		    {
				/* If the BLESS hardware block cannot go to Deep Sleep and BLE Event has not 
				* closed yet, then place CPU to Sleep */
		        CySysPmSleep();
		    }
		}
		
		/* Re-enable global interrupt mask after wakeup */
		CyGlobalIntEnable;
		
		#ifdef CAPSENSE_ENABLED
		/* Wakeup CapSense Block */
		CapSense_Wakeup();
		#endif
		
	#endif
}

/*******************************************************************************
* Function Name: MyISR
********************************************************************************
* Summary:
*        ISR routine for isr_button. System enters here after CPU wakeup.
* Clears pending interrupt.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
CY_ISR(MyISR)
{
	/* Clear Pending interrupts */
	isr_button_ClearPending();
	
	User_Button_ClearInterrupt();
}
/* [] END OF FILE */
