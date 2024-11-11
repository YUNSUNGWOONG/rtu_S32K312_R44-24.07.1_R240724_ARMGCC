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
**  SRC-MODULE: IoHwAb_DigDir.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : APIs implementation for IoHwAb module                         **
**              IoHwAb_DigDirInit                                             **
**              IoHwAb_DigDirReadDirect                                       **
**              IoHwAb_DigDirWriteDirect                                      **
**              IoHwAb_DigDirSetToInput                                       **
**              IoHwAb_DigDirSetToOutput                                      **
**              IoHwAb_DigDirIsInput                                          **
**              IoHwAb_DigDirIsOutput                                         **
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
** 1.3.0.1   30-Jun-2022  KhaLN1            #CP44-365                         **
** 1.1.0     15-Jul-2021  YangJin.Kim       R44-Redmine #18100                **
** 1.0.0     04-Dec-2020  YangJin.Kim       R40-Redmine #26992                **
*******************************************************************************/

/* polyspace-begin MISRA-C3:D4.14 [Justified:Unset] "The pointer is checked always." */
/* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Unset] "It depends on the configuration" */
/* polyspace-begin MISRA-C3:8.3 [Justified:Unset] "Prototypes are generated wrongly. It will be fixed soon" */
/* polyspace-begin DEFECT:DEAD_CODE [Justified:Unset] "It depends on the configuration." */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb_DigDir.h"
#include "IoHwAb_Config.h"
#include "Rte_IoHwAb.h"
#include "Rte_Type.h"

#if (IOHWAB_USE_DIG_DIR == STD_ON)
#include "Port.h"
#include "Dio.h"
#endif /* (IOHWAB_USE_DIG_DIR == STD_ON) */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if (IOHWAB_USE_DIG_DIR == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_DigDirInit                                   **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service initilize DigDir module.               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
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
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaDigDirChIdx,                            **
**                          IoHwAb_GaaDigDirPinDir,                           **
**                          IoHwAb_GaaGenInfos                                **
**                        Function(s) invoked    : none                       **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_DigDirInit(void)
{
  IoHwAb_IndexType LucIdx;
  IoHwAb_IndexType LucChRefIdx;

  /* update the direction information */
  for(LucIdx = 0; LucIdx < IOHWAB_DIGDIR_NUM_LGC; LucIdx++)
  {
    LucChRefIdx = IoHwAb_GaaDigDirChIdx[LucIdx];
    IoHwAb_GaaDigDirPinDir[LucIdx] = IoHwAb_GaaGenInfos[LucChRefIdx].ddCfgPinDir;
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*polyspace-begin RTE:UNR [Not a Defect] "No Impact of this rule violation"*/
/*******************************************************************************
** Function Name        : IoHwAb_DigDirReadDirect                             **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service reads the level value of DIO channel.  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Level                                               **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaDigDirChIdx,                            **
**                          IoHwAb_GaaGenInfos                                **
**                        Function(s) invoked    :                            **
**                          Dio_ReadChannel                                   **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_12412 */
/* @Trace: SWR_IOHWAB_201_002 */
/* @Trace: IoHwAb_SUD_API_023 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_DigDirReadDirect(IoHwAb_IndexType ChIdx,
  P2VAR(IoHwAb_LevelType, AUTOMATIC, IOHWAB_APPL_DATA) Level)
{
  IoHwAb_IndexType LucChRefIdx = 0U;
  if ( ChIdx < IOHWAB_DIGDIR_NUM_LGC)
  {
     LucChRefIdx = IoHwAb_GaaDigDirChIdx[ChIdx];

     if (Level != NULL_PTR)
     {
        if (Dio_ReadChannel(IoHwAb_GaaGenInfos[LucChRefIdx].ddDioChType) == STD_LOW)
        {
           if (IoHwAb_GaaGenInfos[LucChRefIdx].ucPolar == IOHWAB_POL_LOW)
           {
             *Level = IOHWAB_HIGH;
           }
           else
           {
             *Level = IOHWAB_LOW;
           }
        }
        else
        {
           if (IoHwAb_GaaGenInfos[LucChRefIdx].ucPolar == IOHWAB_POL_LOW)
           {
              *Level = IOHWAB_LOW;
           }
           else
           {
              *Level = IOHWAB_HIGH;
           }
        }
     }
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
/*polyspace-end RTE:UNR*/

/*polyspace-begin RTE:UNR [Not a Defect] "No Impact of this rule violation"*/
/*******************************************************************************
** Function Name        : IoHwAb_DigDirWriteDirect                            **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service writes the level value of DIO channel. **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx, Level                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaDigDirChIdx,                            **
**                          IoHwAb_GaaGenInfos                                **
**                        Function(s) invoked    :                            **
**                          Dio_WriteChannel                                  **
*******************************************************************************/
/* @Trace: SWS_IoHwAb_00078 SWR_IOHWAB_201_001 */
/* @Trace: IoHwAb_SUD_API_024 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_DigDirWriteDirect(IoHwAb_IndexType ChIdx,
  IoHwAb_LevelType Level)
{
  Dio_LevelType LvBuf;
  IoHwAb_IndexType LucChRefIdx = 0U;
  if (ChIdx < IOHWAB_DIGDIR_NUM_LGC )
  {
    LucChRefIdx = IoHwAb_GaaDigDirChIdx[ChIdx];

    if (Level == IOHWAB_LOW)
    {
       if (IoHwAb_GaaGenInfos[LucChRefIdx].ucPolar == IOHWAB_POL_LOW)
       {
          LvBuf = (Dio_LevelType)STD_HIGH;
       }
       else 
       {
          LvBuf = (Dio_LevelType)STD_LOW;
       }   
    }
    else
    {
       if (IoHwAb_GaaGenInfos[LucChRefIdx].ucPolar == IOHWAB_POL_LOW)
       {
          LvBuf = STD_LOW;
       }
       else
       {
          LvBuf = STD_HIGH;
       }
    }
    Dio_WriteChannel(IoHwAb_GaaGenInfos[LucChRefIdx].ddDioChType, LvBuf);
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
/*polyspace-end RTE:UNR*/

/*******************************************************************************
** Function Name        : IoHwAb_DigDirSetToInput                             **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service changes the pin direction to input.    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaDigDirChIdx,                            **
**                          IoHwAb_GaaDigDirPinDir,                           **
**                          IoHwAb_GaaGenInfos                                **
**                        Function(s) invoked    :                            **
**                          Port_SetPinDirection                              **
*******************************************************************************/
/* @Trace: SWS_IoHwAb_00078 SWR_IOHWAB_101_001 */
/* @Trace: IoHwAb_SUD_API_025 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_DigDirSetToInput(IoHwAb_IndexType ChIdx)
{
  IoHwAb_IndexType LucChRefIdx = 0U;
  if (ChIdx < IOHWAB_DIGDIR_NUM_LGC )
  {
    LucChRefIdx = IoHwAb_GaaDigDirChIdx[ChIdx];
    IoHwAb_GaaDigDirPinDir[ChIdx] = PORT_PIN_IN;
    Port_SetPinDirection(IoHwAb_GaaGenInfos[LucChRefIdx].ddPortPinType, PORT_PIN_IN);
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_DigDirSetToOutput                            **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service changes the pin direction to output.   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaDigDirChIdx,                            **
**                          IoHwAb_GaaDigDirPinDir,                           **
**                          IoHwAb_GaaGenInfos                                **
**                        Function(s) invoked    :                            **
**                          Port_SetPinDirection                              **
*******************************************************************************/
/* @Trace: SWS_IoHwAb_00078 SWR_IOHWAB_101_002 */
/* @Trace: IoHwAb_SUD_API_026 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_DigDirSetToOutput(IoHwAb_IndexType ChIdx)
{
  IoHwAb_IndexType LucChRefIdx = 0U;
  if (ChIdx < IOHWAB_DIGDIR_NUM_LGC )
  {
    LucChRefIdx = IoHwAb_GaaDigDirChIdx[ChIdx];
    IoHwAb_GaaDigDirPinDir[ChIdx] = PORT_PIN_OUT;
    Port_SetPinDirection(IoHwAb_GaaGenInfos[LucChRefIdx].ddPortPinType, PORT_PIN_OUT);
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_DigDirIsInput                                **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service checks whether the pin direction is    **
**                        input.                                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Result                                              **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaDigDirChIdx,                            **
**                          IoHwAb_GaaDigDirPinDir                            **
**                        Function(s) invoked    : none                       **
*******************************************************************************/
/* @Trace: IoHwAb_SUD_API_027 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_DigDirIsInput(IoHwAb_IndexType ChIdx,
  P2VAR(IoHwAb_BoolType, AUTOMATIC, IOHWAB_APPL_DATA) blResult)
{
  if ((blResult != NULL_PTR) && (ChIdx < IOHWAB_DIGDIR_NUM_LGC ))
  {
    *blResult = (IoHwAb_GaaDigDirPinDir[ChIdx] == PORT_PIN_IN)
      ? IOHWAB_TRUE : IOHWAB_FALSE;
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_DigDirIsOutput                               **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service checks whether the pin direction is    **
**                        output.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Result                                              **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaDigDirChIdx,                            **
**                          IoHwAb_GaaDigDirPinDir                            **
**                        Function(s) invoked    : none                       **
*******************************************************************************/
/* @Trace: IoHwAb_SUD_API_028 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_DigDirIsOutput(IoHwAb_IndexType ChIdx,
  P2VAR(IoHwAb_BoolType, AUTOMATIC, IOHWAB_APPL_DATA) blResult)
{
  if ((blResult != NULL_PTR) && (ChIdx < IOHWAB_DIGDIR_NUM_LGC ))
  {
    *blResult = (IoHwAb_GaaDigDirPinDir[ChIdx] == PORT_PIN_OUT)
      ? IOHWAB_TRUE : IOHWAB_FALSE;
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (IOHWAB_USE_DIG_DIR == STD_ON) */
/* polyspace-end MISRA-C3:D4.14 [Justified:Unset] "The pointer is checked always." */
/* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Unset] "It depends on the configuration" */
/* polyspace-end MISRA-C3:8.3 [Justified:Unset] "Prototypes are generated wrongly. It will be fixed soon" */
/* polyspace-end DEFECT:DEAD_CODE [Justified:Unset] "It depends on the configuration." */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
