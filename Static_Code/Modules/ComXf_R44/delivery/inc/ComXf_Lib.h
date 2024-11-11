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
**  INC-MODULE:           ComXf_Lib.h                                         **
**                                                                            **
**  PRODUCT   :           AUTOSAR COM Based Transformer Module                **
**                                                                            **
**  PURPOSE   :           This file defines extern declarations of packing    **
**                        functions                                           **
**                                                                            **
**  HARDWARE DEPENDANT [Yes/No]: No                                           **
**                                                                            **
**  AUTOSAR RELEASE:  4.4.0                                                   **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By          Description                            **
********************************************************************************
** 1.0.7     31-Aug-2022   KhaLN1      #CP44-614                              **
** 1.0.0     22-Feb-2020   HiepVT1     Initial Version                        **
*******************************************************************************/
#ifndef COMXF_LIB_H
#define COMXF_LIB_H

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "see SWS_MemMap_00003 of AUTOSAR" */

/*******************************************************************************
**                         Header File Include Section                        **
*******************************************************************************/
/* @Trace: SafeComXf_SUD_FILE_001 */
/* Include for ComXf.h */
#include "ComXf.h"

/*******************************************************************************
**                             Version Information                            **
*******************************************************************************/

/*******************************************************************************
**                              MACRO Definition                              **
*******************************************************************************/

/*******************************************************************************
**                              Type Definition                               **
*******************************************************************************/

/*******************************************************************************
**                         Global Variable Declaration                        **
*******************************************************************************/

/*******************************************************************************
**                           Function Declaration                             **
*******************************************************************************/

/* extern declaration of ComXf_PackBoolean */
#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
extern FUNC(void, COMXF_CODE) ComXf_PackBoolean(
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) buffer,
  P2CONST(ComXf_PackSigType, AUTOMATIC, COMXF_APPL_CONST) packSigType,
  VAR(boolean, AUTOMATIC) dataElement);
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/* extern declaration of ComXf_Pack2ByteAlign */
#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
extern FUNC(void, COMXF_CODE) ComXf_Pack2ByteAlign(
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) buffer,
  VAR(uint16, AUTOMATIC) dataElement,
  VAR(sint8, AUTOMATIC) byteDirection);
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/* extern declaration of ComXf_Pack3ByteAlign */
#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
extern FUNC(void, COMXF_CODE) ComXf_Pack3ByteAlign(
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) buffer,
  VAR(uint32, AUTOMATIC) dataElement,
  VAR(sint8, AUTOMATIC) byteDirection);
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/* extern declaration of ComXf_Pack4ByteAlign */
#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
extern FUNC(void, COMXF_CODE) ComXf_Pack4ByteAlign(
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) buffer,
  VAR(uint32, AUTOMATIC) dataElement,
  VAR(sint8, AUTOMATIC) byteDirection);
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/* extern declaration of ComXf_PackUint64ByteAlign */
#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
extern FUNC(void, COMXF_CODE) ComXf_PackUint64ByteAlign(
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) buffer,
  P2CONST(ComXf_PackSigType, AUTOMATIC, COMXF_APPL_CONST) packSigType,
  VAR(uint64, AUTOMATIC) dataElement,
  VAR(sint8, AUTOMATIC) byteDirection);
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/* extern declaration of ComXf_Pack5ByteNotAlign */
#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
extern FUNC(void, COMXF_CODE) ComXf_Pack5ByteNotAlign(
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) buffer,
  P2CONST(ComXf_PackSigType, AUTOMATIC, COMXF_APPL_CONST) packSigType,
  VAR(uint32, AUTOMATIC) dataElement,
  VAR(sint8, AUTOMATIC) byteDirection);
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/* extern declaration of ComXf_Pack4ByteNotAlign */
#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
extern FUNC(void, COMXF_CODE) ComXf_Pack4ByteNotAlign(
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) buffer,
  P2CONST(ComXf_PackSigType, AUTOMATIC, COMXF_APPL_CONST) packSigType,
  VAR(uint32, AUTOMATIC) dataElement, 
  VAR(sint8, AUTOMATIC) byteDirection);
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/* extern declaration of ComXf_Pack3ByteNotAlign */
#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
extern FUNC(void, COMXF_CODE) ComXf_Pack3ByteNotAlign(
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) buffer,
  P2CONST(ComXf_PackSigType, AUTOMATIC, COMXF_APPL_CONST) packSigType,
  VAR(uint32, AUTOMATIC) dataElement,
  VAR(sint8, AUTOMATIC) byteDirection);
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/* extern declaration of ComXf_Pack2ByteNotAlign */
#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
extern FUNC(void, COMXF_CODE) ComXf_Pack2ByteNotAlign(
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) buffer,
  P2CONST(ComXf_PackSigType, AUTOMATIC, COMXF_APPL_CONST) packSigType,
  VAR(uint16, AUTOMATIC) dataElement,
  VAR(sint8, AUTOMATIC) byteDirection);
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/* extern declaration of ComXf_Pack1ByteNotAlign */
#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
extern FUNC(void, COMXF_CODE) ComXf_Pack1ByteNotAlign(
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) buffer,
  P2CONST(ComXf_PackSigType, AUTOMATIC, COMXF_APPL_CONST) packSigType,
  VAR(uint8, AUTOMATIC) dataElement);
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/* extern declaration of ComXf_PackArray */
#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
extern FUNC(void, COMXF_CODE) ComXf_PackArray(
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) buffer,
  P2CONST(ComXf_PackSigType, AUTOMATIC, COMXF_APPL_CONST) packSigType,
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) dataElement);
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/* extern declaration of ComXf_Pack5678ByteNotAlign */
#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
extern FUNC(void, COMXF_CODE) ComXf_Pack5678ByteNotAlign(
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) buffer,
  P2CONST(ComXf_PackSigType, AUTOMATIC, COMXF_APPL_CONST) packSigType,
  VAR(uint64, AUTOMATIC) dataElement,
  VAR(sint8, AUTOMATIC) byteDirection);
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/* extern declaration of ComXf_Pack9ByteNotAlign */
#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
extern FUNC(void, COMXF_CODE) ComXf_Pack9ByteNotAlign(
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) buffer,
  P2CONST(ComXf_PackSigType, AUTOMATIC, COMXF_APPL_CONST) packSigType,
  VAR(uint64, AUTOMATIC) dataElement, 
  VAR(sint8, AUTOMATIC) byteDirection);
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/* extern declaration of ComXf_UnPackBoolean */
#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
extern FUNC(boolean, COMXF_CODE) ComXf_UnPackBoolean(
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) buffer,
  P2CONST(ComXf_UnPackSigType, AUTOMATIC, COMXF_APPL_CONST) unPackSigType);
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/* extern declaration of ComXf_UnPack2ByteAlign */
#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
extern FUNC(uint16, COMXF_CODE) ComXf_UnPack2ByteAlign(
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) buffer,
  VAR(sint8, AUTOMATIC) byteDirection);
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/* extern declaration of ComXf_UnPack3ByteAlign */
#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
extern FUNC(uint32, COMXF_CODE) ComXf_UnPack3ByteAlign(
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) buffer,
  P2CONST(ComXf_UnPackSigType, AUTOMATIC, COMXF_APPL_CONST) unPackSigType,
  VAR(sint8, AUTOMATIC) byteDirection);
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/* extern declaration of ComXf_UnPack4ByteAlign */
#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
extern FUNC(uint32, COMXF_CODE) ComXf_UnPack4ByteAlign(
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) buffer,
  VAR(sint8, AUTOMATIC) byteDirection);
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/* extern declaration of ComXf_UnPackUint64ByteAlign */
#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
extern FUNC(uint64, COMXF_CODE) ComXf_UnPackUint64ByteAlign(
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) buffer,
  P2CONST(ComXf_UnPackSigType, AUTOMATIC, COMXF_APPL_CONST) unPackSigType,
  VAR(sint8, AUTOMATIC) byteDirection);
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/* extern declaration of ComXf_UnPackFloat32ByteAlign */
#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
extern FUNC(float32, COMXF_CODE) ComXf_UnPackFloat32ByteAlign(
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) buffer,
  VAR(sint8, AUTOMATIC) byteDirection);
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/* extern declaration of ComXf_UnPackFloat64ByteAlign */
#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
extern FUNC(float64, COMXF_CODE) ComXf_UnPackFloat64ByteAlign(
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) buffer,
  P2CONST(ComXf_UnPackSigType, AUTOMATIC, COMXF_APPL_CONST) unPackSigType,
  VAR(sint8, AUTOMATIC) byteDirection);
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/* extern declaration of ComXf_UnPack1ByteNotAlign */
#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
extern FUNC(uint8, COMXF_CODE) ComXf_UnPack1ByteNotAlign(
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) buffer,
  P2CONST(ComXf_UnPackSigType, AUTOMATIC, COMXF_APPL_CONST) unPackSigType);
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/* extern declaration of ComXf_UnPack2ByteNotAlign */
#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
extern FUNC(uint16, COMXF_CODE) ComXf_UnPack2ByteNotAlign(
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) buffer,
  P2CONST(ComXf_UnPackSigType, AUTOMATIC, COMXF_APPL_CONST) unPackSigType,
  VAR(sint8, AUTOMATIC) byteDirection);
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/* extern declaration of ComXf_UnPack3ByteNotAlign */
#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
extern FUNC(uint32, COMXF_CODE) ComXf_UnPack3ByteNotAlign(
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) buffer,
  P2CONST(ComXf_UnPackSigType, AUTOMATIC, COMXF_APPL_CONST) unPackSigType,
  VAR(sint8, AUTOMATIC) byteDirection);
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/* extern declaration of ComXf_UnPack4ByteNotAlign */
#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
extern FUNC(uint32, COMXF_CODE) ComXf_UnPack4ByteNotAlign(
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) buffer,
  P2CONST(ComXf_UnPackSigType, AUTOMATIC, COMXF_APPL_CONST) unPackSigType,
  VAR(sint8, AUTOMATIC) byteDirection);
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/* extern declaration of ComXf_UnPack5ByteNotAlign */
#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
extern FUNC(uint32, COMXF_CODE) ComXf_UnPack5ByteNotAlign(
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) buffer,
  P2CONST(ComXf_UnPackSigType, AUTOMATIC, COMXF_APPL_CONST) unPackSigType,
  VAR(sint8, AUTOMATIC) byteDirection);
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/* extern declaration of ComXf_UnPackArray */
#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
extern FUNC(void, COMXF_CODE) ComXf_UnPackArray(
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) buffer,
  P2CONST(ComXf_UnPackSigType, AUTOMATIC, COMXF_APPL_CONST) unPackSigType,
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) dataElement);
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/* extern declaration of ComXf_UnPack5678ByteNotAlign */
#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
extern FUNC(uint64, COMXF_CODE) ComXf_UnPack5678ByteNotAlign(
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) buffer,
  P2CONST(ComXf_UnPackSigType, AUTOMATIC, COMXF_APPL_CONST) unPackSigType,
  VAR(sint8, AUTOMATIC) byteDirection);
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/* extern declaration of ComXf_UnPack9ByteNotAlign */
#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
extern FUNC(uint64, COMXF_CODE) ComXf_UnPack9ByteNotAlign(
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) buffer,
  P2CONST(ComXf_UnPackSigType, AUTOMATIC, COMXF_APPL_CONST) unPackSigType,
  VAR(sint8, AUTOMATIC) byteDirection);
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/* extern declaration of ComXf_UnPackFloat32ByteNotAlign */
#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
extern FUNC(float32, COMXF_CODE) ComXf_UnPackFloat32ByteNotAlign(
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) buffer,
  P2CONST(ComXf_UnPackSigType, AUTOMATIC, COMXF_APPL_CONST) unPackSigType,
  VAR(sint8, AUTOMATIC) byteDirection);
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/* extern declaration of ComXf_UnPackFloat64ByteNotAlign */
#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
extern FUNC(float64, COMXF_CODE) ComXf_UnPackFloat64ByteNotAlign(
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) buffer,
  P2CONST(ComXf_UnPackSigType, AUTOMATIC, COMXF_APPL_CONST) unPackSigType,
  VAR(sint8, AUTOMATIC) byteDirection);
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA RULE CHECKER)                   **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 */
#endif /* COMXF_LIB */
/*******************************************************************************
**                                 End of file                                **
*******************************************************************************/

