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
**  SRC-MODULE: Tm_Types.c                                                    **
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
** Revision  Date           By             Description                        **
********************************************************************************
** 1.0.1     24-Jun-2022    PhatCT         R44-Redmine #25858, #28232         **
** 1.0.0     19-Jun-2020    DanhLT2        Initial Version                    **
*******************************************************************************/
#ifndef TM_TYPES_H
#define TM_TYPES_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Tm_Cfg.h"

/*******************************************************************************
**                      Macros definition                                     **
*******************************************************************************/
/* @Trace: SRS_BSW_00348 Tm_SUD_MACRO_008 Tm_SUD_FILE_001 */

#define TM_INSTANCE_ID                      ((uint8)0x00u)
#define TM_16BIT_ZERO                       ((uint32)0x00000000u)
#define TM_16BIT_ONE                        ((uint32)0x00000001u)
#define TM_16BIT_MAX                        ((uint32)0x0000FFFFu)
#define TM_16BIT_MASK                       ((uint32)0x0000FFFFu)

#define TM_24BIT_ZERO                       ((uint32)0x00000000u)
#define TM_24BIT_ONE                        ((uint32)0x00000001u)
#define TM_24BIT_MAX                        ((uint32)0x00FFFFFFu)
#define TM_24BIT_MASK                       ((uint32)0x00FFFFFFu)

#define TM_32BIT_ZERO                       ((uint32)0x00000000u)
#define TM_32BIT_ONE                        ((uint32)0x00000001u)
#define TM_32BIT_MAX                        ((uint32)0xFFFFFFFFu)
#define TM_32BIT_MASK                       ((uint32)0xFFFFFFFFu)

/*******************************************************************************
**                      Type definition                                       **
*******************************************************************************/

#if (TM_ENABLE_PREDEFTIMER_1US_16BIT  == STD_ON)
/* @Trace: Tm_SUD_DATATYPE_004 */
/* Data type of Time Service Predef Timer 1us16bit. */
typedef struct 
{
  uint16 ui16RefTime;
}Tm_PredefTimer1us16bitType;
#endif /* TM_ENABLE_PREDEFTIMER_1US_16BIT == STD_ON */

#if (TM_ENABLE_PREDEFTIMER_1US_24BIT  == STD_ON)
/* @Trace: Tm_SUD_DATATYPE_005 */
/* Data type of Time Service Predef Timer 1us24bit. */
typedef struct 
{
  uint32 ui24RefTime;
}Tm_PredefTimer1us24bitType;
#endif /* TM_ENABLE_PREDEFTIMER_1US_24BIT == STD_ON */

#if (TM_ENABLE_PREDEFTIMER_1US_32BIT  == STD_ON)
/* @Trace: Tm_SUD_DATATYPE_006 */
/* Data type of Time Service Predef Timer 1us32bit. */
typedef struct 
{
  uint32 ui32RefTime;
}Tm_PredefTimer1us32bitType;
#endif /* TM_ENABLE_PREDEFTIMER_1US_32BIT == STD_ON */

#if (TM_ENABLE_PREDEFTIMER_100US_32BIT  == STD_ON)
/* @Trace: Tm_SUD_DATATYPE_007 */
/* Data type of Time Service Predef Timer 100us32bit. */
typedef struct 
{
  uint32 ui32RefTime;
}Tm_PredefTimer100us32bitType;
#endif /* TM_ENABLE_PREDEFTIMER_100US_32BIT == STD_ON */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                           Function Prototypes                              **
*******************************************************************************/

#endif /* TM_TYPES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
