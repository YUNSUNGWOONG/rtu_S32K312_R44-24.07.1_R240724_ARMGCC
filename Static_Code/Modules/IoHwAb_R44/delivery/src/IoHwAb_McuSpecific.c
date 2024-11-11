/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: IoHwAb_McuSpecific.c                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : APIs implementation for IoHwAb module                         **
**              IoHwAb_McuSpecificControlIBE                                  **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.6.4     08-Dec-2023  YongEun.Lee       #CP44-3041                        **
** 1.3.0.1   30-Jun-2022  KhaLN1            #CP44-365                         **
** 1.0.0     04-Dec-2020  YangJin.Kim       R40-Redmine #26992                **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb_DigDir.h"
#include "IoHwAb_Config.h"
#include "Rte_Type.h"
#include "HwResource.h"
#include "Rte_IoHwAb.h"
#include "SchM_IoHwAb.h"

#if defined(IOHWAB_MCAL_FREESCALE_MPC560XB)
#include "Reg_eSys_SIUL.h"
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/*polyspace:begin<MISRA-C:10.3:Not a defect:Justify with annotations> No Impact of this rule violation*/
/*polyspace:begin<MISRA-C:11.3:Not a defect:Justify with annotations> No Impact of this rule violation*/
/*polyspace:begin<RTE: IDP : Not a defect : No Action Planned >  */
/*polyspace:begin<RTE: NIV : Not a defect : No Action Planned >  */
/*******************************************************************************
** Function Name        : IoHwAb_McuSpecificControlIBE                        **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service updates the PortPin's IBE value        **
**                        for Bolero (leackage current issues)                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : PortGroup - IOHWAB_PORT_X [X is A~H]                **
**                        PinConfig - 0x0000~0xFFFF (ex. 0x0003 -> pin0, pin1)**
**                        Level     - 1(Set) or 0(Clear)                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Result                                              **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : none                       **
**                        Function(s) invoked    : none                       **
*******************************************************************************/
/* @Trace: SRS_BSW_00423 */
/* @Trace: SWR_IOHWAB_901_001 SWR_IOHWAB_702_001 */
/* @Trace: IoHwAb_SUD_API_112 */
#if defined(IOHWAB_MCAL_FREESCALE_MPC560XB)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_McuSpecificControlIBE(IoHwAb_IndexType PortGroup,
IoHwAb_IndexType PinConfig, IoHwAb_LevelType Level )
{
  IoHwAb_IndexType LucIdx = 0U;
  Std_ReturnType LddError = (Std_ReturnType)E_OK;
  IoHwAb_IndexType LucPinConfig  = 0U;
  IoHwAb_IndexType LucPinMaskSet = 0xFFFFU;  
   

  #if HWRESOURCE_PACKAGE(HWRESOURCE_LQFP64)
    if (PortGroup == IOHWAB_PORT_C)
    {
      LucPinMaskSet = 0x07FFU;
    }
    else if ( (PortGroup == IOHWAB_PORT_D) || (PortGroup == IOHWAB_PORT_E) ||
              (PortGroup == IOHWAB_PORT_F) || (PortGroup == IOHWAB_PORT_G) ||
              (PortGroup == IOHWAB_PORT_H) || (PortGroup == IOHWAB_PORT_I) ||
              (PortGroup == IOHWAB_PORT_J) )
    {
       LddError = (Std_ReturnType)E_NOT_OK;      
    }

  #elif HWRESOURCE_PACKAGE(HWRESOURCE_LQFP100)
    if (PortGroup == IOHWAB_PORT_E)
    {
      LucPinMaskSet = 0x1FFFU;
    }
    else if (PortGroup == IOHWAB_PORT_H)
    {
      LucPinMaskSet = 0x0600U;
    }
    else if ( (PortGroup == IOHWAB_PORT_F) || (PortGroup == IOHWAB_PORT_G) ||
              (PortGroup == IOHWAB_PORT_I) || (PortGroup == IOHWAB_PORT_J) )
    {
       LddError = (Std_ReturnType)E_NOT_OK;      
    }
  #elif HWRESOURCE_PACKAGE(HWRESOURCE_LQFP144)
    if (PortGroup == IOHWAB_PORT_H)
    {
      LucPinMaskSet = 0x07FFU;
    }
    else if ( (PortGroup == IOHWAB_PORT_I) || (PortGroup == IOHWAB_PORT_J) )
    {
       LddError = (Std_ReturnType)E_NOT_OK;      
    }
  #endif

  SchM_Enter_IoHwAb_IoHwAbProtection();
  if((Std_ReturnType)LddError != (Std_ReturnType)E_OK)
  {
    SchM_Exit_IoHwAb_IoHwAbProtection();
    #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
      (uint8)IOHWAB_MCUSPECIFIC_SID, (uint8)IOHWAB_E_DET_BUSY);
    #endif /* (IOHWAB_DEV_ERROR_DETECT == STD_ON) */
    #if (IOHWAB_USE_DEM_EVENT == STD_ON)
    Dem_ReportErrorStatus(IOHWAB_E_WRONG_STATE, DEM_EVENT_STATUS_FAILED);
    #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
  }
  else
  {
    
    LucPinConfig = PinConfig & LucPinMaskSet;  
    for (LucIdx = 0U; LucIdx < 16U ; LucIdx++)
    {
      if ( (LucPinConfig & 0x01U) != 0U)
      {
        if ( Level == 1U)
        {
           REG_BIT_SET16(SIUL_PCR(PortGroup + LucIdx), SIUL_PCR_IBE);
        }
        else
        {
           REG_BIT_CLEAR16(SIUL_PCR(PortGroup + LucIdx), SIUL_PCR_IBE);
        }
      }
      LucPinConfig = LucPinConfig >> 1;
    }

    SchM_Exit_IoHwAb_IoHwAbProtection();  
  }  
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*polyspace:end<MISRA-C:10.3:Not a defect:Justify with annotations> No Impact of this rule violation*/
/*polyspace:end<MISRA-C:11.3:Not a defect:Justify with annotations> No Impact of this rule violation*/
/*polyspace:end<RTE: IDP : Not a defect : No Action Planned >  */
/*polyspace:end<RTE: NIV : Not a defect : No Action Planned >  */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
