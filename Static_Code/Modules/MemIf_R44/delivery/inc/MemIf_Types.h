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
**  SRC-MODULE: MemIf_Types.h                                                 **
**                                                                            **
**  TARGET    : ALL                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR MemIf Module                                          **
**                                                                            **
**  PURPOSE   : Provision of Type Definitions                                 **
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
** 0.0.1     25-Nov-2019   Ngocvm2;HuyP4   Initial Version                    **
** 0.0.2     06-Jan-2020   VietPT4         Fix misra rule                     **
** 0.0.3     27-Apr-2020   NgocVM2         Follow New V Cycle                 **
** 0.0.4     07-Jul-2020   Thaodx          Updated SUD R44-Remine <#11836>    **
** 0.0.5     13-Jul-2020   NamTV9          Fix Defect R44-Redmine <#14587>    **
** 1.0.1     28-Aug-2021   JH Lim          Fix Defect R44-Redmine <#19737>    **
** 1.0.2     29-Jun-2022   SH Park         Improvement mobilegence            **
**                                           Classic <CP44-224>               **
*******************************************************************************/

#ifndef MEMIF_TYPES_H
#define MEMIF_TYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* @Trace: MemIf_SUD_DATATYPE_003 */
/* Type definition for MEMIF status types */
typedef enum
{
  MEMIF_UNINIT = 0U,
  MEMIF_IDLE,
  MEMIF_BUSY,
  MEMIF_BUSY_INTERNAL
}MemIf_StatusType;

/* @Trace: MemIf_SUD_DATATYPE_004 */
/* Type definition for MEMIF job result types */
typedef enum
{
  MEMIF_JOB_OK = 0U,
  MEMIF_JOB_FAILED,
  MEMIF_JOB_PENDING,
  MEMIF_JOB_CANCELED,
  MEMIF_BLOCK_INCONSISTENT,
  MEMIF_BLOCK_INVALID
}MemIf_JobResultType;

/* @Trace: MemIf_SUD_DATATYPE_005 */
/* Type definition for MEMIF mode types */
typedef enum
{
  MEMIF_MODE_SLOW = 0U,
  MEMIF_MODE_FAST
}MemIf_ModeType;

#endif /* MEMIF_TYPES_H */
/*******************************************************************************
**                     End of File                                            **
*******************************************************************************/
