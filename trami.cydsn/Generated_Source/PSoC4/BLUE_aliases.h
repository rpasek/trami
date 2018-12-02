/*******************************************************************************
* File Name: BLUE.h  
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

#if !defined(CY_PINS_BLUE_ALIASES_H) /* Pins BLUE_ALIASES_H */
#define CY_PINS_BLUE_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define BLUE_0			(BLUE__0__PC)
#define BLUE_0_PS		(BLUE__0__PS)
#define BLUE_0_PC		(BLUE__0__PC)
#define BLUE_0_DR		(BLUE__0__DR)
#define BLUE_0_SHIFT	(BLUE__0__SHIFT)
#define BLUE_0_INTR	((uint16)((uint16)0x0003u << (BLUE__0__SHIFT*2u)))

#define BLUE_INTR_ALL	 ((uint16)(BLUE_0_INTR))


#endif /* End Pins BLUE_ALIASES_H */


/* [] END OF FILE */
