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
**  SRC-MODULE: MemIf.h                                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR MemIf Module                                          **
**                                                                            **
**  PURPOSE   : Provide macros and declare API                                **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision   Date            By                 Description                  **
********************************************************************************
** 0.0.1      25-Nov-2019     Ngocvm2;HuyP4      Initial Version              **
** 0.0.2      06-Jan-2020     VietPT4            Fix misra rule               **
** 0.0.3      27-Apr-2020     NgocVM2            Follow New V Cycle           **
** 0.0.4      07-Jul-2020     Thaodx          Updated SUD R44-Remine <#11836> **
** 0.0.5      13-Jul-2020     NamTV9          Fix Defect R44-Redmine <#14587> **
** 1.0.1      02-Dec-2021     JH Lim          Fix Defect R44-Redmine <#19737> **
**                                            Fix Defect R44-Redmine <#22520> **
** 1.0.2      29-Jun-2022     SH Park         Improvement mobilegence         **
**                                              Classic <CP44-224>            **
*******************************************************************************/
#ifndef MEMIF_H
#define MEMIF_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: MemIf_SUD_DATATYPE_001  */
#include "Std_Types.h"
/* @Trace: SRS_MemIf_00001 */
#include "MemIf_Cfg.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Global symbols                                        **
*******************************************************************************/
/* Macro for Instance Id to be used as one of the return values on call of
  "Det_GetVersionInfo".*/
#define MEMIF_INSTANCE_ID                      0x00U
#define MEMIF_BROADCAST_ID                     0xFFU
/* one underlying device */
#define MEMIF_ONE_DRIVER                       0x01U
/*******************************************************************************
**                        Service IDs                                         **
*******************************************************************************/
/* @Trace: MemIf_SUD_MACRO_004 */
/* Service ID for SetModes */
#define MEMIF_SETMODE_SID                      0x01U
/* Service ID for Read  */
#define MEMIF_READ_SID                         0x02U
/* Service ID for Write  */
#define MEMIF_WRITE_SID                        0x03U
/* Service ID for Cancel  */
#define MEMIF_CANCEL_SID                       0x04U
/* Service ID for Get Status  */
#define MEMIF_GETSTATUS_SID                    0x05U
/* Service ID for Get Job Result  */
#define MEMIF_GETJOBRESULT_SID                 0x06U
/* Service ID for Invalidate Block */
#define MEMIF_INVALIDATEBLOCK_SID              0x07U
/* Service ID for  Erase Immediate Block */
#define MEMIF_ERASEIMMEDIATEBLOCK_SID          0x09U
/* Service ID for Get Version Info  */
#define MEMIF_GETVERSIONINFO_SID               0x08U

/*******************************************************************************
**                      DET Error Codes                                       **
*******************************************************************************/
/* @Trace: MemIf_SUD_MACRO_007 SRS_BSW_00327 */
/* DET code for invalid device number */
#define MEMIF_E_PARAM_DEVICE                   0x01U
/* DET code for invalid pointer for GetVersionInfo */
#define MEMIF_E_PARAM_POINTER                  0x02U
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#if (MEMIF_ONE_DRIVER == MEMIF_NO_OF_DEVICES)
  /* In case unuse DeviceIndex Parameter */
  #define MEMIF_UNUSE(DeviceIndex) (void)(DeviceIndex)
#endif

#define MEMIF_START_SEC_CODE
#include "MemMap.h"

extern FUNC(void, MEMIF_CODE) MemIf_SetMode(\
  VAR(MemIf_ModeType, AUTOMATIC) Mode);

extern FUNC(MemIf_StatusType, MEMIF_CODE) MemIf_GetStatus(\
  VAR(uint8, AUTOMATIC) DeviceIndex);

extern FUNC(Std_ReturnType, MEMIF_CODE) MemIf_Read(\
  VAR(uint8, AUTOMATIC) DeviceIndex, VAR(uint16, AUTOMATIC) BlockNumber,\
  VAR(uint16, AUTOMATIC) BlockOffset,\
  P2VAR(uint8, AUTOMATIC, MEMIF_APPL_DATA) DataBufferPtr,\
  VAR(uint16, AUTOMATIC) Length);

extern FUNC(Std_ReturnType, MEMIF_CODE) MemIf_Write(\
  VAR(uint8, AUTOMATIC) DeviceIndex, VAR(uint16, AUTOMATIC) BlockNumber,\
  P2CONST(uint8, AUTOMATIC, MEMIF_APPL_CONST) DataBufferPtr);

extern FUNC(void, MEMIF_CODE) MemIf_Cancel(VAR(uint8, AUTOMATIC) DeviceIndex);

extern FUNC(MemIf_JobResultType, MEMIF_CODE) MemIf_GetJobResult(\
  VAR(uint8, AUTOMATIC) DeviceIndex);

extern FUNC(Std_ReturnType, MEMIF_CODE) MemIf_InvalidateBlock(\
  VAR(uint8, AUTOMATIC) DeviceIndex, VAR(uint16, AUTOMATIC) BlockNumber);

extern FUNC(Std_ReturnType, MEMIF_CODE) MemIf_EraseImmediateBlock(\
  VAR(uint8, AUTOMATIC) DeviceIndex, VAR(uint16, AUTOMATIC) BlockNumber);

/* Enable/Disable Version Information */
#if (STD_ON == MEMIF_VERSION_INFO_API)
  extern FUNC(void, MEMIF_CODE) MemIf_GetVersionInfo(\
    P2VAR(Std_VersionInfoType, AUTOMATIC, MEMIF_APPL_DATA) VersionInfoPtr);
#endif /* STD_ON == MEMIF_VERSION_INFO_API */

#define MEMIF_STOP_SEC_CODE
#include "MemMap.h"

#endif /* MEMIF_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
