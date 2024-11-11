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
**  SRC-MODULE: Tm_Version.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Time Service  Module                                  **
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
** 1.0.3     24-Jul-2023   NamNT1         CP44-2279                            **
** 1.0.2     17-Mar-2023   NamNT1         CP44-1740                            **
** 1.0.1     24-Jun-2022   PhatCT         R44-Redmine #25858, #28232          **
** 1.0.0     19-Jun-2020   DanhLT2        Initial Version                     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Tm.h"                            /* Header file of TM */
#include "Tm_Version.h"                    /* Tm Version header file */

#if(TM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                           /* Det module Header file */
#endif
#include "Gpt.h"                           /*Gpt module Header file*/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
 /* @Trace: Tm_SUD_MACRO_001 Tm_SUD_FILE_001  */
 /* Version information Macro */
 
 /* @Trace: Tm_SUD_API_122 */
 /* Tm AUTOSAR Version check */
#if ((TM_AR_RELEASE_MAJOR_VERSION != TM_VERSION_AR_RELEASE_MAJOR_VERSION)||\
     (TM_AR_RELEASE_MINOR_VERSION != TM_VERSION_AR_RELEASE_MINOR_VERSION))
#error "Tm : Mismatch AUTOSAR Version in Tm_Version.c"
#endif

 /* @Trace: Tm_SUD_API_123 */
 /* Tm Software Version check */
#if ((TM_SW_MAJOR_VERSION != TM_VERSION_SW_MAJOR_VERSION)||\
     (TM_SW_MINOR_VERSION != TM_VERSION_SW_MINOR_VERSION)||\
     (TM_SW_PATCH_VERSION != TM_VERSION_SW_PATCH_VERSION))
#error "Tm: Mismatch Software Version in Tm_Version.c"
#endif

 /* @Trace: Tm_SUD_API_124 */
 /* Gpt Version check */
#if defined(GPT_AR_RELEASE_MAJOR_VERSION) && defined(GPT_AR_RELEASE_MINOR_VERSION)
#if ((GPT_AR_RELEASE_MAJOR_VERSION != TM_GPT_AR_RELEASE_MAJOR_VERSION)||\
     ((GPT_AR_RELEASE_MINOR_VERSION != TM_GPT_AR_RELEASE_MINOR_VERSION_R42)&&\
      (GPT_AR_RELEASE_MINOR_VERSION != TM_GPT_AR_RELEASE_MINOR_VERSION_R43)&&\
      (GPT_AR_RELEASE_MINOR_VERSION != TM_GPT_AR_RELEASE_MINOR_VERSION_R44)))
#error "Tm: Mismatch AUTOSAR Version with Gpt.h"
#endif
#endif
 /* @Trace: Tm_SUD_API_125 */
 /* Det Version check */
#if defined(DET_AR_RELEASE_MAJOR_VERSION) && defined(DET_AR_RELEASE_MINOR_VERSION)
#if ((DET_AR_RELEASE_MAJOR_VERSION != TM_DET_AR_RELEASE_MAJOR_VERSION)||\
     (DET_AR_RELEASE_MINOR_VERSION != TM_DET_AR_RELEASE_MINOR_VERSION ))
#error  "Tm: Mismatch AUTOSAR Version with Det.h"
#endif
#endif

/*******************************************************************************
**                      Global Types                                          **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
