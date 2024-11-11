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
**  SRC-MODULE: CanTrcv_IntFunc.c                                             **
**                                                                            **
**  TARGET    : General CAN Transceiver                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN Transceiver Driver Module                         **
**                                                                            **
**  PURPOSE   : Provision APIs of CAN Transceiver Module                      **
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
** 1.0.9          03-Mar-2023         HieuTM8          #CP44-1492, #CP44-1689 **
**                                                     #CP44-1775, #CP44-1774 **
**                                                     #CP44-1777             **
** 1.0.8          09-Dec-2022         HieuTM8          #CP44-1194             **
** 1.0.6          14-Oct-2022         HieuTM8          #CP44-649, #CP44-709   **
**                                                     #CP44-917              **
** 1.0.5          30-Jul-2022         HieuTM8          #CP44-512              **
** 1.0.4          16-May-2022         HieuTM8, HjSeong Redmine #26586, #27336 **
** 1.0.3          29-Apr-2022         HieuTM8          Redmine #26478         **
** 1.0.1          14-Sep-2021         DuyNHP2          Redmine #20148         **
** 1.0.0          15-Dec-2020         JsLim            Initial version        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: CanTrcv_SUD_FILE_001 */
/* Internal function header file */
#include "CanTrcv_IntFunc.h"
/* Can Transceiver header file */
#include "CanTrcv.h"
/* Global variables header file */
#include "CanTrcv_Globals.h"
/* Can Transceiver sheduler header file */
#include "SchM_CanTrcv.h"

#if (STD_OFF == CANTRCV_SUPPORT_AR403)
#if (STD_ON == CANTRCV_TIMER_1US16BIT)
/* Time service header file */
#include "Tm.h"
#endif /* (STD_ON == CANTRCV_TIMER_1US16BIT) */
#endif /*STD_OFF == CANTRCV_SUPPORT_AR403*/


/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

#define CANTRCV_START_SEC_CODE
#include "MemMap.h"

#if (((STD_ON == CANTRCV_TIMER_1US16BIT) && \
      (STD_OFF == CANTRCV_SUPPORT_AR403)) || \
      (STD_ON == CANTRCV_SUPPORT_AR403))
static FUNC(void, CANTRCV_CODE) CanTrcv_Delay(
  volatile VAR(uint32, AUTOMATIC) ticks);
#endif /* (((STD_ON == CANTRCV_TIMER_1US16BIT) && \
      (STD_OFF == CANTRCV_SUPPORT_AR403)) || \
      (STD_ON == CANTRCV_SUPPORT_AR403)) */

#if (STD_ON == CANTRCV_SPI_SUPPORTED)
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SendSpi(
  CONST(uint8, AUTOMATIC) transceiver,
  P2CONST(Spi_DataBufferType, AUTOMATIC, CANTRCV_CONST) ptrSpiSrcData,
  P2VAR(Spi_DataBufferType, AUTOMATIC, CANTRCV_APPL_DATA) ptrSpiDesData);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SpiTransmit(
  VAR(boolean, AUTOMATIC) spiAccessSynchronous,
  VAR(Spi_SequenceType, AUTOMATIC) sequenceId);

#if ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
  (STD_ON == CANTRCV_TLE9255W_SUPPORTED) || \
  (STD_ON == CANTRCV_TCAN1145_SUPPORTED))
#if (STD_OFF == CANTRCV_SUPPORT_AR403)
#if (STD_ON == CANTRCV_SPI_ASYNCTRANSMIT_SUPPORTED)
static FUNC(Spi_SeqResultType, CANTRCV_CODE) CanTrcv_SpiWaitTimeout(
  CONST(uint8, AUTOMATIC) transceiver);
#endif /* (STD_ON == CANTRCV_SPI_ASYNCTRANSMIT_SUPPORTED) */
#endif /*(STD_OFF == CANTRCV_SUPPORT_AR403)*/

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_ReadReg(
  CONST(uint8, AUTOMATIC) transceiver,
  CONST(uint8, AUTOMATIC) address,
  P2VAR(uint8, AUTOMATIC, CANTRCV_VAR) ptrDesData);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_WriteReg(
  CONST(uint8, AUTOMATIC) transceiver,
  CONST(uint8, AUTOMATIC) address,
  CONST(uint8, AUTOMATIC) data);

#endif /* ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
  (STD_ON == CANTRCV_TLE9255W_SUPPORTED) || \
  (STD_ON == CANTRCV_TCAN1145_SUPPORTED)) */
#endif /* (STD_ON == CANTRCV_SPI_SUPPORTED) */

#define CANTRCV_STOP_SEC_CODE
#include "MemMap.h"

#if ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
  (STD_ON == CANTRCV_TLE9255W_SUPPORTED) || \
  (STD_ON == CANTRCV_TCAN1145_SUPPORTED))

#define CANTRCV_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
static CONST(CanTrcv_WriteReadReg_Type, CANTRCV_CONST) CanTrcv_WriteReadReg[] = 
{
  {
    &CanTrcv_WriteReg,
    &CanTrcv_ReadReg
  }
};
#define CANTRCV_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif /* ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
  (STD_ON == CANTRCV_TLE9255W_SUPPORTED) || \
  (STD_ON == CANTRCV_TCAN1145_SUPPORTED))*/

#define CANTRCV_START_SEC_CODE
#include "MemMap.h"

#if (STD_ON == CANTRCV_HW_SUPPORT_SLEEP_MODE)
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetSleepModeByDio(
  VAR(uint8, AUTOMATIC) transceiver);
#endif /* (STD_ON == CANTRCV_HW_SUPPORT_SLEEP_MODE) */

#if (STD_ON == CANTRCV_XJA11XX_SUPPORTED)
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXSetModeControl(
  CONST(uint8, AUTOMATIC) transceiver,
  CONST(XJA11XX_ModeControlType, AUTOMATIC) mode);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXGetModeControl(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(CanTrcv_TrcvModeType, AUTOMATIC, CANTRCV_APPL_DATA) ptrMode);

#if(STD_OFF == CANTRCV_SUPPORT_AR403)
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXSetCanMode(
  CONST(uint8, AUTOMATIC) transceiver,
  CONST(XJA11XX_CanModeType, AUTOMATIC) canMode);
#endif

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXInit(
  CONST(uint8, AUTOMATIC) transceiver,
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXInit_ClearEventSrc(
  CONST(uint8, AUTOMATIC) transceiver,
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork,
  P2VAR(uint8, AUTOMATIC, CANTRCV_VAR) data);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXDeInit(
  CONST(uint8, AUTOMATIC) transceiver);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXResetMemory(
  CONST(uint8, AUTOMATIC) transceiver);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXSetLockControl(
  CONST(uint8, AUTOMATIC) transceiver,
  CONST(XJA11XX_LockCtrlType, AUTOMATIC) lockType);

#if (STD_ON == CANTRCV_HW_PN_SUPPORTED)

#if (STD_ON == CANTRCV_HW_POR_SUPPORTED)
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXGetPorFlag(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(uint8, AUTOMATIC, CANTRCV_APPL_DATA) ptrPorFlag);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXClearPorFlag(
  CONST(uint8, AUTOMATIC) transceiver);
#endif /* (STD_ON == CANTRCV_HW_POR_SUPPORTED) */

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXResetIdentifierType(
  CONST(uint8, AUTOMATIC) transceiver);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXSetDataMask(
  CONST(uint8, AUTOMATIC) transceiver);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXResetDataMask(
  CONST(uint8, AUTOMATIC) transceiver);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXGetSyserrFlag(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(uint8, AUTOMATIC, CANTRCV_APPL_DATA) ptrSyserrFlag);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXClearSyserrFlag(
  CONST(uint8, AUTOMATIC) transceiver);

static FUNC(Std_ReturnType, CANTRCV_CODE)
  CanTrcv_XJA11XXConfigurePartialNetworking(
    CONST(uint8, AUTOMATIC) transceiver);

static FUNC(Std_ReturnType, CANTRCV_CODE)
  CanTrcv_XJA11XXConfigureIdentifierType(CONST(uint8, AUTOMATIC) transceiver);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXGetTrcvSystemData(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(uint32, AUTOMATIC, CANTRCV_APPL_DATA) ptrSystemData);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXReadTrcvTimeoutFlag(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(CanTrcv_TrcvFlagStateType, AUTOMATIC, CANTRCV_APPL_DATA) ptrFlagState);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXClearTrcvTimeoutFlag(
  CONST(uint8, AUTOMATIC) transceiver);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXReadTrcvSilenceFlag(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(CanTrcv_TrcvFlagStateType, AUTOMATIC, CANTRCV_APPL_DATA) ptrFlagState);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXSetPNActivationState(
  CONST(uint8, AUTOMATIC) transceiver,
  CONST(CanTrcv_PNActivationType, AUTOMATIC) activationState);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXClearTrcvWufFlag(
  CONST(uint8, AUTOMATIC) transceiver);
#endif /* (STD_ON == CANTRCV_HW_PN_SUPPORTED) */

#if (STD_ON == CANTRCV_WAKEUP_SUPPORTED)
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXCheckWakeFlag(
  CONST(uint8, AUTOMATIC) transceiver,
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork);

static FUNC(void, CANTRCV_CODE) CanTrcv_XJA11XXMainFunction(
  CONST(uint8, AUTOMATIC) transceiver);

#endif /* (STD_ON == CANTRCV_WAKEUP_SUPPORTED) */
#endif /* (STD_ON == CANTRCV_XJA11XX_SUPPORTED) */

#if (STD_ON == CANTRCV_TLE9255W_SUPPORTED)

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TLE9255WSetModeControl(
  CONST(uint8, AUTOMATIC) transceiver,
  CONST(TLE9255W_ModeControlType, AUTOMATIC) mode);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TLE9255WGetModeControl(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(CanTrcv_TrcvModeType, AUTOMATIC, CANTRCV_APPL_DATA) ptrMode);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TLE9255WInit(
  CONST(uint8, AUTOMATIC) transceiver,
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TLE9255WDeInit(
  CONST(uint8, AUTOMATIC) transceiver);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TLE9255WResetIdentifierType(
  CONST(uint8, AUTOMATIC) transceiver);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TLE9255WResetDataControl(
  CONST(uint8, AUTOMATIC) transceiver);

#if (STD_ON == CANTRCV_HW_PN_SUPPORTED)

#if (STD_ON == CANTRCV_HW_POR_SUPPORTED)
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TLE9255WGetPorFlag(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(uint8, AUTOMATIC, CANTRCV_APPL_DATA) ptrPorFlag);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TLE9255WClearPorFlag(
  CONST(uint8, AUTOMATIC) transceiver);
#endif /* (STD_ON == CANTRCV_HW_POR_SUPPORTED) */

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TLE9255WGetSyserrFlag(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(uint8, AUTOMATIC, CANTRCV_APPL_DATA) ptrSyserrFlag);

static FUNC(Std_ReturnType, CANTRCV_CODE)
  CanTrcv_TLE9255WConfigurePartialNetworking(
    CONST(uint8, AUTOMATIC) transceiver);

static FUNC(Std_ReturnType, CANTRCV_CODE)
  CanTrcv_TLE9255WConfigureIdentifierType(CONST(uint8, AUTOMATIC) transceiver);

static FUNC(Std_ReturnType, CANTRCV_CODE)
  CanTrcv_TLE9255WConfigureDataControl(CONST(uint8, AUTOMATIC) transceiver);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TLE9255WGetTrcvSystemData(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(uint32, AUTOMATIC, CANTRCV_APPL_DATA) ptrSystemData);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TLE9255WReadTrcvTimeoutFlag(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(CanTrcv_TrcvFlagStateType, AUTOMATIC, CANTRCV_APPL_DATA) ptrFlagState);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TLE9255WClearTrcvTimeoutFlag(
  CONST(uint8, AUTOMATIC) transceiver);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TLE9255WReadTrcvSilenceFlag(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(CanTrcv_TrcvFlagStateType, AUTOMATIC, CANTRCV_APPL_DATA) ptrFlagState);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TLE9255WSetPNActivationState(
  CONST(uint8, AUTOMATIC) transceiver,
  CONST(CanTrcv_PNActivationType, AUTOMATIC) activationState);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TLE9255WClearTrcvWufFlag(
  CONST(uint8, AUTOMATIC) transceiver);
#endif /* (STD_ON == CANTRCV_HW_PN_SUPPORTED) */

#if (STD_ON == CANTRCV_WAKEUP_SUPPORTED)
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TLE9255WCheckWakeFlag(
  CONST(uint8, AUTOMATIC) transceiver,
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork);

static FUNC(void, CANTRCV_CODE) CanTrcv_TLE9255WMainFunction(
  CONST(uint8, AUTOMATIC) transceiver);

#endif /* (STD_ON == CANTRCV_WAKEUP_SUPPORTED) */
#endif /* (STD_ON == CANTRCV_TLE9255W_SUPPORTED) */

#if (STD_ON == CANTRCV_TCAN1145_SUPPORTED)
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TCAN1145SetModeControl(
  CONST(uint8, AUTOMATIC) transceiver,
  CONST(TCAN1145_ModeControlType, AUTOMATIC) mode);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TCAN1145GetModeControl(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(CanTrcv_TrcvModeType, AUTOMATIC, CANTRCV_APPL_DATA) ptrMode);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TCAN1145Init(
  CONST(uint8, AUTOMATIC) transceiver,
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TCAN1145DeInit(
  CONST(uint8, AUTOMATIC) transceiver);

#if (STD_ON == CANTRCV_HW_PN_SUPPORTED)

#if (STD_ON == CANTRCV_HW_POR_SUPPORTED)
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TCAN1145GetPorFlag(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(uint8, AUTOMATIC, CANTRCV_APPL_DATA) ptrPorFlag);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TCAN1145ClearPorFlag(
  CONST(uint8, AUTOMATIC) transceiver);
#endif /* (STD_ON == CANTRCV_HW_POR_SUPPORTED) */

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TCAN1145SetDataMask(
  CONST(uint8, AUTOMATIC) transceiver);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TCAN1145ResetDataMask(
  CONST(uint8, AUTOMATIC) transceiver);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TCAN1145GetSyserrFlag(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(uint8, AUTOMATIC, CANTRCV_APPL_DATA) ptrSyserrFlag);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TCAN1145ClearSyserrFlag(
  CONST(uint8, AUTOMATIC) transceiver);

static FUNC(Std_ReturnType, CANTRCV_CODE)
  CanTrcv_TCAN1145ConfigurePartialNetworking(
    CONST(uint8, AUTOMATIC) transceiver);

static FUNC(Std_ReturnType, CANTRCV_CODE)
  CanTrcv_TCAN1145ConfigureIdentifierType(CONST(uint8, AUTOMATIC) transceiver);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TCAN1145GetTrcvSystemData(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(uint32, AUTOMATIC, CANTRCV_APPL_DATA) ptrSystemData);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TCAN1145ReadTrcvTimeoutFlag(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(CanTrcv_TrcvFlagStateType, AUTOMATIC, CANTRCV_APPL_DATA) ptrFlagState);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TCAN1145ClearTrcvTimeoutFlag(
  CONST(uint8, AUTOMATIC) transceiver);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TCAN1145ReadTrcvSilenceFlag(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(CanTrcv_TrcvFlagStateType, AUTOMATIC, CANTRCV_APPL_DATA) ptrFlagState);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TCAN1145SetPNActivationState(
  CONST(uint8, AUTOMATIC) transceiver,
  CONST(CanTrcv_PNActivationType, AUTOMATIC) activationState);

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TCAN1145ClearTrcvWufFlag(
  CONST(uint8, AUTOMATIC) transceiver);
#endif /* (STD_ON == CANTRCV_HW_PN_SUPPORTED) */

#if (STD_ON == CANTRCV_WAKEUP_SUPPORTED)
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TCAN1145CheckWakeFlag(
  CONST(uint8, AUTOMATIC) transceiver,
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork);

static FUNC(void, CANTRCV_CODE) CanTrcv_TCAN1145MainFunction(
  CONST(uint8, AUTOMATIC) transceiver);

#endif /* (STD_ON == CANTRCV_WAKEUP_SUPPORTED) */
#endif /* (STD_ON == CANTRCV_TCAN1145_SUPPORTED) */

/*******************************************************************************
** Function Name        : CanTrcv_SetNormalMode                               **
**                                                                            **
** Service ID           : Not Applicable                                      **
**                                                                            **
** Description          : This service initiates the transition to the Normal **
**                        operating mode with complete functionality.         **
**                                                                            **
** Sync/Async           : None                                                **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : transceiver - CAN transceiver ID                    **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Can Transceiver driver must be initialized.         **
**                                                                            **
** Remarks              : Global variable(s)  : CanTrcv_CanTrcvNetwork        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Icu_DisableNotification,                            **
**                        Dio_WriteChannel,                                   **
**                        Dio_ReadChannel, CanTrcv_IntArisuCan_SetMode,       **
**                        CanTrcv_IntArisuCan_RequestCanMode,                 **
**                        CanTrcv_ArisuCan_CheckCanMode,                      **
**                        CanTrcv_XJA11XXGetModeControl,                      **
**                        CanTrcv_XJA11XXSetModeControl,                      **
**                        CanTrcv_XJA11XXSetCanMode,                          **
**                        CanTrcv_TLE9255WSetModeControl,                     **
**                        CanTrcv_TLE9255WGetModeControl,                     **
**                        SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA,       **
**                        SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA,        **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00100 SWS_CanTrcv_00102
  SWS_CanTrcv_00171 SWS_CanTrcv_00173 SWS_CanTrcv_00086 SWS_CanTrcv_00163
*/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetNormalMode(
  VAR(uint8, AUTOMATIC) transceiver)
{

  #if((STD_ON == CANTRCV_HW_USED_EN_STB_CONTROL_PIN) || \
    (STD_ON == CANTRCV_ARISUCAN_SUPPORTED) || \
    (STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
    (STD_ON == CANTRCV_TLE9255W_SUPPORTED) || \
    (STD_ON == CANTRCV_ICU_CHANNEL_USED) || \
    (STD_ON == CANTRCV_TCAN1145_SUPPORTED))
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  #endif
  VAR(Std_ReturnType, AUTOMATIC) returnStatus;

  /* Get the pointer to the structure of the requested network */
  #if ((STD_ON == CANTRCV_HW_USED_EN_STB_CONTROL_PIN) || \
      (STD_ON == CANTRCV_ARISUCAN_SUPPORTED) || \
      (STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
      (STD_ON == CANTRCV_TLE9255W_SUPPORTED) || \
      (STD_ON == CANTRCV_ICU_CHANNEL_USED) || \
      (STD_ON == CANTRCV_TCAN1145_SUPPORTED)) 
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];
  #endif
  #if (STD_OFF==CANTRCV_SUPPORT_AR403)
  #if (STD_ON == CANTRCV_ICU_CHANNEL_USED)
  /* Check Can Transceiver channel has configured Icu channel or not */
  if (CANTRCV_UNUSED != ptrCanTrcvNetwork->IcuChannelId)
  {
    /* @Trace: CanTrcv_SUD_API_111 */
    /* Disable the wakeup event notification */
    Icu_DisableNotification(ptrCanTrcvNetwork->IcuChannelId);
  }
  else
  {
    /* Nothing to do */
  }
  #endif /* (STD_ON == CANTRCV_ICU_CHANNEL_USED) */
  #endif /*(STD_OFF==CANTRCV_SUPPORT_AR403)*/
  /* Check whether Transceiver Used STB, EN PINS */
  #if (STD_ON == CANTRCV_HW_USED_EN_STB_CONTROL_PIN)
  if ((CANTRCV_TJA1054 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1055 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1041A == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1043 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1463 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE62542G == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE62543G == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE6251G == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE62513G == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1041 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1054A == ptrCanTrcvNetwork->CanTrcvHwDev))
  {
    returnStatus = CanTrcv_SetNormalMode_HW_USED_EN_STB(transceiver);
  }
  #endif /* (STD_ON == CANTRCV_HW_USED_EN_STB_CONTROL_PIN) */

  #if (STD_ON == CANTRCV_ARISUCAN_SUPPORTED)
  if ((CANTRCV_ARISU_CAN0 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_ARISU_CAN1 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_ARISU_CAN2 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_ARISU_CAN3 == ptrCanTrcvNetwork->CanTrcvHwDev))
  {
    returnStatus = CanTrcv_SetNormalMode_ArisuCan(transceiver);
  }
  #endif /* (STD_ON == CANTRCV_ARISUCAN_SUPPORTED) */
  #if (STD_ON == CANTRCV_XJA11XX_SUPPORTED)
  if ((CANTRCV_TJA1145 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_UJA1169 == ptrCanTrcvNetwork->CanTrcvHwDev))
  {
    returnStatus = CanTrcv_SetNormalMode_XJA11XX(transceiver);
  }
  #endif /* (STD_ON == CANTRCV_XJA11XX_SUPPORTED) */
  #if (STD_ON == CANTRCV_TLE9255W_SUPPORTED)
  if (CANTRCV_TLE9255W == ptrCanTrcvNetwork->CanTrcvHwDev)
  {
    returnStatus = CanTrcv_SetNormalMode_TLE9255W(transceiver);
  }
  #endif /* (STD_ON == CANTRCV_TLE9255W_SUPPORTED) */
  #if (STD_ON == CANTRCV_TCAN1145_SUPPORTED)
  if (CANTRCV_TCAN1145 == ptrCanTrcvNetwork->CanTrcvHwDev)
  {
    returnStatus = CanTrcv_SetNormalMode_TCAN1145(transceiver);
  }
  #endif /* (STD_ON == CANTRCV_TCAN1145_SUPPORTED) */
  #if (STD_ON == CANTRCV_TCAN1043A_SUPPORTED)
  if (CANTRCV_TCAN1043A == ptrCanTrcvNetwork->CanTrcvHwDev)
  {
    returnStatus = CanTrcv_SetNormalMode_TCAN1043A(transceiver);
  }
  #endif /* (STD_ON == CANTRCV_TCAN1043A_SUPPORTED) */
  #if (STD_ON == CANTRCV_HW_USED_EN_STB_CONTROL_PIN) || \
      (STD_ON == CANTRCV_ARISUCAN_SUPPORTED) || \
      (STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
      (STD_ON == CANTRCV_TLE9255W_SUPPORTED) || \
      (STD_ON == CANTRCV_TCAN1145_SUPPORTED) 
  if ((CANTRCV_TJA1054 != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_TJA1055 != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_TJA1041A != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_TJA1043 != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_TJA1463 != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_TLE62542G != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_TLE62543G != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_TLE6251G != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_TLE62513G != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_TJA1041 != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_TJA1054A != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_ARISU_CAN0 != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_ARISU_CAN1 != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_ARISU_CAN2 != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_ARISU_CAN3 != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_TJA1145 != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_UJA1169 != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_TLE9255W != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_TCAN1145 != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_TCAN1043A != ptrCanTrcvNetwork->CanTrcvHwDev))
  #endif
  {
    returnStatus = CanTrcv_SetNormalMode_Other_HW(transceiver);
  }
  /* polyspace +1 RTE:NIVL [Justified:Low] "Its value has been checked, no impact" */
  return returnStatus;
}

/*******************************************************************************
** Function Name        : CanTrcv_SetStandbyMode                              **
**                                                                            **
** Service ID           : Not Applicable                                      **
**                                                                            **
** Description          : This service initiates the transition to the        **
**                        Standby operating mode with complete functionality. **
**                                                                            **
** Sync/Async           : None                                                **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : transceiver - CAN transceiver ID                    **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Can Transceiver driver must be initialized.         **
**                                                                            **
** Remarks              : Global variable(s)  : CanTrcv_CanTrcvNetwork        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Icu_EnableNotification,                             **
**                        Dio_WriteChannel,                                   **
**                        Dio_ReadChannel, CanTrcv_IntArisuCan_RequestCanMode,**
**                        CanTrcv_ArisuCan_CheckCanMode, ArisuCan_SendSPI,    **
**                        CanTrcv_XJA11XXGetModeControl,                      **
**                        CanTrcv_XJA11XXSetModeControl,                      **
**                        CanTrcv_TLE9255WSetModeControl,                     **
**                        CanTrcv_TLE9255WGetModeControl,                     **
**                        SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA,       **
**                        SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA,        **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00100 SWS_CanTrcv_00102
  SWS_CanTrcv_00171 SWS_CanTrcv_00172 SWS_CanTrcv_00086 SWS_CanTrcv_00163
*/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetStandbyMode(
  VAR(uint8, AUTOMATIC) transceiver)
{
  #if (STD_ON == CANTRCV_ICU_CHANNEL_USED) || \
      (STD_ON == CANTRCV_HW_USED_EN_STB_CONTROL_PIN) || \
      (STD_ON == CANTRCV_ARISUCAN_SUPPORTED) || \
      (STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
      (STD_ON == CANTRCV_TLE9255W_SUPPORTED) || \
      (STD_ON == CANTRCV_TCAN1145_SUPPORTED) 
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  #endif
  VAR(Std_ReturnType, AUTOMATIC) returnStatus;

  /* Get the pointer to the structure of the requested network */
  #if(STD_ON == CANTRCV_ICU_CHANNEL_USED) || \
      (STD_ON == CANTRCV_HW_USED_EN_STB_CONTROL_PIN) || \
      (STD_ON == CANTRCV_ARISUCAN_SUPPORTED) || \
      (STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
      (STD_ON == CANTRCV_TLE9255W_SUPPORTED) || \
      (STD_ON == CANTRCV_TCAN1145_SUPPORTED) 
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];
  #endif

  #if (STD_OFF == CANTRCV_SUPPORT_AR403)
  #if (STD_ON == CANTRCV_ICU_CHANNEL_USED)
  /* Check Can Transceiver channel has configured Icu channel or not */
  if (CANTRCV_UNUSED != ptrCanTrcvNetwork->IcuChannelId)
  {
    /* @Trace: CanTrcv_SUD_API_121 */
    /* Enable the wakeup event notification */
    Icu_EnableNotification(ptrCanTrcvNetwork->IcuChannelId);
  }
  else
  {
    /* Nothing to do */
  }
  #endif /* (STD_ON == CANTRCV_ICU_CHANNEL_USED) */
  #endif /*#if (STD_OFF == CANTRCV_SUPPORT_AR403)*/
  /* Transceiver has EN/STB control pin */
  #if (STD_ON == CANTRCV_HW_USED_EN_STB_CONTROL_PIN)
  if ((CANTRCV_TLE6251G == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE62513G == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1055 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1043 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1463 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1054 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE62542G == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE62543G == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1041A == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1041 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1054A == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TCAN1043A == ptrCanTrcvNetwork->CanTrcvHwDev))
  {
    returnStatus = CanTrcv_SetStandbyMode_HW_USED_EN_STB(transceiver);
  }
  #endif /* (STD_ON == CANTRCV_HW_USED_EN_STB_CONTROL_PIN) */

  #if (STD_ON == CANTRCV_ARISUCAN_SUPPORTED)
  if ((CANTRCV_ARISU_CAN0 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_ARISU_CAN1 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_ARISU_CAN2 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_ARISU_CAN3 == ptrCanTrcvNetwork->CanTrcvHwDev))
  {
    returnStatus = CanTrcv_SetStandbyMode_ArisuCan(transceiver);
  }
  #endif /* (STD_ON == CANTRCV_ARISUCAN_SUPPORTED) */
  #if (STD_ON == CANTRCV_XJA11XX_SUPPORTED)
  if ((CANTRCV_TJA1145 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_UJA1169 == ptrCanTrcvNetwork->CanTrcvHwDev))
  {
    returnStatus = CanTrcv_SetStandbyMode_XJA11XX(transceiver);
  }
  #endif /* (STD_ON == CANTRCV_XJA11XX_SUPPORTED) */
  #if (STD_ON == CANTRCV_TLE9255W_SUPPORTED)
  if (CANTRCV_TLE9255W == ptrCanTrcvNetwork->CanTrcvHwDev)
  {
    returnStatus = CanTrcv_SetStandbyMode_TLE9255W(transceiver);
  }
  #endif /* (STD_ON == CANTRCV_TLE9255W_SUPPORTED) */
  #if (STD_ON == CANTRCV_TCAN1145_SUPPORTED)
  if (CANTRCV_TCAN1145 == ptrCanTrcvNetwork->CanTrcvHwDev)
  {
    returnStatus = CanTrcv_SetStandbyMode_TCAN1145(transceiver);
  }
  #endif /* (STD_ON == CANTRCV_TCAN1145_SUPPORTED) */

  #if (STD_ON == CANTRCV_HW_USED_EN_STB_CONTROL_PIN) || \
      (STD_ON == CANTRCV_ARISUCAN_SUPPORTED) || \
      (STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
      (STD_ON == CANTRCV_TLE9255W_SUPPORTED) || \
      (STD_ON == CANTRCV_TCAN1145_SUPPORTED) 
  if ((CANTRCV_TLE6251G != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_TLE62513G != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_TJA1055 != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_TJA1043 != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_TJA1463 != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_TJA1054 != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_TLE62542G != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_TLE62543G != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_TJA1041A != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_TJA1041 != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_TJA1054A != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_ARISU_CAN0 != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_ARISU_CAN1 != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_ARISU_CAN2 != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_ARISU_CAN3 != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_TJA1145 != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_UJA1169 != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_TLE9255W != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_TCAN1145 != ptrCanTrcvNetwork->CanTrcvHwDev) &&
    (CANTRCV_TCAN1043A != ptrCanTrcvNetwork->CanTrcvHwDev) )
  #endif
  {
    returnStatus = CanTrcv_SetStandbyMode_Other_HW(transceiver);
  }
  /* polyspace +1 RTE:NIVL [Justified:Low] "Its value has been checked, no impact" */
  return returnStatus;
}

/*******************************************************************************
** Function Name        : CanTrcv_SetSleepMode                                **
**                                                                            **
** Service ID           : Not Applicable                                      **
**                                                                            **
** Description          : This service initiates the transition to the Sleep  **
**                        operating mode with complete functionality.         **
**                                                                            **
** Sync/Async           : None                                                **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : transceiver - CAN transceiver ID                    **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : canTrcvMode - CAN Transceiver Mode                  **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Can Transceiver driver must be initialized.         **
**                                                                            **
** Remarks              : Global variable(s)  : CanTrcv_CanTrcvNetwork        **
**                                                                            **
**                        Function(s) invoked : CanTrcv_SetSleepModeByDio,    **
**                        CanTrcv_XJA11XXGetModeControl,                      **
**                        CanTrcv_XJA11XXSetModeControl,                      **
**                        CanTrcv_TLE9255WSetModeControl,                     **
**                        CanTrcv_TLE9255WGetModeControl,                     **
**                        SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA,       **
**                        SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA         **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00100 SWS_CanTrcv_00102
  SWS_CanTrcv_00105 SWS_CanTrcv_00086 SWS_CanTrcv_00163
*/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetSleepMode(
  VAR(uint8, AUTOMATIC) transceiver)
{
  #if (STD_ON == CANTRCV_HW_SUPPORT_SLEEP_MODE)
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  #endif /* (STD_ON == CANTRCV_HW_SUPPORT_SLEEP_MODE) */
  VAR(Std_ReturnType, AUTOMATIC) returnStatus;

  #if (STD_ON == CANTRCV_ARISUCAN_SUPPORTED) || \
    (STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
    (STD_ON == CANTRCV_TLE9255W_SUPPORTED) || \
    (STD_ON == CANTRCV_TCAN1145_SUPPORTED) 
  VAR(CanTrcv_TrcvModeType, AUTOMATIC) canTrcvMode;

  /* Initialize return value */
  canTrcvMode = CANTRCV_TRCVMODE_SLEEP;
  #endif
  #if (STD_ON == CANTRCV_HW_SUPPORT_SLEEP_MODE)
  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];
  /* Check device has support sleep mode */
  if ((CANTRCV_NCV7342 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1040 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1042 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1044 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1050 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1051 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1057 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE6250G == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE6251DS == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE7250G == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE7250LE == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE9250SJ == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE9251VSJ == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1059 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TCAN1044 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TCAN1057 == ptrCanTrcvNetwork->CanTrcvHwDev))
  #endif /* (STD_ON == CANTRCV_HW_SUPPORT_SLEEP_MODE) */
  {
    /* @Trace: CanTrcv_SUD_API_117 */
    /* Set return value as E_NOT_OK */
    returnStatus = E_NOT_OK;
  }
  #if (STD_ON == CANTRCV_HW_SUPPORT_SLEEP_MODE)
  #if (STD_ON == CANTRCV_ARISUCAN_SUPPORTED)
  else if ((CANTRCV_ARISU_CAN0 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_ARISU_CAN1 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_ARISU_CAN2 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_ARISU_CAN3 == ptrCanTrcvNetwork->CanTrcvHwDev))
  {
    /* @Trace: CanTrcv_SUD_API_118 */
    SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA();

    /* ARISU-CAN CanTrcv Mode Change */
    CanTrcv_IntArisuCan_RequestCanMode(
      ptrCanTrcvNetwork->CanTrcvHwDev, ARISUCAN_SBCMODE_SLEEP);

    /* Check ARISU-CAN CanTrcv Mode */
    canTrcvMode = CanTrcv_ArisuCan_CheckCanMode(
      ptrCanTrcvNetwork->CanTrcvHwDev, ARISUCAN_SBCMODE_SLEEP);

    if (CANTRCV_TRCVMODE_STANDBY != canTrcvMode)
    {
      returnStatus = E_NOT_OK;
    }
    else
    {
      returnStatus = E_OK;
    }

    SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA();
  }
  #endif /* (STD_ON == CANTRCV_ARISUCAN_SUPPORTED) */
  #if (STD_ON == CANTRCV_XJA11XX_SUPPORTED)
  else if ((CANTRCV_TJA1145 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_UJA1169 == ptrCanTrcvNetwork->CanTrcvHwDev))
  {
    /* @Trace: CanTrcv_SUD_API_119 */
    SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA();
    /* Check Transceiver is Sleep Mode */
    returnStatus = CanTrcv_XJA11XXGetModeControl(transceiver, &canTrcvMode);
    if ((E_NOT_OK != returnStatus) && (CANTRCV_TRCVMODE_SLEEP != canTrcvMode))
    {
      /* Set Mode Control as Sleep Mode */
      returnStatus = CanTrcv_XJA11XXSetModeControl(transceiver,
        XJA11XX_SLEEP_MODE);
      /* Get current Mode Control */
      returnStatus |= CanTrcv_XJA11XXGetModeControl(transceiver, &canTrcvMode);
      if (CANTRCV_TRCVMODE_SLEEP != canTrcvMode)
      {
        returnStatus = E_NOT_OK;
      }
      else
      {
        /* Nothing to do */
      }
    }
    else
    {
      /* Nothing to do */
    }
    SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA();
  }
  #endif /* (STD_ON == CANTRCV_XJA11XX_SUPPORTED) */
  #if (STD_ON == CANTRCV_TLE9255W_SUPPORTED)
  else if (CANTRCV_TLE9255W == ptrCanTrcvNetwork->CanTrcvHwDev)
  {
    /* @Trace: CanTrcv_SUD_API_120 */
    SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA();
    /* Set Mode Control as Sleep Mode */
    returnStatus = CanTrcv_TLE9255WSetModeControl(transceiver,
      TLE9255W_SLEEP_MODE);
    /* Get current Mode Control */
    returnStatus |= CanTrcv_TLE9255WGetModeControl(transceiver, &canTrcvMode);
    if (CANTRCV_TRCVMODE_SLEEP != canTrcvMode)
    {
      returnStatus = E_NOT_OK;
    }
    else
    {
      /* Nothing to do */
    }
    SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA();
  }
  #endif /* (STD_ON == CANTRCV_TLE9255W_SUPPORTED) */
  #if (STD_ON == CANTRCV_TCAN1145_SUPPORTED)
  else if (CANTRCV_TCAN1145 == ptrCanTrcvNetwork->CanTrcvHwDev)
  {
    /* @Trace: CanTrcv_SUD_API_381 */
    SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA();
    /* Check Transceiver is Sleep Mode */
    returnStatus = CanTrcv_TCAN1145GetModeControl(transceiver, &canTrcvMode);
    if ((E_NOT_OK != returnStatus) && (CANTRCV_TRCVMODE_SLEEP != canTrcvMode))
    {
      /* Set Mode Control as Sleep Mode */
      returnStatus = CanTrcv_TCAN1145SetModeControl(transceiver,
        TCAN1145_SLEEP_MODE);
      /* Get current Mode Control */
      returnStatus |= CanTrcv_TCAN1145GetModeControl(transceiver, &canTrcvMode);
      if (CANTRCV_TRCVMODE_SLEEP != canTrcvMode)
      {
        returnStatus = E_NOT_OK;
      }
      else
      {
        /* Nothing to do */
      }
    }
    else
    {
      /* Nothing to do */
    }
    SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA();
  }
  #endif /* (STD_ON == CANTRCV_TCAN1145_SUPPORTED) */
  else
  {
    returnStatus = CanTrcv_SetSleepModeByDio(transceiver);
  }
  #endif /* (STD_ON == CANTRCV_NO_SUPPORT_SLEEP_MODE) */
  CANTRCV_UNUSED_VAL(transceiver);
  return returnStatus;
}

/*******************************************************************************
** Function Name        : CanTrcv_SetSleepModeByDio                           **
**                                                                            **
** Service ID           : Not Applicable                                      **
**                                                                            **
** Description          : This service initiates the transition to the Sleep  **
**                        operating mode with complete functionality          **
**                        on devices via DIO.                                 **
**                                                                            **
** Sync/Async           : None                                                **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : transceiver - CAN transceiver ID                    **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter   : E_OK: Set Sleep mode successful.                      **
**                      E_NOT_OK: Set Sleep mode not successful.              **
**                                                                            **
** Preconditions        : Can Transceiver driver must be initialized.         **
**                                                                            **
** Remarks              : Global variable(s)  : CanTrcv_CanTrcvNetwork        **
**                                                                            **
**                        Function(s) invoked : Dio_WriteChannel,             **
**                        Dio_ReadChannel, CanTrcv_Delay,                     **
**                        SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA,       **
**                        SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA         **
*******************************************************************************/
#if (STD_ON == CANTRCV_HW_SUPPORT_SLEEP_MODE)
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetSleepModeByDio(
  VAR(uint8, AUTOMATIC) transceiver)
{
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  VAR(Dio_LevelType, AUTOMATIC) retValPin1;
  VAR(Dio_LevelType, AUTOMATIC) retValPin2;
  VAR(Std_ReturnType, AUTOMATIC) returnStatus;

  /* Initialize return value */
  returnStatus = E_OK;
  
  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];
  #if (STD_ON == CANTRCV_HW_DIO_SUPPORT_SLEEP_MODE)
  if ((CANTRCV_TJA1041A == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1043 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1463 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1041 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TCAN1043A == ptrCanTrcvNetwork->CanTrcvHwDev))
  {
    /* @Trace: CanTrcv_SUD_API_142 */
    SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA();
    /* Invoke the Dio_WriteChannel to set the Standby pin to level-Low */
    Dio_WriteChannel((ptrCanTrcvNetwork->SelectPin1), (Dio_LevelType) STD_LOW);
    /* Invoke the Dio_WriteChannel to set the EN pin to level-High */
    Dio_WriteChannel((ptrCanTrcvNetwork->SelectPin2), (Dio_LevelType) STD_HIGH);
    
    /* Delay */
    #if (((STD_ON == CANTRCV_TIMER_1US16BIT) && \
      (STD_OFF == CANTRCV_SUPPORT_AR403)) || \
      (STD_ON == CANTRCV_SUPPORT_AR403))
    CanTrcv_Delay(CANTRCV_WAIT_TIME);
    #endif /* (((STD_ON == CANTRCV_TIMER_1US16BIT) && \
      (STD_OFF == CANTRCV_SUPPORT_AR403)) || \
      (STD_ON == CANTRCV_SUPPORT_AR403))*/

    retValPin1 = Dio_ReadChannel(ptrCanTrcvNetwork->SelectPin1);
    retValPin2 = Dio_ReadChannel(ptrCanTrcvNetwork->SelectPin2);
    if ((STD_LOW != retValPin1) || (STD_HIGH != retValPin2))
    {
      returnStatus = E_NOT_OK;
    }
    else
    {
      /* Nothing to do */
    }
    SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA();
  }
  else
  #endif /* (STD_ON == CANTRCV_HW_DIO_SUPPORT_SLEEP_MODE) */
  {
    /* @Trace: CanTrcv_SUD_API_143 */
    /* Step 1/2 - GotoSleep */
    SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA();
    /* Invoke the Dio_WriteChannel to set the Standby pin to level-Low */
    Dio_WriteChannel((ptrCanTrcvNetwork->SelectPin1), (Dio_LevelType) STD_LOW);
    /* Invoke the Dio_WriteChannel to set the EN pin to level-High */
    Dio_WriteChannel((ptrCanTrcvNetwork->SelectPin2), (Dio_LevelType) STD_HIGH);
    /* Delay */
	#if (((STD_ON == CANTRCV_TIMER_1US16BIT) && \
      (STD_OFF == CANTRCV_SUPPORT_AR403)) || \
      (STD_ON == CANTRCV_SUPPORT_AR403))
    CanTrcv_Delay(CANTRCV_WAIT_TIME);
  	#endif /* (((STD_ON == CANTRCV_TIMER_1US16BIT) && \
      (STD_OFF == CANTRCV_SUPPORT_AR403)) || \
      (STD_ON == CANTRCV_SUPPORT_AR403))*/
    retValPin1 = Dio_ReadChannel(ptrCanTrcvNetwork->SelectPin1);
    retValPin2 = Dio_ReadChannel(ptrCanTrcvNetwork->SelectPin2);
    if ((STD_LOW != retValPin1) || (STD_HIGH != retValPin2))
    {
      returnStatus = E_NOT_OK;
    }
    else
    {
      /* Nothing to do */
    }

    /* Step 2/2 - Sleep */
    /* Invoke the Dio_WriteChannel to set the Standby pin to level-Low */
    Dio_WriteChannel((ptrCanTrcvNetwork->SelectPin1), (Dio_LevelType) STD_LOW);
    /* Invoke the Dio_WriteChannel to set the EN pin to level-Low */
    Dio_WriteChannel((ptrCanTrcvNetwork->SelectPin2), (Dio_LevelType) STD_LOW);

    retValPin1 = Dio_ReadChannel(ptrCanTrcvNetwork->SelectPin1);
    retValPin2 = Dio_ReadChannel(ptrCanTrcvNetwork->SelectPin2);
    if ((STD_LOW != retValPin1) || (STD_LOW != retValPin2))
    {
      returnStatus = E_NOT_OK;
    }
    else
    {
      /* Nothing to do */
    }
    SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA();
  }
  return returnStatus;
}
#endif /* (STD_ON == CANTRCV_HW_SUPPORT_SLEEP_MODE) */

#if (((STD_ON == CANTRCV_TIMER_1US16BIT) && \
      (STD_OFF == CANTRCV_SUPPORT_AR403)) || \
      (STD_ON == CANTRCV_SUPPORT_AR403))
/*******************************************************************************
** Function Name        : CanTrcv_Delay                                       **
**                                                                            **
** Service ID           : Not Applicable                                      **
**                                                                            **
** Description          : Delay function.                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ticks - Time delay                                  **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global variable(s)     : None                       **
**                        Function(s) invoked    : Tm_BusyWait1us16bit        **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00230 SWS_CanTrcv_00086
*/
static FUNC(void, CANTRCV_CODE) CanTrcv_Delay(
  volatile VAR(uint32, AUTOMATIC) ticks)
{
  #if((STD_OFF == CANTRCV_SUPPORT_AR403) && (STD_ON == CANTRCV_TIMER_1US16BIT))
  /* @Trace: CanTrcv_SUD_API_144 */
  /* Using Tm_BusyWait1us16bit to delay */
  Tm_BusyWait1us16bit((uint8)ticks);
  #endif /*((STD_OFF == CANTRCV_SUPPORT_AR403) && (STD_ON == CANTRCV_TIMER_1US16BIT))*/
  #if (STD_ON == CANTRCV_SUPPORT_AR403)
  /*Prevent for MISRA C:2012 17.8 */
  /* @Trace: CanTrcv_SUD_API_379 */
  volatile uint32 Lddticks = ticks;

  while(CANTRCV_ZERO != Lddticks)
  {
    /* Decrement the counter value */
    Lddticks--;
  }
  #endif /*(STD_ON == CANTRCV_SUPPORT_AR403)*/
}
#endif /*(((STD_ON == CANTRCV_TIMER_1US16BIT) && \
      (STD_OFF == CANTRCV_SUPPORT_AR403)) || \
      (STD_ON == CANTRCV_SUPPORT_AR403)) */

/*******************************************************************************
**                      ARISU CAN                                             **
*******************************************************************************/

#if ((STD_ON == CANTRCV_ARISUCAN_SUPPORTED) && \
  (STD_ON == CANTRCV_SPI_SUPPORTED))
/*******************************************************************************
** Function Name      : CanTrcv_IntArisuCan_SetMode                           **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : Set SBC mode                                          **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : Mode                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK:     Will be returned if the request for         **
**                                transceiver mode change has been accepted.  **
**                      E_NOT_OK: Will be returned if the request for         **
**                                transceiver mode change has not been        **
**                                accepted or any parameter is out of the     **
**                                allowed range.                              **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global variable(s) : ArisuCan_SpiDestData,            **
**                      ArisuCan_SBCModeSts                                   **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      ArisuCan_SendSPI                                      **
*******************************************************************************/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_IntArisuCan_SetMode(
  VAR(ArisuCan_SBCModeType, AUTOMATIC) mode)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  VAR(CanTrcv_ArisuCanType, AUTOMATIC) readData;
  VAR(uint16, AUTOMATIC) spiSrcData;
  VAR(uint16, AUTOMATIC) modeSts;

  /* Initialize local variables */
  returnValue = E_NOT_OK;

  #if (CANTRCV_DEV_ERROR_DETECT == STD_ON)
  /* Check input mode validation */
  if ((mode != ARISUCAN_SBCMODE_INIT)
    && (mode != ARISUCAN_SBCMODE_NORMAL)
    && (mode != ARISUCAN_SBCMODE_STOP)
    && (mode != ARISUCAN_SBCMODE_SLEEP)
    && (mode != ARISUCAN_SBCMODE_RESTART))
  {
    /* Nothing to do */
  }
  else
  #endif
  {

    /* @Trace: CanTrcv_SUD_API_290 */
    spiSrcData =((uint16)mode << (uint16)ARISUCAN_M_S_CTRL_MODE_POS) |
      (uint16)ARISUCAN_M_S_CTRL_REG_W;

    returnValue = ArisuCan_SendSPI(&spiSrcData, &ArisuCan_SpiDestData);

    if (E_OK == returnValue)
    {
      /* @Trace: CanTrcv_SUD_API_291 */
      returnValue = CanTrcv_ArisuCan_IntReadStatus(ARISUCAN_M_S_CTRL_REG_R,
        &readData);

      if (E_OK == returnValue)
      {
        modeSts = ((readData & ARISUCAN_M_S_CTRL_MODE_MASK) >> CANTRCV_SIX);
        /* polyspace +1 MISRA2012:10.5 [Justified:Low] "Operation is guaranteed that does not exceed ArisuCan_SBCModeType." */
        ArisuCan_SBCModeSts = (ArisuCan_SBCModeType)(modeSts);
      }
      else
      {
        /* Nothing to do */
      }
    }
    else
    {
      /* Nothing to do */
    }
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_IntArisuCan_RequestCanMode                    **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This service will request SBC mode of Arisu-CAN.      **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : canTrcv - This parameter contains H/W Specific name.  **
**                      mode    - This parameter contains the desired         **
**                                operating mode.                             **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global variable(s) : CanTrcv_ArisuCanSts,             **
**                      CanTrcv_ArisuChannelUsed, CanTrcv_ArisuCan,           **
**                      ArisuCan_SpiDestData                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      Dio_WriteChannel,                                     **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00086 */
/* @Trace: CanTrcv_SUD_API_316 */
/* polyspace -begin MISRA-C3:18.1 [Justified:Low] "The value of  canTrcv is already checked before being passed through the function." */
FUNC(void, CANTRCV_CODE) CanTrcv_IntArisuCan_RequestCanMode(
  VAR(CanTrcv_HwType, AUTOMATIC) canTrcv,
  VAR(ArisuCan_SBCModeType, AUTOMATIC) mode)
{
  P2CONST(ArisuCan_CanConfigType, AUTOMATIC, CANTRCV_CONST) ptrCanCfg;
  VAR(uint16, AUTOMATIC) spiSrcData;

  /* Initialize local variable */
  ptrCanCfg = &CanTrcv_ArisuCan[mode];
  /* polyspace -begin MISRA-C3:D4.1 [Justified:Low] "The value of  canTrcv is already checked before being passed through the function." */
  switch(canTrcv)
  {
    case CANTRCV_ARISU_CAN0:
      /* @Trace: CanTrcv_SUD_API_293 */
      /* polyspace +4 MISRA-C3:18.1 [Justified:Low] "CanTrcv_ArisuCan is guaranteed by Generator." */
      /* polyspace +3 MISRA-C3:D4.1 [Justified:Low] "CanTrcv_ArisuCan is guaranteed by Generator." */
      /* polyspace +2 RTE:IDP [Justified:Low] "CanTrcv_ArisuCan is guaranteed by Generator." */
      spiSrcData = (uint16)ptrCanCfg->ArisuCan0Mode;
      spiSrcData = ((uint16)((uint16)spiSrcData <<
        (uint16)ARISUCAN_BUS_CTRL_MODE_POS) |
        (uint16)(ARISUCAN_BUS_CTRL_0_REG_W));
      CanTrcv_ArisuCanSts.ArisuCan0Mode = ptrCanCfg->ArisuCan0Mode;
      CanTrcv_ArisuChannelUsed.ArisuCan0Used = ARISUCAN_CONFIGURE;
      (void)ArisuCan_SendSPI(&spiSrcData, &ArisuCan_SpiDestData);
      break;

    case CANTRCV_ARISU_CAN1:
      /* @Trace: CanTrcv_SUD_API_294 */
      /* polyspace +3 MISRA-C3:18.1 [Justified:Low] "CanTrcv_ArisuCan is guaranteed by Generator." */
      /* polyspace +2 MISRA-C3:D4.1 [Justified:Low] "CanTrcv_ArisuCan is guaranteed by Generator." */
      /* polyspace +1 RTE:IDP [Justified:Low] "CanTrcv_ArisuCan is guaranteed by Generator." */
      CanTrcv_ArisuCanSts.ArisuCan1Mode = ptrCanCfg->ArisuCan1Mode;
      CanTrcv_ArisuChannelUsed.ArisuCan1Used = ARISUCAN_CONFIGURE;
      if (CANTRCV_UNUSED == (uint32)ptrCanCfg->ArisuCan2Mode)
      /* polyspace +3 RTE:UNR [Justified:Low] "This branch occurs when ARISU_CAN1 is configured, ARISU_CAN2 is not." */
      {
        /* @Trace: CanTrcv_SUD_API_295 */
        spiSrcData = (uint16)ptrCanCfg->ArisuCan1Mode;
      }
      else
      {
        /* @Trace: CanTrcv_SUD_API_296 */
        spiSrcData = (uint16)((uint16)(CanTrcv_ArisuCanSts.ArisuCan1Mode) |
          (uint16)((uint16)(CanTrcv_ArisuCanSts.ArisuCan2Mode) <<
          (uint16)(ARISUCAN_BUS_CTRL_CANTRCV_3_MODE_POS)));
      }
      spiSrcData = ((uint16)((uint16)spiSrcData <<
        (uint16)ARISUCAN_BUS_CTRL_MODE_POS) |
        (uint16)(ARISUCAN_BUS_CTRL_2_REG_W));
      /* @Trace: CanTrcv_SUD_API_297 */
      (void)ArisuCan_SendSPI(&spiSrcData, &ArisuCan_SpiDestData);
      break;

    case CANTRCV_ARISU_CAN2:
      /* @Trace: CanTrcv_SUD_API_298 */
      /* polyspace +3 MISRA-C3:18.1 [Justified:Low] "CanTrcv_PartialNetwork is guaranteed by Generator." */
      /* polyspace +2 MISRA-C3:D4.1 [Justified:Low] "CanTrcv_ArisuCan is guaranteed by Generator." */
      /* polyspace +1 RTE:IDP [Justified:Low] "CanTrcv_ArisuCan is guaranteed by Generator." */
      CanTrcv_ArisuCanSts.ArisuCan2Mode = ptrCanCfg->ArisuCan2Mode;
      CanTrcv_ArisuChannelUsed.ArisuCan2Used = ARISUCAN_CONFIGURE;
      if (CANTRCV_UNUSED == (uint32)ptrCanCfg->ArisuCan1Mode)
      /* polyspace +3 RTE:UNR [Justified:Low] "This branch occurs when ARISU_CAN2 is configured, ARISU_CAN1 is not." */
      {
        /* @Trace: CanTrcv_SUD_API_299 */
        spiSrcData = (uint16)((uint16)(ptrCanCfg->ArisuCan2Mode) <<
          (uint16)(ARISUCAN_BUS_CTRL_CANTRCV_3_MODE_POS));
      }
      else
      {
        /* @Trace: CanTrcv_SUD_API_300 */
        spiSrcData = (uint16)((uint16)(CanTrcv_ArisuCanSts.ArisuCan1Mode) |
          (uint16)((uint16)(CanTrcv_ArisuCanSts.ArisuCan2Mode) <<
          (uint16)(ARISUCAN_BUS_CTRL_CANTRCV_3_MODE_POS)));
      }
      spiSrcData = ((uint16)((uint16)(spiSrcData & ARISU_8_BIT) <<
        (uint16)ARISUCAN_BUS_CTRL_MODE_POS) |
        (uint16)(ARISUCAN_BUS_CTRL_2_REG_W));
        /* @Trace: CanTrcv_SUD_API_301 */
      (void)ArisuCan_SendSPI(&spiSrcData, &ArisuCan_SpiDestData);
      break;

    case CANTRCV_ARISU_CAN3:
      /* @Trace: CanTrcv_SUD_API_302 */
      /* polyspace +3 MISRA-C3:18.1 [Justified:Low] "CanTrcv_ArisuCan is guaranteed by Generator." */
      /* polyspace +2 MISRA-C3:D4.1 [Justified:Low] "CanTrcv_ArisuCan is guaranteed by Generator." */
      /* polyspace +1 RTE:IDP [Justified:Low] "CanTrcv_ArisuCan is guaranteed by Generator." */
      spiSrcData = (uint16)ptrCanCfg->ArisuCan3Mode;
      spiSrcData = ((uint16)((uint16)spiSrcData << (uint16)ARISUCAN_BUS_CTRL_MODE_POS) |
        (uint16)(ARISUCAN_BUS_CTRL_3_REG_W));
      CanTrcv_ArisuCanSts.ArisuCan3Mode = ptrCanCfg->ArisuCan3Mode;
      CanTrcv_ArisuChannelUsed.ArisuCan3Used = ARISUCAN_CONFIGURE;
      (void)ArisuCan_SendSPI(&spiSrcData, &ArisuCan_SpiDestData);
      break;

    default:
      /* Nothing to do */
      break;
  }

  /* polyspace -end MISRA-C3:D4.1 [Justified:Low] "The value of  canTrcv is already checked before being passed through the function." */

}
/* polyspace -end MISRA-C3:18.1 [Justified:Low] "The value of  canTrcv is already checked before being passed through the function." */
/*******************************************************************************
** Function Name        : ArisuCan_SendSPI                                    **
**                                                                            **
** Service ID           : 0x11                                                **
**                                                                            **
** Description          : This service will send data via SPI for ArisuCan.   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : SpiSrcData - Pointer to source data.                **
**                                                                            **
** In/Out Parameters    : SpiDestData - Pointer to destination buffer.        **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: Transmit success.                             **
**                      : E_NOT_OK: Transmit not success.                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : CanTrcv_SendSpi               **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_BSW_00357 SRS_HWM_00006 */
FUNC(Std_ReturnType, CANTRCV_CODE) ArisuCan_SendSPI(
  P2CONST(uint16, AUTOMATIC, CANTRCV_CONST) SpiSrcData,
  P2VAR(uint16, AUTOMATIC, CANTRCV_VAR) SpiDestData)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  VAR(uint8, AUTOMATIC) transceiver;
  /* @Trace: CanTrcv_SUD_API_249 */
  /* Initialize local variables */
  returnValue = E_OK;

  /* Check ArisuCan status */
  if (ARISUCAN_OK == ArisuCan_ReadFlag)
  {
    /* Get the first ArisuCan configured */
    /* @Trace: CanTrcv_SUD_API_251 */
    for(transceiver = CANTRCV_ZERO;
      transceiver < CANTRCV_NUM_OF_NETWORKS; transceiver++)
    {
      ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];
      if ((ptrCanTrcvNetwork->CanTrcvHwDev <= ARISUCAN_END_OFFSET)
      && (ptrCanTrcvNetwork->CanTrcvHwDev >= ARISUCAN_START_OFFSET))
      {
        /* @Trace: CanTrcv_SUD_API_250 */
        SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA();
        /* Set status of ArisuCan as busy */
        ArisuCan_ReadFlag = ARISUCAN_BUSY;

        SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA();
        /* Send request via SPI */
        /* polyspace -begin MISRA2012:11.8 [Justified:Low] "SpiSrcData is guaranteed that the value not exceed its data type." */
        /* @Trace: CanTrcv_SUD_API_252 */
        /* polyspace +4 MISRA-C3:11.8 [Justified:Low] "The cast is just an indication of data type" */
        returnValue = CanTrcv_SendSpi(transceiver,
          (Spi_DataBufferType*)SpiSrcData,
          (Spi_DataBufferType*)SpiDestData);
        /* polyspace -end MISRA2012:11.8 [Justified:Low] "SpiSrcData is guaranteed that the value not exceed its data type." */
        SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA();
        /* Set ArisuCan status as Idle */
        ArisuCan_ReadFlag = ARISUCAN_OK;
        SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA();

        break;
      }
      else
      {
        /* Nothing to do */
      }
    }
  }
  else
  {
    /* The ArisuCan is busy, set return value as E_NOT_OK */
    returnValue = E_NOT_OK;
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_ArisuCan_CheckCanMode                         **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : Check Can mode                                        **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : LddCanTrcv, LddMode                                   **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : pMode                                                 **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global variable(s) :                                  **
**                      ArisuCan_SpiDestData                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      Det_ReportError, ArisuCan_SendSPI                     **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00086 SWS_CanTrcv_00163
*/
/* @Trace: CanTrcv_SUD_API_316 */
FUNC(CanTrcv_TrcvModeType, CANTRCV_CODE) CanTrcv_ArisuCan_CheckCanMode(
  VAR(CanTrcv_HwType, AUTOMATIC) canTrcv,
  VAR(ArisuCan_SBCModeType, AUTOMATIC) mode)
{
  VAR(uint16, AUTOMATIC) spiSrcData;
  VAR(CanTrcv_TrcvModeType, AUTOMATIC) canTrcvMode;
  VAR(uint16, AUTOMATIC) canModeSts;
  P2CONST(ArisuCan_CanConfigType, AUTOMATIC, CANTRCV_CONST) ptrCanCfg;


  if (ARISUCAN_SBCMODE_NORMAL == mode)
  {
    canTrcvMode = CANTRCV_TRCVMODE_STANDBY;
  }
  else
  {
    canTrcvMode = CANTRCV_TRCVMODE_NORMAL;
  }

  ptrCanCfg = &CanTrcv_ArisuCan[mode];

  switch(canTrcv)
  {
    case CANTRCV_ARISU_CAN0:
      spiSrcData = (uint16)(ARISUCAN_BUS_CTRL_0_REG_R);
      (void)ArisuCan_SendSPI(&spiSrcData, &ArisuCan_SpiDestData);
      canModeSts = (uint16)((ArisuCan_SpiDestData & ARISUCAN_DATAMASK) >> ARISUCAN_EIGHT);
      canModeSts = (((uint16)canModeSts & ARISUCAN_CAN_0_1_3_MASK));
      if (canModeSts == (uint32)(ptrCanCfg->ArisuCan0Mode))
      {
        if (ARISUCAN_SBCMODE_NORMAL == mode)
        {
          canTrcvMode = CANTRCV_TRCVMODE_NORMAL;
        }
        else
        {
          canTrcvMode = CANTRCV_TRCVMODE_STANDBY;
        }
      }
      else
      {
        /* Nothing to do */
      }
      break;

    case CANTRCV_ARISU_CAN1:
      spiSrcData = (uint16)(ARISUCAN_BUS_CTRL_2_REG_R);
      (void)ArisuCan_SendSPI(&spiSrcData, &ArisuCan_SpiDestData);
      canModeSts = (uint16)((ArisuCan_SpiDestData & ARISUCAN_DATAMASK) >> ARISUCAN_EIGHT);
      canModeSts = ((canModeSts & ARISUCAN_CAN_0_1_3_MASK));
      if (canModeSts == (uint32)(ptrCanCfg->ArisuCan1Mode))
      /* polyspace +10 RTE:UNR [Justified:Low] "This branch occurs when check Can mode for configured ARISU_CAN1." */
      {
        if (ARISUCAN_SBCMODE_NORMAL == mode)
        {
          canTrcvMode = CANTRCV_TRCVMODE_NORMAL;
        }
        else
        {
          canTrcvMode = CANTRCV_TRCVMODE_STANDBY;
        }
      }
      else
      {
        /* Nothing to do */
      }
      break;

    case CANTRCV_ARISU_CAN2:
      spiSrcData = (uint16)(ARISUCAN_BUS_CTRL_2_REG_R);
      (void)ArisuCan_SendSPI(&spiSrcData, &ArisuCan_SpiDestData);
      canModeSts = (uint16)((ArisuCan_SpiDestData & ARISUCAN_DATAMASK) >> ARISUCAN_EIGHT);
      canModeSts = ((canModeSts & (uint16)ARISUCAN_CAN_2_MASK) >> CANTRCV_THREE);
      if (canModeSts == (uint32)(ptrCanCfg->ArisuCan2Mode))
      /* polyspace +10 RTE:UNR [Justified:Low] "This branch occurs when check Can mode for configured ARISU_CAN2." */
      {
        if (ARISUCAN_SBCMODE_NORMAL == mode)
        {
          canTrcvMode = CANTRCV_TRCVMODE_NORMAL;
        }
        else
        {
          canTrcvMode = CANTRCV_TRCVMODE_STANDBY;
        }
      }
      else
      {
        /* Nothing to do */
      }
      break;

    case CANTRCV_ARISU_CAN3:
      spiSrcData = (uint16)(ARISUCAN_BUS_CTRL_3_REG_R);
      (void)ArisuCan_SendSPI(&spiSrcData, &ArisuCan_SpiDestData);
      canModeSts = (uint16)((ArisuCan_SpiDestData & ARISUCAN_DATAMASK) >> ARISUCAN_EIGHT);
      canModeSts = ((canModeSts & (uint16)ARISUCAN_CAN_0_1_3_MASK));
      /* polyspace +1 MISRA2012:10.5 [Justified:Low] "Operation is guaranteed that does not exceed ArisuCan_CANModeType." */
      if (canModeSts == (uint32)(ptrCanCfg->ArisuCan3Mode))
      {
        if (ARISUCAN_SBCMODE_NORMAL == mode)
        {
          canTrcvMode = CANTRCV_TRCVMODE_NORMAL;
        }
        else
        {
          canTrcvMode = CANTRCV_TRCVMODE_STANDBY;
        }
      }
      else
      {
        /* Nothing to do */
      }
      break;

    /* polyspace +3 RTE:UNR [Justified:Low] "Coding rule, switch case expression must have default." */
    default:
      /* Nothing to do */
      break;
  }

  return canTrcvMode;
}

/*******************************************************************************
** Function Name      : CanTrcv_ArisuCan_IntPowerDownMode                     **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function will set power down mode for Arisu Can. **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : Mode                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK:     Will be returned if the transceiver         **
**                                state change.                               **
**                      E_NOT_OK: Will be returned if the request for         **
**                                transceiver mode change to stop mode        **
**                                has not been completed.                     **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global variable(s) : CanTrcv_ArisuCan,                **
**                      ArisuCan_SpiDestData                                  **
**                                                                            **
**                      Function(s) invoked : ArisuCan_SendSPI,               **
**                      CanTrcv_IntArisuCan_SetMode                           **
*******************************************************************************/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_ArisuCan_IntPowerDownMode(void)
{
  P2CONST(ArisuCan_CanConfigType, AUTOMATIC, CANTRCV_CONST)
    ptrCanPowerDownModeCfg;
  VAR(Std_ReturnType, AUTOMATIC) result;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  VAR(uint16, AUTOMATIC) spiSrcData;

  /* @Trace: CanTrcv_SUD_API_261 */
  /* Initialize local variables */
  result = E_OK;

  SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA();
  ptrCanPowerDownModeCfg = &CanTrcv_ArisuCan[ARISUCAN_SBCMODE_SLEEP];

  /* @Trace: CanTrcv_SUD_API_262 */
  /* SBC Mode Change to change ArisuCan CanTrcv Mode */
  (void)CanTrcv_IntArisuCan_SetMode(ARISUCAN_SBCMODE_NORMAL);

  /* @Trace: CanTrcv_SUD_API_263 */
  /* ARISU-CAN0 */
  spiSrcData = (uint16)ptrCanPowerDownModeCfg->ArisuCan0Mode;
  spiSrcData =  (uint16)((uint16)((uint16)spiSrcData <<
    (uint16)ARISUCAN_BUS_CTRL_MODE_POS) | (uint16)(ARISUCAN_BUS_CTRL_0_REG_W));
  returnValue = ArisuCan_SendSPI(&spiSrcData, &ArisuCan_SpiDestData);
  if (E_OK != returnValue)
  {
    result = E_NOT_OK;
  }
  else
  {
    /* Nothing to do */
  }

  /* @Trace: CanTrcv_SUD_API_264 */
  /* ARISU-CAN1 & ARISU-CAN2 */
  spiSrcData = (uint16)((uint16)(ptrCanPowerDownModeCfg->ArisuCan1Mode) |
    (uint16)((uint16)(ptrCanPowerDownModeCfg->ArisuCan2Mode) <<
    (uint16)(ARISUCAN_BUS_CTRL_CANTRCV_3_MODE_POS)));
  spiSrcData = (uint16)(((uint16)(spiSrcData & ARISU_8_BIT) <<
    (uint16)ARISUCAN_BUS_CTRL_MODE_POS) | (uint16)(ARISUCAN_BUS_CTRL_2_REG_W));
  returnValue = ArisuCan_SendSPI(&spiSrcData, &ArisuCan_SpiDestData);

  if (E_OK != returnValue)
  {
    result = E_NOT_OK;
  }
  else
  {
    /* Nothing to do */
  }

  /* @Trace: CanTrcv_SUD_API_265 */
  /* ARISU-CAN3 */
  spiSrcData = (uint16)ptrCanPowerDownModeCfg->ArisuCan3Mode;
  spiSrcData = ((uint16)((uint16)spiSrcData << (uint16)ARISUCAN_BUS_CTRL_MODE_POS) |
    (uint16)(ARISUCAN_BUS_CTRL_3_REG_W));
  returnValue = ArisuCan_SendSPI(&spiSrcData, &ArisuCan_SpiDestData);

  if (E_OK != returnValue)
  {
    result = E_NOT_OK;
  }
  else
  {
    /* Nothing to do */
  }

  /* @Trace: CanTrcv_SUD_API_266 */
  /* ARISU-CAN Wake Up Clear */
  spiSrcData = ARISUCAN_WK_STAT_0_REG_W;
  returnValue = ArisuCan_SendSPI(&spiSrcData, &ArisuCan_SpiDestData);

  if (E_OK != returnValue)
  {
    result = E_NOT_OK;
  }
  else
  {
    /* Nothing to do */
  }

  /* @Trace: CanTrcv_SUD_API_267 */
  /* ARISU-CAN Wake Up Clear */
  spiSrcData = ARISUCAN_WK_STAT_2_REG_W;
  returnValue = ArisuCan_SendSPI(&spiSrcData, &ArisuCan_SpiDestData);

  if (E_OK != returnValue)
  {
    result = E_NOT_OK;
  }
  else
  {
    /* Nothing to do */
  }

  /* @Trace: CanTrcv_SUD_API_268 */
  /* SBC Mode Change a SBCMode for PowerDown */
  returnValue = CanTrcv_IntArisuCan_SetMode(ARISUCAN_SBCMODE_SLEEP);

  if (E_OK != returnValue)
  {
    result = E_NOT_OK;
  }
  else
  {
    /* Nothing to do */
  }

  /* @Trace: CanTrcv_SUD_API_269 */
  SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA();

  return result;
}

/*******************************************************************************
** Function Name      : CanTrcv_ArisuCan_IntChangeStopMode                    **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function will set stop mode for Arisu Can.       **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : pMode                                                 **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global variable(s) : CanTrcv_ArisuCan,                **
**                      ArisuCan_SBCModeSts, CanTrcv_ArisuChannelUsed,        **
**                      CanTrcv_ArisuCanSts, ArisuCan_SpiDestData             **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      CanTrcv_ArisuCan_IntReadStatus,                       **
**                      CanTrcv_IntArisuCan_SetMode                           **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_ArisuCan_IntChangeStopMode(
  CONST(ArisuCan_CanConfigType, AUTOMATIC) canTrcvConfigure)
{
  VAR(CanTrcv_ArisuCanType, AUTOMATIC) readData;
  VAR(uint16, AUTOMATIC) spiSrcData;
  VAR(Std_ReturnType, AUTOMATIC) result;

  /* @Trace: CanTrcv_SUD_API_271 */
  SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA();

  /* Check ready to go SBC MODE STOP */
  if ((CanTrcv_ArisuCanSts.ArisuCan0Mode != canTrcvConfigure.ArisuCan0Mode)
    ||(CanTrcv_ArisuCanSts.ArisuCan1Mode != canTrcvConfigure.ArisuCan1Mode)
    ||(CanTrcv_ArisuCanSts.ArisuCan2Mode != canTrcvConfigure.ArisuCan2Mode)
    ||(CanTrcv_ArisuCanSts.ArisuCan3Mode != canTrcvConfigure.ArisuCan3Mode))
  {
    /* @Trace: CanTrcv_SUD_API_278 */
    result = E_NOT_OK;
  }
  else
  {
    /* @Trace: CanTrcv_SUD_API_273 */
    (void)CanTrcv_ArisuCan_IntReadStatus(ARISUCAN_M_S_CTRL_REG_R, &readData);

    if ((CanTrcv_ArisuCanType)ARISUCAN_SBCMODE_NORMAL ==
      ((readData & ARISUCAN_M_S_CTRL_MODE_MASK) >> ARISUCAN_M_S_CTRL_MASK))
    {
      /* @Trace: CanTrcv_SUD_API_274 */
      /* VBSENSE_DISABLE : Bit 1 */
      spiSrcData = (uint16)((uint16)ARISUCAN_W_K_CTRL_0_VBSENSE01_CFG_BIT &
        ARISUCAN_W_K_CTRL_0_VBSENSE_DISABLE_BIT);
      spiSrcData = (uint16)((uint16)((uint16)spiSrcData <<
        (uint16)ARISUCAN_BUS_CTRL_MODE_POS) |
        (uint16)(ARISUCAN_WK_CTRL_0_REG_W));
      (void)ArisuCan_SendSPI(&spiSrcData, &ArisuCan_SpiDestData);
    }
    else
    {
      /* Nothing to do */
    }

    /* @Trace: CanTrcv_SUD_API_275 */
    /* ARISU-CAN Wake Up Clear */
    spiSrcData = ARISUCAN_WK_STAT_0_REG_W;
    (void)ArisuCan_SendSPI(&spiSrcData, &ArisuCan_SpiDestData);

    /* ARISU-CAN Wake Up Clear */
    spiSrcData = ARISUCAN_WK_STAT_2_REG_W;
    (void)ArisuCan_SendSPI(&spiSrcData, &ArisuCan_SpiDestData);

    result = CanTrcv_IntArisuCan_SetMode(ARISUCAN_SBCMODE_STOP);

    if (E_OK == result)
    {
      if (ArisuCan_SBCModeSts != (ArisuCan_SBCModeType)(ARISUCAN_SBCMODE_STOP))
      {
        /* @Trace: CanTrcv_SUD_API_276 */
        result = E_NOT_OK;
      }
      else
      {
        /* Nothing to do */
      }
    }
    else
    {
      /* Nothing to do */
    }
  }

  /* @Trace: CanTrcv_SUD_API_277 */
  SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA();

  return result;
}

/*******************************************************************************
** Function Name      : CanTrcv_ArisuCan_IntGetInternalSBCMode                **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : Return SBC mode of ArisuCan.                          **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : Mode                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : SBC mode for ArisuCan.                                **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global variable(s) : None                             **
**                                                                            **
**                      Function(s) invoked : None                            **
*******************************************************************************/
FUNC(ArisuCan_SBCModeType, CANTRCV_CODE)CanTrcv_ArisuCan_IntGetInternalSBCMode(
  void)
{
  /* @Trace: CanTrcv_SUD_API_254 */
  return ArisuCan_SBCModeSts;
}

/*******************************************************************************
** Function Name      : CanTrcv_ArisuCan_IntReadStatus                        **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This service will read value in register on           **
**                      ArisuCan.                                             **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : address - Pointer to source address.                  **
**                                                                            **
** In/Out Parameters  : None                                                  **
**                                                                            **
** Output Parameters  : data - Value in ArisuCan register.                    **
**                                                                            **
** Return parameter   : E_OK:     Will be returned if the transceiver state   **
**                                read successed.                             **
**                      E_NOT_OK: Will be returned if the transceiver state   **
**                                read failed.                                **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global variable(s) : None                             **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      ArisuCan_SendSPI                                      **
*******************************************************************************/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_ArisuCan_IntReadStatus(
  VAR(CanTrcv_ArisuCanType, AUTOMATIC) address,
  P2VAR(CanTrcv_ArisuCanType, AUTOMATIC, CANTRCV_VAR) data)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  VAR(uint16, AUTOMATIC) spiDestdata;
  VAR(uint16, AUTOMATIC) regAddress;

  /* Initialize local variable */
  spiDestdata = CANTRCV_ZERO;
  regAddress = (uint16)address;

  /* @Trace: CanTrcv_SUD_API_256 */
  SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA();

  /* @Trace: CanTrcv_SUD_API_257 */
  returnValue = ArisuCan_SendSPI(&regAddress,
    (P2VAR(uint16, AUTOMATIC, CANTRCV_VAR))&spiDestdata);
  /* polyspace +2 MISRA2012:D4.14 [Justified:Low] "Pointer data is checked NULL by DET." */
  *data = (CanTrcv_ArisuCanType)((spiDestdata & ARISUCAN_DATAMASK)
    >> ARISUCAN_EIGHT);

  /* @Trace: CanTrcv_SUD_API_259 */
  SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA();

  /* @Trace: CanTrcv_SUD_API_258 */
  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_ArisuCan_IntVbsenseEnable                     **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This service will enable Vbsense.                     **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK:     Will be returned if the Vbsense Enable Bit  **
**                                of ARISU-CAN is set ‘1’.                    **
**                      E_NOT_OK: Will be returned if the Vbsense Enable Bit  **
**                                of ARISU-CAN is set ‘0’.                    **
**                                                                            **
** Preconditions      : CANTRCV_ARISUCAN_SUPPORTED == STD_ON                  **
**                                                                            **
** Remarks            : Global variable(s) :                                  **
**                      ArisuCan_SpiDestData                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      CanTrcv_ArisuCan_IntReadStatus, ArisuCan_SendSPI      **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_ArisuCan_IntVbsenseEnable(void)
{
  VAR(CanTrcv_ArisuCanType, AUTOMATIC) readData;
  VAR(uint16, AUTOMATIC) spiSrcData;
  VAR(Std_ReturnType, AUTOMATIC) result;

  /* @Trace: CanTrcv_SUD_API_282 */
  SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA();

  /* @Trace: CanTrcv_SUD_API_283 */
  /* VBSENSE_Enable : Bit 1 */
  spiSrcData = (uint16)((uint16)ARISUCAN_W_K_CTRL_0_VBSENSE01_CFG_BIT |
    ARISUCAN_W_K_CTRL_0_VBSENSE_EN_BIT);
  spiSrcData = (uint16)((uint16)((uint16)spiSrcData <<
    (uint16)ARISUCAN_BUS_CTRL_MODE_POS) |
    (uint16)(ARISUCAN_WK_CTRL_0_REG_W));
  result = ArisuCan_SendSPI(&spiSrcData, &ArisuCan_SpiDestData);
  if (E_OK == result)
  {
    /* @Trace: CanTrcv_SUD_API_284 */
    (void)CanTrcv_ArisuCan_IntReadStatus(ARISUCAN_WK_CTRL_0_REG_R, &readData);
    if ((CanTrcv_ArisuCanType)CANTRCV_ZERO ==
      (readData & ARISUCAN_W_K_CTRL_0_VBSENSE_EN_BIT))
    {
      result = E_NOT_OK;
    }
    else
    {
      /* Nothing to do */
    }
  }
  else
  {
    /* Nothing to do */
  }
  /* @Trace: CanTrcv_SUD_API_285 */
  SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA();

  return result;

}

/*******************************************************************************
** Function Name      : CanTrcv_ArisuCan_IntVbsenseDisable                    **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This service will disable Vbsense.                    **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK:     Will be returned if the Vbsense Enable Bit  **
**                                of ARISU-CAN is set ‘0’.                    **
**                      E_NOT_OK: Will be returned if the Vbsense Enable Bit  **
**                                of ARISU-CAN is set ‘1’.                    **
**                                                                            **
** Preconditions      : CANTRCV_ARISUCAN_SUPPORTED == STD_ON                  **
**                                                                            **
** Remarks            : Global variable(s) :                                  **
**                      ArisuCan_SpiDestData                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      CanTrcv_ArisuCan_IntReadStatus, ArisuCan_SendSPI      **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_ArisuCan_IntVbsenseDisable(void)
{
  VAR(CanTrcv_ArisuCanType, AUTOMATIC) readData;
  VAR(uint16, AUTOMATIC) spiSrcData;
  VAR(Std_ReturnType, AUTOMATIC) result;

  /* @Trace: CanTrcv_SUD_API_286 */
  SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA();

  /* @Trace: CanTrcv_SUD_API_287 */
  /* VBSENSE_Disable : Bit 0 */
  spiSrcData = (uint16)((uint16)ARISUCAN_W_K_CTRL_0_VBSENSE01_CFG_BIT &
    ARISUCAN_W_K_CTRL_0_VBSENSE_DISABLE_BIT);
  spiSrcData = (uint16)((uint16)((uint16)spiSrcData <<
    (uint16)ARISUCAN_BUS_CTRL_MODE_POS) |
    (uint16)(ARISUCAN_WK_CTRL_0_REG_W));
  result = ArisuCan_SendSPI(&spiSrcData, &ArisuCan_SpiDestData);
  if (E_OK == result)
  {
    /* @Trace: CanTrcv_SUD_API_288 */
    (void)CanTrcv_ArisuCan_IntReadStatus(ARISUCAN_WK_CTRL_0_REG_R, &readData);
    if ((CanTrcv_ArisuCanType)CANTRCV_ONE ==
      (readData & ARISUCAN_W_K_CTRL_0_VBSENSE_EN_BIT))
    {
      result = E_NOT_OK;
    }
    else
    {
      /* Nothing to do */
    }
  }
  else
  {
    /* Nothing to do */
  }
  /* @Trace: CanTrcv_SUD_API_289 */
  SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA();

  return result;

}

/*******************************************************************************
** Function Name      : CanTrcv_ArisuCan_Init                                 **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to initialize Arisu Can device.         **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrArisuCanCfg - Pointer to Arisu Can configuration.  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global variable(s) :                                  **
**                      ArisuCan_SpiDestData                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      CanTrcv_IntArisuCan_SetMode,                          **
**                      CanTrcv_IntArisuCan_RequestCanMode                    **
*******************************************************************************/
FUNC(void, CANTRCV_CODE) CanTrcv_ArisuCan_Init(
  P2CONST(ArisuCan_CanConfigType, AUTOMATIC, CANTRCV_CONST) ptrArisuCanCfg)
{
  VAR(uint16, AUTOMATIC) spiSrcData;

  /* @Trace: CanTrcv_SUD_API_303 */
  /* Set ArisuCan SBC mode */
  (void)CanTrcv_IntArisuCan_SetMode(ARISUCAN_SBCMODE_NORMAL);

  ArisuCan_ReadFlag = ARISUCAN_OK;
  /* ARISU-CAN0 OFF */
  /* @Trace: CanTrcv_SUD_API_304 */
  spiSrcData = (uint16)ptrArisuCanCfg->ArisuCan0Mode;
  spiSrcData = (uint16)((uint16)((uint16)spiSrcData <<
    (uint16)ARISUCAN_BUS_CTRL_MODE_POS) | (uint16)(ARISUCAN_BUS_CTRL_0_REG_W));
  (void)ArisuCan_SendSPI(&spiSrcData, &ArisuCan_SpiDestData);

  /* ARISU-CAN1 & ARISU-CAN2 OFF */
  spiSrcData = (uint16)((uint16)(ptrArisuCanCfg->ArisuCan1Mode) |
    (uint16)((uint16)(ptrArisuCanCfg->ArisuCan2Mode) <<
    (uint16)(ARISUCAN_BUS_CTRL_CANTRCV_3_MODE_POS)));
  spiSrcData = (uint16)((uint16)((uint16)spiSrcData <<
    (uint16)ARISUCAN_BUS_CTRL_MODE_POS) | (uint16)(ARISUCAN_BUS_CTRL_2_REG_W));
  (void)ArisuCan_SendSPI(&spiSrcData, &ArisuCan_SpiDestData);

  /*ARISU-CAN3 OFF */
  spiSrcData = (uint16)ptrArisuCanCfg->ArisuCan3Mode;
  spiSrcData = ((uint16)((uint16)spiSrcData <<
    (uint16)ARISUCAN_BUS_CTRL_MODE_POS) | (uint16)(ARISUCAN_BUS_CTRL_3_REG_W));
  (void)ArisuCan_SendSPI(&spiSrcData, &ArisuCan_SpiDestData);

  /* VBENSE_CFG : 1, VBENSE_EN : 1 */
  spiSrcData = (uint16)((uint16)ARISUCAN_W_K_CTRL_0_VBSENSE01_CFG_BIT |
    ARISUCAN_W_K_CTRL_0_VBSENSE_EN_BIT);
  spiSrcData = (uint16)((uint16)((uint16)spiSrcData <<
    (uint16)ARISUCAN_BUS_CTRL_MODE_POS) | (uint16)(ARISUCAN_WK_CTRL_0_REG_W));
  (void)ArisuCan_SendSPI(&spiSrcData, &ArisuCan_SpiDestData);

  /* Read HW_CTRL_0 Register Value */
  spiSrcData = (uint16)ARISUCAN_HW_CTRL_0_REG_R;
  (void)ArisuCan_SendSPI(&spiSrcData, &ArisuCan_SpiDestData);

  /* PWM_AUTO Function Support */
  spiSrcData = (ArisuCan_SpiDestData & ARISUCAN_DATAMASK) >> ARISUCAN_EIGHT;
  #if (STD_ON == CANTRCV_ARISU_PWM_AUTO)
  /* @Trace: CanTrcv_SUD_API_305 */
  /* Write PWM_AUTO On Value */
  spiSrcData = (uint16)((spiSrcData |
    (uint16)ARISUCAN_H_W_CTRL_0_PWM_AUTO_1_BIT));
  #else
  /* @Trace: CanTrcv_SUD_API_306 */
  /* Write PWM_AUTO Off Value */
  spiSrcData = (uint16)((spiSrcData &
    (uint16)ARISUCAN_H_W_CTRL_0_PWM_AUTO_0_BIT));
  #endif /* (STD_ON == CANTRCV_ARISU_PWM_AUTO) */
  spiSrcData = (uint16)((uint16)((uint16)spiSrcData <<
    (uint16)ARISUCAN_BUS_CTRL_MODE_POS) | (uint16)(ARISUCAN_HW_CTRL_0_REG_W));
  /* @Trace: CanTrcv_SUD_API_307 */
  (void)ArisuCan_SendSPI(&spiSrcData, &ArisuCan_SpiDestData);
}
#endif /* ((STD_ON == CANTRCV_ARISUCAN_SUPPORTED) && \
  (STD_ON == CANTRCV_SPI_SUPPORTED)) */

#if (STD_ON == CANTRCV_SPI_SUPPORTED)

/*******************************************************************************
** Function Name      : CanTrcv_SendSpi                                       **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to send data via SPI.                   **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN transceiver ID.                     **
**                      ptrSpiSrcData - Pointer point to source data.         **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : ptrSpiDesData - Store data return from CAN transceiver**
**                                                                            **
** Return parameter   : E_OK: The request to transceiver has been accepted.   **
**                      E_NOT_OK: The request to transceiver has not been     **
**                                accepted.                                   **
**                                                                            **
** Preconditions      : CANTRCV_SPI_SUPPORTED == STD_ON                       **
**                                                                            **
** Remarks            : Global variable(s): CanTrcv_CanTrcvNetwork            **
**                                                                            **
**                      Function(s) invoked: Spi_SetupEB, Spi_SyncTransmit,   **
**                      Spi_AsyncTransmit, Dio_WriteChannel,                  **
**                      SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA,         **
**                      SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA           **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_BSW_00347 SRS_ES95480_03E_SWP_00004 SRS_ES95480_03E_SWP_00006 SRS_ES95480_03E_SWP_00008 */
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SendSpi(
  CONST(uint8, AUTOMATIC) transceiver,
  P2CONST(Spi_DataBufferType, AUTOMATIC, CANTRCV_CONST) ptrSpiSrcData,
  P2VAR(Spi_DataBufferType, AUTOMATIC, CANTRCV_APPL_DATA) ptrSpiDesData)
{
  /* @Trace: SWS_CanTrcv_00086 */
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  VAR(uint16, AUTOMATIC) retryCount;
  VAR(Spi_ChannelType, AUTOMATIC) channelId;
  VAR(Spi_SequenceType, AUTOMATIC) sequenceId;
  VAR(Dio_ChannelType, AUTOMATIC) chipSelectGpio;

  /* @Trace: CanTrcv_SUD_API_083 */
  /* Initialize local variable */
  #if (STD_ON == CANTRCV_POSTBUILD_SUPPORTED)
  retryCount = CanTrcv_SPICommRetries;
  #else
  retryCount = CANTRCV_SPI_RETRY_COUNT;
  #endif /* (STD_ON == CANTRCV_POSTBUILD_SUPPORTED) */

  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];
  /* Get channel ID */
  channelId = (Spi_ChannelType)ptrCanTrcvNetwork->SelectPin1;
  /* Get sequence ID */
  sequenceId = (Spi_SequenceType)ptrCanTrcvNetwork->SelectPin2;
  /* Get chip select */
  chipSelectGpio = (Dio_ChannelType)ptrCanTrcvNetwork->SelectPin3;

  do
  {
    /* @Trace: CanTrcv_SUD_API_084 */
    /* Setup EB */
    #if(CANTRCV_SPI_LESS_AR42 == STD_ON)
    returnValue = Spi_SetupEB(channelId, ptrSpiSrcData, ptrSpiDesData,
      (Spi_NumberOfDataType)((Spi_NumberOfDataType)(~(Spi_NumberOfDataType)(sizeof(Spi_DataType)))&(Spi_NumberOfDataType)CANTRCV_THREE));
    #else
    returnValue = Spi_SetupEB(channelId, ptrSpiSrcData, ptrSpiDesData,
      (Spi_NumberOfDataType)CANTRCV_ONE);
    #endif
    if (E_NOT_OK != returnValue)
    {
      if (CANTRCV_UNUSED != chipSelectGpio)
      {
        /* @Trace: CanTrcv_SUD_API_085 */
        SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA();
        /* Active chip select */
        Dio_WriteChannel(chipSelectGpio, (Dio_LevelType)STD_LOW);
        SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA();

        /* @Trace: CanTrcv_SUD_API_086 */
        returnValue = CanTrcv_SpiTransmit(ptrCanTrcvNetwork->SpiAccessSynchronous, sequenceId);

        /* @Trace: CanTrcv_SUD_API_088 */
        SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA();
        /* Deactive chip select */
        Dio_WriteChannel(chipSelectGpio, (Dio_LevelType)STD_HIGH);
        SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA();
      }
      else
      {
        /* @Trace: CanTrcv_SUD_API_087 */
        returnValue = CanTrcv_SpiTransmit(ptrCanTrcvNetwork->SpiAccessSynchronous, sequenceId);
      }
    }
    else
    {
      /* Nothing to do */
    }

    /* @Trace: CanTrcv_SUD_API_089 */
    if (E_NOT_OK != returnValue)
    {
      /* Break the loop */
      retryCount = CANTRCV_ZERO;
    }
    else
    {
      /* Decrement counter */
      retryCount--;
    }
  } while(retryCount != CANTRCV_ZERO);

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_SpiTransmit                                   **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to transmit data via SPI.               **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : spiAccessSynchronous - Spi Synchronous enable.        **
**                      sequenceId - Spi sequence.                            **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Data has been transmitted successfully.         **
**                      E_NOT_OK: Data has not been transmitted successfully. **
**                                                                            **
** Preconditions      : CANTRCV_SPI_SUPPORTED == STD_ON                       **
**                                                                            **
** Remarks            : Global variable(s):                                   **
**                                                                            **
**                      Function(s) invoked: Spi_SyncTransmit,                **
**                      Spi_AsyncTransmit                                     **
**                                                                            **
*******************************************************************************/

static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SpiTransmit(
  VAR(boolean, AUTOMATIC) spiAccessSynchronous,
  VAR(Spi_SequenceType, AUTOMATIC) sequenceId)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  #if (STD_OFF == CANTRCV_SUPPORT_AR403)
  #if (STD_ON == CANTRCV_SPI_ASYNCTRANSMIT_SUPPORTED)
  if (CANTRCV_TRUE != spiAccessSynchronous)
  {
    /* Invoke Spi_AsyncTransmit */
    returnValue = Spi_AsyncTransmit(sequenceId);
  }
  else
  #else
  CANTRCV_UNUSED_VAL(spiAccessSynchronous);
  #endif /* (STD_ON == CANTRCV_SPI_ASYNCTRANSMIT_SUPPORTED) */
  #endif /*(CANTRCV_SUPPORT_AR403 == STD_OFF)*/
  {
    /* Invoke Spi_SyncTransmit */
    returnValue = Spi_SyncTransmit(sequenceId);
  }

  return returnValue;
}

#if ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
  (STD_ON == CANTRCV_TLE9255W_SUPPORTED) || \
  (STD_ON == CANTRCV_TCAN1145_SUPPORTED))
#if (STD_OFF == CANTRCV_SUPPORT_AR403)
#if (STD_ON == CANTRCV_SPI_ASYNCTRANSMIT_SUPPORTED)
/*******************************************************************************
** Function Name      : CanTrcv_SpiWaitTimeout                                **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to the SPI transmit complete.           **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN transceiver ID.                     **
**                      ptrSpiSrcData - Pointer point to source data.         **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : ptrSpiDesData - Store data return from CAN transceiver**
**                                                                            **
** Return parameter   : E_OK: The request to transceiver has been accepted.   **
**                      E_NOT_OK: The request to transceiver has not been     **
**                                accepted.                                   **
**                                                                            **
** Preconditions      : CANTRCV_SPI_SUPPORTED == STD_ON                       **
**                                                                            **
** Remarks            : Global variable(s): CanTrcv_CanTrcvNetwork            **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      Spi_GetSequenceResult                                 **
**                                                                            **
*******************************************************************************/
static FUNC(Spi_SeqResultType, CANTRCV_CODE) CanTrcv_SpiWaitTimeout(
  CONST(uint8, AUTOMATIC) transceiver)
{
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  VAR(uint32, AUTOMATIC) spiTimeout;
  VAR(Spi_SeqResultType, AUTOMATIC) returnValue;

  /* @Trace: CanTrcv_SUD_API_090 */
  /* Initialize time out value */
  #if (STD_ON == CANTRCV_POSTBUILD_SUPPORTED)
  spiTimeout = CanTrcv_SPICommTimeout;
  #else
  spiTimeout = CANTRCV_SPI_TIMEOUT;
  #endif /* (STD_ON == CANTRCV_POSTBUILD_SUPPORTED) */
  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];

  do
  {
    /* @Trace: CanTrcv_SUD_API_091 */
    /* Get sequence result */
    returnValue = Spi_GetSequenceResult(ptrCanTrcvNetwork->SelectPin2);
    #if (STD_ON == CANTRCV_POSTBUILD_SUPPORTED)
    /* @Trace: CanTrcv_SUD_API_092 */
    if (CANTRCV_ZERO != spiTimeout)
    {
      spiTimeout--;

    }
    else
    {
      /* Nothing to do */
    }
    #else
    #if (CANTRCV_ZERO != CANTRCV_SPI_TIMEOUT)
    spiTimeout--;

    #endif /* (CANTRCV_ZERO != CANTRCV_SPI_TIMEOUT) */
    #endif /* (STD_ON == CANTRCV_POSTBUILD_SUPPORTED) */
  } while ((SPI_SEQ_OK != returnValue) && (CANTRCV_ZERO != spiTimeout));

  return returnValue;
}
#endif /* (STD_ON == CANTRCV_SPI_ASYNCTRANSMIT_SUPPORTED) */
#endif /*#if (STD_OFF == CANTRCV_SUPPORT_AR403)*/

/*******************************************************************************
** Function Name      : CanTrcv_ReadReg                                       **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to read data from register via SPI.     **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN transceiver ID.                     **
**                      address - Address of register.                        **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : ptrDesData - Store data of register.                  **
**                                                                            **
** Return parameter   : E_OK: The request to transceiver has been accepted.   **
**                      E_NOT_OK: The request to transceiver has not been     **
**                                accepted.                                   **
**                                                                            **
** Preconditions      : CANTRCV_SPI_SUPPORTED == STD_ON                       **
**                                                                            **
** Remarks            : Global variable(s): CanTrcv_CanTrcvNetwork            **
**                                                                            **
**                      Function(s) invoked: CanTrcv_SendSpi                  **
**                                                                            **
*******************************************************************************/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_ReadReg(
  CONST(uint8, AUTOMATIC) transceiver,
  CONST(uint8, AUTOMATIC) address,
  P2VAR(uint8, AUTOMATIC, CANTRCV_VAR) ptrDesData)
{
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  VAR(uint8, AUTOMATIC) srcData[CANTRCV_TWO];
  VAR(uint8, AUTOMATIC) desData[CANTRCV_TWO];
  #if (STD_OFF == CANTRCV_SUPPORT_AR403)
  #if (STD_ON == CANTRCV_SPI_ASYNCTRANSMIT_SUPPORTED)
  VAR(Spi_SeqResultType, AUTOMATIC) seqResult;
  #endif /* (STD_ON == CANTRCV_SPI_ASYNCTRANSMIT_SUPPORTED) */
  #endif /*(STD_OFF == CANTRCV_SUPPORT_AR403)*/
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  /* Initialize local variable */
  returnValue = E_NOT_OK;
  desData[CANTRCV_ZERO] = CANTRCV_ZERO;
  desData[CANTRCV_ONE] = CANTRCV_ZERO;

  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];
  #if (STD_OFF == CANTRCV_SUPPORT_AR403)
  #if (STD_ON == CANTRCV_SPI_ASYNCTRANSMIT_SUPPORTED)
  /* Initialize sequence result */
  seqResult = SPI_SEQ_OK;
  /* Check Spi access type */
  /* polyspace +1 RTE:IDP [Not a defect:Low] "It will be checked by generator code, no impact" */
  if (CANTRCV_TRUE != ptrCanTrcvNetwork->SpiAccessSynchronous)
  {
    /* @Trace: CanTrcv_SUD_API_075 */
    /* Check sequence result */
    seqResult = CanTrcv_SpiWaitTimeout(transceiver);
  }
  else
  {
    /* Nothing to do */
  }

  if (SPI_SEQ_OK == seqResult)
  #endif /* (STD_ON == CANTRCV_SPI_ASYNCTRANSMIT_SUPPORTED) */
  #endif /* (STD_OFF == CANTRCV_SUPPORT_AR403)*/
  {
    #if (STD_ON == CANTRCV_XJA11XX_SUPPORTED)
    /* Check hardware device type */
    if ((CANTRCV_TJA1145 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
      (CANTRCV_UJA1169 == ptrCanTrcvNetwork->CanTrcvHwDev))
    {
      /* @Trace: CanTrcv_SUD_API_076 */
      srcData[CANTRCV_ONE] = ((address << CANTRCV_ONE) | XJA11XX_REG_READ);
      srcData[CANTRCV_ZERO] = (uint8)CANTRCV_ZERO;
      SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA();
      /* Send SPI request */
      returnValue = CanTrcv_SendSpi(transceiver, srcData, desData);
      SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA();
    }
    #endif /* (STD_ON == CANTRCV_XJA11XX_SUPPORTED) */

    #if (STD_ON == CANTRCV_TCAN1145_SUPPORTED)
    if (CANTRCV_TCAN1145 == ptrCanTrcvNetwork->CanTrcvHwDev) 
    {
      /* @Trace: CanTrcv_SUD_API_375 */
      
      srcData[CANTRCV_ONE] = ((address << CANTRCV_ONE) | TCAN1145_REG_READ);
      srcData[CANTRCV_ZERO] = (uint8)CANTRCV_ZERO;
      SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA();
      /* Send SPI request */
      returnValue = CanTrcv_SendSpi(transceiver, srcData, desData);
      SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA();
    }
    #endif /* (STD_ON == CANTRCV_TCAN1145_SUPPORTED) */

    #if (STD_ON == CANTRCV_TLE9255W_SUPPORTED)
    if (CANTRCV_TLE9255W == ptrCanTrcvNetwork->CanTrcvHwDev) 
    {
      /* @Trace: CanTrcv_SUD_API_077 */
      srcData[CANTRCV_ONE] = (address | (TLE9255W_REG_READ << CANTRCV_SEVEN));
      srcData[CANTRCV_ZERO] = (uint8)CANTRCV_ZERO;
      SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA();
      /* Send SPI request */
      returnValue = CanTrcv_SendSpi(transceiver, srcData, desData);
      SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA();
      
    }
    #endif /* (STD_ON == CANTRCV_TLE9255W_SUPPORTED) */
    if (E_NOT_OK != returnValue)
    {
      #if ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || (STD_ON == CANTRCV_TCAN1145_SUPPORTED ))
      /* Check hardware device type */
      if ((CANTRCV_TJA1145 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
        (CANTRCV_UJA1169 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
        (CANTRCV_TCAN1145 == ptrCanTrcvNetwork->CanTrcvHwDev))
      {
        /* @Trace: CanTrcv_SUD_API_078 */
        /* polyspace +1 RTE:IDP [Not a defect:Low] "It has been checked, no impact" */
        *ptrDesData = desData[CANTRCV_ZERO];
      }
      else
      #endif /* (STD_ON == CANTRCV_XJA11XX_SUPPORTED) */
      {
        #if (STD_ON == CANTRCV_TLE9255W_SUPPORTED)
        /* @Trace: CanTrcv_SUD_API_079 */
        /* polyspace +1 RTE:IDP [Not a defect:Low] "It has been checked, no impact" */
        *ptrDesData = desData[CANTRCV_ZERO];
        #endif /* (STD_ON == CANTRCV_TLE9255W_SUPPORTED) */
      }
    }
    else
    {
      /* Nothing to do */
    }
  }
  #if (STD_OFF == CANTRCV_SUPPORT_AR403)
  #if (STD_ON == CANTRCV_SPI_ASYNCTRANSMIT_SUPPORTED)
  else
  {
    /* Nothing to do */
  }
  #endif /* (STD_ON == CANTRCV_SPI_ASYNCTRANSMIT_SUPPORTED) */
  #endif /* (STD_OFF == CANTRCV_SUPPORT_AR403)*/

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_WriteReg                                      **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to write data to register via SPI.      **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN transceiver ID.                     **
**                      address - Address of register.                        **
**                      data - Data write into register.                      **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : CANTRCV_SPI_SUPPORTED == STD_ON                       **
**                                                                            **
** Remarks            : Global variable(s): CanTrcv_CanTrcvNetwork            **
**                                                                            **
**                      Function(s) invoked: CanTrcv_SendSpi                  **
**                                                                            **
*******************************************************************************/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_WriteReg(
  CONST(uint8, AUTOMATIC) transceiver,
  CONST(uint8, AUTOMATIC) address,
  CONST(uint8, AUTOMATIC) data)
{
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  VAR(uint8, AUTOMATIC) srcData[CANTRCV_TWO];
  VAR(uint8, AUTOMATIC) desData[CANTRCV_TWO];
  #if (STD_OFF == CANTRCV_SUPPORT_AR403)
  #if (STD_ON == CANTRCV_SPI_ASYNCTRANSMIT_SUPPORTED)
  VAR(Spi_SeqResultType, AUTOMATIC) seqResult;
  #endif /* (STD_ON == CANTRCV_SPI_ASYNCTRANSMIT_SUPPORTED) */
  #endif /*#if (STD_OFF == CANTRCV_SUPPORT_AR403)*/
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  /* Initialize local variable */
  returnValue = E_NOT_OK;

  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];
  #if (STD_OFF == CANTRCV_SUPPORT_AR403)
  #if (STD_ON == CANTRCV_SPI_ASYNCTRANSMIT_SUPPORTED)
  /* Initialize sequence result */
  seqResult = SPI_SEQ_OK;
  /* Check Spi access type */
  /* polyspace +1 RTE:IDP [Not a defect:Low] "It will be checked by generator code, no impact" */
  if (CANTRCV_TRUE != ptrCanTrcvNetwork->SpiAccessSynchronous)
  {
    /* @Trace: CanTrcv_SUD_API_080 */
    /* Check sequence result */
    seqResult = CanTrcv_SpiWaitTimeout(transceiver);
  }
  else
  {
    /* Nothing to do */
  }

  if (SPI_SEQ_OK == seqResult)
  #endif /* (STD_ON == CANTRCV_SPI_ASYNCTRANSMIT_SUPPORTED) */
  #endif /*#if (STD_OFF == CANTRCV_SUPPORT_AR403)*/
  {
    /* Check hardware device type */
    #if (STD_ON == CANTRCV_XJA11XX_SUPPORTED)
    if ((CANTRCV_TJA1145 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
      (CANTRCV_UJA1169 == ptrCanTrcvNetwork->CanTrcvHwDev))
    {  
      /* @Trace: CanTrcv_SUD_API_081 */
      srcData[CANTRCV_ONE] = ((address << CANTRCV_ONE) | XJA11XX_REG_WRITE);
      srcData[CANTRCV_ZERO] = data;
      SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA();
      /* Send SPI request */
      returnValue = CanTrcv_SendSpi(transceiver, srcData, desData);
      SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA();
    }
    #endif /* (STD_ON == CANTRCV_XJA11XX_SUPPORTED) */
    #if (STD_ON == CANTRCV_TCAN1145_SUPPORTED)
    if (CANTRCV_TCAN1145 == ptrCanTrcvNetwork->CanTrcvHwDev)
    {
      
       /* @Trace: CanTrcv_SUD_API_376 */   
      srcData[CANTRCV_ONE] = ((address << CANTRCV_ONE) | TCAN1145_REG_WRITE);
      srcData[CANTRCV_ZERO] = data;
      SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA();
      /* Send SPI request */
      returnValue = CanTrcv_SendSpi(transceiver, srcData, desData);
      SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA();
      
    }
    #endif /* (STD_ON == CANTRCV_TCAN1145_SUPPORTED) */
    #if (STD_ON == CANTRCV_TLE9255W_SUPPORTED)
    if (CANTRCV_TLE9255W == ptrCanTrcvNetwork->CanTrcvHwDev)
    {
      
      /* @Trace: CanTrcv_SUD_API_082 */
      srcData[CANTRCV_ONE] = (address | (TLE9255W_REG_WRITE << CANTRCV_SEVEN));
      srcData[CANTRCV_ZERO] = data;
      SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA();
      /* Send SPI request */
      returnValue = CanTrcv_SendSpi(transceiver, srcData, desData);
      SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA();
      
    }
    #endif /* (STD_ON == CANTRCV_TLE9255W_SUPPORTED) */
  }
  #if (STD_OFF == CANTRCV_SUPPORT_AR403)
  #if (STD_ON == CANTRCV_SPI_ASYNCTRANSMIT_SUPPORTED)
  else
  {
    /* Nothing to do */
  }
  #endif /* (STD_ON == CANTRCV_SPI_ASYNCTRANSMIT_SUPPORTED) */
  #endif /*STD_OFF == CANTRCV_SUPPORT_AR403)*/

  return returnValue;
}
#endif /* ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
  (STD_ON == CANTRCV_TLE9255W_SUPPORTED) || \
  (STD_ON == CANTRCV_TCAN1145_SUPPORTED)) */

#endif /* (STD_ON == CANTRCV_SPI_SUPPORTED) */

#if (((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
  (STD_ON == CANTRCV_TCAN1145_SUPPORTED)) && \
  (STD_ON == CANTRCV_HW_PN_SUPPORTED))
/*******************************************************************************
** Function Name      : CanTrcv_IntClearSyserrFlag                            **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function will clear SYSERR flag.                 **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - Can Transceiver ID                      **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Clear SYSERR flag successful.                   **
**                      E_NOT_OK: Clear SYSERR not successful.                **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_XJA11XX_SUPPORTED or                **
**                      STD_ON == CANTRCV_TCAN1145_SUPPORTED                  **
**                                                                            **
** Remarks            : Global variable(s): CanTrcv_CanTrcvNetwork            **
**                                                                            **
**                      Function(s) invoked: CanTrcv_XJA11XXClearSyserrFlag   **
**                                           CanTrcv_TCAN1145ClearSyserrFlag  **     
*******************************************************************************/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_IntClearSyserrFlag(
  CONST(uint8, AUTOMATIC) transceiver)
{
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  /* Initialize local variable */
  returnValue = E_NOT_OK;

  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];

  /* Check hardware device type */
  switch(ptrCanTrcvNetwork->CanTrcvHwDev)
  {
    #if(STD_ON == CANTRCV_XJA11XX_SUPPORTED)
    case CANTRCV_TJA1145 :
    case CANTRCV_UJA1169 :
     /* @Trace: CanTrcv_SUD_API_058 */
     /* Clear SYSERR flag for XJA11XX device */
     returnValue = CanTrcv_XJA11XXClearSyserrFlag(transceiver);
     break;
    #endif
    #if(CANTRCV_TCAN1145_SUPPORTED == STD_ON)
    case CANTRCV_TCAN1145 :
     /* @Trace: CanTrcv_SUD_API_362 */
     /* Clear SYSERR flag for TCAN1145 device */
     returnValue = CanTrcv_TCAN1145ClearSyserrFlag(transceiver);
     break;
    #endif
    default:
     /*Nothing to do*/
     break;
  }

  return returnValue;
}
#endif /* (((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
  (STD_ON == CANTRCV_TCAN1145_SUPPORTED)) && \
  (STD_ON == CANTRCV_HW_PN_SUPPORTED)) */

#if ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
  (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
  (STD_ON == CANTRCV_TLE9255W_SUPPORTED))
/*******************************************************************************
** Function Name      : CanTrcv_IntInitializeBySpi                            **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function will initialize for CAN Transceiver     **
**                      via Spi.                                              **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - Can Transceiver ID                      **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK:     The initialization is successful.           **
**                      E_NOT_OK: The initialization is not successful.       **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_XJA11XX_SUPPORTED or                **
**                      STD_ON == CANTRCV_TLE9255W_SUPPORTED or               **
**                      STD_ON == CANTRCV_TCAN1145_SUPPORTED                  **
**                                                                            **
** Remarks            : Global variable(s):                                   **
**                      CanTrcv_CanTrcvNetwork                                **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      CanTrcv_XJA11XXInit,                                  **
**                      CanTrcv_TLE9255WInit                                  **
**                      CanTrcv_TCAN1145Init                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00180
*/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_IntInitializeBySpi(
  CONST(uint8, AUTOMATIC) transceiver)
{
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  /* Initialize return value to E_OK */
  returnValue = E_NOT_OK;

  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];

  /* Check hardware device type */
  #if (STD_ON == CANTRCV_XJA11XX_SUPPORTED)
  if ((CANTRCV_TJA1145 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_UJA1169 == ptrCanTrcvNetwork->CanTrcvHwDev))
  {
    /* @Trace: CanTrcv_SUD_API_015 */
    /* Initialize for XJA11XX device */
    returnValue = CanTrcv_XJA11XXInit(transceiver, ptrCanTrcvNetwork);
  }
  else
  #endif /* (STD_ON == CANTRCV_XJA11XX_SUPPORTED) */
  {
    #if (STD_ON == CANTRCV_TCAN1145_SUPPORTED)
    if (CANTRCV_TCAN1145== ptrCanTrcvNetwork->CanTrcvHwDev)
    {
      /* @Trace: CanTrcv_SUD_API_317 */
      /* Initialize for TCAN1145 device */
      returnValue = CanTrcv_TCAN1145Init(transceiver, ptrCanTrcvNetwork);
    }
    else
    {
      /* Nothing to do */
    }
    #endif /* (STD_ON == CANTRCV_TCAN1145_SUPPORTED) */

    #if (STD_ON == CANTRCV_TLE9255W_SUPPORTED)
    if (CANTRCV_TLE9255W == ptrCanTrcvNetwork->CanTrcvHwDev)
    {
      /* @Trace: CanTrcv_SUD_API_016 */
      /* Initialize for TLE9255W device */
      returnValue = CanTrcv_TLE9255WInit(transceiver, ptrCanTrcvNetwork);
    }
    else
    {
      /* Nothing to do */
    }
    #endif /* (STD_ON == CANTRCV_TLE9255W_SUPPORTED) */
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_IntDeInitializeBySpi                          **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function will deinitialize CAN Transceiver       **
**                      via Spi.                                              **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - Can Transceiver ID                      **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK:     The deinitialization is successful.         **
**                      E_NOT_OK: The deinitialization is not successful.     **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_XJA11XX_SUPPORTED or                **
**                      STD_ON == CANTRCV_TLE9255W_SUPPORTED                  **
**                      STD_ON == CANTRCV_TCAN1145_SUPPORTED                  **
**                                                                            **
** Remarks            : Global variable(s):                                   **
**                      CanTrcv_CanTrcvNetwork                                **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      CanTrcv_XJA11XXDeInit,                                **
**                      CanTrcv_TLE9255WDeInit                                **
**                      CanTrcv_TCAN1145DeInit                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_91002 SRS_Can_01108
*/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_IntDeInitializeBySpi(
  CONST(uint8, AUTOMATIC) transceiver)
{
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  /* Initialize return value to E_OK */
  returnValue = E_NOT_OK;

  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];

  /* Check hardware device type */
  #if (STD_ON == CANTRCV_XJA11XX_SUPPORTED)
  if ((CANTRCV_TJA1145 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_UJA1169 == ptrCanTrcvNetwork->CanTrcvHwDev))
  {
    /* @Trace: CanTrcv_SUD_API_146 */
    /* Deinitialize for XJA11XX device */
    returnValue = CanTrcv_XJA11XXDeInit(transceiver);
  }
  else
  #endif /* (STD_ON == CANTRCV_XJA11XX_SUPPORTED) */
  {
    #if (STD_ON == CANTRCV_TLE9255W_SUPPORTED)
    if (CANTRCV_TLE9255W == ptrCanTrcvNetwork->CanTrcvHwDev)
    {
      /* @Trace: CanTrcv_SUD_API_147 */
      /* Deinitialize for TLE9255W device */
      returnValue = CanTrcv_TLE9255WDeInit(transceiver);
    }
    else
    {
      /* Nothing to do */
    }
    #endif /* (STD_ON == CANTRCV_TLE9255W_SUPPORTED) */

    #if (STD_ON == CANTRCV_TCAN1145_SUPPORTED)
    if (CANTRCV_TCAN1145== ptrCanTrcvNetwork->CanTrcvHwDev)
    {
      /* @Trace: CanTrcv_SUD_API_361 */
      /* Initialize for TCAN1145 device */
      returnValue = CanTrcv_TCAN1145DeInit(transceiver);
    }
    else
    {
      /* Nothing to do */
    }
    #endif /* (STD_ON == CANTRCV_TCAN1145_SUPPORTED) */
  }

  return returnValue;
}
#endif /* ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
    (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
    (STD_ON == CANTRCV_TLE9255W_SUPPORTED)) */

/* Functions for Partial Networking */
#if (STD_ON == CANTRCV_HW_PN_SUPPORTED)

/*******************************************************************************
** Function Name      : CanTrcv_IntInitializePN                               **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to initialize for CAN Transceiver which **
**                      has support selective wake up.                        **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK:     The initialization is successful.           **
**                      E_NOT_OK: The initialization is not successful.       **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_XJA11XX_SUPPORTED or                **
**                      STD_ON == CANTRCV_TLE9255W_SUPPORTED                  **
**                      STD_ON == CANTRCV_TCAN1145_SUPPORTED                  **
**                                                                            **
** Remarks            : Global variable(s):                                   **
**                      CanTrcv_CanTrcvNetwork                                **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      CanTrcv_XJA11XXConfigurePartialNetworking,            **
**                      CanTrcv_TLE9255WConfigurePartialNetworking            **
**                      CanTrcv_TCAN1145ConfigurePartialNetworking            **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00182
*/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_IntInitializePN(
  CONST(uint8, AUTOMATIC) transceiver)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  #if ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
    (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
    (STD_ON == CANTRCV_TLE9255W_SUPPORTED))
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;

  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];
  #else
  CANTRCV_UNUSED_VAL(transceiver);
  #endif /* ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
    (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
    (STD_ON == CANTRCV_TLE9255W_SUPPORTED)) */

  /* Initialize return value to E_OK */
  returnValue = E_NOT_OK;

  #if (STD_ON == CANTRCV_XJA11XX_SUPPORTED)
  /* Check hardware device type */
  if ((CANTRCV_TJA1145 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_UJA1169 == ptrCanTrcvNetwork->CanTrcvHwDev))
  {
    /* @Trace: CanTrcv_SUD_API_060 */
    /* Initialize PN for XJA11XX device */
    returnValue = CanTrcv_XJA11XXConfigurePartialNetworking(transceiver);
  }
  else
  #endif /* (STD_ON == CANTRCV_XJA11XX_SUPPORTED) */
  {
    #if (STD_ON == CANTRCV_TLE9255W_SUPPORTED)
    if (CANTRCV_TLE9255W == ptrCanTrcvNetwork->CanTrcvHwDev)
    {
      /* @Trace: CanTrcv_SUD_API_061 */
      /* Initialize PN for TLE9255W device */
      returnValue = CanTrcv_TLE9255WConfigurePartialNetworking(transceiver);
    }
    else
    {
      /* Other devices are not support selective wake up */
    }
    #endif /* (STD_ON == CANTRCV_TLE9255W_SUPPORTED) */

    #if (STD_ON == CANTRCV_TCAN1145_SUPPORTED)
    if (CANTRCV_TCAN1145== ptrCanTrcvNetwork->CanTrcvHwDev)
    {
      /* @Trace: CanTrcv_SUD_API_363 */
      /* Initialize PN for TCAN1145 device */
      returnValue = CanTrcv_TCAN1145ConfigurePartialNetworking(transceiver);
    }
    else
    {
      /* Other devices are not support selective wake up */
    }
    #endif /* (STD_ON == CANTRCV_TCAN1145_SUPPORTED) */
  }

  return returnValue;
}

#if (STD_ON == CANTRCV_HW_POR_SUPPORTED)

/*******************************************************************************
** Function Name      : CanTrcv_IntGetPorFlag                                 **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to get POR flag status.                 **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : ptrPorFlag - Store POR flag status.                   **
**                                                                            **
** Return parameter   : E_OK:     Get status successfully.                    **
**                      E_NOT_OK: Get status not successfully.                **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_HW_PN_SUPPORTED and                 **
**                      STD_ON == CANTRCV_HW_POR_SUPPORTED                    **
**                                                                            **
** Remarks            : Global variable(s):                                   **
**                      CanTrcv_CanTrcvNetwork                                **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      CanTrcv_XJA11XXGetPorFlag,                            **
**                      CanTrcv_TLE9255WGetPorFlag                            **
**                      CanTrcv_TCAN1145GetPorFlag                            **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00181
*/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_IntGetPorFlag(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(boolean, AUTOMATIC, CANTRCV_APPL_DATA) ptrPorFlag)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  #if ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
    (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
    (STD_ON == CANTRCV_TLE9255W_SUPPORTED))
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;

  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];
  #endif /* ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
    (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
    (STD_ON == CANTRCV_TLE9255W_SUPPORTED)) */

  /* Initialize return value to E_OK */
  returnValue = E_NOT_OK;

  #if (STD_ON == CANTRCV_XJA11XX_SUPPORTED)
  /* Check hardware device type */
  if ((CANTRCV_TJA1145 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_UJA1169 == ptrCanTrcvNetwork->CanTrcvHwDev))
  {
    /* @Trace: CanTrcv_SUD_API_046 */
    /* Get POR flag of XJA11XX device */
    returnValue = CanTrcv_XJA11XXGetPorFlag(transceiver, ptrPorFlag);
  }
  else
  #endif /* (STD_ON == CANTRCV_XJA11XX_SUPPORTED) */
  {
    #if (STD_ON == CANTRCV_TLE9255W_SUPPORTED)
    if (CANTRCV_TLE9255W == ptrCanTrcvNetwork->CanTrcvHwDev)
    {
      /* @Trace: CanTrcv_SUD_API_047 */
      /* Get POR flag of TLE9255W device */
      returnValue = CanTrcv_TLE9255WGetPorFlag(transceiver, ptrPorFlag);
    }
    else
    {
      /* Other device is not support control POR flag */
    }
    #endif /* (STD_ON == CANTRCV_TLE9255W_SUPPORTED) */

     #if (STD_ON == CANTRCV_TCAN1145_SUPPORTED)
    if (CANTRCV_TCAN1145== ptrCanTrcvNetwork->CanTrcvHwDev)
    {
      /* @Trace: CanTrcv_SUD_API_380 */
      /* Get POR flag of TCAN1145 device */
      returnValue = CanTrcv_TCAN1145GetPorFlag(transceiver, ptrPorFlag);
    }
    else
    {
      /* Other device is not support control POR flag */
    }
    #endif /* (STD_ON == CANTRCV_TCAN1145_SUPPORTED) */
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_IntClearPorFlag                               **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to clear POR flag.                      **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK:     Clear POR flag is successfully.             **
**                      E_NOT_OK: Clear POR is not successfully.              **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_HW_PN_SUPPORTED and                 **
**                      STD_ON == CANTRCV_HW_POR_SUPPORTED                    **
**                                                                            **
** Remarks            : Global variable(s):                                   **
**                      CanTrcv_CanTrcvNetwork                                **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      CanTrcv_XJA11XXClearPorFlag,                          **
**                      CanTrcv_TLE9255WClearPorFlag                          **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00181
*/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_IntClearPorFlag(
  CONST(uint8, AUTOMATIC) transceiver)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  #if ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
  (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
  (STD_ON == CANTRCV_TLE9255W_SUPPORTED))
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;

  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];
  #endif /* ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
    (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
    (STD_ON == CANTRCV_TLE9255W_SUPPORTED)) */

  /* Initialize return value to E_OK */
  returnValue = E_NOT_OK;

  #if (STD_ON == CANTRCV_XJA11XX_SUPPORTED)
  /* Check hardware device type */
  if ((CANTRCV_TJA1145 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_UJA1169 == ptrCanTrcvNetwork->CanTrcvHwDev))
  {
    /* @Trace: CanTrcv_SUD_API_050 */
    /* Clear POR flag on XJA11XX device */
    returnValue = CanTrcv_XJA11XXClearPorFlag(transceiver);
  }
  else
  #endif /* (STD_ON == CANTRCV_XJA11XX_SUPPORTED) */
  {
    #if (STD_ON == CANTRCV_TLE9255W_SUPPORTED)
    if (CANTRCV_TLE9255W == ptrCanTrcvNetwork->CanTrcvHwDev)
    {
      /* @Trace: CanTrcv_SUD_API_051 */
      /* Clear POR flag on TLE9255W device */
      returnValue = CanTrcv_TLE9255WClearPorFlag(transceiver);
    }
    else
    {
      /* Other device is not support control POR flag */
    }
    #endif /* (STD_ON == CANTRCV_TLE9255W_SUPPORTED) */

    #if (STD_ON == CANTRCV_TCAN1145_SUPPORTED)
    if (CANTRCV_TCAN1145 == ptrCanTrcvNetwork->CanTrcvHwDev)
    {
      /* @Trace: CanTrcv_SUD_API_377 */
      /* Clear POR flag on TCAN1145 device */
      returnValue = CanTrcv_TCAN1145ClearPorFlag(transceiver);
    }
    else
    {
      /* Other device is not support control POR flag */
    }
    #endif /* (STD_ON == CANTRCV_TCAN1145_SUPPORTED) */
  }

  return returnValue;
}

#endif /* (STD_ON == CANTRCV_HW_POR_SUPPORT) */

/*******************************************************************************
** Function Name        : CanTrcv_IntGetSyserrFlag                            **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : This function will get SYSERR flag.                 **
**                                                                            **
** Sync/Async           : N/A                                                 **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : transceiver - CAN Transceiver ID.                   **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : ptrSyserrFlag - Store status of SYSERR flag.        **
**                                                                            **
** Return parameter     : E_OK:     Get status successfully.                  **
**                        E_NOT_OK: Get status not successfully.              **
**                                                                            **
** Preconditions        : STD_ON == CANTRCV_HW_PN_SUPPORTED                   **
**                                                                            **
** Remarks              : Global variable(s): CanTrcv_CanTrcvNetwork          **
**                                                                            **
**                        Function(s) invoked: CanTrcv_XJA11XXGetSyserrFlag,  **
**                                             CanTrcv_TLE9255WGetSyserrFlag  **
**                                             CanTrcv_TCAN1145GetSyserrFlag  **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00181
*/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_IntGetSyserrFlag(
  #if ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
  (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
  (STD_ON == CANTRCV_TLE9255W_SUPPORTED))
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(boolean, AUTOMATIC, CANTRCV_APPL_DATA) ptrSyserrFlag
  #else
  void
  #endif /* ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
    (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
    (STD_ON == CANTRCV_TLE9255W_SUPPORTED)) */
  )
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  #if ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
     (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
     (STD_ON == CANTRCV_TLE9255W_SUPPORTED))
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;

  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];
  #endif /* ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
    (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
    (STD_ON == CANTRCV_TLE9255W_SUPPORTED)) */

  /* Initialize local variable */
  returnValue = E_NOT_OK;

  #if (STD_ON == CANTRCV_XJA11XX_SUPPORTED)
  if ((CANTRCV_TJA1145 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_UJA1169 == ptrCanTrcvNetwork->CanTrcvHwDev))
  {
    /* @Trace: CanTrcv_SUD_API_054 */
    /* Get SYSERR flag of XJA11XX device */
    returnValue = CanTrcv_XJA11XXGetSyserrFlag(transceiver, ptrSyserrFlag);
  }
  else
  #endif /* (STD_ON == CANTRCV_XJA11XX_SUPPORTED) */
  {
    #if (STD_ON == CANTRCV_TLE9255W_SUPPORTED)
    if (CANTRCV_TLE9255W == ptrCanTrcvNetwork->CanTrcvHwDev)
    {
      /* @Trace: CanTrcv_SUD_API_055 */
      /* Get SYSERR flag of TLE9255W device */
      returnValue = CanTrcv_TLE9255WGetSyserrFlag(transceiver, ptrSyserrFlag);
    }
    else
    {
      /* Other device are not support get SYSERR flag */
    }
    #endif /* (STD_ON == CANTRCV_TLE9255W_SUPPORTED) */

    #if (STD_ON == CANTRCV_TCAN1145_SUPPORTED)
    if (CANTRCV_TCAN1145 == ptrCanTrcvNetwork->CanTrcvHwDev)
    {
      /* @Trace: CanTrcv_SUD_API_378 */
      /* Get SYSERR flag of TCAN1145 device */
      returnValue = CanTrcv_TCAN1145GetSyserrFlag(transceiver, ptrSyserrFlag);
    }
    else
    {
      /* Other device are not support get SYSERR flag */
    }
    #endif /* (STD_ON == CANTRCV_TCAN1145_SUPPORTED) */
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_IntGetTrcvSystemData                          **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to get CAN Transceiver system data.     **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : ptrSystemData - Store CAN Transceiver system data.    **
**                                                                            **
** Return parameter   : E_OK: Get CAN Transceiver system data successful.     **
**                      E_NOT_OK: Get CAN Transceiver system data not         **
**                                successful or device is not support.        **
**                                                                            **
** Preconditions      : CANTRCV_HW_PN_SUPPORTED == STD_ON                     **
**                                                                            **
** Remarks            : Global Variable(s):                                   **
**                      CanTrcv_CanTrcvNetwork                                **
**                                                                            **
**                      Function(s) invoked:                                  **
                        CanTrcv_XJA11XXGetTrcvSystemData,                     **
**                      CanTrcv_TLE9255WGetTrcvSystemData                     **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00189 */
/* polyspace +3 MISRA2012:8.13 [Not a defect:Low] "This function definition follow Autosar requirement SWS_CanTrcv_00213(R21-11). No impact"*/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_IntGetTrcvSystemData(
  CONST(uint8, AUTOMATIC) transceiver
  #if ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
    (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
    (STD_ON == CANTRCV_TLE9255W_SUPPORTED))
  ,P2VAR(uint32, AUTOMATIC, CANTRCV_APPL_DATA) ptrSystemData
  #endif /* ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
    (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
    (STD_ON == CANTRCV_TLE9255W_SUPPORTED)) */
  )
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  #if ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
    (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
    (STD_ON == CANTRCV_TLE9255W_SUPPORTED))
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;

  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];
  #else
  CANTRCV_UNUSED_VAL(transceiver);
  #endif /* ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
    (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
    (STD_ON == CANTRCV_TLE9255W_SUPPORTED)) */

  /* Initialize local variable */
  returnValue = E_NOT_OK;

  /* Check hardware device type */
  #if (STD_ON == CANTRCV_XJA11XX_SUPPORTED)
  if ((CANTRCV_TJA1145 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_UJA1169 == ptrCanTrcvNetwork->CanTrcvHwDev))
  {
    /* @Trace: CanTrcv_SUD_API_178 */
    /* Get system data of XJA11XX device */
    returnValue = CanTrcv_XJA11XXGetTrcvSystemData(transceiver, ptrSystemData);
  }
  else
  #endif /* (STD_ON == CANTRCV_XJA11XX_SUPPORTED) */
  {
    #if (STD_ON == CANTRCV_TLE9255W_SUPPORTED)
    if (CANTRCV_TLE9255W == ptrCanTrcvNetwork->CanTrcvHwDev)
    {
      /* @Trace: CanTrcv_SUD_API_179 */
      /* Get system data of TLE9255W device */
      returnValue = CanTrcv_TLE9255WGetTrcvSystemData(transceiver, ptrSystemData);
    }
    else
    {
      /* Other devices are not support get system data */
    }
    #endif /* (STD_ON == CANTRCV_TLE9255W_SUPPORTED) */

    #if (STD_ON == CANTRCV_TCAN1145_SUPPORTED)
    if (CANTRCV_TCAN1145 == ptrCanTrcvNetwork->CanTrcvHwDev)
    {
      /* @Trace: CanTrcv_SUD_API_364 */
      /* Get system data of TCAN1145 device */
      returnValue = CanTrcv_TCAN1145GetTrcvSystemData(transceiver, ptrSystemData);
    }
    else
    {
      /* Other devices are not support get system data */
    }
    #endif /* (STD_ON == CANTRCV_TCAN1145_SUPPORTED) */
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_IntReadTrcvTimeoutFlag                        **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to get CAN Transceiver time out flag.   **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : ptrFlagState - Store CAN Transceiver time out flag.   **
**                                                                            **
** Return parameter   : E_OK: Get CAN Transceiver time out flag successful.   **
**                      E_NOT_OK: Get CAN Transceiver time out flag not       **
**                                successful or device is not support.        **
**                                                                            **
** Preconditions      : CANTRCV_HW_PN_SUPPORTED == STD_ON                     **
**                                                                            **
** Remarks            : Global Variable(s):                                   **
**                      CanTrcv_CanTrcvNetwork                                **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      CanTrcv_XJA11XXReadTrcvTimeoutFlag,                   **
**                      CanTrcv_TLE9255WReadTrcvTimeoutFlag                   **
**                      CanTrcv_TCAN1145ReadTrcvTimeoutFlag                   **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00215 SWS_CanTrcv_00211
*/
/* polyspace +4 MISRA2012:8.13 [Not a defect:Low] "This function definition follow Autosar requirement SWS_CanTrcv_00215(R21-11). No impact "*/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_IntReadTrcvTimeoutFlag(
  #if ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
    (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
    (STD_ON == CANTRCV_TLE9255W_SUPPORTED))
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(CanTrcv_TrcvFlagStateType, AUTOMATIC, CANTRCV_APPL_DATA) ptrFlagState
  #else
  void
  #endif /* ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
    (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
    (STD_ON == CANTRCV_TLE9255W_SUPPORTED)) */
  )
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  #if ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
    (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
    (STD_ON == CANTRCV_TLE9255W_SUPPORTED))
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;

  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];
  #endif /* ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
    (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
    (STD_ON == CANTRCV_TLE9255W_SUPPORTED)) */

  /* Initialize local variable */
  returnValue = E_NOT_OK;

  /* Check hardware device type */
  #if (STD_ON == CANTRCV_XJA11XX_SUPPORTED)
  if ((CANTRCV_TJA1145 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_UJA1169 == ptrCanTrcvNetwork->CanTrcvHwDev))
  {
    /* @Trace: CanTrcv_SUD_API_182 */
    /* Get time out flag on XJA11XX device */
    returnValue = CanTrcv_XJA11XXReadTrcvTimeoutFlag(transceiver, ptrFlagState);
  }
  else
  #endif /* (STD_ON == CANTRCV_XJA11XX_SUPPORTED) */
  {
    #if (STD_ON == CANTRCV_TLE9255W_SUPPORTED)
    if (CANTRCV_TLE9255W == ptrCanTrcvNetwork->CanTrcvHwDev)
    {
      /* @Trace: CanTrcv_SUD_API_183 */
      /* Get time out flag on TLE9255W device */
      returnValue = CanTrcv_TLE9255WReadTrcvTimeoutFlag(transceiver, ptrFlagState);
    }
    else
    {
      /* Other devices are not support get time out flag */
    }
    #endif /* (STD_ON == CANTRCV_TLE9255W_SUPPORTED) */

    #if (STD_ON == CANTRCV_TCAN1145_SUPPORTED)
    if (CANTRCV_TCAN1145 == ptrCanTrcvNetwork->CanTrcvHwDev)
    {
      /* @Trace: CanTrcv_SUD_API_365 */
      /* Get time out flag on TCAN1145 device */
      returnValue = CanTrcv_TCAN1145ReadTrcvTimeoutFlag(transceiver, ptrFlagState);
    }
    else
    {
      /* Other devices are not support get time out flag */
    }
    #endif /* (STD_ON == CANTRCV_TCAN1145_SUPPORTED) */
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_IntClearTrcvTimeoutFlag                       **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to clear CAN Transceiver time out flag. **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Clear CAN Transceiver time out flag successful. **
**                      E_NOT_OK: Clear CAN Transceiver time out flag not     **
**                                successful or device is not support.        **
**                                                                            **
** Preconditions      : CANTRCV_HW_PN_SUPPORTED == STD_ON                     **
**                                                                            **
** Remarks            : Global Variable(s):                                   **
**                      CanTrcv_CanTrcvNetwork                                **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      CanTrcv_XJA11XXClearTrcvTimeoutFlag,                  **
**                      CanTrcv_TLE9255WClearTrcvTimeoutFlag                  **
**                      CanTrcv_TCAN1145ClearTrcvTimeoutFlag                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00216
*/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_IntClearTrcvTimeoutFlag(
  CONST(uint8, AUTOMATIC) transceiver)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  #if ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
    (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
    (STD_ON == CANTRCV_TLE9255W_SUPPORTED))
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;

  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];
  #else
  CANTRCV_UNUSED_VAL(transceiver);
  #endif /* ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
    (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
    (STD_ON == CANTRCV_TLE9255W_SUPPORTED)) */

  /* Initialize local variable */
  returnValue = E_NOT_OK;

  /* Check hardware device type */
  #if (STD_ON == CANTRCV_XJA11XX_SUPPORTED)
  if ((CANTRCV_TJA1145 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_UJA1169 == ptrCanTrcvNetwork->CanTrcvHwDev))
  {
    /* @Trace: CanTrcv_SUD_API_188 */
    /* Get time out flag of XJA11XX device */
    returnValue = CanTrcv_XJA11XXClearTrcvTimeoutFlag(transceiver);
  }
  else
  #endif /* (STD_ON == CANTRCV_XJA11XX_SUPPORTED) */
  {
    #if (STD_ON == CANTRCV_TLE9255W_SUPPORTED)
    if (CANTRCV_TLE9255W == ptrCanTrcvNetwork->CanTrcvHwDev)
    {
      /* @Trace: CanTrcv_SUD_API_189 */
      /* Get time out flag of TLE9255W device */
      returnValue = CanTrcv_TLE9255WClearTrcvTimeoutFlag(transceiver);
    }
    else
    {
      /* Other devices are not support clear time out flag */
    }
    #endif /* (STD_ON == CANTRCV_TLE9255W_SUPPORTED) */

    #if (STD_ON == CANTRCV_TCAN1145_SUPPORTED)
    if (CANTRCV_TCAN1145 == ptrCanTrcvNetwork->CanTrcvHwDev)
    {
      /* @Trace: CanTrcv_SUD_API_366 */
      /* Get time out flag of TCAN1145 device */
      returnValue = CanTrcv_TCAN1145ClearTrcvTimeoutFlag(transceiver);
    }
    else
    {
      /* Other devices are not support clear time out flag */
    }
    #endif /* (STD_ON == CANTRCV_TCAN1145_SUPPORTED) */
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_IntReadTrcvSilenceFlag                        **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to read CAN Transceiver silence flag.   **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : FlagState - Store the status of silence flag.         **
**                                                                            **
** Return parameter   : E_OK: Read  CAN Transceiver silence flag success.     **
**                      E_NOT_OK: Read CAN Transceiver silence flag is not    **
**                                successful or device is not support.        **
**                                                                            **
** Preconditions      : CANTRCV_HW_PN_SUPPORTED == STD_ON                     **
**                                                                            **
** Remarks            : Global Variable(s): CanTrcv_CanTrcvNetwork            **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      CanTrcv_XJA11XXReadTrcvSilenceFlag,                   **
**                      CanTrcv_TLE9255WReadTrcvSilenceFlag                   **
**                      CanTrcv_TCAN1145ReadTrcvSilenceFlag                   **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00217 SWS_CanTrcv_00211 */
/* polyspace +4 MISRA2012:8.13 [Not a defect:Low] " This function definition follow Autosar requirement SWS_CanTrcv_00217(R21-11). No impact "*/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_IntReadTrcvSilenceFlag(
  #if ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
    (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
    (STD_ON == CANTRCV_TLE9255W_SUPPORTED))
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(CanTrcv_TrcvFlagStateType, AUTOMATIC, CANTRCV_APPL_DATA) ptrFlagState
  #else
  void
  #endif
  )
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  #if ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
    (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
    (STD_ON == CANTRCV_TLE9255W_SUPPORTED))
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;

  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];
  #endif /* ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
    (STD_ON == CANTRCV_TLE9255W_SUPPORTED)) */

  /* Initialize local variable */
  returnValue = E_NOT_OK;

  /* Check hardware device type */
  #if (STD_ON == CANTRCV_XJA11XX_SUPPORTED)
  if ((CANTRCV_TJA1145 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_UJA1169 == ptrCanTrcvNetwork->CanTrcvHwDev))
  {
    /* @Trace: CanTrcv_SUD_API_195 */
    /* Get silence flag of XJA11XX device */
    returnValue = CanTrcv_XJA11XXReadTrcvSilenceFlag(transceiver,
      ptrFlagState);
  }
  else
  #endif /* (STD_ON == CANTRCV_XJA11XX_SUPPORTED) */
  {
    #if (STD_ON == CANTRCV_TLE9255W_SUPPORTED)
    if (CANTRCV_TLE9255W == ptrCanTrcvNetwork->CanTrcvHwDev)
    {
      /* @Trace: CanTrcv_SUD_API_196 */
      /* Get silence flag of TLE9255W device */
      returnValue = CanTrcv_TLE9255WReadTrcvSilenceFlag(transceiver,
        ptrFlagState);
    }
    else
    {
      /* Other devices are not support read status silence flag */
    }
    #endif /* (STD_ON == CANTRCV_TLE9255W_SUPPORTED) */

    #if (STD_ON == CANTRCV_TCAN1145_SUPPORTED)
    if (CANTRCV_TCAN1145 == ptrCanTrcvNetwork->CanTrcvHwDev)
    {
      /* @Trace: CanTrcv_SUD_API_367 */
      /* Get silence flag of TCAN1145 device */
      returnValue = CanTrcv_TCAN1145ReadTrcvSilenceFlag(transceiver,
        ptrFlagState);
    }
    else
    {
      /* Other devices are not support read status silence flag */
    }
    #endif /* (STD_ON == CANTRCV_TCAN1145_SUPPORTED) */
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_IntSetPNActivationState                       **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to set state of partial networking.     **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver     - CAN Transceiver ID.                 **
**                      activationState - PN_ENABLED: PN wakeup enable.       **
**                                        PN_DIABLED: PN wakeup disbale.      **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Set PN Activation state is success.             **
**                      E_NOT_OK: Set PN Activation state success is not      **
**                                successful or device is not support.        **
**                                                                            **
** Preconditions      : CANTRCV_HW_PN_SUPPORTED == STD_ON                     **
**                                                                            **
** Remarks            : Global Variable(s):                                   **
**                      CanTrcv_CanTrcvNetwork                                **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      CanTrcv_XJA11XXSetPNActivationState,                  **
**                      CanTrcv_TLE9255WSetPNActivationState                  **
**                      CanTrcv_TCAN1145SetPNActivationState                  **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00221 SWS_CanTrcv_00222
  SWS_CanTrcv_00210
*/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_IntSetPNActivationState(
  CONST(uint8, AUTOMATIC) transceiver,
  CONST(CanTrcv_PNActivationType, AUTOMATIC) activationState)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  #if ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
    (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
    (STD_ON == CANTRCV_TLE9255W_SUPPORTED))
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;

  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];
  #else
  CANTRCV_UNUSED_VAL(transceiver);
  CANTRCV_UNUSED_VAL(activationState);
  #endif /* ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
    (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
    (STD_ON == CANTRCV_TLE9255W_SUPPORTED)) */

  /* Initialize local variable */
  returnValue = E_NOT_OK;

  /* Check hardware device type */
  #if (STD_ON == CANTRCV_XJA11XX_SUPPORTED)
  if ((CANTRCV_TJA1145 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_UJA1169 == ptrCanTrcvNetwork->CanTrcvHwDev))
  {
    /* @Trace: CanTrcv_SUD_API_201 */
    /* Set state of partial networking on XJA11XX device */
    returnValue = CanTrcv_XJA11XXSetPNActivationState(transceiver,
      activationState);
  }
  else
  #endif /* (STD_ON == CANTRCV_XJA11XX_SUPPORTED) */
  {
    #if (STD_ON == CANTRCV_TLE9255W_SUPPORTED)
    if (CANTRCV_TLE9255W == ptrCanTrcvNetwork->CanTrcvHwDev)
    {
      /* @Trace: CanTrcv_SUD_API_202 */
      /* Set state of partial networking on TLE9255W device */
      returnValue = CanTrcv_TLE9255WSetPNActivationState(transceiver,
        activationState);
    }
    else
    {
      /* Other devices are not support read status silence flag */
    }
    #endif /* (STD_ON == CANTRCV_TLE9255W_SUPPORTED) */

    #if (STD_ON == CANTRCV_TCAN1145_SUPPORTED)
    if (CANTRCV_TCAN1145 == ptrCanTrcvNetwork->CanTrcvHwDev)
    {
      /* @Trace: CanTrcv_SUD_API_368 */
      /* Set state of partial networking on TCAN1145 device */
      returnValue = CanTrcv_TCAN1145SetPNActivationState(transceiver,
        activationState);
    }
    else
    {
      /* Other devices are not support read status silence flag */
    }
    #endif /* (STD_ON == CANTRCV_TCAN1145_SUPPORTED) */
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_IntClearTrcvWufFlag                           **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to clear wake up frame flag.            **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Clear wake up frame flag success.               **
**                      E_NOT_OK: Clear wake up fram flag is not success or   **
**                                device is not support.                      **
**                                                                            **
** Preconditions      : CANTRCV_HW_PN_SUPPORTED == STD_ON                     **
**                                                                            **
** Remarks            : Global Variable(s):                                   **
**                      CanTrcv_CanTrcvNetwork                                **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      CanTrcv_XJA11XXClearTrcvWufFlag,                      **
**                      CanTrcv_TLE9255WClearTrcvWufFlag,                     **
**                      CanTrcv_TCAN1145ClearTrcvWufFlag                      **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00194
*/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_IntClearTrcvWufFlag(
  CONST(uint8, AUTOMATIC) transceiver)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  #if ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
    (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
    (STD_ON == CANTRCV_TLE9255W_SUPPORTED))
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;

  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];
  #else
  CANTRCV_UNUSED_VAL(transceiver);
  #endif /* ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
    (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
    (STD_ON == CANTRCV_TLE9255W_SUPPORTED)) */

  /* Initialize local variable */
  returnValue = E_NOT_OK;

  /* Check hardware device type */
  #if (STD_ON == CANTRCV_XJA11XX_SUPPORTED)
  if ((CANTRCV_TJA1145 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_UJA1169 == ptrCanTrcvNetwork->CanTrcvHwDev))
  {
    /* @Trace: CanTrcv_SUD_API_208 */
    /* Set state of partial networking on XJA11XX device */
    returnValue = CanTrcv_XJA11XXClearTrcvWufFlag(transceiver);
  }
  else
  #endif /* (STD_ON == CANTRCV_XJA11XX_SUPPORTED) */
  {
    #if (STD_ON == CANTRCV_TLE9255W_SUPPORTED)
    if (CANTRCV_TLE9255W == ptrCanTrcvNetwork->CanTrcvHwDev)
    {
      /* @Trace: CanTrcv_SUD_API_209 */
      /* Set state of partial networking on TLE9255W device */
      returnValue = CanTrcv_TLE9255WClearTrcvWufFlag(transceiver);
    }
    else
    {
      /* Other devices are not support wake up frame flag */
    }
    #endif /* (STD_ON == CANTRCV_TLE9255W_SUPPORTED) */

    #if (STD_ON == CANTRCV_TCAN1145_SUPPORTED)
    if (CANTRCV_TCAN1145 == ptrCanTrcvNetwork->CanTrcvHwDev)
    {
      /* @Trace: CanTrcv_SUD_API_369 */
      /* Set state of partial networking on TCAN1145 device */
      returnValue = CanTrcv_TCAN1145ClearTrcvWufFlag(transceiver);
    }
    else
    {
      /* Other devices are not support wake up frame flag */
    }
    #endif /* (STD_ON == CANTRCV_TCAN1145_SUPPORTED) */
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_IntCheckWakeFlag                              **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to check wake up flag.                  **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: The request for checking the wakeup flag has    **
**                            been accepted.                                  **
**                      E_NOT_OK: The request for checking the wakeup flag    **
**                                has not been accepted.                      **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_WAKEUP_SUPPORTED                    **
**                                                                            **
** Remarks            : Global variable(s):                                   **
**                      CanTrcv_CanTrcvNetwork                                **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      Dio_ReadChannel,                                      **
**                      CanTrcv_XJA11XXCheckWakeFlag,                         **
**                      CanTrcv_TLE9255WCheckWakeFlag,                        **
**                      CanTrcv_TCAN1145CheckWakeFlag,                        **
**                      CanIf_CheckTrcvWakeFlagIndication,                    **
**                      EcuM_SetWakeupEvent                                   **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00086 SWS_CanTrcv_00224
  SWS_CanTrcv_00086
*/
FUNC(void, CANTRCV_CODE) CanTrcv_IntCheckWakeFlag(
  CONST(uint8, AUTOMATIC) transceiver)
{

  #if ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
    (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
    (STD_ON == CANTRCV_TLE9255W_SUPPORTED))
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;

  /* @Trace: CanTrcv_SUD_API_233 */
  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];

  /* @Trace: CanTrcv_SUD_API_234 */
  /* Initialize local variables */
  returnValue = (Std_ReturnType)E_NOT_OK;
  #else
  CANTRCV_UNUSED_VAL(transceiver);
  #endif /* ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
    (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
    (STD_ON == CANTRCV_TLE9255W_SUPPORTED)) */

  #if (STD_ON == CANTRCV_XJA11XX_SUPPORTED)
  if ((CANTRCV_TJA1145 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_UJA1169 == ptrCanTrcvNetwork->CanTrcvHwDev))
  {
    /* @Trace: CanTrcv_SUD_API_235 */
    returnValue = CanTrcv_XJA11XXCheckWakeFlag(transceiver, ptrCanTrcvNetwork);
  }
  else
  #endif /* (STD_ON == CANTRCV_XJA11XX_SUPPORTED) */
  {
    #if (STD_ON == CANTRCV_TLE9255W_SUPPORTED)
    if (CANTRCV_TLE9255W == ptrCanTrcvNetwork->CanTrcvHwDev)
    {
      /* @Trace: CanTrcv_SUD_API_236 */
      returnValue = CanTrcv_TLE9255WCheckWakeFlag(transceiver, ptrCanTrcvNetwork);
    }
    else
    {
      /* Other device are not support check wake flag */
    }
    #endif /* (STD_ON == CANTRCV_TLE9255W_SUPPORTED) */

    #if (STD_ON == CANTRCV_TCAN1145_SUPPORTED)
    if (CANTRCV_TCAN1145 == ptrCanTrcvNetwork->CanTrcvHwDev)
    {
      /* @Trace: CanTrcv_SUD_API_371 */
      returnValue = CanTrcv_TCAN1145CheckWakeFlag(transceiver, ptrCanTrcvNetwork);
    }
    else
    {
      /* Other device are not support check wake flag */
    }
    #endif /* (STD_ON == CANTRCV_TCAN1145_SUPPORTED) */
  }
  #if ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
    (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
    (STD_ON == CANTRCV_TLE9255W_SUPPORTED))
  if (E_NOT_OK != returnValue)
  {
    /* @Trace: CanTrcv_SUD_API_237 */
    /* CanTrcv shall inform to CanIf that the wake flag has been checked */
    CanIf_CheckTrcvWakeFlagIndication(transceiver);
  }
  else
  {
    /* Nothing to do */
  }
  #endif /* ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
    (STD_ON == CANTRCV_TCAN1145_SUPPORTED) || \
    (STD_ON == CANTRCV_TLE9255W_SUPPORTED)) */
}
#endif /* (STD_ON == CANTRCV_HW_PN_SUPPORTED) */

#if (STD_ON == CANTRCV_WAKEUP_SUPPORTED)

/*******************************************************************************
** Function Name      : CanTrcv_IntSetWakeupMode                              **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to set wake up mode.                    **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN transceiver ID.                     **
**                    : trcvWakeupMode - Wake up state.                       **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: The request for checking the wakeup flag has    **
**                            been accepted.                                  **
**                      E_NOT_OK: The request for checking the wakeup flag    **
**                                has not been accepted.                      **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_WAKEUP_SUPPORTED                    **
**                                                                            **
** Remarks            : Global variable(s):                                   **
**                      CanTrcv_CanTrcvNetwork,                               **
**                      CanTrcv_WakeupPending,                                **
**                      CanTrcv_WakeupFlagIndication                          **
**                                                                            **
**                      Function(s) invoked : None                            **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00111 SWS_CanTrcv_00093 SWS_CanTrcv_00094
  SWS_CanTrcv_00164 SRS_BSW_00160 SRS_BSW_00388 SRS_BSW_00389 SRS_BSW_00390
  SRS_BSW_00392 SRS_BSW_00393 SRS_BSW_00394 SRS_BSW_00395 SRS_BSW_00408
  SRS_Can_01090
*/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_IntSetWakeupMode(
  CONST(uint8, AUTOMATIC) transceiver,
  CONST(CanTrcv_TrcvWakeupModeType, AUTOMATIC) trcvWakeupMode)
{
  #if(STD_OFF == CANTRCV_ALL_HW_SUPPORT_WAKEUP)
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  #endif
  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  /* Check hardware device type */
  #if(STD_OFF == CANTRCV_ALL_HW_SUPPORT_WAKEUP)
  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];
  
  if ((CANTRCV_NCV7342 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1040 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1041 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1041A == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1042 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1043 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1463 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1044 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1054 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1054A == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1055 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1057 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE6251G == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE62513G == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE6251DS == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE7250G == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE7250LE == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE62542G == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE62543G == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE9250SJ == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE9251VSJ == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1145 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_UJA1169 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE9255W == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TCAN1145 == ptrCanTrcvNetwork->CanTrcvHwDev))
  #endif /* #if(STD_OFF == CANTRCV_ALL_HW_SUPPORT_WAKEUP) */
  {
    if (CANTRCV_WUMODE_ENABLE == trcvWakeupMode)
    {
      /* Check there are any wake up event pending */
      if (CANTRCV_WAKEUP_PENDING == CanTrcv_WakeupPending[transceiver])
      {
        /* @Trace: CanTrcv_SUD_API_168 */
        /* Set wake up status */
        CanTrcv_WakeupFlagIndication[transceiver] = CANTRCV_WAKE_UP_OCCURRED;
      }
      else
      {
        /* Nothing to do */
      }
    }
    else if (CANTRCV_WUMODE_CLEAR == trcvWakeupMode)
    {
      /* @Trace: CanTrcv_SUD_API_169 */
      /* Clear pending wake up event */
      CanTrcv_WakeupPending[transceiver] = CANTRCV_WAKEUP_NO_PENDING;
    }
    else /* @ CANTRCV_WUMODE_DISABLE == trcvWakeupMode */
    {
      /* Nothing to do */
    }

    /* @Trace: CanTrcv_SUD_API_170 */
    /* Set wake up mode */
    CanTrcv_WakeupMode[transceiver] = trcvWakeupMode;
    /* Set return value */
    returnValue = E_OK;
  }
  #if(STD_OFF == CANTRCV_ALL_HW_SUPPORT_WAKEUP)
  else
  {
    /* Other device are not support set wake up mode */
    returnValue = E_NOT_OK;
  }
  #endif /* #if(STD_OFF == CANTRCV_ALL_HW_SUPPORT_WAKEUP) */

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_IntCheckWakeup                                **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to check wake up interrupt.             **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_WAKEUP_SUPPORTED                    **
**                                                                            **
** Remarks            : Global variable(s): CanTrcv_CanTrcvNetwork,           **
**                      CanTrcv_WakeupFlagIndication, CanTrcv_ByteArray       **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      EcuM_SetWakeupEvent                                   **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00143 SWS_CanTrcv_00086
*/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_IntCheckWakeup(
  CONST(uint8, AUTOMATIC) transceiver)
{
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];
  /* Initialize local variables */
  returnValue = E_OK;

  /* Check devices which have support wake up */
  #if(STD_OFF == CANTRCV_ALL_HW_SUPPORT_WAKEUP)
  if ((CANTRCV_NCV7342 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1040 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1041 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1041A == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1042 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1043 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1463 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1044 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1054 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1054A == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1055 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1057 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE6251G == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE62513G == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE6251DS == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE7250G == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE7250LE == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE62542G == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE62543G == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE9250SJ == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE9251VSJ == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1145 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_UJA1169 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE9255W == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TCAN1145 == ptrCanTrcvNetwork->CanTrcvHwDev))
  #endif /* #if(STD_OFF == CANTRCV_ALL_HW_SUPPORT_WAKEUP) */
  {
    /* Check wake up status */
    if (CANTRCV_WAKE_UP_OCCURRED == CanTrcv_WakeupFlagIndication[transceiver])
    {
      /* @Trace: CanTrcv_SUD_API_159 */
      /* Reset wake up status */
      CanTrcv_WakeupFlagIndication[transceiver] = CANTRCV_WAKE_UP_NOT_OCCURRED;
      /* Check current mode of CAN Transceiver */
      if (CANTRCV_TRCVMODE_SLEEP == CanTrcv_ByteArray[transceiver])
      {
        /* @Trace: CanTrcv_SUD_API_160 */
        /* Update current mode of CAN Transceiver because any interrupt occure
          in Sleep mode, CAN Transceiver will go to Standby mode */
        CanTrcv_ByteArray[transceiver] = CANTRCV_TRCVMODE_STANDBY;
      }
      else
      {
        /* Nothing to do */
      }

      /* @Trace: CanTrcv_SUD_API_161 */
      /* Reporting wake up event to EcuM */
      EcuM_SetWakeupEvent(ptrCanTrcvNetwork->WakeupSource);
    }
    else
    {
      /* Nothing to do */
    }
  }
  #if(STD_OFF == CANTRCV_ALL_HW_SUPPORT_WAKEUP)
  else
  {
    /* Set return value as E_NOT_OK */
    returnValue = E_NOT_OK;
  }
  #endif /* #if(STD_OFF == CANTRCV_ALL_HW_SUPPORT_WAKEUP) */
  
  return returnValue;
}

/*******************************************************************************
** Function Name        : CanTrcv_IntMainFunction                             **
**                                                                            **
** Service ID           : Not Applicable                                      **
**                                                                            **
** Description          : This function to check and perform wake up events.  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : transceiver - CAN Transceiver ID.                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global variable(s) : CanTrcv_CanTrcvNetwork         **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Dio_ReadChannel,                                    **
**                        CanTrcv_XJA11XXMainFunction,                        **
**                        CanTrcv_TLE9255WMainFunction                        **
**                        CanTrcv_TCAN1145MainFunction                        **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00112 SWS_CanTrcv_00086 SRS_BSW_00424
*/
FUNC(void, CANTRCV_CODE) CanTrcv_IntMainFunction(
  CONST(uint8, AUTOMATIC) transceiver)
{
  VAR(Dio_LevelType, AUTOMATIC) retValPin3;
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;

  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];

  #if(STD_OFF == CANTRCV_ALL_HW_SUPPORT_WAKEUP_EVENT)
  if ((CANTRCV_NCV7342 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1040 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1041 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1041A == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1042 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1043 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1463 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1044 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1054 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1054A == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1055 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1057 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE6251G == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE62513G == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE6251DS == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE7250G == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE7250LE == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE62542G == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE62543G == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE9250SJ == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE9251VSJ == ptrCanTrcvNetwork->CanTrcvHwDev))
  #endif /* #if(STD_OFF == CANTRCV_ALL_HW_SUPPORT_WAKEUP_EVENT) */
  {
    /* @Trace: CanTrcv_SUD_API_216 */
    /* Read value of ERR/RXD pin */
    retValPin3 = Dio_ReadChannel(ptrCanTrcvNetwork->SelectPin3);
    /* Check status of ERR/RXD pin */
    if (STD_LOW == retValPin3)
    {
      /* @Trace: CanTrcv_SUD_API_217 */
      /* Set wake up reason */
      CanTrcv_WakeUpReason[transceiver] = CANTRCV_WU_BY_BUS;
      /* Check wake up mode */
      if (CANTRCV_WUMODE_ENABLE == CanTrcv_WakeupMode[transceiver])
      {
        /* @Trace: CanTrcv_SUD_API_218 */
        /* Set wake up status */
        CanTrcv_WakeupFlagIndication[transceiver] = CANTRCV_WAKE_UP_OCCURRED;
      }
      else if (CANTRCV_WUMODE_DISABLE == CanTrcv_WakeupMode[transceiver])
      {
        /* @Trace: CanTrcv_SUD_API_219 */
        /* Store the pending wakeup event */
        CanTrcv_WakeupPending[transceiver] = CANTRCV_WAKEUP_PENDING;
      }
      else
      {
        /* Nothing to do */
      }
    }
    else
    {
      /* Nothing to do */
    }
  }
  #if (STD_ON == CANTRCV_XJA11XX_SUPPORTED)
  if ((CANTRCV_TJA1145 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_UJA1169 == ptrCanTrcvNetwork->CanTrcvHwDev))
  {
    /* @Trace: CanTrcv_SUD_API_220 */
    /* Invoke main function of XJA11XX device */
    CanTrcv_XJA11XXMainFunction(transceiver);
  }
  #endif /* (STD_ON == CANTRCV_XJA11XX_SUPPORTED) */
  #if (STD_ON == CANTRCV_TLE9255W_SUPPORTED)
  if (CANTRCV_TLE9255W == ptrCanTrcvNetwork->CanTrcvHwDev)
  {
    /* @Trace: CanTrcv_SUD_API_221 */
    /* Invoke main function of TLE9255W device */
    CanTrcv_TLE9255WMainFunction(transceiver);
  }
  #endif /* (STD_ON == CANTRCV_TLE9255W_SUPPORTED) */
  #if (STD_ON == CANTRCV_TCAN1145_SUPPORTED)
  if (CANTRCV_TCAN1145 == ptrCanTrcvNetwork->CanTrcvHwDev)
  {
    /* @Trace: CanTrcv_SUD_API_370 */
    /* Invoke main function of TCAN1145 device */
    CanTrcv_TCAN1145MainFunction(transceiver);
  }
  #endif /* (STD_ON == CANTRCV_TCAN1145_SUPPORTED) */
  CANTRCV_UNUSED_VAL(retValPin3);
}
#endif /* (STD_ON == CANTRCV_WAKEUP_SUPPORTED) */

#if (STD_ON == CANTRCV_E_BUS_ERROR_SUPPORTED)
/*******************************************************************************
** Function Name        : CanTrcv_IntMainFunctionDiagnostics                  **
**                                                                            **
** Service ID           : Not Applicable                                      **
**                                                                            **
** Description          : This service Reads the transceiver diagnostic       **
**                        status periodically and sets product/development    **
*                         accordingly.                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : transceiver - CAN Transceiver ID.                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global variable(s) : CanTrcv_CanTrcvNetwork         **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Dio_ReadChannel, CanTrcv_ReadReg,                   **
**                        Dem_SetEventStatus                                  **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00204 SWS_CanTrcv_00206 SWS_CanTrcv_00227 SRS_BSW_00327
  SRS_BSW_00331 SRS_BSW_00337 SRS_BSW_00424 SRS_BSW_00339
*/
FUNC(void, CANTRCV_CODE) CanTrcv_IntMainFunctionDiagnostics(
  CONST(uint8, AUTOMATIC) transceiver)
{
  #if ((STD_ON == CANTRCV_TCAN1145_SUPPORTED) ||(STD_ON == CANTRCV_XJA11XX_SUPPORTED))
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  VAR(uint8, AUTOMATIC) data;
  VAR(uint8, AUTOMATIC) returnStatus;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];
  #endif/*((STD_ON == CANTRCV_TCAN1145_SUPPORTED) ||(STD_ON == CANTRCV_XJA11XX_SUPPORTED))*/

  #if (STD_ON == CANTRCV_XJA11XX_SUPPORTED)
  if ((CANTRCV_TJA1145 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_UJA1169 == ptrCanTrcvNetwork->CanTrcvHwDev))
  {

    /* Initialize local variable */
    data = (uint8)CANTRCV_ZERO;

    /* @Trace: CanTrcv_SUD_API_246 */
    /* Read value in Transceiver status register */
    returnStatus = ptrWriteReadReg->ReadReg(transceiver, XJA11XX_TRCV_STATUS_REG, &data);

    /* Check CAN failure status */
    if (E_OK == returnStatus)
    {
    /* Get value bit CFS - bit 0 */
      data &= XJA11XX_CFS_MASK;
      if (XJA11XX_CFS_MASK != data)
      {
        /* @Trace: CanTrcv_SUD_API_247 */
        /* Set Dem Event */
        (void)Dem_SetEventStatus(ptrCanTrcvNetwork->DemEventId, DEM_EVENT_STATUS_PASSED);
      }
      else
      {
        /* @Trace: CanTrcv_SUD_API_248 */
        /* Set Dem Event */
        (void)Dem_SetEventStatus(ptrCanTrcvNetwork->DemEventId, DEM_EVENT_STATUS_FAILED);
      }
    }
    else
    {
    /* Nothing to do */
    }
  }
  #endif
  #if (STD_ON == CANTRCV_TCAN1145_SUPPORTED)
  if (CANTRCV_TCAN1145 == ptrCanTrcvNetwork->CanTrcvHwDev)
  {

    /* @Trace: CanTrcv_SUD_API_372 */
    /* Read value in Transceiver status register */
    returnStatus = ptrWriteReadReg->ReadReg(transceiver, TCAN1145_INT_1_REG, &data);

    /* Check CAN failure status */
    if (E_OK == returnStatus)
    {
    /* Get value bit CFS - bit 0 */
      data &= TCAN1145_INT_1_CANDOM;
      if (TCAN1145_INT_1_CANDOM != data)
      {
        /* @Trace: CanTrcv_SUD_API_373 */
        /* Set Dem Event */
        (void)Dem_SetEventStatus(ptrCanTrcvNetwork->DemEventId, DEM_EVENT_STATUS_PASSED);
      }
      else
      {
        /* @Trace: CanTrcv_SUD_API_374 */
        /* Set Dem Event */
        (void)Dem_SetEventStatus(ptrCanTrcvNetwork->DemEventId, DEM_EVENT_STATUS_FAILED);
      }
    }
    else
    {
    /* Nothing to do */
    }
  }
  else
  {
    /* Nothing to do */
  }
  #endif

  #if ((STD_OFF == CANTRCV_TCAN1145_SUPPORTED) &&(STD_OFF == CANTRCV_XJA11XX_SUPPORTED))
  CANTRCV_UNUSED_VAL(transceiver);
  #endif 
 
}
#endif /* (STD_ON == CANTRCV_E_BUS_ERROR_SUPPORTED) */

/* Functions for XJA11XX device */
#if (STD_ON == CANTRCV_XJA11XX_SUPPORTED)

/*******************************************************************************
** Function Name      : CanTrcv_XJA11XXSetModeControl                         **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to set mode control on XJA11XX device.  **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                      mode - Mode control.                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Set mode control successful.                    **
**                      E_NOT_OK: Set mode control not successful.            **
**                                                                            **
** Preconditions      : CANTRCV_XJA11XX_SUPPORTED == STD_ON                   **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_WriteReg                 **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00102
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXSetModeControl(
  CONST(uint8, AUTOMATIC) transceiver,
  CONST(XJA11XX_ModeControlType, AUTOMATIC) mode)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* @Trace: CanTrcv_SUD_API_133 */
  /* Set Mode Control - Bit MC */
  returnValue = ptrWriteReadReg->WriteReg(transceiver, XJA11XX_MODE_CONTROL_REG,
   (uint8)mode);

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_XJA11XXGetModeControl                         **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to get current mode control of XJA11XX  **
**                      device.                                               **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : ptrMode - Store value of mode control.                **
**                                                                            **
** Return parameter   : E_OK: Get mode control successful.                    **
**                      E_NOT_OK: Get mode control not successful.            **
**                                                                            **
** Preconditions      : CANTRCV_XJA11XX_SUPPORTED == STD_ON                   **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_ReadReg                  **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00163
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXGetModeControl(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(CanTrcv_TrcvModeType, AUTOMATIC, CANTRCV_APPL_DATA) ptrMode)
{
  VAR(uint8, AUTOMATIC) data;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Initialize local variable */
  data = (uint8)CANTRCV_ZERO;

  /* @Trace: CanTrcv_SUD_API_128 */
  /* Read value in Mode control register */
  returnValue = ptrWriteReadReg->ReadReg(transceiver, XJA11XX_MODE_CONTROL_REG, &data);
  if (E_NOT_OK != returnValue)
  {
    /* Get value of MC bit - bit [2:0] */
    data &= XJA11XX_MC_MASK;
    if ((uint32)XJA11XX_NORMAL_MODE == data)
    {
      /* @Trace: CanTrcv_SUD_API_129 */
      *ptrMode = CANTRCV_TRCVMODE_NORMAL;
    }
    else if ((uint32)XJA11XX_STANDBY_MODE == data)
    {
      /* @Trace: CanTrcv_SUD_API_130 */
      *ptrMode = CANTRCV_TRCVMODE_STANDBY;
    }
    else if ((uint32)XJA11XX_SLEEP_MODE == data)
    {
      /* @Trace: CanTrcv_SUD_API_131 */
      *ptrMode = CANTRCV_TRCVMODE_SLEEP;
    }
    else
    {
      /* @Trace: CanTrcv_SUD_API_132 */
      /* Set return value as E_NOT_OK */
      returnValue = E_NOT_OK;
    }
  }
  else
  {
    /* Nothing to do */
  }

  return returnValue;
}

#if (STD_OFF == CANTRCV_SUPPORT_AR403)
/*******************************************************************************
** Function Name      : CanTrcv_XJA11XXSetCanMode                             **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to set CAN mode for XJA11XX device.     **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                      canMode     - Can mode.                               **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Set CAN mode successful.                        **
**                      E_NOT_OK: Set CAN mode not successful.                **
**                                                                            **
** Preconditions      : CANTRCV_XJA11XX_SUPPORTED == STD_ON                   **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_ReadReg, CanTrcv_WriteReg**
*******************************************************************************/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXSetCanMode(
  CONST(uint8, AUTOMATIC) transceiver,
  CONST(XJA11XX_CanModeType, AUTOMATIC) canMode)
{
  VAR(uint8, AUTOMATIC) data;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Initialize local variable */
  data = (uint8)CANTRCV_ZERO;

  /* @Trace: CanTrcv_SUD_API_134 */
  /* Read value in CAN control register */
  returnValue = ptrWriteReadReg->ReadReg(transceiver, XJA11XX_CAN_CONTROL_REG, &data);
  if (E_NOT_OK != returnValue)
  {
    /* Set Can Mode - Bit CMC */
    data &= XJA11XX_CMC_CLEAR;
    data |= (uint8)canMode;
    returnValue = ptrWriteReadReg->WriteReg(transceiver, XJA11XX_CAN_CONTROL_REG,
      data);
  }
  else
  {
    /* Nothing to do */
  }

  return returnValue;
}
#endif /*(STD_OFF == CANTRCV_SUPPORT_AR403)*/
/*******************************************************************************
** Function Name      : CanTrcv_XJA11XXInit                                   **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to initialize XJA11XX device.           **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                      ptrCanTrcvNetwork - Pointer to the configuration      **
**                                           structure.                       **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: The initialization is successful.               **
**                      E_NOT_OK: The initialization is not successful.       **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_XJA11XX_SUPPORTED                   **
**                                                                            **
** Remarks            : Global variable(s): CanTrcv_WakeUpReason              **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      CanTrcv_XJA11XXSetModeControl,                        **
**                      CanTrcv_ReadReg,                                      **
**                      CanTrcv_WriteReg,                                     **
**                      EcuM_SetWakeupEvent                                   **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00180 SWS_CanTrcv_00167
  SWS_CanTrcv_00086
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXInit(
  CONST(uint8, AUTOMATIC) transceiver,
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork)
{
  VAR(uint8, AUTOMATIC) data;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];

  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  /* Initialize local variables */
  data = (uint8)CANTRCV_ZERO;

  #if (STD_OFF == CANTRCV_WAKEUP_SUPPORTED)
  /* Avoid compiler warning */
  CANTRCV_UNUSED_VAL(ptrCanTrcvNetwork);
  #endif

  /* @Trace: CanTrcv_SUD_API_017 */
  /* Unlock register */
  returnValue = CanTrcv_XJA11XXSetLockControl(transceiver, XJA11XX_UNLOCK_REG);

  /* Clear all event sources */
  if (E_NOT_OK != returnValue)
  {
    returnValue = CanTrcv_XJA11XXInit_ClearEventSrc(transceiver, ptrCanTrcvNetwork, &data);
  }
  else
  {
    /* Nothing to do */
  }

  #if (STD_ON == CANTRCV_WAKEUP_SUPPORTED)
  /* Configure WAKE pin event capture enable register */
  if (E_NOT_OK != returnValue)
  {
    /* @Trace: CanTrcv_SUD_API_022 */
    if (CANTRCV_NEGATIVE_EDGE == ptrCanTrcvNetwork->LocalWakeupDirection)
    {
      /* Falling-edge detection on WAKE pin enabled */
      returnValue = ptrWriteReadReg->WriteReg(transceiver,
        XJA11XX_WAKE_PIN_EVENT_CAPTURE_REG, XJA11XX_WPFE_ENABLE);
    }
    else
    {
      /* Rising-edge detection on WAKE pin enabled */
      returnValue = ptrWriteReadReg->WriteReg(transceiver,
        XJA11XX_WAKE_PIN_EVENT_CAPTURE_REG, XJA11XX_WPRE_ENABLE);
    }
  }
  else
  {
    /* Nothing to do */
  }

  /* Configure Transceiver event capture enable register */
  if (E_NOT_OK != returnValue)
  {
    /* @Trace: CanTrcv_SUD_API_023 */
    /* Read value of Transceiver event capture enable register */
    returnValue = ptrWriteReadReg->ReadReg(transceiver,
      XJA11XX_TRCV_EVENT_CAPTURE_ENABLE_REG, &data);
    if (E_NOT_OK != returnValue)
    {
      /* Enable CAN wake-up */
      data |= XJA11XX_CWE_ENABLE;
      /* Send request via SPI */
      returnValue = ptrWriteReadReg->WriteReg(transceiver,
        XJA11XX_TRCV_EVENT_CAPTURE_ENABLE_REG, data);
    }
    else
    {
      /* Nothing to do */
    }
  }
  else
  {
    /* Nothing to do */
  }
  #endif /* (STD_ON == CANTRCV_WAKEUP_SUPPORTED) */

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_XJA11XXDeInit                                 **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to deinitialize XJA11XX device.         **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: The deinitialization is successful.             **
**                      E_NOT_OK: The deinitialization is not successful.     **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_XJA11XX_SUPPORTED                   **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_XJA11XXSetLockControl,   **
**                      CanTrcv_XJA11XXResetDataMask, CanTrcv_WriteReg,       **
**                      CanTrcv_XJA11XXResetIdentifierType                    **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_91002 SRS_Can_01108
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXDeInit(
  CONST(uint8, AUTOMATIC) transceiver)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* @Trace: CanTrcv_SUD_API_148 */
  /* Configure System event capture enable register */
  returnValue = ptrWriteReadReg->WriteReg(transceiver, XJA11XX_SYSTEM_EVENT_CAPTURE_REG,
    XJA11XX_SYSTEM_EVENT_CAPTURE_DEFAULT_VALUE);

  /* Configure General-purpose memory as CANTRCV_ZERO */
  returnValue |= CanTrcv_XJA11XXResetMemory(transceiver);

  /* Configure default value for Transceiver event capture register */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver,
    XJA11XX_TRCV_EVENT_CAPTURE_ENABLE_REG,
    XJA11XX_TRCV_EVENT_CAPTURE_ENABLE_DEFAULT_VALUE);

  /* Disable WAKE pin event capture enable register */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver,
    XJA11XX_WAKE_PIN_EVENT_CAPTURE_REG,
    XJA11XX_WAKE_PIN_EVENT_CAPTURE_DEFAULT_VALUE);

  #if (STD_ON == CANTRCV_HW_PN_SUPPORTED)
  /* Configure default value for Configure CAN control register */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, XJA11XX_CAN_CONTROL_REG,
    XJA11XX_CAN_CONTROL_REG_DEFAULT_VALUE);

  /* Configure default value for Configure Data rate register */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, XJA11XX_DATA_RATE_REG,
    XJA11XX_DATA_RATE_DEFAULT_VALUE);

  /* Configure ID and TD Mask registers */
  returnValue |= CanTrcv_XJA11XXResetIdentifierType(transceiver);

  /* Configure default value for Frame control register */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, XJA11XX_FRAME_CONTROL_REG,
    XJA11XX_FRAME_CONTROL_DEFAULT_VALUE);

    /* Configure default value for Configure Data mask */
    returnValue |= CanTrcv_XJA11XXResetDataMask(transceiver);
  #endif /* (STD_ON == CANTRCV_HW_PN_SUPPORTED) */

  if (E_NOT_OK != returnValue)
  {
    /* Lock register */
    returnValue = CanTrcv_XJA11XXSetLockControl(transceiver, XJA11XX_LOCK_REG);
  }
  else
  {
    /* Nothing to do */
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_XJA11XXResetMemory                            **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to reset Memory on XJA11XX device.      **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Reset Memory is successful.                     **
**                      E_NOT_OK: Reset Memory is not successful.             **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_XJA11XX_SUPPORTED                   **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_WriteReg                 **
*******************************************************************************/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXResetMemory(
  CONST(uint8, AUTOMATIC) transceiver)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* @Trace: CanTrcv_SUD_API_149 */
  /* Configure memory 0 as CANTRCV_ZERO */
  returnValue = ptrWriteReadReg->WriteReg(transceiver, XJA11XX_MEMORY_0_REG,
    (uint8)CANTRCV_ZERO);

  /* Configure memory 1 as CANTRCV_ZERO */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, XJA11XX_MEMORY_1_REG,
    (uint8)CANTRCV_ZERO);

  /* Configure memory 2 as CANTRCV_ZERO */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, XJA11XX_MEMORY_2_REG,
    (uint8)CANTRCV_ZERO);

  /* Configure memory 3 as CANTRCV_ZERO */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, XJA11XX_MEMORY_3_REG,
    (uint8)CANTRCV_ZERO);

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_XJA11XXSetLockControl                         **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to set lock control register on XJA11XX **
**                      device.                                               **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                      lockType - XJA11XX_UNLOCK_REG: Unlock register.       **
**                                 XJA11XX_LOCK_REG: Lock register.           **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Lock/Unlock register successful.                **
**                      E_NOT_OK: Lock/Unlock register is not successful.     **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_XJA11XX_SUPPORTED                   **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_WriteReg                 **
*******************************************************************************/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXSetLockControl(
  CONST(uint8, AUTOMATIC) transceiver,
  CONST(XJA11XX_LockCtrlType, AUTOMATIC) lockType)
{
  VAR(uint8, AUTOMATIC) data;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Initialize local variable */
  data = (uint8)CANTRCV_ZERO;

  if (XJA11XX_UNLOCK_REG == lockType)
  {
    /* @Trace: CanTrcv_SUD_API_093 */
    /* Unlock register */
    /* LK6C Bit */
    data |= (uint8)(XJA11XX_LOCK_CONTROL_ENABLE << XJA11XX_LK6C_SHIFT);
    /* LK5C Bit */
    data |= (uint8)(XJA11XX_LOCK_CONTROL_DISABLE << XJA11XX_LK5C_SHIFT);
    /* LK4C Bit */
    data |= (uint8)(XJA11XX_LOCK_CONTROL_ENABLE << XJA11XX_LK4C_SHIFT);
    /* LK3C Bit */
    data |= (uint8)(XJA11XX_LOCK_CONTROL_DISABLE << XJA11XX_LK3C_SHIFT);
    /* LK2C Bit */
    data |= (uint8)(XJA11XX_LOCK_CONTROL_ENABLE << XJA11XX_LK2C_SHIFT);
    /* LK1C Bit */
    data |= (uint8)(XJA11XX_LOCK_CONTROL_DISABLE << XJA11XX_LK1C_SHIFT);
    /* LK0C Bit */
    data |= (uint8)(XJA11XX_LOCK_CONTROL_ENABLE);
  }
  else
  {
    /* @Trace: CanTrcv_SUD_API_094 */
    /* Lock register */
    /* LK6C Bit */
    data |= (uint8)(XJA11XX_LOCK_CONTROL_DISABLE << XJA11XX_LK6C_SHIFT);
    /* LK5C Bit */
    data |= (uint8)(XJA11XX_LOCK_CONTROL_DISABLE << XJA11XX_LK5C_SHIFT);
    /* LK4C Bit */
    data |= (uint8)(XJA11XX_LOCK_CONTROL_DISABLE << XJA11XX_LK4C_SHIFT);
    /* LK3C Bit */
    data |= (uint8)(XJA11XX_LOCK_CONTROL_DISABLE << XJA11XX_LK3C_SHIFT);
    /* LK2C Bit */
    data |= (uint8)(XJA11XX_LOCK_CONTROL_DISABLE << XJA11XX_LK2C_SHIFT);
    /* LK1C Bit */
    data |= (uint8)(XJA11XX_LOCK_CONTROL_DISABLE << XJA11XX_LK1C_SHIFT);
    /* LK0C Bit */
    data |= (uint8)(XJA11XX_LOCK_CONTROL_DISABLE);
  }

  /* @Trace: CanTrcv_SUD_API_095 */
  /* Send request via SPI */
  returnValue = ptrWriteReadReg->WriteReg(transceiver, XJA11XX_LOCK_CONTROL_REG, data);

  return returnValue;
}

#if (STD_ON == CANTRCV_HW_PN_SUPPORTED)
#if (STD_ON == CANTRCV_HW_POR_SUPPORTED)
/*******************************************************************************
** Function Name      : CanTrcv_XJA11XXGetPorFlag                             **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to get status of POR flag on XJA11XX    **
**                      device.                                               **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : ptrPorFlag - Store status of POR flag.                **
**                                                                            **
** Return parameter   : E_OK: Get status of POR flag successful.              **
**                      E_NOT_OK: Get status of POR flag is not successful.   **
**                                                                            **
** Preconditions      : CANTRCV_XJA11XX_SUPPORTED == STD_ON                   **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_ReadReg                  **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00181 SWS_CanTrcv_00186
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXGetPorFlag(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(uint8, AUTOMATIC, CANTRCV_APPL_DATA) ptrPorFlag)
{
  VAR(uint8, AUTOMATIC) data;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Initialize local variable */
  data = (uint8)CANTRCV_ZERO;

  /* @Trace: CanTrcv_SUD_API_048 */
  /* Read value in System event status register */
  returnValue = ptrWriteReadReg->ReadReg(transceiver, XJA11XX_SYSTEM_EVENT_STATUS_REG,
    &data);
  if (E_NOT_OK != returnValue)
  {
    /* Get status of PO flag - bit 4 */
    *ptrPorFlag = (boolean)((data & XJA11XX_PO_MASK) >> CANTRCV_FOUR);
  }
  else
  {
    /* Nothing to do */
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_XJA11XXClearPorFlag                           **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to clear POR flag on XJA11XX device.    **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Clear POR flag is successful.                   **
**                      E_NOT_OK: Clear POR flag is not successful.           **
**                                                                            **
** Preconditions      : CANTRCV_XJA11XX_SUPPORTED == STD_ON                   **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_WriteReg                 **
*******************************************************************************/
/* @Trace_CanTrcv_00181
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXClearPorFlag(
  CONST(uint8, AUTOMATIC) transceiver)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* @Trace: CanTrcv_SUD_API_052 */
  /* Clear PO flag - bit 4 */
  returnValue = ptrWriteReadReg->WriteReg(transceiver, XJA11XX_SYSTEM_EVENT_STATUS_REG,
    XJA11XX_PO_MASK);

  return returnValue;
}
#endif /* (STD_ON == CANTRCV_HW_POR_SUPPORTED) */

/*******************************************************************************
** Function Name      : CanTrcv_XJA11XXResetIdentifierType                    **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to reset Identifier Type on             **
**                      XJA11XX device.                                       **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Reset Identifier Type is successful.            **
**                      E_NOT_OK: Reset Identifier Type is not successful.    **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_XJA11XX_SUPPORTED                   **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_WriteReg                 **
*******************************************************************************/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXResetIdentifierType(
  CONST(uint8, AUTOMATIC) transceiver)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* @Trace: CanTrcv_SUD_API_150 */
  /* Configure default value for ID registers */
  /* Configure default value for ID registers 0 */
  returnValue = ptrWriteReadReg->WriteReg(transceiver, XJA11XX_ID_0_REG,
    XJA11XX_ID_X_DEFAULT_VALUE);

  /* Configure default value for ID registers 1 */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, XJA11XX_ID_1_REG,
    XJA11XX_ID_X_DEFAULT_VALUE);

  /* Configure default value for ID registers 2 */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, XJA11XX_ID_2_REG,
    XJA11XX_ID_X_DEFAULT_VALUE);

  /* Configure default value for ID registers 3 */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, XJA11XX_ID_3_REG,
    XJA11XX_ID_X_DEFAULT_VALUE);

  /* Configure default value for ID Mask registers */
  if (E_NOT_OK != returnValue)
  {
    /* @Trace: CanTrcv_SUD_API_151 */
    /* Configure default value for ID Mask registers 0 */
    returnValue = ptrWriteReadReg->WriteReg(transceiver, XJA11XX_ID_MASK_0_REG,
      XJA11XX_ID_MASK_X_DEFAULT_VALUE);

    /* Configure default value for ID Mask registers 1 */
    returnValue |= ptrWriteReadReg->WriteReg(transceiver, XJA11XX_ID_MASK_1_REG,
      XJA11XX_ID_MASK_X_DEFAULT_VALUE);

    /* Configure default value for ID Mask registers 2 */
    returnValue |= ptrWriteReadReg->WriteReg(transceiver, XJA11XX_ID_MASK_2_REG,
      XJA11XX_ID_MASK_X_DEFAULT_VALUE);

    /* Configure default value for ID Mask registers 3 */
    returnValue |= ptrWriteReadReg->WriteReg(transceiver, XJA11XX_ID_MASK_3_REG,
      XJA11XX_ID_MASK_X_DEFAULT_VALUE);
  }
  else
  {
    /* Nothing to do */
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_XJA11XXSetDataMask                            **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function set/reset Data Mask for XJA11XX device. **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                      command     - Request command to set or reset data    **
**                                    mask registers.                         **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: The data mask set/reset is successful.          **
**                      E_NOT_OK: The data mask set/reset is not successful.  **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_XJA11XX_SUPPORTED                   **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_WriteReg                 **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_91002 SRS_Can_01108
*/
/* polyspace -begin MISRA-C3:18.1 [Justified:Low] "The value of  transceiver is already checked before being passed through the function." */
/* polyspace -begin MISRA-C3:D4.1 [Justified:Low] "The value of  transceiver is already checked before being passed through the function." */
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXSetDataMask(
  CONST(uint8, AUTOMATIC) transceiver)
{
  P2CONST(CanTrcv_PartialNetworkType, AUTOMATIC, CANTRCV_CONST)
    ptrCanTrcvPnNetwork;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  VAR(uint8, AUTOMATIC) canTrcvPnIndex;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Get the index of partial network */
  canTrcvPnIndex = CanTrcv_CanTrcvNetwork[transceiver].PnNetworkIndex;
  /* Get the pointer to the structure of the requested partial network */
  ptrCanTrcvPnNetwork = &CanTrcv_PartialNetwork[canTrcvPnIndex];

  /* @Trace: CanTrcv_SUD_API_072 */
  /* Configure CAN Data Byte registers 0 */
  /* polyspace +4 MISRA-C3:18.1 [Justified:Low] "ptrCanTrcvPnNetwork points to an element of CanTrcv_CanTrcvNetwork which is  guaranteed by Generator." */
  /* polyspace +3 MISRA-C3:D4.1 [Justified:Low] "ptrCanTrcvPnNetwork points to an element of CanTrcv_CanTrcvNetwork which is  guaranteed by Generator." */
  /* polyspace +2 RTE:IDP [Justified:Low] "CanTrcv_PartialNetwork is guaranteed by Generator." */
  returnValue = ptrWriteReadReg->WriteReg(transceiver, XJA11XX_DATA_MASK_0_REG,
    ptrCanTrcvPnNetwork->PnFrameMaskSpec->PnFrameDataMask0);

  /* Configure CAN Data Byte registers 1 */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, XJA11XX_DATA_MASK_1_REG,
    ptrCanTrcvPnNetwork->PnFrameMaskSpec->PnFrameDataMask1);

  /* Configure CAN Data Byte registers 2 */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, XJA11XX_DATA_MASK_2_REG,
    ptrCanTrcvPnNetwork->PnFrameMaskSpec->PnFrameDataMask2);

  /* Configure CAN Data Byte registers 3 */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, XJA11XX_DATA_MASK_3_REG,
    ptrCanTrcvPnNetwork->PnFrameMaskSpec->PnFrameDataMask3);

  /* Configure CAN Data Byte registers 4 */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, XJA11XX_DATA_MASK_4_REG,
    ptrCanTrcvPnNetwork->PnFrameMaskSpec->PnFrameDataMask4);

  /* Configure CAN Data Byte registers 5 */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, XJA11XX_DATA_MASK_5_REG,
    ptrCanTrcvPnNetwork->PnFrameMaskSpec->PnFrameDataMask5);

  /* Configure CAN Data Byte registers 6 */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, XJA11XX_DATA_MASK_6_REG,
    ptrCanTrcvPnNetwork->PnFrameMaskSpec->PnFrameDataMask6);

  /* Configure CAN Data Byte registers 7 */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, XJA11XX_DATA_MASK_7_REG,
    ptrCanTrcvPnNetwork->PnFrameMaskSpec->PnFrameDataMask7);

  return returnValue;
}
/* polyspace -end MISRA-C3:18.1 [Justified:Low] "The value of  transceiver is already checked before being passed through the function." */
/* polyspace -end MISRA-C3:D4.1 [Justified:Low] "The value of  transceiver is already checked before being passed through the function." */
/*******************************************************************************
** Function Name      : CanTrcv_XJA11XXResetDataMask                          **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function reset Data Mask for XJA11XX device.     **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                      command     - Request command to set or reset data    **
**                                    mask registers.                         **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: The data mask reset is successful.              **
**                      E_NOT_OK: The data mask reset is not successful.      **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_XJA11XX_SUPPORTED                   **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_WriteReg                 **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_91002 SRS_Can_01108
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXResetDataMask(
  CONST(uint8, AUTOMATIC) transceiver)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Reset CAN Data Byte registers 0 */
  returnValue = ptrWriteReadReg->WriteReg(transceiver, XJA11XX_DATA_MASK_0_REG,
    XJA11XX_DATA_MASK_X_DEFAULT_VALUE);

  /* Reset CAN Data Byte registers 1 */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, XJA11XX_DATA_MASK_1_REG,
    XJA11XX_DATA_MASK_X_DEFAULT_VALUE);

  /* Reset CAN Data Byte registers 2 */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, XJA11XX_DATA_MASK_2_REG,
    XJA11XX_DATA_MASK_X_DEFAULT_VALUE);

  /* Reset CAN Data Byte registers 3 */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, XJA11XX_DATA_MASK_3_REG,
    XJA11XX_DATA_MASK_X_DEFAULT_VALUE);

  /* Reset CAN Data Byte registers 4 */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, XJA11XX_DATA_MASK_4_REG,
    XJA11XX_DATA_MASK_X_DEFAULT_VALUE);

  /* Reset CAN Data Byte registers 5 */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, XJA11XX_DATA_MASK_5_REG,
    XJA11XX_DATA_MASK_X_DEFAULT_VALUE);

  /* Reset CAN Data Byte registers 6 */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, XJA11XX_DATA_MASK_6_REG,
    XJA11XX_DATA_MASK_X_DEFAULT_VALUE);

  /* Reset CAN Data Byte registers 7 */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, XJA11XX_DATA_MASK_7_REG,
    XJA11XX_DATA_MASK_X_DEFAULT_VALUE);

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_XJA11XXGetSyserrFlag                          **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to get status of SYSERR flag on XJA11XX **
**                      device.                                               **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Get status of SYSERR flag is successful.        **
**                      E_NOT_OK: Get status of SYSERR flag is not successful.**
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_XJA11XX_SUPPORTED and               **
**                      STD_ON == CANTRCV_HW_PN_SUPPORTED                     **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_ReadReg                  **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00181 SWS_CanTrcv_00186
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXGetSyserrFlag(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(uint8, AUTOMATIC, CANTRCV_APPL_DATA) ptrSyserrFlag)
{
  VAR(uint8, AUTOMATIC) data;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Initialize local variable */
  data = (uint8)CANTRCV_ZERO;

  /* @Trace: CanTrcv_SUD_API_056 */
  /* Read value in Transceiver event status register */
  returnValue = ptrWriteReadReg->ReadReg(transceiver, XJA11XX_TRCV_EVENT_STATUS_REG,
    &data);
  if (E_NOT_OK != returnValue)
  {
    /* Get PNFDE flag - bit 5 */
    *ptrSyserrFlag = (boolean)((data & XJA11XX_PNFDE_MASK) >> CANTRCV_FIVE);
  }
  else
  {
    /* Nothing to do */
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_XJA11XXClearSyserrFlag                        **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to clear status of SYSERR flag on       **
**                      XJA11XX device.                                       **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Clear status of SYSERR flag successful.         **
**                      E_NOT_OK: Clear status of SYSERR flag not successful. **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_XJA11XX_SUPPORTED and               **
**                      STD_ON == CANTRCV_HW_PN_SUPPORTED                     **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_ReadReg                  **
*******************************************************************************/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXClearSyserrFlag(
  CONST(uint8, AUTOMATIC) transceiver)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* @Trace: CanTrcv_SUD_API_059 */
  /* Clear PNFDE flag - bit 5 */
  returnValue = ptrWriteReadReg->WriteReg(transceiver, XJA11XX_TRCV_EVENT_STATUS_REG,
    XJA11XX_PNFDE_MASK);

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_XJA11XXConfigurePartialNetworking             **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to configure partial networking on      **
**                      XJA11XX device.                                       **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Configure partial networking successful.        **
**                      E_NOT_OK: Configure partial networking not successful.**
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_XJA11XX_SUPPORTED and               **
**                      STD_ON == CANTRCV_HW_PN_SUPPORTED                     **
**                                                                            **
** Remarks            : Global variable(s): CanTrcv_CanTrcvNetwork            **
**                                                                            **
**                      Function(s) invoked: CanTrcv_WriteReg,                **
**                      CanTrcv_ReadReg, CanTrcv_XJA11XXSetDataMask,          **
**                      CanTrcv_XJA11XXConfigureIdentifierType,               **
**                      CanTrcv_XJA11XXSetPNActivationState                   **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00182 SWS_CanTrcv_00210
*/
static FUNC(Std_ReturnType, CANTRCV_CODE)
  CanTrcv_XJA11XXConfigurePartialNetworking(
    CONST(uint8, AUTOMATIC) transceiver)
{
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  P2CONST(CanTrcv_PartialNetworkType, AUTOMATIC, CANTRCV_CONST)
    ptrCanTrcvPnNetwork;
  VAR(uint8, AUTOMATIC) data;
  VAR(uint8, AUTOMATIC) pnIndex;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];
  /* Get Parital Network index */
  pnIndex = ptrCanTrcvNetwork->PnNetworkIndex;
  /* Get the pointer to the structure of the requested PN network */
  ptrCanTrcvPnNetwork = &CanTrcv_PartialNetwork[pnIndex];

  /* @Trace: CanTrcv_SUD_API_062 */
  /* Configure data rate */
  /* polyspace +4 MISRA-C3:18.1 [Justified:Low] "ptrCanTrcvPnNetwork points to an element of CanTrcv_CanTrcvNetwork which is  guaranteed by Generator." */
  /* polyspace +3 MISRA-C3:D4.1 [Justified:Low] "ptrCanTrcvPnNetwork points to an element of CanTrcv_CanTrcvNetwork which is  guaranteed by Generator." */
  /* polyspace +2 RTE:IDP [Justified:Low] "CanTrcv_PartialNetwork is guaranteed by Generator." */
  returnValue = ptrWriteReadReg->WriteReg(transceiver, XJA11XX_DATA_RATE_REG,
    ptrCanTrcvPnNetwork->BaudRate);


  /* Configure identifier format and number of data bytes */
  data = (uint8)CANTRCV_ZERO;
  /* Configure identifier format */
  data |= (uint8)(ptrCanTrcvPnNetwork->PnCanIdIsExtended <<
    XJA11XX_IDE_SHIFT);
  /* Configure partial networking data mask */
  data |= ptrCanTrcvPnNetwork->PnDlcMatchingCondition;
  /* Configure data length code */
  data |= ptrCanTrcvPnNetwork->PnFrameDlc;

  /* @Trace: CanTrcv_SUD_API_063 */
  /* Send request via SPI */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, XJA11XX_FRAME_CONTROL_REG, data);

  /* @Trace: CanTrcv_SUD_API_064 */
  /* Configure CAN ID and ID mask */
  returnValue |= CanTrcv_XJA11XXConfigureIdentifierType(transceiver);

  /* @Trace: CanTrcv_SUD_API_065 */
  /* Configure CAN Data Byte registers */
  returnValue |= CanTrcv_XJA11XXSetDataMask(transceiver);

  /* @Trace: CanTrcv_SUD_API_066 */
  /* Read value in CAN control register */
  returnValue |= ptrWriteReadReg->ReadReg(transceiver, XJA11XX_CAN_CONTROL_REG, &data);

  if (E_NOT_OK != returnValue)
  {
    /* Set PNCOK bit in the CAN Control register to confirm all registers are
      configured correctly */
    data |= XJA11XX_PNCOK_SUCCESSFUL;
    returnValue = ptrWriteReadReg->WriteReg(transceiver, XJA11XX_CAN_CONTROL_REG,
      data);
  }
  else
  {
    /* Nothing to do */
  }

  /* @Trace: CanTrcv_SUD_API_067 */
  /* Configure wake uint */
  /* polyspace +2 MISRA2012:10.5 [Justified:Low] "Operation is guaranteed that does not exceed CanTrcv_PNActivationType." */
  returnValue |= CanTrcv_XJA11XXSetPNActivationState(transceiver,
    (CanTrcv_PNActivationType)ptrCanTrcvPnNetwork->PnEnabled);

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_XJA11XXConfigureIdentifierType                **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to configure Identifier Type on         **
**                      XJA11XX device.                                       **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Configure Identifier Type successful.           **
**                      E_NOT_OK: Configure Identifier Type not successful.   **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_XJA11XX_SUPPORTED and               **
**                      STD_ON == CANTRCV_HW_PN_SUPPORTED                     **
**                                                                            **
** Remarks            : Global variable(s): CanTrcv_CanTrcvNetwork            **
**                                                                            **
**                      Function(s) invoked: CanTrcv_WriteReg                 **
*******************************************************************************/
static FUNC(Std_ReturnType, CANTRCV_CODE)
  CanTrcv_XJA11XXConfigureIdentifierType(CONST(uint8, AUTOMATIC) transceiver)
{
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  P2CONST(CanTrcv_PartialNetworkType, AUTOMATIC, CANTRCV_CONST)
    ptrCanTrcvPnNetwork;
  VAR(uint8, AUTOMATIC) data;
  VAR(uint8, AUTOMATIC) pnIndex;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];
  /* Get Parital Network index */
  pnIndex = ptrCanTrcvNetwork->PnNetworkIndex;
  /* Get the pointer to the structure of the requested PN network */
  ptrCanTrcvPnNetwork = &CanTrcv_PartialNetwork[pnIndex];
  /* polyspace -begin MISRA-C3:D4.1 [Justified:Low] "ptrCanTrcvPnNetwork points to an element of CanTrcv_CanTrcvNetwork which is  guaranteed by Generator." */
  /* polyspace +4 MISRA-C3:D4.1 [Justified:Low] "The size of CanTrcv_PartialNetwork is pre-defined, the value of pnIndex is already guaranteed.
   * So, ptrCanTrcvPnNetwork is valid in this case." */
  /* polyspace +2 MISRA-C3:18.1 [Justified:Low] "ptrCanTrcvPnNetwork points to an element of CanTrcv_CanTrcvNetwork which is  guaranteed by Generator." */
  /* polyspace +1 RTE:IDP [Justified:Low] "CanTrcv_PartialNetwork is guaranteed by Generator." */
  if (CANTRCV_TRUE != ptrCanTrcvPnNetwork->PnCanIdIsExtended)
  {
    /* @Trace: CanTrcv_SUD_API_068 */
    /* Bits ID5 to ID0 of the standard frame format */
    data = (uint8)((ptrCanTrcvPnNetwork->PnFrameCanId &
      XJA11XX_ID5_ID0_MASK) << XJA11XX_ID5_ID0_SHIFT);
    returnValue = ptrWriteReadReg->WriteReg(transceiver, XJA11XX_ID_2_REG, data);

    /* Bits ID10 to ID6 of the standard frame format */
    data = (uint8)((ptrCanTrcvPnNetwork->PnFrameCanId &
      XJA11XX_ID10_ID6_MASK) >> CANTRCV_SIX);
    returnValue |= ptrWriteReadReg->WriteReg(transceiver, XJA11XX_ID_3_REG, data);

    /* @Trace: CanTrcv_SUD_API_069 */
    if (E_NOT_OK != returnValue)
    {
      /* ID mask bits 5 to 0 of standard frame format */
      data = (uint8)((ptrCanTrcvPnNetwork->PnFrameCanIdMask &
        XJA11XX_M5_M0_MASK) << XJA11XX_M5_M0_SHIFT);
      returnValue = ptrWriteReadReg->WriteReg(transceiver, XJA11XX_ID_MASK_2_REG,
        data);

      /* ID mask bits 10 to 6 of standard frame format */
      data = (uint8)((ptrCanTrcvPnNetwork->PnFrameCanIdMask &
        XJA11XX_M10_M6_MASK) >> CANTRCV_SIX);
      returnValue |= ptrWriteReadReg->WriteReg(transceiver, XJA11XX_ID_MASK_3_REG,
        data);
    }
    else
    {
      /* Nothing to do */
    }
  }
  /* polyspace -end MISRA-C3:D4.1 [Justified:Low] "ptrCanTrcvPnNetwork points to an element of CanTrcv_CanTrcvNetwork which is  guaranteed by Generator." */
  else
  {
    /* @Trace: CanTrcv_SUD_API_070 */
    /* Bits ID7 to ID0 of the extended frame format */
    data = (uint8)(ptrCanTrcvPnNetwork->PnFrameCanId &
      XJA11XX_ID7_ID0_MASK);
    returnValue = ptrWriteReadReg->WriteReg(transceiver, XJA11XX_ID_0_REG, data);

    /* Bits ID15 to ID8 of the extended frame format */
    data = (uint8)((ptrCanTrcvPnNetwork->PnFrameCanId &
      XJA11XX_ID15_ID8_MASK) >> CANTRCV_EIGHT);
    returnValue |= ptrWriteReadReg->WriteReg(transceiver, XJA11XX_ID_1_REG, data);

    /* Bits ID23 to ID16 of the extended frame format */
    data = (uint8)((ptrCanTrcvPnNetwork->PnFrameCanId &
      XJA11XX_ID23_ID16_MASK) >> CANTRCV_SIXTEEN);
    returnValue |= ptrWriteReadReg->WriteReg(transceiver, XJA11XX_ID_2_REG, data);

    /* Bits ID28 to ID24 of the extended frame format */
    data = (uint8)((ptrCanTrcvPnNetwork->PnFrameCanId &
      XJA11XX_ID28_ID24_MASK) >> CANTRCV_TWENTYFOUR);
    returnValue |= ptrWriteReadReg->WriteReg(transceiver, XJA11XX_ID_3_REG, data);

    /* @Trace: CanTrcv_SUD_API_071 */
    if (E_NOT_OK != returnValue)
    {
      /* Bits ID mask bits 7 to 0 of extended frame format */
      data = (uint8)(ptrCanTrcvPnNetwork->PnFrameCanIdMask &
        XJA11XX_M7_M0_MASK);
      returnValue = ptrWriteReadReg->WriteReg(transceiver, XJA11XX_ID_MASK_0_REG,
        data);

      /* Bits ID mask bits 15 to 8 of extended frame format */
      data = (uint8)((ptrCanTrcvPnNetwork->PnFrameCanIdMask &
        XJA11XX_M15_M8_MASK) >> CANTRCV_EIGHT);
      returnValue |= ptrWriteReadReg->WriteReg(transceiver, XJA11XX_ID_MASK_1_REG,
        data);

      /* Bits ID mask bits 23 to 16 of extended frame format */
      data = (uint8)((ptrCanTrcvPnNetwork->PnFrameCanIdMask &
        XJA11XX_M23_M16_MASK) >> CANTRCV_SIXTEEN);
      returnValue |= ptrWriteReadReg->WriteReg(transceiver, XJA11XX_ID_MASK_2_REG,
        data);

      /* Bits ID mask bits 28 to 24 of extended frame format */
      data = (uint8)((ptrCanTrcvPnNetwork->PnFrameCanIdMask &
        XJA11XX_M28_M24_MASK) >> CANTRCV_TWENTYFOUR);
      returnValue |= ptrWriteReadReg->WriteReg(transceiver, XJA11XX_ID_MASK_3_REG,
        data);
    }
    else
    {
      /* Nothing to do */
    }
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_XJA11XXGetTrcvSystemData                      **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to get system data on XJA11XX device.   **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : ptrSystemData - Store system data of XJA11XX device.  **
**                                                                            **
** Return parameter   : E_OK: Get system data is successful.                  **
**                      E_NOT_OK: Get system data is not successful.          **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_XJA11XX_SUPPORTED and               **
**                      STD_ON == CANTRCV_HW_PN_SUPPORTED                     **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_ReadReg                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00189
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXGetTrcvSystemData(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(uint32, AUTOMATIC, CANTRCV_APPL_DATA) ptrSystemData)
{
  VAR(uint8, AUTOMATIC) data;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Initialize local variable */
  data = (uint8)CANTRCV_ZERO;

  /* @Trace: CanTrcv_SUD_API_180 */
  /* Read value in Transceiver status register */
  returnValue = ptrWriteReadReg->ReadReg(transceiver, XJA11XX_TRCV_STATUS_REG, &data);
  if (E_NOT_OK != returnValue)
  {
    /* @Trace: CanTrcv_SUD_API_180 */
    /* polyspace +1 MISRA2012:D4.14 [Justified:Low] "Pointer ptrSystemData is checked NULL by DET." */
    *ptrSystemData = (uint32)data;
  }
  else
  {
    /* Nothing to do */
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_XJA11XXReadTrcvTimeoutFlag                    **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to get time out flag on XJA11XX device. **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : ptrFlagState - Store time out flag of XJA11XX device. **
**                                                                            **
** Return parameter   : E_OK: Get time out flag is successful.                **
**                      E_NOT_OK: Get time out flag is not successful.        **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_XJA11XX_SUPPORTED and               **
**                      STD_ON == CANTRCV_HW_PN_SUPPORTED                     **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_ReadReg                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00189 SWS_CanTrcv_00211
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXReadTrcvTimeoutFlag(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(CanTrcv_TrcvFlagStateType, AUTOMATIC, CANTRCV_APPL_DATA) ptrFlagState)
{
  VAR(uint8, AUTOMATIC) data;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Initialize local variable */
  data = (uint8)CANTRCV_ZERO;

  /* @Trace: CanTrcv_SUD_API_197 */
  /* Read value in Transceiver event status register */
  returnValue = ptrWriteReadReg->ReadReg(transceiver, XJA11XX_TRCV_EVENT_STATUS_REG,
    &data);
  if (E_NOT_OK != returnValue)
  {
    /* @Trace: CanTrcv_SUD_API_184 */
    /* Get value of bit CBS - bit 4 */
    /* polyspace +3 MISRA2012:D4.14 [Justified:Low] "Pointer ptrFlagState is checked NULL by DET." */
    /* polyspace +2 MISRA2012:10.5 [Justified:Low] "Operation is guaranteed that does not exceed CanTrcv_TrcvFlagStateType." */
    *ptrFlagState = (CanTrcv_TrcvFlagStateType)(uint8)((uint8)(data &
      XJA11XX_CBS_MASK) >> CANTRCV_FOUR);
  }
  else
  {
    /* Nothing to do */
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_XJA11XXClearTrcvTimeoutFlag                   **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to clear time out flag on XJA11XX       **
**                      device.                                               **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Clear time out flag is successful.              **
**                      E_NOT_OK: Clear time out flag is not successful.      **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_XJA11XX_SUPPORTED and               **
**                      STD_ON == CANTRCV_HW_PN_SUPPORTED                     **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_WriteReg                 **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00216
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXClearTrcvTimeoutFlag(
  CONST(uint8, AUTOMATIC) transceiver)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* @Trace: CanTrcv_SUD_API_190 */
  /* Clear bit CBS - bit 4 */
  returnValue = ptrWriteReadReg->WriteReg(transceiver, XJA11XX_TRCV_EVENT_STATUS_REG,
    XJA11XX_CBS_MASK);

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_XJA11XXReadTrcvSilenceFlag                    **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to read silence flag on XJA11XX         **
**                      device.                                               **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : ptrFlagState - Store state of silence flag.           **
**                                                                            **
** Return parameter   : E_OK: Read status of silence flag is successful.      **
**                      E_NOT_OK: Read silence flag is not successful.        **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_XJA11XX_SUPPORTED and               **
**                      STD_ON == CANTRCV_HW_PN_SUPPORTED                     **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_ReadReg                  **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00217 SWS_CanTrcv_00211
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXReadTrcvSilenceFlag(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(CanTrcv_TrcvFlagStateType, AUTOMATIC, CANTRCV_APPL_DATA) ptrFlagState)
{
  VAR(uint8, AUTOMATIC) data;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Initialize local variable */
  data = (uint8)CANTRCV_ZERO;

  /* Read value in Transceiver status register */
  returnValue = ptrWriteReadReg->ReadReg(transceiver, XJA11XX_TRCV_STATUS_REG, &data);
  if (E_NOT_OK != returnValue)
  {
    /* Get value bit CBSS - bit 3 */
    /* polyspace +3 MISRA2012:D4.14 [Justified:Low] "Pointer ptrFlagState is checked NULL by DET." */
    /* polyspace +2 MISRA2012:10.5 [Justified:Low] "Operation is guaranteed that does not exceed CanTrcv_TrcvFlagStateType." */
    *ptrFlagState = (CanTrcv_TrcvFlagStateType)(uint8)(
      (data & XJA11XX_CBSS_MASK) >> CANTRCV_THREE);
  }
  else
  {
    /* Nothing to do */
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_XJA11XXSetPNActivationState                   **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to set state of partial networking on   **
**                      XJA11XX device.                                       **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                      activationState - PN state.
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Set PN state success.                           **
**                      E_NOT_OK: Set PN not success.                         **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_XJA11XX_SUPPORTED and               **
**                      STD_ON == CANTRCV_HW_PN_SUPPORTED                     **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_WriteReg                 **
**                      CanTrcv_ReadReg                                       **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00221 SWS_CanTrcv_00222
  SWS_CanTrcv_00210
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXSetPNActivationState(
  CONST(uint8, AUTOMATIC) transceiver,
  CONST(CanTrcv_PNActivationType, AUTOMATIC) activationState)
{
  VAR(uint8, AUTOMATIC) data;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Initialize local variable */
  data = (uint8)CANTRCV_ZERO;

  /* @Trace: CanTrcv_SUD_API_073 */
  /* Read value in CAN control register */
  returnValue = ptrWriteReadReg->ReadReg(transceiver, XJA11XX_CAN_CONTROL_REG, &data);
  if (E_NOT_OK != returnValue)
  {
    data &= (uint8)(~XJA11XX_CPNC_MASK);
    data |= (uint8)activationState << XJA11XX_CPNC_SHIFT;
    returnValue = ptrWriteReadReg->WriteReg(transceiver, XJA11XX_CAN_CONTROL_REG, data);
  }
  else
  {
    /* Nothing to do */
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_XJA11XXClearTrcvWufFlag                       **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to clear transceiver wake up frame flag **
**                      on XJA11XX device.                                    **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Clear wake up frame flag success.               **
**                      E_NOT_OK: Clear wake up frame flag not success.       **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_XJA11XX_SUPPORTED and               **
**                      STD_ON == CANTRCV_HW_PN_SUPPORTED                     **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_WriteReg                 **
**                      CanTrcv_ReadReg                                       **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00194
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXClearTrcvWufFlag(
  CONST(uint8, AUTOMATIC) transceiver)
{
  VAR(uint8, AUTOMATIC) data;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Initialize local variable */
  data = (uint8)CANTRCV_ZERO;

  /* @Trace: CanTrcv_SUD_API_210 */
  /* Check WUF flag is exits */
  /* Read value in CAN control register */
  returnValue = ptrWriteReadReg->ReadReg(transceiver, XJA11XX_CAN_CONTROL_REG, &data);

  if (E_NOT_OK != returnValue)
  {
    /* Get status of CAN selective wake-up */
    data &= XJA11XX_CPNC_MASK;

    if (XJA11XX_CPNC_MASK == data)
    {
      /* @Trace: CanTrcv_SUD_API_211 */
      /* Read value in Transceiver status register */
      data = (uint8)CANTRCV_ZERO;
      returnValue = ptrWriteReadReg->ReadReg(transceiver, XJA11XX_TRCV_STATUS_REG,
        &data);
      if (E_NOT_OK != returnValue)
      {

          /* Read value in Transceiver event status register */
          data = (uint8)CANTRCV_ZERO;
          returnValue = ptrWriteReadReg->ReadReg(transceiver, XJA11XX_TRCV_EVENT_STATUS_REG,
            &data);
          if (E_NOT_OK != returnValue)
          {
            /* @Trace: CanTrcv_SUD_API_212 */
            /* Clear wake up flag - bit CW */
            returnValue = ptrWriteReadReg->WriteReg(transceiver,
              XJA11XX_TRCV_EVENT_STATUS_REG, XJA11XX_PNFDE_CW_MASK);
          }
          else
          {
            /* Nothing to do */
          }

      }
      else
      {
        /* Nothing to do */
      }
    }
    else
    {
      /* CAN selective wake-up is not enable, so do nothing */
    }
  }
  else
  {
    /* Nothing to do */
  }

  return returnValue;
}
#endif /* (STD_ON == CANTRCV_HW_PN_SUPPORTED) */

#if (STD_ON == CANTRCV_WAKEUP_SUPPORTED)
/*******************************************************************************
** Function Name      : CanTrcv_XJA11XXCheckWakeFlag                          **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to check wake up flag for XJA11XX device**
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN transceiver to which API call has   **
**                                    to be applied.                          **
**                      ptrCanTrcvNetwork - Pointer point to Can Transceiver  **
**                                          configuration.                    **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: The request for checking the wakeup flag has    **
**                            been accepted.                                  **
**                      E_NOT_OK: The request for checking the wakeup flag    **
**                                has not been accepted.                      **
**                                                                            **
** Preconditions      : CANTRCV_XJA11XX_SUPPORTED == STD_ON and               **
**                      CANTRCV_WAKEUP_SUPPORTED == STD_ON                    **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_ReadReg,                 **
**                      CanTrcv_WriteReg, EcuM_SetWakeupEvent                 **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00223 SWS_CanTrcv_00086
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXCheckWakeFlag(
  CONST(uint8, AUTOMATIC) transceiver,
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork)
{
  VAR(uint8, AUTOMATIC) data;
  VAR(uint8, AUTOMATIC) wpeFlag;
  VAR(uint8, AUTOMATIC) cwFlag;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Initialize local variable */
  data = (uint8)CANTRCV_ZERO;

  /* @Trace: CanTrcv_SUD_API_238 */
  /* Read value in Global event status register */
  returnValue = ptrWriteReadReg->ReadReg(transceiver, XJA11XX_GLOBAL_EVENT_STATUS_REG,
    &data);
  if (E_NOT_OK != returnValue)
  {
    /* Get WPE flag - bit 3 */
    wpeFlag = (data & XJA11XX_WPE_MASK);

    /* Check status wake up by pin */
    if (XJA11XX_WPE_MASK == wpeFlag)
    {
      /* @Trace: CanTrcv_SUD_API_239 */
      /* Notify to EcuM wake up source */
      EcuM_SetWakeupEvent(ptrCanTrcvNetwork->WakeupSource);
      /* Clear wake flag */
      returnValue = ptrWriteReadReg->WriteReg(transceiver,
        XJA11XX_WAKE_PIN_EVENT_STATUS_REG,
          (XJA11XX_WPR_MASK | XJA11XX_WPF_MASK));
    }
    else
    {
      /* Nothing to do */
    }
  }
  else
  {
    /* Nothing to do */
  }

  if (E_NOT_OK != returnValue)
  {
    /* @Trace: CanTrcv_SUD_API_240 */
    /* Read value in Transceiver event status register */
    returnValue = ptrWriteReadReg->ReadReg(transceiver, XJA11XX_TRCV_EVENT_STATUS_REG,
      &data);
    if (E_NOT_OK != returnValue)
    {
      /* Get CW flag - bit 0 */
      cwFlag = (data & XJA11XX_CW_MASK);

      /* Check status wake up by bus */
      if (XJA11XX_CW_MASK == cwFlag)
      {
        /* @Trace: CanTrcv_SUD_API_241 */
        /* Notify to EcuM wake up source */
        EcuM_SetWakeupEvent(ptrCanTrcvNetwork->WakeupSource);
      }
      else
      {
        /* Nothing to do */
      }
    }
    else
    {
      /* Nothing to do */
    }
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_XJA11XXMainFunction                           **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to set and perform wake up events on    **
**                      XJA11XX device.                                       **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : CANTRCV_XJA11XX_SUPPORTED == STD_ON and               **
**                      CANTRCV_WAKEUP_SUPPORTED == STD_ON                    **
**                                                                            **
** Remarks            : Global variable(s): CanTrcv_WakeUpReason,             **
**                      CanTrcv_WakeupMode, CanTrcv_WakeupFlagIndication,     **
**                      CanTrcv_WakeupPending                                 **
**                                                                            **
**                      Function(s) invoked: CanTrcv_ReadReg                  **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00112 SRS_BSW_00424
*/
static FUNC(void, CANTRCV_CODE) CanTrcv_XJA11XXMainFunction(
  CONST(uint8, AUTOMATIC) transceiver)
{
  VAR(uint8, AUTOMATIC) data;
  VAR(uint8, AUTOMATIC) wakeFlag;
  VAR(uint8, AUTOMATIC) returnStatus;
  VAR(boolean, AUTOMATIC) syserrFlag;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* @Trace: CanTrcv_SUD_API_222 */
  /* Initialize local variable */
  data = (uint8)CANTRCV_ZERO;
  wakeFlag = (uint8)CANTRCV_ZERO;
  /* Get the pointer to the structure of first network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];

  /* Check wake up by pin */
  /* Read value in Global event status register */
  returnStatus = ptrWriteReadReg->ReadReg(transceiver, XJA11XX_GLOBAL_EVENT_STATUS_REG,
    &data);
  if (E_NOT_OK != returnStatus)
  {
    data &= XJA11XX_WPE_MASK;
    if (XJA11XX_WPE_MASK == data)
    {
      /* @Trace: CanTrcv_SUD_API_223 */
      wakeFlag |= data;
      /* Set wake up reason as CANTRCV_WU_BY_BUS */
      CanTrcv_WakeUpReason[transceiver] = CANTRCV_WU_BY_PIN;
    }
    else
    {
      /* Nothing to do */
    }
  }
  else
  {
    /* Nothing to do */
  }

  /* @Trace: CanTrcv_SUD_API_224 */
  /* Check wake up by bus */
  /* Read value in Transceiver event status register */
  returnStatus = ptrWriteReadReg->ReadReg(transceiver, XJA11XX_TRCV_EVENT_STATUS_REG,
    &data);
  if (E_NOT_OK != returnStatus)
  {
    syserrFlag = (boolean)((data & XJA11XX_PNFDE_MASK) >> CANTRCV_FIVE);
    data &= XJA11XX_CW_MASK;
    if (XJA11XX_CW_MASK == data)
    {
      /* @Trace: CanTrcv_SUD_API_225 */
      wakeFlag |= data;
      /* Set wake up reason as CANTRCV_WU_BY_BUS */
      CanTrcv_WakeUpReason[transceiver] = CANTRCV_WU_BY_BUS;
    }
    else if (syserrFlag == CANTRCV_TRUE)
    {
      #if (STD_ON == CANTRCV_WAKEUP_SUPPORTED)
      /* Set wake up reason */
      CanTrcv_WakeUpReason[transceiver] = CANTRCV_WU_BY_SYSERR;
      #endif /* (STD_ON == CANTRCV_WAKEUP_SUPPORTED) */
      /* If the SYSERR flag is set, wakeup shall be reported to EcuM
        through API EcuM_SetWakeupEvent */
        /*#44737*/
      #if(STD_ON == CANTRCV_HW_PN_SUPPORTED)
      EcuM_SetWakeupEvent(ptrCanTrcvNetwork->SyserrWakeupSource);

      /* Clear SYSERR flag */
      (void)CanTrcv_IntClearSyserrFlag(transceiver);
      #endif
    }
    else 
    {
      /* Nothing to do */
    }
  }
  else
  {
    CANTRCV_UNUSED_VAL(syserrFlag);
  }

  if ((uint8)CANTRCV_ZERO != wakeFlag)
  {
    /* Check state wake up of CAN Transceiver */
    if (CANTRCV_WUMODE_ENABLE == CanTrcv_WakeupMode[transceiver])
    {
      /* @Trace: CanTrcv_SUD_API_226 */
      /* Set wake up status */
      CanTrcv_WakeupFlagIndication[transceiver] = CANTRCV_WAKE_UP_OCCURRED;
    }
    else if (CANTRCV_WUMODE_DISABLE == CanTrcv_WakeupMode[transceiver])
    {
      /* @Trace: CanTrcv_SUD_API_227 */
      /* Store the pending wakeup event */
      CanTrcv_WakeupPending[transceiver] = CANTRCV_WAKEUP_PENDING;
    }
    else
    {
      /* Nothing to do */
    }
  }
  else
  {
    /* Nothing to do */
  }
}
#endif /* (STD_ON == CANTRCV_WAKEUP_SUPPORTED) */

#endif /* (STD_ON == CANTRCV_XJA11XX_SUPPORTED) */

/* Functions for TLE9255W device */
#if (STD_ON == CANTRCV_TLE9255W_SUPPORTED)

/*******************************************************************************
** Function Name      : CanTrcv_TLE9255WSetModeControl                        **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to set mode control for TLE9255W device.**
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                      mode - Mode control will be set.                      **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Set mode control success.                       **
**                      E_NOT_OK: Set mode control not success.               **
**                                                                            **
** Preconditions      : CANTRCV_TLE9255W_SUPPORTED == STD_ON                  **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_WriteReg                 **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00102
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TLE9255WSetModeControl(
  CONST(uint8, AUTOMATIC) transceiver,
  CONST(TLE9255W_ModeControlType, AUTOMATIC) mode)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* @Trace: CanTrcv_SUD_API_140 */
  /* Set Mode Control - bit Mode */
  returnValue = ptrWriteReadReg->WriteReg(transceiver, TLE9255W_MODE_CTRL_REG,
   (uint8)mode);

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_TLE9255WGetModeControl                        **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to get current mode control of TLE9255W **
**                      device.                                               **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : ptrMode - Store mode control.                         **
**                                                                            **
** Return parameter   : E_OK: Get mode control success.                       **
**                      E_NOT_OK: Get mode control not success.               **
**                                                                            **
** Preconditions      : CANTRCV_TLE9255W_SUPPORTED == STD_ON                  **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_ReadReg                  **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00163
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TLE9255WGetModeControl(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(CanTrcv_TrcvModeType, AUTOMATIC, CANTRCV_APPL_DATA) ptrMode)
{
  VAR(uint8, AUTOMATIC) data;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Initialize local variable */
  data = (uint8)CANTRCV_ZERO;

  /* @Trace: CanTrcv_SUD_API_135 */
  /* Read value in Mode Control Register */
  returnValue = ptrWriteReadReg->ReadReg(transceiver, TLE9255W_MODE_CTRL_REG, &data);
  if (E_NOT_OK != returnValue)
  {
    data &= TLE9255W_MODE_MASK;
    if ((uint32)TLE9255W_NORMAL_MODE == data)
    {
      /* @Trace: CanTrcv_SUD_API_136 */
      *ptrMode = CANTRCV_TRCVMODE_NORMAL;
    }
    else if ((uint32)TLE9255W_STANDBY_MODE == data)
    {
      /* @Trace: CanTrcv_SUD_API_137 */
      *ptrMode = CANTRCV_TRCVMODE_STANDBY;
    }
    else if ((uint32)TLE9255W_SLEEP_MODE == data)
    {
      /* @Trace: CanTrcv_SUD_API_138 */
      *ptrMode = CANTRCV_TRCVMODE_SLEEP;
    }
    else
    {
      /* @Trace: CanTrcv_SUD_API_139 */
      /* Set return value as E_NOT_OK */
      returnValue = E_NOT_OK;
    }
  }
  else
  {
    /* Nothing to do */
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_TLE9255WInit                                  **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to initialize for TLE9255 device.       **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                      ptrCanTrcvNetwork - Pointer to the configuration      **
**                                          structure.                        **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Initialize successful.                          **
**                      E_NOT_OK: Initialize not successful.                  **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_TLE9255W_SUPPORTED                  **
**                                                                            **
** Remarks            : Global variable(s): CanTrcv_WakeUpReason              **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      CanTrcv_ReadReg,                                      **
**                      CanTrcv_WriteReg,                                     **
**                      EcuM_SetWakeupEvent                                   **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00180 SWS_CanTrcv_00167
  SWS_CanTrcv_00086
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TLE9255WInit(
  CONST(uint8, AUTOMATIC) transceiver,
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork)
{
  VAR(uint8, AUTOMATIC) data;
  VAR(uint8, AUTOMATIC) lwuFlag;
  VAR(uint8, AUTOMATIC) wupFlag;
  VAR(uint8, AUTOMATIC) wufFlag;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Initialize local variables */
  returnValue = E_OK;
  data = (uint8)CANTRCV_ZERO;

  #if (STD_OFF == CANTRCV_WAKEUP_SUPPORTED)
  /* Avoid compiler warning */
  CANTRCV_UNUSED_VAL(ptrCanTrcvNetwork);
  #endif

  #if (STD_ON == CANTRCV_WAKEUP_SUPPORTED)
  /* @Trace: CanTrcv_SUD_API_024 */
  /* Configure Local wake-up direction */
  /* Read value of Hardware Control register */
  returnValue |= ptrWriteReadReg->ReadReg(transceiver, TLE9255W_HW_CTRL_REG, &data);
  if (E_NOT_OK != returnValue)
  {
    if (CANTRCV_NEGATIVE_EDGE == ptrCanTrcvNetwork->LocalWakeupDirection)
    {
      data &= (~TLE9255W_LWU_POS_PERFORMED);
      data |= TLE9255W_LWU_NEG_PERFORMED;
    }
    else
    {
      data &= (~TLE9255W_LWU_NEG_PERFORMED);
      data |= TLE9255W_LWU_POS_PERFORMED;
    }
      /* Local wake-up will be performed on the positive/negative edge */
      returnValue = ptrWriteReadReg->WriteReg(transceiver, TLE9255W_HW_CTRL_REG, data);
  }
  else
  {
    /* Nothing to do */
  }
  #endif /* (STD_ON == CANTRCV_WAKEUP_SUPPORTED) */

  #if (STD_ON == CANTRCV_WAKEUP_SUPPORTED)
  if (E_NOT_OK != returnValue)
  #endif /* (STD_ON == CANTRCV_WAKEUP_SUPPORTED) */
  {
    /* @Trace: CanTrcv_SUD_API_025 */
    /* Read value in Wake Status */
    returnValue = ptrWriteReadReg->ReadReg(transceiver, TLE9255W_WAKE_STAT_REG, &data);

    if (E_NOT_OK != returnValue)
    {
      /* Get LWU - bit 2 */
      lwuFlag = (data & TLE9255W_LWU_MASK);
      /* Get WUP - bit 1 */
      wupFlag = (data & TLE9255W_WUP_MASK);
      /* Get WUF - bit 0 */
      wufFlag = (data & TLE9255W_WUF_MASK);

      /* Check Local Wake-Up status */
      if (TLE9255W_LWU_MASK == lwuFlag)
      {
        /* @Trace: CanTrcv_SUD_API_026 */
        #if (STD_ON == CANTRCV_WAKEUP_SUPPORTED)
        /* Set wake up reason */
        CanTrcv_WakeUpReason[transceiver] = CANTRCV_WU_BY_PIN;
        /* Report wake up source to EcuM */
        EcuM_SetWakeupEvent(ptrCanTrcvNetwork->WakeupSource);
        #endif /* (STD_ON == CANTRCV_WAKEUP_SUPPORTED) */

        /* Clear LWU flag */
        returnValue = ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_STAT_REG,
          TLE9255W_LWU_MASK);
      }
      else
      {
        /* Nothing to do */
      }

      /* Check Wake-Up Pattern status */
      if (TLE9255W_WUP_MASK == wupFlag)
      {
        /* @Trace: CanTrcv_SUD_API_027 */
        #if (STD_ON == CANTRCV_WAKEUP_SUPPORTED)
        /* Set wake up reason */
        CanTrcv_WakeUpReason[transceiver] = CANTRCV_WU_BY_BUS;
        /* Report wake up source to EcuM */
        EcuM_SetWakeupEvent(ptrCanTrcvNetwork->WakeupSource);
        #endif /* (STD_ON == CANTRCV_WAKEUP_SUPPORTED) */

        /* Clear WUP flag */
        returnValue = ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_STAT_REG,
          TLE9255W_WUP_MASK);
      }
      else
      {
        /* Nothing to do */
      }

      /* Check Wake-Up Frame status */
      if (TLE9255W_WUF_MASK == wufFlag)
      {

        #if (STD_ON == CANTRCV_WAKEUP_SUPPORTED)
        /* Set wake up reason */
        CanTrcv_WakeUpReason[transceiver] = CANTRCV_WU_BY_BUS;
        /* Report wake up source to EcuM */
        EcuM_SetWakeupEvent(ptrCanTrcvNetwork->WakeupSource);
        #endif /* (STD_ON == CANTRCV_WAKEUP_SUPPORTED) */

        /* Clear WUF flag */
        returnValue = ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_STAT_REG,
          TLE9255W_WUF_MASK);
      }
      else
      {
        /* Nothing to do */
      }
    }
    else
    {
      /* Nothing to do */
    }
  }
  #if (STD_ON == CANTRCV_WAKEUP_SUPPORTED)
  else
  {
    /* Nothing to do */
  }
  #endif /* (STD_ON == CANTRCV_WAKEUP_SUPPORTED) */

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_TLE9255WDeInit                                **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to de-initialize TLE9255 device.        **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Initialize successful.                          **
**                      E_NOT_OK: Initialize not successful.                  **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_TLE9255W_SUPPORTED                  **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      CanTrcv_TLE9255WResetIdentifierType,                  **
**                      CanTrcv_TLE9255WResetDataControl,                     **
**                      CanTrcv_WriteReg                                      **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_91002 SRS_Can_01108
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TLE9255WDeInit(
  CONST(uint8, AUTOMATIC) transceiver)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* @Trace: CanTrcv_SUD_API_152 */
  /* Configure default value for Hardware Control register */
  returnValue = ptrWriteReadReg->WriteReg(transceiver, TLE9255W_HW_CTRL_REG,
    TLE9255W_HW_CTRL_DEFAULT_VALUE);

  /* Configure default value for TXD Timeout Control register */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TLE9255W_TXD_TO_CTRL_REG,
    TLE9255W_TXD_TO_CTRL_DEFAULT_VALUE);

  /* Configure default value for Supply Control register */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SUPPLY_CTRL_REG,
    TLE9255W_SUPPLY_CTRL_DEFAULT_VALUE);

  #if (STD_ON == CANTRCV_HW_PN_SUPPORTED)
  /* Configure default value for Selective Wake Control register */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_CTRL_1_REG,
    TLE9255W_SWK_CTRL_1_DEFAULT_VALUE);

  /* Configure default value for Baudrate Control register */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_CTRL_2_REG,
    TLE9255W_SWK_CTRL_2_DEFAULT_VALUE);

  /* Configure default value for Identifier Control registers */
  returnValue |= CanTrcv_TLE9255WResetIdentifierType(transceiver);

  /* Configure default value for Data Length Code Control register */
  returnValue |= CanTrcv_TLE9255WResetDataControl(transceiver);

  /* Configure default value for Data Control registers */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_DATA7_CTRL_REG,
    TLE9255W_SWK_DATAX_CTRL_DEFAULT_VALUE);
  #endif /* (STD_ON == CANTRCV_HW_PN_SUPPORTED) */

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_TLE9255WResetIdentifierType                   **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to reset Identifier Type on             **
**                      TLE9255 device.                                       **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Reset Identifier Type successful.               **
**                      E_NOT_OK: Reset Identifier Type not successful.       **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_TLE9255W_SUPPORTED                  **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_WriteReg                 **
*******************************************************************************/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TLE9255WResetIdentifierType(
  CONST(uint8, AUTOMATIC) transceiver)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* @Trace: CanTrcv_SUD_API_153 */
  /* Configure default value for Identifier Control registers */
  /* Configure default value for Identifier 3 Control register */
  returnValue = ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_ID3_CTRL_REG,
    TLE9255W_SWK_ID3_CTRL_DEFAULT_VALUE);

  /* Configure default value for Identifier 2 Control register */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_ID2_CTRL_REG,
    TLE9255W_SWK_ID2_CTRL_DEFAULT_VALUE);

  /* Configure default value for Identifier 1 Control register */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_ID1_CTRL_REG,
    TLE9255W_SWK_ID1_CTRL_DEFAULT_VALUE);

  /* Configure default value for Identifier 0 Control register */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_ID0_CTRL_REG,
    TLE9255W_SWK_ID0_CTRL_DEFAULT_VALUE);

  /* Configure default value for Mask Identifier Control registers */
  if (E_NOT_OK != returnValue)
  {
    /* @Trace: CanTrcv_SUD_API_154 */
    /* Configure default value for Mask Identifier 3 Control register */
    returnValue = ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_MASK_ID3_CTRL_REG,
      TLE9255W_SWK_MASK_IDX_CTRL_DEFAULT_VALUE);

    /* Configure default value for Mask Identifier 2 Control register */
    returnValue |= ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_MASK_ID2_CTRL_REG,
      TLE9255W_SWK_MASK_IDX_CTRL_DEFAULT_VALUE);

    /* Configure default value for Mask Identifier 1 Control register */
    returnValue |= ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_MASK_ID1_CTRL_REG,
      TLE9255W_SWK_MASK_IDX_CTRL_DEFAULT_VALUE);

    /* Configure default value for Mask Identifier 0 Control register */
    returnValue |= ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_MASK_ID0_CTRL_REG,
      TLE9255W_SWK_MASK_IDX_CTRL_DEFAULT_VALUE);
  }
  else
  {
    /* Nothing to do */
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_TLE9255WResetDataControl                      **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to reset Data Control registers on      **
**                      TLE9255 device.                                       **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Reset Data Control successful.                  **
**                      E_NOT_OK: Reset Data Control not successful.          **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_TLE9255W_SUPPORTED                  **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_WriteReg                 **
*******************************************************************************/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TLE9255WResetDataControl(
  CONST(uint8, AUTOMATIC) transceiver)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* @Trace: CanTrcv_SUD_API_155 */
  /* Configure default value for Data 7 Control register */
  returnValue = ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_DATA7_CTRL_REG,
    TLE9255W_SWK_DATAX_CTRL_DEFAULT_VALUE);

  /* Configure default value for Data 6 Control register */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_DATA6_CTRL_REG,
    TLE9255W_SWK_DATAX_CTRL_DEFAULT_VALUE);

  /* Configure default value for Data 5 Control register */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_DATA5_CTRL_REG,
    TLE9255W_SWK_DATAX_CTRL_DEFAULT_VALUE);

  /* Configure default value for Data 4 Control register */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_DATA4_CTRL_REG,
    TLE9255W_SWK_DATAX_CTRL_DEFAULT_VALUE);

  /* Configure default value for Data 3 Control register */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_DATA3_CTRL_REG,
    TLE9255W_SWK_DATAX_CTRL_DEFAULT_VALUE);

  /* Configure default value for Data 2 Control register */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_DATA2_CTRL_REG,
    TLE9255W_SWK_DATAX_CTRL_DEFAULT_VALUE);

  /* Configure default value for Data 1 Control register */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_DATA1_CTRL_REG,
    TLE9255W_SWK_DATAX_CTRL_DEFAULT_VALUE);

  /* Configure default value for Data 0 Control register */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_DATA0_CTRL_REG,
    TLE9255W_SWK_DATAX_CTRL_DEFAULT_VALUE);

  return returnValue;
}

#if (STD_ON == CANTRCV_HW_PN_SUPPORTED)

#if (STD_ON == CANTRCV_HW_POR_SUPPORTED)
/*******************************************************************************
** Function Name      : CanTrcv_TLE9255WGetPorFlag                            **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to get status of POR flag on TLE9255W   **
**                      device.                                               **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : ptrPorFlag - Store status of POR flag.                **
**                                                                            **
** Return parameter   : E_OK: Get status of POR flag success.                 **
**                      E_NOT_OK: Get status of POR flag not success.         **
**                                                                            **
** Preconditions      : CANTRCV_TLE9255W_SUPPORTED == STD_ON                  **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_ReadReg                  **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00181 SWS_CanTrcv_00186
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TLE9255WGetPorFlag(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(uint8, AUTOMATIC, CANTRCV_APPL_DATA) ptrPorFlag)
{
  VAR(uint8, AUTOMATIC) data;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Initialize local variable */
  data = (uint8)CANTRCV_ZERO;

  /* @Trace: CanTrcv_SUD_API_049 */
  /* Read value in Transceiver Status register */
  returnValue = ptrWriteReadReg->ReadReg(transceiver, TLE9255W_TRANS_STAT_REG, &data);
  if (E_NOT_OK != returnValue)
  {
    /* Get POR flag - bit 7 */
    *ptrPorFlag = (boolean)((data & TLE9255W_POR_MASK) >> CANTRCV_SEVEN);
  }
  else
  {
    /* Nothing to do */
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_TLE9255WClearPorFlag                          **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to clear POR flag on TLE9255W device.   **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Clear POR flag success.                         **
**                      E_NOT_OK: Clea POR flag not success.                  **
**                                                                            **
** Preconditions      : CANTRCV_TLE9255W_SUPPORTED == STD_ON                  **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_WriteReg                 **
*******************************************************************************/
/* @Trace_CanTrcv_00181
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TLE9255WClearPorFlag(
  CONST(uint8, AUTOMATIC) transceiver)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Clear POR flag - bit 7 */
  /* @Trace: CanTrcv_SUD_API_053 */
  returnValue = ptrWriteReadReg->WriteReg(transceiver, TLE9255W_TRANS_STAT_REG,
    TLE9255W_POR_MASK);

  return returnValue;
}
#endif /* (STD_ON == CANTRCV_HW_POR_SUPPORTED) */

/*******************************************************************************
** Function Name      : CanTrcv_TLE9255WGetSyserrFlag                         **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to get status of SYSERR flag on         **
**                      TLE9255W device.                                      **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : ptrSyserrFlag - Store status of SYSERR flag.          **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_TLE9255W_SUPPORTED and              **
**                      STD_ON == CANTRCV_HW_PN_SUPPORTED                     **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_ReadReg                  **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00181 SWS_CanTrcv_00186
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TLE9255WGetSyserrFlag(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(uint8, AUTOMATIC, CANTRCV_APPL_DATA) ptrSyserrFlag)
{
  VAR(uint8, AUTOMATIC) data;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Initialize local variable */
  data = (uint8)CANTRCV_ZERO;

  /* @Trace: CanTrcv_SUD_API_057 */
  /* Read value in Selective Wake Status */
  returnValue = ptrWriteReadReg->ReadReg(transceiver, TLE9255W_SWK_STAT_REG, &data);
  if (E_NOT_OK != returnValue)
  {
    /* Get SYSERR flag - bit 4 */
    *ptrSyserrFlag = (boolean)((data & TLE9255W_SYSERR_MASK) >> CANTRCV_FOUR);
  }
  else
  {
    /* Nothing to do */
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_TLE9255WConfigurePartialNetworking            **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to configure partial networking on      **
**                      TLE9255W device.                                      **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Configure successful.                           **
**                      E_NOT_OK: Configure not successful.                   **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_TLE9255W_SUPPORTED and              **
**                      STD_ON == CANTRCV_HW_PN_SUPPORTED                     **
**                                                                            **
** Remarks            : Global variable(s): CanTrcv_CanTrcvNetwork            **
**                                                                            **
**                      Function(s) invoked: CanTrcv_ReadReg,                 **
**                      CanTrcv_TLE9255WSetPNActivationState,                 **
**                      CanTrcv_TLE9255WConfigureIdentifierType,              **
**                      CanTrcv_TLE9255WConfigureDataControl,                 **
**                      CanTrcv_WriteReg                                      **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00182 SWS_CanTrcv_00187
*/
static FUNC(Std_ReturnType, CANTRCV_CODE)
  CanTrcv_TLE9255WConfigurePartialNetworking(
    CONST(uint8, AUTOMATIC) transceiver)
{
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  P2CONST(CanTrcv_PartialNetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvPnNetwork;
  VAR(uint8, AUTOMATIC) data;
  VAR(uint8, AUTOMATIC) pnIndex;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Initialize local variable */
  data = (uint8)CANTRCV_ZERO;

  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];
  /* Get Parital Network index */
  pnIndex = ptrCanTrcvNetwork->PnNetworkIndex;
  /* Get the pointer to the structure of the requested PN network */
  ptrCanTrcvPnNetwork = &CanTrcv_PartialNetwork[pnIndex];

  /* @Trace: CanTrcv_SUD_API_096 */
  /* Read Baudrate Control register */
  returnValue = ptrWriteReadReg->ReadReg(transceiver, TLE9255W_SWK_CTRL_2_REG, &data);
  /* polyspace -begin MISRA-C3:D4.1 [Justified:Low] "ptrCanTrcvPnNetwork points to an element of CanTrcv_CanTrcvNetwork which is  guaranteed by Generator." */
  if (E_NOT_OK != returnValue)
  {
    /* @Trace: CanTrcv_SUD_API_097 */
    /* Configure data rate */
    data &= TLE9255W_BR_CLEAR;
    /* polyspace +4 MISRA-C3:D4.1 [Justified:Low] "ptrCanTrcvPnNetwork points to an element of CanTrcv_CanTrcvNetwork which is  guaranteed by Generator." */
    /* polyspace +3 MISRA-C3:18.1 [Justified:Low] "ptrCanTrcvPnNetwork points to an element of CanTrcv_CanTrcvNetwork which is  guaranteed by Generator." */
    /* polyspace +2 RTE:IDP [Justified:Low] "CanTrcv_PartialNetwork is guaranteed by Generator." */
    data |= ptrCanTrcvPnNetwork->BaudRate;
    returnValue = ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_CTRL_2_REG, data);

  }
  /* polyspace -end MISRA-C3:D4.1 [Justified:Low] "ptrCanTrcvPnNetwork points to an element of CanTrcv_CanTrcvNetwork which is  guaranteed by Generator." */
  else
  {
    /* Nothing to do */
  }

  /* @Trace: CanTrcv_SUD_API_098 */
  /* Enable Selective Wake Unit */
  returnValue |= CanTrcv_TLE9255WSetPNActivationState(transceiver, PN_ENABLED);


  /* @Trace: CanTrcv_SUD_API_099 */
  /* Configure Identifier Type and Wake-up frame Identifier */
  returnValue |= CanTrcv_TLE9255WConfigureIdentifierType(transceiver);


  /* @Trace: CanTrcv_SUD_API_100 */
  /* Configure data length code */
  /* polyspace +4 MISRA-C3:18.1 [Justified:Low] "ptrCanTrcvPnNetwork points to an element of CanTrcv_CanTrcvNetwork which is  guaranteed by Generator." */
  /* polyspace +3 MISRA-C3:D4.1 [Justified:Low] "ptrCanTrcvPnNetwork points to an element of CanTrcv_CanTrcvNetwork which is  guaranteed by Generator." */
  /* polyspace +2 RTE:IDP [Justified:Low] "CanTrcv_PartialNetwork is guaranteed by Generator." */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_DLC_CTRL_REG,
    ptrCanTrcvPnNetwork->PnFrameDlc);

  /* @Trace: CanTrcv_SUD_API_101 */
  /* Configure Data Control */
  returnValue |= CanTrcv_TLE9255WConfigureDataControl(transceiver);

  /* @Trace: CanTrcv_SUD_API_101 */
  /* Confirm SWK configuration */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_CTRL_1_REG,
    TLE9255W_CFG_VAL_VALID);

  /* @Trace: CanTrcv_SUD_API_102 */
  /* Disable selective wake uint if configuration is disable */
  if (CANTRCV_TRUE != ptrCanTrcvPnNetwork->PnEnabled)
  {
    /* @Trace: CanTrcv_SUD_API_103 */
    /* Disable Selective Wake Unit */
    returnValue |= CanTrcv_TLE9255WSetPNActivationState(transceiver,
      PN_DISABLED);
  }
  else
  {
    /* Nothing to do */
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_TLE9255WConfigureIdentifierType               **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to configure Identifier Type on         **
**                      TLE9255W device.                                      **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Configure Identifier Type successful.           **
**                      E_NOT_OK: Configure Identifier Type not successful.   **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_TLE9255W_SUPPORTED and              **
**                      STD_ON == CANTRCV_HW_PN_SUPPORTED                     **
**                                                                            **
** Remarks            : Global variable(s): CanTrcv_CanTrcvNetwork            **
**                                                                            **
**                      Function(s) invoked: CanTrcv_WriteReg                 **
*******************************************************************************/
static FUNC(Std_ReturnType, CANTRCV_CODE)
  CanTrcv_TLE9255WConfigureIdentifierType(CONST(uint8, AUTOMATIC) transceiver)
{
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  P2CONST(CanTrcv_PartialNetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvPnNetwork;
  VAR(uint8, AUTOMATIC) data;
  VAR(uint8, AUTOMATIC) pnIndex;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];
  /* Get Parital Network index */
  pnIndex = ptrCanTrcvNetwork->PnNetworkIndex;
  /* Get the pointer to the structure of the requested PN network */
  ptrCanTrcvPnNetwork = &CanTrcv_PartialNetwork[pnIndex];

  /* polyspace +3 MISRA-C3:18.1 [Justified:Low] "ptrCanTrcvPnNetwork points to an element of CanTrcv_CanTrcvNetwork which is  guaranteed by Generator." */
  /* polyspace +2 MISRA-C3:D4.1 [Justified:Low] "ptrCanTrcvPnNetwork points to an element of CanTrcv_CanTrcvNetwork which is  guaranteed by Generator." */
  /* polyspace +1 RTE:IDP [Justified:Low] "CanTrcv_PartialNetwork is guaranteed by Generator." */
  if (CANTRCV_FALSE != ptrCanTrcvPnNetwork->PnCanIdIsExtended)
  {
    /* @Trace: CanTrcv_SUD_API_106 */
    /* Configure Identifier Type */
    data = ((uint8)ptrCanTrcvPnNetwork->PnCanIdIsExtended <<
      TLE9255W_IDE_SHIFT);
    /* Configure the extend identifier bits ID28 - ID24 */
    data |= (uint8)((ptrCanTrcvPnNetwork->PnFrameCanId &
      TLE9255W_ID28_24_MASK) >> CANTRCV_TWENTYFOUR);
    returnValue = ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_ID3_CTRL_REG,
      data);

    /* Configure the extend identifier bits ID23 - ID16 */
    data = (uint8)((ptrCanTrcvPnNetwork->PnFrameCanId &
      TLE9255W_ID23_16_MASK) >> CANTRCV_SIXTEEN);
    returnValue |= ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_ID2_CTRL_REG,
      data);

    /* Configure the extend identifier bits ID15 - ID8 */
    data = (uint8)((ptrCanTrcvPnNetwork->PnFrameCanId &
      TLE9255W_ID15_8_MASK) >> CANTRCV_EIGHT);
    returnValue |= ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_ID1_CTRL_REG,
      data);

    /* Configure the extend identifier bits ID7 - ID0 */
    data = (uint8)(ptrCanTrcvPnNetwork->PnFrameCanId &
      TLE9255W_ID7_0_MASK);
    returnValue |= ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_ID0_CTRL_REG,
      data);

    /* @Trace: CanTrcv_SUD_API_107 */
    if (E_NOT_OK != returnValue)
    {
      /* Configure the extend mask identifier bits ID28 - ID24 */
      data = (uint8)((ptrCanTrcvPnNetwork->PnFrameCanIdMask &
        TLE9255W_MASK_ID28_24_MASK) >> CANTRCV_TWENTYFOUR);
      returnValue = ptrWriteReadReg->WriteReg(transceiver,
        TLE9255W_SWK_MASK_ID3_CTRL_REG, data);

      /* Configure the extend mask identifier bits ID23 - ID16 */
      data = (uint8)((ptrCanTrcvPnNetwork->PnFrameCanIdMask &
        TLE9255W_MASK_ID23_16_MASK) >> CANTRCV_SIXTEEN);
      returnValue |= ptrWriteReadReg->WriteReg(transceiver,
        TLE9255W_SWK_MASK_ID2_CTRL_REG, data);

      /* Configure the extend mask identifier bits ID15 - ID8 */
      data = (uint8)((ptrCanTrcvPnNetwork->PnFrameCanIdMask &
        TLE9255W_MASK_ID15_8_MASK) >> CANTRCV_EIGHT);
      returnValue |= ptrWriteReadReg->WriteReg(transceiver,
        TLE9255W_SWK_MASK_ID1_CTRL_REG, data);

      /* Configure the extend mask identifier bits ID7 - ID0 */
      data = (uint8)(ptrCanTrcvPnNetwork->PnFrameCanIdMask &
        TLE9255W_MASK_ID7_0_MASK);
      returnValue |= ptrWriteReadReg->WriteReg(transceiver,
        TLE9255W_SWK_MASK_ID0_CTRL_REG, data);
    }
    else
    {
      /* Nothing to do */
    }
  }
  else
  {
    /* @Trace: CanTrcv_SUD_API_108 */
    /* Configure Identifier Type */
    data = ((uint8)ptrCanTrcvPnNetwork->PnCanIdIsExtended <<
      TLE9255W_IDE_SHIFT);
    /* Configure the normal identifier bits ID10 - ID6 */
    data |= (uint8)((ptrCanTrcvPnNetwork->PnFrameCanId &
      TLE9255W_ID10_6_MASK) >> CANTRCV_SIX);
    returnValue = ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_ID3_CTRL_REG,
      data);

    /* Configure the normal identifier bits ID5 - ID0 */
    data = (uint8)(ptrCanTrcvPnNetwork->PnFrameCanId &
      TLE9255W_ID5_0_MASK) ;
    returnValue |= ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_ID2_CTRL_REG,
      data);
    
    /* @Trace: CanTrcv_SUD_API_109 */
    if (E_NOT_OK != returnValue)
    {
      /* Configure the normal Mask Identifier bit MASK_ID7_0 */
      data = (uint8)(ptrCanTrcvPnNetwork->PnFrameCanIdMask &
        TLE9255W_MASK_ID7_0_MASK);
      returnValue = ptrWriteReadReg->WriteReg(transceiver,
        TLE9255W_SWK_MASK_ID0_CTRL_REG, data);

      /* Configure the normal Mask Identifier bit MASK_ID10_8 */
      data = (uint8)((ptrCanTrcvPnNetwork->PnFrameCanIdMask &
        TLE9255W_MASK_ID10_8_MASK) >> CANTRCV_EIGHT);
      returnValue |= ptrWriteReadReg->WriteReg(transceiver,
        TLE9255W_SWK_MASK_ID1_CTRL_REG, data);
    }
    else
    {
      /* Nothing to do */
    }
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_TLE9255WConfigureDataControl                  **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to configure Identifier Type on         **
**                      TLE9255W device.                                      **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Configure successful.                           **
**                      E_NOT_OK: Configure not successful.                   **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_TLE9255W_SUPPORTED and              **
**                      STD_ON == CANTRCV_HW_PN_SUPPORTED                     **
**                                                                            **
** Remarks            : Global variable(s): CanTrcv_CanTrcvNetwork            **
**                                                                            **
**                      Function(s) invoked: CanTrcv_ReadReg,                 **
**                      CanTrcv_TLE9255WSetPNActivationState,                 **
**                      CanTrcv_WriteReg                                      **
*******************************************************************************/
/* polyspace -begin MISRA-C3:18.1 [Justified:Low] "The value of  transceiver is already checked before being passed through the function." */
/* polyspace -begin MISRA-C3:D4.1 [Justified:Low] "The value of  transceiver is already checked before being passed through the function." */
static FUNC(Std_ReturnType, CANTRCV_CODE)
  CanTrcv_TLE9255WConfigureDataControl(CONST(uint8, AUTOMATIC) transceiver)
{
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  P2CONST(CanTrcv_PartialNetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvPnNetwork;
  VAR(uint8, AUTOMATIC) pnIndex;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];
  /* Get Parital Network index */
  pnIndex = ptrCanTrcvNetwork->PnNetworkIndex;
  /* Get the pointer to the structure of the requested PN network */
  ptrCanTrcvPnNetwork = &CanTrcv_PartialNetwork[pnIndex];

  /* @Trace: CanTrcv_SUD_API_110 */
  /* polyspace +4 MISRA-C3:18.1 [Justified:Unset] "ptrCanTrcvPnNetwork points to an element of CanTrcv_CanTrcvNetwork which is  guaranteed by Generator." */
  /* polyspace +3 MISRA-C3:D4.1 [Justified:Low] "ptrCanTrcvPnNetwork points to an element of CanTrcv_CanTrcvNetwork which is  guaranteed by Generator." */
  /* polyspace +2 RTE:IDP [Justified:Low] "CanTrcv_PartialNetwork is guaranteed by Generator." */
  returnValue = ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_DATA7_CTRL_REG,
    ptrCanTrcvPnNetwork->PnFrameMaskSpec->PnFrameDataMask7);

  /* Configure Data 6 Control */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_DATA6_CTRL_REG,
    ptrCanTrcvPnNetwork->PnFrameMaskSpec->PnFrameDataMask6);

  /* Configure Data 5 Control */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_DATA5_CTRL_REG,
    ptrCanTrcvPnNetwork->PnFrameMaskSpec->PnFrameDataMask5);

  /* Configure Data 4 Control */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_DATA4_CTRL_REG,
    ptrCanTrcvPnNetwork->PnFrameMaskSpec->PnFrameDataMask4);

  /* Configure Data 3 Control */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_DATA3_CTRL_REG,
    ptrCanTrcvPnNetwork->PnFrameMaskSpec->PnFrameDataMask3);

  /* Configure Data 2 Control */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_DATA2_CTRL_REG,
    ptrCanTrcvPnNetwork->PnFrameMaskSpec->PnFrameDataMask2);

  /* Configure Data 1 Control */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_DATA1_CTRL_REG,
    ptrCanTrcvPnNetwork->PnFrameMaskSpec->PnFrameDataMask1);

  /* Configure Data 0 Control */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_DATA0_CTRL_REG,
    ptrCanTrcvPnNetwork->PnFrameMaskSpec->PnFrameDataMask0);

  return returnValue;
}
/* polyspace -end MISRA-C3:18.1 [Justified:Low] "The value of  transceiver is already checked before being passed through the function." */
/* polyspace -end MISRA-C3:D4.1 [Justified:Low] "The value of  transceiver is already checked before being passed through the function." */
/*******************************************************************************
** Function Name      : CanTrcv_TLE9255WGetTrcvSystemData                     **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to get system data of TLE9255W device.  **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : ptrSystemData - Store system data.                    **
**                                                                            **
** Return parameter   : E_OK: Get system data success.                        **
**                      E_NOT_OK: Get system data not success.                **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_TLE9255W_SUPPORTED and              **
**                      STD_ON == CANTRCV_HW_PN_SUPPORTED                     **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_ReadReg                  **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00189
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TLE9255WGetTrcvSystemData(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(uint32, AUTOMATIC, CANTRCV_APPL_DATA) ptrSystemData)
{
  VAR(uint8, AUTOMATIC) data;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Initialize local variable */
  data = (uint8)CANTRCV_ZERO;

  /* Read value in Transceiver status register */
  returnValue = ptrWriteReadReg->ReadReg(transceiver, TLE9255W_SWK_STAT_REG, &data);
  if (E_NOT_OK != returnValue)
  {
    /* @Trace: CanTrcv_SUD_API_181 */
    /* polyspace +1 MISRA2012:D4.14 [Justified:Low] "Pointer ptrSystemData is checked NULL by DET." */
    *ptrSystemData = (uint32)data;
  }
  else
  {
    /* Nothing to do */
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_TLE9255WReadTrcvTimeoutFlag                   **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to get system data of TLE9255W device.  **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : ptrFlagState - Store time out state.                  **
**                                                                            **
** Return parameter   : E_OK: Get time out flag success.                      **
**                      E_NOT_OK: Get time out not success.                   **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_TLE9255W_SUPPORTED and              **
**                      STD_ON == CANTRCV_HW_PN_SUPPORTED                     **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_ReadReg                  **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00215 SWS_CanTrcv_00211
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TLE9255WReadTrcvTimeoutFlag(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(CanTrcv_TrcvFlagStateType, AUTOMATIC, CANTRCV_APPL_DATA) ptrFlagState)
{
  VAR(uint8, AUTOMATIC) data;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Initialize local variable */
  data = (uint8)CANTRCV_ZERO;

  /* Read value in Selective Wake Status */
  returnValue = ptrWriteReadReg->ReadReg(transceiver, TLE9255W_SWK_STAT_REG, &data);
  if (E_NOT_OK != returnValue)
  {
    /* @Trace: CanTrcv_SUD_API_185 */
    /* Get bit CANTO - bit 2 */
    /* polyspace +3 MISRA2012:D4.14 [Justified:Low] "Pointer ptrFlagState is checked NULL by DET." */
    /* polyspace +2 MISRA2012:10.5 [Justified:Low] "Operation is guaranteed that does not exceed CanTrcv_TrcvFlagStateType." */
    *ptrFlagState = (CanTrcv_TrcvFlagStateType)(uint8)((
      data & TLE9255W_CANTO_MASK) >> CANTRCV_TWO);
  }
  else
  {
    /* Nothing to do */
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_TLE9255WClearTrcvTimeoutFlag                  **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to clear system data of TLE9255W device.**
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : ptrFlagState - Store time out state.                  **
**                                                                            **
** Return parameter   : E_OK: Clear time out flag success.                    **
**                      E_NOT_OK: Clear time out not success.                 **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_TLE9255W_SUPPORTED and              **
**                      STD_ON == CANTRCV_HW_PN_SUPPORTED                     **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_WriteReg                 **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00216
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TLE9255WClearTrcvTimeoutFlag(
  CONST(uint8, AUTOMATIC) transceiver)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* @Trace: CanTrcv_SUD_API_191 */
  /* Clear CANTO bit - bit 2 */
  returnValue = ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_STAT_REG,
    TLE9255W_CANTO_MASK);

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_TLE9255WReadTrcvSilenceFlag                   **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to clear system data of TLE9255W device.**
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : ptrFlagState - Store time out state.                  **
**                                                                            **
** Return parameter   : E_OK: Clear time out flag success.                    **
**                      E_NOT_OK: Clear time out not success.                 **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_TLE9255W_SUPPORTED and              **
**                      STD_ON == CANTRCV_HW_PN_SUPPORTED                     **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_WriteReg                 **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00217 SWS_CanTrcv_00211
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TLE9255WReadTrcvSilenceFlag(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(CanTrcv_TrcvFlagStateType, AUTOMATIC, CANTRCV_APPL_DATA) ptrFlagState)
{
  VAR(uint8, AUTOMATIC) data;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Initialize local variable */
  data = (uint8)CANTRCV_ZERO;

  /* @Trace: CanTrcv_SUD_API_198 */
  /* Read value in Selective Wake Status register */
  returnValue = ptrWriteReadReg->ReadReg(transceiver, TLE9255W_SWK_STAT_REG, &data);
  if (E_NOT_OK != returnValue)
  {
    /* Get value bit CANSIL - bit 1 */
    /* polyspace +3 MISRA2012:D4.14 [Justified:Low] "Pointer ptrFlagState is checked NULL by DET." */
    /* polyspace +2 MISRA2012:10.5 [Justified:Low] "Operation is guaranteed that does not exceed CanTrcv_TrcvFlagStateType." */
    *ptrFlagState = (CanTrcv_TrcvFlagStateType)(uint8)((data &
      TLE9255W_CANSIL_MASK) >> CANTRCV_ONE);
  }
  else
  {
    /* Nothing to do */
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_TLE9255WSetPNActivationState                  **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to set state of selective wake up uint  **
**                      on TLE9255W device.                                   **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                      activationType - PN_DISABLED: Disable selective       **
**                                                    wake up.                **
**                                       PN_ENABLED: Enable selective         **
**                                                   wake up.                 **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Set state selective wake up is successful.      **
**                      E_NOT_OK: Set state selective wake up is not          **
**                                successful.                                 **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_TLE9255W_SUPPORTED and              **
**                      STD_ON == CANTRCV_HW_PN_SUPPORTED                     **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_ReadReg,                 **
**                      CanTrcv_WriteReg                                      **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00221 SWS_CanTrcv_00222
  SWS_CanTrcv_00210
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TLE9255WSetPNActivationState(
  CONST(uint8, AUTOMATIC) transceiver,
  CONST(CanTrcv_PNActivationType, AUTOMATIC) activationState)
{
  VAR(uint8, AUTOMATIC) data;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Initialize local variable */
  data = (uint8)CANTRCV_ZERO;

  /* @Trace: CanTrcv_SUD_API_104 */
  /* Read value in CAN control register */
  returnValue = ptrWriteReadReg->ReadReg(transceiver, TLE9255W_SWK_CTRL_2_REG, &data);
  if (E_NOT_OK != returnValue)
  {
    /* Set CAN selective wake-up */
    data &= (uint8)(~TLE9255W_SWK_MASK);
    data |= ((uint8)activationState << TLE9255W_SWK_EN_SHIFT);
    returnValue = ptrWriteReadReg->WriteReg(transceiver, TLE9255W_SWK_CTRL_2_REG, data);
  }
  else
  {
    /* Nothing to do */
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_TLE9255WClearTrcvWufFlag                      **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to clear wake up frame flag on TLE9255W **
**                      device.                                               **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Clear wake up frame flag success.               **
**                      E_NOT_OK: Clear wake up frame flag not success.       **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_TLE9255W_SUPPORTED and              **
**                      STD_ON == CANTRCV_HW_PN_SUPPORTED                     **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_ReadReg,                 **
**                      CanTrcv_WriteReg                                      **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00194
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TLE9255WClearTrcvWufFlag(
  CONST(uint8, AUTOMATIC) transceiver)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* @Trace: CanTrcv_SUD_API_213 */
  /* Clear bit WUF - bit 0 */
  returnValue = ptrWriteReadReg->WriteReg(transceiver, TLE9255W_WAKE_STAT_REG,
    TLE9255W_WUF_MASK);

  return returnValue;
}
#endif /* (STD_ON == CANTRCV_HW_PN_SUPPORTED) */

#if (STD_ON == CANTRCV_WAKEUP_SUPPORTED)
/*******************************************************************************
** Function Name      : CanTrcv_TLE9255WCheckWakeFlag                         **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to check wake up flag of TLE9255W       **
**                      device.                                               **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - Transceiver ID.                         **
**                      ptrCanTrcvNetwork - Pointer to Can Transceiver        **
**                                          configuration.                    **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: The request for checking the wakeup flag has    **
**                            been accepted.                                  **
**                      E_NOT_OK: The request for checking the wakeup flag    **
**                                has not been accepted.                      **
**                                                                            **
** Preconditions      : CANTRCV_TLE9255W_SUPPORTED == STD_ON and              **
**                      CANTRCV_WAKEUP_SUPPORTED == STD_ON                    **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_ReadReg,                 **
**                      CanTrcv_WriteReg, EcuM_SetWakeupEvent                 **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00223 SWS_CanTrcv_00086
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TLE9255WCheckWakeFlag(
  CONST(uint8, AUTOMATIC) transceiver,
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork)
{
  VAR(uint8, AUTOMATIC) data;
  VAR(uint8, AUTOMATIC) lwuFlag;
  VAR(uint8, AUTOMATIC) wupFlag;
  VAR(uint8, AUTOMATIC) wufFlag;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Initialize local variable */
  data = (uint8)CANTRCV_ZERO;

  /* @Trace: CanTrcv_SUD_API_242 */
  /* Read value in Wake Status register */
  returnValue = ptrWriteReadReg->ReadReg(transceiver, TLE9255W_WAKE_STAT_REG, &data);
  if (E_NOT_OK != returnValue)
  {
    /* Get LWU flag -bit 2 */
    lwuFlag = (data & TLE9255W_LWU_MASK);
    /* Get WUP flag - bit 1 */
    wupFlag = (data & TLE9255W_WUP_MASK);
    /* Get WUF flag - bit 0 */
    wufFlag = (data & TLE9255W_WUF_MASK);

    /* Check status wake up by bus */
    if ((TLE9255W_WUP_MASK == wupFlag) || (TLE9255W_WUF_MASK == wufFlag))
    {
      /* @Trace: CanTrcv_SUD_API_243 */
      /* Notify to EcuM wake up source */
      EcuM_SetWakeupEvent(ptrCanTrcvNetwork->WakeupSource);
    }
    else
    {
      /* Nothing to do */
    }

    /* Check status wake up by pin */
    if (TLE9255W_LWU_MASK == lwuFlag)
    {
      /* @Trace: CanTrcv_SUD_API_244 */
      /* Notify to EcuM wake up source */
      EcuM_SetWakeupEvent(ptrCanTrcvNetwork->WakeupSource);
      /* Clear wake up flag */
      returnValue = ptrWriteReadReg->WriteReg(transceiver, TLE9255W_WAKE_STAT_REG,
        TLE9255W_LWU_MASK);
    }
    else
    {
      /* Nothing to do */
    }
  }
  else
  {
    /* Nothing to do */
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_TLE9255WMainFunction                          **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to check and perform wake up flag on    **
**                      TLE9255W device.                                      **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - Transceiver ID.                         **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : CANTRCV_TLE9255W_SUPPORTED == STD_ON and              **
**                      CANTRCV_WAKEUP_SUPPORTED == STD_ON                    **
**                                                                            **
** Remarks            : Global variable(s): CanTrcv_WakeUpReason,             **
**                      CanTrcv_WakeupMode, CanTrcv_WakeupFlagIndication,     **
**                      CanTrcv_WakeupPending                                 **
**                                                                            **
**                      Function(s) invoked: CanTrcv_ReadReg,                 **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00112 SRS_BSW_00424
*/
static FUNC(void, CANTRCV_CODE) CanTrcv_TLE9255WMainFunction(
  CONST(uint8, AUTOMATIC) transceiver)
{
  VAR(uint8, AUTOMATIC) data;
  VAR(uint8, AUTOMATIC) wakeByBusFlag;
  VAR(uint8, AUTOMATIC) wakeByPinFlag;
  VAR(uint8, AUTOMATIC) returnStatus;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* @Trace: CanTrcv_SUD_API_228 */
  /* Initialize local variable */
  data = (uint8)CANTRCV_ZERO;
  wakeByBusFlag = (uint8)CANTRCV_ZERO;
  wakeByPinFlag = (uint8)CANTRCV_ZERO;

  /* Check wake up by bus */
  /* Read Wake Status register */
  returnStatus = ptrWriteReadReg->ReadReg(transceiver, TLE9255W_WAKE_STAT_REG, &data);
  if (E_NOT_OK != returnStatus)
  {
    wakeByBusFlag |= (data & TLE9255W_WUP_MASK);
    wakeByBusFlag |= (data & TLE9255W_WUF_MASK);
    if ((uint8)CANTRCV_ZERO != wakeByBusFlag)
    {
      /* @Trace: CanTrcv_SUD_API_229 */
      /* Set wake up reason as CANTRCV_WU_BY_BUS */
      CanTrcv_WakeUpReason[transceiver] = CANTRCV_WU_BY_BUS;
    }
    else
    {
      /* Nothing to do */
    }

    wakeByPinFlag |= (data & TLE9255W_LWU_MASK);
    if ((uint8)CANTRCV_ZERO != wakeByPinFlag)
    {
      /* @Trace: CanTrcv_SUD_API_230 */
      /* Set wake up reason as CANTRCV_WU_BY_PIN */
      CanTrcv_WakeUpReason[transceiver] = CANTRCV_WU_BY_PIN;
    }
    else
    {
      /* Nothing to do */
    }

    if (((uint8)CANTRCV_ZERO != wakeByBusFlag) ||
      ((uint8)CANTRCV_ZERO != wakeByPinFlag))
    {
      /* Check state wake up of CAN Transceiver */
      if (CANTRCV_WUMODE_ENABLE == CanTrcv_WakeupMode[transceiver])
      {
        /* @Trace: CanTrcv_SUD_API_231 */
        /* Update wake up status */
        CanTrcv_WakeupFlagIndication[transceiver] = CANTRCV_WAKE_UP_OCCURRED;
      }
      else if (CANTRCV_WUMODE_DISABLE == CanTrcv_WakeupMode[transceiver])
      {
        /* @Trace: CanTrcv_SUD_API_232 */
        /* Store the pending wakeup event */
        CanTrcv_WakeupPending[transceiver] = CANTRCV_WAKEUP_PENDING;
      }
      else
      {
        /* Nothing to do */
      }
    }
    else
    {
      /* Nothing to do */
    }
  }
  else
  {
    /* Nothing to do */
  }
}
#endif /* (STD_ON == CANTRCV_WAKEUP_SUPPORTED) */

#endif /* (STD_ON == CANTRCV_TLE9255W_SUPPORTED) */

/* Functions for TCAN1145 device */
#if (STD_ON == CANTRCV_TCAN1145_SUPPORTED)

/*******************************************************************************
** Function Name      : CanTrcv_TCAN1145SetModeControl                         **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to set mode control on TCAN1145 device.  **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                      mode - Mode control.                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Set mode control successful.                    **
**                      E_NOT_OK: Set mode control not successful.            **
**                                                                            **
** Preconditions      : CANTRCV_TCAN1145_SUPPORTED == STD_ON                  **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_WriteReg,                **
**                                           CaNTrcv_ReadReg                  **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00102
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TCAN1145SetModeControl(
  CONST(uint8, AUTOMATIC) transceiver,
  CONST(TCAN1145_ModeControlType, AUTOMATIC) mode)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
   VAR(uint8,AUTOMATIC) data;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  data = (uint8)CANTRCV_ZERO;
  /* @Trace: CanTrcv_SUD_API_337 */
  /* Set Mode Control - Bit MC */
  returnValue = ptrWriteReadReg->ReadReg(transceiver, TCAN1145_MODE_CNTRL_REG,
    &data);
  data &= (uint8)TCAN1145_MODE_CNTRL_BITMASKS;
  data |= (uint8)mode;
  returnValue = ptrWriteReadReg->WriteReg(transceiver, TCAN1145_MODE_CNTRL_REG,(uint8)data);

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_TCAN1145GetModeControl                         **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to get current mode control of TCAN1145  **
**                      device.                                               **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : ptrMode - Store value of mode control.                **
**                                                                            **
** Return parameter   : E_OK: Get mode control successful.                    **
**                      E_NOT_OK: Get mode control not successful.            **
**                                                                            **
** Preconditions      : CANTRCV_TCAN1145_SUPPORTED == STD_ON                   **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_ReadReg                  **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00163
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TCAN1145GetModeControl(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(CanTrcv_TrcvModeType, AUTOMATIC, CANTRCV_APPL_DATA) ptrMode)
{
  VAR(uint8, AUTOMATIC) data;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Initialize local variable */
  data = (uint8)CANTRCV_ZERO;

  /* @Trace: CanTrcv_SUD_API_332 */
  /* Read value in Mode control register */
  returnValue = ptrWriteReadReg->ReadReg(transceiver, TCAN1145_MODE_CNTRL_REG, &data);
  if (E_NOT_OK != returnValue)
  {
    /* Get value of MC bit - bit [2:0] */
    data &= TCAN1145_MC_MASK;
    if ((uint32)TCAN1145_NORMAL_MODE == data)
    {
      /* @Trace: CanTrcv_SUD_API_333 */
      *ptrMode = CANTRCV_TRCVMODE_NORMAL;
    }
    else if ((uint32)TCAN1145_STANDBY_MODE == data)
    {
      /* @Trace: CanTrcv_SUD_API_334 */
      *ptrMode = CANTRCV_TRCVMODE_STANDBY;
    }
    else if ((uint32)TCAN1145_SLEEP_MODE == data)
    {
      /* @Trace: CanTrcv_SUD_API_335 */
      *ptrMode = CANTRCV_TRCVMODE_SLEEP;
    }
    else
    {
      /* @Trace: CanTrcv_SUD_API_336 */
      /* Set return value as E_NOT_OK */
      returnValue = E_NOT_OK;
    }
  }
  else
  {
    /* Nothing to do */
  }

  return returnValue;
}


/*******************************************************************************
** Function Name      : CanTrcv_TCAN1145Init                                   **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to initialize TCAN1145 device.           **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                      ptrCanTrcvNetwork - Pointer to the configuration      **
**                                           structure.                       **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: The initialization is successful.               **
**                      E_NOT_OK: The initialization is not successful.       **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_TCAN1145_SUPPORTED                   **
**                                                                            **
** Remarks            : Global variable(s): CanTrcv_WakeUpReason              **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      CanTrcv_TCAN1145SetModeControl,                        **
**                      CanTrcv_ReadReg,                                      **
**                      CanTrcv_WriteReg,                                     **
**                      EcuM_SetWakeupEvent                                   **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00180 SWS_CanTrcv_00167
  SWS_CanTrcv_00086
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TCAN1145Init(
  CONST(uint8, AUTOMATIC) transceiver,
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork)
{
  VAR(uint8, AUTOMATIC) data;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];

  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  /* Initialize local variables */
  data = (uint8)CANTRCV_ZERO;

  #if (STD_OFF == CANTRCV_WAKEUP_SUPPORTED)
  /* Avoid compiler warning */
  CANTRCV_UNUSED_VAL(ptrCanTrcvNetwork);
  #endif

  #if (STD_ON == CANTRCV_WAKEUP_SUPPORTED)
  /* Configure WAKE pin event capture enable register */
  
    /* @Trace: CanTrcv_SUD_API_318 */
    if (CANTRCV_NEGATIVE_EDGE == ptrCanTrcvNetwork->LocalWakeupDirection)
    {
      /* Falling-edge detection on WAKE pin enabled */
      returnValue = ptrWriteReadReg->WriteReg(transceiver,
        TCAN1145_WAKE_PIN_CONFIG_REG, TCAN1145_WAKE_PIN_FE_EDGE);
    }
    else
    {
      /* Rising-edge detection on WAKE pin enabled */
      returnValue = ptrWriteReadReg->WriteReg(transceiver,
        TCAN1145_WAKE_PIN_CONFIG_REG, TCAN1145_WAKE_PIN_RE_EDGE);
    }


  /* Configure Transceiver event capture enable register */
 /* @Trace: CanTrcv_SUD_API_319 */
    /* Read value of Transceiver event capture enable register */
    returnValue = ptrWriteReadReg->ReadReg(transceiver,
      TCAN1145_CONFIG4_REG, &data);
    if (E_NOT_OK != returnValue)
    {
      /* Enable CAN wake-up */
      data |= TCAN1145_CONFIG4_SWCFG_REG_BIT;
      /* Send request via SPI */
      returnValue = ptrWriteReadReg->WriteReg(transceiver,
        TCAN1145_CONFIG4_REG, data);
    }
    else
    {
      /* Nothing to do */
    }

  #endif /* (STD_ON == CANTRCV_WAKEUP_SUPPORTED) */

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_TCAN1145DeInit                                 **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to deinitialize TCAN1145 device.         **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: The deinitialization is successful.             **
**                      E_NOT_OK: The deinitialization is not successful.     **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_TCAN1145_SUPPORTED                   **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_TCAN1145SetLockControl,   **
**                      CanTrcv_TCAN1145ResetDataMask, CanTrcv_WriteReg,       **
**                      CanTrcv_TCAN1145ResetIdentifierType                    **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_91002 SRS_Can_01108
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TCAN1145DeInit(
  CONST(uint8, AUTOMATIC) transceiver)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* @Trace: CanTrcv_SUD_API_148 */
  /* Configure System event capture enable register */
  returnValue = ptrWriteReadReg->WriteReg(transceiver, TCAN1145_MODE_CNTRL_REG,
    TCAN1145_MODE_CNTRL_REG_DEFAULT_VALUE);
   #if (STD_ON == CANTRCV_HW_PN_SUPPORTED)
    /* Configure default value for Configure Data mask */
    returnValue |= CanTrcv_TCAN1145ResetDataMask(transceiver);
  #endif 
  return returnValue;
}



#if (STD_ON == CANTRCV_HW_PN_SUPPORTED)
#if (STD_ON == CANTRCV_HW_POR_SUPPORTED)
/*******************************************************************************
** Function Name      : CanTrcv_TCAN1145GetPorFlag                             **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to get status of POR flag on TCAN1145    **
**                      device.                                               **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : ptrPorFlag - Store status of POR flag.                **
**                                                                            **
** Return parameter   : E_OK: Get status of POR flag successful.              **
**                      E_NOT_OK: Get status of POR flag is not successful.   **
**                                                                            **
** Preconditions      : CANTRCV_TCAN1145_SUPPORTED == STD_ON                   **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_ReadReg                  **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00181 SWS_CanTrcv_00186
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TCAN1145GetPorFlag(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(uint8, AUTOMATIC, CANTRCV_APPL_DATA) ptrPorFlag)
{
  VAR(uint8, AUTOMATIC) data;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Initialize local variable */
  data = (uint8)CANTRCV_ZERO;

  /* @Trace: CanTrcv_SUD_API_356 */
  /* Read value in System event status register */
  returnValue = ptrWriteReadReg->ReadReg(transceiver, TCAN1145_INT_2_REG,
    &data);
  if (E_NOT_OK != returnValue)
  {
    /* Get status of PO flag - bit 4 */
    *ptrPorFlag = (boolean)((data & TCAN1145_INT_2_PWRON_BIT) >> CANTRCV_SIX);
  }
  else
  {
    /* Nothing to do */
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_TCAN1145ClearPorFlag                           **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to clear POR flag on TCAN1145 device.    **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Clear POR flag is successful.                   **
**                      E_NOT_OK: Clear POR flag is not successful.           **
**                                                                            **
** Preconditions      : CANTRCV_TCAN1145_SUPPORTED == STD_ON                   **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_WriteReg                 **
*******************************************************************************/
/* @Trace_CanTrcv_00181
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TCAN1145ClearPorFlag(
  CONST(uint8, AUTOMATIC) transceiver)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  VAR(uint8,AUTOMATIC) data;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  data = (uint8)CANTRCV_ZERO;
  /* @Trace: CanTrcv_SUD_API_357 */
  /* Clear PO flag - bit 4 */
  returnValue = ptrWriteReadReg->ReadReg(transceiver, TCAN1145_INT_2_REG,
    &data);
  data |= TCAN1145_INT_2_PWRON_BIT;
  returnValue = ptrWriteReadReg->WriteReg(transceiver, TCAN1145_INT_2_REG,
    data);

  return returnValue;
}
#endif /* (STD_ON == CANTRCV_HW_POR_SUPPORTED) */


/*******************************************************************************
** Function Name      : CanTrcv_TCAN1145SetDataMask                            **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function set/reset Data Mask for TCAN1145 device. **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                      command     - Request command to set or reset data    **
**                                    mask registers.                         **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: The data mask set/reset is successful.          **
**                      E_NOT_OK: The data mask set/reset is not successful.  **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_TCAN1145_SUPPORTED                   **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_WriteReg                 **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_91002 SRS_Can_01108
*/
/* polyspace -begin MISRA-C3:18.1 [Justified:Low] "The value of  transceiver is already checked before being passed through the function." */
/* polyspace -begin MISRA-C3:D4.1 [Justified:Low] "The value of  transceiver is already checked before being passed through the function." */
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TCAN1145SetDataMask(
  CONST(uint8, AUTOMATIC) transceiver)
{
  P2CONST(CanTrcv_PartialNetworkType, AUTOMATIC, CANTRCV_CONST)
    ptrCanTrcvPnNetwork;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  VAR(uint8, AUTOMATIC) canTrcvPnIndex;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Get the index of partial network */
  canTrcvPnIndex = CanTrcv_CanTrcvNetwork[transceiver].PnNetworkIndex;
  /* Get the pointer to the structure of the requested partial network */
  ptrCanTrcvPnNetwork = &CanTrcv_PartialNetwork[canTrcvPnIndex];

  /* @Trace: CanTrcv_SUD_API_359 */
  /* Configure CAN Data Byte registers 0 */
  /* polyspace +4 MISRA-C3:18.1 [Justified:Low] "ptrCanTrcvPnNetwork points to an element of CanTrcv_CanTrcvNetwork which is  guaranteed by Generator." */
  /* polyspace +3 MISRA-C3:D4.1 [Justified:Low] "ptrCanTrcvPnNetwork points to an element of CanTrcv_CanTrcvNetwork which is  guaranteed by Generator." */
  /* polyspace +2 RTE:IDP [Justified:Low] "CanTrcv_PartialNetwork is guaranteed by Generator." */
  returnValue = ptrWriteReadReg->WriteReg(transceiver, TCAN1145_DATA_MASK_7_REG,
    ptrCanTrcvPnNetwork->PnFrameMaskSpec->PnFrameDataMask0);

  /* Configure CAN Data Byte registers 1 */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TCAN1145_DATA_MASK_6_REG,
    ptrCanTrcvPnNetwork->PnFrameMaskSpec->PnFrameDataMask1);

  /* Configure CAN Data Byte registers 2 */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TCAN1145_DATA_MASK_5_REG,
    ptrCanTrcvPnNetwork->PnFrameMaskSpec->PnFrameDataMask2);

  /* Configure CAN Data Byte registers 3 */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TCAN1145_DATA_MASK_4_REG,
    ptrCanTrcvPnNetwork->PnFrameMaskSpec->PnFrameDataMask3);

  /* Configure CAN Data Byte registers 4 */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TCAN1145_DATA_MASK_3_REG,
    ptrCanTrcvPnNetwork->PnFrameMaskSpec->PnFrameDataMask4);

  /* Configure CAN Data Byte registers 5 */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TCAN1145_DATA_MASK_2_REG,
    ptrCanTrcvPnNetwork->PnFrameMaskSpec->PnFrameDataMask5);

  /* Configure CAN Data Byte registers 6 */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TCAN1145_DATA_MASK_1_REG,
    ptrCanTrcvPnNetwork->PnFrameMaskSpec->PnFrameDataMask6);

  /* Configure CAN Data Byte registers 7 */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TCAN1145_DATA_MASK_0_REG,
    ptrCanTrcvPnNetwork->PnFrameMaskSpec->PnFrameDataMask7);

  return returnValue;
}
/* polyspace -end MISRA-C3:18.1 [Justified:Low] "The value of  transceiver is already checked before being passed through the function." */
/* polyspace -end MISRA-C3:D4.1 [Justified:Low] "The value of  transceiver is already checked before being passed through the function." */
/*******************************************************************************
** Function Name      : CanTrcv_TCAN1145ResetDataMask                          **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function reset Data Mask for TCAN1145 device.     **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                      command     - Request command to set or reset data    **
**                                    mask registers.                         **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: The data mask reset is successful.              **
**                      E_NOT_OK: The data mask reset is not successful.      **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_TCAN1145_SUPPORTED                   **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_WriteReg                 **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_91002 SRS_Can_01108
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TCAN1145ResetDataMask(
  CONST(uint8, AUTOMATIC) transceiver)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Reset CAN Data Byte registers 0 */
  returnValue = ptrWriteReadReg->WriteReg(transceiver, TCAN1145_DATA_MASK_0_REG,
    TCAN1145_DATA_MASK_Y_DEFAULT_VALUE);

  /* Reset CAN Data Byte registers 1 */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TCAN1145_DATA_MASK_1_REG,
    TCAN1145_DATA_MASK_Y_DEFAULT_VALUE);

  /* Reset CAN Data Byte registers 2 */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TCAN1145_DATA_MASK_2_REG,
    TCAN1145_DATA_MASK_Y_DEFAULT_VALUE);

  /* Reset CAN Data Byte registers 3 */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TCAN1145_DATA_MASK_3_REG,
    TCAN1145_DATA_MASK_Y_DEFAULT_VALUE);

  /* Reset CAN Data Byte registers 4 */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TCAN1145_DATA_MASK_4_REG,
    TCAN1145_DATA_MASK_Y_DEFAULT_VALUE);

  /* Reset CAN Data Byte registers 5 */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TCAN1145_DATA_MASK_5_REG,
    TCAN1145_DATA_MASK_Y_DEFAULT_VALUE);

  /* Reset CAN Data Byte registers 6 */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TCAN1145_DATA_MASK_6_REG,
    TCAN1145_DATA_MASK_Y_DEFAULT_VALUE);

  /* Reset CAN Data Byte registers 7 */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TCAN1145_DATA_MASK_7_REG,
    TCAN1145_DATA_MASK_Y_DEFAULT_VALUE);

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_TCAN1145GetSyserrFlag                          **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to get status of SYSERR flag on TCAN1145 **
**                      device.                                               **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Get status of SYSERR flag is successful.        **
**                      E_NOT_OK: Get status of SYSERR flag is not successful.**
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_TCAN1145_SUPPORTED and               **
**                      STD_ON == CANTRCV_HW_PN_SUPPORTED                     **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_ReadReg                  **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00181 SWS_CanTrcv_00186
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TCAN1145GetSyserrFlag(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(uint8, AUTOMATIC, CANTRCV_APPL_DATA) ptrSyserrFlag)
{
  VAR(uint8, AUTOMATIC) data;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Initialize local variable */
  data = (uint8)CANTRCV_ZERO;

  /* @Trace: CanTrcv_SUD_API_358 */
  /* Read value in Transceiver event status register */
  returnValue = ptrWriteReadReg->ReadReg(transceiver, TCAN1145_INT_3_REG,
    &data);
  if (E_NOT_OK != returnValue)
  {
    /* Get PNFDE flag - bit 5 */
    *ptrSyserrFlag = (boolean)((data & TCAN1145_INT_3_SWERR_BIT) >> CANTRCV_SIX);
  }
  else
  {
    /* Nothing to do */
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_TCAN1145ClearSyserrFlag                        **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to clear status of SYSERR flag on       **
**                      TCAN1145 device.                                       **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Clear status of SYSERR flag successful.         **
**                      E_NOT_OK: Clear status of SYSERR flag not successful. **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_TCAN1145_SUPPORTED and               **
**                      STD_ON == CANTRCV_HW_PN_SUPPORTED                     **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_ReadReg                  **
*******************************************************************************/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TCAN1145ClearSyserrFlag(
  CONST(uint8, AUTOMATIC) transceiver)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  VAR(uint8,AUTOMATIC) data;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  data = (uint8)CANTRCV_ZERO;
  /* @Trace: CanTrcv_SUD_API_320 */
  /* Clear PNFDE flag - bit 5 */
  returnValue = ptrWriteReadReg->ReadReg(transceiver, TCAN1145_INT_1_REG,&data);

  data &= (uint8)(TCAN1145_INT_1_CLEAR_FRAME_OVF_BIT);
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TCAN1145_INT_1_REG,data);

  returnValue = ptrWriteReadReg->ReadReg(transceiver, TCAN1145_CONFIG4_REG,&data);
  data |= (uint8)TCAN1145_CONFIG4_SWCFG_REG_BIT;
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TCAN1145_CONFIG4_REG, data);
  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_TCAN1145ConfigurePartialNetworking             **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to configure partial networking on      **
**                      TCAN1145 device.                                       **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Configure partial networking successful.        **
**                      E_NOT_OK: Configure partial networking not successful.**
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_TCAN1145_SUPPORTED and               **
**                      STD_ON == CANTRCV_HW_PN_SUPPORTED                     **
**                                                                            **
** Remarks            : Global variable(s): CanTrcv_CanTrcvNetwork            **
**                                                                            **
**                      Function(s) invoked: CanTrcv_WriteReg,                **
**                      CanTrcv_ReadReg, CanTrcv_TCAN1145SetDataMask,          **
**                      CanTrcv_TCAN1145ConfigureIdentifierType,               **
**                      CanTrcv_TCAN1145SetPNActivationState                   **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00182 SWS_CanTrcv_00210
*/
static FUNC(Std_ReturnType, CANTRCV_CODE)
  CanTrcv_TCAN1145ConfigurePartialNetworking(
    CONST(uint8, AUTOMATIC) transceiver)
{
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  P2CONST(CanTrcv_PartialNetworkType, AUTOMATIC, CANTRCV_CONST)
    ptrCanTrcvPnNetwork;
  VAR(uint8, AUTOMATIC) data;
  VAR(uint8, AUTOMATIC) pnIndex;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];
  /* Get Parital Network index */
  pnIndex = ptrCanTrcvNetwork->PnNetworkIndex;
  /* Get the pointer to the structure of the requested PN network */
  ptrCanTrcvPnNetwork = &CanTrcv_PartialNetwork[pnIndex];

  /* Configure identifier format and number of data bytes */
  data = (uint8)CANTRCV_ZERO;
  /* @Trace: CanTrcv_SUD_API_321 */
  /* Configure data rate */
  /* polyspace +4 MISRA-C3:18.1 [Justified:Low] "ptrCanTrcvPnNetwork points to an element of CanTrcv_CanTrcvNetwork which is  guaranteed by Generator." */
  /* polyspace +3 MISRA-C3:D4.1 [Justified:Low] "ptrCanTrcvPnNetwork points to an element of CanTrcv_CanTrcvNetwork which is  guaranteed by Generator." */
  /* polyspace +2 RTE:IDP [Justified:Low] "CanTrcv_PartialNetwork is guaranteed by Generator." */
  returnValue = ptrWriteReadReg->ReadReg(transceiver, TCAN1145_CONFIG1_REG,&data);
  data |= (uint8)((ptrCanTrcvPnNetwork->BaudRate)<<CANTRCV_FOUR);
  returnValue = ptrWriteReadReg->WriteReg(transceiver, TCAN1145_CONFIG1_REG, data);

  /* Configure identifier format */
  /* @Trace: CanTrcv_SUD_API_322 */
  returnValue = ptrWriteReadReg->ReadReg(transceiver, TCAN1145_ID_REG3_REG,&data);
  data |= (uint8)(ptrCanTrcvPnNetwork->PnCanIdIsExtended <<TCAN1145_ID_REG3_IDE_SHIFT);
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TCAN1145_ID_REG3_REG, data);
  
  /* Configure identifier format and number of data bytes */
  data = (uint8)CANTRCV_ZERO;
  returnValue = ptrWriteReadReg->ReadReg(transceiver, TCAN1145_ID_MASK_DLC_REG,&data);
  /* Configure partial networking data mask */
  data |= ptrCanTrcvPnNetwork->PnDlcMatchingCondition;
  /* Configure data length code */
  data |= (uint8)(ptrCanTrcvPnNetwork->PnFrameDlc <<CANTRCV_ONE);

  /* @Trace: CanTrcv_SUD_API_323 */
  /* Send request via SPI */
  returnValue |= ptrWriteReadReg->WriteReg(transceiver, TCAN1145_ID_MASK_DLC_REG, data);

  /* @Trace: CanTrcv_SUD_API_324 */
  /* Configure CAN ID and ID mask */
  returnValue |= CanTrcv_TCAN1145ConfigureIdentifierType(transceiver);

  /* @Trace: CanTrcv_SUD_API_325 */
  /* Configure CAN Data Byte registers */
  returnValue |= CanTrcv_TCAN1145SetDataMask(transceiver);

  /* @Trace: CanTrcv_SUD_API_326 */
  /* Read value in CAN control register */
  returnValue |= ptrWriteReadReg->ReadReg(transceiver, TCAN1145_MODE_CNTRL_REG, &data);

  if (E_NOT_OK != returnValue)
  {
    /* Set PNCOK bit in the CAN Control register to confirm all registers are
      configured correctly */
    data |= TCAN1145_MODE_CNTRL_SW_EN;
    returnValue = ptrWriteReadReg->WriteReg(transceiver, TCAN1145_MODE_CNTRL_REG,
      data);
  }
  else
  {
    /* Nothing to do */
  }

  /* @Trace: CanTrcv_SUD_API_327 */
  /* Configure wake uint */
  /* polyspace +2 MISRA2012:10.5 [Justified:Low] "Operation is guaranteed that does not exceed CanTrcv_PNActivationType." */
  returnValue |= CanTrcv_TCAN1145SetPNActivationState(transceiver,
    (CanTrcv_PNActivationType)ptrCanTrcvPnNetwork->PnEnabled);

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_TCAN1145ConfigureIdentifierType                **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to configure Identifier Type on         **
**                      TCAN1145 device.                                       **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Configure Identifier Type successful.           **
**                      E_NOT_OK: Configure Identifier Type not successful.   **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_TCAN1145_SUPPORTED and               **
**                      STD_ON == CANTRCV_HW_PN_SUPPORTED                     **
**                                                                            **
** Remarks            : Global variable(s): CanTrcv_CanTrcvNetwork            **
**                                                                            **
**                      Function(s) invoked: CanTrcv_WriteReg                 **
*******************************************************************************/
static FUNC(Std_ReturnType, CANTRCV_CODE)
  CanTrcv_TCAN1145ConfigureIdentifierType(CONST(uint8, AUTOMATIC) transceiver)
{
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  P2CONST(CanTrcv_PartialNetworkType, AUTOMATIC, CANTRCV_CONST)
    ptrCanTrcvPnNetwork;
  VAR(uint8, AUTOMATIC) data;
  VAR(uint8, AUTOMATIC) pnIndex;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];
  /* Get Parital Network index */
  pnIndex = ptrCanTrcvNetwork->PnNetworkIndex;
  /* Get the pointer to the structure of the requested PN network */
  ptrCanTrcvPnNetwork = &CanTrcv_PartialNetwork[pnIndex];
  data = (uint8)CANTRCV_ZERO;
  /* polyspace -begin MISRA-C3:D4.1 [Justified:Low] "ptrCanTrcvPnNetwork points to an element of CanTrcv_CanTrcvNetwork which is  guaranteed by Generator." */
  /* polyspace +4 MISRA-C3:D4.1 [Justified:Low] "The size of CanTrcv_PartialNetwork is pre-defined, the value of pnIndex is already guaranteed.
   * So, ptrCanTrcvPnNetwork is valid in this case." */
  /* polyspace +2 MISRA-C3:18.1 [Justified:Low] "ptrCanTrcvPnNetwork points to an element of CanTrcv_CanTrcvNetwork which is  guaranteed by Generator." */
  /* polyspace +1 RTE:IDP [Justified:Low] "CanTrcv_PartialNetwork is guaranteed by Generator." */
  if (CANTRCV_TRUE != ptrCanTrcvPnNetwork->PnCanIdIsExtended)
  {
    /* @Trace: CanTrcv_SUD_API_328 */
    /* Bits ID10 to ID6 of the standard frame format */
    returnValue = ptrWriteReadReg->ReadReg(transceiver, TCAN1145_ID_REG3_REG, &data);
    data &= (uint8)TCAN1145_ID_REG3_REG_BITMASK;
    data |= (uint8)((ptrCanTrcvPnNetwork->PnFrameCanId &
      (uint16) 0x07C0) >> 6);
    returnValue |= ptrWriteReadReg->WriteReg(transceiver, TCAN1145_ID_REG3_REG, data);

    /* Bits ID5 to ID0 of the standard frame format */
    returnValue |= ptrWriteReadReg->ReadReg(transceiver, TCAN1145_ID_REG4_REG, &data);
    data &= (uint8)TCAN1145_ID_REG4_REG_BITMASK;
    data |= (uint8)((ptrCanTrcvPnNetwork->PnFrameCanId &
      (uint16)0x003F) <<2);
    returnValue |= ptrWriteReadReg->WriteReg(transceiver, TCAN1145_ID_REG4_REG, data);

    /* ID mask bits 10 to 3 of standard frame format */
    data = (uint8)((ptrCanTrcvPnNetwork->PnFrameCanIdMask &
      (uint16)0x07F8) >> 3);
    returnValue = ptrWriteReadReg->WriteReg(transceiver, TCAN1145_ID_MASK4_REG,
      data);

    /* ID mask bits 2 to 0 of standard frame format */
    returnValue |= ptrWriteReadReg->ReadReg(transceiver, TCAN1145_ID_MASK_DLC_REG, &data);
    data &= (uint8)TCAN1145_ID_MASK_DLC_BITMASK;
    data |= (uint8)((ptrCanTrcvPnNetwork->PnFrameCanIdMask &
      (uint16)0x0007) << 5);
    returnValue |= ptrWriteReadReg->WriteReg(transceiver, TCAN1145_ID_MASK_DLC_REG,
      data);
  }
  /* polyspace -end MISRA-C3:D4.1 [Justified:Low] "ptrCanTrcvPnNetwork points to an element of CanTrcv_CanTrcvNetwork which is  guaranteed by Generator." */
  else
  {
    /* @Trace: CanTrcv_SUD_API_329 */
    /* Bits ID28 to ID24 of the extended frame format */
    returnValue = ptrWriteReadReg->ReadReg(transceiver, TCAN1145_ID_REG3_REG, &data);
    data &= (uint8)TCAN1145_ID_REG3_REG_BITMASK;
    data |= (uint8)((ptrCanTrcvPnNetwork->PnFrameCanId &
      (uint32)(0x1F000000U)) >> 24);
    returnValue |= ptrWriteReadReg->WriteReg(transceiver, TCAN1145_ID_REG3_REG, data);

    /* Bits ID23 to ID18 of the extended frame format */
    returnValue |= ptrWriteReadReg->ReadReg(transceiver, TCAN1145_ID_REG4_REG, &data);
    data &= (uint8)TCAN1145_ID_REG4_REG_BITMASK;
    data |= (uint8)((ptrCanTrcvPnNetwork->PnFrameCanId &
      (uint32)(0x00FC0000U))>> 16);
    returnValue |= ptrWriteReadReg->WriteReg(transceiver, TCAN1145_ID_REG4_REG, data);

    /* Bits ID17 to ID10 of the extended frame format */
    data = (uint8)((ptrCanTrcvPnNetwork->PnFrameCanId &
      (uint32)(0x0003FC00U) >> 10));
    returnValue |= ptrWriteReadReg->WriteReg(transceiver, TCAN1145_ID_REG1_REG, data);

    /* Bits ID9 to ID2 of the extended frame format */
    data = (uint8)((ptrCanTrcvPnNetwork->PnFrameCanId &
      (uint32)(0x000003FCU) >> 2));
    returnValue |= ptrWriteReadReg->WriteReg(transceiver, TCAN1145_ID_REG2_REG, data);

    /* Bits ID1 to ID0 of the extended frame format */
    returnValue = ptrWriteReadReg->ReadReg(transceiver, TCAN1145_ID_REG3_REG, &data);
    data &= (uint8)TCAN1145_ID_REG3_REG_EX_ID_BITMASK;
     data |= (uint8)((ptrCanTrcvPnNetwork->PnFrameCanId &
      (uint32)(0x00000003U)<<6));
    returnValue |= ptrWriteReadReg->WriteReg(transceiver, TCAN1145_ID_REG3_REG, data);

    /* @Trace: CanTrcv_SUD_API_330 */
    if (E_NOT_OK != returnValue)
    {
      /* Bits ID mask bits 28 to 21 of extended frame format */
      data = (uint8)((ptrCanTrcvPnNetwork->PnFrameCanIdMask &
         (uint32)(0x1F700000U) >> 21));
      returnValue = ptrWriteReadReg->WriteReg(transceiver, TCAN1145_ID_MASK4_REG,
        data);

      /* Bits ID mask bits 20 to 18 of extended frame format */
      returnValue = ptrWriteReadReg->ReadReg(transceiver, TCAN1145_ID_MASK_DLC_REG, &data);
      data &= (uint8)TCAN1145_ID_MASK_DLC_BITMASK;
      data |= (uint8)((ptrCanTrcvPnNetwork->PnFrameCanIdMask &
         (uint32)(0x001C0000U)  >> 13));
      returnValue |= ptrWriteReadReg->WriteReg(transceiver, TCAN1145_ID_MASK_DLC_REG,
        data);

      /* Bits ID mask bits 17 to 16 of extended frame format */
      data = (uint8)((ptrCanTrcvPnNetwork->PnFrameCanIdMask &
         (uint32)(0x00030000U) >> 16));
      returnValue |= ptrWriteReadReg->WriteReg(transceiver, TCAN1145_ID_MASK1_REG,
        data);

      /* Bits ID mask bits 15 to 8 of extended frame format */
      data = (uint8)((ptrCanTrcvPnNetwork->PnFrameCanIdMask &
         (uint32)(0x0000FF00) >> 8));
      returnValue |= ptrWriteReadReg->WriteReg(transceiver, TCAN1145_ID_MASK2_REG,
        data);
        /* Bits ID mask bits 7 to 0 of extended frame format */
      data = (uint8)(ptrCanTrcvPnNetwork->PnFrameCanIdMask &
         (uint32)(0x000000FF));
      returnValue |= ptrWriteReadReg->WriteReg(transceiver, TCAN1145_ID_MASK3_REG,
        data);
    }
    else
    {
      /* Nothing to do */
    }
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_TCAN1145GetTrcvSystemData                      **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to get system data on TCAN1145 device.   **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : ptrSystemData - Store system data of TCAN1145 device.  **
**                                                                            **
** Return parameter   : E_OK: Get system data is successful.                  **
**                      E_NOT_OK: Get system data is not successful.          **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_TCAN1145_SUPPORTED and               **
**                      STD_ON == CANTRCV_HW_PN_SUPPORTED                     **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_ReadReg                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00189
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TCAN1145GetTrcvSystemData(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(uint32, AUTOMATIC, CANTRCV_APPL_DATA) ptrSystemData)
{
  VAR(uint8, AUTOMATIC) data;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Initialize local variable */
  data = (uint8)CANTRCV_ZERO;

  /* @Trace: CanTrcv_SUD_API_340 */
  /* Read value in Transceiver status register */
  returnValue = ptrWriteReadReg->ReadReg(transceiver, TCAN1145_INT_3_REG, &data);
  if (E_NOT_OK != returnValue)
  {
    /* @Trace: CanTrcv_SUD_API_180 */
    /* polyspace +1 MISRA2012:D4.14 [Justified:Low] "Pointer ptrSystemData is checked NULL by DET." */
    *ptrSystemData = (uint32)data;
  }
  else
  {
    /* Nothing to do */
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_TCAN1145ReadTrcvTimeoutFlag                    **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to get time out flag on TCAN1145 device. **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : ptrFlagState - Store time out flag of TCAN1145 device. **
**                                                                            **
** Return parameter   : E_OK: Get time out flag is successful.                **
**                      E_NOT_OK: Get time out flag is not successful.        **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_TCAN1145_SUPPORTED and               **
**                      STD_ON == CANTRCV_HW_PN_SUPPORTED                     **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_ReadReg                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00189 SWS_CanTrcv_00211
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TCAN1145ReadTrcvTimeoutFlag(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(CanTrcv_TrcvFlagStateType, AUTOMATIC, CANTRCV_APPL_DATA) ptrFlagState)
{
  VAR(uint8, AUTOMATIC) data;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Initialize local variable */
  data = (uint8)CANTRCV_ZERO;

  /* @Trace: CanTrcv_SUD_API_342 */
  /* Read value in Transceiver event status register */
  returnValue = ptrWriteReadReg->ReadReg(transceiver, TCAN1145_INT_1_REG,
    &data);
  if (E_NOT_OK != returnValue)
  {
    /* @Trace: CanTrcv_SUD_API_343 */
    /* Get value of bit CANSLNT - bit 2 */
    /* polyspace +3 MISRA2012:D4.14 [Justified:Low] "Pointer ptrFlagState is checked NULL by DET." */
    /* polyspace +2 MISRA2012:10.5 [Justified:Low] "Operation is guaranteed that does not exceed CanTrcv_TrcvFlagStateType." */
    *ptrFlagState = (CanTrcv_TrcvFlagStateType)(uint8)((uint8)(data &
      TCAN1145_INT_1_CANSLNT) >> CANTRCV_TWO);
  }
  else
  {
    /* Nothing to do */
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_TCAN1145ClearTrcvTimeoutFlag                   **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to clear time out flag on TCAN1145       **
**                      device.                                               **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Clear time out flag is successful.              **
**                      E_NOT_OK: Clear time out flag is not successful.      **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_TCAN1145_SUPPORTED and               **
**                      STD_ON == CANTRCV_HW_PN_SUPPORTED                     **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_WriteReg                 **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00216
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TCAN1145ClearTrcvTimeoutFlag(
  CONST(uint8, AUTOMATIC) transceiver)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  VAR(uint8,AUTOMATIC) data;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  data = (uint8)CANTRCV_ZERO;
  /* @Trace: CanTrcv_SUD_API_341 */
  /* Clear bit CBS - bit 4 */
   returnValue = ptrWriteReadReg->ReadReg(transceiver, TCAN1145_INT_1_REG,
    &data);
  if (E_NOT_OK != returnValue)
  {
  data &= (uint8)(~TCAN1145_INT_1_CANSLNT);
  returnValue = ptrWriteReadReg->WriteReg(transceiver, TCAN1145_INT_1_REG,
    data);
  }
   else
  {
    /* Nothing to do */
  }


  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_TCAN1145ReadTrcvSilenceFlag                    **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to read silence flag on TCAN1145         **
**                      device.                                               **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : ptrFlagState - Store state of silence flag.           **
**                                                                            **
** Return parameter   : E_OK: Read status of silence flag is successful.      **
**                      E_NOT_OK: Read silence flag is not successful.        **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_TCAN1145_SUPPORTED and               **
**                      STD_ON == CANTRCV_HW_PN_SUPPORTED                     **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_ReadReg                  **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00217 SWS_CanTrcv_00211
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TCAN1145ReadTrcvSilenceFlag(
  CONST(uint8, AUTOMATIC) transceiver,
  P2VAR(CanTrcv_TrcvFlagStateType, AUTOMATIC, CANTRCV_APPL_DATA) ptrFlagState)
{
  VAR(uint8, AUTOMATIC) data;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Initialize local variable */
  data = (uint8)CANTRCV_ZERO;

  /* Read value in Transceiver status register */
  returnValue = ptrWriteReadReg->ReadReg(transceiver, TCAN1145_INT_1_REG, &data);
  if (E_NOT_OK != returnValue)
  {
    /* Get value bit CBSS - bit 3 */
    /* polyspace +3 MISRA2012:D4.14 [Justified:Low] "Pointer ptrFlagState is checked NULL by DET." */
    /* polyspace +2 MISRA2012:10.5 [Justified:Low] "Operation is guaranteed that does not exceed CanTrcv_TrcvFlagStateType." */
    *ptrFlagState = (CanTrcv_TrcvFlagStateType)(uint8)(
      (data & TCAN1145_INT_1_CANSLNT) >> CANTRCV_TWO);
  }
  else
  {
    /* Nothing to do */
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_TCAN1145SetPNActivationState                   **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to set state of partial networking on   **
**                      TCAN1145 device.                                       **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                      activationState - PN state.
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Set PN state success.                           **
**                      E_NOT_OK: Set PN not success.                         **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_TCAN1145_SUPPORTED and               **
**                      STD_ON == CANTRCV_HW_PN_SUPPORTED                     **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_WriteReg                 **
**                      CanTrcv_ReadReg                                       **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00221 SWS_CanTrcv_00222
  SWS_CanTrcv_00210
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TCAN1145SetPNActivationState(
  CONST(uint8, AUTOMATIC) transceiver,
  CONST(CanTrcv_PNActivationType, AUTOMATIC) activationState)
{
  VAR(uint8, AUTOMATIC) data;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Initialize local variable */
  data = (uint8)CANTRCV_ZERO;

  /* @Trace: CanTrcv_SUD_API_360*/
  /* Read value in CAN control register */
  returnValue = ptrWriteReadReg->ReadReg(transceiver, TCAN1145_CONFIG4_REG, &data);
  if (E_NOT_OK != returnValue)
  {
    data |= (uint8)TCAN1145_CONFIG4_SWCFG_REG_BIT;
    returnValue = ptrWriteReadReg->WriteReg(transceiver, TCAN1145_CONFIG4_REG, (uint8)data);
  }
  else
  {
    /* Nothing to do */
  }

   returnValue = ptrWriteReadReg->ReadReg(transceiver, TCAN1145_MODE_CNTRL_REG, &data);
  if (E_NOT_OK != returnValue)
  {
    data &= TCAN1145_MODE_CNTRL_SW_EN_CLEAR;
    data |= (uint8)activationState << TCAN1145_MODE_CNTRL_SW_EN_SHIFT;
    returnValue = ptrWriteReadReg->WriteReg(transceiver, TCAN1145_MODE_CNTRL_REG, (uint8)data);
  }
  else
  {
    /* Nothing to do */
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_TCAN1145ClearTrcvWufFlag                       **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to clear transceiver wake up frame flag **
**                      on TCAN1145 device.                                    **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Clear wake up frame flag success.               **
**                      E_NOT_OK: Clear wake up frame flag not success.       **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_TCAN1145_SUPPORTED and               **
**                      STD_ON == CANTRCV_HW_PN_SUPPORTED                     **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_WriteReg                 **
**                      CanTrcv_ReadReg                                       **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00194
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TCAN1145ClearTrcvWufFlag(
  CONST(uint8, AUTOMATIC) transceiver)
{
  VAR(uint8, AUTOMATIC) data;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Initialize local variable */
  data = (uint8)CANTRCV_ZERO;

  /* @Trace: CanTrcv_SUD_API_345 */
  /* Check WUF flag is exits */
  /* Read value in CAN control register */
  returnValue = ptrWriteReadReg->ReadReg(transceiver, TCAN1145_MODE_CNTRL_REG, &data);

  if (E_NOT_OK != returnValue)
  {
    /* Get status of CAN selective wake-up */
    data &= TCAN1145_MODE_CNTRL_SW_EN;

    if (TCAN1145_MODE_CNTRL_SW_EN == data)
    {
      /* @Trace: CanTrcv_SUD_API_346 */
      /* Read value in Transceiver status register */
      data = (uint8)CANTRCV_ZERO;
      returnValue = ptrWriteReadReg->ReadReg(transceiver, TCAN1145_INT_1_REG,
        &data);
      if (E_NOT_OK != returnValue)
      {
        /* @Trace: CanTrcv_SUD_API_347 */
        /* Clear wake up flag - bit CW */
        data &= TCAN1145_INT_1_CANINT_CLEAR_BIT;
        returnValue = ptrWriteReadReg->WriteReg(transceiver,
          TCAN1145_INT_1_REG, data);
      }
      else
      {
        /* Nothing to do */
      }
    }
    else
    {
      /* CAN selective wake-up is not enable, so do nothing */
    }
  }
  else
  {
    /* Nothing to do */
  }

  return returnValue;
}
#endif /* (STD_ON == CANTRCV_HW_PN_SUPPORTED) */

#if (STD_ON == CANTRCV_WAKEUP_SUPPORTED)
/*******************************************************************************
** Function Name      : CanTrcv_TCAN1145CheckWakeFlag                          **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to check wake up flag for TCAN1145 device**
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN transceiver to which API call has   **
**                                    to be applied.                          **
**                      ptrCanTrcvNetwork - Pointer point to Can Transceiver  **
**                                          configuration.                    **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: The request for checking the wakeup flag has    **
**                            been accepted.                                  **
**                      E_NOT_OK: The request for checking the wakeup flag    **
**                                has not been accepted.                      **
**                                                                            **
** Preconditions      : CANTRCV_TCAN1145_SUPPORTED == STD_ON and               **
**                      CANTRCV_WAKEUP_SUPPORTED == STD_ON                    **
**                                                                            **
** Remarks            : Global variable(s): None                              **
**                                                                            **
**                      Function(s) invoked: CanTrcv_ReadReg,                 **
**                      CanTrcv_WriteReg, EcuM_SetWakeupEvent                 **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00223 SWS_CanTrcv_00086
*/
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_TCAN1145CheckWakeFlag(
  CONST(uint8, AUTOMATIC) transceiver,
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork)
{
  VAR(uint8, AUTOMATIC) data;
  VAR(uint8, AUTOMATIC) wpeFlag;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* Initialize local variable */
  data = (uint8)CANTRCV_ZERO;

  /* @Trace: CanTrcv_SUD_API_354 */
  /* Read value in Global event status register */
  returnValue = ptrWriteReadReg->ReadReg(transceiver, TCAN1145_INT_1_REG,
    &data);
  if (E_NOT_OK != returnValue)
  {
    /* Get WPE flag - bit 3 */
    wpeFlag = (data & TCAN1145_INT_1_CANINT_REG);

    /* Check status wake up by pin */
    if (TCAN1145_INT_1_CANINT_REG == wpeFlag)
    {
      /* @Trace: CanTrcv_SUD_API_355 */
      /* Notify to EcuM wake up source */
      EcuM_SetWakeupEvent(ptrCanTrcvNetwork->WakeupSource);
    }
    else
    {
      /* Nothing to do */
    }
  }
  else
  {
    /* Nothing to do */
  }

  return returnValue;
}

/*******************************************************************************
** Function Name      : CanTrcv_TCAN1145MainFunction                          **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to set and perform wake up events on    **
**                      TCAN1145 device.                                      **
**                                                                            **
** Sync/Async         : N/A                                                   **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : CANTRCV_TCAN1145_SUPPORTED == STD_ON and              ** 
**                      CANTRCV_WAKEUP_SUPPORTED == STD_ON                    **
**                                                                            **
** Remarks            : Global variable(s): CanTrcv_WakeUpReason,             **
**                      CanTrcv_WakeupMode, CanTrcv_WakeupFlagIndication,     **
**                      CanTrcv_WakeupPending                                 **
**                                                                            **
**                      Function(s) invoked: CanTrcv_ReadReg                  **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00112 SRS_BSW_00424
*/
static FUNC(void, CANTRCV_CODE) CanTrcv_TCAN1145MainFunction(
  CONST(uint8, AUTOMATIC) transceiver)
{
  VAR(uint8, AUTOMATIC) data;
  VAR(uint8, AUTOMATIC) wakeFlag;
  VAR(uint8, AUTOMATIC) returnStatus;
  VAR(boolean, AUTOMATIC) syserrFlag;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  /* @Trace: CanTrcv_SUD_API_348 */
  /* Initialize local variable */
  data = (uint8)CANTRCV_ZERO;
  wakeFlag = (uint8)CANTRCV_ZERO;
  /* Get the pointer to the structure of first network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];

  /* Check wake up by pin */
  /* Read value in Global event status register */
  returnStatus = ptrWriteReadReg->ReadReg(transceiver, TCAN1145_WAKE_PIN_CONFIG_REG,
    &data);
  if (E_NOT_OK != returnStatus)
  {
    data &= TCAN1145_WAKE_PIN_MASK;
    if ( (CANTRCV_ZERO != data) &&(data !=TCAN1145_WAKE_PIN_MASK))
    {
      /* @Trace: CanTrcv_SUD_API_349 */
      wakeFlag |= data;
      /* Set wake up reason as CANTRCV_WU_BY_BUS */
      CanTrcv_WakeUpReason[transceiver] = CANTRCV_WU_BY_PIN;
    }
    else
    {
      /* Nothing to do */
    }
  }
  else
  {
    /* Nothing to do */
  }

  /* @Trace: CanTrcv_SUD_API_350 */
  /* Check wake up by bus */
  /* Read value in Transceiver event status register */
  returnStatus = ptrWriteReadReg->ReadReg(transceiver, TCAN1145_INT_1_REG,
    &data);
  if (E_NOT_OK != returnStatus)
  {
    syserrFlag = (boolean)((data & TCAN1145_INT_1_FRAME_OVF_BIT) >> CANTRCV_FOUR);
    data &= TCAN1145_INT_1_CANINT_REG;
    if (TCAN1145_INT_1_CANINT_REG == data)
    {
      /* @Trace: CanTrcv_SUD_API_351 */
      wakeFlag |= data;
      /* Set wake up reason as CANTRCV_WU_BY_BUS */
      CanTrcv_WakeUpReason[transceiver] = CANTRCV_WU_BY_BUS;
    }
    else if (syserrFlag == CANTRCV_TRUE)
    {
      #if (STD_ON == CANTRCV_WAKEUP_SUPPORTED)
      /* Set wake up reason */
      CanTrcv_WakeUpReason[transceiver] = CANTRCV_WU_BY_SYSERR;
      #endif /* (STD_ON == CANTRCV_WAKEUP_SUPPORTED) */
      /* If the SYSERR flag is set, wakeup shall be reported to EcuM
        through API EcuM_SetWakeupEvent */
      #if (STD_ON == CANTRCV_HW_PN_SUPPORTED)
      EcuM_SetWakeupEvent(ptrCanTrcvNetwork->SyserrWakeupSource);
      /* Clear SYSERR flag */
      (void)CanTrcv_IntClearSyserrFlag(transceiver);
      #endif
    }
    else 
    {
      /* Nothing to do */
    }
  }
  else
  {
    CANTRCV_UNUSED_VAL(syserrFlag);
  }

  if ((uint8)CANTRCV_ZERO != wakeFlag)
  {
    /* Check state wake up of CAN Transceiver */
    if (CANTRCV_WUMODE_ENABLE == CanTrcv_WakeupMode[transceiver])
    {
      /* @Trace: CanTrcv_SUD_API_352 */
      /* Set wake up status */
      CanTrcv_WakeupFlagIndication[transceiver] = CANTRCV_WAKE_UP_OCCURRED;
    }
    else if (CANTRCV_WUMODE_DISABLE == CanTrcv_WakeupMode[transceiver])
    {
      /* @Trace: CanTrcv_SUD_API_353 */
      /* Store the pending wakeup event */
      CanTrcv_WakeupPending[transceiver] = CANTRCV_WAKEUP_PENDING;
    }
    else
    {
      /* Nothing to do */
    }
  }
  else
  {
    /* Nothing to do */
  }
}
#endif /* (STD_ON == CANTRCV_WAKEUP_SUPPORTED) */

#endif /* (STD_ON == CANTRCV_TCAN1145_SUPPORTED) */


#if (STD_ON == CANTRCV_WAKEUP_SUPPORTED)
/*******************************************************************************
** Function Name        : CanTrcv_IntCheckWakeupInit                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used to detect valid wakeup at     **
**                        initialization.                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : transceiver - Transceiver ID.                       **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : CANTRCV_WAKEUP_SUPPORTED is STD_ON                  **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        CanTrcv_CanTrcvNetwork,                             **
**                        CanTrcv_WakeUpReason                                **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Dio_ReadChannel,                                    **
**                        EcuM_SetWakeupEvent,                                **
**                        CanTrcv_SetNormalMode                               **
*******************************************************************************/
/* @Trace: SWS_CanTrcv_00167 SWS_CanTrcv_00086
*/
FUNC(void, CANTRCV_CODE) CanTrcv_IntCheckWakeupInit(
  CONST(uint8, AUTOMATIC) transceiver)
{
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  #if (STD_ON == CANTRCV_HW_SUPPORT_WAKEUP_USED_STB_EN_PIN)
  VAR(Dio_LevelType, AUTOMATIC) retValPin2;
  #endif /* (STD_ON == CANTRCV_HW_SUPPORT_WAKEUP_USED_STB_EN_PIN) */

  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];

  VAR(Dio_LevelType, AUTOMATIC) retValPin1;
  VAR(Dio_LevelType, AUTOMATIC) retValPin3;

  /* Set default wake up reason */
  CanTrcv_WakeUpReason[transceiver] = CANTRCV_WU_POWER_ON;
  /* polyspace +8 DEFECT:DEAD_CODE [Not a defect:Justified] "It's depend on the configuration of CanTrcv. No impact" */
  /* Check hardware device type */
  #if (STD_ON == CANTRCV_HW_SUPPORT_WAKEUP_USED_STB_EN_PIN)
  if ((CANTRCV_TJA1041 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1041A == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1043 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1463 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1054 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1054A == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1055 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE6251G == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE62513G == ptrCanTrcvNetwork->CanTrcvHwDev))
  {
    /* @Trace: CanTrcv_SUD_API_013 */
    /* Read value of ERR pin */
    retValPin3 = Dio_ReadChannel(ptrCanTrcvNetwork->SelectPin3);
    /* Check status of ERR pin */
    if (STD_LOW == retValPin3)
    {
      /* Read value of STB pin */
      retValPin1 = Dio_ReadChannel(ptrCanTrcvNetwork->SelectPin1);
      /* Read value of EN pin */
      retValPin2 = Dio_ReadChannel(ptrCanTrcvNetwork->SelectPin2);
      /* Check current mode of Can Transceiver is in Standby mode or not */
      if ((STD_LOW == retValPin1) && (STD_LOW == retValPin2))
      {
        /* Set wake up reason */
        CanTrcv_WakeUpReason[transceiver] = CANTRCV_WU_BY_BUS;
        /* Reporting to EcuM */
        EcuM_SetWakeupEvent(ptrCanTrcvNetwork->WakeupSource);
      }
      else
      {
        /* Nothing to do */
      }
      /* Update default mode as Normal, it will clear wake up flag in case
        CanTrcvInitState is STANDBY/SLEEP */
      (void)CanTrcv_SetNormalMode(transceiver);
    }
    else
    {
      /* Nothing to do */
    }
  }
  #endif /* (STD_ON == CANTRCV_HW_SUPPORT_WAKEUP_USED_STB_EN_PIN) */
  /* polyspace +10 RTE:UNR [Not a defect:Low] "It depends on the configuration of CanTrcv, No impact" */
  #if (STD_OFF == CANTRCV_ALL_HW_SUPPORT_WAKEUP_USED_STB_PIN)
  if ((CANTRCV_NCV7342 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1040 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1042 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1057 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TJA1044 == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE6251DS == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE7250G == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE7250LE == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE9250SJ == ptrCanTrcvNetwork->CanTrcvHwDev) ||
    (CANTRCV_TLE9251VSJ == ptrCanTrcvNetwork->CanTrcvHwDev))
  #endif /* (STD_OFF == CANTRCV_ALL_HW_SUPPORT_WAKEUP_USED_STB_PIN) */
  {
    /* @Trace: CanTrcv_SUD_API_014 */
    /* Read value of ERR pin */
    retValPin3 = Dio_ReadChannel(ptrCanTrcvNetwork->SelectPin3);
    /* Check status of ERR pin */
    if (STD_LOW == retValPin3)
    {
      /* Read value of STB pin */
      retValPin1 = Dio_ReadChannel(ptrCanTrcvNetwork->SelectPin1);
      /* Check current mode of Can Transceiver is in Standby mode or not */
      if (STD_HIGH == retValPin1)
      {
        /* Set wake up reason */
        CanTrcv_WakeUpReason[transceiver] = CANTRCV_WU_BY_BUS;
        /* Reporting to EcuM */
        EcuM_SetWakeupEvent(ptrCanTrcvNetwork->WakeupSource);
      }
      else
      {
        /* Nothing to do */
      }
    }
    else
    {
      /* Nothing to do */
    }
  }
  CANTRCV_UNUSED_VAL(retValPin1);
  CANTRCV_UNUSED_VAL(retValPin3);
}
#endif /* (STD_ON == CANTRCV_WAKEUP_SUPPORTED) */

/*******************************************************************************
** Function Name        : CanTrcv_SetNormalMode_ArisuCan                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service initiates the transition to the Normal **
**                        operating mode with complete functionality.         **
**                                                                            **
** Sync/Async           : None                                                **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : transceiver - Transceiver ID.                       **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Can Transceiver driver must be initialized.         **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        CanTrcv_CanTrcvNetwork                              **
**                                                                            **
**                        Function(s) invoked :                               **
**                        CanTrcv_IntArisuCan_SetMode,                        **
**                        CanTrcv_IntArisuCan_RequestCanMode,                 **
**                        CanTrcv_ArisuCan_CheckCanMode                       **
*******************************************************************************/
#if (STD_ON == CANTRCV_ARISUCAN_SUPPORTED)
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetNormalMode_ArisuCan(
  CONST(uint8, AUTOMATIC) transceiver)
{
  VAR(Std_ReturnType, AUTOMATIC) returnStatus;
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  VAR(CanTrcv_TrcvModeType, AUTOMATIC) canTrcvMode;

  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];
  /* Initialize return value */
  returnStatus = E_OK;

  /* @Trace: CanTrcv_SUD_API_113 */
  SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA();

  if (ARISUCAN_SBCMODE_NORMAL != ArisuCan_SBCModeSts)
  {
    (void)CanTrcv_IntArisuCan_SetMode(ARISUCAN_SBCMODE_NORMAL);
  }
  else
  {
    /* Nothing to do */
  }

  /* Set ArisuCan SBC mode */
  CanTrcv_IntArisuCan_RequestCanMode(
    ptrCanTrcvNetwork->CanTrcvHwDev, ARISUCAN_SBCMODE_NORMAL);

  /* Check ARISU-CAN CanTrcv Mode */
  canTrcvMode = CanTrcv_ArisuCan_CheckCanMode(
    ptrCanTrcvNetwork->CanTrcvHwDev, ARISUCAN_SBCMODE_NORMAL);

  if (CANTRCV_TRCVMODE_NORMAL != canTrcvMode)
  {
    returnStatus = E_NOT_OK;
  }
  else
  {
    /* Nothing to do */
  }
  SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA();
  return(returnStatus);
}
#endif /* STD_ON == CANTRCV_ARISUCAN_SUPPORTED */
/*******************************************************************************
** Function Name        : CanTrcv_SetNormalMode_XJA11XX                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service initiates the transition to the Normal **
**                        operating mode with complete functionality.         **
**                                                                            **
** Sync/Async           : None                                                **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : transceiver - Transceiver ID.                       **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Can Transceiver driver must be initialized.         **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        CanTrcv_CanTrcvNetwork                              **
**                                                                            **
**                        Function(s) invoked :                               **
**                        CanTrcv_XJA11XXGetModeControl,                      **
**                        CanTrcv_XJA11XXSetModeControl,                      **
**                        CanTrcv_XJA11XXGetModeControl                       **
*******************************************************************************/
#if (STD_ON == CANTRCV_XJA11XX_SUPPORTED)
FUNC(Std_ReturnType, CANTRCV_CODE)CanTrcv_SetNormalMode_XJA11XX(
  CONST(uint8, AUTOMATIC) transceiver)
{
  VAR(Std_ReturnType, AUTOMATIC) returnStatus;
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  VAR(CanTrcv_TrcvModeType, AUTOMATIC) canTrcvMode;

  /* Initialize local variable */
  canTrcvMode = CANTRCV_TRCVMODE_NORMAL;
  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];

  /* @Trace: CanTrcv_SUD_API_114 */
  SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA();
  /* Check Transceiver is Normal Mode */
  returnStatus = CanTrcv_XJA11XXGetModeControl(transceiver, &canTrcvMode);
  if ((E_NOT_OK != returnStatus) && (CANTRCV_TRCVMODE_NORMAL != canTrcvMode))
  {
    /* Set Mode Control as Normal Mode */
    returnStatus = CanTrcv_XJA11XXSetModeControl(transceiver,
      XJA11XX_NORMAL_MODE);
    /* Get current Mode Control */
    returnStatus |= CanTrcv_XJA11XXGetModeControl(transceiver, &canTrcvMode);
    if (CANTRCV_TRCVMODE_NORMAL != canTrcvMode)
    {
      returnStatus = E_NOT_OK;
    }
    else
    {
      /* Nothing to do */
    }
  }
  else
  {
    /* Nothing to do */
  }

  if (E_NOT_OK != returnStatus)
  {
    /* Set Can Mode */
    returnStatus = CanTrcv_XJA11XXSetCanMode(transceiver,
      ptrCanTrcvNetwork->XJA11XXCanMode);
  }
  else
  {
    /* Nothing to do */
  }
  SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA();
  return(returnStatus);
}
#endif /* STD_ON == CANTRCV_XJA11XX_SUPPORTED */

/*******************************************************************************
** Function Name        : CanTrcv_SetNormalMode_TLE9255W                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service initiates the transition to the Normal **
**                        operating mode with complete functionality.         **
**                                                                            **
** Sync/Async           : None                                                **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : transceiver - Transceiver ID.                       **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Can Transceiver driver must be initialized.         **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        CanTrcv_CanTrcvNetwork                              **
**                                                                            **
**                        Function(s) invoked :                               **
**                        CanTrcv_TLE9255WSetModeControl,                     **
**                        CanTrcv_TLE9255WGetModeControl                      **
*******************************************************************************/
#if (STD_ON == CANTRCV_TLE9255W_SUPPORTED)
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetNormalMode_TLE9255W(
  CONST(uint8, AUTOMATIC) transceiver)
{
  VAR(Std_ReturnType, AUTOMATIC) returnStatus;
  VAR(CanTrcv_TrcvModeType, AUTOMATIC) canTrcvMode;

  /* Initialize local variable */
  canTrcvMode = CANTRCV_TRCVMODE_NORMAL;

  /* @Trace: CanTrcv_SUD_API_115 */
  SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA();
  /* Set Mode Control as Normal Mode */
  returnStatus = CanTrcv_TLE9255WSetModeControl(transceiver,
    TLE9255W_NORMAL_MODE);
  /* Get current Mode Control */
  returnStatus |= CanTrcv_TLE9255WGetModeControl(transceiver, &canTrcvMode);
  if (CANTRCV_TRCVMODE_NORMAL != canTrcvMode)
  {
    returnStatus = E_NOT_OK;
  }
  else
  {
    /* Nothing to do */
  }
  SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA();

  return(returnStatus);
}
#endif /* STD_ON == CANTRCV_TLE9255W_SUPPORTED */

/*******************************************************************************
** Function Name        : CanTrcv_SetNormalMode_TCAN1145                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service initiates the transition to the Normal **
**                        operating mode with complete functionality.         **
**                                                                            **
** Sync/Async           : None                                                **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : transceiver - Transceiver ID.                       **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Can Transceiver driver must be initialized.         **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        CanTrcv_CanTrcvNetwork                              **
**                                                                            **
**                        Function(s) invoked :                               **
**                        CanTrcv_TCAN1145GetModeControl,                      **
**                        CanTrcv_TCAN1145SetModeControl,                      **
**                        CanTrcv_TCAN1145GetModeControl                       **
*******************************************************************************/
#if (STD_ON == CANTRCV_TCAN1145_SUPPORTED)
FUNC(Std_ReturnType, CANTRCV_CODE)CanTrcv_SetNormalMode_TCAN1145(
  CONST(uint8, AUTOMATIC) transceiver)
{
  VAR(Std_ReturnType, AUTOMATIC) returnStatus;
  VAR(CanTrcv_TrcvModeType, AUTOMATIC) canTrcvMode;

  /* Initialize local variable */
  canTrcvMode = CANTRCV_TRCVMODE_NORMAL;


  /* @Trace: CanTrcv_SUD_API_338 */
  SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA();
  /* Check Transceiver is Normal Mode */
  returnStatus = CanTrcv_TCAN1145GetModeControl(transceiver, &canTrcvMode);
  if ((E_NOT_OK != returnStatus) && (CANTRCV_TRCVMODE_NORMAL != canTrcvMode))
  {
    /* Set Mode Control as Normal Mode */
    returnStatus = CanTrcv_TCAN1145SetModeControl(transceiver,
      TCAN1145_NORMAL_MODE);
    /* Get current Mode Control */
    returnStatus |= CanTrcv_TCAN1145GetModeControl(transceiver, &canTrcvMode);
    if (CANTRCV_TRCVMODE_NORMAL != canTrcvMode)
    {
      returnStatus = E_NOT_OK;
    }
    else
    {
      /* Nothing to do */
    }
  }
  else
  {
    /* Nothing to do */
  }

  if (E_NOT_OK != returnStatus)
  {
    /* Set Can Mode */
    //returnStatus = CanTrcv_TCAN1145SetCanMode(transceiver,
    //  ptrCanTrcvNetwork->TCAN1145CanMode);
  }
  else
  {
    /* Nothing to do */
  }
  SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA();
  return(returnStatus);
}
#endif /* STD_ON == CANTRCV_TCAN1145_SUPPORTED */

/*******************************************************************************
** Function Name        : CanTrcv_SetNormalMode_TCAN1043A                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service initiates the transition to the Normal **
**                        operating mode with complete functionality.         **
**                                                                            **
** Sync/Async           : None                                                **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : transceiver - Transceiver ID.                       **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Can Transceiver driver must be initialized.         **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        CanTrcv_CanTrcvNetwork                              **
**                                                                            **
**                        Function(s) invoked :                               **
**                        CanTrcv_XJA11XXGetModeControl,                      **
**                        CanTrcv_XJA11XXSetModeControl,                      **
**                        CanTrcv_XJA11XXSetCanMode                           **
*******************************************************************************/
#if (STD_ON == CANTRCV_TCAN1043A_SUPPORTED)
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetNormalMode_TCAN1043A(
  CONST(uint8, AUTOMATIC) transceiver)
{
  VAR(Std_ReturnType, AUTOMATIC) returnStatus;
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  VAR(Dio_LevelType, AUTOMATIC) retValPin1;
  VAR(Dio_LevelType, AUTOMATIC) retValPin2;
  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];
  /* Initialize return value */
  returnStatus = E_OK;

  /* @Trace: CanTrcv_SUD_API_331 */
  /*Step 1/4 - EN HIGH*/
  SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA();
  /* Invoke the Dio_WriteChannel to set the EN pin to level-High */
  Dio_WriteChannel((ptrCanTrcvNetwork->SelectPin2), (Dio_LevelType) STD_HIGH);

  /* Delay */
  #if (((STD_ON == CANTRCV_TIMER_1US16BIT) && \
      (STD_OFF == CANTRCV_SUPPORT_AR403)) || \
      (STD_ON == CANTRCV_SUPPORT_AR403))
  CanTrcv_Delay(CANTRCV_WAIT_TIME);
  #endif /*(((STD_ON == CANTRCV_TIMER_1US16BIT) && \
      (STD_OFF == CANTRCV_SUPPORT_AR403)) || \
      (STD_ON == CANTRCV_SUPPORT_AR403))*/

  /* Check Hardware pin status */
  retValPin2 = Dio_ReadChannel(ptrCanTrcvNetwork->SelectPin2);
  if (STD_HIGH != retValPin2)
  {
    returnStatus = E_NOT_OK;
  }
  else
  {
    /* Nothing to do */
  }
  
  /*Step 2/4 - STB LOW*/
  /* Invoke the Dio_WriteChannel to set the STB pin to level-Low */
  Dio_WriteChannel((ptrCanTrcvNetwork->SelectPin1), (Dio_LevelType) STD_LOW);
  
  /* Delay */
  #if (((STD_ON == CANTRCV_TIMER_1US16BIT) && \
      (STD_OFF == CANTRCV_SUPPORT_AR403)) || \
      (STD_ON == CANTRCV_SUPPORT_AR403))
  CanTrcv_Delay(CANTRCV_WAIT_TIME);
  #endif /*(((STD_ON == CANTRCV_TIMER_1US16BIT) && \
      (STD_OFF == CANTRCV_SUPPORT_AR403)) || \
      (STD_ON == CANTRCV_SUPPORT_AR403))*/
  
  /* Check Hardware pin status */
  retValPin1 = Dio_ReadChannel(ptrCanTrcvNetwork->SelectPin1);
  if (STD_LOW != retValPin1)
  {
    returnStatus = E_NOT_OK;
  }
  else
  {
    /* Nothing to do */
  }

  /*Step 3/4 - EN LOW*/
  /* Invoke the Dio_WriteChannel to set the EN pin to level-Low */
  Dio_WriteChannel((ptrCanTrcvNetwork->SelectPin2), (Dio_LevelType) STD_LOW);
  /* Delay */
  #if (((STD_ON == CANTRCV_TIMER_1US16BIT) && \
      (STD_OFF == CANTRCV_SUPPORT_AR403)) || \
      (STD_ON == CANTRCV_SUPPORT_AR403))
  CanTrcv_Delay(CANTRCV_WAIT_TIME);
  #endif /*(((STD_ON == CANTRCV_TIMER_1US16BIT) && \
      (STD_OFF == CANTRCV_SUPPORT_AR403)) || \
      (STD_ON == CANTRCV_SUPPORT_AR403))*/
  /* Check Hardware pin status */
  retValPin2 = Dio_ReadChannel(ptrCanTrcvNetwork->SelectPin2);
  if (STD_LOW != retValPin2)
  {
    returnStatus = E_NOT_OK;
  }
  else
  {
    /* Nothing to do */
  }
  #if(CANTRCV_SUPPORT_AR403 == STD_ON)
  /*Delay for TCAN1043A 20 us*/ 
  CanTrcv_Delay(CANTRCV_TCAN1043A_WAIT_COUNT);
  #endif 
  #if ((STD_ON == CANTRCV_TIMER_1US16BIT) && \
      (STD_OFF == CANTRCV_SUPPORT_AR403)) 
  /*Delay for TCAN1043A 20 us*/ 
  CanTrcv_Delay(CANTRCV_TCAN1043A_WAIT_TIME);
  #endif

  /*Step 4/4 - STB_HIGH,EN_HIGH*/
  /* Invoke the Dio_WriteChannel to set the STB pin to level-High */
  Dio_WriteChannel((ptrCanTrcvNetwork->SelectPin1), (Dio_LevelType) STD_HIGH);
  /* Invoke the Dio_WriteChannel to set the EN pin to level-High */
  Dio_WriteChannel((ptrCanTrcvNetwork->SelectPin2), (Dio_LevelType) STD_HIGH);

  /* Delay */
  #if (((STD_ON == CANTRCV_TIMER_1US16BIT) && \
      (STD_OFF == CANTRCV_SUPPORT_AR403)) || \
      (STD_ON == CANTRCV_SUPPORT_AR403))
  CanTrcv_Delay(CANTRCV_WAIT_TIME);
  #endif /*(((STD_ON == CANTRCV_TIMER_1US16BIT) && \
      (STD_OFF == CANTRCV_SUPPORT_AR403)) || \
      (STD_ON == CANTRCV_SUPPORT_AR403))*/

  /* Check Hardware pin status */
  retValPin1 = Dio_ReadChannel(ptrCanTrcvNetwork->SelectPin1);
  retValPin2 = Dio_ReadChannel(ptrCanTrcvNetwork->SelectPin2);
  if ((STD_HIGH != retValPin1) || (STD_HIGH != retValPin2))
  {
    returnStatus = E_NOT_OK;
  }
  else
  {
    /* Nothing to do */
  }

  SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA();
  return(returnStatus);
}
#endif /* STD_ON == CANTRCV_TCAN1043A_SUPPORTED */

/*******************************************************************************
** Function Name        : CanTrcv_SetNormalMode_Other_HW                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service initiates the transition to the Normal **
**                        operating mode with complete functionality.         **
**                                                                            **
** Sync/Async           : None                                                **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : transceiver - Transceiver ID.                       **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Can Transceiver driver must be initialized.         **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        CanTrcv_CanTrcvNetwork                              **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Dio_WriteChannel, CanTrcv_Delay,                    **
**                        Dio_ReadChannel                                     **
*******************************************************************************/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetNormalMode_Other_HW(
  CONST(uint8, AUTOMATIC) transceiver)
{
  VAR(Std_ReturnType, AUTOMATIC) returnStatus;
  VAR(Dio_LevelType, AUTOMATIC) retValPin1;
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;

  /* Initialize return value */
  returnStatus = E_OK;

  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];

  /* @Trace: CanTrcv_SUD_API_116 */
  SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA();
  /* Invoke the Dio_WriteChannel to set the Standby pin to level-Low */
  /* These devices STB Active LOW */
  Dio_WriteChannel((ptrCanTrcvNetwork->SelectPin1), (Dio_LevelType) STD_LOW);

  /* Delay */
  #if (((STD_ON == CANTRCV_TIMER_1US16BIT) && \
      (STD_OFF == CANTRCV_SUPPORT_AR403)) || \
      (STD_ON == CANTRCV_SUPPORT_AR403))
  CanTrcv_Delay(CANTRCV_WAIT_TIME);
  #endif /*(((STD_ON == CANTRCV_TIMER_1US16BIT) && \
      (STD_OFF == CANTRCV_SUPPORT_AR403)) || \
      (STD_ON == CANTRCV_SUPPORT_AR403))*/

  retValPin1 = Dio_ReadChannel(ptrCanTrcvNetwork->SelectPin1);
  if (STD_LOW != retValPin1)
  {
    returnStatus = E_NOT_OK;
  }
  else
  {
    /* Nothing to do */
  }
  SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA();

  return(returnStatus);
}

/*******************************************************************************
** Function Name        : CanTrcv_SetNormalMode_HW_USED_EN_STB                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service initiates the transition to the Normal **
**                        operating mode with complete functionality.         **
**                                                                            **
** Sync/Async           : None                                                **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : transceiver - Transceiver ID.                       **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Can Transceiver driver must be initialized.         **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        CanTrcv_CanTrcvNetwork                              **
**                                                                            **
**                        Function(s) invoked :                               **
**                        CanTrcv_XJA11XXGetModeControl,                      **
**                        CanTrcv_XJA11XXSetModeControl,                      **
**                        CanTrcv_XJA11XXSetCanMode                           **
*******************************************************************************/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetNormalMode_HW_USED_EN_STB(
  CONST(uint8, AUTOMATIC) transceiver)
{
  VAR(Std_ReturnType, AUTOMATIC) returnStatus;
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  VAR(Dio_LevelType, AUTOMATIC) retValPin1;
  VAR(Dio_LevelType, AUTOMATIC) retValPin2;
  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];
  /* Initialize return value */
  returnStatus = E_OK;

  /* @Trace: CanTrcv_SUD_API_112 */
  SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA();
  /* These devices STB, EN Active High */
  /* Invoke the Dio_WriteChannel to set the STB pin to level-High */
  Dio_WriteChannel((ptrCanTrcvNetwork->SelectPin1), (Dio_LevelType) STD_HIGH);
  /* Invoke the Dio_WriteChannel to set the EN pin to level-High */
  Dio_WriteChannel((ptrCanTrcvNetwork->SelectPin2), (Dio_LevelType) STD_HIGH);

  /* Delay */
  #if (((STD_ON == CANTRCV_TIMER_1US16BIT) && \
      (STD_OFF == CANTRCV_SUPPORT_AR403)) || \
      (STD_ON == CANTRCV_SUPPORT_AR403))
  CanTrcv_Delay(CANTRCV_WAIT_TIME);
  #endif /*(((STD_ON == CANTRCV_TIMER_1US16BIT) && \
      (STD_OFF == CANTRCV_SUPPORT_AR403)) || \
      (STD_ON == CANTRCV_SUPPORT_AR403))*/

  /* Check Hardware pin status */
  retValPin1 = Dio_ReadChannel(ptrCanTrcvNetwork->SelectPin1);
  retValPin2 = Dio_ReadChannel(ptrCanTrcvNetwork->SelectPin2);
  if ((STD_HIGH != retValPin1) || (STD_HIGH != retValPin2))
  {
    returnStatus = E_NOT_OK;
  }
  else
  {
    /* Nothing to do */
  }
  SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA();
  return(returnStatus);
}

/*******************************************************************************
** Function Name        : CanTrcv_SetStandbyMode_HW_USED_EN_STB               **
**                                                                            **
** Service ID           : Not Applicable                                      **
**                                                                            **
** Description          : This service initiates the transition to the        **
**                        Standby operating mode with complete functionality. **
**                                                                            **
** Sync/Async           : None                                                **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : transceiver - CAN transceiver ID                    **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Can Transceiver driver must be initialized.         **
**                                                                            **
** Remarks              : Global variable(s)  : CanTrcv_CanTrcvNetwork        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Dio_WriteChannel,                                   **
**                        Dio_ReadChannel                                     **
**                        SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA,       **
**                        SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA,        **
*******************************************************************************/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetStandbyMode_HW_USED_EN_STB(
  VAR(uint8, AUTOMATIC) transceiver)
{
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  VAR(Std_ReturnType, AUTOMATIC) returnStatus;
  VAR(Dio_LevelType, AUTOMATIC) retValPin1;
  VAR(Dio_LevelType, AUTOMATIC) retValPin2;
  
  /* Initialize return value */
  returnStatus = E_OK;
  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];

  /* @Trace: CanTrcv_SUD_API_123 */
  SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA();
  /* CanTrcv shoud need two h/w pins */
  /* Invoke the Dio_WriteChannel to set the STB pin to level-Low */
  Dio_WriteChannel((ptrCanTrcvNetwork->SelectPin1), (Dio_LevelType) STD_LOW);
  /* Invoke the Dio_WriteChannel to set the EN pin to level-Low */
  Dio_WriteChannel((ptrCanTrcvNetwork->SelectPin2), (Dio_LevelType) STD_LOW);

  /* Delay */
  #if (((STD_ON == CANTRCV_TIMER_1US16BIT) && \
      (STD_OFF == CANTRCV_SUPPORT_AR403)) || \
      (STD_ON == CANTRCV_SUPPORT_AR403))
  CanTrcv_Delay(CANTRCV_WAIT_TIME);
  #endif /*(((STD_ON == CANTRCV_TIMER_1US16BIT) && \
      (STD_OFF == CANTRCV_SUPPORT_AR403)) || \
      (STD_ON == CANTRCV_SUPPORT_AR403))*/


  retValPin1 = Dio_ReadChannel(ptrCanTrcvNetwork->SelectPin1);
  retValPin2 = Dio_ReadChannel(ptrCanTrcvNetwork->SelectPin2);
  if ((STD_LOW != retValPin1) || (STD_LOW != retValPin2))
  {
    returnStatus = E_NOT_OK;
  }
  else
  {
    /* Nothing to do */
  }
  SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA();

  return returnStatus;
}

/*******************************************************************************
** Function Name        : CanTrcv_SetStandbyMode_ArisuCan                     **
**                                                                            **
** Service ID           : Not Applicable                                      **
**                                                                            **
** Description          : This service initiates the transition to the        **
**                        Standby operating mode with complete functionality. **
**                                                                            **
** Sync/Async           : None                                                **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : transceiver - CAN transceiver ID                    **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Can Transceiver driver must be initialized.         **
**                                                                            **
** Remarks              : Global variable(s)  : CanTrcv_CanTrcvNetwork        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Dio_WriteChannel,                                   **
**                        Dio_ReadChannel, CanTrcv_Delay                      **
**                        SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA,       **
**                        SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA,        **
*******************************************************************************/
#if (STD_ON == CANTRCV_ARISUCAN_SUPPORTED)
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetStandbyMode_ArisuCan(
  VAR(uint8, AUTOMATIC) transceiver)
{
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  VAR(Std_ReturnType, AUTOMATIC) returnStatus;
  VAR(CanTrcv_TrcvModeType, AUTOMATIC) canTrcvMode;
  VAR(uint16, AUTOMATIC) spiSrcData;

  /* Initialize return value */
  returnStatus = E_OK;
  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];

  /* @Trace: CanTrcv_SUD_API_124 */
  SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA();

  /* ARISU-CAN CanTrcv Mode Change */
  CanTrcv_IntArisuCan_RequestCanMode
    (ptrCanTrcvNetwork->CanTrcvHwDev, ARISUCAN_SBCMODE_STOP);

  /* Check ARISU-CAN CanTrcv Mode */
  canTrcvMode = CanTrcv_ArisuCan_CheckCanMode(
    ptrCanTrcvNetwork->CanTrcvHwDev, ARISUCAN_SBCMODE_STOP);

  if (CANTRCV_TRCVMODE_STANDBY != canTrcvMode)
  {
    returnStatus = E_NOT_OK;
  }
  else
  {
    /* ARISU-CAN Wake Up Clear */
    spiSrcData = ARISUCAN_WK_STAT_0_REG_W;
    (void)ArisuCan_SendSPI(&spiSrcData, &ArisuCan_SpiDestData);

    /* ARISU-CAN Wake Up Clear */
    spiSrcData = ARISUCAN_WK_STAT_2_REG_W;
    (void)ArisuCan_SendSPI(&spiSrcData, &ArisuCan_SpiDestData);
  }
  SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA();

  return returnStatus;
}
#endif /* #if (STD_ON == CANTRCV_ARISUCAN_SUPPORTED */

/*******************************************************************************
** Function Name        : CanTrcv_SetStandbyMode_XJA11XX                      **
**                                                                            **
** Service ID           : Not Applicable                                      **
**                                                                            **
** Description          : This service initiates the transition to the        **
**                        Standby operating mode with complete functionality. **
**                                                                            **
** Sync/Async           : None                                                **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : transceiver - CAN transceiver ID                    **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Can Transceiver driver must be initialized.         **
**                                                                            **
** Remarks              : Global variable(s)  : CanTrcv_CanTrcvNetwork        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        CanTrcv_XJA11XXGetModeControl,                      **
**                        CanTrcv_XJA11XXSetModeControl,                      **
**                        SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA,       **
**                        SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA,        **
*******************************************************************************/
#if (STD_ON == CANTRCV_XJA11XX_SUPPORTED)
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetStandbyMode_XJA11XX(
  VAR(uint8, AUTOMATIC) transceiver)
{
  VAR(Std_ReturnType, AUTOMATIC) returnStatus;
  VAR(CanTrcv_TrcvModeType, AUTOMATIC) canTrcvMode;
  /* Initialize local variable */
  canTrcvMode = CANTRCV_TRCVMODE_STANDBY;

  /* @Trace: CanTrcv_SUD_API_125 */
  SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA();
  /* Check Transceiver is Standby Mode */
  returnStatus = CanTrcv_XJA11XXGetModeControl(transceiver, &canTrcvMode);
  if ((E_NOT_OK != returnStatus) && (CANTRCV_TRCVMODE_STANDBY != canTrcvMode))
  {
    /* Set Mode Control as Standby Mode */
    returnStatus = CanTrcv_XJA11XXSetModeControl(transceiver,
      XJA11XX_STANDBY_MODE);
    /* Get current Mode Control */
    returnStatus |= CanTrcv_XJA11XXGetModeControl(transceiver, &canTrcvMode);
    if (CANTRCV_TRCVMODE_STANDBY != canTrcvMode)
    {
      returnStatus = E_NOT_OK;
    }
    else
    {
      /* Nothing to do */
    }
  }
  else
  {
    /* Nothing to do */
  }
  SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA();

  return returnStatus;
}
#endif /* #if (STD_ON == CANTRCV_XJA11XX_SUPPORTED */

/*******************************************************************************
** Function Name        : CanTrcv_SetStandbyMode_TLE9255W                     **
**                                                                            **
** Service ID           : Not Applicable                                      **
**                                                                            **
** Description          : This service initiates the transition to the        **
**                        Standby operating mode with complete functionality. **
**                                                                            **
** Sync/Async           : None                                                **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : transceiver - CAN transceiver ID                    **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Can Transceiver driver must be initialized.         **
**                                                                            **
** Remarks              : Global variable(s)  : CanTrcv_CanTrcvNetwork        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        CanTrcv_TLE9255WSetModeControl,                     **
**                        CanTrcv_TLE9255WGetModeControl,                     **
**                        SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA,       **
**                        SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA,        **
*******************************************************************************/
#if (STD_ON == CANTRCV_TLE9255W_SUPPORTED)
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetStandbyMode_TLE9255W(
  VAR(uint8, AUTOMATIC) transceiver)
{
  VAR(Std_ReturnType, AUTOMATIC) returnStatus;
  VAR(CanTrcv_TrcvModeType, AUTOMATIC) canTrcvMode;

  /* Initialize local variable */
  canTrcvMode = CANTRCV_TRCVMODE_STANDBY;

  /* @Trace: CanTrcv_SUD_API_126 */
  SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA();
  /* Set Mode Control as Standby Mode */
  returnStatus = CanTrcv_TLE9255WSetModeControl(transceiver,
    TLE9255W_STANDBY_MODE);
  /* Get current Mode Control */
  returnStatus |= CanTrcv_TLE9255WGetModeControl(transceiver, &canTrcvMode);
  if (CANTRCV_TRCVMODE_STANDBY != canTrcvMode)
  {
    returnStatus = E_NOT_OK;
  }
  else
  {
    /* Nothing to do */
  }
  SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA();

  return returnStatus;
}
#endif /* #if (STD_ON == CANTRCV_TLE9255W_SUPPORTED */

/*******************************************************************************
** Function Name        : CanTrcv_SetStandbyMode_TCAN1145                      **
**                                                                            **
** Service ID           : Not Applicable                                      **
**                                                                            **
** Description          : This service initiates the transition to the        **
**                        Standby operating mode with complete functionality. **
**                                                                            **
** Sync/Async           : None                                                **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : transceiver - CAN transceiver ID                    **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Can Transceiver driver must be initialized.         **
**                                                                            **
** Remarks              : Global variable(s)  : CanTrcv_CanTrcvNetwork        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        CanTrcv_TCAN1145GetModeControl,                      **
**                        CanTrcv_TCAN1145SetModeControl,                      **
**                        SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA,       **
**                        SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA,        **
*******************************************************************************/
#if (STD_ON == CANTRCV_TCAN1145_SUPPORTED)
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetStandbyMode_TCAN1145(
  VAR(uint8, AUTOMATIC) transceiver)
{
  VAR(Std_ReturnType, AUTOMATIC) returnStatus;
  VAR(CanTrcv_TrcvModeType, AUTOMATIC) canTrcvMode;
  /* Initialize local variable */
  canTrcvMode = CANTRCV_TRCVMODE_STANDBY;

  /* @Trace: CanTrcv_SUD_API_339*/
  SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA();
  /* Check Transceiver is Standby Mode */
  returnStatus = CanTrcv_TCAN1145GetModeControl(transceiver, &canTrcvMode);
  
  if ((E_NOT_OK != returnStatus) && (CANTRCV_TRCVMODE_STANDBY != canTrcvMode))
  {
    /* Set Mode Control as Standby Mode */
    returnStatus = CanTrcv_TCAN1145SetModeControl(transceiver,
      TCAN1145_STANDBY_MODE);
    /* Get current Mode Control */
    returnStatus |= CanTrcv_TCAN1145GetModeControl(transceiver, &canTrcvMode);
    if (CANTRCV_TRCVMODE_STANDBY != canTrcvMode)
    {
      returnStatus = E_NOT_OK;
    }
    else
    {
      /* Nothing to do */
    }
  }
  else
  {
    /* Nothing to do */
  }
  SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA();

  return returnStatus;
}
#endif /* #if (STD_ON == CANTRCV_TCAN1145_SUPPORTED */

/*******************************************************************************
** Function Name        : CanTrcv_SetStandbyMode_Other_HW                     **
**                                                                            **
** Service ID           : Not Applicable                                      **
**                                                                            **
** Description          : This service initiates the transition to the        **
**                        Standby operating mode with complete functionality. **
**                                                                            **
** Sync/Async           : None                                                **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : transceiver - CAN transceiver ID                    **
**                                                                            **
** In/Out Parameters    : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Can Transceiver driver must be initialized.         **
**                                                                            **
** Remarks              : Global variable(s)  : CanTrcv_CanTrcvNetwork        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        CanTrcv_TLE9255WSetModeControl,                     **
**                        CanTrcv_TLE9255WGetModeControl,                     **
**                        SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA,       **
**                        SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA,        **
*******************************************************************************/
FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_SetStandbyMode_Other_HW(
  VAR(uint8, AUTOMATIC) transceiver)
{
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork;
  VAR(Std_ReturnType, AUTOMATIC) returnStatus;
  VAR(Dio_LevelType, AUTOMATIC) retValPin1;
  /* Get the pointer to the structure of the requested network */
  ptrCanTrcvNetwork = &CanTrcv_CanTrcvNetwork[transceiver];
  returnStatus = E_OK;
  /* @Trace: CanTrcv_SUD_API_127 */
  SchM_Enter_CanTrcv_INTERRUPT_PROTECTION_AREA();
  /* Invoke the Dio_WriteChannel to set the Standby pin to level-High */
  Dio_WriteChannel((ptrCanTrcvNetwork->SelectPin1), (Dio_LevelType) STD_HIGH);
  /* Delay */
  #if (((STD_ON == CANTRCV_TIMER_1US16BIT) && \
      (STD_OFF == CANTRCV_SUPPORT_AR403)) || \
      (STD_ON == CANTRCV_SUPPORT_AR403))
  CanTrcv_Delay(CANTRCV_WAIT_TIME);
  #endif /*(((STD_ON == CANTRCV_TIMER_1US16BIT) && \
      (STD_OFF == CANTRCV_SUPPORT_AR403)) || \
      (STD_ON == CANTRCV_SUPPORT_AR403))*/

  retValPin1 = Dio_ReadChannel(ptrCanTrcvNetwork->SelectPin1);
  if (STD_HIGH != retValPin1)
  {
    returnStatus = E_NOT_OK;
  }
  else
  {
    /* Nothing to do */
  }
  SchM_Exit_CanTrcv_INTERRUPT_PROTECTION_AREA();

  return returnStatus;
}

/*******************************************************************************
** Function Name      : CanTrcv_XJA11XXInit                                   **
**                                                                            **
** Service ID         : N/A                                                   **
**                                                                            **
** Description        : This function to initialize XJA11XX device.           **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : transceiver - CAN Transceiver ID.                     **
**                      ptrCanTrcvNetwork - Pointer to the configuration      **
**                                           structure.                       **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: The initialization is successful.               **
**                      E_NOT_OK: The initialization is not successful.       **
**                                                                            **
** Preconditions      : STD_ON == CANTRCV_XJA11XX_SUPPORTED                   **
**                                                                            **
** Remarks            : Global variable(s): CanTrcv_WakeUpReason              **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      CanTrcv_XJA11XXSetModeControl,                        **
**                      CanTrcv_ReadReg,                                      **
**                      CanTrcv_WriteReg,                                     **
**                      EcuM_SetWakeupEvent                                   **
*******************************************************************************/
/* polyspace +5 MISRA-C3:8.13 [Not a defect:Low] "It will be used to get data, no impact" */
#if (STD_ON == CANTRCV_XJA11XX_SUPPORTED)
static FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_XJA11XXInit_ClearEventSrc(
  CONST(uint8, AUTOMATIC) transceiver,
  P2CONST(CanTrcv_NetworkType, AUTOMATIC, CANTRCV_CONST) ptrCanTrcvNetwork,
  P2VAR(uint8, AUTOMATIC, CANTRCV_VAR) data)
{
  /* @Trace: SWS_CanTrcv_00180 SWS_CanTrcv_00167 SWS_CanTrcv_00086 */
  VAR(uint8, AUTOMATIC) wpeFlag;
  VAR(uint8, AUTOMATIC) trxeFlag;
  VAR(uint8, AUTOMATIC) syseFlag;
  #if (STD_ON == CANTRCV_WAKEUP_SUPPORTED)
  VAR(uint8, AUTOMATIC) cwFlag;
  #endif /* (STD_ON == CANTRCV_WAKEUP_SUPPORTED) */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  P2CONST(CanTrcv_WriteReadReg_Type, AUTOMATIC, CANTRCV_CONST) ptrWriteReadReg;
  ptrWriteReadReg = &CanTrcv_WriteReadReg[CANTRCV_ZERO];
  #if (STD_OFF == CANTRCV_WAKEUP_SUPPORTED)
  /* Avoid compiler warning */
  CANTRCV_UNUSED_VAL(ptrCanTrcvNetwork);
  #endif

  /* @Trace: CanTrcv_SUD_API_018 */
  /* Read Global event status register */
  returnValue = ptrWriteReadReg->ReadReg(transceiver, XJA11XX_GLOBAL_EVENT_STATUS_REG,
    data);
  if (E_NOT_OK != returnValue)
  {
    /* Get WPE flag - bit 3 */
    wpeFlag = (*data & XJA11XX_WPE_MASK);
    /* Get TRXE flag - bit 2 */
    trxeFlag = (*data & XJA11XX_TRXE_MASK);
    /* Get SYSE flag - bit 0 */
    syseFlag = (*data & XJA11XX_SYSE_MASK);

    /* Check WAKE pin event pending */
    if (XJA11XX_WPE_MASK == wpeFlag)
    {
      /* @Trace: CanTrcv_SUD_API_019 */
      #if (STD_ON == CANTRCV_WAKEUP_SUPPORTED)
      /* Set wake up reason */
      CanTrcv_WakeUpReason[transceiver] = CANTRCV_WU_BY_PIN;
      /* Report wake up source to EcuM */
      EcuM_SetWakeupEvent(ptrCanTrcvNetwork->WakeupSource);
      #endif /* (STD_ON == CANTRCV_WAKEUP_SUPPORTED) */
      /* Clear WAKE pin event status */
      returnValue |= ptrWriteReadReg->WriteReg(transceiver,
        XJA11XX_WAKE_PIN_EVENT_STATUS_REG,
          (XJA11XX_WPR_MASK | XJA11XX_WPF_MASK));
    }

    /* Check transceiver event pending */
    if (XJA11XX_TRXE_MASK == trxeFlag)
    {
      /* @Trace: CanTrcv_SUD_API_020 */
      #if (STD_ON == CANTRCV_WAKEUP_SUPPORTED)
      /* Read Transceiver event status register */
      returnValue |= ptrWriteReadReg->ReadReg(transceiver,
        XJA11XX_TRCV_EVENT_STATUS_REG, data);
      if (E_NOT_OK != returnValue)
      {
        /* Get CW flag - bit 0 */
        cwFlag = (*data & XJA11XX_CW_MASK);
        /* Check CAN wake-up status */
        if (XJA11XX_CW_MASK == cwFlag)
        {
          /* Set wake up reason */
          CanTrcv_WakeUpReason[transceiver] = CANTRCV_WU_BY_BUS;
          /* Report wake up source to EcuM */
          EcuM_SetWakeupEvent(ptrCanTrcvNetwork->WakeupSource);
        }
      }
      #endif /* (STD_ON == CANTRCV_WAKEUP_SUPPORTED) */

      /* Clear Transceiver event status */
      returnValue |= ptrWriteReadReg->WriteReg(transceiver,
        XJA11XX_TRCV_EVENT_STATUS_REG,
        (XJA11XX_CBS_MASK | XJA11XX_CF_MASK | XJA11XX_CW_MASK));
    }

    /* Check system event pending */
    if (XJA11XX_SYSE_MASK == syseFlag)
    {
      /* @Trace: CanTrcv_SUD_API_021 */
      /* Clear system event status pending */
      returnValue |= ptrWriteReadReg->WriteReg(transceiver,
        XJA11XX_SYSTEM_EVENT_STATUS_REG,
        (XJA11XX_OTW_MASK | XJA11XX_SPIF_MASK));
    }
  }
  return returnValue;
}
#endif /* STD_ON == CANTRCV_XJA11XX_SUPPORTED */


#define CANTRCV_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
