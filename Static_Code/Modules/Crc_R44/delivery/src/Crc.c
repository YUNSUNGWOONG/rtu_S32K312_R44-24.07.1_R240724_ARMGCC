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
**  SRC-MODULE: Crc.c                                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crc Library Module                                    **
**                                                                            **
**  PURPOSE   : Implementation of Version Information for CRC Library Module  **
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
** 0.0.1     05-Sep-2019   TuanVA17         Initial Version                   **
** 0.0.2     03-Mar-2020   TienNV21         Update traceability apply new     **
**                                          V-Cycle                           **
** 0.0.3     07-Apr-2020   TienNV21         Update code annotation            **
** 1.0.2     06-Jan-2022   JHLim            Redmine #21418                    **
** 1.0.2.2   29-Jun-2022   SH Park          Improvement mobilegence           **
**                                            Classic <CP44-224>              **
** 1.0.3     12-Aug-2022   SH Park          Improvement mobilegence           **
**                                            Classic <CP44-81>               **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: SafeCRC_SUD_FILE_001 */
#include "Crc.h"                       /* Crc Header file */

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CRC_START_SEC_CODE_ASIL_D
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Crc_GetVersionInfo                                  **
**                                                                            **
** Service ID           : CRC_GETVERSIONINFO_SID: 0x04                        **
**                                                                            **
** Description          : This function returns the version information of CRC**
**                        Library module.                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : VersionInfo : Pointer to where to store             ** 
**                                      the version information of CRC module **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/

/* @Trace: SRS_BSW_00407 SRS_BSW_00411 */
FUNC(void, CRC_CODE) Crc_GetVersionInfo
  (P2VAR(Std_VersionInfoType, AUTOMATIC, CRC_APPL_DATA) VersionInfo)
{
  if (NULL_PTR != VersionInfo)
  {
    /* @Trace: SafeCrc_SUD_API_001 */
    /* Copy the vendor Id */
    VersionInfo->vendorID = CRC_VENDOR_ID; /* polyspace MISRA2012:D4.14 [Justified:Low] "Null pointer is checked before used" */
    /* Copy the module Id */
    VersionInfo->moduleID = CRC_MODULE_ID;
    /* Copy Software Major Version */
    VersionInfo->sw_major_version = CRC_SW_MAJOR_VERSION;
    /* Copy Software Minor Version */
    VersionInfo->sw_minor_version = CRC_SW_MINOR_VERSION;
    /* Copy Software Patch Version */
    VersionInfo->sw_patch_version = CRC_SW_PATCH_VERSION;
  }
  /* @Trace: SafeCrc_SUD_API_002 */
  /* If the received Versioninfo pointer is NULL it shall return from the
  Crc_GetVersionInfo API without performing any further functionality. */
}
#define CRC_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
