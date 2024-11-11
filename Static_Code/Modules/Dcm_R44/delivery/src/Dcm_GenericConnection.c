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
**  SRC-MODULE: Dcm_GenericConnection.h                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : Contain the main implementation for Generic Connection        **
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
#include "Dcm_PCTypes.h"
#include "Dcm_Validate.h"
#include "Dcm_DsdInternal.h"
#include "Dcm_GenericConnection.h"
#include "Dcm_Utils.h"

#define METADATA_SA_IDX (0)
#define METADATA_SA_LEN (2)

#define METADATA_TA_IDX (METADATA_SA_LEN)
#define METADATA_TA_LEN (2)

#define METADATA_LEN (METADATA_SA_LEN + METADATA_TA_LEN)

#if (DCM_GENERIC_CONNECTION_HANDLING == STD_ON)
/* |            Meta data            | */
/* | source address | target address | */
/* |     2 byte     |     2 byte     | */

static VAR(uint8, DCM_VAR) TxMetaDataArray[METADATA_LEN];
#endif


#define DCM_START_SEC_CODE
#include "MemMap.h"

#if (DCM_GENERIC_CONNECTION_HANDLING == STD_ON)
static FUNC(uint16, DCM_CODE) Dcm_GetRxSourceAddress(
  PduInfoConstPtrType Info);

static FUNC(uint16, DCM_CODE) Dcm_GetRxTargetAddress(
  PduInfoConstPtrType Info);

static FUNC(void, DCM_CODE) Dcm_SetTxMetaDataArray(
  uint16 TxSourceAddress
  , uint16 TxTargetAddress);
#endif

/*******************************************************************************
** Function Name        : Dcm_InitGenericConnection                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to initialize Generic Connection feature   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : pConfig                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : Dcm_Init must be called before call this fucntion   **
**                                                                            **
** Remarks              : Global Variable(s) : TxMetaDataArray                **
**                                                                            **
**                        Function(s) :  Dcm_MemClear                         **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_InitGenericConnection(
  Dcm_ConfigConstPtrType pConfig)
{
  /* @Trace: Dcm_SUD_API_50401 */
  #if (DCM_GENERIC_CONNECTION_HANDLING == STD_ON)
  Dcm_MemClear(TxMetaDataArray, METADATA_LEN);
  #endif

  DCM_UNUSED(pConfig);
}

/*******************************************************************************
** Function Name        : Dcm_ChkRxMetaDataPtr                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function check received Metadata                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ApiId, Id, Info                                     **
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
**                        Function(s) :  Dcm_ChkP2Const                       **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_ChkRxMetaDataPtr(
  uint8 ApiId
  , PduIdType Id
  , PduInfoConstPtrType Info)
{
  /* @Trace: Dcm_SUD_API_50402 */
  boolean ChkVal = DCM_TRUE;

  #if (DCM_GENERIC_CONNECTION_HANDLING == STD_ON)
  Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[Id];
  Dcm_PduRefType PduRef = pPduIdTable->PduRef;

  if ((PDUREF_METADATA_SA_TA == PduRef)
      || (PDUREF_METADATA_SA == PduRef))
  {
    /* @Trace: Dcm_SUD_API_50403 */
    ChkVal = Dcm_ChkP2Const(ApiId, Info);
    CHK_NEXT(ChkVal, Dcm_ChkP2Const(ApiId, Info->MetaDataPtr));
  }
  #else
  DCM_UNUSED(Id);
  DCM_UNUSED(ApiId);
  DCM_UNUSED(Info);
  #endif

  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_ChkRxTargetAddress                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function check received target address              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Id, Info                                            **
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
**                        Function(s) :  Dcm_GetProtocolConfigPtr             **
**                                       Dcm_GetRxTargetAddress               **
**                                                                            **
*******************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_ChkRxTargetAddress(
  PduIdType Id
  , PduInfoConstPtrType Info)
{
  /* @Trace: Dcm_SUD_API_50404 */
  boolean ChkVal = DCM_TRUE;

  #if (DCM_GENERIC_CONNECTION_HANDLING == STD_ON)
  Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[Id];
  Dcm_ProtocolRxAddrType ReqType = pPduIdTable->ucRxAddrType;
  Dcm_PduRefType PduRef = pPduIdTable->PduRef;

  Dcm_ProtocolConfigConstPtrType pProtocolCfg = Dcm_GetProtocolConfigPtr(Id);
  uint16 EcuAddress = pProtocolCfg->EcuAddress;

  if (DCM_PHYSICAL_TYPE == ReqType
      && PDUREF_METADATA_SA_TA == PduRef
      && ADDRESS_UNSET != EcuAddress)
  {
    /* @Trace: SWS_Dcm_01347 */
    /* @Trace: Dcm_SUD_API_50405 Dcm_SUD_API_50406 */
    uint16 TargetAddress = Dcm_GetRxTargetAddress(Info);
    ChkVal = (TargetAddress == EcuAddress) ? DCM_TRUE : DCM_FALSE;
  }
  #else
  DCM_UNUSED(Id);
  DCM_UNUSED(Info);
  #endif

  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_StoreSourceTesterAddress                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function store tester source address                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Id, Info                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) :  Dcm_GetRxSourceAddress               **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04170 */
FUNC(void, DCM_CODE) Dcm_StoreSourceTesterAddress(
  PduIdType Id
  , PduInfoConstPtrType Info)
{
  /* @Trace: Dcm_SUD_API_50407 */
  #if (DCM_GENERIC_CONNECTION_HANDLING == STD_ON)
  Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[Id];
  Dcm_PduRefType PduRef = pPduIdTable->PduRef;

  pPduIdTable->SourceTesterAddress = ADDRESS_UNSET;
  if ((PDUREF_METADATA_SA_TA == PduRef)
      || (PDUREF_METADATA_SA == PduRef))
  {
    /* @Trace: SWS_Dcm_00848 */
    /* @Trace: Dcm_SUD_API_50408 */
    pPduIdTable->SourceTesterAddress = Dcm_GetRxSourceAddress(Info);
  }
  #else
  DCM_UNUSED(Id);
  DCM_UNUSED(Info);
  #endif
}

/*******************************************************************************
** Function Name        : Dcm_GetTxMetaDataPtr                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to get transmission Metadata               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Id, Info                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : TxMetaDataArray                **
**                                                                            **
**                        Function(s) :  Dcm_GetProtocolConfigPtr             **
**                                       Dcm_SetTxMetaDataArray               **
**                                                                            **
*******************************************************************************/
/* polyspace +3 MISRA2012:8.13 [Justified:Low] Justify with annotations */
FUNC(void, DCM_CODE) Dcm_GetTxMetaDataPtr(
  PduIdType Id
  , PduInfoPtrType Info)
{
  /* @Trace: Dcm_SUD_API_50409 */
  #if (DCM_GENERIC_CONNECTION_HANDLING == STD_ON)
  Dcm_PduIdTablePtrType pPduIdTable = &Dcm_GaaPduIdTableConfig[Id];
  Dcm_PduRefType PduRef = pPduIdTable->PduRef;

  if (PDUREF_NO_METADATA != PduRef)
  {
    /* @Trace: Dcm_SUD_API_50410 */
    Dcm_ProtocolConfigConstPtrType pProtocolCfg = Dcm_GetProtocolConfigPtr(Id);

    /* @Trace: SWS_Dcm_00849 SWS_Dcm_01348 */
    uint16 TxSourceAddress = pProtocolCfg->EcuAddress;
    uint16 TxTargetAddress = pPduIdTable->SourceTesterAddress;

    Dcm_SetTxMetaDataArray(TxSourceAddress, TxTargetAddress);
    Info->MetaDataPtr = TxMetaDataArray;
  }
  #else
  DCM_UNUSED(Id);
  DCM_UNUSED(Info);
  #endif
}

/*******************************************************************************
** Function Name        : Dcm_GetRxSourceAddress                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to get received source address             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Info                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint16                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) :                                       **
**                                                                            **
*******************************************************************************/
#if (DCM_GENERIC_CONNECTION_HANDLING == STD_ON)
static FUNC(uint16, DCM_CODE) Dcm_GetRxSourceAddress(
  PduInfoConstPtrType Info)
{
  /* @Trace: Dcm_SUD_API_50411 */
  uint16 SourceAddress = Info->MetaDataPtr[METADATA_SA_IDX];
  SourceAddress <<= 8U;
  SourceAddress |= Info->MetaDataPtr[METADATA_SA_IDX + 1];

  return SourceAddress;
}

/*******************************************************************************
** Function Name        : Dcm_GetRxTargetAddress                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to get received target address             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Info                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint16                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) :                                       **
**                                                                            **
*******************************************************************************/
static FUNC(uint16, DCM_CODE) Dcm_GetRxTargetAddress(
  PduInfoConstPtrType Info)
{
  /* @Trace: Dcm_SUD_API_50412 */
  uint16 TargetAddress = Info->MetaDataPtr[METADATA_TA_IDX];
  TargetAddress <<= 8U;
  TargetAddress |= Info->MetaDataPtr[METADATA_TA_IDX + 1];

  return TargetAddress;
}

/*******************************************************************************
** Function Name        : Dcm_SetTxMetaDataArray                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to set transmission Metadata to array      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Info                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint16                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : TxMetaDataArray                **
**                                                                            **
**                        Function(s) :                                       **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_SetTxMetaDataArray(
  uint16 TxSourceAddress
  , uint16 TxTargetAddress)
{
  /* @Trace: Dcm_SUD_API_50413 */
  TxMetaDataArray[METADATA_SA_IDX] = (uint8)(TxSourceAddress >> 8U);
  TxMetaDataArray[METADATA_SA_IDX + 1] = (uint8)TxSourceAddress;

  TxMetaDataArray[METADATA_TA_IDX] = (uint8)(TxTargetAddress >> 8U);
  TxMetaDataArray[METADATA_TA_IDX + 1] = (uint8)TxTargetAddress;
}
#endif

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
