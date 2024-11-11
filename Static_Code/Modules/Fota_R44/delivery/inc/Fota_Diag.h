
/*******************************************************************************
**                                                                            **
**  (C) 2021~2022 HYUNDAI AUTOEVER Co., Ltd.                                  **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Fota_Diag.h                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   :                                                               **
**                                                                            **
**  PURPOSE   :                                                               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     30-Mar-2022   jys          Initial version                       **
*******************************************************************************/


#ifndef FOTA_DIAG_H
#define FOTA_DIAG_H

#include "Rte_Dcm_Type.h"

#include "Dcm_Version.h"
#if (DCM_VERSION_AR_RELEASE_MAJOR_VERSION == 4U) && (DCM_VERSION_AR_RELEASE_MINOR_VERSION == 4U) /* DCM R44 */
  #include "Dcm_Types.h" 
  #include "EcuM_Cfg.h" 
  #define FOTA_DCM_VERSION 44U /*R44*/
  #define DCM_E_POSITIVERESPONSE                             DCM_POSITIVE_RESPONSE /* workaround DCM_R44 missing DCM_E_POSITIVERESPONSE */
#elif (DCM_VERSION_AR_RELEASE_MAJOR_VERSION == 4U) && (DCM_VERSION_AR_RELEASE_MINOR_VERSION == 0U) /* DCM R40 */
  #define FOTA_DCM_VERSION 40U /*R40*/
#else
  #error "Fota and Dcm_Version : Mismatch in Specification Major Version"
#endif

#if (FOTA_DCM_VERSION == 44U)
#define FOTA_ADDR_PHYSICAL DCM_PHYSICAL_TYPE         /* R44, define is change to Dcm_ProtocolRxAddrType */
#define FOTA_MODE_USER         (ECUM_USER_APP)       /* Since R44, the reset user setting should be ECUM_USER_APP. In R40, this value is ignored. */
#else 
#define FOTA_ADDR_PHYSICAL DCM_ADDR_PHYSICAL         /* R40 */
#define FOTA_MODE_USER         (0U)                  /* R40, this value is not used */
#endif

/************************ RETURN VALUE MAPPING SECTION ************************/
#define FOTA_CHKDEP_OK        E_OK//RTE_E_OK
#define FOTA_CHKDEP_RCRRP     DCM_E_FORCE_RCRRP//RTE_E_RoutineServices_RID_FF01h_CheckProgrammingDependency_DCM_E_FORCE_RCRRP
#define FOTA_CHKDEP_NG        E_NOT_OK//RTE_E_RoutineServices_RID_FF01h_CheckProgrammingDependency_E_NOT_OK
#define FOTA_CHKDEP_PENDING   DCM_E_PENDING//RTE_E_RoutineServices_RID_FF01h_CheckProgrammingDependency_DCM_E_PENDING

#define FOTA_ERSTGT_OK        E_OK//RTE_E_OK
#define FOTA_ERSTGT_RCRRP     DCM_E_FORCE_RCRRP//RTE_E_RoutineServices_RID_FF00h_EraseTargetArea_DCM_E_FORCE_RCRRP
#define FOTA_ERSTGT_NG        E_NOT_OK//RTE_E_RoutineServices_RID_FF00h_EraseTargetArea_E_NOT_OK
#define FOTA_ERSTGT_PENDING   DCM_E_PENDING//RTE_E_RoutineServices_RID_FF00h_EraseTargetArea_DCM_E_PENDING

#define FOTA_WRIMEM_OK        DCM_WRITE_OK
#define FOTA_WRIMEM_RCRRP     DCM_WRITE_FORCE_RCRRP
#define FOTA_WRIMEM_NG        DCM_WRITE_FAILED
#define FOTA_WRIMEM_PENDING   DCM_WRITE_PENDING

#define FOTA_REQDWL_OK        E_OK
//#define FOTA_REQDWL_RCRRP   DCM_E_FORCE_RCRRP /* Not defined DCM_UM doc */
#define FOTA_REQDWL_NG        E_NOT_OK
#define FOTA_REQDWL_PENDING   DCM_E_PENDING

#define FOTA_TRSEXT_OK        E_OK
//#define FOTA_REQDWL_RCRRP   DCM_E_FORCE_RCRRP /* Not defined DCM_UM doc */
#define FOTA_TRSEXT_NG        E_NOT_OK
#define FOTA_TRSEXT_PENDING   DCM_E_PENDING

#ifndef DCM_E_LOWERVERSIONDOWNLOADATTEMPT
#define DCM_E_LOWERVERSIONDOWNLOADATTEMPT 0xF4U
#endif 

typedef enum
{
  FOTA_CMD_IDLE,
  FOTA_CMD_ERASE,
  FOTA_CMD_PROCESS,
  FOTA_CMD_VERIFY
} Fota_CmdStatType;

typedef enum
{
  FOTA_DIAG_ACT_USER_INIT=0,
  FOTA_DIAG_ACT_USER_PEND,
  FOTA_DIAG_ACT_INTERAL_INIT,
  FOTA_DIAG_ACT_INTERAL_PEND,
  FOTA_SYNC_ACT_END,
  FOTA_SYNC_ACT_ERR
} Fota_DiagActCmdType;

/*******************************************************************************
**                        Function Prototypes                                 **
*******************************************************************************/
#define Fota_START_SEC_CODE
#include "Fota_MemMap.h"

FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Fota_Start_CheckMemory
(
    VAR(uint8, AUTOMATIC) OpStatus,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpErrorCode
);

extern FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Fota_Start_CheckProgrammingDependency
(
    P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) pRoutineDataIn,
    VAR(uint8, AUTOMATIC) OpStatus,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pRoutineDataOut,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) LpCur_DataLen,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpErrorCode
);

extern FUNC (Std_ReturnType, DCM_CALLOUT_CODE) Fota_Start_ReadActiveArea // return value & FctID
(
    P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) pRoutineDataIn,
    VAR(uint8, AUTOMATIC) OpStatus,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pRoutineDataOut,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) LpCur_DataLen,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpErrorCode
);

extern FUNC (Std_ReturnType, DCM_CALLOUT_CODE) Fota_Start_SwapActiveArea // return value & FctID
(
    P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) pRoutineDataIn,
    VAR(uint8, AUTOMATIC) OpStatus,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pRoutineDataOut,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) LpCur_DataLen,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpErrorCode
);

extern FUNC (Std_ReturnType, DCM_CALLOUT_CODE) Fota_Start_EraseTargetArea // return value & FctID
(
    P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) pRoutineDataIn,
    VAR(uint8, AUTOMATIC) OpStatus,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pRoutineDataOut,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) LpCur_DataLen,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpErrorCode
);
extern FUNC (Std_ReturnType, DCM_CALLOUT_CODE) Fota_Start_EraseMemory // return value & FctID
(
    P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) pRoutineDataIn,
    VAR(uint8, AUTOMATIC) OpStatus,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pRoutineDataOut,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) LpCur_DataLen,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpErrorCode
);
extern FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Fota_RequestDownload
(
    Dcm_OpStatusType OpStatus,
    uint8 DataFormatIdentifier,
    uint32 MemoryAddress,
    uint32 MemorySize,
    P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) LpBlockLength,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpErrorCode
);

extern FUNC(Dcm_ReturnWriteMemoryType, DCM_CALLOUT_CODE) Fota_DataTransfer
(
    Dcm_OpStatusType OpStatus,
    uint8 MemoryIdentifier /* Not Supported Argument */,
    uint32 MemoryAddress,
    uint32 MemoryWriteLen,
    P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) pWriteData
);

extern FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Fota_RequestTransferExit
(
    Dcm_OpStatusType OpStatus,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpMemoryData,
    uint32* LulParameterRecordSize,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) LpErrorCode
);

FUNC (Std_ReturnType, DCM_CALLOUT_CODE) Fota_Start_FinishUpdate // return value & FctID
(
    VAR(uint8, AUTOMATIC) OpStatus,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpErrorCode
);

extern FUNC(void,DCM_CALLOUT_CODE) FotaBlockProcessing_Decompress(void);

extern FUNC(void,DCM_CALLOUT_CODE) FotaBlockProcessing_Decrypt(void);

extern FUNC(Std_ReturnType,FOTA_CALLOUT_CODE) UserCallout_PreRoutineControl(void);
extern FUNC(Std_ReturnType,FOTA_CALLOUT_CODE) UserCallout_PostRoutineControl(void);

#define Fota_STOP_SEC_CODE
#include "Fota_MemMap.h"


#endif /* End FOTA_DIAG_H */
