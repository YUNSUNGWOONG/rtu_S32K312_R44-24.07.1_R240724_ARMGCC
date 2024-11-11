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
**  SRC-MODULE: Dem_Dcm.h                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Event Manager                              **
**                                                                            **
**  PURPOSE   : Provision of extern declarations of APIs and Service ID       **
**              macros                                                        **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By            Description                          **
********************************************************************************
** 2.0.0.0   31-Dec-2023   EK Kim        Jira #CP44-1515 #CP44-3198 #CP44-3298**
** 1.0.1.0   07-May-2021   HaoLT6        R44-Redmine #18724                   **
** 1.0.0     26-Feb-2021   EK Kim        Initial version                      **
*******************************************************************************/

#ifndef DEM_DCM_H
#define DEM_DCM_H

/* 
   polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Not a
   defect
   polyspace:begin<MISRA-C:19.7:Not a defect:Justify with annotations> Not a
   defect
   polyspace:begin<MISRA-C:8.8:Not a defect:Justify with annotations> Not a
   defect
*/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem_Types.h"
#include "Dem_PCTypes.h" 
#include "Dem_Cfg.h"     /* Dem_PBcfg.h [SWS_Dem_00151] */
#include "Dem_Config.h"
#include "Dcm.h"

#if(DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
#include "Dem_Obd.h"
#endif

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/



/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"

#if(DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)

extern FUNC(Std_ReturnType, DEM_CODE)Dem_DcmGetDTRData(
  VAR(uint8, DEM_VAR) Obdmid,
  VAR(uint8, DEM_VAR) TIDindex,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) TIDvalue,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) UaSID,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) Testvalue,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) Lowlimvalue,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) Upplimvalue);

extern FUNC(Std_ReturnType, DEM_CODE)Dem_DcmGetNumTIDsOfOBDMID(
  VAR(uint8, DEM_VAR) Obdmid,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) numberOfTIDs);

extern FUNC(Std_ReturnType, DEM_CODE)Dem_DcmGetAvailableOBDMIDs(
  VAR(uint8, DEM_VAR) Obdmid,
  P2VAR(uint32, AUTOMATIC, DEM_APPL_DATA) Obdmidvalue);


/* Dem_DcmGetInfoTypeValue08 */
/* @Trace: DEM_SUD_DATATYPE_001 */
extern FUNC(Std_ReturnType, DEM_CODE) Dem_DcmGetInfoTypeValue08(
  VAR(Dcm_OpStatusType, DEM_VAR) OpStatus,
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) Iumprdata08,
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) Iumprdata08BufferSize
  );

/* Dem_DcmGetInfoTypeValue0B */
/* @Trace: DEM_SUD_DATATYPE_001 */
extern FUNC(Std_ReturnType, DEM_CODE) Dem_DcmGetInfoTypeValue0B(
  VAR(Dcm_OpStatusType, DEM_VAR) OpStatus,
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) Iumprdata0B,
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) Iumprdata0BBufferSize
  );
#if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
/* Dem_DcmGetInfoTypeValue79 */
/* Trace: DEM_19792_06_16 */
#if (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO)
extern FUNC(Std_ReturnType, DEM_CODE) Dem_DcmGetInfoTypeValue79(
  VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) DataValueBuffer,
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) DataValueBufferSize
  );
#endif
#endif /* J19792 */

#endif


#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
/* Dem_DcmReadDataOfPID01 */
extern FUNC(Std_ReturnType, DEM_CODE)Dem_DcmReadDataOfPID01(
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) PID01Value);

/* Dem_DcmReadDataOfPID1C */
extern FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID1C(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID1CValue);

/* Dem_DcmReadDataOfPID21 */
extern FUNC(Std_ReturnType, DEM_CODE)Dem_DcmReadDataOfPID21(
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) PID21Value);

/* Dem_DcmReadDataOfPID30 */
extern FUNC(Std_ReturnType, DEM_CODE)Dem_DcmReadDataOfPID30(
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) PID30Value);

/* Dem_DcmReadDataOfPID41 */
extern FUNC(Std_ReturnType, DEM_CODE)Dem_DcmReadDataOfPID41(
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) PID41Value);

extern FUNC(Std_ReturnType, DEM_CODE)Dem_DcmReadDataOfPID91(
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) PID91value);
#endif

#if (DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU)
/* Dem_DcmReadDataOfPID31 */
extern FUNC(Std_ReturnType, DEM_CODE)Dem_DcmReadDataOfPID31(
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) PID31Value);

/* Dem_DcmReadDataOfPID4D */
extern FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID4D(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID4DValue);

/* Dem_DcmReadDataOfPID4E */
extern FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID4E(
 P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID4EValue);
#endif

#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
extern FUNC(Std_ReturnType, DEM_CODE)Dem_DcmReadDataOfOBDFreezeFrame(
  VAR(uint8, DEM_VAR) PID,
  VAR(uint8, DEM_VAR) DataElementIndexOfPID,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)BufSize);
#endif

#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
extern FUNC(Std_ReturnType, DEM_CODE) Dem_DcmGetDTCOfOBDFreezeFrame(
  VAR(uint8, DEM_VAR) FrameNumber,
  P2VAR(uint32, AUTOMATIC, DEM_APPL_DATA)DTC,
  Dem_DTCFormatType DTCFormat);
#endif

#define DEM_STOP_SEC_CODE
#include "MemMap.h"


#endif /* DEM_DCM_H */


/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
