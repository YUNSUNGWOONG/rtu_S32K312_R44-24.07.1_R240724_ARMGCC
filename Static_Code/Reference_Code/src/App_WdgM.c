/*******************************************************************************
**  (C) 2014, 2020 Hyundai AUTRON                                                   **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: App_WdgM.c                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR WdgM                                                  **
**                                                                            **
**  PURPOSE   : Sample code for testing WdgM module                           **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 2.0.1     26-Sep-2020   TienVD         Update memory section               **
** 2.0.0     15-May-2020   TienVD         Add more test cases                 **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Rte_SWC_WdgMTest.h"
#include "EcuM_Ram.h"
#include "WdgM_IntTypes.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

#define WDGMTEST_CHECK_ALIVESUPERVISION       (0)
#define WDGMTEST_CHECK_DEADLINESUPERVISION    (1)
#define WDGMTEST_CHECK_LOCALSUPERVISION       (2)
#define WDGMTEST_CHECK_PERFORMRESET           (3)
#define WDGMTEST_CHECK_OFFMODE                (4)
#define WDGMTEST_CHECK_REPORT_DET             (5)
#define WDGMTEST_CHECK_SUPERVISION_INACTIVE   (6)

/*******************************************************************************
**                       Global Data                                          **
*******************************************************************************/
#define SWC_WdgMTest_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "SWC_WdgMTest_MemMap.h"
WdgM_GlobalStatusType WdgMTest_GddGlobalStatus;
WdgM_SupervisedEntityIdType WdgMTest_GddExpiredSEID;
WdgM_LocalStatusType WdgMTest_GddLocalStatus;
uint8 WdgMTest_StateCheck = 0;
#define SWC_WdgMTest_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "SWC_WdgMTest_MemMap.h"

#define SWC_WdgMTest_START_SEC_VAR_INIT_UNSPECIFIED
#include "SWC_WdgMTest_MemMap.h"
WdgM_ModeType WdgMTest_CurrentMode = 0;
#define SWC_WdgMTest_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "SWC_WdgMTest_MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/*******************************************************************************
** Function Name        : RE_WdgMTest                                         **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This service provides Test method for WdgM behavior **
**                        using Supervised Entity as expired                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Rte_Start should be initialized                     **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        WdgMTest_GblStart,                                  **
**                        WdgMTest_GblExpireWdg,                              **
**                        WdgMTest_GddGlobalStatus                            ** 
**                                                                            **
**                        Function(s) invoked :                               **
**                        Rte_Call_WdgM_API_R_SetMode,                        **
**                        Rte_Call_SE_WdgMTest_CheckpointReached,             **
**                        Rte_Call_WdgM_API_R_GetGlobalStatus,                **
**                        Rte_Call_WdgM_API_R_GetFirstExpiredSEID             **
*******************************************************************************/
#define SWC_WdgMTest_START_SEC_CODE
#include "SWC_WdgMTest_MemMap.h"

void RE_WdgMTest(void)
{
  if (WdgMTest_StateCheck == WDGMTEST_CHECK_ALIVESUPERVISION)
  {
    if (WdgMTest_CurrentMode != 1)
    {
      Rte_Call_SWC_WdgMTest_WdgM_GlobalSupervision_SetMode(1);
      WdgMTest_CurrentMode = 1;
    }
      /* WdgMAliveSupervision0 */
      Rte_Call_SWC_WdgMTest_SE_Init_CP_AS0_CheckpointReached();
  }

}
#define SWC_WdgMTest_STOP_SEC_CODE
#include "SWC_WdgMTest_MemMap.h"


/*******************************************************************************
** Function Name        : RE_WdgMTestGlobalMode                               **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This service provides check method for              **
**                        WdgM Global Supervision Status                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Rte_Start should be initialized                     **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        WdgMTest_GddGlobalStatus,                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Rte_Call_WdgM_API_R_GetGlobalStatus,                **
**                        Rte_Call_WdgM_API_R_GetFirstExpiredSEID             **
*******************************************************************************/
#define SWC_WdgMTest_START_SEC_CODE
#include "SWC_WdgMTest_MemMap.h"
void RE_WdgMTestGlobalMode(void)
{
  Rte_Call_WdgM_GlobalSupervision_GetGlobalStatus(&WdgMTest_GddGlobalStatus);

  switch (WdgMTest_GddGlobalStatus)
  {
  case WDGM_GLOBAL_STATUS_OK:
    break;
  case WDGM_GLOBAL_STATUS_FAILED:
    break;
  case WDGM_GLOBAL_STATUS_EXPIRED:
    Rte_Call_WdgM_GlobalSupervision_GetFirstExpiredSEID(&WdgMTest_GddExpiredSEID);
    break;
  case WDGM_GLOBAL_STATUS_STOPPED:
    break;
  }
}
#define SWC_WdgMTest_STOP_SEC_CODE
#include "SWC_WdgMTest_MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
