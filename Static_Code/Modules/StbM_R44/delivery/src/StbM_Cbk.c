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
**  SRC-MODULE: StbM_Cbk.c                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Synchronized Time-Base Manager Module                 **
**                                                                            **
**  PURPOSE   : Provision of call back functions and their functionality.     **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision        Date                By              Description            **
********************************************************************************
** 1.0.3           21-Jul-2022         ThuanVT         JIRA BUGCLASSIC-152,   **
**												  	   R44-Redmine #633	      **
** 1.0.1           15-Sep-2021         SHKim           #20096                 **
** 1.0.0     	   16-Dec-2020         SHKim           Initial Version        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/* StbM module header */
#include "StbM_Cbk.h"

#include "StbM_Ram.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : StbM_TimerCallback                                  **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Call back function that call by GPT interrupt       **
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
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                                StbM_GaaTimeBaseValue                       **
**                                StbM_GaaNotificationValue                   **
**                        Function(s) invoked : None                          **
*******************************************************************************/
#define STBM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, STBM_CODE) StbM_TimerCallback(void)
{
  P2VAR(StbM_TimeBaseValueType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseValue;
  P2CONST(StbM_NotificationConfigType, AUTOMATIC, STBM_APPL_DATA)lpConfig;
  P2VAR(StbM_NotificationValueType, AUTOMATIC, STBM_APPL_DATA)lpValue;

  if(STBM_TRUE == StbM_GaaCallBackParameterValue.enCbk)   
  {
    lpConfig = & StbM_GaaNotificationConfig[StbM_GaaCallBackParameterValue.usId]; 
    /* polyspace +1 RTE:IDP [Not a defect:Low] "StbM_GaaTimeBaseConfig is verified and generated by Generator Tool" */
    lpTimeBaseValue = & StbM_GaaTimeBaseValue[lpConfig->ddTimeBaseId]; /*polyspace MISRA-C:18.1 [Not a defect:Low] "StbM_GaaNotificationConfig is verified and generated by Generator Tool"*/
    lpValue = & StbM_GaaNotificationValue[StbM_GaaCallBackParameterValue.usId]; 
    
    /* @Trace: SWS_StbM_00271 */
    /* @Trace: StbM_SUD_API_581 */
#if(STBM_NUMBER_NOTIFICATION_CUSTOMER_CONFIGURED > 0)
    (void)(*(lpConfig->pCallback))((StbM_TimeDiffType)STBM_ZERO); 
#endif
    /* Clear request callback function */  
    lpValue->blStartTimer = STBM_FALSE;
    lpTimeBaseValue->blStartTimerCount = 
                              lpTimeBaseValue->blStartTimerCount - STBM_ONE;
    /* Clear flag */
    StbM_GaaCallBackParameterValue.enCbk = STBM_FALSE;
  }
  else
  {
    /* Do nothing */
  }
} /* End of StbM_TimerCallback(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
