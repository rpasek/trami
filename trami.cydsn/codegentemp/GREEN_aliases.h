/*******************************************************************************
* File Name: GREEN.h  
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

#if !defined(CY_PINS_GREEN_ALIASES_H) /* Pins GREEN_ALIASES_H */
#define CY_PINS_GREEN_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define GREEN_0			(GREEN__0__PC)
#define GREEN_0_PS		(GREEN__0__PS)
#define GREEN_0_PC		(GREEN__0__PC)
#define GREEN_0_DR		(GREEN__0__DR)
#define GREEN_0_SHIFT	(GREEN__0__SHIFT)
#define GREEN_0_INTR	((uint16)((uint16)0x0003u << (GREEN__0__SHIFT*2u)))

#define GREEN_INTR_ALL	 ((uint16)(GREEN_0_INTR))


#endif /* End Pins GREEN_ALIASES_H */


/* [] END OF FILE */
