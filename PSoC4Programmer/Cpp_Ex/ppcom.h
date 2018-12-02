/*******************************************************************************
* © 2008-2017, Cypress Semiconductor Corporation
* or a subsidiary of Cypress Semiconductor Corporation. All rights
* reserved.
* 
* This software, including source code, documentation and related
* materials (“Software”), is owned by Cypress Semiconductor
* Corporation or one of its subsidiaries (“Cypress”) and is protected by
* and subject to worldwide patent protection (United States and foreign),
* United States copyright laws and international treaty provisions.
* Therefore, you may use this Software only as provided in the license
* agreement accompanying the software package from which you
* obtained this Software (“EULA”).
* 
* If no EULA applies, Cypress hereby grants you a personal, non-
* exclusive, non-transferable license to copy, modify, and compile the
* Software source code solely for use in connection with Cypress’s
* integrated circuit products. Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
* 
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO
* WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING,
* BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE. Cypress reserves the right to make
* changes to the Software without notice. Cypress does not assume any
* liability arising out of the application or use of the Software or any
* product or circuit described in the Software. Cypress does not
* authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death (“High Risk Product”). By
* including Cypress’s product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
********************************************************************************/
#if !defined(PPCOM_INCLUDED)
#define PPCOM_INCLUDED
//------------------------------------------------------------------------------
// Definitions extracted from PSoCProgrammerCOM.idl - PP COM-object ver 3.00
//------------------------------------------------------------------------------

enum enumInterfaces
{
	JTAG	= 0x01,
	ISSP	= 0x02,
	I2C		= 0x04,
	SWD		= 0x08,
	SPI     = 0x10
};

enum enumFrequencies
{
    FREQ_48_0 = 0x00,
    FREQ_24_0 = 0x04,
    FREQ_16_0 = 0x10,
    FREQ_12_0 = 0x84,
    FREQ_08_0 = 0x90,
    FREQ_06_0 = 0x60,
    FREQ_03_2 = 0x18,
    FREQ_03_0 = 0xE0,
    FREQ_01_6 = 0x98,
    FREQ_01_5 = 0xC0,
    FREQ_RESET = 0xFC
};

enum enumVoltages
{
	VOLT_50V	= 0x01,
	VOLT_33V	= 0x02,
	VOLT_25V	= 0x04,
	VOLT_18V	= 0x08,
};

enum enumI2Cspeed
{
	CLK_100K	= 0x01,
	CLK_400K	= 0x02,
	CLK_50K		= 0x04,
};

enum  enumSonosArrays
{ 
	ARRAY_FLASH			= 0x01,
	ARRAY_EEPROM		= 0x02,
	ARRAY_NVL_USER		= 0x04,
	ARRAY_NVL_FACTORY	= 0x08,
	ARRAY_NVL_WO_LATCHES= 0x10,
	ARRAY_ALL			= 0x1F
};

//Used in the GetProgrammerCapabilities()/GetProgrammerCapsByName()
enum enumUpgradeFirmware
{
	INITIALIZE		= 0x00,
	UPGRADE_BLOCK	= 0x01,
	VERIFY_BLOCK	= 0x02,
	FINALIZE		= 0x03
};

enum enumValidAcquireModes
{
	CAN_RESET_ACQUIRE		= 0x01,
	CAN_POWER_CYCLE_ACQUIRE	= 0x02,
	CAN_POWER_DETECT_ACQUIRE= 0x04
};
	
enum enumCanPowerDevice
{
	CAN_POWER_DEVICE	= 0x01,
	CAN_READ_POWER		= 0x02,
	CAN_MEASURE_POWER	= 0x04,
	CAN_MEASURE_POWER_2 = 0x08
};

enum enumCanProgram
{
	CAN_PROGRAM_CARBON	= 0x01,
	CAN_PROGRAM_ENCORE	= 0x02
};

#endif