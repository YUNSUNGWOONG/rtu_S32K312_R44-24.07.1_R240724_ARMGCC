/*******************************************************************************
**                                                                            **
**  (C) 2022 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Fota_MacUpdateMgr.c                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR FOTA                                                  **
**                                                                            **
**  PURPOSE   : Provide definition of FOTA function                           **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
** 1.0.0     23-Oct-2023   Djlee        Initial version                       **
********************************************************************************
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Fota_Types.h"
#include "Fota_IntFunc.h"
#include "Fota_Cfg.h"
#include "Fota_Globals.h"
#include "Fota_User_Callouts.h"
#include "Fota_MacUpdateMgr.h"

/* polyspace-begin MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation" */
/*******************************************************************************
**                      Macros                                                **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

static Fota_MacUpdateStatType   rue_MacUpdateState    = FOTA_MACUPDATE_IDLE;
static Fota_JobResultType       rue_MacUpdateResult   = FOTA_JOB_FAILED;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define Fota_START_SEC_CODE
#include "Fota_MemMap.h"

static FUNC(void, FOTA_CODE)Fota_MacUpdateEnd_Cbk(void);
static FUNC(void, FOTA_CODE)Fota_MacUpdateErr_Cbk(void);


/*******************************************************************************
** Function Name        : Fota_GetMacUpdateState                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get Mac Update state                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : none                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
FUNC(Fota_MacUpdateStatType, FOTA_CODE) Fota_GetMacUpdateState(void)
{
	/* @Trace: FOTA_SUD_API_00199 */
	return rue_MacUpdateState;
}

/*******************************************************************************
** Function Name        : Fota_MacUpdateRequest                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Request Mac Update operation                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
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
** Remarks              : Global Variable(s)  : rue_MacUpdateState            **
**                                              rue_MacUpdateResult           **
**                                                                            **
**                        Function(s) invoked :  None                         **
**                                                                            **
*******************************************************************************/

/* polyspace-begin MISRA-C3:2.7 [Justified:Low] "Parameter depends on the Configuration." */
FUNC(Std_ReturnType, FOTA_CODE) Fota_MacUpdateRequest(void)
/* polyspace-end MISRA-C3:2.7 [Justified:Low] "Parameter depends on the Configuration." */
{
	/* @Trace: FOTA_SUD_API_00041 */
	Std_ReturnType RetVal=E_NOT_OK;

    if(rue_MacUpdateState==FOTA_MACUPDATE_IDLE)
    {
		rue_MacUpdateResult   = FOTA_JOB_PENDING;
		rue_MacUpdateState    = FOTA_MACUPDATE_START;
		RetVal = E_OK;
    }

	return RetVal;
}

/*******************************************************************************
** Function Name        : Fota_MacUpdateResult                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : result check area sync operation                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : none                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/

FUNC(Fota_JobResultType, FOTA_CODE) Fota_MacUpdateResult(void)
{
	/* @Trace: FOTA_SUD_API_00042 */
	return rue_MacUpdateResult;
}

/*******************************************************************************
** Function Name        : Fota_MacUpdateEnd_Cbk                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : End result save                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : none                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/

static FUNC(void, FOTA_CODE) Fota_MacUpdateEnd_Cbk(void)
{
	/* @Trace: FOTA_SUD_API_00151 */
	rue_MacUpdateState  = FOTA_MACUPDATE_IDLE;
	rue_MacUpdateResult = FOTA_JOB_OK;
}

/*******************************************************************************
** Function Name        : Fota_MacUpdateErr_Cbk                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Err result save                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
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
** Remarks              : Global Variable(s)  : rue_MacUpdateState            **
**                                              rue_MacUpdateResult           **
**                                                                            **
**                        Function(s) invoked :  None                         **
**                                                                            **
*******************************************************************************/

static FUNC(void, FOTA_CODE) Fota_MacUpdateErr_Cbk(void)
{
	/* @Trace: FOTA_SUD_API_00152 */
	rue_MacUpdateState  = FOTA_MACUPDATE_IDLE;
	rue_MacUpdateResult = FOTA_JOB_FAILED;
}

/*******************************************************************************
** Function Name        : Fota_MacUpdateMain                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Area Sync Main Function                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : none                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
FUNC(void, FOTA_CODE) Fota_MacUpdateMain(void)
{
	Fota_JobResultType macUpdateResult;

    switch(rue_MacUpdateState)
    {
      case FOTA_MACUPDATE_IDLE:


      break;

      case FOTA_MACUPDATE_START:
	  	/* @Trace: FOTA_SUD_API_00150 */
        /* polyspace-begin DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the configuration." */
        /* polyspace-begin MISRA-C3:10.5 [Not a defect:Low] "No Impact of this rule violation" */
        macUpdateResult=(Fota_JobResultType)Fota_SecureBootMacUpdate();

    	  if(macUpdateResult==FOTA_JOB_OK)
    	  {
    		  rue_MacUpdateState=FOTA_MACUPDATE_END;
    	  }
    	  else if(macUpdateResult==FOTA_JOB_FAILED)
    	  {
    		  rue_MacUpdateState=FOTA_MACUPDATE_ERR;
    	  }
    	  else
    	  {
    	    /* Pending */
    	  }
        /* polyspace-end DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the configuration." */
        /* polyspace-end MISRA-C3:10.5 [Not a defect:Low] "No Impact of this rule violation" */

      break;
      case FOTA_MACUPDATE_END:
		  /* @Trace: FOTA_SUD_API_00262 */
    	  Fota_MacUpdateEnd_Cbk();

      break;

      case FOTA_MACUPDATE_ERR:
      default:
		  /* @Trace: FOTA_SUD_API_00263 */
    	  Fota_MacUpdateErr_Cbk();

      break;
    }
}

#define Fota_STOP_SEC_CODE
#include "Fota_MemMap.h"

/* polyspace-end MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
