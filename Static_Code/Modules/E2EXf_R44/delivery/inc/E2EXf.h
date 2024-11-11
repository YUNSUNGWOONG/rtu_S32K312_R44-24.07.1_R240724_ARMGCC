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
**  SRC-MODULE: E2EXf.h                                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR E2E Transformer Module                                **
**                                                                            **
**  PURPOSE   : Header file to publish E2E Transformer function prototypes    **
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
** 1.1.1.   30-Jun-2022    Seungjin Noh        #CP44-2597                     ** 
** 1.1.0.   09-Nov-2022    Gongbin Lim         #CP44-765                      **
** 1.0.2.1  30-Jun-2022    Gongbin Lim         #CP44-321                      **
** 1.0.0    04-Dec-2020    Gongbin Lim         Initial Version                **
*******************************************************************************/

#ifndef E2EXF_H
#define E2EXF_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: SafeE2EXf_SUD_FILE_001 */

#include "E2EXf_APIs.h"				       /* E2EXf Generated Functions Header File */
#if (E2EXF_PRECOMPILE_CONFIG == STD_OFF)
#include "E2EXf_PbCfg.h"         /* E2EXf PostBuild Configuration Header File */
#endif /*End of (E2EXF_PRECOMPILE_CONFIG == STD_OFF)*/


/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      MACRO Definition                                      **
*******************************************************************************/
/* polyspace-begin MISRA-C3:2.5 [Justified:Low] "Macro is defined following specification document" */
/* @Trace: SafeE2EXf_SUD_MACRO_001 */
/* E2EXf Development Error ID */ 

/* Error code if any other API service, except GetVersionInfo is called before
the transformer module was initialized with Init or after a call to DeInit */
#define E2EXF_E_UNINIT                          (0x01U)

/* Error code if an invalid configuration set was selected */
#define E2EXF_E_INIT_FAILED                     (0x02U)

/* API service called with wrong parameter */
#define E2EXF_E_PARAM                           (0x03U)

/* API service called with invalid pointer */
#define E2EXF_E_PARAM_POINTER                   (0x04U)

/* @Trace: SafeE2EXf_SUD_MACRO_004 */
/* Service SID for E2EXf */

#define E2EXF_GETVERSIONINFO_SID                (0x00U)

#define E2EXF_INIT_SID                          (0x01U)

#define E2EXF_DEINIT_SID                        (0x02U)

#define E2EXF_TRANSFORMERID_SID                 (0x03U)

#define E2EXF_INV_TRANSFORMERID_SID             (0x04U)

/* polyspace-end MISRA-C3:2.5 */             


/* @Trace: SafeE2EXf_SUD_MACRO_005 */        
/* E2EXf Data Semantics Macros*/             
#define E2EXF_ZERO                              (0U)
#define E2EXF_ONE                               (1U)
#define E2EXF_FOUR                              (4U)
#define E2EXF_EIGHT                             (8U)
#define E2EXF_TWELVE                            (12U)
#define E2EXF_HIGH_NIBBLE_MASK                  (0xF0U)
#define E2EXF_LOW_NIBBLE_MASK                   (0x0FU)


/* polyspace-begin MISRA-C3:2.5 [Justified:Low] "Macro is defined following specification document" */
/* @Trace: SafeE2EXf_SUD_MACRO_002 */
/* Function-like Macros */

#define E2EXF_INPLACE_PRECONDITIONS ((NULL_PTR == buffer) \
  || ((buffer != NULL_PTR) && (inputBufferLength < (upperHeaderBitsToShift / E2EXF_EIGHT))) \
  || (NULL_PTR == bufferLength))

#define E2EXF_OUTPLACE_PRECONDITIONS ((NULL_PTR == inputBuffer) \
  || ((inputBuffer != NULL_PTR) && (inputBufferLength < (upperHeaderBitsToShift / E2EXF_EIGHT))) \
  || (NULL_PTR == bufferLength) \
  || (NULL_PTR == buffer))

#define E2EXF_INV_INPLACE_PRECONDITIONS (((NULL_PTR == buffer) && (inputBufferLength != E2EXF_ZERO)) \
  || ((buffer != NULL_PTR) && (inputBufferLength < (((uint32)headerLength / E2EXF_EIGHT) + (upperHeaderBitsToShift / E2EXF_EIGHT)))) \
  || (NULL_PTR == bufferLength))

#define E2EXF_INV_OUTPLACE_PRECONDITIONS (((NULL_PTR == inputBuffer) && (inputBufferLength != E2EXF_ZERO)) \
  || ((inputBuffer != NULL_PTR) && (inputBufferLength < (((uint32)headerLength / E2EXF_EIGHT) + (upperHeaderBitsToShift / E2EXF_EIGHT)))) \
  || (NULL_PTR == bufferLength) \
  || (NULL_PTR == buffer))

/* polyspace-end MISRA-C3:2.5 */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define E2EXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"

/* @Trace: SafeE2EXf_SUD_API_002 */
extern FUNC(void, E2EXF_CODE) E2EXf_DeInit(void);

/* @Trace: SafeE2EXf_SUD_API_003 */
#if (E2EXF_VERSION_INFO_API == STD_ON)
/* polyspace +2 MISRA-C3:D4.5 [Justified:Low] "Parameter name is following specification document" */
extern FUNC(void, E2EXF_CODE) E2EXf_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, E2EXF_APPL_DATA) versionInfo);
#endif /* End of (E2EXF_VERSION_INFO_API == STD_ON) */

#define E2EXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

#endif /* E2EXF_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
