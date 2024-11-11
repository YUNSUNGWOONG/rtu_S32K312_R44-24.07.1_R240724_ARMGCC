/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**                                                                            **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: CanTp_Config.c                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN Transport Protocol                                **
**                                                                            **
**  PURPOSE   : CanTp Library Release.                                        **
**                                                                            **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.0.7     31-Oct-2022   HieuTM8        #CP44-1038                          **
** 1.0.3.1   22-Jun-2022   SMKwon         CP44-94                             **
** 1.0.1     28-Feb-2022   HieuTM8        R44-Redmine #20400, #19344          **
** 1.0.0     04-Dec-2020   SMKwon         Initial Version                     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Platform_Types.h"

#include "CanTp.h"

#include "CanTp_PCTypes.h"

/*******************************************************************************
**            Variable for Library                  **
*******************************************************************************/

/* @Trace: SWS_CanTp_00059 */
/* Note: The value used for padding bytes is configurable via configuration parameter CANTP_PADDING_BYTE */
#define CANTP_START_SEC_CONST_8
#include "MemMap.h"
CONST(uint8, CANTP_CONST) CanTp_PaddingByte[CANTP_SIXTEEN] = {CANTP_PADDING_BYTE, CANTP_PADDING_BYTE, CANTP_PADDING_BYTE, CANTP_PADDING_BYTE,
                                                               CANTP_PADDING_BYTE, CANTP_PADDING_BYTE, CANTP_PADDING_BYTE, CANTP_PADDING_BYTE, 
                                                               CANTP_PADDING_BYTE, CANTP_PADDING_BYTE, CANTP_PADDING_BYTE, CANTP_PADDING_BYTE,
                                                               CANTP_PADDING_BYTE, CANTP_PADDING_BYTE, CANTP_PADDING_BYTE, CANTP_PADDING_BYTE};
#define CANTP_STOP_SEC_CONST_8
#include "MemMap.h"

#define CANTP_START_SEC_CONST_8
#include "MemMap.h"
CONST(uint8, CANTP_CONST) CanTp_DiscreteDlcDataLength[CANTP_SEVEN]
                                                = {12U,16U,20U,24U,32U,48U,64U};
#define CANTP_STOP_SEC_CONST_8
#include "MemMap.h"

#if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT)
#define CANTP_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
P2CONST(CanTp_ConfigType, AUTOMATIC, CANTP_CONST) Variant_Select;
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */

/* Byte position in the frames */
#define CANTP_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
CONST(uint8, CANTP_CONST) CanTp_BytePos[CANTP_FIVE] =
{
  /* Standard */
  CANTP_ZERO,
  /* Extended */
  CANTP_ONE,
  /* Mixed */
  CANTP_ONE,
  /* Mixed29 */
  CANTP_ONE,
  /* NormalFix */
  CANTP_ZERO
};
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
