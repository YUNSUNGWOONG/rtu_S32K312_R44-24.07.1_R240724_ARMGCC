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
**  FILE-NAME : Cache_Setup.c                                                 **
**                                                                            **
**  TARGET    : S32K31x                                                       **
**                                                                            **
**  PRODUCT   :                                                               **
**                                                                            **
**  PURPOSE   : APIs implementation for Cache setup                           **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: Yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: Yes                                       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                              Revision History                              **
********************************************************************************
** Revision   Date          By            Description                         **
********************************************************************************
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Cache_Setup.h"
#include "Cache_Ip.h"
#include "CDD_Mcl.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : User_Cache_Init                                     **
**                                                                            **
** Service ID           :                                                     **
**                                                                            **
** Description          : This function executes initialization of Cache.     **
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
** Remarks              : None                                                **
*******************************************************************************/
void User_Cache_Init(void)
{
#if (CACHE_IP_IS_AVAILABLE == STD_ON)
  /*----------------------------------------------------------------------------
  ** Note : If user want to enable Cache, user should modify the below code.
  **        Please contact NXP for example code.
  **        The below code enables only I-Cache.
  **--------------------------------------------------------------------------*/
  /* Invalidate I-Cache*/
  Cache_Ip_Invalidate(MCL_CACHE_CORE, CACHE_IP_INSTRUCTION);

  /* Enable I-Cache */
  Cache_Ip_Enable (MCL_CACHE_CORE, CACHE_IP_INSTRUCTION);
#endif
}

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
