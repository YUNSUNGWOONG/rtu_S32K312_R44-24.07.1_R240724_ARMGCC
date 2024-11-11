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
**  SRC-MODULE: CanDrv_422_Compat.h                                           **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CanIf                                                 **
**                                                                            **
**  PURPOSE   : Type definition of AUTOSAR CanIf                              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By              Description                        **
********************************************************************************
** 1.0.5  30-Jun-2022    HieuTM8       #CP44-130                              **
** 1.0.1  22-Sep-2021    HieuTM8       #20891                                 **
** 1.0.0  21-Dec-2020    SJ Kim        Initialization (Support CanDrv 4.2.2)  **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#ifndef CANDRV_422_COMPAT_H
#define CANDRV_422_COMPAT_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Can.h"                 /* CAN driver header file*/
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* polyspace +5 MISRA2012:D4.9 [No action planned:Low] "use macro function to reduce length of code"*/
#define CANIF_CANDRV_AR(x,y,z) 	\
								((CAN_AR_RELEASE_MAJOR_VERSION == x) && \
								(CAN_AR_RELEASE_MINOR_VERSION == y) && \
								(CAN_AR_RELEASE_REVISION_VERSION ==z))
#if CANIF_CANDRV_AR(4,2,2)
/* State transitions that are used by the function CanIf_SetControllerMode */
typedef enum
{
  CAN_CS_UNINIT = 0,
  CAN_CS_SLEEP,
  CAN_CS_STARTED,
  CAN_CS_STOPPED
} Can_ControllerStateType;

typedef enum
{
  CANIF_CS_UNINIT = 0,
  CANIF_CS_SLEEP,
  CANIF_CS_STARTED,
  CANIF_CS_STOPPED
} CanIf_ControllerModeType;

/* Error states of a CAN controller */
typedef enum {
	CAN_ERRORSTATE_ACTIVE = 0,
	CAN_ERRORSTATE_PASSIVE,
	CAN_ERRORSTATE_BUSOFF
} Can_ErrorStateType;
#endif

#endif /* CANDRV_422_COMPAT_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
