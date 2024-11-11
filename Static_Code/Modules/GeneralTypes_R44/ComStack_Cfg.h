/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: ComStack_Cfg.h                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR BSW R4.4.0 Modules                                    **
**                                                                            **
**  PURPOSE   : Provision for Communication Stack Configuration file, AUTOSAR **
**              type definition of the PduIdType and PduLengthType. shall be  **
**              generated by the generator of EcuC Virtual Layer              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: yes                                       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By          Description                            **
********************************************************************************
** 1.0.0     29-Apr-2019   Khanh Le    Initial Version                        **
*******************************************************************************/

#ifndef COMSTACK_CFG_H
#define COMSTACK_CFG_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR specification version information */
#define COMSTACK_CFG_AR_RELEASE_MAJOR_VERSION             4
#define COMSTACK_CFG_AR_RELEASE_MINOR_VERSION             4

/* File version information */
#define COMSTACK_CFG_SW_MAJOR_VERSION                     1
#define COMSTACK_CFG_SW_MINOR_VERSION                     0
#define COMSTACK_CFG_SW_PATCH_VERSION                     0

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/


/*******************************************************************************
**                      Global Data Types (ECU dependent)                     **
*******************************************************************************/

/* SWS_COMTYPE_00005 ,SWS_Comtype_00006 */
/* This type serve as a unique identifier of a PDU within a software module. Allowed ranges: uint8, uint16 */
typedef uint16       PduIdType;

/* SWS_COMTYPE_00008 ,SWS_Comtype_00010 */
/* This type serve as length information of a PDU in bytes. Allowed ranges: uint8, uint16, uint32 */
typedef uint16       PduLengthType;

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* COMSTACK_CFG_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/