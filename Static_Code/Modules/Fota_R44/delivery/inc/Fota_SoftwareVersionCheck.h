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
**  SRC-MODULE: Fota_SwVersionCheck.c                                          **
**                                                                            **
**  TARGET    : ALL													                                  **
**                                                                            **
**  PRODUCT   : Cdd_FBL                                                       **
**                                                                            **
**  PURPOSE   : SW Version Check                                              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 2.3.0.0   12-May-2022   JSChoi           Redmine #34783                    **
** 1.23.0    27-Dec-2021   JH Lim           R40-Redmine #31776                **
*******************************************************************************/

#ifndef FOTA_SOFTWAREVERSIONCHECKER_H
#define FOTA_SOFTWAREVERSIONCHECKER_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Std_Types.h"
#include "Fota_IntTypes.h"

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
/* The following macros are used to specify job type */
typedef enum {
  FOTA_BLK_INIT = 0,
  /* State 1 : Header and Trailer have no value */
  FOTA_BLK_VIRGIN,
  /* State 2 : Header is Invalid, Trailer is Valid */
  FOTA_BLK_HEADER_INVALID,
  /* State 3 : Header's current version is higher than Trailer */
  FOTA_BLK_HEADER_UPDATED,
  /* State 4 : Both Current version are same */
  FOTA_BLK_NORMAL,
  /* State 5 : Header is valid, Trailer is Invalid */
  FOTA_BLK_TRAILER_INVALID,
  /* State 6 : Trailer version is more latest then Header */
  FOTA_BLK_TRAILER_UPDATED,
} Fota_BlkStateType;

typedef enum
{
  FOTA_MEM_INIT = 0,
  FOTA_MEM_ERASE_TRAILER_BEFORE_ERASE,
  FOTA_MEM_WRITE_HEADER_UPDATE,
  FOTA_MEM_WRITE_TRAILER_UPDATE_CPD,
  FOTA_MEM_RECOVERY_TRAILER_BEFORE_ERASE_ROM,
  FOTA_MEM_WRITE_RECOVERY_TRAILER,
  FOTA_MEM_ERASE_TRAILER_AFTER_DOWNLOAD,
  FOTA_MEM_WAITING_RECOVERY_TRAILER
} Fota_VersionCheckMemType;

typedef enum {
  /* State 0 : INIT State */
  FOTA_VERSION_CHECK_INIT = 0,
  /* State 1 : Action version check before erase memory in RoutineControl */
  FOTA_VERSION_CHECK_BEFORE_ERASE,
  /* State 2 : Action version check after blk header is written */
  FOTA_VERSION_CHECK_UPDATE_HEADER_AFTER_DOWNLOAD,
  /* State 3 : Action version check in CPD check */
  FOTA_VERSION_CHECK_UPDATE_TRAILER_AFTER_CPD,
  /* State 4 : Action version check in CPD failed */
  FOTA_VERSION_CHECK_ERASE_TRAILER_BEFORE_ERASE_ROM,

  FOTA_VERSION_CHECK_MEM_JOB_RESULT,

} Fota_VersionCheckStateType;

typedef enum {
  /* State 0 : INIT State */
  FOTA_VERSION_CHECK_BEFORE_ERASE_REQUEST = 0,
  /* State 1 : Version OK */
  FOTA_VERSION_CHECK_AFTER_DOWNLOAD_REQUEST,
  /* State 2 : Version NOT OK */
  FOTA_VERSION_CHECK_CPD_REQUEST,
  /* State 2 : Version NOT OK */
  FOTA_VERSION_CHECK_ERASE_ROM_REQUEST,
} Fota_VersionCheckRequestType;

typedef struct
{
  uint32 magicNumber;
  uint8 lengthCurrentVersion;
  uint8 lengthPreviousVersion;
  uint8 currentVersion[127];
  uint8 previousVersion[127];
} Fota_BlkInfo;

typedef struct
{
  Fota_BlkInfo blkInfo;
  uint16 blkCrcInit;
  uint16 blkCrc16;
} Fota_BlkCrcInfo;

typedef enum
{
  FOTA_BLK_HEADER = 0,
  FOTA_BLK_TRAILER,
  FOTA_BLK_TRAILER_LAST
} Fota_BlkType;

typedef enum
{
  FOTA_VERSION_CHECK_EQUAL = 0,
  FOTA_VERSION_CHECK_SMALLER,
  FOTA_VERSION_CHECK_GREATER
} Fota_VersionCompareType;

typedef struct
{
  /* [1] Calculate offset of Address
   *
   *   +----------------+-------------------+---------------+--------------------+------+-----+-----------+--------------+
   *   | magicNumber(4) | currentVersion(4) | reserved(248) | previousVersion(4) | crcInit(2) | crcVal(2) | reserved(248)|
   *   +----------------+-------------------+---------------+--------------------+------+-----+-----------+--------------+
   *   |<------------0x100 (App Data)---------------------->|<-----------------------0x100 (FBL Note)-------------------->|
   */
  /* Magic Number 4-byte*/
  uint32 magicNumber;

  /* Current Version 4-byte */
  uint8 currentVersion[127];

  uint8 lengthCurrentVersion;
  /* Reserved for write unit 248-byte */
  uint8 reserved_1[124];
  /* Current Version 4-byte */
  uint8 previousVersion[127];

  uint8 lengthPreviousVersion;
  /* crcInit 2-byte */
  uint16 crcInit;
  /* crcVal 2-byte */
  uint16 crcVal;
  /* Reserved for write unit 248-byte */
  uint8 reserved_2[124];
} Fota_BlkFlashInfo;

/* Instance id */
#define SVC_INSTANCE_ID                                               ((uint8)0)

#define SVC_MAIN_FUNCTION_SID                                         ((uint8)0)

#define FOTA_BLK_MAGIC_NUMBER_HEADER                                (0x6D6F6269U)

#define FOTA_BLK_MAGIC_NUMBER_TRAILER                               (0x6C67656EU)

#define FOTA_BLK_SWVERSION_INIT                                           (0x00U)

#define FOTA_BLK_SWVERSION_MAX                                      (0xFFFFFFFFU)

#define FOTA_SVC_MAGIC_LENGTH                                              (0x4U)

#define FOTA_SVC_LENGTH_OF_LENGTH                                          (0x2U)

#define FOTA_SVC_MAX_LENGTH_SUPPORT                                       (0x7FU)

#define FOTA_SVC_SWVERSION_LENGTH_INIT                                     (0x4U)

#define FOTA_BLK_CRC_TARGET_LENGTH                                       (0x104U)

#define FOTA_BLK_HALF_LENGTH                                             (0x100U)

#define FOTA_BLK_TOTAL_LENGTH                                            (0x200U)
/*******************************************************************************
**                      DET ERROR CODES                                       **
*******************************************************************************/
/* Version check Index Failed */
#define SVC_E_VCINDEX                                              ((uint8)0x00)

/* Detect the Flash Downgrade  */
#define SVC_E_DETECT_DOWNGRADE                                     ((uint8)0x01)

/* Detect the Flash Downgrade  */
#define SVC_E_BLK_VERIFY_FAIL                                      ((uint8)0x02)

/* Detect the Flash Downgrade  */
#define SVC_E_BLK_RECOVERY_FAIL                                    ((uint8)0x03)

/* Detect the Flash Downgrade  */
#define SVC_E_BLK_UPDATE_FAIL                                      ((uint8)0x04)

/* Detect the Flash Downgrade  */
#define SVC_E_BLK_NOT_FOUND                                        ((uint8)0x05)


/*******************************************************************************
**                      DET ERROR CODES                                       **
*******************************************************************************/

/*******************************************************************************
**                        Global Function Definition                          **
*******************************************************************************/
#define Fota_START_SEC_CODE
#include "Fota_MemMap.h"

extern FUNC(Std_ReturnType, FOTA_CODE) Fota_SvcInit(uint8 swUnitIndex);

extern FUNC(void, FOTA_CODE) Fota_VersionCheckRequest(
                                  Fota_VersionCheckRequestType requestType,
                                  uint32 addressCheck);

extern FUNC(Fota_JobResultType, FOTA_CODE) Fota_VersionCheckResult(void);

extern FUNC(void, FOTA_CODE) Fota_MainVersionCheck(void);

extern FUNC(uint32, FOTA_CODE) Fota_VersionCheckEraseRomLength(
                                                          uint8 swUnitIndex);

extern FUNC(void, FOTA_CODE) Fota_SvcResetGlobalVariable(uint8 indexSwUnit);

#define Fota_STOP_SEC_CODE
#include "Fota_MemMap.h"

#endif /* Fota_SWCHECK_H */
/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
