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
**  SRC-MODULE: CanSM_Types.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN State Manager Module                              **
**                                                                            **
**  PURPOSE   : Type definition of Autosar CAN State Manager                  **
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
** 1.0.5     31-Oct-2022   HieuTM8        #CP44-1035                          **
** 1.0.3     25-Jul-2022   HieuTM8        CP44-511                            **
** 1.0.1     14-Jan-2022   HieuTM8        R44-Redmine #14419,#19306           **
** 1.0.0     04-Dec-2020   SMKwon         Initial Version                     **
*******************************************************************************/
/* @Trace: CanSM_SUD_FILE_001  */
#ifndef CANSM_TYPES_H
#define CANSM_TYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: CanSM_SUD_DATATYPE_023 CanSM_SUD_DATATYPE_024 CanSM_SUD_MACRO_010 CanSM_SUD_MACRO_011  */
#include "CanSM_Cfg.h"                /* CanSM config header */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* @Trace: CanSM_SUD_MACRO_001  */
/* AUTOSAR Specification Version Information */
#define CANSM_TYPES_H_AR_RELEASE_MAJOR_VERSION         0x04u
#define CANSM_TYPES_H_AR_RELEASE_MINOR_VERSION         0x04u
#define CANSM_TYPES_H_AR_RELEASE_REVISION_VERSION      0x00u

/* Software Version Information */
#define CANSM_TYPES_H_SW_MAJOR_VERSION                 0x01u
#define CANSM_TYPES_H_SW_MINOR_VERSION                 0x00u

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/* CanSM Bus Off mode */
/* @Trace:  CanSM_SUD_DATATYPE_017 */
#define CANSM_BSWM_BOR_START                           (uint16)0x00 

#define CANSM_BSWM_BOR_COMPLETE                        (uint16)0x01 

/* Structure for the CANSM configuration type */
/* @Trace:  SRS_BSW_00400 SRS_BSW_00438 */
/* @Trace:  CanSM_SUD_DATATYPE_023 */
typedef struct
{
  #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
  /* number of networks per a configuration set  */
  uint8 CanSMNWPerCfg;
  #endif

  #if((STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)&&(STD_ON == CANSM_CANTRCV_SUPPORT))
  /* the largest Trcv Id per a configuration set  */
  uint8 CanSMLastTrcvHandle;
  #endif

  #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
  /* the largest Ctrl Index per a configuration set */
  uint8 CanSMLastCtrlHandle;
  #endif

  #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
  /* The largest Network ID per a configuration set */
  uint8 CanSMLastNetworkHandle;
  #endif

  #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
  /* number of static controller */
  uint8 CanSMStaticController;
  #endif


  /* CanSMModeRequestRepetitionMax */
  uint8 ModeReqRptMax;


  /* CanSMModeRequestRepetitionTime */
  uint16 ModeReqRptTime;

  /* Pointer to first network */
  P2CONST(void, AUTOMATIC, CANSM_CONST)pStaticNetwork;


  #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
  /* pointer to CanSM Internal controller */
  P2CONST(uint8,AUTOMATIC,CANSM_CONST) pCtrlIDToNW;
  #endif

  #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
  /* pointer to CanSM static controller */
  P2CONST(uint8,AUTOMATIC,CANSM_CONST) pCtrlIndexToId;
  #endif


  #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
  /* pointer to CanSM Internal network */
  P2CONST(uint8,AUTOMATIC,CANSM_CONST) pNwIdToIndex;
  #endif

  #if((STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)&&(STD_ON == CANSM_CANTRCV_SUPPORT))
  /* pointer to CanSM static network */
  P2CONST(uint8,AUTOMATIC,CANSM_CONST) pTrcvIdToNwIndex;
  #endif

} CanSM_ConfigType;

/*******************************************************************************
**                      MACRO Definitions                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* CANSM_TYPES_H */

/*******************************************************************************
**                   End of File                                              **
*******************************************************************************/

