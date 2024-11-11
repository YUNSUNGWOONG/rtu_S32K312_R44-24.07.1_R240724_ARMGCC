/*******************************************************************************
**                                                                            **
** (C) 2021 HYUNDAI AUTOEVER Corp.                                            **
** Confidential Proprietary Information. Distribution Limited.                **
** This source code is permitted to be used only in projects contracted       **
** with Hyundai Autoever, and any other use is prohibited.                    **
** If you use it for other purposes or change the source code,                **
** you may take legal responsibility.                                         **
** In this case, There is no warranty and technical support.                  **
**                                                                            **
**  SRC-MODULE: Det_Version.c                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Default Error Tracer Module                           **
**                                                                            **
**  PURPOSE   : Provision of callback functions and their functionality.      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 0.0.1     30-Sep-2019   DanhLT2      Initial Version                       **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Det.h"                /* Header file of DET */
#include "Det_Version.h"        /* Det Version header file */
#if (DET_RAM_BUFFER == STD_ON)
#include "Rte.h"                  /* Header file of RTE */
#endif
#if (DET_FORWARD_TO_DLT == STD_ON)
#include "Dlt.h"                  /* Header file of DLT */
#endif

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* Det AUTOSAR Specification Version Information */
#if ((DET_AR_RELEASE_MAJOR_VERSION != DET_VERSION_AR_RELEASE_MAJOR_VERSION) || \
    (DET_AR_RELEASE_MINOR_VERSION != DET_VERSION_AR_RELEASE_MINOR_VERSION))

#error "Det : Mismatch AUTOSAR Version in Det_Version.c"

#endif

/* Det Software Version Information */
#if ((DET_SW_MAJOR_VERSION != DET_VERSION_SW_MAJOR_VERSION) || \
    (DET_SW_MINOR_VERSION != DET_VERSION_SW_MINOR_VERSION) || \
    (DET_SW_PATCH_VERSION != DET_VERSION_SW_PATCH_VERSION))

#error "Det : Mismatch Software Version in Det_Version.c"

#endif

#if (DET_RAM_BUFFER == STD_ON)
/* RTE AUTOSAR Specification Version Information */
#if defined(RTE_AR_RELEASE_MAJOR_VERSION) \
  && defined(RTE_AR_RELEASE_MINOR_VERSION)

#if ((RTE_AR_RELEASE_MAJOR_VERSION != DET_RTE_AR_RELEASE_MAJOR_VERSION) || \
     (RTE_AR_RELEASE_MINOR_VERSION != DET_RTE_AR_RELEASE_MINOR_VERSION))

#error "Det : Mismatch AUTOSAR Version with Rte.h"

#endif
#endif
#endif 

/* Dlt AUTOSAR Specification Version Information */
#if (DET_FORWARD_TO_DLT == STD_ON)
#if defined(DLT_AR_RELEASE_MAJOR_VERSION) \
  && defined(DLT_AR_RELEASE_MINOR_VERSION)

#if ((DLT_AR_RELEASE_MAJOR_VERSION != DET_DLT_AR_RELEASE_MAJOR_VERSION) || \
     (DLT_AR_RELEASE_MINOR_VERSION != DET_DLT_AR_RELEASE_MINOR_VERSION))

#error "Det : Mismatch AUTOSAR Version with Dlt.h"

#endif
#endif

#endif /* DET_FORWARD_TO_DLT == STD_ON */

/*******************************************************************************
**                      Global Types                                          **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
