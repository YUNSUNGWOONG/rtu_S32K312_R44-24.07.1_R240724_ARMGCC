/*******************************************************************************
**                            HYUNDAI MOTORS GROUP                            **
**                                                                            **
**                            All rights reserved                             **
**                                                                            **
**            You can NOT use this sample code for Product Release            **
*******************************************************************************/
#ifndef LOWPOWER_CALLOUT_H
#define LOWPOWER_CALLOUT_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "EcuM.h"
#include "SchM_EcuM.h"

#include "Icu.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define ECUM_WKSOURCE_NONE        0x00000000U

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

#define ECUM_START_SEC_CALLOUT_CODE
#include "MemMap.h"

FUNC(void, ECUM_CALLOUT_CODE) EcuM_H2LTransition_Callout_App(void);

FUNC(void, ECUM_CALLOUT_CODE) EcuM_H2LTransition_Callout_Swp(void);

FUNC(void, ECUM_CALLOUT_CODE) EcuM_L2HTransition_Callout_App(void);

FUNC(void, ECUM_CALLOUT_CODE) EcuM_L2HTransition_Callout_Swp(void);

FUNC(void, ECUM_CALLOUT_CODE) EcuM_Boot_Callout(void);
FUNC(void, ECUM_CALLOUT_CODE) EcuM_PostInitUser(void);

extern FUNC(void, ECUM_CALLOUT_CODE) CheckWakeup_HS_CAN1_RX(void);
extern FUNC(void, ECUM_CALLOUT_CODE) CheckWakeup_FD_CAN1_RX(void);
extern FUNC(void, ICU_CALLOUT_CODE) IcuSignalNotification_HS_CAN1_RX(void);

#define ECUM_STOP_SEC_CALLOUT_CODE
#include "MemMap.h"

#endif
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

