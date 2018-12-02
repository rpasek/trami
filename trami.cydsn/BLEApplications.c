/******************************************************************************
* Project Name		: PSoC_4_BLE_CapSense_Slider_LED
* File Name			: BLEApplications.c
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

/**************************Variable Declarations*****************************/
/* 'connectionHandle' stores connection parameters */
CYBLE_CONN_HANDLE_T  connectionHandle;

/* 'rgbHandle' stores RGB control data parameters */
CYBLE_GATT_HANDLE_VALUE_PAIR_T		rgbHandle;	

/*This flag is set when the Central device writes to CCCD (Client Characteristic 
* Configuration Descriptor) of the CapSense slider Characteristic to enable 
* notifications */
uint8 sendCapSenseSliderNotifications = FALSE;	

/*This flag is set when the Central device writes to CCCD of the 
* RGB LED Characteristic to enable notifications */
uint8 rgbledNotifications = FALSE;

/* Array to store the present RGB LED control data. The 4 bytes 
* of the array represent {R,G,B,Intensity} */
uint8 RGBledData[RGB_CHAR_DATA_LEN];

/* This flag is used by application to know whether a Central 
* device has been connected. This is updated in BLE event callback 
* function*/
uint8 deviceConnected = FALSE;

/* 'restartAdvertisement' flag provides the present state of power mode in firmware */
uint8 restartAdvertisement = FALSE;

/*'enableCapSenseData' flag is set after the Connection LED off status is received.
  This flag ensures that the CapSense related scanning does not increase the loop 
  time of firmware, causing the LED to be always ON.*/
uint8 enableCapSenseData = FALSE;	

/* This flag is used to let application send a L2CAP connection update request
* to Central device */
static uint8 isConnectionUpdateRequested = TRUE;

/* Connection Parameter update values. These values are used by the BLE component
* to update the connection parameters, including connection interval, to desired 
* value */
static CYBLE_GAP_CONN_UPDATE_PARAM_T ConnectionParam =
{
    CONN_PARAM_UPDATE_MIN_CONN_INTERVAL,  		      
    CONN_PARAM_UPDATE_MAX_CONN_INTERVAL,		       
    CONN_PARAM_UPDATE_SLAVE_LATENCY,			    
    CONN_PARAM_UPDATE_SUPRV_TIMEOUT 			         	
};

/* This flag is used to switch between CPU Deep Sleep and Sleep, depending on
* the status of RGB LED color values received. This method allows to conserve 
* more power during LED usage */
uint8 shut_down_led = TRUE;

/* Counter to keep the LED ON for a selected period before shutting the LEDs down */
uint8 led_timer = FALSE;

/* Counter to allow an initial 3 second Status LED ON for indicating connection */
uint8 timer_tick = FALSE;

/* Flag to switch off the LED after connection */
uint8 switch_off_status_led = FALSE;

/* Status flag for the Stack Busy state. This flag is used to notify the application 
* whether there is stack buffer free to push more data or not */
uint8 busyStatus = 0;

/* Local variable to store the current CCCD value */
uint8 CapSenseCCCDvalue[2];
uint8 RGBCCCDvalue[2];

/* Handle value to update the CCCD */
CYBLE_GATT_HANDLE_VALUE_PAIR_T CapSenseNotificationCCCDhandle;

/* Handle value to update the CCCD */
CYBLE_GATT_HANDLE_VALUE_PAIR_T RGBNotificationCCCDhandle;


/****************************************************************************/

/*******************************************************************************
* Function Name: CustomEventHandler
********************************************************************************
* Summary:
*        Call back event function to handle various events from BLE stack
*
* Parameters:
*  uint32 event:		event returned
*  void * eventParam:	link to value of the events returned
*
* Return:
*  void
*
*******************************************************************************/
void CustomEventHandler(uint32 event, void * eventParam)
{
	/* Local variable to store the data received as part of the Write request 
	* events */
	CYBLE_GATTS_WRITE_REQ_PARAM_T *wrReqParam;

    switch(event)
    {
        case CYBLE_EVT_STACK_ON:
			/* This event is received when component is Started */
			
			/* Set restartAdvertisement flag to allow calling Advertisement 
			* API from main function */
			restartAdvertisement = TRUE;
			
			break;
			
		case CYBLE_EVT_TIMEOUT:
			/* Event Handling for Timeout  */
	
			break;
        
		/**********************************************************
        *                       GAP Events
        ***********************************************************/
		case CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
			
			/* If the current BLE state is Disconnected, then the Advertisement
			* Start Stop event implies that advertisement has stopped */
			if(CyBle_GetState() == CYBLE_STATE_DISCONNECTED)
			{
				/* Set restartAdvertisement flag to allow calling Advertisement 
				* API from main function */
				restartAdvertisement = TRUE;
			}
			break;
			
		case CYBLE_EVT_GAP_DEVICE_CONNECTED: 					
			/* This event is received when device is connected over GAP layer */
			break;

			
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
			/* This event is received when device is disconnected */
			
			/* Set restartAdvertisement flag to allow calling Advertisement 
			* API from main function */
			restartAdvertisement = TRUE;
			
			/* Set flag to allow system to go to Deep Sleep */
			shut_down_led = TRUE;
			break;
        
		/**********************************************************
        *                       GATT Events
        ***********************************************************/
        case CYBLE_EVT_GATT_CONNECT_IND:
			/* This event is received when device is connected over GATT level */
			
			/* Update attribute handle on GATT Connection*/
            connectionHandle = *(CYBLE_CONN_HANDLE_T  *)eventParam;
			
			/* This flag is used in application to check connection status */
			deviceConnected = TRUE;
			break;
        
        case CYBLE_EVT_GATT_DISCONNECT_IND:
			/* This event is received when device is disconnected */
			
			/* Update deviceConnected flag*/
			deviceConnected = FALSE;
			
			/* Reset CapSense notification flag to prevent further notifications
			 * being sent to Central device after next connection. */
			sendCapSenseSliderNotifications = FALSE;
			
			/* Reset RGB notification flag to prevent further notifications
			 * being sent to Central device after next connection. */
			rgbledNotifications = FALSE;
			
			/* Reset the CCCD value to disable notifications */
    		/* Write the present CapSense notification status to the local variable */
    		CapSenseCCCDvalue[0] = sendCapSenseSliderNotifications;
    		CapSenseCCCDvalue[1] = 0x00;
    		
    		/* Update CCCD handle with notification status data*/
    		CapSenseNotificationCCCDhandle.attrHandle = CYBLE_CAPSENSE_CAPSENSE_SLIDER_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE;
    		CapSenseNotificationCCCDhandle.value.val = CapSenseCCCDvalue;
    		CapSenseNotificationCCCDhandle.value.len = CCCD_DATA_LEN;
    		
    		/* Report data to BLE component for sending data when read by Central device */
    		CyBle_GattsWriteAttributeValue(&CapSenseNotificationCCCDhandle, ZERO, &connectionHandle, CYBLE_GATT_DB_PEER_INITIATED);
		
    		/* Write the present RGB notification status to the local variable */
    		RGBCCCDvalue[0] = rgbledNotifications;
    		RGBCCCDvalue[1] = 0x00;
    		
    		/* Update CCCD handle with notification status data*/
    		RGBNotificationCCCDhandle.attrHandle = CYBLE_RGB_LED_RGB_LED_CONTROL_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE;
    		RGBNotificationCCCDhandle.value.val = RGBCCCDvalue;
    		RGBNotificationCCCDhandle.value.len = CCCD_DATA_LEN;
    		
    		/* Report data to BLE component for sending data when read by Central device */
    		CyBle_GattsWriteAttributeValue(&RGBNotificationCCCDhandle, ZERO, &connectionHandle, CYBLE_GATT_DB_PEER_INITIATED);
			
			/* Reset the color coordinates */
			RGBledData[RED_INDEX] = ZERO;
            RGBledData[GREEN_INDEX] = ZERO;
            RGBledData[BLUE_INDEX] = ZERO;
            RGBledData[INTENSITY_INDEX] = ZERO;
			UpdateRGBled();

			/* Reset the isConnectionUpdateRequested flag to allow sending
			* connection parameter update request in next connection */
			isConnectionUpdateRequested = TRUE;
			
			/* Set the flag to allow system to go to Deep Sleep */
			shut_down_led = TRUE;
			
			break;
            
        case CYBLE_EVT_GATTS_WRITE_REQ:
			/* This event is received when Central device sends a Write command on an Attribute */
            wrReqParam = (CYBLE_GATTS_WRITE_REQ_PARAM_T *) eventParam;
            
			/* When this event is triggered, the peripheral has received a write command on the custom characteristic */
			/* Check if command is for correct attribute and update the flag for sending Notifications */
            if(CYBLE_CAPSENSE_CAPSENSE_SLIDER_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE == wrReqParam->handleValPair.attrHandle)
			{
				/* Extract the Write value sent by the Client for CapSense Slider CCCD */
                if(wrReqParam->handleValPair.value.val[CYBLE_CAPSENSE_CAPSENSE_SLIDER_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_INDEX] == TRUE)
                {
                    sendCapSenseSliderNotifications = TRUE;
                }
                else if(wrReqParam->handleValPair.value.val[CYBLE_CAPSENSE_CAPSENSE_SLIDER_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_INDEX] == FALSE)
                {
                    sendCapSenseSliderNotifications = FALSE;
                }
				
        		/* Write the present CapSense notification status to the local variable */
        		CapSenseCCCDvalue[0] = sendCapSenseSliderNotifications;
        		CapSenseCCCDvalue[1] = 0x00;
        		
        		/* Update CCCD handle with notification status data*/
        		CapSenseNotificationCCCDhandle.attrHandle = CYBLE_CAPSENSE_CAPSENSE_SLIDER_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE;
        		CapSenseNotificationCCCDhandle.value.val = CapSenseCCCDvalue;
        		CapSenseNotificationCCCDhandle.value.len = CCCD_DATA_LEN;
        		
        		/* Report data to BLE component for sending data when read by Central device */
        		CyBle_GattsWriteAttributeValue(&CapSenseNotificationCCCDhandle, ZERO, &connectionHandle, CYBLE_GATT_DB_PEER_INITIATED);
            }
			
			if(CYBLE_RGB_LED_RGB_LED_CONTROL_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE == wrReqParam->handleValPair.attrHandle)
            {
				/* Extract the Write value sent by the Client for RGB LED CCCD */
                if(wrReqParam->handleValPair.value.val[CYBLE_RGB_LED_RGB_LED_CONTROL_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_INDEX] == TRUE)
                {
                    rgbledNotifications = TRUE;
                }
                else if(wrReqParam->handleValPair.value.val[CYBLE_RGB_LED_RGB_LED_CONTROL_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_INDEX] == FALSE)
                {
                    rgbledNotifications = FALSE;
                }
				
        		/* Write the present RGB notification status to the local variable */
        		RGBCCCDvalue[0] = rgbledNotifications;
        		RGBCCCDvalue[1] = 0x00;
        		
        		/* Update CCCD handle with notification status data*/
        		RGBNotificationCCCDhandle.attrHandle = CYBLE_RGB_LED_RGB_LED_CONTROL_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE;
        		RGBNotificationCCCDhandle.value.val = RGBCCCDvalue;
        		RGBNotificationCCCDhandle.value.len = CCCD_DATA_LEN;
        		
        		/* Report data to BLE component for sending data when read by Central device */
        		CyBle_GattsWriteAttributeValue(&RGBNotificationCCCDhandle, ZERO, &connectionHandle, CYBLE_GATT_DB_PEER_INITIATED);
				
				/* Update the RGB LED Notification attribute with new color coordinates */
				SendDataOverRGBledNotification(RGBledData, RGB_CHAR_DATA_LEN);
            }
			
			/* Check if the returned handle is matching to RGB LED Control Write Attribute and extract the RGB data*/
            if(CYBLE_RGB_LED_RGB_LED_CONTROL_CHAR_HANDLE == wrReqParam->handleValPair.attrHandle)
            {
				/* Extract the Write value sent by the Client for RGB LED Color characteristic */
                RGBledData[RED_INDEX] = wrReqParam->handleValPair.value.val[RED_INDEX];
                RGBledData[GREEN_INDEX] = wrReqParam->handleValPair.value.val[GREEN_INDEX];
                RGBledData[BLUE_INDEX] = wrReqParam->handleValPair.value.val[BLUE_INDEX];
                RGBledData[INTENSITY_INDEX] = wrReqParam->handleValPair.value.val[INTENSITY_INDEX];
                
				/* Update the PrISM components and the attribute for RGB LED read characteristics*/
                UpdateRGBled();
            }
			
			/* Send the response to the write request received. */
			CyBle_GattsWriteRsp(connectionHandle);
			
			break;
			
		case CYBLE_EVT_L2CAP_CONN_PARAM_UPDATE_RSP:
				/* If L2CAP connection parameter update response received, reset application flag */
            	isConnectionUpdateRequested = FALSE;
            break;
			
		case CYBLE_EVT_STACK_BUSY_STATUS:
			/* This event is generated when the internal stack buffer is full and no more
			* data can be accepted or the stack has buffer available and can accept data.
			* This event is used by application to prevent pushing lot of data to stack. */
			
			/* Extract the present stack status */
            busyStatus = * (uint8*)eventParam;
            break;
			
        default:

       	 	break;
    }   	/* switch(event) */
}

/*******************************************************************************
* Function Name: SendDataOverCapSenseNotification
********************************************************************************
* Summary:
*        Send CapSense Slider data as BLE Notifications. This function updates
* the notification handle with data and triggers the BLE component to send 
* notification
*
* Parameters:
*  uint8 CapSenseSliderData:	CapSense slider value	
*
* Return:
*  void
*
*******************************************************************************/
void SendDataOverCapSenseNotification(uint8 CapSenseSliderData)
{
	/* 'CapSensenotificationHandle' stores CapSense notification data parameters */
	CYBLE_GATTS_HANDLE_VALUE_NTF_T		CapSensenotificationHandle;	
	
	/* If stack is not busy, then send the notification */
	if(busyStatus == CYBLE_STACK_STATE_FREE)
	{
		/* Update notification handle with CapSense slider data*/
		CapSensenotificationHandle.attrHandle = CYBLE_CAPSENSE_CAPSENSE_SLIDER_CHAR_HANDLE;				
		CapSensenotificationHandle.value.val = &CapSenseSliderData;
		CapSensenotificationHandle.value.len = CAPSENSE_SLIDER_NTF_DATA_LEN;
		
		/* Send the updated handle as part of attribute for notifications */
		CyBle_GattsNotification(connectionHandle,&CapSensenotificationHandle);
	}
}

/*******************************************************************************
* Function Name: SendDataOverRGBledNotification
********************************************************************************
* Summary:
*        Send RGB LED data as BLE Notifications. This function updates
* the notification handle with data and triggers the BLE component to send 
* notification
*
* Parameters:
*  uint8 *rgbLedData:	pointer to an array containing RGB color and Intensity values
*  uint8 len: length of the array
*
* Return:
*  void
*
*******************************************************************************/
void SendDataOverRGBledNotification(uint8 *rgbLedData, uint8 len)
{
	/* 'rgbLednotificationHandle' stores RGB LED notification data parameters */
	CYBLE_GATTS_HANDLE_VALUE_NTF_T 	rgbLednotificationHandle;
	
	/* If stack is not busy, then send the notification */
	if(busyStatus == CYBLE_STACK_STATE_FREE)
	{
		/* Update notification handle with CapSense slider data*/
		rgbLednotificationHandle.attrHandle = CYBLE_RGB_LED_RGB_LED_CONTROL_CHAR_HANDLE;				
		rgbLednotificationHandle.value.val = rgbLedData;
		rgbLednotificationHandle.value.len = len;
		
		/* Send the updated handle as part of attribute for notifications */
		CyBle_GattsNotification(connectionHandle,&rgbLednotificationHandle);
	}
}

/*******************************************************************************
* Function Name: UpdateConnectionParam
********************************************************************************
* Summary:
*        Send the Connection Update Request to Client device after connection 
* and modify the connection interval for low power operation.
*
* Parameters:
*	void
*
* Return:
*  void
*
*******************************************************************************/
void UpdateConnectionParam(void)
{
	/* If device is connected and Update connection parameter not updated yet,
	* then send the Connection Parameter Update request to Client. */
    if(deviceConnected && isConnectionUpdateRequested)
	{
		/* Reset the flag to indicate that connection Update request has been sent */
		isConnectionUpdateRequested = FALSE;
		
		/* Send Connection Update request with set Parameter */
		CyBle_L2capLeConnectionParamUpdateRequest(connectionHandle.bdHandle, &ConnectionParam);
	}
}

/*******************************************************************************
* Function Name: UpdateRGBled
********************************************************************************
* Summary:
*        Receive the new RGB data and modify PrISM parameters. Also, update the
* read characteristic handle so that the next read from the BLE central device
* gives present RGB color and intensity data.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void UpdateRGBled(void)
{
	/* Local variables to calculate the color components from RGB received data*/
	uint8 debug_red;
	uint8 debug_green;
	uint8 debug_blue;
	uint8 intensity_divide_value = RGBledData[INTENSITY_INDEX];
	
	/* Calculate the intensity of the Red, Green and Blue components from the
	* received 4-byte data */
	debug_red = (uint8)(((uint16)RGBledData[RED_INDEX]*intensity_divide_value)/255);
	debug_green = (uint8)(((uint16)RGBledData[GREEN_INDEX]*intensity_divide_value)/255);
	debug_blue = (uint8)(((uint16)RGBledData[BLUE_INDEX]*intensity_divide_value)/255);
	
	/*If the Intensity value sent by client is below a set threshold, assume no intensity
	* and switch off the RGB colors on LED. Also, set the appropriate flag to allow the system 
	* to go to Deep Sleep */
	if(RGBledData[INTENSITY_INDEX] < LED_NO_COLOR_THRESHOLD)
	{
		/* Set the flag to allow the system to go to Deep Sleep */
		shut_down_led = TRUE;
		
		/* Set the RGB LED pin drive mode to HiZ to prevent leakage of current */
		RED_SetDriveMode(RED_DM_ALG_HIZ);
		GREEN_SetDriveMode(GREEN_DM_ALG_HIZ);
		BLUE_SetDriveMode(BLUE_DM_ALG_HIZ);
	}
	else
	{
		/* If the individual color value of Red, Green and Blue component is less than
		*  set threshold, then assume no color and shut down the LEDs. Also,set the 
		* appropriate flag to allow system to go to Deep Sleep */
		if((debug_red < LED_NO_COLOR_THRESHOLD) && \
			(debug_green < LED_NO_COLOR_THRESHOLD) && \
			(debug_blue < LED_NO_COLOR_THRESHOLD))
		{
			/* Set the flag to allow the system to go to Deep Sleep */
			shut_down_led = TRUE;
			
			/* Set the RGB LED pin drive mode to HiZ to prevent leakage of current */
			RED_SetDriveMode(RED_DM_ALG_HIZ);
			GREEN_SetDriveMode(GREEN_DM_ALG_HIZ);
			BLUE_SetDriveMode(BLUE_DM_ALG_HIZ);
		}
		else
		{
			/* If the color and intensity values received are within the acceptable 
			* range, then PrISM has to be enabled and written with correct density 
			* value to present the right color. For this, reset the shut_down_led 
			* flag to allow CPU to go to only Sleep, and not Deep Sleep. This is 
			* because CPU cannot be in Deep Sleep while PrISM is active */
			shut_down_led = FALSE;
			
			/* Set the time for RGB LED on Period. After this time (in seconds), the 
			* LED will be shutdown to prevent current usage */
			led_timer = LED_OFF_TIME_PERIOD;
			
			/* Set the drive mode for LED pins to Strong mode */
			RED_SetDriveMode(RED_DM_STRONG);
			GREEN_SetDriveMode(GREEN_DM_STRONG);
			BLUE_SetDriveMode(BLUE_DM_STRONG);
			
			/* Update the density value of the PrISM module for color control*/
			PrISM_1_WritePulse0(RGB_LED_MAX_VAL - debug_red);
		    PrISM_1_WritePulse1(RGB_LED_MAX_VAL - debug_green);
		    PrISM_2_WritePulse0(RGB_LED_MAX_VAL - debug_blue);
		}
	}
	
	/* Update RGB control handle with new values */
	rgbHandle.attrHandle = CYBLE_RGB_LED_RGB_LED_CONTROL_CHAR_HANDLE;
	rgbHandle.value.val = RGBledData;
	rgbHandle.value.len = RGB_CHAR_DATA_LEN;
	
	/* Send updated RGB control handle as attribute for read by central device, so that
	* Client reads the new RGB color data */
	CyBle_GattsWriteAttributeValue(&rgbHandle,FALSE,&connectionHandle,FALSE);
}


/*******************************************************************************
* Function Name: HandleStatusLED
********************************************************************************
* Summary:
*        Handle LED status, such as blinking, ON or OFF depending on BLE state.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void HandleStatusLED(void)
{
	/* Local static counter to handle the periodic toggling of LED or keeping LED ON
	* for some time. */
	static uint32 led_counter = TRUE;
	
	/* Local static variable that stores the last BLE state in which firmware was */
	static uint8 state = 0xFF;
	
	/* Flag to indicate that the state of BLE has changed from the last known value */
	uint8 state_changed = FALSE;
	
	if(state != CyBle_GetState())
	{
		/* If the present BLE state is different from the new BLE state, set the 
		* state_changed flag and reset the local counter */
		state_changed = TRUE;
				
		if(CyBle_GetState() == CYBLE_STATE_ADVERTISING)
		{
			led_counter = TRUE;
		}
	}
	
	/* Store the new BLE state into the present state variable */
	state = CyBle_GetState();
		
	switch(state)
	{
		case CYBLE_STATE_CONNECTED:
			/* If the present BLE state is connected, keep the LED ON for
			* pre-determined time and then switch it OFF in WDT ISR */
			if(state_changed)
			{
				/* Reset the flag for state change */
				state_changed = FALSE;
				
				/* Set the drive mode of LED to Strong to allow driving the LED */
				RED_SetDriveMode(RED_DM_STRONG);

				/* Put the Status LED to ON state */
				PrISM_1_WritePulse0(RGB_LED_ON);
				
				/* Set flag and counter for Connection indication on LED */
				switch_off_status_led = TRUE;
				timer_tick = LED_CONN_ON_TIME;
				
				/* Initialize the Watchdog for 1 second timing events. The watchdog 
				* is initialized after connection and disabled after disconnection.
				* This is done to ensure that Watchdog provides periodic wakeup only
				* when the system is connected and RGB LED control is required. During 
				* other times, it should not wakeup the system, causing increase in power
				* consumption */
				InitializeWatchdog();
			}
		break;
		
		case CYBLE_STATE_ADVERTISING:
			/* If the present BLE state is advertising, toggle the LED
			* at pre-determined period to indicate advertising. */
			if((--led_counter) == FALSE)
			{
				/* Toggle Status LED for indicating Advertisement */
				if(PrISM_1_ReadPulse0() == RGB_LED_OFF)
				{
					PrISM_1_WritePulse0(RGB_LED_ON);
					RED_SetDriveMode(RED_DM_STRONG);
					
					led_counter	= LED_ADV_BLINK_PERIOD_ON;
				}
				else
				{
					PrISM_1_WritePulse0(RGB_LED_OFF);
					RED_SetDriveMode(RED_DM_ALG_HIZ);
					
					led_counter	= LED_ADV_BLINK_PERIOD_OFF;
				}
			}
		break;
		
		case CYBLE_STATE_DISCONNECTED:
			/* If the present BLE state is disconnected, switch off LED
			* and set the drive mode of LED to Hi-Z (Analog)*/
			PrISM_1_WritePulse0(RGB_LED_OFF);
			RED_SetDriveMode(RED_DM_ALG_HIZ);
			GREEN_SetDriveMode(GREEN_DM_ALG_HIZ);
			BLUE_SetDriveMode(BLUE_DM_ALG_HIZ);
			
			/* Disable Watchdog to prevent Watchdog waking system after
			*  disconnection */
			CyIntDisable(WATCHDOG_INT_VEC_NUM);
		break;
		
		default:

		break;
	}
	
	/* Reset the state changed flag. */
	state_changed = FALSE;
}

/*******************************************************************************
* Function Name: WDT_INT_Handler
********************************************************************************
* Summary:
*        Watchdog interrupt routine for controlling LED status in connected state
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void WDT_INT_Handler(void)
{
	/* If the Interrupt source is Counter 0 match, then process */
	if(CySysWdtGetInterruptSource() & CY_SYS_WDT_COUNTER0_INT)
	{
		/* Clear Watchdog Interrupt from Counter 0 */
		CySysWdtClearInterrupt(CY_SYS_WDT_COUNTER0_INT);
		
		/* If switch_off_status_led is TRUE, then the Connection status LED 
		* is ON and it is required to shut it down after 3 seconds */
		if(switch_off_status_led)
		{
			/* If timer ticks for Connection status LED ON period has expired, then switch
			* off LED */
			if(timer_tick == FALSE)
			{
				/* Switch off Status LED */
				PrISM_1_WritePulse0(RGB_LED_OFF);
				
				/* Set the drive mode of LED to Analog HiZ to prevent leakage current */
				RED_SetDriveMode(RED_DM_ALG_HIZ);
				
				/* Reset the Flag */
				switch_off_status_led = FALSE;
				
			}
			else
			{
				/* Decrement timer_tick as counting method */
				timer_tick--;
			}
		}
		/* If the LED activity for Connection LED ON is completed, then firmware is 
		* allowed to do timing for RGB LED Control operation after connection. This 
		* operation keeps the RGB LED ON for determined time (default 3 seconds) from
		* the last time RGB LED data was sent. This ensures that continuous usage of 
		* the kit in RGB mode does not consume too much power */
		else
		{
			/* After displaying color for predetermined time, switch off 
			* the LEDs to save power */
			if(FALSE == led_timer)
			{
				/* Set the flag to indicate to the Low power mode function that system 
				* can be put to Deep Sleep as no LED operation is required */
				shut_down_led= TRUE;
				
				/* Shut down LEDs*/
				RED_SetDriveMode(RED_DM_ALG_HIZ);
				GREEN_SetDriveMode(GREEN_DM_ALG_HIZ);
				BLUE_SetDriveMode(BLUE_DM_ALG_HIZ);
			}
			else
			{	
				/* Decrement the led_timer as counting method for RGB LED Control. During
				* this period, the PrISM is active and drives the signal to display the 
				* appropriate color */
				led_timer--;
			}
		}
		
		/* Unlock the WDT registers for modification */
		CySysWdtUnlock();
		
		/* Disable Counter 0 to allow modifications */
		CySysWdtDisable(CY_SYS_WDT_COUNTER0_MASK);
		
		/* Reset Counter 0 and give ~3 LFCLK cycles to take effect */
		CySysWdtResetCounters(CY_SYS_WDT_COUNTER0_RESET);
		CyDelayUs(WATCHDOG_REG_UPDATE_WAIT_TIME);
		
		/* Write the Counter 0 match value for 1 second and give ~3 LFCLK
		* cycles to take effect */
		CySysWdtWriteMatch(CY_SYS_WDT_COUNTER0, WATCHDOG_ONE_SEC_COUNT_VAL);
		CyDelayUs(WATCHDOG_REG_UPDATE_WAIT_TIME);
		
		/* Enable Watchdog Counter 0 */
		CySysWdtEnable(CY_SYS_WDT_COUNTER0_MASK);
		
		/* Lock Watchdog to prevent any further change */
	    CySysWdtLock();
	}
}

/*******************************************************************************
* Function Name: InitializeWatchdog
********************************************************************************
* Summary:
*        Reset watchdog timer
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void InitializeWatchdog(void)
{
	/* Unlock the WDT registers for modification */
	CySysWdtUnlock(); 
	
	/* Write Mode for Counter 0 as Interrupt on Match */
    CySysWdtWriteMode(CY_SYS_WDT_COUNTER0, CY_SYS_WDT_MODE_INT);
	
	/* Set Clear on Match for Counter 0*/
	CySysWdtWriteClearOnMatch(CY_SYS_WDT_COUNTER0, TRUE);
    
	/* Set Watchdog interrupt to lower priority */
	CyIntSetPriority(WATCHDOG_INT_VEC_NUM, WATCHDOG_INT_VEC_PRIORITY);
	
	/* Enable Watchdog Interrupt using Interrupt number */
    CyIntEnable(WATCHDOG_INT_VEC_NUM);
	
	/* Write the match value equal to 1 second in Counter 0 */
	CySysWdtWriteMatch(CY_SYS_WDT_COUNTER0, WATCHDOG_ONE_SEC_COUNT_VAL);
    
	/* Enable Counter 0 */
    CySysWdtEnable(CY_SYS_WDT_COUNTER0_MASK);
	
	/* Lock Watchdog to prevent further changes */
    CySysWdtLock();
}
/* [] END OF FILE */
