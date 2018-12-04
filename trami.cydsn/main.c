/******************************************************************************
* Project Name		: PSoC_4_BLE_CapSense_Slider_LED
* File Name			: main.c
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

/******************************************************************************
*                           THEORY OF OPERATION
*******************************************************************************
* This project will showcase the capability of PSoC 4 BLE to communicate 
* bi-directionally with a BLE Central device over custom services. The CapSense 
* custom service allows notifications to be sent to the central device when 
* notifications are enabled. On the other hand, the RGB LED custom service allows 
* read and write of attributes under the RGB characteristics.
* This project utilizes CapSense component to check finger position on slider 
* and report this to the central device over BLE. On the other hand, the control  
* values sent to PSoC 4 BLE are converted to respective color and intensity on the   
* onboard RGB LED. The BLE central device can be any BLE central device, including  
* CySmart mobile app or CySmart PC tool. 
* This project also includes low power mode operation, ideal for battery operated 
* devices. The project utilizes Deep Sleep feature of both BLESS and CPU to remain 
* in low power mode as much as possible, while maintaining the BLE connection and  
* data transfer. This allows the device to run on coin cell battery for long time.
*
* Note:
* The programming pins have been configured as GPIO, and not SWD. This is because 
* the silicon consumes extra power through the pins when the programming pins are  
* configured for SWD. To prevent the leakage of power, the pins have been set 
* to GPIO. With this setting, the kit can still be acquired by PSoC Creator or
* PSoC Programmer software tools for programming, but the project cannot be 
* externally debugged. To re-enable debugging, go to PSoC_4_BLE_CapSense_Slider_LED.cydwr 
* from Workspace Explorer, go to Systems tab, and set the Debug Select option to 'SWD'.
* Build and program this project to enable external Debugging.
*
* Refer to CY8CKIT-042-BLE Pioneer Kit guide for details.
*******************************************************************************
* Hardware connection required for testing -
* Slider pins 	- P2[1]-P2[5] (hard-wired on the BLE Pioneer kit)
* Cmod pin		- P4[0] (hard-wired on the PSoC 4 BLE module)
* R-G-B LED 	- P2[6], P3[6] and P3[7] (hard-wired on the BLE Pioneer kit)
* User Switch	- P2[7] (hard-wired on the BLE Pioneer kit)
******************************************************************************/
#include <project.h>
#include <interface.h>
#include <main.h>


/* Global variables */
/* Global variables used because this is the method uProbe uses to access firmware data */
/* CapSense tuning variables */
uint8 modDac = SENSOR_MODDAC;               /* Modulation DAC current setting */
uint8 compDac[NUMSENSORS] = {SENSOR_CMPDAC, SENSOR_CMPDAC, SENSOR_CMPDAC, SENSOR_CMPDAC, SENSOR_CMPDAC, SENSOR_CMPDAC, SENSOR_CMPDAC, SENSOR_CMPDAC, SENSOR_CMPDAC, SENSOR_CMPDAC, SENSOR_CMPDAC, SENSOR_CMPDAC}; /* Compensation DAC current setting */
uint8 senseDivider = SENSOR_SENDIV;         /* Sensor clock divider */
uint8 modDivider = SENSOR_MODDIV;           /* Modulation clock divider */
/* Liquid Level variables */
int32 sensorRaw[NUMSENSORS] = {0u};         /* Sensor raw counts */
int32 sensorDiff[NUMSENSORS] = {0u};        /* Sensor difference counts */
int16 sensorEmptyOffset[NUMSENSORS] = {0u}; /* Sensor counts when empty to calculate diff counts. Loaded from EEPROM array */
const int16 CYCODE eepromEmptyOffset[] = {0u};/* Sensor counts when empty to calculate diff counts. Loaded from EEPROM array */
int16 sensorScale[NUMSENSORS] = {0x01D0, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x01C0}; /* Scaling factor to normalize sensor full scale counts. 0x0100 = 1.0 in fixed precision 8.8 */
int32 sensorProcessed[NUMSENSORS] = {0u, 0u}; /* fixed precision 24.8 */
uint16 sensorLimit = SENSORLIMIT;           /* Threshold for determining if a sensor is submerged. Set to half of SENSORMAX value */
uint8 sensorActiveCount = 0u;               /* Number of sensors currently submerged */
int32 levelPercent = 0u;                    /* fixed precision 24.8 */
int32 levelMm = 0u;                         /* fixed precision 24.8 */   
int32 sensorHeight = SENSORHEIGHT;          /* Height of a single sensor. Fixed precision 24.8 */
uint8 calFlag = FALSE;                      /* Flag to signal when new sensor calibration values should be stored to EEPROM */
/* Communication variables */
uint16 delayMs = UART_DELAY;                /* Main loop delay in ms to control UART data log output speed */


/* This flag is used by application to know whether a Central 
* device has been connected. This is updated in BLE event callback 
* function*/
extern uint8 deviceConnected;

/*This flag is set when the Central device writes to CCCD of the 
* CapSense slider Characteristic to enable notifications */
extern uint8 sendCapSenseSliderNotifications;

/* 'restartAdvertisement' flag is used to restart advertisement */
extern uint8 restartAdvertisement;

/* 'initializeCapSenseBaseline' flag is used to call the function that initializes 
* all CapSense baselines, once. The baseline is initialized when the first advertisement 
* is started. This is done so that any external disturbance while powering the kit does 
* not influence the baseline value, that may cause wrong readings. */
uint8 initializeCapSenseBaseline = TRUE;

/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
*        System entrance point. This calls the initializing function and
* continuously processes BLE and CapSense events.
*
* Parameters:
*  void
*
* Return:
*  int
*

*******************************************************************************/
int main()
{
    uint8 i;
    
	/* This function will initialize the system resources such as BLE and CapSense */
    InitializeSystem();
	
    for(;;)
    {
	/* Check for CapSense scan complete*/
        if(CapSense_CSD_IsBusy() == FALSE)
        {
            /* Delay to control data logging rate */
            CyDelay(delayMs);
            
            /* Read and store new sensor raw counts*/
            for(i = 0; i < NUMSENSORS; i++)
            {
                sensorRaw[i] = CapSense_CSD_ReadSensorRaw(i);
                sensorDiff[i] = sensorRaw[i];
            }

            /* Start scan for next iteration */
            CapSense_CSD_ScanEnabledWidgets();
            
            /* Check if we should store new empty offset calibration values */
            if(calFlag == TRUE)
            {
                calFlag = FALSE;
                StoreCalibration();
            }
            
            /* Remove empty offset calibration from sensor raw counts and normalize sensor full count values */
            for(i = 0; i < NUMSENSORS; i++)
            {
                sensorDiff[i] -= sensorEmptyOffset[i];
                sensorProcessed[i] = (sensorDiff[i] * sensorScale[i]) >> 8;
            }
                      
            /* Find the number of submerged sensors */
            sensorActiveCount = 0;
            for(i = 0; i < NUMSENSORS; i++)
            {
                if(sensorProcessed[i] > sensorLimit)
                {
                    /* First and last sensor are half the height of middle sensors */
                    if((i == 0) || (i == NUMSENSORS - 1))
                    {
                        sensorActiveCount += 1;
                    }
                    /* Middle sensors are twice the height of 1st and last sensors */
                    else
                    {
                        sensorActiveCount += 2;
                    }
                }
            }
            
            /* Calculate liquid level height in mm */
            levelMm = sensorActiveCount * (sensorHeight >> 1);
            /* If level is near full value then round to full. Avoids fixed precision rounding errors */
            if(levelMm > ((int32)LEVELMM_MAX << 8) - (sensorHeight >> 2))
            {
                levelMm = LEVELMM_MAX << 8;
            }

            /* Calculate level percent. Stored in fixed precision 24.8 format to hold fractional percent */
            levelPercent = (levelMm * 100) / LEVELMM_MAX;
            
            /* Report level and process uProbe and UART interfaces */
            ProcessUprobe();
            ProcessUart();
        }
        

        /*Process event callback to handle BLE events. The events generated and 
		* used for this application are inside the 'CustomEventHandler' routine*/
        CyBle_ProcessEvents();
		
		/* Updated LED for status during BLE active states */
		HandleStatusLED();
		
		if(TRUE == deviceConnected)
		{
			/* After the connection, send new connection parameter to the Client device 
			* to run the BLE communication on desired interval. This affects the data rate 
			* and power consumption. High connection interval will have lower data rate but 
			* lower power consumption. Low connection interval will have higher data rate at
			* expense of higher power. This function is called only once per connection. */
			UpdateConnectionParam();
			
			/* Send CapSense Slider data when respective notification is enabled */
			if(sendCapSenseSliderNotifications == CCCD_NTF_BIT_MASK)
			{
				#ifdef ENABLE_LOW_POWER_MODE
                if(CYBLE_BLESS_STATE_ECO_STABLE == CyBle_GetBleSsState())
                #endif
				{
					/* Check for CapSense slider swipe and send data accordingly */
					HandleCapSenseSlider();
				}
			}
		}
		
		#ifdef ENABLE_LOW_POWER_MODE
			/* Put system to Deep sleep, including BLESS, and wakeup on interrupt. 
			* The source of the interrupt can either be BLESS Link Layer in case of 
			* BLE advertisement and connection or by User Button press during BLE 
			* disconnection */
			HandleLowPowerMode();
		#endif
		
		if(restartAdvertisement)
		{
			/* Reset 'restartAdvertisement' flag*/
			restartAdvertisement = FALSE;
			
			/* If CapSense Initialize Baseline API has not been called yet, call the
			* API and reset the flag. */
			if(initializeCapSenseBaseline)
			{
				/* Reset 'initializeCapSenseBaseline' flag*/
				initializeCapSenseBaseline = FALSE;
				
				/* Initialize all CapSense Baselines */
				// CapSense_InitializeAllBaselines();
			}

			/* Start Advertisement and enter Discoverable mode*/
			CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);	
		}
    }	/* End of for(;;) */
}

/*******************************************************************************
* Function Name: InitializeSystem
********************************************************************************
* Summary:
*        Start the components and initialize system 
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void InitializeSystem(void)
{
	uint8 i;

	/* Enable global interrupt mask */
	CyGlobalIntEnable; 
			
	/* Start BLE component and register the CustomEventHandler function. This 
	* function exposes the events from BLE component for application use */
    CyBle_Start(CustomEventHandler);
	
	/* Start the PrISM component for LED control*/
    PrISM_1_Start();
    PrISM_2_Start();
	
	/* The RGB LED on BLE Pioneer kit is active low. Drive HIGH on 
		pins for OFF and drive LOW on pins for ON*/
	PrISM_1_WritePulse0(RGB_LED_OFF);
	PrISM_1_WritePulse1(RGB_LED_OFF);
	PrISM_2_WritePulse0(RGB_LED_OFF);
	
	/* Set Drive mode of output pins from HiZ to Strong */
	RED_SetDriveMode(RED_DM_STRONG);
	GREEN_SetDriveMode(GREEN_DM_STRONG);
	BLUE_SetDriveMode(BLUE_DM_STRONG);
	
	/* Start the Button ISR to allow wakeup from sleep */
	isr_button_StartEx(MyISR);
	 
    /* Read stored empty offset values from EEPROM */
    for(i = 0; i < NUMSENSORS; i++)
    {
        sensorEmptyOffset[i] = eepromEmptyOffset[i];
    }
    
    /* Start CapSense and UART components */
    CapSense_CSD_Start();	
    CapSense_CSD_ScanEnabledWidgets();
    UART_Start();  
    InitialUartMessage();
	
	/* Set the Watchdog Interrupt vector to the address of Interrupt routine 
	* WDT_INT_Handler. This routine counts the 3 seconds for LED ON state during
	* connection. */
	CyIntSetVector(WATCHDOG_INT_VEC_NUM, &WDT_INT_Handler);

}

/*******************************************************************************
* Function Name: HandleCapSenseSlider
********************************************************************************
* Summary:
*        This function scans for finger position on CapSense slider, and if the  
* position is different, triggers separate routine for BLE notification
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void HandleCapSenseSlider(void)
{
	#ifdef CAPSENSE_ENABLED
	/* Last read CapSense slider position value */
	static uint16 lastPosition;	

	/* Present slider position read by CapSense */
	uint16 sliderPosition;
	
	/* Read the finger position on the slider */
	sliderPosition = levelPercent / 100;

	/* If finger position on the slider is changed then send data as BLE notifications */
	if(sliderPosition != lastPosition)
	{
		/*If finger is detected on the slider*/
		if((sliderPosition == NO_FINGER) || (sliderPosition <= SLIDER_MAX_VALUE))
		{
			/* Send data over Slider Notification */
			SendDataOverCapSenseNotification((uint8)sliderPosition);

		}	/* if(sliderPosition != NO_FINGER) */
		
		/* Update local static variable with present finger position on slider*/
		lastPosition = sliderPosition;
		
	}	/* if(sliderPosition != lastPosition) */
	#endif
}
/* [] END OF FILE */
