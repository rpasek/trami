/*******************************************************************************
* File Name: PrISM_Clock.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_PrISM_Clock_H)
#define CY_CLOCK_PrISM_Clock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void PrISM_Clock_StartEx(uint32 alignClkDiv);
#define PrISM_Clock_Start() \
    PrISM_Clock_StartEx(PrISM_Clock__PA_DIV_ID)

#else

void PrISM_Clock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void PrISM_Clock_Stop(void);

void PrISM_Clock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 PrISM_Clock_GetDividerRegister(void);
uint8  PrISM_Clock_GetFractionalDividerRegister(void);

#define PrISM_Clock_Enable()                         PrISM_Clock_Start()
#define PrISM_Clock_Disable()                        PrISM_Clock_Stop()
#define PrISM_Clock_SetDividerRegister(clkDivider, reset)  \
    PrISM_Clock_SetFractionalDividerRegister((clkDivider), 0u)
#define PrISM_Clock_SetDivider(clkDivider)           PrISM_Clock_SetDividerRegister((clkDivider), 1u)
#define PrISM_Clock_SetDividerValue(clkDivider)      PrISM_Clock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define PrISM_Clock_DIV_ID     PrISM_Clock__DIV_ID

#define PrISM_Clock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define PrISM_Clock_CTRL_REG   (*(reg32 *)PrISM_Clock__CTRL_REGISTER)
#define PrISM_Clock_DIV_REG    (*(reg32 *)PrISM_Clock__DIV_REGISTER)

#define PrISM_Clock_CMD_DIV_SHIFT          (0u)
#define PrISM_Clock_CMD_PA_DIV_SHIFT       (8u)
#define PrISM_Clock_CMD_DISABLE_SHIFT      (30u)
#define PrISM_Clock_CMD_ENABLE_SHIFT       (31u)

#define PrISM_Clock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << PrISM_Clock_CMD_DISABLE_SHIFT))
#define PrISM_Clock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << PrISM_Clock_CMD_ENABLE_SHIFT))

#define PrISM_Clock_DIV_FRAC_MASK  (0x000000F8u)
#define PrISM_Clock_DIV_FRAC_SHIFT (3u)
#define PrISM_Clock_DIV_INT_MASK   (0xFFFFFF00u)
#define PrISM_Clock_DIV_INT_SHIFT  (8u)

#else 

#define PrISM_Clock_DIV_REG        (*(reg32 *)PrISM_Clock__REGISTER)
#define PrISM_Clock_ENABLE_REG     PrISM_Clock_DIV_REG
#define PrISM_Clock_DIV_FRAC_MASK  PrISM_Clock__FRAC_MASK
#define PrISM_Clock_DIV_FRAC_SHIFT (16u)
#define PrISM_Clock_DIV_INT_MASK   PrISM_Clock__DIVIDER_MASK
#define PrISM_Clock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_PrISM_Clock_H) */

/* [] END OF FILE */
