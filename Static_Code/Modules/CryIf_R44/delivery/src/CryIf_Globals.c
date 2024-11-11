/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: CryIf_Globals.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CRYIF                                                 **
**                                                                            **
**  PURPOSE   : Define all global data that is not configured                 **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date               By           Description                      **
********************************************************************************
** 1.0.0.0   15-Jan-2021        JH Lim       Initial version                  **
** 1.0.1.0   20-Mar-2021        TamTV6       Add trace SUD                    **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/* For global variables */
#include "CryIf_Globals.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CRYIF_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

/* @Trace: CryIf_SUD_GLOBALVAR_001 */
/* Variable holds the state initialization of module */
VAR(boolean, CRYIF_VAR_CLEARED) CryIf_ModuleInitialized;

#define CRYIF_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#define CRYIF_START_SEC_VAR_CLEARED_32
#include "MemMap.h"

/* @Trace: CryIf_SUD_GLOBALVAR_002 */
/* @Trace: CryIf_SUD_GLOBALVAR_003 */
/* Array holds key element Id of a Crypto interface key */
VAR(uint32, AUTOMATIC) \
  CryIf_SourceElementArray[CRYIF_MAX_KEY_ELEMENT_NUMBER];
VAR(uint32, AUTOMATIC) \
  CryIf_TargetElementArray[CRYIF_MAX_KEY_ELEMENT_NUMBER];

#define CRYIF_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"

#define CRYIF_START_SEC_VAR_CLEARED_8
#include "MemMap.h"

/* @Trace: CryIf_SUD_GLOBALVAR_004 */
/* Array is key pointer buffer */
VAR(uint8, AUTOMATIC) CryIf_KeySourceData[CRYIF_MAX_KEY_ELEMENT_SIZE];
/* @Trace: CryIf_SUD_GLOBALVAR_005 */
/* Array is target key pointer buffer */
VAR(uint8, AUTOMATIC) CryIf_KeyTargetData[CRYIF_MAX_KEY_ELEMENT_SIZE];

#define CRYIF_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
