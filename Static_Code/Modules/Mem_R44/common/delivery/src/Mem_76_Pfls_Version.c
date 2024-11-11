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
**  SRC-MODULE: Mem_76_Pfls_Version.c                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR MEM PFLS                                              **
**                                                                            **
**  PURPOSE   : Provides definition of API's provided for upper layers        **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision    Date           By          Description                         **
********************************************************************************
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Mem_76_Pfls_Version.h"  /* Macros */
#include "Mem_76_Pfls.h"
#include "Mem_76_Pfls_Cfg.h"
#include "Det.h"        /* For version check with Det */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* Check version between Mem_76_Pfls_Version and Mem_76_Pfls */

/* Mem_76_Pfls AUTOSAR Version check */
#if ((MEM_76_PFLS_AR_RELEASE_MAJOR_VERSION != MEM_76_PFLS_VERSION_AR_RELEASE_MAJOR_VERSION) || \
  (MEM_76_PFLS_AR_RELEASE_MINOR_VERSION != MEM_76_PFLS_VERSION_AR_RELEASE_MINOR_VERSION))
  #error "Mem_76_Pfls : Mismatch AUTOSAR Version in Mem_76_Pfls_Version.c "
#endif

/* Mem_76_Pfls Software Version check */
#if ((MEM_76_PFLS_SW_MAJOR_VERSION != MEM_76_PFLS_VERSION_SW_MAJOR_VERSION) || \
  (MEM_76_PFLS_SW_MINOR_VERSION != MEM_76_PFLS_VERSION_SW_MINOR_VERSION) || \
  (MEM_76_PFLS_SW_PATCH_VERSION != MEM_76_PFLS_VERSION_SW_PATCH_VERSION))
  #error "Mem_76_Pfls : Mismatch Software Version in Mem_76_Pfls_Version.c "
#endif

/* Check version for dependency modules */



/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
