/*******************************************************************************
* File Name: RED.h  
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

#if !defined(CY_PINS_RED_ALIASES_H) /* Pins RED_ALIASES_H */
#define CY_PINS_RED_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define RED_0			(RED__0__PC)
#define RED_0_PS		(RED__0__PS)
#define RED_0_PC		(RED__0__PC)
#define RED_0_DR		(RED__0__DR)
#define RED_0_SHIFT	(RED__0__SHIFT)
#define RED_0_INTR	((uint16)((uint16)0x0003u << (RED__0__SHIFT*2u)))

#define RED_INTR_ALL	 ((uint16)(RED_0_INTR))


#endif /* End Pins RED_ALIASES_H */


/* [] END OF FILE */
