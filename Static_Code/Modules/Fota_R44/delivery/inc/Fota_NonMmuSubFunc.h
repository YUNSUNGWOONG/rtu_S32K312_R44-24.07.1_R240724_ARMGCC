/*******************************************************************************
**                                                                            **
**  (C) 2022 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: FOTA_NonMmuSubFunc.h                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR FOTA                                                  **
**                                                                            **
**  PURPOSE   : Provides all of the user type define                          **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By                        Description              **
********************************************************************************
*******************************************************************************/
#ifndef FOTA_NONMMUSUBFUNC_H
#define FOTA_NONMMUSUBFUNC_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#include "Fota_Cfg.h"
#include "Fota_IntTypes.h"
#include "Fota_IntFunc.h"
/*******************************************************************************
**                          Macros                                            **
*******************************************************************************/

/*******************************************************************************
**                     Global Data                                            **
*******************************************************************************/
extern FUNC(Std_ReturnType,FOTA_CODE) Fota_IsDualPartitionSwUnit(
		  VAR(uint16,AUTOMATIC) ecuSwUnit);

extern FUNC(Std_ReturnType,FOTA_CODE) Fota_GetSwUnitIdByPartition(
		VAR(Fota_PartitionType,AUTOMATIC) Partition,
		P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) SwUnitIdx);

extern FUNC(Std_ReturnType,FOTA_CODE) Fota_GetTargetPartition(
		P2VAR(Fota_PartitionType, AUTOMATIC, FOTA_PRIVATE_DATA) pTargetPartition);

extern FUNC(Std_ReturnType,FOTA_CODE) Fota_GetActivePartition(
		P2VAR(Fota_PartitionType, AUTOMATIC, FOTA_PRIVATE_DATA) pActivePartition);

extern FUNC(Std_ReturnType,FOTA_CODE) Fota_GetRunPartition(
		P2VAR(Fota_PartitionType, AUTOMATIC, FOTA_PRIVATE_DATA) pRunPartition);

#endif /* FOTA_INTTYPES_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
