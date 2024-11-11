/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**                                                                            **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: CanTp_PCTypes.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CanTp                                                 **
**                                                                            **
**  PURPOSE   : To provide precompile configuration specific data types       **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.1.0     13-Sep-2023   HieuTM8        #CP44-2819                          **
** 1.0.3.1   22-Jun-2022   SMKwon         CP44-94                             **
** 1.0.3     30-May-2022   HieuTM8        R44-Redmine #26803                  **
** 1.0.1     28-Feb-2022   HieuTM8        R44-Redmine #20400, #19344          **
** 1.0.0     04-Dec-2020   SMKwon         Initial Version                     **
*******************************************************************************/

#ifndef CANTP_PCTYPES_H
#define CANTP_PCTYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanTp_IntTypes.h"       /* CanTp Internal types Header File */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* @Trace: SWS_CanTp_00267 */
/* @Trace: CanTp_SUD_MACRO_004 */
/* SWS_CanTp_00267: Version number macros for checking */
/* AUTOSAR specification version information */
#define CANTP_PCTYPES_AR_RELEASE_MAJOR_VERSION    0x04u
#define CANTP_PCTYPES_AR_RELEASE_MINOR_VERSION    0x04u
#define CANTP_PCTYPES_AR_RELEASE_REVISION_VERSION 0x00u

/* File version information */
#define CANTP_PCTYPES_SW_MAJOR_VERSION            0x01u
#define CANTP_PCTYPES_SW_MINOR_VERSION            0x01u

/*******************************************************************************
**                      Pre-Compile Options                                   **
*******************************************************************************/

/*******************************************************************************
**                       Global Symbols                                       **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/* @Trace: SWS_CanTp_00286 */
/* SWS_CanTp_00286, SWS_CanTp_00120: All the necessary information (Channel number, Timing parameter) is configured inside
 * the CAN Transport Layer module */
/* @Trace: CanTp_SUD_GLOBALVAR_001 */
#define CANTP_START_SEC_CONST_8
#include "MemMap.h"
extern CONST(uint8, CANTP_CONST) CanTp_PaddingByte[CANTP_SIXTEEN];
#define CANTP_STOP_SEC_CONST_8
#include "MemMap.h"

#define CANTP_START_SEC_CONST_8
#include "MemMap.h"
/* @Trace: CanTp_SUD_GLOBALVAR_002 */
extern CONST(uint8, CANTP_CONST) CanTp_ChannelMapping[CANTP_TOTAL_RX_TX_CHANNELS];
#define CANTP_STOP_SEC_CONST_8
#include "MemMap.h"

/* If support PostBuild */
#if (CANTP_VARIANT_POSTBUILD_SUPPORT == STD_ON)
#define CANTP_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern P2CONST(CanTp_ConfigType, AUTOMATIC, CANTP_CONST) Variant_Select;
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#else /* End of if (STD_ON ==  CANTP_VARIANT_POSTBUILD_SUPPORT) */

#if (CANTP_TX_NSDU == STD_ON)
#define CANTP_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
/* @Trace: CanTp_SUD_GLOBALVAR_004 */
extern CONST(CanTp_TxNsduStaticType, CANTP_CONST) CanTp_TxSduStatic[CANTP_NO_OF_TXSDUSTATIC];
#define CANTP_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
#endif


#if (CANTP_RX_NSDU == STD_ON)
#define CANTP_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
/* @Trace: CanTp_SUD_GLOBALVAR_005 */
extern CONST(CanTp_RxNsduStaticType, CANTP_CONST) CanTp_RxSduStatic[CANTP_NO_OF_RXSDUSTATIC];
#define CANTP_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
#endif

#define CANTP_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
/* @Trace: CanTp_SUD_GLOBALVAR_006 */
extern CONST(CanTp_RxExtPdusType, CANTP_CONST) CanTp_RxExtPdus[CANTP_NO_OF_RXEXTPDUS];
#define CANTP_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"

#if (CANTP_RX_NSDU == STD_ON)
#define CANTP_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
/* @Trace: CanTp_SUD_GLOBALVAR_008 */
extern CONST(CanTp_RxNSduDynamicType, CANTP_CONST) CanTp_RxSduDynamic[CANTP_MAXNO_RX_SDU];
#define CANTP_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
#endif

#if (CANTP_TX_NSDU == STD_ON)
#define CANTP_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
/* @Trace: CanTp_SUD_GLOBALVAR_010 */
extern CONST(CanTp_TxNSduDynamicType, CANTP_CONST) CanTp_TxSduDynamic[CANTP_NO_OF_TXSDUSTATIC];
#define CANTP_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
#endif


#ifndef INVALID_RXEXTFCPDUS
#define CANTP_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
/* Extended RxNsdu Flow Control ROM array */
/* @Trace: CanTp_SUD_GLOBALVAR_011 */
extern CONST(CanTp_RxExtPdusType, CANTP_CONST) CanTp_RxExtFcPdus[CANTP_NO_OF_RXEXTPDUS];
#define CANTP_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
#endif

#ifndef INVALID_NSAORNAESDUMAPPING
#if ((CANTP_TX_EXTENDED_ADDRESS == STD_ON) ||\
(CANTP_TX_MIXED_ADDRESS == STD_ON) ||\
(CANTP_TX_MIXED29BIT_ADDRESS == STD_ON) ||\
(CANTP_TX_NORMALFIXED_ADDRESS == STD_ON) ||\
(CANTP_RX_EXTENDED_ADDRESS == STD_ON) ||\
(CANTP_RX_MIXED_ADDRESS == STD_ON) ||\
(CANTP_RX_MIXED29BIT_ADDRESS == STD_ON) ||\
(CANTP_RX_NORMALFIXED_ADDRESS == STD_ON))

#define CANTP_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
/* Nsa and Sdu Mapping */
/* @Trace: CanTp_SUD_GLOBALVAR_012 */
extern CONST(CanTp_RxNSaOrNAeSduMappingType, CANTP_CONST)
  CanTp_NSaOrNAeSduMapping[CANTP_NO_OF_NSAORNAESDUMAPPING];
#define CANTP_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
#endif /* End of #if ((CANTP_TX_EXTENDED_ADDRESS == STD_ON) ||\
(CANTP_TX_MIXED_ADDRESS == STD_ON) ||\
(CANTP_TX_MIXED29BIT_ADDRESS == STD_ON) ||\
(CANTP_RX_EXTENDED_ADDRESS == STD_ON) ||\
(CANTP_RX_MIXED_ADDRESS == STD_ON) ||\
(CANTP_RX_MIXED29BIT_ADDRESS == STD_ON)) */
#endif

#define CANTP_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#if (CANTP_RX_PHYSICAL_ADDRESSING == STD_ON)
/* @Trace: CanTp_SUD_GLOBALVAR_016 */
extern VAR(CanTp_STminBsType, CANTP_VAR) CanTp_STminBs[CANTP_MAXNO_RX_SDU];
#endif /* End of #if (CANTP_RX_PHYSICAL_ADDRESSING == STD_ON) */
#define CANTP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

#define CANTP_START_SEC_CONFIG_DATA_PREBUILD_8
#include "MemMap.h"
/* @Trace: CanTp_SUD_GLOBALVAR_003 */
extern CONST(CanTp_ChannelType, CANTP_CONST) CanTp_RxSduMap[CANTP_NO_OF_RXSDUMAP];
#define CANTP_STOP_SEC_CONFIG_DATA_PREBUILD_8
#include "MemMap.h"

#endif /* End of if(STD_OFF == CANTP_VARIANT_POSTBUILD_SUPPORT) */

#define CANTP_START_SEC_CONST_8
#include "MemMap.h"
/* @Trace: CanTp_SUD_GLOBALVAR_009 */
extern CONST(uint8, CANTP_CONST) CanTp_BytePos[CANTP_FIVE];
#define CANTP_STOP_SEC_CONST_8
#include "MemMap.h"

#if (CANTP_TX_PHYSICAL_ADDRESSING == STD_ON)
#define CANTP_START_SEC_CONST_8
#include "MemMap.h"
/* @Trace: CanTp_SUD_GLOBALVAR_007 */
extern CONST(uint8, CANTP_CONST) CanTp_STminMapping[CANTP_TEN];
#define CANTP_STOP_SEC_CONST_8
#include "MemMap.h"
#endif

#define CANTP_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* @Trace: SWS_CanTp_00285 SWS_CanTp_00289 */
/* SWS_CanTp_00285: The connection channels are only destined for CAN TP internal use */
/* SWS_CanTp_00289: Number of channels will be configured by tools */
/* @Trace: CanTp_SUD_GLOBALVAR_013 */
extern VAR(CanTp_ChannelRamType, CANTP_VAR) CanTp_ChannelTxRam[CANTP_TOTAL_RX_TX_CHANNELS];
#define CANTP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CANTP_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* @Trace: SWS_CanTp_00285 SWS_CanTp_00289 */
/* SWS_CanTp_00285: The connection channels are only destined for CAN TP internal use */
/* SWS_CanTp_00289: Number of channels will be configured by tools */
/* @Trace: CanTp_SUD_GLOBALVAR_019 */
extern VAR(CanTp_ChannelRamType, CANTP_VAR) CanTp_ChannelRxRam[CANTP_TOTAL_RX_TX_CHANNELS];
#define CANTP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CANTP_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
/* @Trace: CanTp_SUD_GLOBALVAR_014 */
extern VAR(uint16, CANTP_VAR) CanTp_Timers[CANTP_TOTAL_RX_TX_CHANNELS][CANTP_SIX];
#define CANTP_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

#define CANTP_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
/* @Trace: CanTp_SUD_GLOBALVAR_015 */
extern VAR(uint8, CANTP_VAR) CanTp_StMinTimers[CANTP_TOTAL_RX_TX_CHANNELS];
#define CANTP_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define CANTP_START_SEC_CONST_8
#include "MemMap.h"
/* @Trace: CanTp_SUD_GLOBALVAR_017 */
extern CONST(uint8, CANTP_CONST) CanTp_DiscreteDlcDataLength[CANTP_SEVEN];
#define CANTP_STOP_SEC_CONST_8
#include "MemMap.h"


/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#endif /* CANTP_PCTYPES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

