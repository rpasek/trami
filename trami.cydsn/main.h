/******************************************************************************
* Project Name		: PSoC_4_BLE_CapSense_Slider_LED
* File Name			: main.h
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

/********************************************************************************
*	Contains all macros and function declarations used in the main.c file 
********************************************************************************/
#if !defined(MAIN_H)
#define MAIN_H

#include <project.h>
#include <BLEApplications.h>
#include <HandleLowPower.h>
#include "CyFlash.h"
/* Function prototypes */
cystatus Em_EEPROM_Write(const uint8 srcBuf[], const uint8 eepromPtr[], uint32 byteCount);

/* Project Constants */
/* CapSense tuning constants */
#define SENSOR_MODDAC       (150u)        /* Modulation DAC current setting */
#define SENSOR_CMPDAC       (20u)         /* Compensation DAC current setting */
#define SENSOR_SENDIV       (9u)          /* Sensor clock divider */
#define SENSOR_MODDIV       (9u)          /* Modulation clock divider */
/* Liquid Level constants */
#define NUMSENSORS          (12u)          /* Number of CapSense sensors */
#define SENSORMAX           (600u)         /* Maximum difference count of each calibrated sensor at full level */
#define SENSORLIMIT         (SENSORMAX / 2) /* Threshold for determining if a sensor is submerged. Set to half of SENSORMAX value */
#define LEVELMM_MAX         (153u)         /* Max sensor height in mm */
#define SENSORHEIGHT        ((LEVELMM_MAX * 256) / (NUMSENSORS - 1)) /* Height of a single sensor. Fixed precision 24.8 */
/* EEPROM constants */
#define Em_EEPROM_FLASH_BASE_ADDR        (CYDEV_FLASH_BASE)
#define Em_EEPROM_FLASH_SIZE             (CYDEV_FLASH_SIZE)
#define Em_EEPROM_FLASH_END_ADDR         (Em_EEPROM_FLASH_BASE_ADDR + Em_EEPROM_FLASH_SIZE)
#define Em_EEPROM_ROWS_IN_ARRAY          (CY_FLASH_SIZEOF_ARRAY/CY_FLASH_SIZEOF_ROW)


/***************************Macro Declarations*******************************/
/* Respective indexes of color co-ordinates in the 4-byte data received
* over RGB LED control characteristic */
#define RED_INDEX						0
#define GREEN_INDEX						1
#define BLUE_INDEX						2
#define INTENSITY_INDEX					3
	
/* Slider position value received from CapSense Component when no finger is 
* placed on the slider */
#define NO_FINGER 						0xFFFFu
	
/* Range of CapSense Slider centroid with finger placed on slider is 0-100 */
#define SLIDER_MAX_VALUE				0x0064

/* PrISM Density value for Max intensity. Note that the LED on the BLE Pioneer 
* kit is active Low, so the correct value to drive to maximum intensity is 0.
* This is taken care by the UpdateRGBled() function */
#define RGB_LED_MAX_VAL					255

/* PrISM density value for LED OFF. Note that LED on BLE Pioneer kit is
* active low */
#define RGB_LED_OFF						255
	
/* PrISM density value for LED ON. Note that LED on BLE Pioneer kit is
* active low */
#define RGB_LED_ON						0

/* Firmware thresholds for the two extremes of LED intensity */
#define LED_FULL_INTENSITY				0xF0
#define LED_NO_COLOR_THRESHOLD			0x04

/* General Macros */
#define TRUE							1
#define FALSE							0
#define ZERO							0
/****************************************************************************/
	
/**************************Function Declarations*****************************/
CY_ISR_PROTO(MyISR);
void InitializeSystem(void);
void UpdateRGBled(void);
void HandleCapSenseSlider(void);
void SendDataOverCapSenseNotification(uint8 CapSenseSliderData);
/****************************************************************************/
#endif
/* [] END OF FILE */
