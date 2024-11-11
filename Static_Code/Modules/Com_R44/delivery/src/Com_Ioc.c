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
**  SRC-MODULE: Com_Ioc.c                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Com Module                                            **
**                                                                            **
**  PURPOSE   : Provision of Com multicore feature relevant to IOC solution   **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By          Description                            **
********************************************************************************
** 1.1.4.0  11-Oct-2022    HaoTA4      CP44-772                               **
*******************************************************************************/


/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Com.h"          /* Com header file */
#include "Com_Main.h"     /* Com Main header file */
#include "SchM_Com.h"     /* SchM Com header file */
#include "Com_Error.h"    /* Com Error header file */
#include "Com_Ioc.h"
#if(COM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"          /* Det header file */
#endif
#if (STD_ON == COM_MULTI_CORE_SUPPORT)
#include "Os.h"
#endif /* STD_ON == COM_MULTI_CORE_SUPPORT */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/*******************************************************************************
** Function Name        : Com_DirectTrigger                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function invokes the configured Notify         **
**                        function. Only support for multicore                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same data.                    **
**                        Reentrant for different data.                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaSigNotifCbk,        **
**                             Com_GaaSigErrorCbk, Com_GaaInvNotifCbk,        **
**                                                 Com_GaaSigNotifCbkMask,    **
**                             Com_GaaSigErrorCbkMask, Com_GaaInvNotifCbkMask,**
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#if (STD_ON == COM_MULTI_CORE_SUPPORT)

#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, COM_CODE) Com_DirectTrigger(void)
{
  /* @Trace: Com_SUD_API_00649 */
  #if(COM_TX_IPDU_COUNT > COM_MACRO_ZERO)
  uint16 LulCount;
  CoreIdType CoreId;

  if(Com_GddComStatus != COM_UNINIT)
  {
    /* @Trace: Com_SUD_API_00650 */
    /* create mask of core id */
    CoreId = GetCoreID();
    /* Trigger all TxIPdu when its flag is set */
    /* @Trace: Com_SUD_API_00651 */
    /* @Trace: Com_SUD_API_00652 */
    for(LulCount=COM_ZERO; LulCount<COM_TX_IPDU_COUNT; LulCount++)
    {
      if(CoreId == Com_GaaTxIpduCorePosition[LulCount])
      {
        if(COM_ONE == (Com_GaaTxIpduTransmitFlag[LulCount]))
        {
          /* @Trace: Com_SUD_API_00653 */
          /* Invoke Com_Transmit function */
          Com_Transmit(LulCount);
          /* Clear flag */
          SchM_Enter_Com_SWITCH_CORE_PROTECTION_AREA();
          Com_GaaTxIpduTransmitFlag[LulCount] = COM_ZERO;
          SchM_Exit_Com_SWITCH_CORE_PROTECTION_AREA();
        }
      }
    }
  }
  #endif /* (COM_TX_IPDU_COUNT > COM_MACRO_ZERO) */
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
