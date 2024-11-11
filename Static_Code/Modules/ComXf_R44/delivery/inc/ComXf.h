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
**  INC-MODULE:           ComXf.h                                             **
**                                                                            **
**  PRODUCT   :           AUTOSAR COM Based Transformer Module                **
**                                                                            **
**  PURPOSE   :           This file defines extern declarations of packing    **
**                        functions                                           **
**                                                                            **
**  HARDWARE DEPENDANT [Yes/No]: No                                           **
**                                                                            **
**  AUTOSAR RELEASE:  4.4.0                                                   **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By          Description                            **
********************************************************************************
** 1.0.10    27-Dec-2022   KhaLN1      #CP44-1403                             **
** 1.0.7     31-Aug-2022   KhaLN1      #CP44-614                              **
** 1.0.4     14-Dec-2021   PhucNHM     R44-Redmine #23089                     **
** 1.0.0     22-Feb-2020   HiepVT1     Initial Version                        **
*******************************************************************************/

#ifndef COMXF_H
#define COMXF_H

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "see SWS_MemMap_00003 of AUTOSAR" */

/*******************************************************************************
**                         Header File Include Section                        **
*******************************************************************************/
/* @Trace: SafeComXf_SUD_FILE_001 */
/*include for Std_Types.h*/
#include "TransformerTypes.h"
/*include for ComXf_Cfg.h*/
#include "ComXf_Cfg.h"
/*include for ComXf_APIs.h*/
#include "ComXf_APIs.h"
/*include for Det.h*/
#if (COMXF_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif
/*include for ComXf_PbCfg.h*/
#if (COMXF_PRECOMPILE_CONFIG == STD_OFF)
#include "ComXf_PbCfg.h"
#endif

/*******************************************************************************
**                              MACRO Definition                              **
*******************************************************************************/
/* @Trace: SafeComXf_SUD_MACRO_003 SafeComXf_SUD_MACRO_004 SafeComXf_SUD_MACRO_005*/
/* Macro used for module initialization */
#define COMXF_CS_INIT                      (0x01U)

/* Macro used for module deinitialization */
#define COMXF_CS_DEINIT                    (0x00U)

/* Macro used for API service called without initialization */
#define COMXF_E_UNINIT                     (0x01U)

/* Macro used for API service called with wrong parameter */
#define COMXF_E_PARAM                      (0x03U)

/* Macro used for API service called with invalid pointer */
#define COMXF_E_PARAM_POINTER             (0x04U)

/* Macro used for Compatin 0 value */
#define COMXF_HEX_00                       (0x00U)

/* Macro used for Checking signed value */
#define COMXF_NOT_SIGNED_SIGNAL            (0x00U)

/* Macro used for init API service id */
#define COMXF_INIT_SERVICE_ID            (0x01U)

/* Macro used for deinit API service id */
#define COMXF_DEINIT_SERVICE_ID            (0x02U)

/* Macro used for transformer API service id */
#define COMXF_TRANSFORMER_SERVICE_ID       (0x03U)

/* Macro used for inverse transformer API service id */
#define COMXF_INV_TRANSFORMER_SERVICE_ID    (0x04U)

/* Macro used for GetVersionInfo API service id */
#define COMXF_GETVERSIONINFO_SERVICE_ID    (0x00U)

/* Macro used for 2 bytes */
#define COMXF_TWO_BYTES                    (2U)

/* Macro used for 3 bytes */
#define COMXF_THREE_BYTES                  (3U)

/* Macro used for shifting by 8 */
#define COMXF_SHIFT_BY_EIGHT               (8U)

/* Macro used for array index zero */
#define COMXF_ZEROTH_BYTE                  (0U)

/* Macro used for array index one */
#define COMXF_FIRST_BYTE                   (1U)

/* Macro used for array index two */
#define COMXF_SECOND_BYTE                  (2U)

/* Macro used for array index three */
#define COMXF_THIRD_BYTE                   (3U)

/* Macro used for shifting by 32  */
#define COMXF_SHIFT_BY_THIRTYTWO           (32U)

/* Macro used for define zero value  */
#define COMXF_ZERO                         (0U)

/*******************************************************************************
**                              Type Definition                               **
*******************************************************************************/
/* polyspace-begin MISRA2012:19.2 [Justified:Low] "Using union is acceptable in this case" */
/* @Trace: SafeComXf_SUD_DATATYPE_009 */
/* ComXf_Float32DataType union */
typedef union
{
  /* uint32 data type */
  uint32 u32;
  /* float32 data type */
  float32 f32;
}ComXf_Float32DataType;

/* @Trace: SafeComXf_SUD_DATATYPE_010 */
/* ComXf_Float64DataType union */
typedef union
{
  /* uint64 data type */
  uint64 u64;
  /* float64 data type */
  float64 f64;
}ComXf_Float64DataType;
/* polyspace-end MISRA2012:19.2 */

/*******************************************************************************
**                           Function Declaration                             **
*******************************************************************************/
/* extern declaration of ComXf_DeInit */
#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
extern FUNC(void, COMXF_CODE) ComXf_DeInit(void);
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/* extern declaration of ComXf_GetVersionInfo */
#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
extern FUNC(void, COMXF_CODE) ComXf_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, COMXF_APPL_DATA) versionInfo);
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
extern FUNC(void, COMXF_APPL_CODE) ComXf_FillUnusedBufferArea(
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) buffer,
  VAR(uint32, AUTOMATIC) ComXfBufferLength,
  VAR(uint8, AUTOMATIC) ComXfUnusedAreaValue);
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA RULE CHECKER)                   **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 */

#endif /* COMXF_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
