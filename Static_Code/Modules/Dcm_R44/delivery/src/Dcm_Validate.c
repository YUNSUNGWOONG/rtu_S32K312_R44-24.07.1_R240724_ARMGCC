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
**  SRC-MODULE: Dcm_Validate.c                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : Common validatation function for Dcm                          **
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
** 0.0.3     18-Dec-2020   HueKM          Mapping SUD API ID as per #17448    **
** 1.1.0     12-Oct-2023   SY Kim         Refer #CP44-3106                    **
*******************************************************************************/

#include "Dcm.h"
#include "Dcm_Ram.h"
#include "Dcm_Config.h"
#include "Dcm_Validate.h"

#define DCM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Dcm_ChkInit                                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function check Dcm initialize status                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ApiId                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GblInitStatus              **
**                                                                            **
**                        Function(s) :                                       **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_ChkInit(uint8 ApiId)
{
  /* @Trace: Dcm_SUD_API_10170 */
  boolean ChkVal = DCM_TRUE;

  if (DCM_UNINITIALIZED == Dcm_GblInitStatus)
  {
    /* @Trace: Dcm_SUD_API_10171 */
    DCM_REPORT_ERROR(ApiId, DCM_E_UNINIT);
    ChkVal = DCM_FALSE;
  }

  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_ChkPduId                                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check available PduId                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ApiId, PduId                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) :                                       **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_ChkPduId(uint8 ApiId, PduIdType PduId)
{
  /* @Trace: Dcm_SUD_API_10173 */
  boolean ChkVal = DCM_TRUE;

  if (DCM_NUM_OF_PDUIDTABLECONFIG <= PduId)
  {
    /* @Trace: Dcm_SUD_API_10174 */
    DCM_REPORT_ERROR(ApiId, DCM_E_PARAM);
    ChkVal = DCM_FALSE;
  }

  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_ChkP2Var                                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check Null variable pointer                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ApiId, Ptr                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) :                                       **
**                                                                            **
*******************************************************************************/
/* polyspace +1 MISRA2012:8.13 [Not a defect:Low] Justify with annotations */
FUNC(boolean, DCM_CODE) Dcm_ChkP2Var(uint8 ApiId, void *Ptr)
{
  /* @Trace: Dcm_SUD_API_10176 */
  boolean ChkVal = DCM_TRUE;

  if (NULL_PTR == Ptr)
  {
    /* @Trace: Dcm_SUD_API_10177 */
    DCM_REPORT_ERROR(ApiId, DCM_E_PARAM_POINTER);
    ChkVal = DCM_FALSE;
  }

  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_ChkP2Const                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check Null constant pointer                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ApiId, Ptr                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) :                                       **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_ChkP2Const(uint8 ApiId, const void *Ptr)
{
  /* @Trace: Dcm_SUD_API_10179 */
  boolean ChkVal = DCM_TRUE;

  if (NULL_PTR == Ptr)
  {
    /* @Trace: Dcm_SUD_API_10180 */
    DCM_REPORT_ERROR(ApiId, DCM_E_PARAM_POINTER);
    ChkVal = DCM_FALSE;
  }

  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_ChkComMChannel                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function validate ComM channel                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ApiId, ComMChannelId                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) :                                       **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_ChkComMChannel(uint8 ApiId, uint8 ComMChannelId)
{
  /* @Trace: Dcm_SUD_API_10182 */
  boolean ChkVal = DCM_TRUE;

  if (DCM_NO_OF_COMM_CHANNELS <= ComMChannelId)
  {
    /* @Trace: Dcm_SUD_API_10183 */
    DCM_REPORT_ERROR(ApiId, DCM_E_PARAM);
    ChkVal = DCM_FALSE;
  }

  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_ChkZeroLength                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function check length equal zero                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ApiId, Length                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) :                                       **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_ChkZeroLength(uint8 ApiId, uint32 Length)
{
  /* @Trace: Dcm_SUD_API_10185 */
  boolean ChkVal = DCM_TRUE;

  if (0 == Length)
  {
    /* @Trace: Dcm_SUD_API_10186 */
    DCM_REPORT_ERROR(ApiId, DCM_E_PARAM);
    ChkVal = DCM_FALSE;
  }

  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_ChkLength                                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function check length                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ApiId, SrcLength, DstLength                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) :                                       **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_ChkLength(uint8 ApiId, uint32 SrcLength, uint32 DstLength)
{
  /* @Trace: Dcm_SUD_API_10188 */
  boolean ChkVal = DCM_TRUE;

  if (DstLength < SrcLength)
  {
    /* @Trace: Dcm_SUD_API_10189 */
    DCM_REPORT_ERROR(ApiId, DCM_E_INTERFACE_BUFFER_OVERFLOW);
    ChkVal = DCM_FALSE;
  }

  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_ChkNumRespPend                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function number of return response pending          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ApiId, NumRespPend                                  **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) :                                       **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_ChkNumRespPend(uint8 ApiId, uint16 NumRespPend)
{
  /* @Trace: Dcm_SUD_API_10191 */
  boolean ChkVal = DCM_TRUE;

  /* @Trace: SWS_Dcm_00120 */
  if (DCM_DIAG_RESP_MAX_NUM_RESPEND < NumRespPend)
  {
    /* @Trace: Dcm_SUD_API_10192 */
    DCM_REPORT_RUNTIME_ERROR(ApiId, DCM_E_INTERFACE_TIMEOUT);
    ChkVal = DCM_FALSE;
  }

  return ChkVal;
}

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
