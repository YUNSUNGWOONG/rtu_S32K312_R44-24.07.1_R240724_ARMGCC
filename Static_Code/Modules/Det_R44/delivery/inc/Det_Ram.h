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
**  SRC-MODULE: Det_Ram.h                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Default Error Tracer Module                           **
**                                                                            **
**  PURPOSE   : Provision of callback functions and their functionality.      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 0.0.1     30-Sep-2019   DanhLT2      Initial Version                       **
*******************************************************************************/

#ifndef DET_RAM_H
#define DET_RAM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"                  /* standard AUTOSAR types */
#include "Det_PCTypes.h"                /* Det PCTypes header file */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/* @Trace: Det_SUD_GLOBALVAR_001*/
#define DET_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

/* Global variable to store status of Det */
extern VAR(boolean, DET_VAR_POWER_ON_INIT) Det_GblInitStatus;
#define DET_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#define DET_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

extern VAR(Det_ErrorStatusType, DET_VAR_POWER_ON_INIT) Det_GaaErrorStatus;

#if (DET_RAM_BUFFER == STD_ON)
/* Global array of structure to store the development error parameters */
extern VAR(Det_ErrorType, DET_VAR_POWER_ON_INIT) Det_GaaErrors[DET_RAM_BUFFER_SIZE];
#endif /* DET_RAM_BUFFER == STD_ON */

#define DET_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif  /* DET_RAM_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
