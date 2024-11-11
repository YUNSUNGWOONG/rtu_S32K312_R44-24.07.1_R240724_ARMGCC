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
**  SRC-MODULE: FiM_PCTypes.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Function Inhibition Manager Module                    **
**                                                                            **
**  PURPOSE   : This file contains the structure definitions and macro        **
**              definitions of FiM module                                     **
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
** 0.0.4    11-Sept-2020   ThienVT1        Changes made As per Redmine #15664 **
** 0.0.3     20-Aug-2020   ThienVT1        Changes made As per Redmine #15009 **
** 0.0.2    18-July-2020   ThienVT1        Changes made As per Redmine #13068 **
** 0.0.1    05-June-2020   ThienVT1        Initial Version                    **
*******************************************************************************/
/* @Trace: FiM_SUD_MACRO_004*/
#ifndef FIM_PCTYPES_H
#define FIM_PCTYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "FiM_Types.h"        /* FiM Types Definition Header File */
#include "Dem_Types.h"        /* Dem Types Header File */
#include "Dem.h"              /* Dem Header File */

/*******************************************************************************
**                      MACRO Definitions                                     **
*******************************************************************************/



/* Inhibition mask for Last Failed */
#define FIM_LAST_FAILED                            0x00

/* Inhibition mask for Not Tested*/
#define FIM_NOT_TESTED                             0x01

/* Inhibition mask for Tested */
#define FIM_TESTED                                 0x02

/* Inhibition mask for Tested & Failed */
#define FIM_TESTED_AND_FAILED                      0x03

#define FIM_ZERO                                   0x00U
#define FIM_ONE                                    0x01U
#define FIM_FOUR                                   0x04U

#define FIM_TRUE                                   0x01
#define FIM_FALSE                                  0x00

#define FIM_NOT_INITIALIZED                        0x00
#define FIM_INITIALIZING                           0x01
#define FIM_INITIALIZED                            0x02

/* Bit 0 of the status is set */
#define FIM_MASK_LAST_FAILED                       0x01
/* Bit 1 of the status is set */
#define FIM_MASK_NOT_TESTED                        0x02
/*
 * Bit 1 of the status is not set, mask is same that of FIM_MASK_NOT_TESTED
 * Only the expected value after masking (FIM_EXP_STS_TESTED) will differ.
 */
#define FIM_MASK_TESTED                            0x02

/* Bit 0 and Bit 1 are set */
#define FIM_MASK_TESTED_AND_FAILED                 0x03

/* Expected result is the expected result of (status & mask) for a given mask*/

/* (Status)&(FIM_MASK_LAST_FAILED = 0000 0001b), expected 0000 0001b */
#define FIM_EXP_STS_LAST_FAILED                    0x01
/* (Status)&(FIM_MASK_NOT_TESTED = 0000 0010b), expected 0000 0010b */
#define FIM_EXP_STS_NOT_TESTED                     0x02
/* (Status)&(FIM_MASK_TESTED = 0000 0010b), expected 0000 0000b */
#define FIM_EXP_STS_TESTED                         0x00
/* (Status)&(FIM_MASK_TESTED_AND_FAILED = 0000 0011b), expected 0000 0001b */
#define FIM_EXP_STS_TESTED_AND_FAILED              0x01

#define FIM_MAX_INHIBIT_COUNTER                    0xFFFF
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                     EventMask Configuration structure                      **
*******************************************************************************/
/* @Trace: SWS_Fim_00002 */
/* @Trace: SWS_Fim_00003 */
/* @Trace: SWS_Fim_00010 */
/* @Trace: SWS_Fim_00013 */
/* @Trace: SRS_Fim_04700 */
/* @Trace: SRS_Fim_04701 */
/* @Trace: SRS_Fim_04706 */
/* @Trace: FiM_SUD_DATATYPE_013 */
typedef struct 
{
  /* This parameter provides the index number of FID array */
  FiM_FidsSizeType ddFidIndex;

  /*
   * This structure element gives the mask of event and must be fetched from
   * FiMInhInhibitionMask parameter in inhibition configuration container
   */
  uint8 ucInhibitionMask;
}FiM_FunctionIdMask;

/*******************************************************************************
**                         Event Information structure                        **
*******************************************************************************/
/* @Trace: SWS_Fim_00061 */
/* @Trace: SWS_Fim_00064 */
/* @Trace: SWS_Fim_00013 */
/* @Trace: SWS_Fim_00016 */
/* @Trace: SRS_Fim_04706 */
/* @Trace: SRS_Fim_04719 */
/* @Trace: FiM_SUD_DATATYPE_015 */
typedef struct 
{
  /*
   * This element gives the EventId and is fetched from parameter
   * DemEventId in DemEventParameter container if it is configured
   * in FiMInhEventRef in FiMInhibitionConfiguration container and from
   * parameter DemEventId in DemEventParameter container if it is configured
   * in FiMInputEventRef of FiMSummaryEvent container and this FiMSummaryEvent
   * container is configured in FiMInhSumRef in FiMInhibitionConfiguration
   * container.
   */
   /* @Trace: SWS_Fim_00061 */
  Dem_EventIdType ddEventId;

  /*
   * This structure element contains the no of FIDs associated to the above
   * eventid. Generation tool shall generate this parameter based on the
   * FiMInhFunctionIdRef parameter from the FiMInhibitionconfiguration
   * container
   */
  FiM_FidsSizeType ddNumberOfFids;

  /*
   * This element contains the index of first Fid (to which this event belongs)
   * in the array FiM_GaaFunctionIdMask
   */
  FiM_EventFidLinkType ddFidArrayIndex;
}FiM_EventInfo;

/*******************************************************************************
**                         Component Information structure                    **
*******************************************************************************/
typedef struct 
{
  /*
   * This element gives the ComponentId and is fetched from parameter
   * DemComponentId in DemComponent container if it is configured
   * in FiMInhComponentRef in FiMInhibitionConfiguration container
   */
  Dem_ComponentIdType ddComponentId;

  /*
   * This structure element contains the no of FIDs associated to the above
   * ComponentId. Generation tool shall generate this parameter based on the
   * FiMInhFunctionIdRef parameter from the FiMInhibitionconfiguration
   * container
   */
  uint16 ddNumberOfFids;

  /*
   * This element contains the index of first Fid (to which this event belongs)
   * in the array FiM_GaaFunctionIdMask
   */
  uint16 ddFidArrayIndex;
}FiM_ComponentInfo;

/*******************************************************************************
**                     ComponentMask Configuration structure                  **
*******************************************************************************/
typedef struct 
{
  /* This parameter provides the index number of FID array */
  FiM_FidsSizeType ddFidIndex;

}FiM_FunctionIdComponent;

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define FIM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#if (FIM_TOTAL_NUM_OF_FIDS > FIM_ZERO)
extern CONST(FiM_FunctionIdType, FIM_CONST)
    FiM_GaaFunctionId[FIM_TOTAL_NUM_OF_FIDS];
#endif

#if (FIM_TOTAL_NUM_OF_DEM_EVENTS > FIM_ZERO)
extern CONST(FiM_EventInfo, FIM_CONST)
    FiM_GaaEventInfo[FIM_TOTAL_NUM_OF_DEM_EVENTS];
#endif

#if (FIM_TOTAL_NUM_OF_FUNCTION_ID_MASK > FIM_ZERO)
extern CONST(FiM_FunctionIdMask, FIM_CONST)
    FiM_GaaFunctionIdMask[FIM_TOTAL_NUM_OF_FUNCTION_ID_MASK];
#endif

#if (FIM_TOTAL_NUM_OF_DEM_COMPONENT > FIM_ZERO)
extern CONST(FiM_ComponentInfo, FIM_CONST)
    FiM_GaaComponentInfo[FIM_TOTAL_NUM_OF_DEM_COMPONENT];
#endif

#if (FIM_TOTAL_NUM_OF_FUNCTION_ID_COMPONENT > FIM_ZERO)
extern CONST(FiM_FunctionIdComponent, FIM_CONST)
    FiM_GaaFunctionIdComponent[FIM_TOTAL_NUM_OF_FUNCTION_ID_COMPONENT];
#endif

#define FIM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* polyspace:end<MISRA-C:8.12:Not a defect:Justify with annotations> size of array is determined by configuration */

#endif /* FIM_PCTYPES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
