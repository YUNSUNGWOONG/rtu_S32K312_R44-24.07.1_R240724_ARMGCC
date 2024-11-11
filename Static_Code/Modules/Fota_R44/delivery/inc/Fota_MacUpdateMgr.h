/*******************************************************************************
**                                                                            **
**  (C) 2022 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Fota_AreaSyncMgr.h                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR FOTA                                                  **
**                                                                            **
**  PURPOSE   : Provide all marcos for internal module                        **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By                        Description              **
********************************************************************************
*******************************************************************************/
#ifndef FOTA_MACUPDATEMGR_H
#define FOTA_MACUPDATEMGR_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#include "Fota_IntTypes.h"
#include "Fota_Types.h"

/*******************************************************************************
**                        Service IDs                                         **
*******************************************************************************/

/*******************************************************************************
**                      DET Error Codes                                       **
*******************************************************************************/

/*******************************************************************************
**                     Macros                                                 **
*******************************************************************************/




/*******************************************************************************
**                     Global Data Types                                      **
*******************************************************************************/
typedef enum
{
  FOTA_MACUPDATE_IDLE=0,
  FOTA_MACUPDATE_START,
  FOTA_MACUPDATE_END,
  FOTA_MACUPDATE_ERR
} Fota_MacUpdateStatType;

/*******************************************************************************
**                     Global Data                                            **
*******************************************************************************/

/*******************************************************************************
**                     Function Prototypes                                    **
*******************************************************************************/
#define Fota_START_SEC_CODE
#include "Fota_MemMap.h"

extern FUNC(Fota_MacUpdateStatType, FOTA_CODE) Fota_GetMacUpdateState(void);
extern FUNC(Std_ReturnType, FOTA_CODE) Fota_MacUpdateRequest(void);
extern FUNC(Fota_JobResultType, FOTA_CODE) Fota_MacUpdateResult(void);
extern FUNC(void, FOTA_CODE) Fota_MacUpdateMain(void);


#define Fota_STOP_SEC_CODE
#include "Fota_MemMap.h"

#endif /* FOTA_AREASYNCMGR_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
