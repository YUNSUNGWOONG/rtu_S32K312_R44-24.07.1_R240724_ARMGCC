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
**  SRC-MODULE: LinSM_InternalFunc.h                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR LinSM Module                                          **
**                                                                            **
**  PURPOSE   : Provision of LINSM Internal Functions                         **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/
 
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision       Date                  By               Description          **
********************************************************************************
** 1.0.6          25-Nov-2022           TruongND18       #CP44-1089           **
** 1.0.2          17-Sep-2021           DuyNGB           R44-Redmine #20123   **
** 1.0.0          22-Dec-2020           SJ Kim           Initial Version      **
*******************************************************************************/

#ifndef LINSM_INTERNALFUNC_H
#define LINSM_INTERNALFUNC_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "LinSM_PCTypes.h"        /* LinSM pre-compile config header */
#include "LinSM_Ram.h"            /* LinSM Ram header file */

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define LINSM_START_SEC_CODE
#include "MemMap.h"
#if (LINSM_TIMEOUT_FUNC == STD_ON)
extern FUNC(uint16, LINSM_CODE) LinSM_ProcessTimer(NetworkHandleType
  LddLocalChannelId, uint16 LusTimerCount, uint8 LucTimerType);

extern FUNC(uint16, LINSM_CODE) LinSM_ProcessTimerSlave(uint16 LusTimerCount);

#endif

#if (LINSM_DEV_ERROR_DETECT == STD_ON)
extern FUNC(Std_ReturnType, LINSM_CODE) LinSM_CheckSchedule(
  NetworkHandleType network, LinIf_SchHandleType schedule);
extern FUNC(Std_ReturnType, LINSM_CODE)LinSM_DetRequestComMode(
    Std_ReturnType ReturnValue,
    ComM_ModeType mode,
    NetworkHandleType network);
#endif

#if (LINSM_SLAVE_SUPPORT == STD_ON)
extern FUNC(Std_ReturnType, LINSM_CODE)LinSM_SlaveRequestComMode(NetworkHandleType network);
#endif

#if ((LINSM_TIMEOUT_FUNC == STD_ON) && (LINSM_SLAVE_SUPPORT == STD_ON))
extern FUNC(void, LINSM_CODE)LinSM_SlaveMainFunc(
P2VAR(LinSM_Channel, AUTOMATIC, LINSM_DATA) LpChannel,
P2CONST(LinSM_StaticChannel, AUTOMATIC, LINSM_CONST) LpStaticChannel,
P2CONST(LinSM_ConfigType, AUTOMATIC, LINSM_CONST) LpConfigType,
NetworkHandleType network,
NetworkHandleType LddLocalChannelId,
ComM_ModeType LddComMode);
#endif


#define LINSM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* LINSM_INTERNALFUNC_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
