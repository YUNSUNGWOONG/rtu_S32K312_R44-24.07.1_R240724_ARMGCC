/*******************************************************************************
**                            HYUNDAI MOTORS GROUP                            **
**                                                                            **
**                            All rights reserved                             **
**                                                                            **
**            You can NOT use this sample code for Product Release            **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "App_Lin.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define APP_LIN_SCHEDULE_NONE  (0xFF)
Rte_ModeType_MDG_LinSchedule_LIN1 LddPrevLinSchedule, LddNextLinSchedule;
uint16 AppLin_ScheduleCmd = APP_LIN_SCHEDULE_NONE;

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*This function is provided as a sample.
Purpose: Request to change LIN schedule.
It can be deleted, but you need to create a user Applicatoin SWC and connect DataMapping to it again.*/
FUNC(void, App_Lin_LIN1_CODE) Sym_LinScheduleRequest_LIN1(void)
{
  Rte_Write_P_SR_LIN1_SCHEDULE_CHANGE_LinSchedule_LIN1((VAR(uint8, AUTOMATIC))AppLin_ScheduleCmd);
}

/*This function is provided as a sample.
Purpose: Request to change LIN schedule.
It can be deleted, but you need to create a user Applicatoin SWC and connect DataMapping to it again.*/
FUNC(void, App_Lin_LIN1_CODE) Sym_LinScheduleRequest_LIN2(void)
{
  Rte_Write_P_SR_LIN2_SCHEDULE_CHANGE_LinSchedule_LIN2((VAR(uint8, AUTOMATIC))AppLin_ScheduleCmd);
}

/*This function is provided as a sample.
Purpose: Request to change LIN schedule.
It can be deleted, but you need to create a user Applicatoin SWC and connect DataMapping to it again.*/
FUNC(void, App_Lin_LIN1_CODE) Sym_LinScheduleSwitch_LIN1(void)
{
  Rte_Mode_App_Lin_LIN1_R_MSR_LIN1_SCHEDULE_INDICATION_LinSchedule_LIN1(&LddPrevLinSchedule, &LddNextLinSchedule);

  if(LddNextLinSchedule > 0x2000)
  {
    LddNextLinSchedule &= 0x00FF;
  }
}

/*This function is provided as a sample.
Purpose: Request to change LIN schedule.
It can be deleted, but you need to create a user Applicatoin SWC and connect DataMapping to it again.*/
FUNC(void, App_Lin_LIN1_CODE) Sym_LinScheduleSwitch_LIN2(void)
{
  Rte_Mode_App_Lin_LIN1_R_MSR_LIN2_SCHEDULE_INDICATION_LinSchedule_LIN2(&LddPrevLinSchedule, &LddNextLinSchedule);
  
  if(LddNextLinSchedule > 0x2000)
  {
    LddNextLinSchedule &= 0x00FF;
  }
}

/*This function is provided as a sample.
Purpose: Request to change LIN schedule.
It can be deleted, but you need to create a user Applicatoin SWC and connect DataMapping to it again.*/
void lin_after_schedule(uint8 channelId, uint8 schId, uint8 schEntryNum, uint8 frameId)
{
}

/*This function is provided as a sample.
Purpose: Request to change LIN schedule.
It can be deleted, but you need to create a user Applicatoin SWC and connect DataMapping to it again.*/
void lin_cbk_err(uint8 channelid, uint8 errcode, uint8 schEntryNum, uint8 frameId)
{
}

/*This function is provided as a sample.
Purpose: Request to change LIN schedule.
It can be deleted, but you need to create a user Applicatoin SWC and connect DataMapping to it again.*/
void AppLin_LinLinScheduleRequest(uint16 scheduleID)
{
  if(scheduleID != AppLin_ScheduleCmd)
  {
    AppLin_ScheduleCmd = scheduleID;
    Sym_LinScheduleRequest_LIN2();
  }
  else
  {
    /* for MISRA-C:2012 15.7 */
  }
}

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
