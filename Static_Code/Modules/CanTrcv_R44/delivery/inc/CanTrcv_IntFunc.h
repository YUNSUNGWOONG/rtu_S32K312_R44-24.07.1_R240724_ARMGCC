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
**  SRC-MODULE: CanTrcv_IntFunc.h                                             **
**                                                                            **
**  TARGET    : General CAN Transceiver                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN Transceiver Driver Module                         **
**                                                                            **
**  PURPOSE   : Header file of CanTrcv_IntFunc.c                              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision       Date                By               Description            **
********************************************************************************
** 1.0.11         08-Feb-2024         Yubin Song       #CP44-3726             **
** 1.0.6          17-Oct-2022         HieuTM8          #CP44-877              **
** 1.0.5          30-Jul-2022         HieuTM8          #CP44-512              **
** 1.0.1          14-Sep-2021         DuyNHP2          Redmine #20148         **
** 1.0.0          15-Dec-2020         JsLim            Initial version        **
*******************************************************************************/
/* @Trace: SRS_BSW_00300 */
#ifndef CANTRCV_INTFUNC_H
#define CANTRCV_INTFUNC_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: CanTrcv_SUD_FILE_001 */
/* CanIf callback header file */
#include "CanIf_CanTrcv.h"
/* Can Transceiver header file */
#include "CanTrcv.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define CANTRCV_START_SEC_CODE
#include "MemMap.h"

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetNormalMode(
  VAR(uint8, AUTOMATIC) transceiver);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetNormalMode_HW_USED_EN_STB(
  CONST(uint8, AUTOMATIC) transceiver);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetNormalMode_XJA11XX(
  CONST(uint8, AUTOMATIC) transceiver);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetNormalMode_ArisuCan(
  CONST(uint8, AUTOMATIC) transceiver);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetNormalMode_TLE9255W(
  CONST(uint8, AUTOMATIC) transceiver);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetNormalMode_TCAN1145(
  CONST(uint8, AUTOMATIC) transceiver);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetNormalMode_TCAN1043A(
  CONST(uint8, AUTOMATIC) transceiver);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetNormalMode_Other_HW(
  CONST(uint8, AUTOMATIC) transceiver);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetStandbyMode(
  VAR(uint8, AUTOMATIC) transceiver);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetStandbyMode_HW_USED_EN_STB(
  VAR(uint8, AUTOMATIC) transceiver);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetStandbyMode_ArisuCan(
  VAR(uint8, AUTOMATIC) transceiver);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetStandbyMode_XJA11XX(
  VAR(uint8, AUTOMATIC) transceiver);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetStandbyMode_TLE9255W(
  VAR(uint8, AUTOMATIC) transceiver);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetStandbyMode_TCAN1145(
  VAR(uint8, AUTOMATIC) transceiver);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetStandbyMode_Other_HW(
  VAR(uint8, AUTOMATIC) transceiver);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetSleepMode(
  VAR(uint8, AUTOMATIC) transceiver);

#if ((STD_ON == CANTRCV_ARISUCAN_SUPPORTED) && \
  (STD_ON == CANTRCV_SPI_SUPPORTED))

extern FUNC(void, CANTRCV_CODE) CanTrcv_ArisuCan_Init(
  P2CONST(ArisuCan_CanConfigType, AUTOMATIC, CANTRCV_CONST) ptrArisuCanCfg);

extern FUNC(void, CANTRCV_CODE) CanTrcv_IntArisuCan_RequestCanMode(
  VAR(CanTrcv_HwType, AUTOMATIC) canTrcv,
  VAR(ArisuCan_SBCModeType, AUTOMATIC) mode);

extern FUNC(CanTrcv_TrcvModeType, CANTRCV_CODE) CanTrcv_ArisuCan_CheckCanMode(
  VAR(CanTrcv_HwType, AUTOMATIC) canTrcv,
  VAR(ArisuCan_SBCModeType, AUTOMATIC) mode);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_IntArisuCan_SetMode(
  VAR(ArisuCan_SBCModeType, AUTOMATIC) mode);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_ArisuCan_IntReadStatus(
  VAR(CanTrcv_ArisuCanType, AUTOMATIC) address,
  P2VAR(CanTrcv_ArisuCanType, AUTOMATIC, CANTRCV_VAR) data);

extern FUNC(Std_ReturnType, CANTRCV_CODE)
  CanTrcv_ArisuCan_IntPowerDownMode(void);

extern FUNC(ArisuCan_SBCModeType, CANTRCV_CODE)
  CanTrcv_ArisuCan_IntGetInternalSBCMode(void);

extern FUNC(Std_ReturnType, CANTRCV_CODE)
  CanTrcv_ArisuCan_IntChangeStopMode(
    CONST(ArisuCan_CanConfigType, AUTOMATIC) canTrcvConfigure);

extern FUNC(Std_ReturnType, CANTRCV_CODE)
  CanTrcv_ArisuCan_IntVbsenseEnable(void);

extern FUNC(Std_ReturnType, CANTRCV_CODE)
  CanTrcv_ArisuCan_IntVbsenseDisable(void);

extern FUNC(Std_ReturnType, CANTRCV_CODE) ArisuCan_SendSPI(
  P2CONST(uint16, AUTOMATIC, CANTRCV_CONST) SpiSrcData,
  P2VAR(uint16, AUTOMATIC, CANTRCV_VAR) SpiDestData);

#endif /* STD_ON == CANTRCV_ARISUCAN_SUPPORTED */

#if (((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
  (STD_ON == CANTRCV_TCAN1145_SUPPORTED)) && \
  (STD_ON == CANTRCV_HW_PN_SUPPORTED))
extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_IntClearSyserrFlag(
  CONST(uint8, AUTOMATIC) transceiver);
#endif /* (((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
  (STD_ON == CANTRCV_TCAN1145_SUPPORTED)) && \
  (STD_ON == CANTRCV_HW_PN_SUPPORTED)) */

#if ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
  (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
  (STD_ON == CANTRCV_TLE9255W_SUPPORTED))
extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_IntInitializeBySpi(
  CONST(uint8, AUTOMATIC) transceiver);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_IntDeInitializeBySpi(
  CONST(uint8, AUTOMATIC) transceiver);
#endif /* ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
  (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
  (STD_ON == CANTRCV_TLE9255W_SUPPORTED)) */

#if (STD_ON == CANTRCV_HW_PN_SUPPORTED)
extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_IntInitializePN(
  CONST(uint8, AUTOMATIC) transceiver);

#if (STD_ON == CANTRCV_HW_POR_SUPPORTED)
extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_IntGetPorFlag(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(boolean, AUTOMATIC, CANTRCV_APPL_DATA) ptrPorFlag);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_IntClearPorFlag(
  CONST(uint8, AUTOMATIC) transceiver);
#endif /* (STD_ON == CANTRCV_HW_POR_SUPPORTED) */

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_IntGetSyserrFlag(
  #if ((STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
       (STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
       (STD_ON == CANTRCV_TLE9255W_SUPPORTED))
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(boolean, AUTOMATIC, CANTRCV_APPL_DATA) ptrSyserrFlag
  #else
  void
  #endif /* ((STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
       (STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
       (STD_ON == CANTRCV_TLE9255W_SUPPORTED)) */
  );

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_IntGetTrcvSystemData(
  CONST(uint8, AUTOMATIC) transceiver
  #if ((STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
       (STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
       (STD_ON == CANTRCV_TLE9255W_SUPPORTED))
  ,P2VAR(uint32, AUTOMATIC, CANTRCV_APPL_DATA) ptrSystemData
  #endif /* ((STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
       (STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
       (STD_ON == CANTRCV_TLE9255W_SUPPORTED)) */
  );

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_IntReadTrcvTimeoutFlag(
  #if ((STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
       (STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
       (STD_ON == CANTRCV_TLE9255W_SUPPORTED))
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(CanTrcv_TrcvFlagStateType, AUTOMATIC, CANTRCV_APPL_DATA) ptrFlagState
  #else
  void
  #endif /* ((STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
       (STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
       (STD_ON == CANTRCV_TLE9255W_SUPPORTED)) */
  );

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_IntClearTrcvTimeoutFlag(
  CONST(uint8, AUTOMATIC) transceiver);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_IntReadTrcvSilenceFlag(
  #if ((STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
       (STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
       (STD_ON == CANTRCV_TLE9255W_SUPPORTED))
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(CanTrcv_TrcvFlagStateType, AUTOMATIC, CANTRCV_APPL_DATA) ptrFlagState
  #else
  void
  #endif /* ((STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
       (STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
       (STD_ON == CANTRCV_TLE9255W_SUPPORTED)) */
  );

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_IntSetPNActivationState(
  CONST(uint8, AUTOMATIC) transceiver,
  CONST(CanTrcv_PNActivationType, AUTOMATIC) activationState);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_IntClearTrcvWufFlag(
  CONST(uint8, AUTOMATIC) transceiver);
  
extern FUNC(void, CANTRCV_CODE) CanTrcv_IntCheckWakeFlag(
  CONST(uint8, AUTOMATIC) transceiver);
#endif /* (STD_ON == CANTRCV_HW_PN_SUPPORTED) */

#if (STD_ON == CANTRCV_WAKEUP_SUPPORTED)

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_IntSetWakeupMode(
  CONST(uint8, AUTOMATIC) transceiver,
  CONST(CanTrcv_TrcvWakeupModeType, AUTOMATIC) trcvWakeupMode);

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_IntCheckWakeup(
  CONST(uint8, AUTOMATIC) transceiver);

extern FUNC(void, CANTRCV_CODE) CanTrcv_IntMainFunction(
  CONST(uint8, AUTOMATIC) transceiver);

extern FUNC(void, CANTRCV_CODE) CanTrcv_IntCheckWakeupInit(
  CONST(uint8, AUTOMATIC) transceiver);
#endif /* (STD_ON == CANTRCV_WAKEUP_SUPPORTED) */

extern FUNC(void, CANTRCV_CODE) CanTrcv_IntMainFunctionDiagnostics(
  CONST(uint8, AUTOMATIC) transceiver);

#define CANTRCV_STOP_SEC_CODE
#include "MemMap.h"

#endif /* CANTRCV_INTFUNC_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
