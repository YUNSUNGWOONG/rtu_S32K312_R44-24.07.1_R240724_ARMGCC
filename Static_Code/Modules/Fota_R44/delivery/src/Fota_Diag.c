/*******************************************************************************
**                                                                            **
**  (C) 2022~2025 HYUNDAI AUTOEVER Co., Ltd.                                  **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Fota_Diag.c                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR FOTA                                                  **
**                                                                            **
**  PURPOSE   :                                                               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     20-Jun-2022   jys          Initial version                       **
** 2.0.0     20-Feb-2023   VuPH6        #38026                                **
*******************************************************************************/
#include "Rte_Fota.h"
#include "Fota_Diag.h"
#include "Fota.h"
#include "Dcm_Types.h"
#include "Fota_User_Callouts.h"
#include "Fota_IntFunc.h"
/* polyspace-begin MISRA-C3:2.7,8.13 [Justified:Low] "Not a defect" */

static Fota_CmdStatType ren_CurCmdStat=FOTA_CMD_IDLE;
/* polyspace-begin MISRA-C3:8.9 [Not a defect: Justify with annotations] "No Impact of this rule violation" */
static VAR(boolean, AUTOMATIC) rue_ResetAfterSwapReq=FALSE;
/* polyspace-end MISRA-C3:8.9 [Not a defect: Justify with annotations] "No Impact of this rule violation" */
static VAR(boolean, AUTOMATIC) rub_NotDefinedSwUnit=FALSE;


static FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Fota_DiagCmdSeqSet(Fota_CmdStatType CmdStatSet);
static FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Fota_DiagCmdSeqChk(Fota_CmdStatType CmdStatReq);

/*******************************************************************************
** Function Name        : Fota_Start_FinishUpdate                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Server Function in the Client-Server Port Comm      **
**                        DCM Call this at Finish Update (RID=0211)           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpErrorCode                                         **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                                                                            **
**                        Function(s) invoked :      Fota_ProcessAreaDataSync **
**                                                                            **
*******************************************************************************/
/* @Trace: FOTA_SRS_ES98765_02E_00022 FOTA_SRS_UDS_00027 */
#define Fota_START_SEC_CODE
#include "Fota_MemMap.h"

FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Fota_Start_FinishUpdate
(
  VAR(uint8, AUTOMATIC) OpStatus,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpErrorCode
)
{
  /* @Trace: FOTA_SUD_API_00177 */
  VAR(Std_ReturnType,AUTOMATIC) LddRetVal   = E_NOT_OK;


  #if(FOTA_IMPLEMENTATION_RULE==FOTA_OTA_ES98765_02)
    /* Commend Excution */
    LddRetVal = Fota_ProcessAreaDataSync(OpStatus, LpErrorCode);

  #else
    FOTA_UNUSED(OpStatus);
    LddRetVal = E_NOT_OK;
    *LpErrorCode = DCM_E_REQUESTOUTOFRANGE;

  #endif

  return LddRetVal;
}

#define Fota_STOP_SEC_CODE
#include "Fota_MemMap.h"

/*******************************************************************************
** Function Name        : Fota_Start_CheckMemory                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Server Function in the Client-Server Port Comm      **
**                        DCM Call this at Programming Dependency             **
**                        Checking                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : DataIn_CheckProgDependency_RoutineInSignal,         **
**                        OpStatus                                            **
**                                                                            **
**                                                                            **
** InOut parameter      : none                                                **
**                                                                            **
** Output Parameters    : LpCur_DataLen                                       **
**                        LpErrorCode                                         **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : none                                                **
**                                                                            **
** Remarks              : none                                                **
*******************************************************************************/
#define Fota_START_SEC_CODE
#include "Fota_MemMap.h"
/* @Trace: FOTA_SRS_ES95489_52E_00008 FOTA_SRS_ES98765_02E_00020 */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Fota_Start_CheckMemory
(
  VAR(uint8, AUTOMATIC) OpStatus,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpErrorCode
)
{
  /* @Trace: FOTA_SUD_API_00178 */
  VAR(Std_ReturnType,AUTOMATIC) LddRetVal   = E_NOT_OK;
  #if(FOTA_IMPLEMENTATION_RULE==FOTA_OTA_ES98765_02)
  VAR(uint8         ,AUTOMATIC) InMemArea   = FOTA_ZERO;
  VAR(uint16        ,AUTOMATIC) InEcuSwUnit = FOTA_ZERO;
  VAR(uint8         ,AUTOMATIC) OutMemArea   = FOTA_ZERO;


    if(Fota_DiagCmdSeqChk(FOTA_CMD_VERIFY)==E_OK)
    {
      /* Req Routine Control Option Recored */

      InMemArea = FOTA_ZERO;

      /* SwUnitHB SwUintLB */
      InEcuSwUnit=(uint16)FOTA_ZERO;

      /* Commend Excution */
      if(rub_NotDefinedSwUnit==FALSE)
      {
        LddRetVal = Fota_ProcessVerifyGenTwo(InMemArea, InEcuSwUnit, OpStatus, &OutMemArea, LpErrorCode);
      }
      else
      {
        LddRetVal = Fota_ProcessVerify_UserCallout(InMemArea, InEcuSwUnit, OpStatus, &OutMemArea, LpErrorCode);
      }


      if(LddRetVal==E_OK)
      {
        (void)Fota_DiagCmdSeqSet(FOTA_CMD_VERIFY);
      }
    }
    else
    {
      LddRetVal = E_NOT_OK;
      *LpErrorCode = DCM_E_REQUESTSEQUENCEERROR;
    }

  #else
    FOTA_UNUSED(OpStatus);
    LddRetVal = E_NOT_OK;
    *LpErrorCode = DCM_E_REQUESTOUTOFRANGE;

  #endif

  return LddRetVal;
}

#define Fota_STOP_SEC_CODE
#include "Fota_MemMap.h"

/*******************************************************************************
** Function Name        : Fota_Start_CheckProgrammingDependency               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Server Function in the Client-Server Port Comm      **
**                        DCM Call this at check programming dependency       **
**                        (RID=FF01)                                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : pRoutineDataIn                                      **
**                        OpStatus                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pRoutineDataOut                                     **
**                        LpCur_DataLen                                       **
**                        LpErrorCode                                         **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : rub_NotDefinedSwUnit          **
**                                                                            **
**                        Function(s) invoked :            Fota_DiagCmdSeqChk **
**                                                   (void)Fota_DiagCmdSeqSet **
**                                                   Fota_ProcessVerifyGenOne **
**                                             Fota_ProcessVerify_UserCallout **
**                                                Fota_ProcessActivateDualMem **
**                                              Fota_ProcessActivateSingleMem **
**                                           Fota_ProcessActivate_UserCallout **
**                                            (void) Fota_DestructiveResetSet **
**                                                                            **
*******************************************************************************/

#define Fota_START_SEC_CODE
#include "Fota_MemMap.h"
/* @Trace: FOTA_SRS_ES95489_52E_00008 FOTA_SRS_ES98765_02E_00029 FOTA_SRS_ES98765_01E_00007 */
/* @Trace: FOTA_SRS_ES98765_02E_00036 FOTA_SRS_ES98765_02E_00046 FOTA_SRS_UDS_00005 FOTA_SRS_UDS_00026 */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Fota_Start_CheckProgrammingDependency
(
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) pRoutineDataIn,
  VAR(uint8, AUTOMATIC) OpStatus,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pRoutineDataOut,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) LpCur_DataLen,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpErrorCode
)
{
  VAR(Std_ReturnType,AUTOMATIC) LddRetVal   = E_NOT_OK;
  VAR(uint8         ,AUTOMATIC) InMemArea   = FOTA_ZERO;
  VAR(uint16        ,AUTOMATIC) InEcuSwUnit = FOTA_ZERO;

  #if(FOTA_IMPLEMENTATION_RULE==FOTA_OTA_ES98765_01)
  /* @Trace: FOTA_SUD_API_00181 */
  VAR(uint8         ,AUTOMATIC) OutMemArea  = FOTA_ZERO;

  if(*LpCur_DataLen==FOTA_THREE)
  {
    if(Fota_DiagCmdSeqChk(FOTA_CMD_VERIFY)==E_OK)
    {
      /* Req Routine Control Option Recored */

      /* MemArea SwUnitHB SwUnitLB */
      InMemArea  =(uint8)pRoutineDataIn[FOTA_ZERO];

      /* polyspace-begin MISRA-C3:10.8 [Justified:Low] "Casting to different type for consistency." */
      /* polyspace-begin MISRA-C3:12.2 [Justified:Low] "No Impact of this rule violation" */
      InEcuSwUnit=(uint16)(pRoutineDataIn[FOTA_ONE]<<FOTA_EIGHT)|
              (uint16)(pRoutineDataIn[FOTA_TWO]);
      /* polyspace-end MISRA-C3:10.8 [Justified:Low] "Casting to different type for consistency." */
      /* polyspace-end MISRA-C3:12.2 [Justified:Low] "No Impact of this rule violation" */

      /* Commend Excution */

      if(rub_NotDefinedSwUnit==FALSE)
      {
        LddRetVal = Fota_ProcessVerifyGenOne(InMemArea, InEcuSwUnit, OpStatus, &OutMemArea, LpErrorCode);
      }
      else
      {
        LddRetVal = Fota_ProcessVerify_UserCallout(InMemArea, InEcuSwUnit, OpStatus, &OutMemArea, LpErrorCode);
      }

      /* Res Routine Control Option Recored */
      if(LddRetVal==E_OK)
      {
        pRoutineDataOut[FOTA_ZERO] = InMemArea;
        pRoutineDataOut[FOTA_ONE]  = (uint8)(InEcuSwUnit>>FOTA_EIGHT);
        pRoutineDataOut[FOTA_TWO]  = (uint8)InEcuSwUnit;
        *LpCur_DataLen = FOTA_THREE;
        (void)Fota_DiagCmdSeqSet(FOTA_CMD_VERIFY);
      }
    }
    else
    {
      LddRetVal = E_NOT_OK;
      *LpErrorCode = DCM_E_REQUESTSEQUENCEERROR;
    }
  }
  else
  {
    LddRetVal = E_NOT_OK;
    *LpErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }

  #elif(FOTA_IMPLEMENTATION_RULE==FOTA_OTA_ES98765_02)
  static Fota_DiagActCmdType rue_DiagActCmd=FOTA_DIAG_ACT_USER_INIT;
  FOTA_UNUSED(pRoutineDataIn);
  FOTA_UNUSED(pRoutineDataOut);

  if(*LpCur_DataLen==FOTA_ZERO)
  {
    /* Req Routine Control Option Recored */
    InMemArea  =(uint8)FOTA_ZERO;

    InEcuSwUnit=(uint16)FOTA_ZERO;

    if(OpStatus == DCM_INITIAL)
    {
      rue_DiagActCmd = FOTA_DIAG_ACT_USER_INIT;
    }

    switch(rue_DiagActCmd)
    {
        case FOTA_DIAG_ACT_USER_INIT:
        case FOTA_DIAG_ACT_USER_PEND:
          /* @Trace: FOTA_SUD_API_00182 */
          LddRetVal = Fota_ProcessActivate_UserCallout(InMemArea, InEcuSwUnit, OpStatus, LpErrorCode);

          /* polyspace-begin MISRA-C3:14.3 [Justified:Low] "if-condition depends on user logic." */
          if(LddRetVal==E_OK)
          {
            LddRetVal      = DCM_E_PENDING;
            rue_DiagActCmd = FOTA_DIAG_ACT_INTERAL_INIT;
          }
          /* polyspace-end MISRA-C3:14.3 [Justified:Low] "if-condition depends on user logic." */

        break;

        case FOTA_DIAG_ACT_INTERAL_INIT:
        /* @Trace: FOTA_SUD_API_00202 */
        #if(FOTA_MCU_MEMORY_ACCESS_TYPE!=FOTA_SINGLE_TYPE)
           /* Commend Excution */
           LddRetVal = Fota_ProcessActivateDualMem(InMemArea, InEcuSwUnit, DCM_INITIAL, LpErrorCode);
        #else
         /* Commend Excution */
         LddRetVal = Fota_ProcessActivateSingleMem(InMemArea, InEcuSwUnit, DCM_INITIAL, LpErrorCode);
        #endif

        rue_DiagActCmd = FOTA_DIAG_ACT_INTERAL_PEND;

        break;

        case FOTA_DIAG_ACT_INTERAL_PEND:
        /* @Trace: FOTA_SUD_API_00203 */
        #if(FOTA_MCU_MEMORY_ACCESS_TYPE!=FOTA_SINGLE_TYPE)
           /* Commend Excution */
           LddRetVal = Fota_ProcessActivateDualMem(InMemArea, InEcuSwUnit, OpStatus, LpErrorCode);
        #else
         /* Commend Excution */
         LddRetVal = Fota_ProcessActivateSingleMem(InMemArea, InEcuSwUnit, OpStatus, LpErrorCode);
        #endif

        break;

        default:
        /* Do Nothing */
        break;
    }


    /* Res Routine Control Option Recored */
    if(LddRetVal==E_OK)
    {
      *LpCur_DataLen = FOTA_ZERO;
      #if(FOTA_MCU_MEMORY_ACCESS_TYPE!=FOTA_SINGLE_TYPE)
       /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "if-condition depends on the configuration." */
       Fota_DestructiveResetSet();
       /* polyspace-end MISRA-C3:2.2 [Justified:Low] "if-condition depends on the configuration." */
    #endif

    }
  }
  else
  {
    LddRetVal = E_NOT_OK;
    *LpErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  #else

  LddRetVal = E_NOT_OK;
  *LpErrorCode = DCM_E_REQUESTOUTOFRANGE;

  #endif

  return LddRetVal;
}

#define Fota_STOP_SEC_CODE
#include "Fota_MemMap.h"

/*******************************************************************************
** Function Name        : Fota_Start_ReadActiveArea                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Server Function in the Client-Server Port Comm      **
**                        DCM Call this at read active area (RID=0210)        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : pRoutineDataIn                                      **
**                        OpStatus                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pRoutineDataOut                                     **
**                        LpCur_DataLen                                       **
**                        LpErrorCode                                         **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                                                                            **
**                        Function(s) invoked :       Fota_GetSwUnitIdByLabel **
**                                                 Fota_ProcessReadActiveArea **
**                                     Fota_ProcessReadActiveArea_UserCallout **
**                                                                            **
*******************************************************************************/

#define Fota_START_SEC_CODE
#include "Fota_MemMap.h"
/* @Trace: FOTA_SRS_UDS_00002 */
FUNC (Std_ReturnType, DCM_CALLOUT_CODE) Fota_Start_ReadActiveArea // return value & FctID
(
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pRoutineDataIn,
  VAR(uint8, AUTOMATIC) OpStatus,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pRoutineDataOut,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) LpCur_DataLen,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpErrorCode
)
{
  /* @Trace: FOTA_SUD_API_00183 */
  VAR(Std_ReturnType,AUTOMATIC) LddRetVal   = E_NOT_OK;

  #if (FOTA_IMPLEMENTATION_RULE==FOTA_OTA_ES98765_01)
  VAR(uint8         ,AUTOMATIC) OutMemArea   = FOTA_ZERO;
  VAR(uint16        ,AUTOMATIC) InEcuSwUnit = FOTA_ZERO;
  VAR(uint8         ,AUTOMATIC) SwUnitIdx   = FOTA_ZERO;

    if(*LpCur_DataLen==FOTA_TWO)
    {
      /* polyspace-begin MISRA-C3:10.8 [Justified:Low] "Casting to different type for consistency." */
      /* polyspace-begin MISRA-C3:12.2 [Justified:Low] "No Impact of this rule violation" */
      /* Req Routine Control Option Recored */
      InEcuSwUnit=(uint16)(pRoutineDataIn[FOTA_ZERO]<<FOTA_EIGHT)|
              (uint16)(pRoutineDataIn[FOTA_ONE ]);
      /* polyspace-end MISRA-C3:10.8 [Justified:Low] "Casting to different type for consistency." */
      /* polyspace-end MISRA-C3:12.2 [Justified:Low] "No Impact of this rule violation" */

      /* Commend Excution */
      if(Fota_GetSwUnitIdByLabel(InEcuSwUnit,&SwUnitIdx)==E_OK)
      {
        LddRetVal = Fota_ProcessReadActiveArea(InEcuSwUnit, OpStatus, &OutMemArea, LpErrorCode);
      }
      else
      {
        LddRetVal = Fota_ProcessReadActiveArea_UserCallout(InEcuSwUnit, OpStatus, &OutMemArea, LpErrorCode);
      }

      /* polyspace-begin DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the configuration." */
      /* Res Routine Control Option Recored */
      if(LddRetVal==E_OK)
      {
        pRoutineDataOut[FOTA_ZERO]=(uint8)OutMemArea;
        *LpCur_DataLen = FOTA_ONE;
      }
      /* polyspace-end DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the configuration." */
    }
    else
    {
      LddRetVal = E_NOT_OK;
      *LpErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }

  #else
    FOTA_UNUSED(pRoutineDataIn);
    FOTA_UNUSED(OpStatus);
    FOTA_UNUSED(pRoutineDataOut);
    FOTA_UNUSED(LpCur_DataLen);
    LddRetVal = E_NOT_OK;
    *LpErrorCode = DCM_E_REQUESTOUTOFRANGE;

  #endif

  return LddRetVal;
}
#define Fota_STOP_SEC_CODE
#include "Fota_MemMap.h"

/*******************************************************************************
** Function Name        : Fota_Start_SwapActiveArea                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Server Function in the Client-Server Port Comm      **
**                        DCM Call this at swap active area (RID=0213)        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : pRoutineDataIn                                      **
**                        OpStatus                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pRoutineDataOut                                     **
**                        LpCur_DataLen                                       **
**                        LpErrorCode                                         **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                                                                            **
**                        Function(s) invoked :       Fota_GetSwUnitIdByLabel **
**                                                Fota_ProcessActivateDualMem **
**                                           Fota_ProcessActivate_UserCallout **
**                                                                            **
*******************************************************************************/

#define Fota_START_SEC_CODE
#include "Fota_MemMap.h"
/* @Trace: FOTA_SRS_ES98765_01E_00008 FOTA_SRS_ES98765_01E_00009 FOTA_SRS_ES98765_02E_00028 FOTA_SRS_UDS_00004 */
FUNC (Std_ReturnType, DCM_CALLOUT_CODE) Fota_Start_SwapActiveArea // return value & FctID
(
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pRoutineDataIn,
  VAR(uint8, AUTOMATIC) OpStatus,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pRoutineDataOut,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) LpCur_DataLen,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpErrorCode
)
{
  /* @Trace: FOTA_SUD_API_00184 */
  VAR(Std_ReturnType,AUTOMATIC) LddRetVal   = E_NOT_OK;
  #if(FOTA_IMPLEMENTATION_RULE==FOTA_OTA_ES98765_01)
  VAR(uint8         ,AUTOMATIC) InMemArea   = FOTA_ZERO;
  VAR(uint16        ,AUTOMATIC) InEcuSwUnit = FOTA_ZERO;
  VAR(uint8         ,AUTOMATIC) SwUnitIdx   = FOTA_ZERO;
  #endif
  #if((FOTA_IMPLEMENTATION_RULE != FOTA_OTA_ES98765_01) || \
      (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))
    FOTA_UNUSED(pRoutineDataIn);
    FOTA_UNUSED(OpStatus);
    FOTA_UNUSED(pRoutineDataOut);
    FOTA_UNUSED(LpCur_DataLen);
  #endif
  #if (FOTA_IMPLEMENTATION_RULE==FOTA_OTA_ES98765_01)

  #if (FOTA_MCU_MEMORY_ACCESS_TYPE!=FOTA_SINGLE_TYPE)
  if (*LpCur_DataLen==FOTA_THREE)
  {
    if (NULL_PTR != pRoutineDataIn)
    {
      /* Req Routine Control Option Recored */
      InMemArea  =(uint8)pRoutineDataIn[FOTA_ZERO];

      /* polyspace-begin MISRA-C3:10.8 [Justified:Low] "Casting to different type for consistency." */
  /* polyspace-begin MISRA-C3:12.2 [Justified:Low] "No Impact of this rule violation" */
      InEcuSwUnit=(uint16)(pRoutineDataIn[FOTA_ONE]<<FOTA_EIGHT)|
                  (uint16)(pRoutineDataIn[FOTA_TWO]);
      /* polyspace-end MISRA-C3:10.8 [Justified:Low] "Casting to different type for consistency." */
  /* polyspace-end MISRA-C3:12.2 [Justified:Low] "No Impact of this rule violation" */

      /* Commend Excution */
      if (Fota_GetSwUnitIdByLabel(InEcuSwUnit, &SwUnitIdx)==E_OK)
      {
        LddRetVal = Fota_ProcessActivateDualMem(InMemArea, InEcuSwUnit, OpStatus, LpErrorCode);
      }
      else
      {
        LddRetVal = Fota_ProcessActivate_UserCallout(InMemArea, InEcuSwUnit, OpStatus, LpErrorCode);
      }

      if(LddRetVal==E_OK)
      {
        /* Res Routine Control Option Recored */
        pRoutineDataOut[FOTA_ZERO] =InMemArea;
        pRoutineDataOut[FOTA_ONE]  =(uint8)(InEcuSwUnit>>FOTA_EIGHT);
        pRoutineDataOut[FOTA_TWO]  =(uint8)(InEcuSwUnit);
        pRoutineDataOut[FOTA_THREE]=(uint8)(Fota_OutDelayTime_Callout()>>FOTA_EIGHT);
        pRoutineDataOut[FOTA_FOUR] =(uint8)(Fota_OutDelayTime_Callout());

        *LpCur_DataLen = FOTA_FIVE;
        rue_ResetAfterSwapReq=TRUE;
      }
    }
  }
  else
  {
    LddRetVal = E_NOT_OK;
    *LpErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  #else
  FOTA_UNUSED(SwUnitIdx);
  FOTA_UNUSED(InEcuSwUnit);
  FOTA_UNUSED(InMemArea);
  LddRetVal = E_NOT_OK;
  *LpErrorCode = DCM_E_REQUESTOUTOFRANGE;

  #endif  /* FOTA_MCU_MEMORY_ACCESS_TYPE!=FOTA_SINGLE_TYPE */
  #else
  LddRetVal = E_NOT_OK;
  *LpErrorCode = DCM_E_REQUESTOUTOFRANGE;
  #endif  /* FOTA_IMPLEMENTATION_RULE==FOTA_OTA_ES98765_01 */

  return LddRetVal;
}
#define Fota_STOP_SEC_CODE
#include "Fota_MemMap.h"

/*******************************************************************************
** Function Name        : Fota_Start_EraseTargetArea                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Server Function in the Client-Server Port Comm      **
**                        DCM Call this to erase target area                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : pRoutineDataIn                                      **
**                        OpStatus                                            **
**                                                                            **
** InOut parameter      : none                                                **
**                                                                            **
** Output Parameters    : LpOut_MemoryArea                                    **
**                        LpCur_DataLen                                       **
**                        LpErrorCode                                         **
**                                                                            **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : none                                                **
**                                                                            **
** Remarks              : none                                                **
*******************************************************************************/

#define Fota_START_SEC_CODE
#include "Fota_MemMap.h"
/* @Trace: FOTA_SRS_ES98765_01E_00007 FOTA_SRS_ES98765_02E_00046 FOTA_SRS_UDS_00003 */
FUNC (Std_ReturnType, DCM_CALLOUT_CODE) Fota_Start_EraseTargetArea // return value & FctID
(
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pRoutineDataIn,
  VAR(uint8, AUTOMATIC) OpStatus,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pRoutineDataOut,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) LpCur_DataLen,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpErrorCode
)
{
  /* @Trace: FOTA_SUD_API_00185 */
  VAR(Std_ReturnType,AUTOMATIC) LddRetVal   = E_NOT_OK;
  #if(FOTA_IMPLEMENTATION_RULE==FOTA_OTA_ES98765_01)
  #if(FOTA_MCU_MEMORY_ACCESS_TYPE!=FOTA_SINGLE_TYPE)
  VAR(uint8         ,AUTOMATIC) SwUnitIdx = FOTA_ZERO;
  #endif
  VAR(uint8         ,AUTOMATIC) InMemArea   = FOTA_ZERO;
  VAR(uint16        ,AUTOMATIC) InEcuSwUnit = FOTA_ZERO;
  VAR(uint8         ,AUTOMATIC) OutMemArea  = FOTA_ZERO;
  #endif
  #if((FOTA_IMPLEMENTATION_RULE != FOTA_OTA_ES98765_01) || \
      (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))
    FOTA_UNUSED(pRoutineDataIn);
    FOTA_UNUSED(OpStatus);
    FOTA_UNUSED(pRoutineDataOut);
    FOTA_UNUSED(LpCur_DataLen);
  #endif
  #if(FOTA_IMPLEMENTATION_RULE==FOTA_OTA_ES98765_01)

      #if(FOTA_MCU_MEMORY_ACCESS_TYPE!=FOTA_SINGLE_TYPE)
      if(*LpCur_DataLen==FOTA_THREE)
      {
        if(Fota_DiagCmdSeqChk(FOTA_CMD_ERASE)==E_OK)
        {
          /* Req Routine Control Option Recored */
          InMemArea  =(uint8)pRoutineDataIn[FOTA_ZERO];

          /* polyspace-begin MISRA-C3:10.8 [Justified:Low] "Casting to different type for consistency." */
          /* polyspace-begin MISRA-C3:12.2 [Justified:Low] "No Impact of this rule violation" */
          InEcuSwUnit=(uint16)(pRoutineDataIn[FOTA_ONE]<<FOTA_EIGHT)|
                (uint16)(pRoutineDataIn[FOTA_TWO]);
          /* polyspace-end MISRA-C3:10.8 [Justified:Low] "Casting to different type for consistency." */
          /* polyspace-end MISRA-C3:12.2 [Justified:Low] "No Impact of this rule violation" */

          /* Commend Excution */
          if(Fota_GetSwUnitIdByLabel(InEcuSwUnit,&SwUnitIdx)==E_OK)
          {
            LddRetVal = Fota_ProcessEraseTargetArea(InMemArea, InEcuSwUnit, OpStatus, &OutMemArea, LpErrorCode);    /* DualMem */

            rub_NotDefinedSwUnit = FALSE;
          }
          else
          {
            LddRetVal = Fota_ProcessEraseTargetArea_UserCallout(InMemArea, InEcuSwUnit, OpStatus, &OutMemArea, LpErrorCode);    /* DualMem */

            rub_NotDefinedSwUnit = TRUE;
          }

          /* Res Routine Control Option Recored */
          if(LddRetVal==E_OK)
          {
            pRoutineDataOut[FOTA_ZERO]=InMemArea;

            *LpCur_DataLen=FOTA_ONE;

            (void)Fota_DiagCmdSeqSet(FOTA_CMD_ERASE);
          }
        }
        else
        {
          LddRetVal = E_NOT_OK;
          *LpErrorCode = DCM_E_REQUESTSEQUENCEERROR;
        }
      }
      else
      {
        LddRetVal = E_NOT_OK;
        *LpErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
      }

    #else
      FOTA_UNUSED(OutMemArea);
      FOTA_UNUSED(InEcuSwUnit);
      FOTA_UNUSED(InMemArea);
      LddRetVal = E_NOT_OK;
      *LpErrorCode = DCM_E_REQUESTOUTOFRANGE;

      #endif

  #else

    LddRetVal = E_NOT_OK;
    *LpErrorCode = DCM_E_REQUESTOUTOFRANGE;

  #endif


  return LddRetVal;
}

#define Fota_STOP_SEC_CODE
#include "Fota_MemMap.h"

/*******************************************************************************
** Function Name        : Fota_Start_EraseMemory                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Server Function in the Client-Server Port Comm      **
**                        DCM Call this to erase memory (RID = FF00)          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : In_BlockId                                          **
**                        OpStatus                                            **
**                                                                            **
**                                                                            **
**                                                                            **
** InOut parameter      : none                                                **
**                                                                            **
** Output Parameters    :LpOut_MemoryArea                                     **
**                       LpCur_DataLen                                        **
**                       LpErrorCode                                          **
**                                                                            **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : none                                                **
**                                                                            **
** Remarks              : none                                                **
*******************************************************************************/

#define Fota_START_SEC_CODE
#include "Fota_MemMap.h"

/* @Trace: FOTA_SRS_ES98765_01E_00007 FOTA_SRS_ES98765_02E_00019 FOTA_SRS_ES98765_02E_00046 FOTA_SRS_UDS_00001 FOTA_SRS_UDS_00024 */
FUNC (Std_ReturnType, DCM_CALLOUT_CODE) Fota_Start_EraseMemory // return value & FctID
(
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pRoutineDataIn,
  VAR(uint8, AUTOMATIC) OpStatus,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pRoutineDataOut,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) LpCur_DataLen,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpErrorCode
)
{
  VAR(Std_ReturnType,AUTOMATIC) LddRetVal   = E_NOT_OK;
  #if(((FOTA_IMPLEMENTATION_RULE==FOTA_OTA_ES98765_01)&&(FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_SINGLE_TYPE)) || \
      (FOTA_IMPLEMENTATION_RULE==FOTA_OTA_ES98765_02))
  VAR(uint8         ,AUTOMATIC) InMemArea   = FOTA_ZERO;
  VAR(uint8         ,AUTOMATIC) OutMemArea  = FOTA_ZERO;
  VAR(uint16        ,AUTOMATIC) InEcuSwUnit = FOTA_ZERO;
  VAR(uint8         ,AUTOMATIC) SwUnitIdx   = FOTA_ZERO;
  #endif

  #if(FOTA_IMPLEMENTATION_RULE==FOTA_OTA_ES98765_01)
  /* @Trace: FOTA_SUD_API_00186 */
    #if(FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_SINGLE_TYPE)

      if(*LpCur_DataLen==FOTA_TWO)
      {
        if(Fota_DiagCmdSeqChk(FOTA_CMD_ERASE)==E_OK)
        {
          /* polyspace-begin MISRA-C3:10.8 [Justified:Low] "Casting to different type for consistency." */
          /* polyspace-begin MISRA-C3:12.2 [Justified:Low] "No Impact of this rule violation" */
          /* Req Routine Control Option Recored */
          InEcuSwUnit=(uint16)(pRoutineDataIn[FOTA_ZERO]<<FOTA_EIGHT)|
                      (uint16)(pRoutineDataIn[FOTA_ONE ]);
          /* polyspace-begin MISRA-C3:10.8 [Justified:Low] "Casting to different type for consistency." */
          /* polyspace-end MISRA-C3:12.2 [Justified:Low] "No Impact of this rule violation" */

          /* Commend Excution */
      if(Fota_GetSwUnitIdByLabel(InEcuSwUnit,&SwUnitIdx)==E_OK)
      {
        LddRetVal = Fota_ProcessEraseTargetArea(InMemArea, InEcuSwUnit, OpStatus, &OutMemArea, LpErrorCode);  /* SingleMem */

        rub_NotDefinedSwUnit = FALSE;
      }
      else
      {
        LddRetVal = Fota_ProcessEraseTargetArea_UserCallout(InMemArea, InEcuSwUnit, OpStatus, &OutMemArea, LpErrorCode);  /* SingleMem */

        rub_NotDefinedSwUnit = TRUE;
      }

          /* Res Routine Control Option Recored */
          if(LddRetVal==E_OK)
          {
            pRoutineDataOut[0]=(uint8)(InEcuSwUnit>>8);
            pRoutineDataOut[1]=(uint8)(InEcuSwUnit);

            *LpCur_DataLen=FOTA_TWO;
            (void)Fota_DiagCmdSeqSet(FOTA_CMD_ERASE);
          }
        }
        else
        {
          LddRetVal = E_NOT_OK;
          *LpErrorCode = DCM_E_REQUESTSEQUENCEERROR;
        }
      }
      else
      {
        /* MemBlock Update is not supported because of single memory downgrade protection logic */
        LddRetVal = E_NOT_OK;
        *LpErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
      }

    #else
      FOTA_UNUSED(pRoutineDataIn);
      FOTA_UNUSED(OpStatus);
      FOTA_UNUSED(pRoutineDataOut);
      FOTA_UNUSED(LpCur_DataLen);
      LddRetVal = E_NOT_OK;
      *LpErrorCode = DCM_E_REQUESTOUTOFRANGE;

    #endif


  #elif(FOTA_IMPLEMENTATION_RULE==FOTA_OTA_ES98765_02)
  /* @Trace: FOTA_SUD_API_00187 */
      if(*LpCur_DataLen==FOTA_TWO)
      {

        InMemArea  = FOTA_ZERO; /* Not Specify */

        InEcuSwUnit=((uint16)(pRoutineDataIn[FOTA_ZERO])<<FOTA_EIGHT)|
                    (uint16)(pRoutineDataIn[FOTA_ONE]);

        if(Fota_DiagCmdSeqChk(FOTA_CMD_ERASE)==E_OK)
        {
          #if(FOTA_MCU_MEMORY_ACCESS_TYPE!=FOTA_SINGLE_TYPE)

          if(Fota_GetSwUnitIdByLabel(InEcuSwUnit,&SwUnitIdx)==E_OK)
          {
            LddRetVal = Fota_ProcessEraseTargetArea(InMemArea, InEcuSwUnit, OpStatus, &OutMemArea, LpErrorCode);  /* DualMem */

            rub_NotDefinedSwUnit = FALSE;
          }
          else
          {
        LddRetVal = Fota_ProcessEraseTargetArea_UserCallout(InMemArea, InEcuSwUnit, OpStatus, &OutMemArea, LpErrorCode);    /* DualMem */

        rub_NotDefinedSwUnit = TRUE;
          }

            if(LddRetVal==E_OK)
            {
              pRoutineDataOut[FOTA_ZERO]=(uint8)(InEcuSwUnit>>FOTA_EIGHT);
              pRoutineDataOut[FOTA_ONE]=(uint8)(InEcuSwUnit);
              /* polyspace-begin DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the configuration." */
              if(FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_NON_MMU_TYPE)
              {
                pRoutineDataOut[FOTA_TWO]=(uint8)OutMemArea;
              }
              else
              {
                pRoutineDataOut[FOTA_TWO]=FOTA_ZERO;
              }
              /* polyspace-end DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the configuration." */

              *LpCur_DataLen=FOTA_THREE;
            }

          #else

          if(Fota_GetSwUnitIdByLabel(InEcuSwUnit,&SwUnitIdx)==E_OK)
          {
            LddRetVal = Fota_ProcessEraseTargetArea(InMemArea, InEcuSwUnit, OpStatus, &OutMemArea, LpErrorCode);  /* SingleMem */

            rub_NotDefinedSwUnit = FALSE;
          }
          else
          {
            LddRetVal = Fota_ProcessEraseTargetArea_UserCallout(InMemArea, InEcuSwUnit, OpStatus, &OutMemArea, LpErrorCode);

            rub_NotDefinedSwUnit = TRUE;
          }

            if(LddRetVal==E_OK)
            {
              pRoutineDataOut[FOTA_ZERO]=(uint8)(InEcuSwUnit>>FOTA_EIGHT);
              pRoutineDataOut[FOTA_ONE]=(uint8)(InEcuSwUnit);
              pRoutineDataOut[FOTA_TWO]=FOTA_ZERO;

              *LpCur_DataLen=FOTA_THREE;
            }

          #endif
            if(LddRetVal==E_OK)
            {
              (void)Fota_DiagCmdSeqSet(FOTA_CMD_ERASE);
            }
          }
          else
          {
            LddRetVal = E_NOT_OK;
            *LpErrorCode = DCM_E_REQUESTSEQUENCEERROR;
          }
      }
      else
      {
        /* MemBlock Update is not supported because of single memory downgrade protection logic */
        LddRetVal = E_NOT_OK;
        *LpErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
      }

  #else /* #if(FOTA_IMPLEMENTATION_RULE!=FOTA_OTA_ES98765_01) */
      FOTA_UNUSED(SwUnitIdx);
      FOTA_UNUSED(InEcuSwUnit);
      FOTA_UNUSED(OutMemArea);
      FOTA_UNUSED(InMemArea);
      FOTA_UNUSED(pRoutineDataIn);
      FOTA_UNUSED(OpStatus);
      FOTA_UNUSED(pRoutineDataOut);
      FOTA_UNUSED(LpCur_DataLen);
      LddRetVal = E_NOT_OK;
      *LpErrorCode = DCM_E_REQUESTOUTOFRANGE;

  #endif

  return LddRetVal;
}

#define Fota_STOP_SEC_CODE
#include "Fota_MemMap.h"
/*******************************************************************************
** Function Name        : Fota_RequestDownload                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : DCM CallOut function call this to request download  **
**                                                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, DataFormatIdentifier,                     **
**                        MemoryAddress, MemorySize                           **
**                                                                            **
**                                                                            **
** InOut parameter      : none                                                **
**                                                                            **
** Output Parameters    : LpBlockLength, LpNegativeErrorCode                  **
**                                                                            **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : none                                                **
**                                                                            **
** Remarks              : none                                                **
*******************************************************************************/
#define Fota_START_SEC_CODE
#include "Fota_MemMap.h"
/* @Trace: FOTA_SRS_ES95489_52E_00008 FOTA_SRS_ES98765_01E_00005 FOTA_SRS_ES98765_02E_00026 FOTA_SRS_ES98765_01E_00007 */
/* @Trace: FOTA_SRS_ES98765_02E_00046 FOTA_SRS_UDS_00006 FOTA_SRS_ES98765_02E_00025 FOTA_SRS_ES98765_01E_00006 */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Fota_RequestDownload
(
  VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
  VAR(uint8,AUTOMATIC) DataFormatIdentifier,
  VAR(uint32,AUTOMATIC) MemoryAddress,
  VAR(uint32,AUTOMATIC) MemorySize,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) LpBlockLength,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpErrorCode
)
{
  /* @Trace: FOTA_SUD_API_00188 */
  VAR(Std_ReturnType,AUTOMATIC) LddRetVal;

  LddRetVal = E_NOT_OK;

  if(Fota_DiagCmdSeqChk(FOTA_CMD_PROCESS)==E_OK)
  {
    if(rub_NotDefinedSwUnit==FALSE)
    {
      LddRetVal = Fota_ProcessRequestDownload(OpStatus,
                          DataFormatIdentifier,
                          MemoryAddress,
                          MemorySize,
                          LpBlockLength,
                          LpErrorCode);
    }
    else
    {
      LddRetVal = Fota_ProcessRequestDownload_UserCallout(OpStatus,
                            DataFormatIdentifier,
                            MemoryAddress,
                            MemorySize,
                            LpBlockLength,
                            LpErrorCode);
    }
  }

  return LddRetVal;
}

#define Fota_STOP_SEC_CODE
#include "Fota_MemMap.h"

/*******************************************************************************
** Function Name        : Fota_DataTransfer                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : DCM CallOut function call this to write memory      **
**                                                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus,                                           **
**                        MemoryIdentifier                                    **
**                        MemoryAddress                                       **
**                        MemoryWriteLen, pWriteData                          **
** InOut parameter      : none                                                **
**                                                                            **
** Output Parameters    : none                                                **
**                                                                            **
**                                                                            **
** Return parameter     : Dcm_ReturnWriteMemoryType                           **
**                                                                            **
** Preconditions        : none                                                **
**                                                                            **
** Remarks              : none                                                **
*******************************************************************************/
#define Fota_START_SEC_CODE
#include "Fota_MemMap.h"

/* @Trace: FOTA_SRS_ES95489_52E_00008 FOTA_SRS_ES98765_01E_00005 FOTA_SRS_ES98765_02E_00026 FOTA_SRS_ES98765_01E_00006 */
/* @Trace: FOTA_SRS_ES98765_01E_00007 FOTA_SRS_ES98765_02E_00046 FOTA_SRS_UDS_00007 FOTA_SRS_ES98765_02E_00025 */
FUNC(Dcm_ReturnWriteMemoryType, DCM_CALLOUT_CODE) Fota_DataTransfer
(
  VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
  VAR(uint8,AUTOMATIC) MemoryIdentifier /* Not Supported Argument */,
  VAR(uint32,AUTOMATIC) MemoryAddress,
  VAR(uint32,AUTOMATIC) MemoryWriteLen,
  P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) pWriteData
)
{
  /* @Trace: FOTA_SUD_API_00189 */
  VAR(Dcm_ReturnWriteMemoryType,AUTOMATIC) LddRetVal = DCM_WRITE_FAILED;

  if(Fota_DiagCmdSeqChk(FOTA_CMD_PROCESS)==E_OK)
  {
    if(rub_NotDefinedSwUnit==FALSE)
    {
      LddRetVal = Fota_ProcessTransferDataWrite(OpStatus,
                          MemoryIdentifier,
                          MemoryAddress,
                          MemoryWriteLen,
                          pWriteData);
    }
    else
    {
      LddRetVal = Fota_ProcessTransferDataWrite_UserCallout(OpStatus,
                                MemoryIdentifier,
                                MemoryAddress,
                                MemoryWriteLen,
                                pWriteData);
    }
  }

  return LddRetVal;
}

#define Fota_STOP_SEC_CODE
#include "Fota_MemMap.h"

/*******************************************************************************
** Function Name        : Fota_RequestTransferExit                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : DCM CallOut function call this to exit Transfer     **
**                                                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus,                                           **
**                        LpMemoryData                                        **
**                        LulParameterRecordSize                              **
**                                                                            **
** InOut parameter      : none                                                **
**                                                                            **
** Output Parameters    : LpErrorCode                                         **
**                                                                            **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : none                                                **
**                                                                            **
** Remarks              : none                                                **
*******************************************************************************/
#define Fota_START_SEC_CODE
#include "Fota_MemMap.h"

/* @Trace: FOTA_SRS_ES95489_52E_00008 FOTA_SRS_ES98765_01E_00007 FOTA_SRS_ES98765_02E_00046 FOTA_SRS_UDS_00008 */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Fota_RequestTransferExit
(
  VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpMemoryData,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) LulParameterRecordSize,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) LpErrorCode
)
{
  /* @Trace: FOTA_SUD_API_00190 */
  VAR(Std_ReturnType,AUTOMATIC) LddRetVal = E_NOT_OK;
  if(Fota_DiagCmdSeqChk(FOTA_CMD_PROCESS)==E_OK)
  {

    if(rub_NotDefinedSwUnit==FALSE)
    {
      LddRetVal = Fota_ProcessRequestTransferExit(OpStatus,
                            LpMemoryData,
                            LulParameterRecordSize,
                            LpErrorCode);
    }
    else
    {
      LddRetVal = Fota_ProcessRequestTransferExit_UserCallout(OpStatus,
                              LpMemoryData,
                              LulParameterRecordSize,
                              LpErrorCode);

    }

    if(LddRetVal==E_OK)
    {
      (void)Fota_DiagCmdSeqSet(FOTA_CMD_PROCESS);
    }
  }
  return LddRetVal;
}

#define Fota_STOP_SEC_CODE
#include "Fota_MemMap.h"

/*******************************************************************************
** Function Name        : Fota_DiagCmdSeqSet                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Setting Fota Diag Command Sequence state variable   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : Fota_CmdStatType                                    **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : ren_CurCmdStat                **
**                                                                            **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/

#define Fota_START_SEC_CODE
#include "Fota_MemMap.h"

static FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Fota_DiagCmdSeqSet(Fota_CmdStatType CmdStatSet)
{
  /* @Trace: FOTA_SUD_API_00180 */
  ren_CurCmdStat = CmdStatSet;

  return E_OK;
}

#define Fota_STOP_SEC_CODE
#include "Fota_MemMap.h"

/*******************************************************************************
** Function Name        : Fota_DiagCmdSeqChk                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Checking Fota Diag Command Sequence state variable  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : Fota_CmdStatType                                    **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : ren_CurCmdStat                **
**                                                                            **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/

#define Fota_START_SEC_CODE
#include "Fota_MemMap.h"

static FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Fota_DiagCmdSeqChk(Fota_CmdStatType CmdStatReq)
{
    Std_ReturnType RetVal = E_NOT_OK;

    switch(ren_CurCmdStat)
    {
      case FOTA_CMD_IDLE:
        /* @Trace: FOTA_SUD_API_00179 */
        if(CmdStatReq==FOTA_CMD_ERASE)
        {
          RetVal = E_OK;
        }

        break;
      /* erase complete state */
      case FOTA_CMD_ERASE:
        /* @Trace: FOTA_SUD_API_00204 */
        /* Initial state of the FOTA Handler after the ECU startup procedure */

        if((CmdStatReq==FOTA_CMD_PROCESS)||
         (CmdStatReq==FOTA_CMD_ERASE))
        {
          RetVal = E_OK;
        }

        break;

      /* process(TransferExit) complete state */
      case FOTA_CMD_PROCESS:
        /* @Trace: FOTA_SUD_API_00205 */
        /* Initial state of the FOTA Handler after the ECU startup procedure */

        if((CmdStatReq==FOTA_CMD_PROCESS)||
         (CmdStatReq==FOTA_CMD_ERASE)||
         (CmdStatReq==FOTA_CMD_VERIFY))
        {
          RetVal = E_OK;
        }

        break;

      /* Verify complete state */
      case FOTA_CMD_VERIFY:
        /* @Trace: FOTA_SUD_API_00206 */
        /* Initial state of the FOTA Handler after the ECU startup procedure */

        if((CmdStatReq==FOTA_CMD_VERIFY)||
         (CmdStatReq==FOTA_CMD_ERASE))
        {
          RetVal = E_OK;
        }

        break;

      default:
        /* Do Nothing */
        break;

    }

    return RetVal;
}
#define Fota_STOP_SEC_CODE
#include "Fota_MemMap.h"



/*******************************************************************************
** Function Name        : FotaBlockProcessing_Decompress                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : DCM CallOut function call this to start             **
**                      decompression                                         **
**                                                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : none                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
#define Fota_START_SEC_CODE
#include "Fota_MemMap.h"

FUNC(void,DCM_CALLOUT_CODE) FotaBlockProcessing_Decompress(void)
{
  
}
#define Fota_STOP_SEC_CODE
#include "Fota_MemMap.h"

/*******************************************************************************
** Function Name        : FotaBlockProcessing_Decrypt                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : DCM CallOut function call this to start             **
**                      decryption                                            **
**                                                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : none                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
#define Fota_START_SEC_CODE
#include "Fota_MemMap.h"

FUNC(void,DCM_CALLOUT_CODE) FotaBlockProcessing_Decrypt(void)
{
  
}
#define Fota_STOP_SEC_CODE
#include "Fota_MemMap.h"

/*********************************************************************************
** Function Name        : Fota_SupplierNotification_ServiceRequest_Confirmation **
**                                                                              **
** Service ID           : NA                                                    **
**                                                                              **
** Description          : Server Function in the Client-Server Port Comm        **
**                        DCM Call this to Service Request confirmation         **
**                                                                              **
** Sync/Async           : Synchronous                                           **
**                                                                              **
** Re-entrancy          : Non Reentrant                                         **
**                                                                              **
** Input Parameters     :                                                       **
** - SID : Service ID                                                           **
** - ReqType : Rx message address type                                          **
** - SourceAddress : Source address                                             **
** - ConfirmationStatus :                                                       **
**   - DCM_RES_POS_OK : Transmission of positive response was successful        **
**   - DCM_RES_POS_NOT_OK : Transmission of positive response failled           **
**   - DCM_RES_NEG_OK : Transmission of negative response was successful        **
**   - DCM_RES_NEG_NOT_OK : Transmission of negative response failled           **
**                                                                              **
** InOut parameter      :                                                       **
**                                                                              **
** Output Parameters    :                                                       **
**                                                                              **
**                                                                              **
** Return parameter     :                                                       **
** - Std_ReturnType                                                             **
**   - RTE_E_OK : Request was successful                                        **
**   - RTE_E_ServiceRequestNotification_E_NOT_OK : Request was not successful   **
**                                                                              **
** Preconditions        : none                                                  **
**                                                                              **
** Remarks              :                                                       **
*********************************************************************************/
#define Fota_START_SEC_CODE
#include "Fota_MemMap.h"
/* @Trace: FOTA_SRS_ES98765_01E_00008 FOTA_SRS_ES98765_01E_00009 FOTA_SRS_ES98765_02E_00028 FOTA_SRS_UDS_00004 */
#if (FOTA_DCM_VERSION == 40U)
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Fota_SupplierNotification_ServiceRequest_Confirmation
(
  VAR(uint8, AUTOMATIC) SID,
  VAR(uint8, AUTOMATIC) ReqType,
  VAR(uint16, AUTOMATIC) SourceAddress,
  VAR(Dcm_ConfirmationStatusType, AUTOMATIC) ConfirmationStatus
)
#else
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Fota_SupplierNotification_ServiceRequest_Confirmation
(
  VAR(uint8, AUTOMATIC) SID,
  VAR(uint8, AUTOMATIC) ReqType,
  VAR(uint16, AUTOMATIC) ConnectionId,
  VAR(Dcm_ConfirmationStatusType, AUTOMATIC) ConfirmationStatus,
  VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolType,
  VAR(uint16, AUTOMATIC) TesterSourceAddress
)
#endif
{
  /* @Trace: FOTA_SUD_API_00193 */
  Std_ReturnType LddRetVal = RTE_E_OK;
  #if (FOTA_DCM_VERSION == 40U)
  FOTA_UNUSED(SourceAddress);
  #else
  FOTA_UNUSED(ConnectionId);
  FOTA_UNUSED(ProtocolType);
  FOTA_UNUSED(TesterSourceAddress);
  #endif


  if((SID == DCM_ROUTINECONTROL) &&
     (ReqType == FOTA_ADDR_PHYSICAL) &&
     (rue_ResetAfterSwapReq == TRUE))
  {
    if(ConfirmationStatus == DCM_RES_POS_OK)
    {
      /* ECU RESET */
      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "if-condition depends on the configuration." */
      Fota_DestructiveResetSet();
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "if-condition depends on the configuration." */
        (void)Rte_Call_Fota_StateRequest_RequestReset(FOTA_MODE_USER);
        rue_ResetAfterSwapReq = FALSE;
      LddRetVal = RTE_E_OK;
    }
    else
    {
      rue_ResetAfterSwapReq = FALSE;
      LddRetVal = RTE_E_INVALID;
    }
  }
  else
  {

  }

  return LddRetVal;
}
#define Fota_STOP_SEC_CODE
#include "Fota_MemMap.h"

/*******************************************************************************
** Function Name       : Fota_SupplierNotification_ServiceRequest_Indication  **
** Input Parameters     :                           **
** - SID : Service ID                                                         **
** - RequestData : Pointer to received data                                   **
** - DataSize : Data length of received data                                  **
** - ReqType : Rx message address type                                        **
**             1 : Functional Address                                         **
**             0: Physical Address                                            **
**                                                                            **
** - SourceAddress : Source address (Refer to configureation DcmDslProtocolRx **
** TesterSourceAddr)                                                          **
** Output Parameters    :                                                     **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**                                                                            **
**   ErrorCode parameter value. (Refer to the Rte_Dcm_Type.h)                 **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_Xxx_E_NOT_OK : Request was not successful                        **
*******************************************************************************/
#define Fota_START_SEC_CODE
#include "Fota_MemMap.h"
#if (FOTA_DCM_VERSION == 40U)
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Fota_SupplierNotification_ServiceRequest_Indication
(
  VAR(uint8, AUTOMATIC) SID,
  P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) RequestData,
  VAR(uint16, AUTOMATIC) DataSize,
  VAR(uint8, AUTOMATIC) ReqType,
  VAR(uint16, AUTOMATIC) SourceAddress,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode
)
{
  /* @Trace: FOTA_SUD_API_00200 */
  Std_ReturnType LddRetVal = RTE_E_OK;
  FOTA_UNUSED(SID);
  FOTA_UNUSED(RequestData);
  FOTA_UNUSED(DataSize);
  FOTA_UNUSED(ReqType);
  FOTA_UNUSED(SourceAddress);
  FOTA_UNUSED(ErrorCode);
  return LddRetVal;
}
#else
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Fota_SupplierNotification_ServiceRequest_Indication
(
  VAR(uint8, AUTOMATIC) SID,
  P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) RequestData,
  VAR(uint16, AUTOMATIC) DataSize,
  VAR(uint8, AUTOMATIC) ReqType,
  VAR(uint16, AUTOMATIC) ConnectionId,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode,
  VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolType, VAR(uint16, AUTOMATIC) TesterSourceAddress
)
{
  /* @Trace: FOTA_SUD_API_00194 */
  Std_ReturnType LddRetVal = RTE_E_OK;
  FOTA_UNUSED(SID);
  FOTA_UNUSED(RequestData);
  FOTA_UNUSED(DataSize);
  FOTA_UNUSED(ReqType);
  FOTA_UNUSED(ConnectionId);
  FOTA_UNUSED(ErrorCode);
  FOTA_UNUSED(ProtocolType);
  FOTA_UNUSED(TesterSourceAddress);
  return LddRetVal;
}
#endif
#define Fota_STOP_SEC_CODE
#include "Fota_MemMap.h"

/*******************************************************************************
** Function Name        : UserCallout_PreRoutineControl                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Fota Generated Code                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/

#define Fota_START_SEC_CODE
#include "Fota_MemMap.h"

FUNC(Std_ReturnType,FOTA_CALLOUT_CODE) UserCallout_PreRoutineControl(void)
{
    /* @Trace: FOTA_SUD_API_00195 */
    Std_ReturnType retVal;

    retVal = E_OK;

    return retVal;
}

/*******************************************************************************
** Function Name        : UserCallout_PostRoutineControl                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Fota Generated Code                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/

FUNC(Std_ReturnType,FOTA_CALLOUT_CODE) UserCallout_PostRoutineControl(void)
{
    /* @Trace: FOTA_SUD_API_00196 */
    Std_ReturnType retVal;

    retVal = E_OK;

    return retVal;
}
#define Fota_STOP_SEC_CODE
#include "Fota_MemMap.h"

/* polyspace-end MISRA-C3:2.7,8.13 [Justified:Low] "Not a defect" */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
