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
**  INC-MODULE: ComM_Config.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR COM Manager                                           **
**                                                                            **
**  PURPOSE   : Provision of external declaration of constant variables       **
**              to save the configured values                                 **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision       Date                By               Description            **
********************************************************************************
** 1.1.7          31-Jan-2024         MUKim            CP44-3149              **
** 1.0.4.1        20-Jun-2022         SMKwon           CP44-115               **
** 1.0.3          22-Feb-2022         ThuanVT          R44-Redmine #24036     **
** 1.0.2          20-Dec-2020         DatNXT           R44-Redmine #14793,    **
**                                                     #14801                 **
** 1.0.0          15-Dec-2020         JsLim            Initial Version        **
*******************************************************************************/

#ifndef COMM_CONFIG_H_
#define COMM_CONFIG_H_

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: ComM_SUD_MACRO_004  */
/* @Trace: ComM_SUD_MACRO_006  */
#include "ComM_PCTypes.h"
/* @Trace: ComM_SUD_DATATYPE_004 */
/* @Trace: ComM_SUD_DATATYPE_007 */
/* @Trace: SRS_ComM_AR_00204 */
/* @Trace: SRS_ComM_AR_00206 */
#include "ComStack_Types.h"       /* Communication Stack header file */
/* @Trace: ComM_SUD_DATATYPE_002 */
/* @Trace: SRS_ComM_AR_00254 */
/* @Trace: ComM_SUD_DATATYPE_003 */
#include "ComM_Cfg.h"
#if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_ON)
#include "ComM_PBcfg.h"             /* Module configuration header file for PB*/
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#define COMM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COMM_CODE) ComM_MainFunction(NetworkHandleType Channel);

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON))

#define COMM_START_SEC_CODE
#include "MemMap.h"

/* Extern for ComM_COMCbk */
extern FUNC(void, COMM_CODE) ComM_COMCbk(Com_SignalIdType SignalId);

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

#endif /*(COMM_PNC_SUPPORT == STD_ON)&& (COMM_PNC_ENABLED == STD_ON)*/
#endif /* End of if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED ==
        *STD_ON)) */

#endif /* COMM_CONFIG_H_ */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
