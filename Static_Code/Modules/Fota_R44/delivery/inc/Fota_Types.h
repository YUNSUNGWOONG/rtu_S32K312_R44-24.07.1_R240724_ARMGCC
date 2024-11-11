/*******************************************************************************
**                                                                            **
**  (C) 2022 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Fota_Types.h                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR FOTA                                                  **
**                                                                            **
**  PURPOSE   : Provides all of the user type define                          **
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
** 1.0.0     28-Dec-2022   VuPH6          Initial version                      **
*******************************************************************************/
#ifndef FOTA_TYPES_H
#define FOTA_TYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Error Id for valid check argument of function */
#define FOTA_E_NULL_POINTER                                          ((uint8) 0)
#define FOTA_E_BLOCKID_INVALID                                       ((uint8) 1)
#define FOTA_E_ADDRESS_LENGTH_INVALID                                ((uint8) 2)

/* Error Id for memory function */
#define FOTA_E_ERASE_REQUEST_FAILED                                  ((uint8) 3)
#define FOTA_E_ERASE_JOB_FAILED                                      ((uint8) 4)
#define FOTA_E_WRITE_REQUEST_FAILED                                  ((uint8) 5)
#define FOTA_E_WRITE_JOB_FAILED                                      ((uint8) 6)
#define FOTA_E_WRITE_METADATA_REQUEST_FAILED                        ((uint8) 33)

/* Error Id for verification process */
#define FOTA_E_VERIFY_JOB_FAILED                                     ((uint8) 7)
#define FOTA_E_VERIFY_CSM_START_FAILED                               ((uint8) 8)
#define FOTA_E_VERIFY_CSM_UPDATE_FAILED                              ((uint8) 9)
#define FOTA_E_VERIFY_CSM_FINIISH_FAILED                            ((uint8) 10)
#define FOTA_E_VERIFY_CRC_FAILED                                    ((uint8) 11)

/* Error Id for software version check from Fota.c */
#define FOTA_E_SVC_ERASE_CHECK_FAILED                               ((uint8) 12)
#define FOTA_E_SVC_UPDATE_HEADER_FAILED                             ((uint8) 13)
#define FOTA_E_SVC_UPDATE_TRAILER_FAILED                            ((uint8) 14)
#define FOTA_E_SVC_RECOVERY_TRAILER_FAILED                          ((uint8) 15)
#define FOTA_E_SVC_ERASE_LENGTH_INVALID                             ((uint8) 16)

/* Error Id for software version check from Fota_SoftwareVersionCheck.c */
#define FOTA_E_SVC_ERASE_REQUEST_FAILED                             ((uint8) 17)
#define FOTA_E_SVC_WRITE_REQUEST_FAILED                             ((uint8) 18)
#define FOTA_E_SVC_CRC_CHECK_FAILED                                 ((uint8) 19)
#define FOTA_E_SVC_HEADER_TRAILER_ADDRESS_INVALID                   ((uint8) 20)
#define FOTA_E_SVC_MEM_JOB_FAILED                                   ((uint8) 21)
#define FOTA_E_SVC_DOWNGRADE_DETECT                                 ((uint8) 34)
#define FOTA_E_BLK_UPDATE_FAIL                                      ((uint8) 35)
/* Error Id for secure flash 2.0 */
#define FOTA_E_DECRYPT_START_FAILED                                 ((uint8) 22)
#define FOTA_E_DECRYPT_UPDATE_FAILED                                ((uint8) 23)
#define FOTA_E_DECRYPT_FINISH_FAILED                                ((uint8) 24)
#define FOTA_E_DERIVE_KEY_FAILED                                    ((uint8) 25)

/* Error Id for Updater operation */
#define FOTA_E_UPDATER_ERASE_REQUEST_FAILED                         ((uint8) 26)
#define FOTA_E_UPDATER_ADDRESS_LENGTH_INVALID                       ((uint8) 27)
#define FOTA_E_UPDATER_CALIB_ADDRESS_LENGTH_FAILED                  ((uint8) 28)
#define FOTA_E_UPDATER_WRITE_REQUEST_FAILED                         ((uint8) 29)
#define FOTA_E_UPDATER_VERIFY_JOB_FAILED                            ((uint8) 30)
#define FOTA_E_UPDATER_WRITE_PARTITION_REQUEST_FAILED               ((uint8) 31)
#define FOTA_E_UPDATER_MEM_JOB_FAILED                               ((uint8) 32)
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* FOTA_TYPES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
