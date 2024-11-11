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
#ifndef FOTA_AREASYNCMGR_H
#define FOTA_AREASYNCMGR_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#include "Fota_IntTypes.h"
#include "Dcm_Types.h"
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

#define MAX_OF_CMPLOOPCNT 255U
#define FOTA_SYNC_ALL_RETRY_CNT 3U
#define FOTA_SYNC_VERIFIED_NONACT_SWUNIT_RETRY_CNT 1U
#define FOTA_SYNCWAITCNT 100000UL


/*******************************************************************************
**                     Global Data Types                                      **
*******************************************************************************/
typedef enum
{
  FOTA_SYNC_IDLE=0,
  FOTA_SYNC_START,
  FOTA_SYNC_SET_SWUNIT,
  FOTA_SYNC_ERASE_SWUNIT_REQ,
  FOTA_SYNC_ERASE_SWUNIT_CHK,
  FOTA_SYNC_SET_VERIFY_UNIT,
  FOTA_SYNC_SET_VERIFY_UNIT_MODULE,
  FOTA_SYNC_WRITE_FW_REQ,
  FOTA_SYNC_WRITE_FW_CHK,
  FOTA_SYNC_SET_VERIFY_UNIT_MODULE_END,
  FOTA_SYNC_SET_VERIFY_UNIT_END,
  FOTA_SYNC_WRITE_SIG_REQ,
  FOTA_SYNC_WRITE_SIG_CHK,
  FOTA_SYNC_VERIFY_REQ,
  FOTA_SYNC_VERIFY_CHK,
  FOTA_SYNC_WRITE_VFYKEY_REQ,
  FOTA_SYNC_WRITE_VFYKEY_CHK,
  FOTA_SYNC_SET_SWUNIT_END,
  FOTA_SYNC_END,
  FOTA_SYNC_ERR
} Fota_SyncStatType;

typedef enum
{
  FOTA_SYNC_ALL_SWUNIT=0,
  FOTA_SYNC_VERIFIED_NONACT_SWUNIT
} Fota_SyncReqType;

typedef enum
{
  FOTA_SYNC_CANCEL_OFF=0,
  FOTA_SYNC_CANCEL_ON
} Fota_SyncCancelType;


/*******************************************************************************
**                     Global Data                                            **
*******************************************************************************/

/*******************************************************************************
**                     Function Prototypes                                    **
*******************************************************************************/
#define Fota_START_SEC_CODE
#include "Fota_MemMap.h"

extern FUNC(Std_ReturnType, FOTA_CODE) Fota_AreaSyncIdleChk(void);

extern FUNC(Fota_SyncStatType, FOTA_CODE) Fota_GetAreaSyncState(void);

extern FUNC(Std_ReturnType, FOTA_CODE) Fota_AreaSyncRequest(Fota_SyncReqType ren_ReqSync);

extern FUNC(Fota_JobResultType, FOTA_CODE) Fota_AreaSyncResult(void);

extern FUNC(void, FOTA_CODE) Fota_AreaSyncMain(void);


#define Fota_STOP_SEC_CODE
#include "Fota_MemMap.h"

#endif /* FOTA_AREASYNCMGR_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
