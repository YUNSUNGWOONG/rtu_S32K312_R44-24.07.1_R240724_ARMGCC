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
**  SRC-MODULE: IoHwAb.h                                                      **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : Provision of external declaration of APIs and Service IDs     **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.3.0.1   30-Jun-2022  KhaLN1            #CP44-365                         **
** 1.0.0     04-Dec-2020  YangJin.Kim       R40-Redmine #26992                **
*******************************************************************************/

#ifndef IOHWAB_H
#define IOHWAB_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: IoHwAb_SUD_MACRO_005 */
#include "Std_Types.h"
#include "IoHwAb_Cfg.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* Instance identification */
#define IOHWAB_INSTANCE_ID                          ((uint8)0x00)

/*******************************************************************************
**                      DET Error Codes                                       **
*******************************************************************************/
/* @Trace: IoHwAb_SUD_MACRO_006 */
/* DET error is reported if an API is invoked with a null pointer parameter */
#define IOHWAB_E_DET_WRONG_STATE                    0x01
#define IOHWAB_E_DET_WRONG_SETTING                  0x02
#define IOHWAB_E_DET_WRONG_PARAM                    0x03
#define IOHWAB_E_DET_SETUP_FAIL                     0x04
#define IOHWAB_E_DET_PROC_FAIL                      0x05
#define IOHWAB_E_DET_BUSY                           0x06
#define IOHWAB_E_DET_MCAL_BUSY                      0x07
#define IOHWAB_E_DET_GETPS_FAILED					0x08
#define IOHWAB_E_DET_PREPAREPS_FAILED				0x09
#define IOHWAB_E_DET_ENTERPS_FAILED					0x0A

/*******************************************************************************
**                      Service IDs                                           **
*******************************************************************************/
/* @Trace: SWS_IoHwAb_00119 */
/* @Trace: IoHwAb_SUD_MACRO_003 */
/* Service Id of IoHwAb_Init */
#define IOHWAB_INIT_SID                             0x01

/* Service Id of IoHwAb_GetVersionInfo */
#define IOHWAB_GETVERSIONINFO_SID                   0x10

/* Service Id of IoHwAb_AdcNotification */
#define IOHWAB_ADCNOTIFICATION_SID                  0x20

/* Service Id of IoHwAb_PwmNotification */
#define IOHWAB_PWMNOTIFICATION_SID                  0x30

/* Service Id of IoHwAb_IcuNotification */
#define IOHWAB_ICUNOTIFICATION_SID                  0x40

/* Service Id of IoHwAb_GptNotification */
#define IOHWAB_GPTNOTIFICATION_SID                  0x50

/* Service Id of IoHwAb_OcuNotification */
#define IOHWAB_OCUNOTIFICATION_SID                  0xa0

/* Service Id of IoHwAb_Pwm_NotifyReadyForPowerState  */
#define IOHWAB_PWM_NOTIFYREADYFORPOWERSTATE_SID     0x60

/* Service Id of IoHwAb_Adc_NotifyReadyForPowerState  */
#define IOHWAB_ADC_NOTIFYREADYFORPOWERSTATE_SID     0x70

/* Service Id of IoHwAb_PreparePowerState */
#define IOHWAB_PREPAREPOWERSTATE_SID                0x80

/* Service Id of IoHwAb_EnterPowerState */
#define IOHWAB_ENTERPOWERSTATE_SID                  0x90

/* Service Id of IoHwAb_IOM_10ms */
#define IOHWAB_IOM_10MS_SID                         0xaf

#define IOHWAB_ANAIN_INIT_SID                       0xb0
#define IOHWAB_ANAINDIR_READ_DIRECT_SID             0xb1
#define IOHWAB_ANAIN_CONVERT_ALL_SID                0xb2
#define IOHWAB_ANAIN_READ_DIRECT_SID                0xb3

#define IOHWAB_DIGIN_MC33972_INIT_SID               0xc0
#define IOHWAB_DIGIN_MC33972_ACQ_SID                0xc1
#define IOHWAB_DIGIN_MC33972_L2H_SID                0xc2
#define IOHWAB_DIGIN_MC33972_H2L_SID                0xc3

#define IOHWAB_DIGOUT_L9826_SID                     0xd0
#define IOHWAB_DIGOUT_L99MC6_SID                    0xd1
#define IOHWAB_DIGOUT_TLE7240SL_SID                 0xd2

#define IOHWAB_VOLMON_SID                           0xe0

#define IOHWAB_MCUSPECIFIC_SID                      0xf0

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
/* @Trace: SRS_BSW_00414 */
/* @Trace: SWS_IoHwAb_00119 SWS_IoHwAb_00157 */
typedef struct
{
	uint8 LucVar;
}IoHwAb_ConfigType;


#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, IOHWAB_CODE)IoHwAb_Init(P2CONST(IoHwAb_ConfigType, AUTOMATIC, IOHWAB_APPL_CONST) ConfigPtr);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, IOHWAB_CODE)IoHwAb_DeInit(void);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#if (IOHWAB_VERSION_INFO_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, IOHWAB_CODE)IoHwAb_GetVersionInfo
  (P2VAR(Std_VersionInfoType, AUTOMATIC, IOHWAB_APPL_DATA) versioninfo);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /*(IOHWAB_VERSION_INFO_API == STD_ON)*/

#if (IOHWAB_USE_IO_MAN_FASTTIMER == STD_ON)
typedef CoSvAb_FastTimerDelay IoHwAb_TimerDelay;
#endif
#if (IOHWAB_USE_IO_MAN_GPTTIMER == STD_ON)
typedef Gpt_ValueType IoHwAb_TimerDelay;
#endif

#if (IOHWAB_USE_POWER_STATE == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_PreparePowerState(uint8 state);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_EnterPowerState(void);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (IOHWAB_USE_POWER_STATE == STD_ON) */

#endif /* IOHWAB_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

