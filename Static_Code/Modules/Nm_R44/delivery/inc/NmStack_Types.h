/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: NmStack_Types.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Nm Module                                             **
**                                                                            **
**  PURPOSE   : Provision of Nm Stack types                                   **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision   Date          By             Description                        **
********************************************************************************
** 1.0.1.1    20-Jun-2022   SMKwon         CP44-105                           **
** 1.0.0      04-Dec-2020   Autoever       Initial Version                    **
*******************************************************************************/

#ifndef NMSTACK_TYPES_H
#define NMSTACK_TYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
#define NMSTACK_TYPES_AR_RELEASE_MAJOR_VERSION      (0x04u)
#define NMSTACK_TYPES_AR_RELEASE_MINOR_VERSION      (0x04u)

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* @Trace: SRS_Nm_00044 SRS_Nm_00050 */
typedef enum
{
  /* @Trace: Nm_SUD_DATATYPE_005 */
  NM_MODE_BUS_SLEEP,
  NM_MODE_PREPARE_BUS_SLEEP,
  NM_MODE_SYNCHRONIZE,
  NM_MODE_NETWORK
} Nm_ModeType;

typedef enum
{
  /* @Trace: Nm_SUD_DATATYPE_006 */
  NM_STATE_UNINIT = 0x00,
  NM_STATE_BUS_SLEEP,
  NM_STATE_PREPARE_BUS_SLEEP,
  NM_STATE_READY_SLEEP,
  NM_STATE_NORMAL_OPERATION,
  NM_STATE_REPEAT_MESSAGE,
  NM_STATE_SYNCHRONIZE,
  NM_STATE_OFFLINE
} Nm_StateType;

typedef enum
{
  /* @Trace: Nm_SUD_DATATYPE_007 */
  NM_BUSNM_CANNM,
  NM_BUSNM_FRNM,
  NM_BUSNM_UDPNM,
  NM_BUSNM_GENERICNM,
  NM_BUSNM_J1939NM,
  NM_BUSNM_LOCALNM,
  NM_BUSNM_UNDEF = 0xff
} Nm_BusNmType;

/*******************************************************************************
**                      Global Function Prototypes                            **
*******************************************************************************/
#endif  /* NMSTACK_TYPES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
