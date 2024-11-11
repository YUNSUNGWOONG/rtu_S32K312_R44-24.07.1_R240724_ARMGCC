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
**  SRC-MODULE: NvM_MemIf.h                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR NvM Module                                            **
**                                                                            **
**  PURPOSE   : Callback Function declaration of NVRAM module                 **
**              NvM_JobEndNotification                                        **
**              NvM_JobErrorNotification                                      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision    Date          By          Description                          **
********************************************************************************
** 0.0.1       06-Dec-2019    KienHT11    Initial version                     **
** 0.0.2       04-May-2020    VinhLV5     Update traceability, apply          **
**                                        new v cycle, Fix Misra              **
** 0.0.3       24-Jul-2020    VinhLV5     R44-Redmine #9958                   **
** 1.0.2       27-Aug-2021    JH Lim      R44-Redmine #19726                  **
** 1.1.1.1     29-Jun-2022    SH Park     Improvement mobilegence             **
**                                          Classic <CP44-221>                **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#ifndef NVM_MEMIF_H
#define NVM_MEMIF_H

#include "NvM_Cfg.h"

/* SWS_NvM_00440 */
#if(STD_OFF == NVM_POLLING_MODE)

#define NVM_START_SEC_CODE
#include "MemMap.h"

/* The callback function is used by the underlaying memory abstraction 
to signal end of job without error */
extern FUNC(void, NVM_CODE) NvM_JobEndNotification(void);

/* The callback function is used by the underlaying memory abstraction 
to signal end of job with error */
extern FUNC(void, NVM_CODE) NvM_JobErrorNotification(void);

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (STD_OFF == NVM_POLLING_MODE) */
#endif /* NVM_MEMIF_H */
