/*****************************************************************************
* File Name: interface.h
*
* Version: 1.00
*
* Description: Demonstrates Liquid Level Sensing (LLS) using CapSense CSD with 12 sensors.
*
* Related Document: Code example CE202479
*
* Hardware Dependency: See code example CE202479
*
******************************************************************************
* Copyright (2015), Cypress Semiconductor Corporation.
******************************************************************************
* This software is owned by Cypress Semiconductor Corporation (Cypress) and is
* protected by and subject to worldwide patent protection (United States and
* foreign), United States copyright laws and international treaty provisions.
* Cypress hereby grants to licensee a personal, non-exclusive, non-transferable
* license to copy, use, modify, create derivative works of, and compile the
* Cypress Source Code and derivative works for the sole purpose of creating
* custom software in support of licensee product to be used only in conjunction
* with a Cypress integrated circuit as specified in the applicable agreement.
* Any reproduction, modification, translation, compilation, or representation of
* this software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH
* REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes without further notice to the
* materials described herein. Cypress does not assume any liability arising out
* of the application or use of any product or circuit described herein. Cypress
* does not authorize its products for use as critical components in life-support
* systems where a malfunction or failure may reasonably be expected to result in
* significant injury to the user. The inclusion of Cypress' product in a life-
* support systems application implies that the manufacturer assumes all risk of
* such use and in doing so indemnifies Cypress against all charges. Use may be
* limited by and subject to the applicable Cypress software license agreement.
*****************************************************************************/
#include <project.h>


/* Function prototypes */
void StoreCalibration(void);
void ProcessUprobe(void);
void InitialUartMessage(void);
void CalUartCommands(void);
void CalUartMessage(void);
void TestUartMessage(void);
void ProcessUart(void);
void TxIntNumber(int32 number, int8 leadingZeros);
void TxIntFixedNumber(int32 number, uint8 fixedShift, uint8 numDecimal);
cystatus Em_EEPROM_Write(const uint8 srcBuf[], const uint8 eepromPtr[], uint32 byteCount);


/* Project Constants */
/* uProbe constants */  
#define NUMSAMPLES          (20u)          /* Number of sensor levels to test */
/* UART constants */
#define UART_DELAY          (500u)         /* Delay in ms to control data logging rate */
#define UART_NONE           (0u)
#define UART_BASIC          (1u)
#define UART_CSVINIT        (2u)
#define UART_CSV            (3u)


/* [] END OF FILE */
