/*******************************************************************************
**                                                                            **
**  (C) 2022 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Fbl_SharedCfg.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Provide SharedRAM and StartUp Command Address for FBL and DCM **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Fbl_Stub.h"
/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     17-Nov-2022   LinhTT36     Initial version                       **
*******************************************************************************/


/*******************************************************************************
** Function Name        : Fbl_SetStartupCommand                               **
**                                                                            **
** Description          : This function set startup command value to a        **
**                        SharedRAM address that is reserved for FOTA         **
**                        and RTSW                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : command                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
#define MAINSW_START_SEC_CRC
#include "Fbl_SharedMemMap.h"
FUNC(void, FOTA_CODE) Fbl_SetStartupCommand(VAR(uint32,FOTA_VAR) command)
{
  *FBL_STARTUP_COMMAND_PTR = command;
}
#define MAINSW_STOP_SEC_CRC
#include "Fbl_SharedMemMap.h"
/*******************************************************************************
** Function Name        : Fbl_GetProgConditionsAddress                        **
**                                                                            **
** Description          : This function provide SharedRAM address which is    **
**                        which is used by both FOTA and RTSW                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : (Dcm_McuDepProgConditionsType*)FBL_COMMON_RAM_PTR   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
#define MAINSW_START_SEC_CRC
#include "Fbl_SharedMemMap.h"
/* polyspace-begin MISRA-C3:20.7 [Not a defect:Low] "No Impact of this rule violation" */
FUNC(Dcm_McuDepProgConditionsType*,FOTA_CODE) Fbl_GetProgConditionsAddress(void)
/* polyspace-end MISRA-C3:20.7 [Not a defect:Low] "No Impact of this rule violation" */
{
  return (Dcm_McuDepProgConditionsType*)FBL_COMMON_RAM_PTR;
}
#define MAINSW_STOP_SEC_CRC
#include "Fbl_SharedMemMap.h"
/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
