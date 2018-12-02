/*******************************************************************************
* File Name: BLUE.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_BLUE_H) /* Pins BLUE_H */
#define CY_PINS_BLUE_H

#include "cytypes.h"
#include "cyfitter.h"
#include "BLUE_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} BLUE_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   BLUE_Read(void);
void    BLUE_Write(uint8 value);
uint8   BLUE_ReadDataReg(void);
#if defined(BLUE__PC) || (CY_PSOC4_4200L) 
    void    BLUE_SetDriveMode(uint8 mode);
#endif
void    BLUE_SetInterruptMode(uint16 position, uint16 mode);
uint8   BLUE_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void BLUE_Sleep(void); 
void BLUE_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(BLUE__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define BLUE_DRIVE_MODE_BITS        (3)
    #define BLUE_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - BLUE_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the BLUE_SetDriveMode() function.
         *  @{
         */
        #define BLUE_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define BLUE_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define BLUE_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define BLUE_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define BLUE_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define BLUE_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define BLUE_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define BLUE_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define BLUE_MASK               BLUE__MASK
#define BLUE_SHIFT              BLUE__SHIFT
#define BLUE_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in BLUE_SetInterruptMode() function.
     *  @{
     */
        #define BLUE_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define BLUE_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define BLUE_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define BLUE_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(BLUE__SIO)
    #define BLUE_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(BLUE__PC) && (CY_PSOC4_4200L)
    #define BLUE_USBIO_ENABLE               ((uint32)0x80000000u)
    #define BLUE_USBIO_DISABLE              ((uint32)(~BLUE_USBIO_ENABLE))
    #define BLUE_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define BLUE_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define BLUE_USBIO_ENTER_SLEEP          ((uint32)((1u << BLUE_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << BLUE_USBIO_SUSPEND_DEL_SHIFT)))
    #define BLUE_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << BLUE_USBIO_SUSPEND_SHIFT)))
    #define BLUE_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << BLUE_USBIO_SUSPEND_DEL_SHIFT)))
    #define BLUE_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(BLUE__PC)
    /* Port Configuration */
    #define BLUE_PC                 (* (reg32 *) BLUE__PC)
#endif
/* Pin State */
#define BLUE_PS                     (* (reg32 *) BLUE__PS)
/* Data Register */
#define BLUE_DR                     (* (reg32 *) BLUE__DR)
/* Input Buffer Disable Override */
#define BLUE_INP_DIS                (* (reg32 *) BLUE__PC2)

/* Interrupt configuration Registers */
#define BLUE_INTCFG                 (* (reg32 *) BLUE__INTCFG)
#define BLUE_INTSTAT                (* (reg32 *) BLUE__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define BLUE_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(BLUE__SIO)
    #define BLUE_SIO_REG            (* (reg32 *) BLUE__SIO)
#endif /* (BLUE__SIO_CFG) */

/* USBIO registers */
#if !defined(BLUE__PC) && (CY_PSOC4_4200L)
    #define BLUE_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define BLUE_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define BLUE_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define BLUE_DRIVE_MODE_SHIFT       (0x00u)
#define BLUE_DRIVE_MODE_MASK        (0x07u << BLUE_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins BLUE_H */


/* [] END OF FILE */
