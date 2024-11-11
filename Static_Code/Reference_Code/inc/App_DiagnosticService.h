/*******************************************************************************
**                            HYUNDAI MOTORS GROUP                            **
**                                                                            **
**                            All rights reserved                             **
**                                                                            **
**            You can NOT use this sample code for Product Release            **
*******************************************************************************/

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
**  FILE-NAME : App_DiagnosticService.h                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains the API definitions for SW-C Sample of Dcm **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: yes                                       **
**                                                                            **
*******************************************************************************/
#ifndef APP_DIAGNOSTICSERVICE_H
#define APP_DIAGNOSTICSERVICE_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
extern uint8 AppDcm_GaaSeed[4];
extern uint8 AppDcm_GucEcuIsBusy;

extern uint8 AppDcm_ReadDataInvoked;
extern uint8 AppDcm_WriteDataInvoked;

extern uint8 AppDcm_Tid1RequestControlInvoked;
extern uint8 AppDcm_ConditionCheckReadInvoked;
extern uint8 AppDcm_GetScalingInformationInvoked;

#endif /* APP_DIAGNOSTICSERVICE_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
