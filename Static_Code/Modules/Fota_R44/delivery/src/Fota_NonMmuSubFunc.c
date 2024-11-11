/*******************************************************************************
**                                                                            **
**  (C) 2022 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Fota_NonMmuSubFunc.c                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR FOTA                                                  **
**                                                                            **
**  PURPOSE   :                                                               **
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
** 1.0.0     20-Feb-2023   DJ Lee        #                                    **
********************************************************************************
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Fota.h"
#include "Fota_NonMmuSubFunc.h"
#include "Fota_MagicKeyMgr.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/



/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Fota_IsDualPartitionSwUnit                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to get the Index of Software Unit based on **
**                        SwUnitMemoryArea (in Dual Memory Case)              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : ecuSwUnit                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType retVal                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Fota_Gast_SwUnitTable         **
**                                                                            **
**                        Function(s) invoked :       Fota_GetSwUnitIdByLabel **
**                                                                            **
*******************************************************************************/

FUNC(Std_ReturnType,FOTA_CODE) Fota_IsDualPartitionSwUnit(
		  VAR(uint16,AUTOMATIC) ecuSwUnit)
{
	VAR(Std_ReturnType,AUTOMATIC) retVal=E_NOT_OK;
	VAR(uint8,AUTOMATIC)          rub_ProgID;
	/* @Trace: FOTA_SUD_API_00056 */
	retVal = E_NOT_OK;

	if(Fota_GetSwUnitIdByLabel(ecuSwUnit, &rub_ProgID)==E_OK)
	{
		if((Fota_Gast_SwUnitTable[rub_ProgID].SoftwareType == FOTA_RTSW_PARTA_TYPE)||
		   (Fota_Gast_SwUnitTable[rub_ProgID].SoftwareType == FOTA_RTSW_PARTB_TYPE))
		{
			retVal = E_OK;
		}
	}

    return retVal;
}

/*******************************************************************************
** Function Name        : Fota_GetSwUnitIdByPartition                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to get the Index of Software Unit based on **
**                        Partition                                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : Partition                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : SwUnitIdx                                           **
**                                                                            **
** Return parameter     : Std_ReturnType retVal                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                                                                            **
**                        Function(s) invoked :                               **
**                                          Fota_GetSoftwareModuleBlkBySwType **
**                                                                            **
*******************************************************************************/

FUNC(Std_ReturnType,FOTA_CODE) Fota_GetSwUnitIdByPartition(
		VAR(Fota_PartitionType,AUTOMATIC) Partition,
		P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) SwUnitIdx)
{
	VAR(Std_ReturnType,AUTOMATIC) retVal=E_NOT_OK;

	retVal = E_NOT_OK;
	/* @Trace: FOTA_SUD_API_00058 */
	if(Partition==FOTA_PARTITION_A)
	{
		retVal = Fota_GetSoftwareModuleBlkBySwType(FOTA_RTSW_PARTA_TYPE,SwUnitIdx);
	}
	else if(Partition==FOTA_PARTITION_B)
	{
		retVal = Fota_GetSoftwareModuleBlkBySwType(FOTA_RTSW_PARTB_TYPE,SwUnitIdx);
	}
	else
	{

	}

    return retVal;
}

/*******************************************************************************
** Function Name        : Fota_GetTargetPartition                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to get the target partition info           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pTargetPartition                                    **
**                                                                            **
** Return parameter     : Std_ReturnType retVal                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                                                                            **
**                        Function(s) invoked :       Fota_GetActivePartition **
**                                                                            **
*******************************************************************************/

FUNC(Std_ReturnType,FOTA_CODE) Fota_GetTargetPartition(
		P2VAR(Fota_PartitionType, AUTOMATIC, FOTA_PRIVATE_DATA) pTargetPartition)
{
	VAR(Std_ReturnType,AUTOMATIC) retVal=E_NOT_OK;
	VAR(Fota_PartitionType,AUTOMATIC) ActPart;
	/* @Trace: FOTA_SUD_API_00055 */
	retVal = E_NOT_OK;

	if(Fota_GetActivePartition(&ActPart)==E_OK)
	{
		if(ActPart==FOTA_PARTITION_A)
		{
			*pTargetPartition = FOTA_PARTITION_B;
			retVal = E_OK;
		}
		else if(ActPart==FOTA_PARTITION_B)
		{
			*pTargetPartition = FOTA_PARTITION_A;
			retVal = E_OK;
		}
		else
		{
/* UNKNOWN OR NO RTSW */
#if (FOTA_MODE==FOTA_FBL_MODE)
			*pTargetPartition = FOTA_PARTITION_A;
			retVal = E_OK;
#else

#endif

		}
	}
    return retVal;
}

/*******************************************************************************
** Function Name        : Fota_GetActivePartition                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to get the active parition info            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pActivePartition                                    **
**                                                                            **
** Return parameter     : Std_ReturnType retVal                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                                                                            **
**                        Function(s) invoked :          Fota_GetRunPartition **
**                                                                            **
*******************************************************************************/

FUNC(Std_ReturnType,FOTA_CODE) Fota_GetActivePartition(
		P2VAR(Fota_PartitionType, AUTOMATIC, FOTA_PRIVATE_DATA) pActivePartition)
{
	VAR(Std_ReturnType,AUTOMATIC) retVal=E_NOT_OK;
	/* @Trace: FOTA_SUD_API_00011 */
	retVal = E_NOT_OK;

	if(Fota_GetRunPartition(pActivePartition)==E_OK)
	{
		retVal = E_OK;
	}

    return retVal;
}

/*******************************************************************************
** Function Name        : Fota_GetRunPartition                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to get the running partition               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pRunPartition                                       **
**                                                                            **
** Return parameter     : Std_ReturnType retVal                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Fota_Gast_SwUnitTable         **
**                                                                            **
**                        Function(s) invoked :         Fota_GetTopPrioActKey **
**                                         Fota_GetSoftwareModuleBlkByRunArea **
**                                                                            **
*******************************************************************************/

FUNC(Std_ReturnType,FOTA_CODE) Fota_GetRunPartition(
		P2VAR(Fota_PartitionType, AUTOMATIC, FOTA_PRIVATE_DATA) pRunPartition)
{
  VAR(uint8, AUTOMATIC) programmingSwUnitId;

  VAR(Std_ReturnType,AUTOMATIC) retVal=E_NOT_OK;
  /* @Trace: FOTA_SUD_API_00012 */
  retVal = E_NOT_OK;

#if ((FOTA_MODE==FOTA_APP_MODE)||(FOTA_MODE==FOTA_UPDATER_MODE))
  if(Fota_GetSoftwareModuleBlkByRunArea(&programmingSwUnitId)==E_OK)
#else /*(FOTA_MODE==FOTA_FBL_MODE)*/
  if(Fota_GetTopPrioActKey(FOTA_FLKEY_MGR,&programmingSwUnitId)==E_OK)
#endif
  {
	  if(Fota_Gast_SwUnitTable[programmingSwUnitId].SoftwareType==FOTA_RTSW_PARTA_TYPE)
	  {
		  *pRunPartition=FOTA_PARTITION_A;
		  retVal=E_OK;
	  }
	  else if(Fota_Gast_SwUnitTable[programmingSwUnitId].SoftwareType==FOTA_RTSW_PARTB_TYPE)
	  {
		  *pRunPartition=FOTA_PARTITION_B;
		  retVal=E_OK;
	  }
	  else
	  {
		  *pRunPartition=FOTA_PARTITION_UNKNOWN;
	  }
  }
#if (FOTA_MODE==FOTA_FBL_MODE)
  else
  {
	  /* @Trace: FOTA_SUD_API_00014 */
	  *pRunPartition=FOTA_PARTITION_UNKNOWN;
	  retVal=E_OK;
  }
#endif
  return retVal;
}

