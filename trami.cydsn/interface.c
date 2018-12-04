/*****************************************************************************
* File Name: interface.c
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
#include <main.h>
#include <interface.h>


/* Global variables */
/* Global variables used because this is the method uProbe uses to access firmware data */
/* uProbe variables */
uint8 storeSampleFlag = FALSE;
uint8 resetSampleFlag = FALSE;
int16 arrayAxisLabel[NUMSAMPLES] = {-5,0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,153,160,0};
/* UART variables */
uint8 uartTxMode = UART_BASIC;
/* External globals */
extern uint8 modDac;
extern uint8 compDac[];
extern uint8 senseDivider;
extern uint8 modDivider;
extern int16 sensorEmptyOffset[];
extern uint8 storeSampleFlag;
extern uint8 resetSampleFlag;
extern uint8 uartTxMode;
extern int16 arrayAxisLabel[];
extern int32 levelPercent;                 
extern int32 levelMm; 
extern int32 sensorRaw[];
extern int32 sensorDiff[];
extern int32 sensorProcessed[];
extern uint8 calFlag;
extern int16 eepromEmptyOffset[];
extern uint8 sensorActiveCount;


/*******************************************************************************
* Function Name: StoreCalibration
********************************************************************************/
/* Store current raw counts with an empty container to emulated EEPROM (in Flash).             */
/* Allows restoring calibration values on power on or reset. CapSense_CSD_ScanEnabledWidgets() */
/* function must be called prior to this function to ensure valid data is present for storage. */
void StoreCalibration(void)
{
    uint8 i;
    uint8 status;
    
    /* Calculate offset for each sensor */
    for(i = 0; i < NUMSENSORS; i++)
    {
        sensorEmptyOffset[i] = sensorDiff[i];
    }
    CalUartMessage();
    
    /* Store new cal values */
    status = Em_EEPROM_Write((uint8 *)sensorEmptyOffset, (uint8 *)eepromEmptyOffset, 6u);
    if (CYRET_SUCCESS != status)
    {
        while(1);
        /* EEPROM Error handler */   
    }
}


/*******************************************************************************
* Function Name: ProcessUprobe
********************************************************************************/
/* Check if storage of current raw and level values to array has been commanded.            */
/* Set CapSense tuning parameters based on current global variable values.                  */
/* For more information on the CapSense_CSD functions called by this function, please       */
/* refer to the CapSense component datasheet and the PSoC 4 CapSense Tuning Guide document. */
void ProcessUprobe(void)
{
    uint8 i;
    
    /* Update CapSense scan settings from uProbe*/
    for(i = 0; i < NUMSENSORS; i++)
    {
        CapSense_CSD_SetSenseClkDivider(i, senseDivider);
        modDivider = senseDivider;      /* Divider values should be the same */
        CapSense_CSD_SetModulatorClkDivider(i, modDivider);
        CapSense_CSD_SetModulationIDAC(i, modDac);
        CapSense_CSD_SetCompensationIDAC(i, compDac[i]);
    }
        
}


/*******************************************************************************
* Function Name: InitialUartMessage
********************************************************************************/
/* Transmit startup project information */
void InitialUartMessage(void)
{
    UART_UartPutString("-- Liquid Level Sensing Example Project --\n\r");
    UART_UartPutString("CSD 12RX - Version 1.0 \n\r");
    CalUartCommands();
    CalUartMessage();
}


/*******************************************************************************
* Function Name: CalUartCommands
********************************************************************************/
/* Transmit list of available commands */
void CalUartCommands(void)
{
    UART_UartPutString("\n\r");
    UART_UartPutString("Commands \n\r");
    UART_UartPutString("  stop - Stops outputing data over UART.\n\r");
    UART_UartPutString("  cal - Stores empty container sensor values to EEPROM for calibration.\n\r");
    UART_UartPutString("  basic - Outputs liquid level in mm and %.\n\r");
    UART_UartPutString("  csv - Outputs intermediate computation values as well as liquid level in CSV format.\n\r");
    UART_UartPutString("  'Enter' - Outputs the next set of level values from the sample array.\n\r");
    UART_UartPutString("  reset - Resets the sample array pointer to 0 %.\n\r");
    UART_UartPutString("\n\r");
}


/*******************************************************************************
* Function Name: CalUartMessage
********************************************************************************/
/* Transmit currently stored calibration values */
void CalUartMessage(void)
{
    uint8 i;
    
    UART_UartPutString("EmptyCal=");
    for(i = 0; i < NUMSENSORS; i++)
    {
        TxIntNumber(sensorEmptyOffset[i], 0);
        UART_UartPutString(",");
    }
    UART_UartPutString("\r\n");
}


/*******************************************************************************
* Function Name: TestUartMessage
********************************************************************************/
/* Outputs the next set of level values from the sample array */
void TestUartMessage(void)
{
    uint8 i;
    static uint16 sampleIndex;

    /* Check if we should output sensor level data */
    if(storeSampleFlag == TRUE)
    {
        uartTxMode = UART_NONE;
        
        if(sampleIndex == 0)
        {
            UART_UartPutString("Presetmm,");
            for(i = 1; i < NUMSENSORS; i++)
            {
                UART_UartPutString("SenDiff");
                TxIntNumber(i, 0);
                UART_UartPutString(",");
            }
            UART_UartPutString("Level%,Levelmm");
            UART_UartPutString("\r\n");
        }
        TxIntNumber(arrayAxisLabel[sampleIndex], 0);
        UART_UartPutString(",");
        for(i = 1; i < NUMSENSORS; i++)
        {
            TxIntNumber(sensorProcessed[i], 0);
            UART_UartPutString(",");
        }
        TxIntFixedNumber(levelPercent, 8, 1);
        UART_UartPutString(",");
        /* Transmit current liquid level mm */
        TxIntFixedNumber(levelMm, 8, 1);
        UART_UartPutString("\r\n");
            
        /* Increment and limit array index */
        sampleIndex += 1;
        if(sampleIndex >= NUMSAMPLES)
        {
            sampleIndex = NUMSAMPLES - 1;
        }
        
        /* Clear flag to allow user to press for next store request */
        storeSampleFlag = FALSE;
    }
    /* Check if we should reset for a new test sequence */
    if(resetSampleFlag == TRUE)
    { 
        sampleIndex = 0;
        UART_UartPutString("Reset Test Level");
        UART_UartPutString("\r\n");
        /* Clear flags to allow user to press for next store request */
        resetSampleFlag = FALSE;
        storeSampleFlag = FALSE;
    }
}


/*******************************************************************************
* Function Name: ProcessUart
********************************************************************************/
/* Transmit over UART the current liquid level in percent and mm */
void ProcessUart(void)
{
    char character;
    static uint16 bufferIndex = 0;
    static char rxBuffer[32];
    uint8 i;
    
    if(uartTxMode == UART_BASIC)
    {
        /* Transmit current liquid level Percent */
        UART_UartPutString("%=");
        TxIntNumber(levelPercent >> 8, 0);
        /* Add one decimal point digit to percent */
        UART_UartPutString(".");
        TxIntNumber(((levelPercent & 0x000000FF) * 10) >> 8, 0);
        /* Transmit current liquid level mm */
        UART_UartPutString("   mm=");
        TxIntNumber(levelMm >> 8, 0);
        UART_UartPutString(".");
        TxIntNumber(((levelMm & 0x000000FF) * 10) >> 8, 0);
        UART_UartPutString("\r\n");
    }
    if(uartTxMode == UART_CSVINIT)
    {
        for(i = 0; i < NUMSENSORS; i++)
        {
            UART_UartPutString("Raw");
            TxIntNumber(i, 0);
            UART_UartPutString(",");
        }
        for(i = 0; i < NUMSENSORS; i++)
        {
            UART_UartPutString("Diff");
            TxIntNumber(i, 0);
            UART_UartPutString(",");
        }
        for(i = 0; i < NUMSENSORS; i++)
        {
            UART_UartPutString("Proc");
            TxIntNumber(i, 0);
            UART_UartPutString(",");
        }

        UART_UartPutString("SenActCnt,");

        UART_UartPutString("Level%,Levelmm");
        UART_UartPutString("\r\n");
        uartTxMode = UART_CSV;
    }
    else if(uartTxMode == UART_CSV)
    {
        for(i = 0; i < NUMSENSORS; i++)
        {
            TxIntNumber(sensorRaw[i], 0);
            UART_UartPutString(",");
        }
        for(i = 0; i < NUMSENSORS; i++)
        {
            TxIntNumber(sensorDiff[i], 0);
            UART_UartPutString(",");
        }
        for(i = 0; i < NUMSENSORS; i++)
        {
            TxIntNumber(sensorProcessed[i], 0);
            UART_UartPutString(",");
        }

        TxIntNumber(sensorActiveCount, 0);
        UART_UartPutString(",");

        TxIntFixedNumber(levelPercent, 8, 1);
        UART_UartPutString(",");
        /* Transmit current liquid level mm */
        TxIntFixedNumber(levelMm, 8, 1);
        UART_UartPutString("\r\n");
    }
    
    /* Looking for UART commands. */
    /* Carriage return (CR) and/or Line Feed (LF) terminated */
    character = UART_UartGetChar();	
	while(character > 0)
	{
        UART_UartPutChar(character);    /* Echo received characters */
        
        if((character == '\r') || (character == '\n'))
        {
            rxBuffer[bufferIndex] = 0;
            
            if(strcmp("cal", rxBuffer) == 0) 
    		{
    			calFlag = TRUE;
                UART_UartPutString("\r\n");
    		}
            else if(strcmp("stop", rxBuffer) == 0) 
    		{
    			uartTxMode = UART_NONE;
                UART_UartPutString("\r\n");
    		}
            else if(strcmp("csv", rxBuffer) == 0) 
    		{
    			uartTxMode = UART_CSVINIT;
                UART_UartPutString("\r\n");
    		}
            else if(strcmp("basic", rxBuffer) == 0) 
    		{
    			uartTxMode = UART_BASIC;
                UART_UartPutString("\r\n");
    		}
            else if(strcmp("", rxBuffer) == 0) 
    		{
    			storeSampleFlag = TRUE;
                uartTxMode = UART_NONE;
    		}
            else if(strcmp("reset", rxBuffer) == 0) 
    		{
    			resetSampleFlag = TRUE;
                uartTxMode = UART_NONE;
                UART_UartPutString("\r\n");
    		}
            else
            {
                UART_UartPutString("Command Error");
                UART_UartPutString("\r\n");
            }
            bufferIndex = 0;
            rxBuffer[bufferIndex] = 0;
            character = 0;
            while(UART_UartGetChar() > 0);
        }
        else
        {
            rxBuffer[bufferIndex] = character;          
			bufferIndex++;
            character = UART_UartGetChar();
        }
    }
    
    /* Check if test UART message should be sent */
    TestUartMessage();
}


/*******************************************************************************
* Function Name: TxIntNumber
********************************************************************************/
/* Transmit over UART the decimal representation of a int32 variable with optional leading zeros. */
/* leadingZeros - Number of leading zeros to force display of. Useful for fractional numbers after decimal point. */
void TxIntNumber(int32 number, int8 leadingZeros)
{
    uint8 digit = 0;
    uint8 zeroFlag = 0;
    int8 i = 0;
    const int32 decimal[] = {1000000000, 100000000, 10000000, 1000000, 100000, 10000, 1000, 100, 10, 1};
    
    /* Check for out of range parameters */
    if(leadingZeros > 10)
    {
        leadingZeros = 10;
    }
    if(number < 0)
    {
        number *= -1;
        UART_SpiUartWriteTxData('-');
    }
    
    /* Loop through each digit and subtract out represented decimal quantity */
    for(i = 0; i <= 9; i++)
    {
        digit = 0;
        while(number >= decimal[i])
        {
            zeroFlag = 1;
            number -= decimal[i];
            digit++;
        }
        /* display digit (and any following) if digit > 0, 1s digit = 0, or we have reached the number of forced leading zeros */ 
        if((zeroFlag == 1) || (i == 9) || (i >= (10 - leadingZeros)))
        {
            UART_SpiUartWriteTxData(digit + 48);
        }
    }
}
  

/*******************************************************************************
* Function Name: TxIntFixedNumber
********************************************************************************/
/* Transmit over UART the decimal representation of a fixed precision int32 variable. */
/* fixedShift - Number of bits for fractional portion of number                       */
/* numDecimal - Number of decimal digits after the decimal point to display           */
void TxIntFixedNumber(int32 number, uint8 fixedShift, uint8 numDecimal)
{
    int8 i = 0;
    int64 decimalNum = 0;
    int32 decDigits = 1;
    
    /* Check for out of range parameters */
    if(fixedShift > 32)
    {
        fixedShift = 32;
    }
    if(numDecimal > 9)
    {
        numDecimal = 9;   
    }
    
    /* Display whole number part of value */
    TxIntNumber(number >> fixedShift, 0);
    /* Display fractional part of number if required */
    if(numDecimal > 0)
    {
        UART_SpiUartWriteTxData('.');
        decDigits = 1;
        /* Calculate fractional portion scaling multiplier */ 
        for(i = 0; i < numDecimal; i++)
        {
            decDigits *= 10;
        }
        decimalNum = ((number & (0xFFFFFFFF >> (32 - fixedShift))) * decDigits) >> fixedShift;
        TxIntNumber(decimalNum, numDecimal);
    }
}


/*******************************************************************************
* Function Name: Em_EEPROM_Write
********************************************************************************
*
* Summary:
*  Writes the specified number of bytes from the source buffer in SRAM to the
*  emulated EEPROM array in flash, without modifying other data in flash.
*
* Parameters:
*  srcBuf:    Pointer to the SRAM buffer holding the data to write.
*  eepromPtr: Pointer to the array or variable in flash representing
*             the emulated EEPROM.
*  byteCount: Number of bytes to write from srcBuf to eepromPtr.
*
* Return:
*    CYRET_SUCCESS     Successful write.
*    CYRET_BAD_PARAM   eepromPtr is out of range of flash memory.
*    CYRET_UNKNOWN     Other error in writing flash.
*
*******************************************************************************/
cystatus Em_EEPROM_Write(const uint8 srcBuf[], const uint8 eepromPtr[], uint32 byteCount)
{
    uint8 writeBuffer[CY_FLASH_SIZEOF_ROW];
    uint32 arrayId;
    uint32 rowId;
    uint32 dstIndex;
    uint32 srcIndex;
    cystatus rc;
    uint32 eeOffset;
    uint32 byteOffset;
    
    eeOffset = (uint32)eepromPtr;

    /* Make sure, that eepromPtr[] points to ROM */
    if (((uint32)eepromPtr + byteCount) < Em_EEPROM_FLASH_END_ADDR)
    {
        arrayId = eeOffset / CY_FLASH_SIZEOF_ARRAY;
        rowId = (eeOffset / CY_FLASH_SIZEOF_ROW) % Em_EEPROM_ROWS_IN_ARRAY;
        byteOffset = (CY_FLASH_SIZEOF_ARRAY * arrayId) + (CY_FLASH_SIZEOF_ROW * rowId);
        srcIndex = 0u;

        rc = CYRET_SUCCESS;

        while ((srcIndex < byteCount) && (CYRET_SUCCESS == rc))
        {
            /* Copy data to the write buffer either from the source buffer or from the flash */
            for (dstIndex = 0u; dstIndex < CY_FLASH_SIZEOF_ROW; dstIndex++)
            {
                if ((byteOffset >= eeOffset) && (srcIndex < byteCount))
                {
                    writeBuffer[dstIndex] = srcBuf[srcIndex];
                    srcIndex++;
                }
                else
                {
                    writeBuffer[dstIndex] = CY_GET_XTND_REG8(CYDEV_FLASH_BASE + byteOffset);
                }
                byteOffset++;
            }

            /* Write flash row */
            rc = CySysFlashWriteRow(rowId, writeBuffer);

            /* Go to the next row */
            rowId++;
            #if (CY_FLASH_NUMBER_ARRAYS > 1)
                if (rowId >= Em_EEPROM_ROWS_IN_ARRAY)
                {
                    arrayId++;
                    rowId = 0u;
                }
            #endif /* (CY_FLASH_NUMBER_ARRAYS > 1) */
        }

        /* Flush both Cache and PHUB prefetch buffer */
    }
    else
    {
        rc = CYRET_BAD_PARAM;
    }

    /* Mask return codes from flash, if they are not supported */
    if ((CYRET_SUCCESS != rc) && (CYRET_BAD_PARAM != rc))
    {
        rc = CYRET_UNKNOWN;
    }
    
    return (rc);
}



/* [] END OF FILE */
