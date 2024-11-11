/*******************************************************************************
**                                                                            **
**  (C) 2023 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Os_EccConfig.c                                                **
**                                                                            **
**  TARGET    : s32k31x                                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR Platform Integration Code                             **
**                                                                            **
**  PURPOSE   : Set Register configuration for handling RAM ECC error         **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: yes                                       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date           By            Description                         **
********************************************************************************
** 1.1.0      7-Apr-2023    HG.Kim        Redmine # 39577                     **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_EccConfig.h"
#include "Os_Imp_Cfg.h"
#include "Os_Arch_Except.h"
#include "Os_Definition.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/*******************************************************************************
** Function Name      : OsImp_EnterConfig                                     **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : FCCU Enters Config State                              **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : void                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) : None                             **
**                                                                            **
**                      Function(s) invoked : None                            **
*******************************************************************************/
FUNC(void, OS_CODE)OsImp_EnterConfig(void)
{
  while(OS_FCCU_CTRL.B.OPS == OS_INPROGRESS)
  {
  }
  /* Unlock OP1 */
  OS_FCCU_CTRLK.U = OS_UNLOCK_OP1;
  /* Run OP1 */
  OS_FCCU_CTRL.U = 0x00000201U;
  while(OS_FCCU_CTRL.B.OPS == OS_INPROGRESS)
  {
  }

  /* FCCU Configuration */
  /* NCF 2 : RAM Ecc, NCF 3 : Flash Ecc */
  /* fault on that channel causes FCCU to assert the rst_sfunc_b signal : NCF 2,3 ON */
  OS_FCCU_NCF_CFG0.U = 0x0000000CU;
  /* NMI Enable : NCF 2,3 ON */
  OS_FCCU_NMI_EN0.U = 0x0000000CU;
  /* Fault Enable : NCF 2,3 ON */
  OS_FCCU_NCF_E0.U = 0x0000000CU;
  /* -------------------*/

  /* Prevent Switching to Alarm State */
  /* Only USE Normal, Config, Fault State on FCCU */
	OS_FCCU_NCF_TOE.U = 0x00000000U;

  if(OS_FCCU_CTRL.B.OPS == OS_ABORTED)
  {
    /* Unlock to clear FCCU configuration */
	  OS_FCCU_NCFK.U = OS_UNLOCK_NCF_S;

    /* Reset FCCU */ 
	  OS_FCCU_NCF_S.U = 0xFFFFFFFFU;
    OS_FCCU_NCF_CFG0.U = 0x00000000U;
    OS_FCCU_NMI_EN0.U = 0x00000000U;
    OS_FCCU_NCF_E0.U = 0x00000000U;
  }
}
/*******************************************************************************
** Function Name      : OsImp_EnterNormal                                     **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : FCCU Enters Normal State                              **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : void                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) : None                             **
**                                                                            **
**                      Function(s) invoked : None                            **
*******************************************************************************/
FUNC(void, OS_CODE)OsImp_EnterNormal(void)
{
  boolean NOT_ABORTED = OS_TRUE;

  while(NOT_ABORTED == OS_TRUE)
  {
    while(OS_FCCU_CTRL.B.OPS == OS_INPROGRESS)
    {
    }
    /* Unlock OP2 */
    OS_FCCU_CTRLK.U = OS_UNLOCK_OP2;
    /* Run OP2 */
    OS_FCCU_CTRL.U = 0x00000202U;
    while(OS_FCCU_CTRL.B.OPS == OS_INPROGRESS)
    {
    }
    NOT_ABORTED = OS_FALSE;
    if(OS_FCCU_CTRL.B.OPS == OS_ABORTED)
    {
      NOT_ABORTED = OS_TRUE;
    }
  }

  if(OS_FCCU_CTRL.B.OPS == OS_SUCCESSFUL)
  {
    /* Temporarily lock the configuration */
	  OS_FCCU_TRANS_LOCK.U = OS_LOCK_TRANSKEY;
    /* Permanently lock the configuration */
	  OS_FCCU_PERMNT_LOCK.U = OS_LOCK_PERMNTKEY;
  }
}
/*******************************************************************************
** Function Name      : OsImp_Init                                            **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : Set FCCU configuration for handling RAM ECC error     **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : void                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) : None                             **
**                                                                            **
** Function(s) invoked : OsImp_EnterConfig(), OsImp_EnterNormal()             **
*******************************************************************************/
FUNC(void, OS_CODE)OsImp_Init(void)
{
  /* NCF_S flag clear */
  /* Unlock to clear FCCU configuration */
  OS_FCCU_NCFK.U = OS_UNLOCK_NCF_S;
  /* Clear FCCU Flag */
  OS_FCCU_NCF_S.U = 0xFFFFFFFFU;
  OS_FCCU_CFG_TO.U = 0x00000007U;

  /* Enter CONFIG State from NORMAL State */
  OS_FCCU_TRANS_LOCK.U = OS_UNLOCK_TRANSKEY;
  switch(OS_FCCU_STAT.B.STATUS)
  {
    case OS_NORMAL_STATE:
    	OsImp_EnterConfig();
    	break;
    case OS_ALARM_STATE:
    case OS_FAULT_STATE:
    	/* This case does not occur due to FCCU Flag Initialization */
    	break;
    case OS_CONFIG_STATE:
    	/* Nothing */
    	break;
    default:
    	/* Reserver */
    	break;
  }

  /* Enter NORMAL State from CONFIG State */
  switch(OS_FCCU_STAT.B.STATUS)
    {
      case OS_NORMAL_STATE:
      	OS_FCCU_TRANS_LOCK.U = OS_LOCK_TRANSKEY;
      	OS_FCCU_PERMNT_LOCK.U = OS_UNLOCK_TRANSKEY;
      	break;
      case OS_ALARM_STATE:
      case OS_FAULT_STATE:
      	/* This case does not occur due to FCCU Flag Initialization */
      	break;
      case OS_CONFIG_STATE:
      	OsImp_EnterNormal();
      	break;
      default:
      	/* Reserver */
      	break;
    }
}

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
