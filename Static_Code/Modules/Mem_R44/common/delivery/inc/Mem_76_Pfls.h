/*******************************************************************************
**                                                                            **
**  (C) 2022 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Mem_76_Pfls.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Memory Driver                                         **
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
#ifndef MEM_76_PFLS_H
#define MEM_76_PFLS_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#include "Mem_76_Pfls_Cfg.h"
#include "string.h"

#if (MEM_76_PFLS_USE_NVM == STD_ON)
#include "NvM.h"
#endif
/*******************************************************************************
**                        Service IDs                                         **
*******************************************************************************/
#define MEM_76_PFLS_MEMCPY(dst, src, size)  (memcpy((dst), (src), (size)))
#define MEM_76_PFLS_MEMSET(dst, src, size)  (memset((dst), (src), (size)))
/* @Trace: SRS_Mem_BSW_00415 Mem_76_Pfls_SUD_MACRO_001 */
#define MEM_76_PFLS_INIT_SID                ((uint8)0x01)
#define MEM_76_PFLS_DEINIT_SID              ((uint8)0x0B)
#define MEM_76_PFLS_SUSPEND_SID             ((uint8)0x0C)
#define MEM_76_PFLS_RESUME_SID              ((uint8)0x0D)
#define MEM_76_PFLS_PROPAGATE_ERROR_SID     ((uint8)0x08)
#define MEM_76_PFLS_READ_SID                ((uint8)0x05)
#define MEM_76_PFLS_WRITE_SID               ((uint8)0x06)
#define MEM_76_PFLS_ERASE_SID               ((uint8)0x07)
#define MEM_76_PFLS_BLANK_CHECK_SID         ((uint8)0x09)
#define MEM_76_PFLS_GETJOBRESULT_SID        ((uint8)0x04)
#define MEM_76_PFLS_HW_SPECIFIC_SERVICE_SID ((uint8)0x0A)
#define MEM_76_PFLS_MAINFUNCTION_SID        ((uint8)0x03)
#define MEM_76_PFLS_GETVERSIONINFO_SID      ((uint8)0x02)

/*******************************************************************************
**                      DET Error Codes                                       **
*******************************************************************************/
/* @Trace: SRS_Mem_BSW_00385 Mem_76_Pfls_SUD_MACRO_002 Mem_76_Pfls_SUD_MACRO_002 */
/* API service called with wrong parameter */
/* API service called without module initialization */
#define MEM_76_PFLS_E_UNINIT                  ((uint8)0x01)
/* API service called with NULL pointer */
#define MEM_76_PFLS_E_PARAM_POINTER           ((uint8)0x02)
/* API service called with an invalid address */
#define MEM_76_PFLS_E_PARAM_ADDRESS           ((uint8)0x03)
/* API service called with an invalid length */
#define MEM_76_PFLS_E_PARAM_LENGTH            ((uint8)0x04)
/* API service called with an invalid driver instance ID */
#define MEM_76_PFLS_E_PARAM_INSTANCE_ID       ((uint8)0x05)
/* API service called while a job request is still in progress */
#define MEM_76_PFLS_E_JOB_PENDING             ((uint8)0x06)

/*******************************************************************************
**                     HardWare Specific Service                              **
*******************************************************************************/

/* @Trace: SRS_Mem_MemHwAb_14042 Mem_76_Pfls_SUD_DATATYPE_007 */
typedef enum
{
  MEM_76_PFLS_ACTIVE_BANK_CHECK        =   1U,
  MEM_76_PFLS_GET_FLASH_ALIGNMENT      =   2U,
  MEM_76_PFLS_GET_SECTOR_SIZE          =   3U,
  MEM_76_PFLS_GET_OFFSET_STD_ALT       =   4U,
  MEM_76_PFLS_TOOLBOX_ACTIVE_SERVICE   =   5U,
  MEM_76_PFLS_SWAP_ACTIVE              =   100U,
  MEM_76_PFLS_DIRECT_ADDRESS_ACCESS    =   101U,
  MEM_76_PFLS_ALT_ADDRESS_ACCESS       =   102U,
  MEM_76_PFLS_CANCEL_JOB               =   103U
}Mem_76_Pfls_HwServiceIdType;
/*******************************************************************************
**                     Global Data Types                                      **
*******************************************************************************/
/* Postbuild configuration structure type */
/* @Trace: SRS_Mem_BSW_00414 Mem_76_Pfls_SUD_DATATYPE_002*/
typedef struct
{
  uint8 Dummy;
} Mem_76_Pfls_ConfigType;
/* @Trace: SRS_Mem_BSW_14051 Mem_76_Pfls_SUD_DATATYPE_003 */
/* Read data user buffer type */
typedef uint8 Mem_76_Pfls_DataType;
/* Read data user buffer type */
/* @Trace: SRS_Mem_MemHwAb_14045 SRS_Mem_MemHwAb_14046 SRS_Mem_MemHwAb_14049 Mem_76_Pfls_SUD_DATATYPE_001 */
typedef uint32 Mem_76_Pfls_AddressType;
/* Job end notification function called by Mem in case the job processing is
 * configured for job end notification
 */
/* @Trace: Mem_76_Pfls_SUD_DATATYPE_005 */
/* Asynchronous job result type */
typedef enum
{
  /* The last job has been finished successfully */
  MEM_JOB_OK = 0x00U,
  /* A job is currently being processed */
  MEM_JOB_PENDING,
  /* Job failed for some unspecific reason */
  MEM_JOB_FAILED,
  /* The checked page is not blank */
  MEM_INCONSISTENT,
  /* Uncorrectable ECC errors occurred during memory access */
  MEM_ECC_UNCORRECTED,
  /* Correctable ECC errors occurred during memory access */
  MEM_ECC_CORRECTED
} Mem_76_Pfls_JobResultType;
/* Physical memory device length type */
/* @Trace: Mem_76_Pfls_SUD_DATATYPE_006 */
typedef uint32 Mem_76_Pfls_LengthType;
/* Hardware specific service request identifier type */
/* @Trace: SRS_Mem_MemHwAb_14043 Mem_76_Pfls_SUD_DATATYPE_004 */
typedef uint32 Mem_76_Pfls_InstanceIdType;

#if (MEM_76_PFLS_DEV_ERROR_DETECT == STD_ON)
#define MEM_76_PFLS_REPORT_ERROR(sid,error) \
do {\
  (void)Det_ReportError(MEM_76_PFLS_MODULE_ID, MEM_76_PFLS_INSTANCE_ID, (sid), (error));\
} while(0)
#else
#define MEM_76_PFLS_REPORT_ERROR(sid,error)  do {} while(0)
#endif /* end of DET */

/*******************************************************************************
**                     Global Data                                            **
*******************************************************************************/

/*******************************************************************************
**                     Function Prototypes                                    **
*******************************************************************************/
#define MEM_76_PFLS_START_SEC_CODE
#include "MemMap.h"

extern FUNC(void, MEM_76_PFLS_CODE) Mem_76_Pfls_Init(\
  P2CONST(Mem_76_Pfls_ConfigType, AUTOMATIC, MEM_76_PFLS_APPL_CONST) ConfigPtr);

extern FUNC(void, MEM_76_PFLS_CODE) Mem_76_Pfls_DeInit(void);

extern FUNC(void, MEM_76_PFLS_CODE) Mem_76_Pfls_GetVersionInfo(\
  P2VAR(Std_VersionInfoType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) versionInfoPtr);

extern FUNC(Mem_76_Pfls_JobResultType, MEM_76_PFLS_CODE) Mem_76_Pfls_GetJobResult(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) instanceId);

extern FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_Suspend(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) instanceId);

extern FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_Resume(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) instanceId);

extern FUNC(void, MEM_76_PFLS_CODE) Mem_76_Pfls_PropagateError(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) instanceId);

extern FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_Read(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) instanceId, \
  VAR(Mem_76_Pfls_AddressType, AUTOMATIC) sourceAddress, \
  P2VAR(Mem_76_Pfls_DataType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) destinationDataPtr, \
  VAR(Mem_76_Pfls_LengthType, AUTOMATIC) length);

extern FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_Write(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) instanceId, \
  VAR(Mem_76_Pfls_AddressType, AUTOMATIC) targetAddress, \
  P2CONST(Mem_76_Pfls_DataType, AUTOMATIC, MEM_76_PFLS_APPL_CONST) sourceDataPtr, \
  VAR(Mem_76_Pfls_LengthType, AUTOMATIC) length);

extern FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_Erase(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) instanceId, \
  VAR(Mem_76_Pfls_AddressType, AUTOMATIC) targetAddress, \
  VAR(Mem_76_Pfls_LengthType, AUTOMATIC) length);

extern FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_BlankCheck(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) instanceId, \
  VAR(Mem_76_Pfls_AddressType, AUTOMATIC) targetAddress, \
  VAR(Mem_76_Pfls_LengthType, AUTOMATIC) length);

extern FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_HwSpecificService(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) instanceId, \
  VAR(Mem_76_Pfls_HwServiceIdType, AUTOMATIC) hwServiceId, \
  P2VAR(Mem_76_Pfls_DataType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) dataPtr, \
  P2VAR(Mem_76_Pfls_LengthType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) lengthPtr);

#if (MEM_76_PFLS_USE_NVM == STD_ON)
extern FUNC(NvM_OpStatusType, MEM_76_PFLS_CODE) Mem_76_Pfls_MainFunction(void);
#else
extern FUNC(void, MEM_76_PFLS_CODE) Mem_76_Pfls_MainFunction(void);
#endif

#define MEM_76_PFLS_STOP_SEC_CODE
#include "MemMap.h"

#endif /* MEM_76_PFLS_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
