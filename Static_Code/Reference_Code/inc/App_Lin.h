/*******************************************************************************
**                            HYUNDAI MOTORS GROUP                            **
**                                                                            **
**                            All rights reserved                             **
**                                                                            **
**            You can NOT use this sample code for Product Release            **
*******************************************************************************/
#ifndef APP_LIN_H
#define APP_LIN_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Rte_App_Lin_LIN1.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
extern FUNC(void, App_Lin_LIN1_CODE) Sym_LinScheduleRequest(void);
extern FUNC(void, App_Lin_LIN1_CODE) Sym_LinScheduleSwitch(void);
extern void lin_after_schedule(uint8 channelId, uint8 schId, uint8 schEntryNum, uint8 frameId);
extern void lin_cbk_err(uint8 channelid, uint8 errcode, uint8 schEntryNum, uint8 frameId);
extern void AppLin_LinLinScheduleRequest(uint16 scheduleID);

#endif
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
