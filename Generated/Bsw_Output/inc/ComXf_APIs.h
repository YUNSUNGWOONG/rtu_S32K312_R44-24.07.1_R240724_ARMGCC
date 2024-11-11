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
**  INC-MODULE:           ComXf_APIs.h                                        **
**                                                                            **
**  PRODUCT   :           AUTOSAR COM Based Transformer Module                **
**                                                                            **
**  PURPOSE   :           This file defines public function prototype.        **
**                                                                            **
**  HARDWARE DEPENDANT [Yes/No]: No                                           **
**                                                                            **
**  AUTOSAR RELEASE:  4.4.0                                                   **
*******************************************************************************/

/*******************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  FrameWork  Version: 1.1.5                                                 **
**                                                                            **
**  Module Version: 1.0.11.1                                                   **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            ** 
*******************************************************************************/

#ifndef COMXF_APIS_H
#define COMXF_APIS_H

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "see SWS_MemMap_00003 of AUTOSAR" */ 

/*******************************************************************************
**                         Header File Include Section                        **
*******************************************************************************/
/* @Trace: SafeComXf_SUD_FILE_001 */
/*include for Rte_Type.h*/
#include "Rte_Type.h"

/*******************************************************************************
**                              Type Definition                               **
*******************************************************************************/

/* @Trace: SafeComXf_SUD_DATATYPE_002 */
/* Packing information of Signal/Group Signal */
typedef struct
{
  /* Clear or Start bit mask for the signal data */
  uint8 startORClearBitMask;

  /* Set or End bit mask for the signal data */
  uint8 setOREndMsk;

  /* Size of signal in bytes */
  uint8 noOfBytes;

  /* Shift bit to align the signal at actual start bit */
  uint8 shiftBits;

} ComXf_PackSigType;

/* @Trace: SafeComXf_SUD_DATATYPE_003 */
/* Unpacking information of Signal/Group Signal */
typedef struct
{
  /* uint64 SigSignMsk64; */
  uint64 sigSignMsk64;

  /* uint32 SigSignMsk32; */
  uint32 sigSignMsk32;

  /* End bit mask for the signal data */
  uint8 rxEndMsk;

  /* Size of signal in bytes */
  uint8 noOfBytes;

  /* Shift bit to align the signal at actual start bit */
  uint8 shiftBits;

} ComXf_UnPackSigType;

typedef struct
{
  /* Unused variable created because of compilation issue */
  uint8 u8_UnUsed;

} ComXf_ConfigType;


/*******************************************************************************
**                         Global Variable Declaration                        **
*******************************************************************************/

#define COMXF_START_SEC_VAR_INIT_ASIL_D_BOOLEAN
#include "MemMap.h"
/* Definition of the global Initialization status variable */
extern VAR(boolean, AUTOMATIC) ComXf_InitStatus;
#define COMXF_STOP_SEC_VAR_INIT_ASIL_D_BOOLEAN
#include "MemMap.h"

#if(COMXF_PACK_INFO_COUNT > 0U)
/* extern declaration for the global signal data packing variable */
#define COMXF_START_SEC_CONFIG_DATA_ASIL_D_UNSPECIFIED
#include "MemMap.h"
extern CONST(ComXf_PackSigType, COMXF_CONST) ComXf_Kast_SigPackInfo[COMXF_PACK_INFO_COUNT];
#define COMXF_STOP_SEC_CONFIG_DATA_ASIL_D_UNSPECIFIED
#include "MemMap.h"
#endif /* (COMXF_PACK_INFO_COUNT > 0U) */

#if(COMXF_UNPACK_INFO_COUNT > 0U)
/* extern declaration for the global signal data unpacking variable */
#define COMXF_START_SEC_CONFIG_DATA_ASIL_D_UNSPECIFIED
#include "MemMap.h"
extern CONST(ComXf_UnPackSigType, COMXF_CONST) ComXf_Kast_SigUnPackInfo[COMXF_UNPACK_INFO_COUNT];
#define COMXF_STOP_SEC_CONFIG_DATA_ASIL_D_UNSPECIFIED
#include "MemMap.h"
#endif /* (COMXF_UNPACK_INFO_COUNT > 0U) */


/*******************************************************************************
**                       Tx Group Signals Handle Ids                          **
*******************************************************************************/
#define ComXf_FD_CAN1_TCU_01_10ms_P11_TCU_EngRpmDisSta_Tx_P11 0


/*******************************************************************************
**                       Rx Group Signals Handle Ids                          **
*******************************************************************************/
#define ComXf_FD_CAN1_BSD_01_50ms_P11_TCU_EngRpmDisSta_Rx_P11 0


/*******************************************************************************
**                            Function Declaration                            **
*******************************************************************************/

#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
extern FUNC(void, COMXF_CODE) ComXf_Init(
  P2CONST(ComXf_ConfigType, AUTOMATIC, COMXF_APPL_CONST) config);
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"
#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
extern FUNC(uint8, COMXF_CODE) ComXf_Inv_Com_ComISignalGroup_MsgGr_E2E_FD_CAN1_BSD_01_50ms_P11(
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) buffer,
  VAR(uint32, AUTOMATIC) bufferLength,
  P2VAR(MsgGr_E2E_FD_CAN1_BSD_01_50ms_P11, AUTOMATIC, COMXF_APPL_DATA)
  dataElement);
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
extern FUNC(uint8, COMXF_CODE) ComXf_Com_ComISignalGroup_MsgGr_E2E_FD_CAN1_TCU_01_10ms_P11(
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) buffer,
  P2VAR(uint32, AUTOMATIC, COMXF_APPL_DATA) bufferLength,
  P2CONST(MsgGr_E2E_FD_CAN1_TCU_01_10ms_P11, AUTOMATIC, COMXF_APPL_CONST)
  dataElement);
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"



/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA RULE CHECKER)                   **
*******************************************************************************/
/* polyspace-end MISRA-C3:20.1 */

#endif /* COMXF_APIS_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
