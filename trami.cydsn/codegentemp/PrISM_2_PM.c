/*******************************************************************************
* File Name: PrISM_2_PM.c
* Version 2.20
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality of the PrISM component
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "PrISM_2.h"


/***************************************
* Local data allocation
***************************************/
static PrISM_2_BACKUP_STRUCT  PrISM_2_backup = 
{
    /* enableState */
    0u,
    /* cr */
    #if(!PrISM_2_PULSE_TYPE_HARDCODED)
       (((PrISM_2_GREATERTHAN_OR_EQUAL == PrISM_2_COMPARE0) ? \
                                                PrISM_2_CTRL_COMPARE_TYPE0_GREATER_THAN_OR_EQUAL : 0u) |
        ((PrISM_2_GREATERTHAN_OR_EQUAL == PrISM_2_COMPARE1) ? \
                                                PrISM_2_CTRL_COMPARE_TYPE1_GREATER_THAN_OR_EQUAL : 0u)),
    #endif /* End PrISM_2_PULSE_TYPE_HARDCODED */
    /* seed */    
    PrISM_2_SEED,
    /* seed_copy */    
    PrISM_2_SEED,
    /* polynom */
    PrISM_2_POLYNOM,
    #if(CY_UDB_V0)
        /* density0 */
        PrISM_2_DENSITY0,
        /* density1 */
        PrISM_2_DENSITY1,
    #endif /*End CY_UDB_V0*/
};


/*******************************************************************************
* Function Name: PrISM_2_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*  
* Parameters:  
*  None.
*
* Return: 
*  None.
*
* Global Variables:
*  PrISM_2_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void PrISM_2_SaveConfig(void) 
{
    #if (CY_UDB_V0)
        #if(!PrISM_2_PULSE_TYPE_HARDCODED)
            PrISM_2_backup.cr = PrISM_2_CONTROL_REG;
        #endif /* End PrISM_2_PULSE_TYPE_HARDCODED */
        PrISM_2_backup.seed = PrISM_2_ReadSeed();
        PrISM_2_backup.seed_copy = CY_GET_REG8(PrISM_2_SEED_COPY_PTR);
        PrISM_2_backup.polynom = PrISM_2_ReadPolynomial();
        PrISM_2_backup.density0 = PrISM_2_ReadPulse0();
        PrISM_2_backup.density1 = PrISM_2_ReadPulse1();
    #else /* CY_UDB_V1 */
        #if(!PrISM_2_PULSE_TYPE_HARDCODED)
            PrISM_2_backup.cr = PrISM_2_CONTROL_REG;
        #endif /* End PrISM_2_PULSE_TYPE_HARDCODED */
        PrISM_2_backup.seed = PrISM_2_ReadSeed();
        PrISM_2_backup.seed_copy = CY_GET_REG8(PrISM_2_SEED_COPY_PTR);
        PrISM_2_backup.polynom = PrISM_2_ReadPolynomial();
    #endif  /* CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: PrISM_2_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  None.
*
* Return: 
*  None.
*
* Global Variables:
*  PrISM_2_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void PrISM_2_RestoreConfig(void) 
{
    #if (CY_UDB_V0)
    
        uint8 enableInterrupts;
        
        #if(!PrISM_2_PULSE_TYPE_HARDCODED)
            PrISM_2_CONTROL_REG = PrISM_2_backup.cr;
        #endif /* End PrISM_2_PULSE_TYPE_HARDCODED */

        CY_SET_REG8(PrISM_2_SEED_COPY_PTR, PrISM_2_backup.seed_copy);
        CY_SET_REG8(PrISM_2_SEED_PTR, PrISM_2_backup.seed);
        PrISM_2_WritePolynomial(PrISM_2_backup.polynom);
        PrISM_2_WritePulse0(PrISM_2_backup.density0);
        PrISM_2_WritePulse1(PrISM_2_backup.density1);
        
        enableInterrupts = CyEnterCriticalSection();
        /* Set FIFO0_CLR bit to use FIFO0 as a simple one-byte buffer*/
        CY_SET_REG8(PrISM_2_AUX_CONTROL_PTR, 
                        CY_GET_REG8(PrISM_2_AUX_CONTROL_PTR) | PrISM_2_FIFO0_CLR);
        CyExitCriticalSection(enableInterrupts);

    #else   /* CY_UDB_V1 */

        #if(!PrISM_2_PULSE_TYPE_HARDCODED)
            PrISM_2_CONTROL_REG = PrISM_2_backup.cr;
        #endif /* End PrISM_2_PULSE_TYPE_HARDCODED */

        CY_SET_REG8(PrISM_2_SEED_COPY_PTR, PrISM_2_backup.seed_copy);
        CY_SET_REG8(PrISM_2_SEED_PTR, PrISM_2_backup.seed);
        PrISM_2_WritePolynomial(PrISM_2_backup.polynom);
    
    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: PrISM_2_Sleep
********************************************************************************
*
* Summary:
*  Stops and saves the user configuration
*  
* Parameters:  
*  None.
*
* Return: 
*  None.
*
* Global Variables:
*  PrISM_2_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void PrISM_2_Sleep(void) 
{
    #if(!PrISM_2_PULSE_TYPE_HARDCODED)
        if((PrISM_2_CONTROL_REG & PrISM_2_CTRL_ENABLE) != 0u) 
        {
            PrISM_2_backup.enableState = 1u;
        }
        else
        {
            PrISM_2_backup.enableState = 0u;
        }
    #endif /* End PrISM_2_PULSE_TYPE_HARDCODED */
    PrISM_2_Stop();
    PrISM_2_SaveConfig();
}


/*******************************************************************************
* Function Name: PrISM_2_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  None.
*
* Return: 
*  None.
*
* Global Variables:
*  PrISM_2_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void PrISM_2_Wakeup(void) 
{
    PrISM_2_RestoreConfig();
    if(PrISM_2_backup.enableState != 0u)
    {
        PrISM_2_Enable();
    } 
}


/* [] END OF FILE */
