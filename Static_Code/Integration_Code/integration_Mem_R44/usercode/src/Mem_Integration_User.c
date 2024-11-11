/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**                                                                            **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Mem_Integration_User.c                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR MemStack Integration Module                           **
**                                                                            **
**  PURPOSE   : Provision of Version information                              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: yes                                       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:11.4,20.9 [Justified:Low] "This is nessasary for access the H/W Register, not a defect" */

/*******************************************************************************
**                     Include Section                                        **
*******************************************************************************/
#include "HwResource.h"
#include "Mem_Integration.h"
#include "Mem_Integration_User.h"

#if (MEM_FEE_USED == STD_ON)
#include "Fee.h"
#endif


#if (MEM_FLS_USED == STD_ON)
#include "Fls.h"
#endif

#define NVM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Mem_PostFeeInitCallback                             **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : This function is invoked before Fee is initialized  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
FUNC(void, NVM_CODE) Mem_PostFeeInitCallback(void)
{
  /* USER CODE */
}


/*******************************************************************************
** Function Name        : Mem_Cypress_IllegalStateCallback                    **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : This function handles exception when Fee module     **
**                        faileds to initialize                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Only Cypress MCU                                    **
*******************************************************************************/
#if (HWRESOURCE_VENDOR(HWRESOURCE_CYPRESS))
FUNC(boolean, NVM_CODE) Mem_Cypress_IllegalStateCallback(void)
{
  static volatile uint8 numOfRetry = 1;
  boolean retVal = MEM_FALSE;

  /* There is no workaround other than erasing the internal EEPROM
   *
   * Please refer to Fee/Fls manual */
  if (numOfRetry > 0U)
  {
    numOfRetry--;
    /* Write the code for Fee illegal State, if App needs to do something */   
  }
  else
  {
    /* Write the code for Fee illegal State, if App needs to do something */ 
  }

  return retVal;
}
#endif

/*******************************************************************************
** Function Name        : Mem_Infineon_IllegalStateCallback                   **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Callback function which will be called              **
**                        when the FEE reaches the illegal state.             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Only Infineon MCU                                   **
*******************************************************************************/
#if (HWRESOURCE_VENDOR(HWRESOURCE_INFINEON))
FUNC(void, NVM_CODE) Mem_Infineon_IllegalStateCallback (void)
{
  /* 1. During Initialisation of the FEE driver, FEE reads the state pages 
   *    and the content of the same leads to an invalid / illegal state. 
   *    Eg: Valid State Page is missing in both of the FEE sectors. 
   *     - The only mechanism for recovering from this Illegal State is by 
   *       erasing of the DF_EEPROM area. The user can enable FEE to erase both 
   *       the sectors (not an API request) by configuring FeeEraseAllEnable to 
   *       TRUE, such that the automatic erase of both sectors is executed. 
   *
   * 2. FEE reaches illegal state if it detects a virgin (all 0x00) flash 
   *    (DF_EEPROM) when FeeVirginFlashIllegalState is configured as true and
   *    FeeEraseAllEnable is configured as false
   *
   * For more information, please refer Fee User Manual 
   */

   /* Write the code for Fee illegal State, if App needs to do something */
   {

   }
}
#endif

/*******************************************************************************
** Function Name        : Mem_ErrorCalloutHandler                             **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : This function is user callback function             **
**                        User should fill this function for dealling with    **
**                        WorkFlash Non-Correctable ECC Error.                **
**                        It is called in the Fee module after detecting ECC  **
**                        and Fls_Fault_Handling is involed                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : 1. Fault Struct for workflash NC-ECC should be set  **
**                        2. ISR of Fault Struct should be set                **
**                        3. Fls Fault Struct should be configured            **
**                        4. Fls FlsConfigSet_0-FlsDedErrorNotification       **
**                           should be configured                             **
**                        5. Fee FeeErrorCalloutFunction should be configured **
**                                                                            **
** Remarks              : Only Traveo-II MCU                                  **
**                                                                            **
*******************************************************************************/
#if (\
  (defined(HWRESOURCE_CYT2BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT2BXX)) || \
  (defined(HWRESOURCE_CYT3BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT3BXX)) || \
  (defined(HWRESOURCE_CYT4BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT4BXX)) || \
  (defined(HWRESOURCE_CYT6BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT6BXX)))
FUNC(void, NVM_CODE) Mem_ErrorCalloutHandler (uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId)
{
#if defined(FEE_E_2BIT_ECC_ERROR_OCCURRED)  
  /* Only Ded Error is not correctable, needs recovery */
  if (ErrorId == FEE_E_2BIT_ECC_ERROR_OCCURRED)
  {
    /* 
     * It's depend on user's strategy 
     * Following the TVII_FEE_material_V1.3.pdf, Fee_Init can recovery the ECC Block
     * because of Recycling strategy. So, Recommendation is SW Reset for Invoke Mem Stack Initialization  
     */
  }
#else
  (void)ErrorId;
#endif

  /* Unused Parameter */
  (void)ModuleId;
  (void)InstanceId;
  (void)ApiId;
}
#endif
#define NVM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA-C3:11.4,20.9 [Justified:Low] "This is nessasary for access the H/W Register, not a defect" */

/*******************************************************************************
**                         End of File                                        **
*******************************************************************************/
