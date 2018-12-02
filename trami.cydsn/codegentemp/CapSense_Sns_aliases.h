/*******************************************************************************
* File Name: CapSense_Sns.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_CapSense_Sns_ALIASES_H) /* Pins CapSense_Sns_ALIASES_H */
#define CY_PINS_CapSense_Sns_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define CapSense_Sns_0			(CapSense_Sns__0__PC)
#define CapSense_Sns_0_PS		(CapSense_Sns__0__PS)
#define CapSense_Sns_0_PC		(CapSense_Sns__0__PC)
#define CapSense_Sns_0_DR		(CapSense_Sns__0__DR)
#define CapSense_Sns_0_SHIFT	(CapSense_Sns__0__SHIFT)
#define CapSense_Sns_0_INTR	((uint16)((uint16)0x0003u << (CapSense_Sns__0__SHIFT*2u)))

#define CapSense_Sns_1			(CapSense_Sns__1__PC)
#define CapSense_Sns_1_PS		(CapSense_Sns__1__PS)
#define CapSense_Sns_1_PC		(CapSense_Sns__1__PC)
#define CapSense_Sns_1_DR		(CapSense_Sns__1__DR)
#define CapSense_Sns_1_SHIFT	(CapSense_Sns__1__SHIFT)
#define CapSense_Sns_1_INTR	((uint16)((uint16)0x0003u << (CapSense_Sns__1__SHIFT*2u)))

#define CapSense_Sns_2			(CapSense_Sns__2__PC)
#define CapSense_Sns_2_PS		(CapSense_Sns__2__PS)
#define CapSense_Sns_2_PC		(CapSense_Sns__2__PC)
#define CapSense_Sns_2_DR		(CapSense_Sns__2__DR)
#define CapSense_Sns_2_SHIFT	(CapSense_Sns__2__SHIFT)
#define CapSense_Sns_2_INTR	((uint16)((uint16)0x0003u << (CapSense_Sns__2__SHIFT*2u)))

#define CapSense_Sns_3			(CapSense_Sns__3__PC)
#define CapSense_Sns_3_PS		(CapSense_Sns__3__PS)
#define CapSense_Sns_3_PC		(CapSense_Sns__3__PC)
#define CapSense_Sns_3_DR		(CapSense_Sns__3__DR)
#define CapSense_Sns_3_SHIFT	(CapSense_Sns__3__SHIFT)
#define CapSense_Sns_3_INTR	((uint16)((uint16)0x0003u << (CapSense_Sns__3__SHIFT*2u)))

#define CapSense_Sns_4			(CapSense_Sns__4__PC)
#define CapSense_Sns_4_PS		(CapSense_Sns__4__PS)
#define CapSense_Sns_4_PC		(CapSense_Sns__4__PC)
#define CapSense_Sns_4_DR		(CapSense_Sns__4__DR)
#define CapSense_Sns_4_SHIFT	(CapSense_Sns__4__SHIFT)
#define CapSense_Sns_4_INTR	((uint16)((uint16)0x0003u << (CapSense_Sns__4__SHIFT*2u)))

#define CapSense_Sns_INTR_ALL	 ((uint16)(CapSense_Sns_0_INTR| CapSense_Sns_1_INTR| CapSense_Sns_2_INTR| CapSense_Sns_3_INTR| CapSense_Sns_4_INTR))
#define CapSense_Sns_LinearSlider0_e0__LS			(CapSense_Sns__LinearSlider0_e0__LS__PC)
#define CapSense_Sns_LinearSlider0_e0__LS_PS		(CapSense_Sns__LinearSlider0_e0__LS__PS)
#define CapSense_Sns_LinearSlider0_e0__LS_PC		(CapSense_Sns__LinearSlider0_e0__LS__PC)
#define CapSense_Sns_LinearSlider0_e0__LS_DR		(CapSense_Sns__LinearSlider0_e0__LS__DR)
#define CapSense_Sns_LinearSlider0_e0__LS_SHIFT	(CapSense_Sns__LinearSlider0_e0__LS__SHIFT)
#define CapSense_Sns_LinearSlider0_e0__LS_INTR	((uint16)((uint16)0x0003u << (CapSense_Sns__0__SHIFT*2u)))

#define CapSense_Sns_LinearSlider0_e1__LS			(CapSense_Sns__LinearSlider0_e1__LS__PC)
#define CapSense_Sns_LinearSlider0_e1__LS_PS		(CapSense_Sns__LinearSlider0_e1__LS__PS)
#define CapSense_Sns_LinearSlider0_e1__LS_PC		(CapSense_Sns__LinearSlider0_e1__LS__PC)
#define CapSense_Sns_LinearSlider0_e1__LS_DR		(CapSense_Sns__LinearSlider0_e1__LS__DR)
#define CapSense_Sns_LinearSlider0_e1__LS_SHIFT	(CapSense_Sns__LinearSlider0_e1__LS__SHIFT)
#define CapSense_Sns_LinearSlider0_e1__LS_INTR	((uint16)((uint16)0x0003u << (CapSense_Sns__1__SHIFT*2u)))

#define CapSense_Sns_LinearSlider0_e2__LS			(CapSense_Sns__LinearSlider0_e2__LS__PC)
#define CapSense_Sns_LinearSlider0_e2__LS_PS		(CapSense_Sns__LinearSlider0_e2__LS__PS)
#define CapSense_Sns_LinearSlider0_e2__LS_PC		(CapSense_Sns__LinearSlider0_e2__LS__PC)
#define CapSense_Sns_LinearSlider0_e2__LS_DR		(CapSense_Sns__LinearSlider0_e2__LS__DR)
#define CapSense_Sns_LinearSlider0_e2__LS_SHIFT	(CapSense_Sns__LinearSlider0_e2__LS__SHIFT)
#define CapSense_Sns_LinearSlider0_e2__LS_INTR	((uint16)((uint16)0x0003u << (CapSense_Sns__2__SHIFT*2u)))

#define CapSense_Sns_LinearSlider0_e3__LS			(CapSense_Sns__LinearSlider0_e3__LS__PC)
#define CapSense_Sns_LinearSlider0_e3__LS_PS		(CapSense_Sns__LinearSlider0_e3__LS__PS)
#define CapSense_Sns_LinearSlider0_e3__LS_PC		(CapSense_Sns__LinearSlider0_e3__LS__PC)
#define CapSense_Sns_LinearSlider0_e3__LS_DR		(CapSense_Sns__LinearSlider0_e3__LS__DR)
#define CapSense_Sns_LinearSlider0_e3__LS_SHIFT	(CapSense_Sns__LinearSlider0_e3__LS__SHIFT)
#define CapSense_Sns_LinearSlider0_e3__LS_INTR	((uint16)((uint16)0x0003u << (CapSense_Sns__3__SHIFT*2u)))

#define CapSense_Sns_LinearSlider0_e4__LS			(CapSense_Sns__LinearSlider0_e4__LS__PC)
#define CapSense_Sns_LinearSlider0_e4__LS_PS		(CapSense_Sns__LinearSlider0_e4__LS__PS)
#define CapSense_Sns_LinearSlider0_e4__LS_PC		(CapSense_Sns__LinearSlider0_e4__LS__PC)
#define CapSense_Sns_LinearSlider0_e4__LS_DR		(CapSense_Sns__LinearSlider0_e4__LS__DR)
#define CapSense_Sns_LinearSlider0_e4__LS_SHIFT	(CapSense_Sns__LinearSlider0_e4__LS__SHIFT)
#define CapSense_Sns_LinearSlider0_e4__LS_INTR	((uint16)((uint16)0x0003u << (CapSense_Sns__4__SHIFT*2u)))


#endif /* End Pins CapSense_Sns_ALIASES_H */


/* [] END OF FILE */
