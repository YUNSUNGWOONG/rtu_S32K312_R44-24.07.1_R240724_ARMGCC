/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**                                                                            **
** Confidential Proprietary Information. Distribution Limited.                **
** This source code is permitted to be used only in projects contracted       **
** with Hyundai Autoever, and any other use is prohibited.                    **
** If you use it for other purposes or change the source code,                **
** you may take legal responsibility.                                         **
** In this case, There is no warranty and technical support.                  **
**                                                                            **
**  SRC-MODULE: E2E.c                                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR E2E Module                                            **
**                                                                            **
**  PURPOSE   : To implement specification of E2E StatePtr machine driver     **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision Date           By              Description                        **
********************************************************************************
** 1.0.1.1  27-Jun-2022    Gongbin Lim     #CP44-320                          **
** 0.0.1    10-Sep-2019    CuongLX         Initial Version                    **
** 0.0.2    20-Feb-2020    CuongLX         Remove marcro less meaning         **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Include for E2E External API's */
#include "E2E.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define E2E_START_SEC_CODE_ASIL_D /*polyspace MISRA2012:2.5 [Justified:Low] "This macro is necessary for Memory mapping"*/
#include "MemMap.h"

/* CRC Library Version check */
#if defined(CRC_AR_RELEASE_MAJOR_VERSION) \
		&& defined(CRC_AR_RELEASE_MINOR_VERSION)
#if ((CRC_AR_RELEASE_MAJOR_VERSION != E2E_CRC_AR_RELEASE_MAJOR_VERSION) || \
		(CRC_AR_RELEASE_MINOR_VERSION != E2E_CRC_AR_RELEASE_MINOR_VERSION))
#error "E2E : Mismatch AUTOSAR Version with CRC.h"
#endif
#endif

/*******************************************************************************
** Function Name        : E2E_GetVersionInfo                                  **
**                                                                            **
** Service ID           : 0x14                                                **
**                                                                            **
** Description          : This function returns the version information of E2E**
**                        Routines module.                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : VersionInfo                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return Value         : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                                                                            **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
/* @Trace:   SRS_BSW_00004, */
FUNC(void, E2E_CODE) E2E_GetVersionInfo (
  P2VAR(Std_VersionInfoType, AUTOMATIC, E2E_APPL_DATA) VersionInfoPtr)
{
  
  /* @Trace: SafeE2E_SUD_MF_806 */
  if (NULL_PTR != VersionInfoPtr) 
  {
    /* polyspace-begin MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/    
    /* Copy the vendor Id */
    VersionInfoPtr->vendorID = E2E_VENDOR_ID;

    /* Copy the module Id */
    VersionInfoPtr->moduleID = E2E_MODULE_ID;

    /* Copy Software Major Version */
    VersionInfoPtr->sw_major_version = (uint8)E2E_SW_MAJOR_VERSION;

    /* Copy Software Minor Version */
    VersionInfoPtr->sw_minor_version = (uint8)E2E_SW_MINOR_VERSION;

    /* Copy Software Patch Version */
    VersionInfoPtr->sw_patch_version = (uint8)E2E_SW_PATCH_VERSION;
    /* polyspace-end MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
    
  }
  

  /*
   * If the received VersionInfo pointer is NULL and shall return from the
   * E2E_GetVersionInfo API without performing any further functionality.
   */
}

#define E2E_STOP_SEC_CODE_ASIL_D
#include "MemMap.h" /*polyspace MISRA2012:20.1 [Justified:Low] "This include directive is necessary for Memory mapping"*/
