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
**  SRC-MODULE: FiM_Types.h                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Function Inhibition Manager Module                    **
**                                                                            **
**  PURPOSE   : Type definition of Function Inhibition Manager                **
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
** 0.0.5    11-Sept-2020   ThienVT1        Changes made As per Redmine #15664 **
** 0.0.4     20-Aug-2020   ThienVT1        Changes made As per Redmine #15009 **
** 0.0.3    28-July-2020   ThienVT1        Changes made As per Redmine #14839 **
** 0.0.2    18-July-2020   ThienVT1        Changes made As per Redmine #13068 **
** 0.0.1    05-June-2020   ThienVT1        Initial Version                    **
*******************************************************************************/
#ifndef FIM_TYPES_H
#define FIM_TYPES_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: FiM_SUD_DATATYPE_005 */
/* @Trace: FiM_SUD_DATATYPE_006 */
#include "Std_Types.h"     /* Std Types Definition Header File */
/* @Trace: SWS_Fim_00080 */
#include "Rte_FiM_Type.h"  /* Rte FiM Definition Header file */
#include "FiM_Cfg.h"       /* FiM Cfg Definition Header File */
#include "Dem.h"
#if (FIM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"           /* Det header file */
/* @Trace: SWS_Fim_00080 */
#endif
/*******************************************************************************
**                           Global Data                                      **
*******************************************************************************/
typedef uint16 FiM_EventsSizeType;
typedef uint16 FiM_FidsSizeType;
typedef uint16 FiM_EventFidLinkType;
typedef uint16 FiM_ComponentSizeType;
typedef uint16 FiM_ComponentFidLinkType;
/* @Trace: SWS_Fim_00008 */
/* @Trace: SWS_Fim_00092 */
/* @Trace: SRS_Fim_04706 */
/* @Trace: FiM_SUD_DATATYPE_014 */
typedef struct
{
  uint8 dummy;
}FiM_ConfigType;

/*******************************************************************************
**                      RUNTIME ERRORS                                        **
*******************************************************************************/

#ifndef UNUSED
/* polyspace +1 MISRA-C3:D4.9 [Justified:Low] "A function should be used in preference to a function-like macro where they are interchangeable." */
#define UNUSED(variable) (void) variable
#endif
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#endif /* FIM_TYPES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
