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
**  SRC-MODULE: Dem_Component.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Event Manager                              **
**                                                                            **
**  PURPOSE   : C header for Dem_Component.c                                  **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By            Description                          **
********************************************************************************
** 1.0.1.0   07-May-2021   HaoLT6        R44-Redmine #18724                   **
** 1.0.0     26-Feb-2021   EK Kim        Initial version                      **
*******************************************************************************/

#ifndef DEM_COMPONENT_H
#define DEM_COMPONENT_H


/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem_PCTypes.h"
#include "SchM_Dem.h"


/*******************************************************************************
**                  Extern Function Definition                                **
*******************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"

#if (DEM_NUMBER_OF_DEM_COMPONENT > DEM_ZERO )
extern FUNC(void, DEM_CODE)  Dem_Component_Init(void);
#endif

#if ((DEM_NUMBER_OF_EVENTS > DEM_ZERO) && \
     (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY))
extern FUNC(void, DEM_CODE) Dem_EventAvailable_Init(void);
#endif

#if (DEM_NUMBER_OF_DEM_COMPONENT > DEM_ZERO)
extern FUNC(void, DEM_CODE) Dem_CheckConsecutiveFault(
  Dem_EventIdType EventId, Dem_EventStatusType EventStatus);

extern FUNC(void, DEM_CODE) Dem_ComponentProcessing(Dem_EventIdType EventId);
#endif

#define DEM_STOP_SEC_CODE
#include "MemMap.h"


#endif /* DEM_COMPONENT_H */
