/*******************************************************************************
* File Name: CapSense_CSD.h
* Version 2.60
*
* Description:
*  This file provides constants and parameter values for the CapSense CSD
*  component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CAPSENSE_CSD_CapSense_CSD_H)
#define CY_CAPSENSE_CSD_CapSense_CSD_H

#include "cytypes.h"
#include "cyfitter.h"
#include "core_cm0_psoc4.h"
#include "CyLib.h"

#include "CapSense_CSD_IP.h"
#include "CapSense_CSD_SenseClk.h"
#include "CapSense_CSD_SampleClk.h"

/* Constants set by Customizer */
#define CapSense_CSD_TOTAL_SENSOR_COUNT            (12u)
#define CapSense_CSD_TOTAL_SCANSLOT_COUNT          (12u)
#define CapSense_CSD_INDEX_TABLE_SIZE              (0u)

/* Define Sensors */
#define CapSense_CSD_SENSOR_GENERIC0_0__GEN    (0u)
#define CapSense_CSD_SENSOR_GENERIC1_0__GEN    (1u)
#define CapSense_CSD_SENSOR_GENERIC2_0__GEN    (2u)
#define CapSense_CSD_SENSOR_GENERIC3_0__GEN    (3u)
#define CapSense_CSD_SENSOR_GENERIC4_0__GEN    (4u)
#define CapSense_CSD_SENSOR_GENERIC5_0__GEN    (5u)
#define CapSense_CSD_SENSOR_GENERIC6_0__GEN    (6u)
#define CapSense_CSD_SENSOR_GENERIC7_0__GEN    (7u)
#define CapSense_CSD_SENSOR_GENERIC8_0__GEN    (8u)
#define CapSense_CSD_SENSOR_GENERIC9_0__GEN    (9u)
#define CapSense_CSD_SENSOR_GENERIC10_0__GEN    (10u)
#define CapSense_CSD_SENSOR_GENERIC11_0__GEN    (11u)

#define CapSense_CSD_TOTAL_SENSOR_MASK (((CapSense_CSD_TOTAL_SENSOR_COUNT - 1u) / 8u) + 1u)

/* Interrupt handler */
CY_ISR_PROTO(CapSense_CSD_ISR);

/* ISR Number and Priority to work with CyLib functions */
#define CapSense_CSD_ISR_NUMBER        (CapSense_CSD_ISR__INTC_NUMBER)
#define CapSense_CSD_ISR_PRIORITY      (CapSense_CSD_ISR__INTC_PRIOR_NUM)

/***************************************
*   Condition compilation parameters
***************************************/

#define CapSense_CSD_CONNECT_INACTIVE_SNS       (0u)
#define CapSense_CSD_IS_COMPLEX_SCANSLOTS       (0u)
#define CapSense_CSD_COMPLEX_SCANSLOTS_NUM      (0u)
#define CapSense_CSD_DEDICATED_SENSORS_NUM      (0u)
#define CapSense_CSD_PORT_PIN_CONFIG_TBL_ZISE   (12u)

#define CapSense_CSD_IDAC_CNT                   (2u)
#define CapSense_CSD_IDAC1_POLARITY             (0u)
#define CapSense_CSD_IDAC1_RANGE_VALUE          (1u)
#define CapSense_CSD_IDAC2_RANGE_VALUE          (1u)

#define CapSense_CSD_MULTIPLE_FREQUENCY_SET     (0u)
#define CapSense_CSD_FILTER_ENABLE              (0u)
#define CapSense_CSD_PRS_OPTIONS                (2u)

#define CapSense_CSD_WATER_PROOF                (0u)

#define CapSense_CSD_TUNING_METHOD              (1u)
#define CapSense_CSD_TUNER_API_GENERATE         (0u)

#define CapSense_CSD_CSHL_API_GENERATE          (0u)

#define CapSense_CSD_CMOD_PREGARGE_OPTION       (1u)
#define CapSense_CSD_CSH_TANK_PREGARGE_OPTION   (1u)
#define CapSense_CSD_IS_SHIELD_ENABLE           (0u)
#define CapSense_CSD_CSH_TANK_ENABLE            (0u)

#define CapSense_CSD_SHIELD_DELAY               (0u)
#define CapSense_CSD_AUTOCALIBRATION_ENABLE     (0u)

#define CapSense_CSD_IS_OVERSAMPLING_EN         (1u)

#define CapSense_CSD_CSD_4B_PWM_MODE            (0u)
#define CapSense_CSD_CSD_4B_PWM_COUNT           (0u)

/**************************************
*    Enumerated Types and Parameters
**************************************/

/* Current source definitions */
#define CapSense_CSD__IDAC_SOURCE 0
#define CapSense_CSD__IDAC_SINK 1

#define CapSense_CSD__IDAC_4X 0
#define CapSense_CSD__IDAC_8X 1

#define CapSense_CSD__PRS_NONE 0
#define CapSense_CSD__PRS_8BITS 1
#define CapSense_CSD__PRS_12BITS 2
#define CapSense_CSD__PRS_AUTO 3

/* Connection of inactive sensors definitions */
#define CapSense_CSD__GROUND 0
#define CapSense_CSD__HIZ_ANALOG 1
#define CapSense_CSD__SHIELD 2

/* Precharge options definitions */
#define CapSense_CSD__CAPPRIOBUF 0
#define CapSense_CSD__CAPPRVREF 1

/* Method of tuning */
#define CapSense_CSD__TUNING_NONE 0
#define CapSense_CSD__TUNING_MANUAL 1
#define CapSense_CSD__TUNING_AUTO 2

/* Dead band PWM modulator options */
#define CapSense_CSD__PWM_OFF 0
#define CapSense_CSD__PWM_HIGH 2
#define CapSense_CSD__PWM_LOW 3


#define CapSense_CSD_DELAY_EXTRACYCLES_NUM          (9u)
#define CapSense_CSD_GLITCH_ELIMINATION_TIMEOUT     (0u)
#define CapSense_CSD_GLITCH_ELIMINATION_CYCLES_CALC (CapSense_CSD_GLITCH_ELIMINATION_TIMEOUT * CYDEV_BCLK__SYSCLK__MHZ)

#if(CapSense_CSD_GLITCH_ELIMINATION_CYCLES_CALC >= CapSense_CSD_DELAY_EXTRACYCLES_NUM)
    #define CapSense_CSD_GLITCH_ELIMINATION_CYCLES (CapSense_CSD_GLITCH_ELIMINATION_CYCLES_CALC -\
                                                        CapSense_CSD_DELAY_EXTRACYCLES_NUM)
#else
    #define CapSense_CSD_GLITCH_ELIMINATION_CYCLES (CapSense_CSD_GLITCH_ELIMINATION_CYCLES_CALC)
#endif /* (CapSense_CSD_GLITCH_ELIMINATION_CYCLES_CALC >= CapSense_CSD_DELAY_EXTRACYCLES_NUM) */

#define CapSense_CSD_INITIAL_CLK_DIVIDER            (CYDEV_BCLK__HFCLK__KHZ / CYDEV_BCLK__SYSCLK__KHZ)


/* Structure to save registers before going to sleep */
typedef struct
{
    uint8 enableState;
} CapSense_CSD_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/
void CapSense_CSD_Init(void);
void CapSense_CSD_CsdHwBlockInit(void);
void CapSense_CSD_Enable(void);
void CapSense_CSD_Start(void);
void CapSense_CSD_Stop(void);
void CapSense_CSD_SaveConfig(void);
void CapSense_CSD_Sleep(void);
void CapSense_CSD_RestoreConfig(void);
void CapSense_CSD_Wakeup(void);
uint32 CapSense_CSD_IsBusy(void);
void CapSense_CSD_ScanSensor(uint32 sensor);
void CapSense_CSD_ScanWidget(uint32 widget);
void CapSense_CSD_ScanEnabledWidgets(void);
uint16 CapSense_CSD_ReadSensorRaw(uint32 sensor);
void CapSense_CSD_WriteSensorRaw(uint32 sensor, uint16 value);
void CapSense_CSD_ClearSensors(void);
void CapSense_CSD_SetShieldDelay(uint32 delay);
uint32 CapSense_CSD_ReadCurrentScanningSensor(void);

uint32 CapSense_CSD_GetScanResolution(uint32 widget);
uint32 CapSense_CSD_GetSenseClkDivider(uint32 sensor);
uint32 CapSense_CSD_GetModulatorClkDivider(uint32 sensor);
uint32 CapSense_CSD_GetModulationIDAC(uint32 sensor);
uint32 CapSense_CSD_GetCompensationIDAC(uint32 sensor);
uint32 CapSense_CSD_GetIDACRange(void);

#if (CapSense_CSD_TUNING_METHOD != CapSense_CSD__TUNING_NONE)
    void CapSense_CSD_SetScanResolution(uint32 widget, uint32 resolution);
    void CapSense_CSD_SetSenseClkDivider(uint32 sensor, uint32 senseClk);
    void CapSense_CSD_SetModulatorClkDivider(uint32 sensor, uint32 modulatorClk);
    void CapSense_CSD_SetModulationIDAC(uint32 sensor, uint32 modIdacValue);
    void CapSense_CSD_SetCompensationIDAC(uint32 sensor, uint32 compIdacValue);
    void CapSense_CSD_SetIDACRange(uint32 iDacRange);
#endif /* (CapSense_CSD_TUNING_METHOD != CapSense_CSD__TUNING_NONE) */


void CapSense_CSD_SetDriveModeAllPins(uint32 driveMode);
void CapSense_CSD_RestoreDriveModeAllPins(void);
void CapSense_CSD_SetUnscannedSensorState(uint32 sensor, uint32 sensorState);
void CapSense_CSD_NormalizeWidgets(uint32 widgetsNum, uint8 dataPtr[]);

/***************************************
*           API Constants
***************************************/

/* PWM Resolution */
#define CapSense_CSD_CNT_MSB_RESOLUTION_8_BITS  (0x00u)
#define CapSense_CSD_CNT_MSB_RESOLUTION_9_BITS  (0x01u)
#define CapSense_CSD_CNT_MSB_RESOLUTION_10_BITS (0x03u)
#define CapSense_CSD_CNT_MSB_RESOLUTION_11_BITS (0x07u)
#define CapSense_CSD_CNT_MSB_RESOLUTION_12_BITS (0x0Fu)
#define CapSense_CSD_CNT_MSB_RESOLUTION_13_BITS (0x1Fu)
#define CapSense_CSD_CNT_MSB_RESOLUTION_14_BITS (0x3Fu)
#define CapSense_CSD_CNT_MSB_RESOLUTION_15_BITS (0x7Fu)
#define CapSense_CSD_CNT_MSB_RESOLUTION_16_BITS (0xFFu)

#define CapSense_CSD_ONE_CYCLE                  (0x00010000Lu)

#define CapSense_CSD_WINDOW_APPEND              (0xFFFF0000Lu)
#define CapSense_CSD_RESOLUTION_6_BITS          (0x003F0000Lu)
#define CapSense_CSD_RESOLUTION_7_BITS          (0x007F0000Lu)
#define CapSense_CSD_RESOLUTION_8_BITS          (0x00FF0000Lu)
#define CapSense_CSD_RESOLUTION_9_BITS          (0x01FF0000Lu)
#define CapSense_CSD_RESOLUTION_10_BITS         (0x03FF0000Lu)
#define CapSense_CSD_RESOLUTION_11_BITS         (0x07FF0000Lu)
#define CapSense_CSD_RESOLUTION_12_BITS         (0x0FFF0000Lu)
#define CapSense_CSD_RESOLUTION_13_BITS         (0x1FFF0000Lu)
#define CapSense_CSD_RESOLUTION_14_BITS         (0x3FFF0000Lu)
#define CapSense_CSD_RESOLUTION_15_BITS         (0x7FFF0000Lu)
#define CapSense_CSD_RESOLUTION_16_BITS         (0xFFFF0000Lu)

#define CapSense_CSD_RESOLUTION_OFFSET          (16u)
#define CapSense_CSD_MSB_RESOLUTION_OFFSET      (22u)
#define CapSense_CSD_RESOLUTIONS_TBL_SIZE       (12u)

/* Software Status Register Bit Masks */
#define CapSense_CSD_SW_STS_BUSY                (0x01u)
/* Software Control Register Bit Masks */
#define CapSense_CSD_SW_CTRL_SINGLE_SCAN        (0x80u)

/* Software Control Register Bit Masks for scanning one widget */
#define CapSense_CSD_SW_CTRL_WIDGET_SCAN        (0x40u)

/* Flag for complex scan slot */
#define CapSense_CSD_COMPLEX_SS_FLAG            (0x80u)

/* Flag for scanning is complete */
#define CapSense_CSD_NOT_SENSOR                 (0xFFFFFFFFLu)

/* Number of bits for each pin in PC register. */
#define CapSense_CSD_PC_PIN_CFG_SIZE            (0x03u)

/* Number of bits for each pin in HSIOM register. */
#define CapSense_CSD_HSIOM_PIN_CFG_SIZE         (0x04u)

#define CapSense_CSD_CFG_REG_TBL_SIZE           (7u)

/***************************************
*             Registers
***************************************/

#define CapSense_CSD_CSD_ID_REG             (*(reg32 *)  CapSense_CSD_CSD_FFB__CSD_ID)
#define CapSense_CSD_CSD_ID_PTR             ( (reg32 *)  CapSense_CSD_CSD_FFB__CSD_ID)

#define CapSense_CSD_CSD_CFG_REG            (*(reg32 *)  CapSense_CSD_CSD_FFB__CSD_CONFIG)
#define CapSense_CSD_CSD_CFG_PTR            ( (reg32 *)  CapSense_CSD_CSD_FFB__CSD_CONFIG)

#define CapSense_CSD_CSD_IDAC_REG           (*(reg32 *)  CapSense_CSD_IDAC1_cy_psoc4_idac__CSD_IDAC)
#define CapSense_CSD_CSD_IDAC_PTR           ( (reg32 *)  CapSense_CSD_IDAC1_cy_psoc4_idac__CSD_IDAC)

#define CapSense_CSD_CSD_CNT_REG            (*(reg32 *) CapSense_CSD_CSD_FFB__CSD_COUNTER)
#define CapSense_CSD_CSD_CNT_PTR            ( (reg32 *) CapSense_CSD_CSD_FFB__CSD_COUNTER)

#define CapSense_CSD_CSD_STAT_REG           (*(reg32 *) CapSense_CSD_CSD_FFB__CSD_STATUS)
#define CapSense_CSD_CSD_STAT_PTR           ( (reg32 *) CapSense_CSD_CSD_FFB__CSD_STATUS)

#define CapSense_CSD_CSD_INTR_REG           (*(reg32 *) CapSense_CSD_CSD_FFB__CSD_INTR)
#define CapSense_CSD_CSD_INTR_PTR           ( (reg32 *) CapSense_CSD_CSD_FFB__CSD_INTR)

#define CapSense_CSD_CSD_INTR_SET_REG       (*(reg32 *) CapSense_CSD_CSD_FFB__CSD_INTR_SET)
#define CapSense_CSD_CSD_INTR_SET_PTR       ( (reg32 *) CapSense_CSD_CSD_FFB__CSD_INTR_SET)

#define CapSense_CSD_CSD_4B_PWM_REG         (*(reg32 *) CapSense_CSD_CSD_FFB__CSD_PWM)
#define CapSense_CSD_CSD_4B_PWM_PTR         ( (reg32 *) CapSense_CSD_CSD_FFB__CSD_PWM)

#define CapSense_CSD_CSD_TRIM1_REG          (*(reg32 *) CapSense_CSD_IDAC1_cy_psoc4_idac__CSD_TRIM1)
#define CapSense_CSD_CSD_TRIM1_PTR          ( (reg32 *) CapSense_CSD_IDAC1_cy_psoc4_idac__CSD_TRIM1)

#define CapSense_CSD_CSD_TRIM2_REG          (*(reg32 *) CapSense_CSD_IDAC1_cy_psoc4_idac__CSD_TRIM2)
#define CapSense_CSD_CSD_TRIM2_PTR          ( (reg32 *) CapSense_CSD_IDAC1_cy_psoc4_idac__CSD_TRIM2)

#if (2u == CapSense_CSD_M0S8CSD_BLOCK_CNT)
    #if (CapSense_CSD_CSD_FFB__CSD_NUMBER != 1u)
        #define CapSense_CSD_SFLASH_CSD_TRIM1_REG   (*(reg8 *) CYREG_SFLASH_CSD_TRIM1_CSD)
        #define CapSense_CSD_SFLASH_CSD_TRIM1_PTR   ( (reg8 *) CYREG_SFLASH_CSD_TRIM1_CSD)

        #define CapSense_CSD_SFLASH_CSD_TRIM2_REG   (*(reg8 *) CYREG_SFLASH_CSD_TRIM2_CSD)
        #define CapSense_CSD_SFLASH_CSD_TRIM2_PTR   ( (reg8 *) CYREG_SFLASH_CSD_TRIM2_CSD)
    #else
        #define CapSense_CSD_SFLASH_CSD_TRIM1_REG   (*(reg8 *) CYREG_SFLASH_CSD1_TRIM1_CSD)
        #define CapSense_CSD_SFLASH_CSD_TRIM1_PTR   ( (reg8 *) CYREG_SFLASH_CSD1_TRIM1_CSD)

        #define CapSense_CSD_SFLASH_CSD_TRIM2_REG   (*(reg8 *) CYREG_SFLASH_CSD1_TRIM2_CSD)
        #define CapSense_CSD_SFLASH_CSD_TRIM2_PTR   ( (reg8 *) CYREG_SFLASH_CSD1_TRIM2_CSD)
    #endif /* (CapSense_CSD_CSD_FFB__CSD_NUMBER != 1u) */
#else
    #define CapSense_CSD_SFLASH_CSD_TRIM1_REG   (*(reg8 *) CYREG_SFLASH_CSD_TRIM1_CSD)
    #define CapSense_CSD_SFLASH_CSD_TRIM1_PTR   ( (reg8 *) CYREG_SFLASH_CSD_TRIM1_CSD)

    #define CapSense_CSD_SFLASH_CSD_TRIM2_REG   (*(reg8 *) CYREG_SFLASH_CSD_TRIM2_CSD)
    #define CapSense_CSD_SFLASH_CSD_TRIM2_PTR   ( (reg8 *) CYREG_SFLASH_CSD_TRIM2_CSD)
#endif /* (2u == CapSense_CSD_M0S8CSD_BLOCK_CNT) */

/* Port function select */
#define CapSense_CSD_PORT_SEL0_REG          (*(reg32 *) CYREG_HSIOM_PORT_SEL0 )
#define CapSense_CSD_PORT_SEL0_PTR          (*(reg32 *) CYREG_HSIOM_PORT_SEL0 )

#define CapSense_CSD_PORT_SEL1_REG          (*(reg32 *) CYREG_HSIOM_PORT_SEL1 )
#define CapSense_CSD_PORT_SEL1_PTR          (*(reg32 *) CYREG_HSIOM_PORT_SEL1 )

#define CapSense_CSD_PORT_SEL2_REG          (*(reg32 *) CYREG_HSIOM_PORT_SEL2 )
#define CapSense_CSD_PORT_SEL2_PTR          (*(reg32 *) CYREG_HSIOM_PORT_SEL2 )

#define CapSense_CSD_PORT_SEL3_REG          (*(reg32 *) CYREG_HSIOM_PORT_SEL3 )
#define CapSense_CSD_PORT_SEL3_PTR          (*(reg32 *) CYREG_HSIOM_PORT_SEL3 )

#define CapSense_CSD_PORT_SEL4_REG          (*(reg32 *) CYREG_HSIOM_PORT_SEL4 )
#define CapSense_CSD_PORT_SEL4_PTR          (*(reg32 *) CYREG_HSIOM_PORT_SEL4 )

#define CapSense_CSD_PORT_SEL5_REG          (*(reg32 *) CYREG_HSIOM_PORT_SEL5 )
#define CapSense_CSD_PORT_SEL5_PTR          (*(reg32 *) CYREG_HSIOM_PORT_SEL5 )

#define CapSense_CSD_PORT_SEL6_REG          (*(reg32 *) CYREG_HSIOM_PORT_SEL6 )
#define CapSense_CSD_PORT_SEL6_PTR          (*(reg32 *) CYREG_HSIOM_PORT_SEL6 )


#define CapSense_CSD_PORT0_PC_REG          (*(reg32 *) CYREG_GPIO_PRT0_PC )
#define CapSense_CSD_PORT0_PC_PTR          (*(reg32 *) CYREG_GPIO_PRT0_PC )

#define CapSense_CSD_PORT1_PC_REG          (*(reg32 *) CYREG_GPIO_PRT1_PC )
#define CapSense_CSD_PORT1_PC_PTR          (*(reg32 *) CYREG_GPIO_PRT1_PC )

#define CapSense_CSD_PORT2_PC_REG          (*(reg32 *) CYREG_GPIO_PRT2_PC )
#define CapSense_CSD_PORT2_PC_PTR          (*(reg32 *) CYREG_GPIO_PRT2_PC )

#define CapSense_CSD_PORT3_PC_REG          (*(reg32 *) CYREG_GPIO_PRT3_PC )
#define CapSense_CSD_PORT3_PC_PTR          (*(reg32 *) CYREG_GPIO_PRT3_PC )

#define CapSense_CSD_PORT4_PC_REG          (*(reg32 *) CYREG_GPIO_PRT4_PC )
#define CapSense_CSD_PORT4_PC_PTR          (*(reg32 *) CYREG_GPIO_PRT4_PC )

#define CapSense_CSD_PORT5_PC_REG          (*(reg32 *) CYREG_GPIO_PRT5_PC )
#define CapSense_CSD_PORT5_PC_PTR          (*(reg32 *) CYREG_GPIO_PRT5_PC )

#define CapSense_CSD_PORT6_PC_REG          (*(reg32 *) CYREG_GPIO_PRT6_PC )
#define CapSense_CSD_PORT6_PC_PTR          (*(reg32 *) CYREG_GPIO_PRT6_PC )


#define CapSense_CSD_PORT0_DR_REG          (*(reg32 *) CYREG_GPIO_PRT0_DR )
#define CapSense_CSD_PORT0_DR_PTR          (*(reg32 *) CYREG_GPIO_PRT0_DR )

#define CapSense_CSD_PORT1_DR_REG          (*(reg32 *) CYREG_GPIO_PRT1_DR )
#define CapSense_CSD_PORT1_DR_PTR          (*(reg32 *) CYREG_GPIO_PRT1_DR )

#define CapSense_CSD_PORT2_DR_REG          (*(reg32 *) CYREG_GPIO_PRT2_DR )
#define CapSense_CSD_PORT2_DR_PTR          (*(reg32 *) CYREG_GPIO_PRT2_DR )

#define CapSense_CSD_PORT3_DR_REG          (*(reg32 *) CYREG_GPIO_PRT3_DR )
#define CapSense_CSD_PORT3_DR_PTR          (*(reg32 *) CYREG_GPIO_PRT3_DR )

#define CapSense_CSD_PORT4_DR_REG          (*(reg32 *) CYREG_GPIO_PRT4_DR )
#define CapSense_CSD_PORT4_DR_PTR          (*(reg32 *) CYREG_GPIO_PRT4_DR )

#define CapSense_CSD_PORT5_DR_REG          (*(reg32 *) CYREG_GPIO_PRT5_DR )
#define CapSense_CSD_PORT5_DR_PTR          (*(reg32 *) CYREG_GPIO_PRT5_DR )

#define CapSense_CSD_PORT6_DR_REG          (*(reg32 *) CYREG_GPIO_PRT6_DR )
#define CapSense_CSD_PORT6_DR_PTR          (*(reg32 *) CYREG_GPIO_PRT6_DR )



#define CapSense_CSD_CMOD_CONNECTION_REG        (*(reg32 *) CapSense_CSD_Cmod__0__HSIOM)
#define CapSense_CSD_CMOD_PORT_PC_REG           (*(reg32 *) CapSense_CSD_Cmod__0__PC)
#define CapSense_CSD_CMOD_PORT_DR_REG           (*(reg32 *) CapSense_CSD_Cmod__0__DR)

#define CapSense_CSD_CTANK_CONNECTION_REG       (*(reg32 *) CapSense_CSD_Csh_tank__0__HSIOM)
#define CapSense_CSD_CTANK_PORT_PC_REG          (*(reg32 *) CapSense_CSD_Csh_tank__0__PC)
#define CapSense_CSD_CTANK_PORT_DR_REG          (*(reg32 *) CapSense_CSD_Csh_tank__0__DR)

/***************************************
*       Register Constants
***************************************/

/* Port configuration defines */
#define CapSense_CSD_CSD_HSIOM_MASK                 (0x0000000FLu)

#define CapSense_CSD_CSD_SENSE_PORT_MODE            (0x00000004Lu)
#define CapSense_CSD_CSD_SHIELD_PORT_MODE           (0x00000005Lu)

#define CapSense_CSD_AMUXA_CONNECTION_MODE          (0x00000006Lu)
#define CapSense_CSD_AMUXB_CONNECTION_MODE          (0x00000007Lu)

#define CapSense_CSD_CSD_PIN_MODE_MASK              (0x00000007Lu)
#define CapSense_CSD_CSD_PIN_DRIVE_MASK             (0x00000001Lu)

#define CapSense_CSD_CSD_PIN_DM_STRONG              (0x00000006Lu)
#define CapSense_CSD_CSD_PIN_DM_HIGH_Z              (0x00000000Lu)

#define CapSense_CSD_CSD_CMOD_CONNECTION_MASK   (uint32)(CapSense_CSD_Cmod__0__HSIOM_MASK)
#define CapSense_CSD_CSD_CMOD_TO_AMUXBUS_A      (uint32)(CapSense_CSD_AMUXA_CONNECTION_MODE << CapSense_CSD_Cmod__0__HSIOM_SHIFT)
#define CapSense_CSD_CSD_CMOD_TO_AMUXBUS_B      (uint32)(CapSense_CSD_AMUXB_CONNECTION_MODE << CapSense_CSD_Cmod__0__HSIOM_SHIFT)

#if(0u != CapSense_CSD_CSH_TANK_ENABLE)
    #define CapSense_CSD_CSD_CTANK_CONNECTION_MASK  (uint32)(CapSense_CSD_Csh_tank__0__HSIOM_MASK)
    #define CapSense_CSD_CSD_CTANK_TO_AMUXBUS_A     (uint32)(CapSense_CSD_AMUXA_CONNECTION_MODE << CapSense_CSD_Csh_tank__0__HSIOM_SHIFT)
    #define CapSense_CSD_CSD_CTANK_TO_AMUXBUS_B     (uint32)(CapSense_CSD_AMUXB_CONNECTION_MODE << CapSense_CSD_Csh_tank__0__HSIOM_SHIFT)
#endif /* (0u != CapSense_CSD_CSH_TANK_ENABLE) */

#define  CapSense_CSD_CSD_CMOD_PC_MASK          (uint32)(CapSense_CSD_CSD_PIN_MODE_MASK <<\
                                                            ((uint32)CapSense_CSD_Cmod__0__SHIFT * CapSense_CSD_PC_PIN_CFG_SIZE))
#define  CapSense_CSD_CMOD_PC_STRONG_MODE       (uint32)(CapSense_CSD_CSD_PIN_DM_STRONG <<\
                                                            ((uint32)CapSense_CSD_Cmod__0__SHIFT * CapSense_CSD_PC_PIN_CFG_SIZE))
#define  CapSense_CSD_CMOD_PC_HIGH_Z_MODE       (uint32)(CapSense_CSD_CSD_PIN_DM_HIGH_Z <<\
                                                            ((uint32)CapSense_CSD_Cmod__0__SHIFT * CapSense_CSD_PC_PIN_CFG_SIZE))

#if(0u != CapSense_CSD_CSH_TANK_ENABLE)
    #define  CapSense_CSD_CSD_CTANK_PC_MASK         (uint32)(CapSense_CSD_CSD_PIN_MODE_MASK <<\
                                                                ((uint32)CapSense_CSD_Csh_tank__0__SHIFT * CapSense_CSD_PC_PIN_CFG_SIZE))
    #define  CapSense_CSD_CTANK_PC_STRONG_MODE      (uint32)(CapSense_CSD_CSD_PIN_DM_STRONG <<\
                                                                ((uint32)CapSense_CSD_Csh_tank__0__SHIFT * CapSense_CSD_PC_PIN_CFG_SIZE))
    #define  CapSense_CSD_CTANK_PC_HIGH_Z_MODE      (uint32)(CapSense_CSD_CSD_PIN_DM_HIGH_Z <<\
                                                                ((uint32)CapSense_CSD_Csh_tank__0__SHIFT * CapSense_CSD_PC_PIN_CFG_SIZE))
#endif /* (0u != CapSense_CSD_CSH_TANK_ENABLE) */

#define  CapSense_CSD_CMOD_DR_VSSIO             (uint32)(CapSense_CSD_Cmod__0__MASK)
#define  CapSense_CSD_CMOD_DR_VDDIO             (0x00000000Lu)
#define  CapSense_CSD_CMOD_DR_MASK              (uint32)(CapSense_CSD_Cmod__0__MASK)

#if(0u != CapSense_CSD_CSH_TANK_ENABLE)
    #define  CapSense_CSD_CTANK_DR_VSSIO            (uint32)(CapSense_CSD_Csh_tank__0__MASK)
    #define  CapSense_CSD_CTANK_DR_VDDIO            (0x00000000Lu)
    #define  CapSense_CSD_CTANK_DR_MASK             (uint32)(CapSense_CSD_Csh_tank__0__MASK)
#endif /* (0u != CapSense_CSD_CSH_TANK_ENABLE) */

#define  CapSense_CSD_CMOD_PIN_NUMBER               (CapSense_CSD_Cmod__0__SHIFT)
#define  CapSense_CSD_CMOD_PRT_NUMBER               (CapSense_CSD_Cmod__0__PORT)

#if(0u != CapSense_CSD_CSH_TANK_ENABLE)
    #define  CapSense_CSD_CTANK_PIN_NUMBER          (CapSense_CSD_Csh_tank__0__SHIFT)
    #define  CapSense_CSD_CTANK_PRT_NUMBER          (CapSense_CSD_Csh_tank__0__PORT)
#endif /* (0u != CapSense_CSD_CSH_TANK_ENABLE) */

/* ID register fields position */
#define CapSense_CSD_CSD_ID_ID__POS                 (0x00u)
#define CapSense_CSD_CSD_ID_REV__POS                (0x10u)

#define CapSense_CSD_CSD_ID_ID                      (0xFFLu << CapSense_CSD_CSD_ID_ID__POS)
#define CapSense_CSD_CSD_ID_REV                     (0xFFLu << CapSense_CSD_CSD_ID_REV__POS)

/* CSD_CONFIG register fields position */
#define CapSense_CSD_CSD_CFG_DSI_SAMPLE_EN_POS      (0x00u)
#define CapSense_CSD_CSD_CFG_SAMPLE_SYNC_POS        (0x01u)
#define CapSense_CSD_CSD_CFG_FILTER_EN_POS          (0x03u)
#define CapSense_CSD_CSD_CFG_PRS_CLEAR_POS          (0x05u)
#define CapSense_CSD_CSD_CFG_PRS_SELECT_POS         (0x06u)
#define CapSense_CSD_CSD_CFG_PRS_12_8_POS           (0x07u)
#define CapSense_CSD_CSD_CFG_DSI_SENSE_EN_POS       (0x08u)
#define CapSense_CSD_CSD_CFG_SHIELD_DELAY_POS       (0x09u)
#define CapSense_CSD_CSD_CFG_SENSE_COMP_BW_POS      (0x0Bu)
#define CapSense_CSD_CSD_CFG_SENSE_EN_POS           (0x0Cu)
#define CapSense_CSD_CSD_CFG_REFBUF_EN_POS          (0x0Du)
#define CapSense_CSD_CSD_CFG_CHARGE_IO_POS          (0x0Eu)
#define CapSense_CSD_CSD_CFG_COMP_PIN_POS           (0x0Fu)
#define CapSense_CSD_CSD_CFG_POLARITY_POS           (0x10u)
#define CapSense_CSD_CSD_CFG_MUTUAL_CAP_POS         (0x12u)
#define CapSense_CSD_CSD_CFG_SENSE_COMP_EN_POS      (0x13u)
#define CapSense_CSD_CSD_CFG_REFBUF_OUTSEL_POS      (0x15u)
#define CapSense_CSD_CSD_CFG_SENSE_INSEL_POS        (0x16u)
#define CapSense_CSD_CSD_REFBUF_DRV_POS             (0x17u)
#define CapSense_CSD_CSD_CFG_DDFTSEL_POS            (0x1Au)
#define CapSense_CSD_CSD_CFG_ADFTEN_POS             (0x1Du)
#define CapSense_CSD_CSD_CFG_DDFTCOMP_POS           (0x1Eu)
#define CapSense_CSD_CSD_CFG_ENABLE_POS             (0x1Fu)

/* CSD_STATUS register fields position */
#define CapSense_CSD_CSD_STAT_CSD_CHARGE_POS        (0x00u)
#define CapSense_CSD_CSD_STAT_CSD_SENSE_POS         (0x01u)
#define CapSense_CSD_CSD_STAT_COMP_OUT_POS          (0x02u)
#define CapSense_CSD_CSD_STAT_SAMPLE_POS            (0x03u)

/* CSD_IDAC control register fields position */
#define CapSense_CSD_CSD_IDAC1_MODE_MASK_POS        (0x08u)
#define CapSense_CSD_CSD_IDAC1_MODE_FIXED_POS       (0x08u)
#define CapSense_CSD_CSD_IDAC1_MODE_VARIABLE_POS    (0x08u)
#define CapSense_CSD_CSD_IDAC1_MODE_DSI_POS         (0x08u)
#define CapSense_CSD_CSD_IDAC1_RANGE_8X_POS         (0x0Au)
#define CapSense_CSD_CSD_IDAC1_DATA_MASK_POS        (0x00u)

#define CapSense_CSD_CSD_IDAC2_MODE_MASK_POS        (0x18u)
#define CapSense_CSD_CSD_IDAC2_MODE_FIXED_POS       (0x18u)
#define CapSense_CSD_CSD_IDAC2_MODE_VARIABLE_POS    (0x18u)
#define CapSense_CSD_CSD_IDAC2_MODE_DSI_POS         (0x18u)
#define CapSense_CSD_CSD_IDAC2_RANGE_8X_POS         (0x1Au)
#define CapSense_CSD_CSD_IDAC2_DATA_MASK_POS        (0x10u)

/* CSD_COUNTER register fields position */
#define CapSense_CSD_CSD_CNT_COUNTER_POS            (0x00u)
#define CapSense_CSD_CSD_CNT_PERIOD_POS             (0x10u)

/* CSD_CONFIRG register definitions */
#define CapSense_CSD_CSD_CFG_DSI_SAMPLE_EN          (0x01Lu << CapSense_CSD_CSD_CFG_DSI_SAMPLE_EN_POS)
#define CapSense_CSD_CSD_CFG_SAMPLE_SYNC            (0x01Lu << CapSense_CSD_CSD_CFG_SAMPLE_SYNC_POS)
#define CapSense_CSD_CSD_CFG_FILTER_EN              (0x01Lu << CapSense_CSD_CSD_CFG_FILTER_EN_POS)
#define CapSense_CSD_CSD_CFG_PRS_CLEAR              (0x01Lu << CapSense_CSD_CSD_CFG_PRS_CLEAR_POS)
#define CapSense_CSD_CSD_CFG_PRS_SELECT             (0x01Lu << CapSense_CSD_CSD_CFG_PRS_SELECT_POS)
#define CapSense_CSD_CSD_CFG_PRS_12_8               (0x01Lu << CapSense_CSD_CSD_CFG_PRS_12_8_POS)
#define CapSense_CSD_CSD_CFG_DSI_SENSE_EN           (0x01Lu << CapSense_CSD_CSD_CFG_DSI_SENSE_EN_POS)
#define CapSense_CSD_CSD_CFG_SHIELD_DELAY_MASK      (0x03Lu << CapSense_CSD_CSD_CFG_SHIELD_DELAY_POS)
#define CapSense_CSD_CSD_CFG_SENSE_COMP_BW          (0x01Lu << CapSense_CSD_CSD_CFG_SENSE_COMP_BW_POS)
#define CapSense_CSD_CSD_CFG_SENSE_EN               (0x01Lu << CapSense_CSD_CSD_CFG_SENSE_EN_POS)
#define CapSense_CSD_CSD_CFG_REFBUF_EN              (0x01Lu << CapSense_CSD_CSD_CFG_REFBUF_EN_POS)
#define CapSense_CSD_CSD_CFG_CHARGE_IO              (0x01Lu << CapSense_CSD_CSD_CFG_CHARGE_IO_POS)
#define CapSense_CSD_CSD_CFG_COMP_PIN_CH2           (0x01Lu << CapSense_CSD_CSD_CFG_COMP_PIN_POS)
#define CapSense_CSD_CSD_CFG_POLARITY_VDDIO         (0x01Lu << CapSense_CSD_CSD_CFG_POLARITY_POS)
#define CapSense_CSD_CSD_CFG_MUTUAL_CAP             (0x01Lu << CapSense_CSD_CSD_CFG_MUTUAL_CAP_POS)
#define CapSense_CSD_CSD_CFG_SENSE_COMP_EN          (0x01Lu << CapSense_CSD_CSD_CFG_SENSE_COMP_EN_POS)
#define CapSense_CSD_CSD_CFG_REFBUF_OUTSEL          (0x01Lu << CapSense_CSD_CSD_CFG_REFBUF_OUTSEL_POS)
#define CapSense_CSD_CSD_CFG_SENSE_INSEL            (0x01Lu << CapSense_CSD_CSD_CFG_SENSE_INSEL_POS)
#define CapSense_CSD_CSD_REFBUF_DRV_MASK            (0x03Lu << CapSense_CSD_CSD_REFBUF_DRV_POS)
#define CapSense_CSD_CSD_REFBUF_DRV_LOW             (0x01Lu << CapSense_CSD_CSD_REFBUF_DRV_POS)
#define CapSense_CSD_CSD_REFBUF_DRV_MEDIUM          (0x02Lu << CapSense_CSD_CSD_REFBUF_DRV_POS)
#define CapSense_CSD_CSD_REFBUF_DRV_HIGH            (0x03Lu << CapSense_CSD_CSD_REFBUF_DRV_POS)
#define CapSense_CSD_CSD_CFG_DDFTSEL_MASK           (0x07Lu << CapSense_CSD_CSD_CFG_DDFTSEL_POS)
#define CapSense_CSD_CSD_CFG_ADFTEN                 (0x01Lu << CapSense_CSD_CSD_CFG_ADFTEN_POS)
#define CapSense_CSD_CSD_CFG_DDFTCOMP_MASK          (0x03Lu << CapSense_CSD_CSD_CFG_DDFTCOMP_POS)
#define CapSense_CSD_CSD_CFG_DDFTCOMP_REFCOMP       (0x01Lu << CapSense_CSD_CSD_CFG_DDFTCOMP_POS)
#define CapSense_CSD_CSD_CFG_DDFTCOMP_SENSECOMP     (0x02Lu << CapSense_CSD_CSD_CFG_DDFTCOMP_POS)
#define CapSense_CSD_CSD_CFG_ENABLE                 (0x01Lu << CapSense_CSD_CSD_CFG_ENABLE_POS)

/* CSD_STATUS register definitions */
#define CapSense_CSD_CSD_STAT_CSD_CHARGE            (0x01Lu << CapSense_CSD_CSD_STAT_CSD_CHARGE_POS)
#define CapSense_CSD_CSD_STAT_CSD_SENSE             (0x01Lu << CapSense_CSD_CSD_STAT_CSD_SENSE_POS)
#define CapSense_CSD_CSD_STAT_COMP_OUT              (0x01Lu << CapSense_CSD_CSD_STAT_COMP_OUT_POS)
#define CapSense_CSD_CSD_STAT_SAMPLE                (0x01Lu << CapSense_CSD_CSD_STAT_SAMPLE_POS)

/* CSD_IDAC control register definitions */
#define CapSense_CSD_CSD_IDAC1_MODE_MASK            (0x03Lu << CapSense_CSD_CSD_IDAC1_MODE_MASK_POS)
#define CapSense_CSD_CSD_IDAC1_MODE_FIXED           (0x01Lu << CapSense_CSD_CSD_IDAC1_MODE_FIXED_POS)
#define CapSense_CSD_CSD_IDAC1_MODE_VARIABLE        (0x02Lu << CapSense_CSD_CSD_IDAC1_MODE_VARIABLE_POS)
#define CapSense_CSD_CSD_IDAC1_MODE_DSI             (0x03Lu << CapSense_CSD_CSD_IDAC1_MODE_DSI_POS)
#define CapSense_CSD_CSD_IDAC1_RANGE_8X             (0x01Lu << CapSense_CSD_CSD_IDAC1_RANGE_8X_POS)
#define CapSense_CSD_CSD_IDAC1_DATA_MASK            (0xFFLu << CapSense_CSD_CSD_IDAC1_DATA_MASK_POS)

#define CapSense_CSD_CSD_IDAC2_MODE_MASK            (0x03Lu << CapSense_CSD_CSD_IDAC2_MODE_MASK_POS)
#define CapSense_CSD_CSD_IDAC2_MODE_FIXED           (0x01Lu << CapSense_CSD_CSD_IDAC2_MODE_FIXED_POS)
#define CapSense_CSD_CSD_IDAC2_MODE_VARIABLE        (0x02Lu << CapSense_CSD_CSD_IDAC2_MODE_VARIABLE_POS)
#define CapSense_CSD_CSD_IDAC2_MODE_DSI             (0x03Lu << CapSense_CSD_CSD_IDAC2_MODE_DSI_POS)
#define CapSense_CSD_CSD_IDAC2_RANGE_8X             (0x01Lu << CapSense_CSD_CSD_IDAC2_RANGE_8X_POS)
#define CapSense_CSD_CSD_IDAC2_DATA_MASK            (0x7FLu << CapSense_CSD_CSD_IDAC2_DATA_MASK_POS)

#define CapSense_CSD_CSD_IDAC2_DATA_OFFSET          (16u)

#define CapSense_CSD_CSD_IDAC1_TRIM_MASK            (0xFFFFFFF0u)
#define CapSense_CSD_CSD_IDAC2_TRIM_MASK            (0xFFFFFF0Fu)

#define CapSense_CSD_CSFLASH_TRIM_IDAC1_MASK        (0x0Fu)
#define CapSense_CSD_CSFLASH_TRIM_IDAC2_MASK        (0xF0)

#define CapSense_CSD_CSD_4B_PWM_MODE_OFFSET         (4u)
#define CapSense_CSD_CSD_4B_PWM_MODE_DEFAULT        (CapSense_CSD_CSD_4B_PWM_MODE << CapSense_CSD_CSD_4B_PWM_MODE_OFFSET)

#define CapSense_CSD_CSD_4B_PWM_COUNT_MASK          (0x0000000Fu)
#define CapSense_CSD_CSD_4B_PWM_MODE_MASK           (0x00000030u)

#define CapSense_CSD_CSD_IDAC_PRECHARGE_CONFIG      (CapSense_CSD_CSD_IDAC1_MODE_FIXED |\
                                                        CapSense_CSD_PRECHARGE_IDAC1_VAL)

/* CSD_COUNTER register definitions */
#define CapSense_CSD_CSD_CNT_COUNTER                (0xFFLu << CapSense_CSD_CSD_CNT_COUNTER_POS )
#define CapSense_CSD_CSD_CNT_PERIOD                 (0xFFLu << CapSense_CSD_CSD_CNT_PERIOD_POS)

#define CapSense_CSD_CSD_PRS_8_BIT                  (0x00000000u)
#define CapSense_CSD_CSD_PRS_12_BIT                 (CapSense_CSD_CSD_CFG_PRS_12_8)
#define CapSense_CSD_PRS_MODE_MASK                  (CapSense_CSD_CSD_CFG_PRS_12_8)

/***************************************
*    Initial Parameter Constants
***************************************/

#if (0u != CapSense_CSD_FILTER_ENABLE)
    #define CapSense_CSD_DEFAULT_FILTER_STATE       (CapSense_CSD_CSD_CFG_FILTER_EN)

#else
    #define CapSense_CSD_DEFAULT_FILTER_STATE       (0u)

#endif /* (CapSense_CSD_PRS_OPTIONS == CapSense_CSD_PRS_8BITS) */

#define CapSense_CSD_DEFAULT_CSD_4B_PWM_CONFIG      (CapSense_CSD_CSD_4B_PWM_MODE_DEFAULT | CapSense_CSD_CSD_4B_PWM_COUNT)

/* Set PRS */
#if (CapSense_CSD_PRS_OPTIONS == CapSense_CSD__PRS_8BITS)
    #define CapSense_CSD_DEFAULT_MODULATION_MODE    CapSense_CSD_CSD_CFG_PRS_SELECT

#elif (CapSense_CSD_PRS_OPTIONS == CapSense_CSD__PRS_12BITS)
    #define CapSense_CSD_DEFAULT_MODULATION_MODE    (CapSense_CSD_CSD_CFG_PRS_12_8 |\
                                                        CapSense_CSD_CSD_CFG_PRS_SELECT)
#else
    #define CapSense_CSD_DEFAULT_MODULATION_MODE    (0u)
#endif /* (CapSense_CSD_PRS_OPTIONS == CapSense_CSD_PRS_8BITS) */

/* Set IDAC ranges */
#if (CapSense_CSD_IDAC1_RANGE_VALUE == CapSense_CSD__IDAC_8X)
    #define CapSense_CSD_DEFAULT_IDAC1_RANGE        CapSense_CSD_CSD_IDAC1_RANGE_8X
    #define CapSense_CSD_DEFAULT_IDAC2_RANGE        CapSense_CSD_CSD_IDAC2_RANGE_8X
#else
    #define CapSense_CSD_DEFAULT_IDAC1_RANGE        (0u)
    #define CapSense_CSD_DEFAULT_IDAC2_RANGE        (0u)
#endif /* (CapSense_CSD_IDAC1_RANGE_VALUE == CapSense_CSD_IDAC_RANGE_8X) */

/* Set IDAC polarity */
#if(CapSense_CSD_IDAC1_POLARITY == CapSense_CSD__IDAC_SINK)

    #define CapSense_CSD_DEFAULT_IDAC_POLARITY      CapSense_CSD_CSD_CFG_POLARITY_VDDIO
    #define CapSense_CSD_CMOD_DR_CONFIG             CapSense_CSD_CMOD_DR_VDDIO
    #define CapSense_CSD_CTANK_DR_CONFIG            CapSense_CSD_CTANK_DR_VDDIO
#else

    #define CapSense_CSD_DEFAULT_IDAC_POLARITY      (0u)
    #define CapSense_CSD_CMOD_DR_CONFIG             CapSense_CSD_CMOD_DR_VSSIO
    #define CapSense_CSD_CTANK_DR_CONFIG            CapSense_CSD_CTANK_DR_VSSIO
#endif /* (CapSense_CSD_IDAC_OPTIONS == CapSense_CSD_IDAC_SINK) */

#define CapSense_CSD_SNS_GROUND_CONNECT             (6u)
#define CapSense_CSD_SNS_HIZANALOG_CONNECT          (0u)

/* Inactive sensors connection configuration */
#if (CapSense_CSD_CONNECT_INACTIVE_SNS == CapSense_CSD__GROUND)
    #define CapSense_CSD_CSD_INACTIVE_CONNECT       (CapSense_CSD_SNS_GROUND_CONNECT)
#else
    #define CapSense_CSD_CSD_INACTIVE_CONNECT       (CapSense_CSD_SNS_HIZANALOG_CONNECT)
#endif /* CapSense_CSD_CONNECT_INACTIVE_SNS == CapSense_CSD__GROUND */

#if(CapSense_CSD_IS_SHIELD_ENABLE)
    #define CapSense_CSD_SHIELD_PORT_NUMBER CapSense_CSD_Shield__PORT
    #define CapSense_CSD_SHIELD_PIN_NUMBER  CapSense_CSD_Shield__SHIFT
#endif /* (CapSense_CSD_IS_SHIELD_ENABLE) */

/* Defining default CSD configuration according to settings in customizer. */
#define CapSense_CSD_DEFAULT_CSD_CONFIG             (CapSense_CSD_DEFAULT_FILTER_STATE |\
                                                         CapSense_CSD_DEFAULT_MODULATION_MODE |\
                                                         CapSense_CSD_CSD_CFG_SENSE_COMP_BW |\
                                                         CapSense_CSD_DEFAULT_IDAC_POLARITY |\
                                                         CapSense_CSD_CSD_CFG_REFBUF_OUTSEL |\
                                                         CapSense_CSD_CSD_REFBUF_DRV_HIGH)

#define CapSense_CSD_CSD_CONFIG_MASK                (CapSense_CSD_CSD_CFG_FILTER_EN |\
                                                         CapSense_CSD_CSD_CFG_PRS_SELECT |\
                                                         CapSense_CSD_CSD_CFG_PRS_12_8 |\
                                                         CapSense_CSD_CSD_CFG_SENSE_COMP_BW |\
                                                         CapSense_CSD_CSD_CFG_REFBUF_EN |\
                                                         CapSense_CSD_CSD_CFG_REFBUF_OUTSEL |\
                                                         CapSense_CSD_CSD_CFG_POLARITY_VDDIO |\
                                                         CapSense_CSD_CSD_CFG_REFBUF_OUTSEL  |\
                                                         CapSense_CSD_CSD_REFBUF_DRV_MASK)


/* Defining the default IDACs configuration according to settings in customizer. */
#if (CapSense_CSD_IDAC_CNT == 1u)
    #define CapSense_CSD_DEFAULT_CSD_IDAC_CONFIG    (CapSense_CSD_CSD_IDAC1_MODE_VARIABLE |\
                                                             CapSense_CSD_DEFAULT_IDAC1_RANGE)
#else
    #define CapSense_CSD_DEFAULT_CSD_IDAC_CONFIG    (CapSense_CSD_CSD_IDAC1_MODE_VARIABLE |\
                                                             CapSense_CSD_CSD_IDAC2_MODE_FIXED |\
                                                             CapSense_CSD_DEFAULT_IDAC1_RANGE |\
                                                             CapSense_CSD_DEFAULT_IDAC2_RANGE)
#endif /* (CapSense_CSD_IDAC_CNT == 1u) */

/* Defining mask intended for clearing bits related to pre-charging options. */
#define CapSense_CSD_PRECHARGE_CONFIG_MASK          (CapSense_CSD_CSD_CFG_REFBUF_EN |\
                                                         CapSense_CSD_CSD_CFG_CHARGE_IO |\
                                                         CapSense_CSD_CSD_CFG_COMP_PIN_CH2  |\
                                                         CapSense_CSD_CSD_CFG_REFBUF_OUTSEL)

/* Cmod the precharge mode configuration */
#if(CapSense_CSD_CMOD_PREGARGE_OPTION == CapSense_CSD__CAPPRVREF)

    #define CapSense_CSD_CMOD_PRECHARGE_CONFIG      (CapSense_CSD_CSD_CFG_REFBUF_EN |\
                                                         CapSense_CSD_CSD_CFG_COMP_PIN_CH2)

#else

    #define CapSense_CSD_CMOD_PRECHARGE_CONFIG      (CapSense_CSD_CSD_CFG_REFBUF_OUTSEL |\
                                                         CapSense_CSD_CSD_CFG_REFBUF_EN |\
                                                         CapSense_CSD_CSD_CFG_CHARGE_IO)

#endif /* (CapSense_CSD_CMOD_PREGARGE_OPTION == CapSense_CSD__CAPPRVREF) */

/* Ctank the precharge mode configuration */
#if(CapSense_CSD_CSH_TANK_PREGARGE_OPTION == CapSense_CSD__CAPPRVREF)

    #if(0u != CapSense_CSD_IS_SHIELD_ENABLE)
        #define  CapSense_CSD_CTANK_PRECHARGE_CONFIG    (CapSense_CSD_CSD_CFG_REFBUF_EN |\
                                                             CapSense_CSD_CSD_CFG_PRS_CLEAR |\
                                                             CapSense_CSD_CSD_CFG_REFBUF_OUTSEL)
    #else
        #define  CapSense_CSD_CTANK_PRECHARGE_CONFIG    (CapSense_CSD_CSD_CFG_REFBUF_OUTSEL |\
                                                             CapSense_CSD_CSD_CFG_PRS_CLEAR)
    #endif /* (0u != CapSense_CSD_IS_SHIELD_ENABLE) */

#else

    #define  CapSense_CSD_CTANK_PRECHARGE_CONFIG    (CapSense_CSD_CSD_CFG_REFBUF_OUTSEL |\
                                                         CapSense_CSD_CSD_CFG_REFBUF_EN |\
                                                         CapSense_CSD_CSD_CFG_CHARGE_IO |\
                                                         CapSense_CSD_CSD_CFG_PRS_CLEAR |\
                                                         CapSense_CSD_CSD_CFG_COMP_PIN_CH2)
#endif /* (CapSense_CSD_CSH_TANK_PREGARGE_OPTION == CapSense_CSD__CAPPRIOBUF) */

#define CapSense_CSD_MAX_UINT_8                     (0xFFu)
#define CapSense_CSD_MAX_UINT_16                    (0xFFFFu)
#define CapSense_CSD_MAX_UINT_32                    (0xFFFFFFFFLu)

/***************************************
*     Vars with External Linkage
***************************************/
/* SmartSense functions */
#if (CapSense_CSD_TUNING_METHOD == CapSense_CSD__TUNING_AUTO)
    extern uint8 CapSense_CSD_lowLevelTuningDone;
    extern uint8 CapSense_CSD_scanSpeedTbl[((CapSense_CSD_TOTAL_SENSOR_COUNT - 1u) / 8u) + 1u];
    extern void CapSense_CSD_AutoTune(void);
#endif /* (CapSense_CSD_TUNING_METHOD == CapSense_CSD__TUNING_AUTO) */

#if(CapSense_CSD_PRS_OPTIONS != CapSense_CSD__PRS_NONE)
    extern uint8 CapSense_CSD_prescalersTuningDone;
#endif /* (CapSense_CSD_PRS_OPTIONS == CapSense_CSD__PRS_NONE) */

/* Global software variables */
extern volatile uint8 CapSense_CSD_csdStatusVar;
extern volatile uint8 CapSense_CSD_sensorIndex;
extern uint16 CapSense_CSD_sensorRaw[CapSense_CSD_TOTAL_SENSOR_COUNT];
extern uint8 CapSense_CSD_unscannedSnsDriveMode[CapSense_CSD_PORT_PIN_CONFIG_TBL_ZISE];
extern uint8 CapSense_CSD_sensorEnableMaskBackup[CapSense_CSD_TOTAL_SENSOR_MASK];
extern uint8 CapSense_CSD_sensorEnableMask[CapSense_CSD_TOTAL_SENSOR_MASK];

#if ((CapSense_CSD_TUNING_METHOD != CapSense_CSD__TUNING_NONE) || (0u != CapSense_CSD_AUTOCALIBRATION_ENABLE))
    extern uint8 CapSense_CSD_modulationIDAC[CapSense_CSD_TOTAL_SENSOR_COUNT];
    extern uint8 CapSense_CSD_compensationIDAC[CapSense_CSD_TOTAL_SENSOR_COUNT];
#else
    extern const uint8 CapSense_CSD_modulationIDAC[CapSense_CSD_TOTAL_SENSOR_COUNT];
    extern const uint8 CapSense_CSD_compensationIDAC[CapSense_CSD_TOTAL_SENSOR_COUNT];
#endif /* ((CapSense_CSD_TUNING_METHOD != CapSense_CSD__TUNING_NONE) || (0u != CapSense_CSD_AUTOCALIBRATION_ENABLE)) */

#if (CapSense_CSD_TUNING_METHOD != CapSense_CSD__TUNING_NONE)
    extern uint32 CapSense_CSD_widgetResolution[CapSense_CSD_RESOLUTIONS_TBL_SIZE];
    #if (0u != CapSense_CSD_MULTIPLE_FREQUENCY_SET)
        extern uint8 CapSense_CSD_senseClkDividerVal[CapSense_CSD_TOTAL_SCANSLOT_COUNT];
        extern uint8 CapSense_CSD_sampleClkDividerVal[CapSense_CSD_TOTAL_SCANSLOT_COUNT];
    #else
        extern uint8 CapSense_CSD_senseClkDividerVal;
        extern uint8 CapSense_CSD_sampleClkDividerVal;
    #endif /* (0u != CapSense_CSD_MULTIPLE_FREQUENCY_SET) */
#else
    extern const uint32 CapSense_CSD_widgetResolution[CapSense_CSD_RESOLUTIONS_TBL_SIZE];
    #if (0u != CapSense_CSD_MULTIPLE_FREQUENCY_SET)
        extern const uint8 CapSense_CSD_senseClkDividerVal[CapSense_CSD_TOTAL_SCANSLOT_COUNT];
        extern const uint8 CapSense_CSD_sampleClkDividerVal[CapSense_CSD_TOTAL_SCANSLOT_COUNT];
    #else
        extern const uint8 CapSense_CSD_senseClkDividerVal;
        extern const uint8 CapSense_CSD_sampleClkDividerVal;
    #endif /* (0u != CapSense_CSD_MULTIPLE_FREQUENCY_SET) */
#endif /* (CapSense_CSD_TUNING_METHOD != CapSense_CSD__TUNING_NONE)  */

extern const uint8 CapSense_CSD_widgetNumber[CapSense_CSD_TOTAL_SENSOR_COUNT];

extern reg32* const CapSense_CSD_prtSelTbl[CapSense_CSD_CFG_REG_TBL_SIZE];
extern reg32* const CapSense_CSD_prtCfgTbl[CapSense_CSD_CFG_REG_TBL_SIZE];
extern reg32* const CapSense_CSD_prtDRTbl[CapSense_CSD_CFG_REG_TBL_SIZE];
extern reg32 * CapSense_CSD_pcTable[CapSense_CSD_PORT_PIN_CONFIG_TBL_ZISE];

extern const uint8  CapSense_CSD_portTable[CapSense_CSD_PORT_PIN_CONFIG_TBL_ZISE];
extern const uint32 CapSense_CSD_maskTable[CapSense_CSD_PORT_PIN_CONFIG_TBL_ZISE];
extern const uint8  CapSense_CSD_pinShiftTbl[CapSense_CSD_PORT_PIN_CONFIG_TBL_ZISE];

#if (0u != CapSense_CSD_INDEX_TABLE_SIZE)
extern const uint8 CYCODE CapSense_CSD_indexTable[CapSense_CSD_INDEX_TABLE_SIZE];
#endif /* (0u != CapSense_CSD_INDEX_TABLE_SIZE)) */

/***************************************************
*    Obsolete Names (will be removed in future)
***************************************************/
#define  CapSense_CSD_PrescalersTuningDone         CapSense_CSD_prescalersTuningDone
#define  CapSense_CSD_SensorRaw                    CapSense_CSD_sensorRaw
#define  CapSense_CSD_PRSResolutionTbl             CapSense_CSD_prsResolutionTbl
#define  CapSense_CSD_SensorEnableMask             CapSense_CSD_sensorEnableMask
#define  CapSense_CSD_Clk1DividerVal               CapSense_CSD_senseClkDividerVal
#define  CapSense_CSD_Clk2DividerVal               CapSense_CSD_sampleClkDividerVal
#define  CapSense_CSD_PrtSelTbl                    CapSense_CSD_prtSelTbl
#define  CapSense_CSD_PrtCfgTbl                    CapSense_CSD_prtCfgTbl
#define  CapSense_CSD_PrtDRTbl                     CapSense_CSD_prtDRTbl
#define  CapSense_CSD_idac1Settings                CapSense_CSD_modulationIDAC
#define  CapSense_CSD_idac2Settings                CapSense_CSD_compensationIDAC

#endif /* CY_CAPSENSE_CSD_CapSense_CSD_H */


 /* [] END OF FILE */
