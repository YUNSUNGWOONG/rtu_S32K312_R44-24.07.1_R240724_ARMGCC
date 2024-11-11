/*******************************************************************************
**                                                                            **
** (C) 2021 HYUNDAI AUTOEVER Corp.                                            **
** Confidential Proprietary Information. Distribution Limited.                **
** This source code is permitted to be used only in projects contracted       **
** with Hyundai Autoever, and any other use is prohibited.                    **
** If you use it for other purposes or change the source code,                **
** you may take legal responsibility.                                         **
** In this case, There is no warranty and technical support.                  **
**                                                                            **
**  SRC-MODULE: Dcm_ComM.c                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : Manage ComM mode                                              **
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
** 0.0.1     31-Dec-2019   LanhLT         AR440 Implementation                **
** 0.0.2     13-Oct-2020   LanhLT         Changes made as per #15766          **
** 0.0.3     16-Dec-2020   HueKM          Mapping SUD API ID as per #17448    **
*******************************************************************************/
#include "Dcm.h"
#include "Rte_Dcm.h"
#include "Dcm_Ram.h"
#include "Dcm_ComM.h"
#include "Dcm_Validate.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Dcm_ComM_NoComModeEntered                           **
**                                                                            **
** Service ID           : 0x21                                                **
**                                                                            **
** Description          : Informs the Dcm module about a ComM mode change to  **
**                        COMM_NO_COMMUNICATION                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : NetworkId                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GaaCommMode                **
**                                                                            **
**                        Function(s) :                                       **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_00148 SWS_Dcm_00151 SWS_Dcm_01324 SWS_Dcm_00356 */
FUNC(void, DCM_APPL_CODE) Dcm_ComM_NoComModeEntered(uint8 NetworkId)
{
  /* @Trace: Dcm_SUD_API_09000 */
  uint8 ApiId = DCM_COMM_NO_COM_MODE_ENTERED_SID;
  boolean ChkVal = Dcm_ChkInit(ApiId);
  CHK_NEXT(ChkVal, Dcm_ChkComMChannel(ApiId, NetworkId));

  if (DCM_TRUE == ChkVal)
  {
    /* @Trace: Dcm_SUD_API_09001 */
    Dcm_GaaCommMode[NetworkId] = DCM_NO_COMMUNICATION;
  }
}

/*******************************************************************************
** Function Name        : Dcm_ComM_SilentComModeEntered                       **
**                                                                            **
** Service ID           : 0x22                                                **
**                                                                            **
** Description          : Informs the Dcm module about a ComM mode change to  **
**                        COMM_SILENT_COMMUNICATION                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : NetworkId                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GblInitStatus              **
**                                                                            **
**                        Function(s) :                                       **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_00153 SWS_Dcm_00156 SWS_Dcm_01325 SWS_Dcm_00358 */
FUNC(void, DCM_APPL_CODE) Dcm_ComM_SilentComModeEntered(uint8 NetworkId)
{
  /* @Trace: Dcm_SUD_API_09003 */
  uint8 ApiId = DCM_COMM_SILENT_COM_MODE_ENTERED_SID;
  boolean ChkVal = Dcm_ChkInit(ApiId);
  CHK_NEXT(ChkVal, Dcm_ChkComMChannel(ApiId, NetworkId));

  if (DCM_TRUE == ChkVal)
  {
    /* @Trace: Dcm_SUD_API_09004 */
    Dcm_GaaCommMode[NetworkId] = DCM_SILENT_COMMUNICATION;
  }
}

/*******************************************************************************
** Function Name        : Dcm_ComM_FullComModeEntered                         **
**                                                                            **
** Service ID           : 0x23                                                **
**                                                                            **
** Description          : Informs the Dcm module about a ComM mode change to  **
**                        COMM_FULL_COMMUNICATION                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : NetworkId                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GaaCommMode                **
**                                                                            **
**                        Function(s) :                                       **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_01326 SWS_Dcm_00360 */
FUNC(void, DCM_APPL_CODE) Dcm_ComM_FullComModeEntered(uint8 NetworkId)
{
  /* @Trace: Dcm_SUD_API_09005 */
  uint8 ApiId = DCM_COMM_FULL_COM_MODE_ENTERED_SID;
  boolean ChkVal = Dcm_ChkInit(ApiId);
  CHK_NEXT(ChkVal, Dcm_ChkComMChannel(ApiId, NetworkId));

  if (DCM_TRUE == ChkVal)
  {
    /* @Trace: Dcm_SUD_API_09006 */
    Dcm_GaaCommMode[NetworkId] = DCM_FULL_COMMUNICATION;
  }
}

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
