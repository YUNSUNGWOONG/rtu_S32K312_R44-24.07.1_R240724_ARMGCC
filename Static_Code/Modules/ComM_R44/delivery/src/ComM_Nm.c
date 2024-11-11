/* polyspace +1 MISRA2012:1.1 [Not a defect:Low] "This rule is manually checked and has no impact." */
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
**  SRC-MODULE: ComM_Nm.c                                                     **
**                                                                            **
**  TARGET    : ALL                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR COM Manager                                           **
**                                                                            **
**  PURPOSE   : Provision of ComM Nm Indication APIs                          **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision       Date                By               Description            **
********************************************************************************
** 1.1.0.0        12-Aug-2022         ThuanVT          R44-Redmine #29733     **
** 1.0.4.1        20-Jun-2022         SMKwon           CP44-115               **
** 1.0.1          27-Dec-2020         DatNXT           R44-Redmine #14801     **
** 1.0.0          15-Dec-2020         JsLim            Initial Version        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "ComM_Internal.h" /* ComM Internal functions header file */
#include "ComM_Nm.h"              /* Nm callback header file */
/* @Trace: ComM_SUD_MACRO_002 */
/* @Trace: SRS_ComM_AR_00217 SRS_ComM_AR_00217 SRS_ComM_AR_00223
 * SRS_ComM_AR_00224 SRS_ComM_AR_00226 SRS_ComM_AR_00227 SRS_ComM_AR_00228
 * SRS_ComM_AR_00229 SRS_ComM_AR_00230 SRS_ComM_AR_00231 SRS_ComM_AR_00233
 * SRS_ComM_AR_00234 SRS_ComM_AR_00237 SRS_ComM_AR_00238 SRS_ComM_AR_00239 
 */
/* @Trace: ComM_SUD_MACRO_005   */
#include "ComM_Ram.h"             /* ComM global Ram variables header file */
#include "SchM_ComM.h"            /* SchM data protection API header file */

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : ComM_Nm_NetworkStartIndication                      **
**                                                                            **
** Service ID           : 0x15                                                **
**                                                                            **
** Description          : Indicates that a Nm message has been received       **
**                        in the Bus sleep mode                               **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : Channel                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : ComM shall be Initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_ChannelMapArray[], ComM_NmIndication[]         **
**                        Function(s) invoked    :                            **
**                        ComM_ChannelDETCheck(),                             **
**                        SchM_Enter_ComM_NM_INDICATION_PROTECTION(),         **
**                        SchM_Exit_ComM_NM_INDICATION_PROTECTION()           **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386
 * SRS_BSW_00406 SRS_ComM_AR_00189 SRS_ComM_AR_00154
 */
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COMM_CODE)
  ComM_Nm_NetworkStartIndication(NetworkHandleType Channel)
{
  /* @Trace: ComM_SUD_API_100 */
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Variable to store E_OK or E_NOT_OK or COMM_UNINIT */
  Std_ReturnType returnValue;
  #endif

  /* Variable to store channel */
  NetworkHandleType handleChnlIndex;
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Check if the channel is valid or not */
  returnValue = ComM_ChannelDETCheck(Channel,
    COMM_NM_NETWORKSTARTINDICATION_SID);

  /* Check, if no development error occurred */
  if (E_OK == returnValue)
  #endif /* End of if (COMM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* @Trace: ComM_SUD_API_101 */
    #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)

    /* Get the channel id from the mapping array */
    handleChnlIndex = ComM_ChannelMapArray[Channel]; /* polyspace MISRA2012:D4.14 [Not a defect:Low] "Channel value and ComM_ChannelMapArray are generated by Tcode and has checked manual and it is not having any impact" */
    #else

    /* Channel Id is updated into local variable */
    handleChnlIndex = Channel;
    #endif

    /* Enter Data Protection */
    SchM_Enter_ComM_NM_INDICATION_PROTECTION();

    /* Update Status of Global Variable */
    /* polyspace +4 DEFECT:OUT_BOUND_ARRAY [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +3 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +2 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    ComM_NmIndication[handleChnlIndex] = COMM_NMSTART_IND; /* polyspace RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    #if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)
    ComM_NmRequestProcessing[handleChnlIndex] = COMM_FALSE;
    #endif

    /* Exit Data Protection */
    SchM_Exit_ComM_NM_INDICATION_PROTECTION();
  }
} /* End of ComM_Nm_NetworkStartIndication(NetworkHandleType Channel) */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : ComM_Nm_NetworkMode                                 **
**                                                                            **
** Service ID           : 0x18                                                **
**                                                                            **
** Description          : Indicates Network Management has entered Network    **
**                        Mode                                                **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : Channel                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : ComM shall be Initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_ChannelMapArray[], ComM_NmIndication[]         **
**                        Function(s) invoked    :                            **
**                        ComM_ChannelDETCheck(),                             **
**                        SchM_Enter_ComM_NM_INDICATION_PROTECTION(),         **
**                        SchM_Exit_ComM_NM_INDICATION_PROTECTION()           **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386
 * SRS_BSW_00406 SRS_ComM_AR_00188 SRS_ComM_AR_00154
 */
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COMM_CODE)
  ComM_Nm_NetworkMode(NetworkHandleType Channel)
{
  /* @Trace: ComM_SUD_API_102 */
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Standard return type variable */
  Std_ReturnType returnValue;
  #endif

  /* Variable to store channel */
  NetworkHandleType handleChnlIndex;
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Check if the channel is valid or not */
  returnValue = ComM_ChannelDETCheck(Channel, COMM_NM_NETWORKMODE_SID);

  /* Check, if no development error occurred */
  if (E_OK == returnValue)
  #endif
  {
    /* @Trace: ComM_SUD_API_103 */
    /* Check If Binary Search Is Enabled*/
    #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)

    /* Get the channel id from the mapping array */
    handleChnlIndex = ComM_ChannelMapArray[Channel]; /* polyspace MISRA2012:D4.14 [Not a defect:Low] "Channel value and ComM_ChannelMapArray are generated by Tcode and has checked manual and it is not having any impact" */
    #else

    /* Channel Id is updated into local variable */
    handleChnlIndex = Channel;
    #endif

    /* Enter Data Protection */
    SchM_Enter_ComM_NM_INDICATION_PROTECTION();

    /* Update Status of Global Variable */
    /* polyspace +4 DEFECT:OUT_BOUND_ARRAY [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +3 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +2 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    ComM_NmIndication[handleChnlIndex] = COMM_NMMODE_IND; /* polyspace RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    #if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)
    ComM_NmRequestProcessing[handleChnlIndex] = COMM_FALSE;
    #endif

    /* Exit Data Protection */
    SchM_Exit_ComM_NM_INDICATION_PROTECTION();
  }
} /* End of ComM_Nm_NetworkMode(NetworkHandleType Channel) */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : ComM_Nm_PrepareBusSleepMode                         **
**                                                                            **
** Service ID           : 0x19                                                **
**                                                                            **
** Description          : Indicates Network Management has entered Prepare Bus**
**                        Sleep Mode                                          **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : Channel                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : ComM shall be Initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_ChannelMapArray[], ComM_NmIndication[]         **
**                        Function(s) invoked    :                            **
**                        ComM_ChannelDETCheck(),                             **
**                        SchM_Enter_ComM_NM_INDICATION_PROTECTION(),         **
**                        SchM_Exit_ComM_NM_INDICATION_PROTECTION()           **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386
 * SRS_BSW_00406 SRS_ComM_AR_00190
 */
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COMM_CODE)
ComM_Nm_PrepareBusSleepMode(NetworkHandleType Channel)
{
  /* @Trace: ComM_SUD_API_104 */
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Standard return type variable */
  Std_ReturnType returnValue;
  #endif

  /* Variable to store channel */
  NetworkHandleType handleChnlIndex;
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Check if the channel is valid or not */
  returnValue = ComM_ChannelDETCheck(Channel, COMM_NM_PREPAREBUSSLEEPMODE_SID);

  /* Check, if no development error occurred */
  if (E_OK == returnValue)
  #endif
  {
    /* @Trace: ComM_SUD_API_105 */
    #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)

    /* Get the channel id from the mapping array */
    handleChnlIndex = ComM_ChannelMapArray[Channel]; /* polyspace MISRA2012:D4.14 [Not a defect:Low] "Channel value and ComM_ChannelMapArray are generated by Tcode and has checked manual and it is not having any impact" */
    #else

    /* Channel Id is updated into local variable */
    handleChnlIndex = Channel;
    #endif

    /* Enter Data Protection */
    SchM_Enter_ComM_NM_INDICATION_PROTECTION();

    /* Update Status of Global Variable */
    /* polyspace +5 DEFECT:OUT_BOUND_ARRAY [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +4 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +3 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +2 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    ComM_NmIndication[handleChnlIndex] = COMM_PREPBUSSLEEPMODE_IND;
    #if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)
    ComM_NmRequestProcessing[handleChnlIndex] = COMM_FALSE;
    #endif

    /* Exit Data Protection */
    SchM_Exit_ComM_NM_INDICATION_PROTECTION();
  }
} /* End of ComM_Nm_PrepareBusSleepMode */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : ComM_Nm_BusSleepMode                                **
**                                                                            **
** Service ID           : 0x1a                                                **
**                                                                            **
** Description          : Indication that network management has entered      **
**                        Bus Sleep Mode                                      **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : Channel                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : ComM shall be Initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_ChannelMapArray[], ComM_NmIndication[]         **
**                        Function(s) invoked    :                            **
**                        ComM_ChannelDETCheck(),                             **
**                        SchM_Enter_ComM_NM_INDICATION_PROTECTION(),         **
**                        SchM_Exit_ComM_NM_INDICATION_PROTECTION()           **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386
 * SRS_BSW_00406 SRS_ComM_AR_00187
 */
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COMM_CODE)
ComM_Nm_BusSleepMode(NetworkHandleType Channel)
{
  /* @Trace: ComM_SUD_API_106 */
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Standard return type variable */
  Std_ReturnType returnValue;
  #endif

  /* Variable to store the channel */
  NetworkHandleType handleChnlIndex;
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Check if channel is valid or not */
  returnValue = ComM_ChannelDETCheck(Channel, COMM_NM_BUSSLEEPMODE_SID);

  /* Check, if no development error occurred */
  if (E_OK == returnValue)
  #endif
  {
    /* @Trace: ComM_SUD_API_107 */
    #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)

    /* Get the channel id from the mapping array */
    handleChnlIndex = ComM_ChannelMapArray[Channel]; /* polyspace MISRA2012:D4.14 [Not a defect:Low] "Channel value and ComM_ChannelMapArray are generated by Tcode and has checked manual and it is not having any impact" */
    #else

    /* Channel Id is updated into local variable */
    handleChnlIndex = Channel;
    #endif

    /* Enter Data Protection */
    SchM_Enter_ComM_NM_INDICATION_PROTECTION();

    /* Update Status of Global Variable */
    /* polyspace +4 DEFECT:OUT_BOUND_ARRAY [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    ComM_NmIndication[handleChnlIndex] = COMM_BUSSLEEPMODE_IND; 
    #if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)
    ComM_NmRequestProcessing[handleChnlIndex] = COMM_FALSE;
    #endif

    /* Exit Data Protection */
    SchM_Exit_ComM_NM_INDICATION_PROTECTION();
  }
} /* End of ComM_Nm_BusSleepMode */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : ComM_Nm_RestartIndication                           **
**                                                                            **
** Service ID           : 0x1b                                                **
**                                                                            **
** Description          : Indicates that the Transmission of NM-messages      **
**                        has failed in Network mode                          **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : Channel                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : ComM shall be initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_ChannelMapArray[], ComM_NmIndication[]         **
**                        Function(s) invoked    :                            **
**                        ComM_ChannelDETCheck(),                             **
**                        SchM_Enter_ComM_NM_INDICATION_PROTECTION(),         **
**                        SchM_Exit_ComM_NM_INDICATION_PROTECTION()           **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386
 * SRS_BSW_00406 SRS_ComM_AR_00191
 */
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COMM_CODE)
ComM_Nm_RestartIndication(NetworkHandleType Channel)
{
  /* @Trace: ComM_SUD_API_108 */
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Standard return type variable */
  Std_ReturnType returnValue;
  #endif

  /* Variable to store the channel*/
  NetworkHandleType handleChnlIndex;
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Check if the channel is valid or not */
  returnValue = ComM_ChannelDETCheck(Channel, COMM_NM_RESTARTINDICATION_SID);

  /* Check, if no development error occurred */
  if (E_OK == returnValue)
  #endif
  {
    /* @Trace: ComM_SUD_API_109 */
    #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)

    /* Get the channel id from the mapping array */
    handleChnlIndex = ComM_ChannelMapArray[Channel]; /* polyspace MISRA2012:D4.14 [Not a defect:Low] "Channel value and ComM_ChannelMapArray are generated by Tcode and has checked manual and it is not having any impact" */
    #else

    /* Channel Id is updated into local variable */
    handleChnlIndex = Channel;
    #endif

    /* Enter Data Protection */
    SchM_Enter_ComM_NM_INDICATION_PROTECTION();

    /* Update Status of Global Variable */
    /* polyspace +4 DEFECT:OUT_BOUND_ARRAY [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +3 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +2 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    ComM_NmIndication[handleChnlIndex] = COMM_NMRST_IND;
    #if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)
    ComM_NmRequestProcessing[handleChnlIndex] = COMM_FALSE;
    #endif

    /* Exit Data Protection */
    SchM_Exit_ComM_NM_INDICATION_PROTECTION();
  }
} /* End of ComM_Nm_RestartIndication */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

