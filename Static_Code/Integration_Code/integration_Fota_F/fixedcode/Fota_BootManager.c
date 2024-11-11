/*******************************************************************************
**                                                                            **
**  (C) 2022 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Fota_BootManager.c                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR FOTA                                                  **
**                                                                            **
**  PURPOSE   : Provide definition of FOTA function                           **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     23-Dec-2022   VuPH6        Initial version                       **
** 2.0.0     20-Feb-2023   VuPH6        #38233                                **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Fota_User_Callouts.h"
#include "Fota_MagicKeyMgr.h"

#if (defined __GHS__) || (defined __ghs__)
/* polyspace-begin MISRA-C3:D1.1,8.4 [Not a Defect:Medium] "#pragma is used for assembler" */
// TEST //#pragma ghs section rodata=".ASW_SECURITY_KEY"
Fota_MagicKeyAreaType_forImage const Fbl_Gu32_SecurityKey = {{{FOTA_CPD_KEY_VALUE, 0xFFFFFFFFUL, FOTA_CPD_KEY_VALUE, 0xFFFFFFFFUL}}, \
                                                            {{{FOTA_SECURITY_KEY_VALUE, (uint32)FOTA_ZERO, FOTA_SECURITY_KEY_VALUE, (uint32)FOTA_ZERO}}}};
// TEST //#pragma ghs section

#elif defined __TASKING__
#pragma section farrom "ASW_SECURITY_KEY"
Fota_MagicKeyAreaType_forImage const Fbl_Gu32_SecurityKey = {{{FOTA_CPD_KEY_VALUE, 0xFFFFFFFFUL, FOTA_CPD_KEY_VALUE, 0xFFFFFFFFUL}}, \
                                                            {{{FOTA_SECURITY_KEY_VALUE, (uint32)FOTA_ZERO, FOTA_SECURITY_KEY_VALUE, (uint32)FOTA_ZERO}}}};
#pragma section farrom restore
/* polyspace-end MISRA-C3:D1.1,8.4 [Not a Defect:Medium] "#pragma is used for assembler" */
#endif /* (defined __GHS__) || (defined __ghs__) */

#ifndef FOTA_INTEGRATION_SINGLEMEM_PLATFORM

#include "Fota_Cfg.h"
#include "Fota_IntFunc.h"
#include "Fota_Globals.h"
#include "Fota.h"
#include "Fota_PflsInterface.h"
#include "Fota_BootManager.h"
#include "Fota_Callout_Fixed.h"
/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                     Global Data                                            **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define Fota_START_SEC_CODE
#include "Fota_MemMap.h"

#if FOTA_BOOT_MANAGER_USED
#if (FOTA_MODE == FOTA_FBL_MODE)
static FUNC(void, FOTA_CODE) Fota_CheckWarmStart(void);

static FUNC(void, FOTA_CODE) Fota_CheckForAppl(void);

static FUNC(Std_ReturnType, FOTA_CODE) Fbl_GetMainSwEntryPointAddress(
  P2VAR(uint32, AUTOMATIC, FOTA_PRIVATE_DATA) entryPointAddress);

#endif
/*******************************************************************************
** Function Name        : Fota_BootManager                                    **
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
** Input Parameters     : OpStatus,                                           **
**                                                                            **
**                                                                            **
**                                                                            **
** InOut parameter      :                                                     **
**                                                                            **
** Output Parameters    :                                                     **
**                                                                            **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : none                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
#if (FOTA_MODE == FOTA_FBL_MODE)
FUNC(void, FOTA_CODE) Fota_BootManager(void)
{
  Fota_CheckWarmStart();
  /* polyspace-begin CERT-C:INT36-C, MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
  * the register value can be read via the address" */
  /* Check reset is cold reset or control by FBL, data in RAM is cleared */
  if (*((uint32*)Fota_StartupCommandAddress) != FBL_STARTUP_COMMAND_VALUE)
  {
    *((uint32*)Fota_StartupCommandAddress) = 0;
    Fota_CheckForAppl();
  }
  else
  {
    *((uint32*)Fota_StartupCommandAddress) = 0;
  }
  /* polyspace-end CERT-C:INT36-C, MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
  * the register value can be read via the address" */
}
/*******************************************************************************
** Function Name        : Fota_CheckWarmStart                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if it's cold reset or warm reset              **
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
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : none                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
#if (HWRESOURCE_VENDOR(HWRESOURCE_CYPRESS)) || (HWRESOURCE_FAMILY(HWRESOURCE_S32K31X)) || (HWRESOURCE_FAMILY(HWRESOURCE_S32G2X))
static FUNC(void, FOTA_CODE) Fota_CheckWarmStart(void)
{
  volatile uint64 * Lpu64_MemPtr;
  uint16    Lu16_MemLength;
  uint16    Lu16_Indx;
  volatile uint64 Lu64_Zero = 0;
  Std_ReturnType ResetReason;

  /* Reset save RAM initialization */
  /* Check if it is warm start */
  ResetReason = Fota_IsWarmReset();

  if (E_NOT_OK == ResetReason)
  {

    /* Its power-on[cold]reset, Need to write/clear reset save RAM
     * before accessing it to avoid ECC error while read in later stage
     */

    /* Initialize reset save RAM for BTL */
    /* polyspace-begin CERT-C:EXP36-C, MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
    * the register value can be read via the address" */
    Lpu64_MemPtr = (volatile uint64 *)Fota_Gau32_BTLResetSaveData;
    Lu16_MemLength = (uint16)&Fota_Gpu32_BTLResetSaveDataSize /(uint16)sizeof(uint64);
    /* polyspace-end CERT-C:EXP36-C, MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
    * the register value can be read via the address" */

    for (Lu16_Indx = 0u; Lu16_Indx < (uint16)(Lu16_MemLength); Lu16_Indx++)
    {
      /* polyspace-begin DEFECT:OUT_BOUND_PTR, CERT-C:ARR30-C,MEM35-C, MISRA-C3:18.1 [Justified:High] "It gets array index in range" */
      Lpu64_MemPtr[Lu16_Indx] = Lu64_Zero;
      /* polyspace-end DEFECT:OUT_BOUND_PTR, CERT-C:ARR30-C,MEM35-C, MISRA-C3:18.1 [Justified:High] "It gets array index in range" */
    }

    /* Initialize Reset safe ram, used by application and bootloader to share
     * ProgSignature
     */
    #if 0
    Lpu64_MemPtr = (volatile uint64 *)Fota_Gau32_BTL_APPLResetSaveData;
    Lu16_MemLength = (uint16)&Fota_Gpu32_BTL_APPLResetSaveDataSize/(uint16)sizeof(uint64);

    for (Lu16_Indx = 0UL; Lu16_Indx < (uint16)(Lu16_MemLength); Lu16_Indx++)
    {
      Lpu64_MemPtr[Lu16_Indx] = Lu64_Zero;
    }
    #endif
  }
}
#else
static FUNC(void, FOTA_CODE) Fota_CheckWarmStart(void)
{
  uint32 * memPtr;
  uint16    memLength;
  uint16    Lu16_Indx;
  Std_ReturnType ResetReason;

  /* Reset save RAM initialization */
  /* Check if it is warm start */
  ResetReason = Fota_IsWarmReset();

  /* polyspace-begin MISRA-C3:14.3 [Justified:Low] "if-condition depends on the MCU." */
  if (E_NOT_OK == ResetReason)
  {

    /* Its power-on[cold]reset, Need to write/clear reset save RAM
     * before accessing it to avoid ECC error while read in later stage
     */

    /* Initialize reset save RAM for BTL */
    /* polyspace-begin MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
    * the register value can be read via the address" */
	  memPtr = (uint32 *)Fota_Gau32_BTLResetSaveData;
	  memLength = (uint16)((uint32)&Fota_Gpu32_BTLResetSaveDataSize / (uint32)sizeof(uint32));
    /* polyspace-end MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
    * the register value can be read via the address" */

    for (Lu16_Indx = 0u; Lu16_Indx < (uint16)(memLength); Lu16_Indx++)
    {
    	memPtr[Lu16_Indx] = 0U;
    }

    /* Initialize Reset safe ram, used by application and bootloader to share
     * ProgSignature
     */
    #if 0
    memPtr = (uint32 *)Fota_Gau32_BTL_APPLResetSaveData;
    Lu16_MemLength = (uint16)((uint32)&Fota_Gpu32_BTL_APPLResetSaveDataSize / (uint32)sizeof(uint32));

    for (Lu16_Indx = 0UL; Lu16_Indx < (uint16)(memLength); Lu16_Indx++)
    {
    	memPtr[Lu16_Indx] = 0U;
    }
    #endif
  }
  /* polyspace-end MISRA-C3:14.3 [Justified:Low] "if-condition depends on the MCU." */
}
#endif /* HWRESOURCE_VENDOR(HWRESOURCE_CYPRESS) */
/*******************************************************************************
** Function Name        : Fota_CheckForAppl                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check Application is valid codition and jump        **
**                        software                                            **
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
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : none                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(void, FOTA_CODE) Fota_CheckForAppl(void)
{
  uint32 startAddressEntry;
  Std_ReturnType retVal;
  void (*Fota_FuncPtr)(void);

  startAddressEntry = 0UL;
  retVal = Fbl_GetMainSwEntryPointAddress(&startAddressEntry);

  if (E_OK == retVal)
  {
    /* polyspace-begin MISRA-C3:14.3 [Justified:Low] "if-condition depends on the configuration." */
    if (FOTA_ARM_ARCHITECHTURE_MCU == FOTA_STD_ON)
    {
      startAddressEntry = startAddressEntry + 1;
    }
    /* polyspace-end MISRA-C3:14.3 [Justified:Low] "if-condition depends on the configuration." */

	/* polyspace-begin MISRA-C3:11.1 [Justified:Low] "Call application using the application entry address available" */
	/* polyspace-begin CERT-C:INT36-C [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
	* the register value can be read via the address" */
    Fota_FuncPtr = (void (*)(void))startAddressEntry;
	/* polyspace-end CERT-C:INT36-C [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
	* the register value can be read via the address" */

    if (NULL_FUNC != *Fota_FuncPtr)
    {
      /* Application didn't requested to remain in Bootloader */
      /* Perform any system steps before entering in application */
      Fota_PrepareForApplEntry();

      Fota_FuncPtr();
    }
	/* polyspace-end MISRA-C3:11.1 [Justified:Low] "Call application using the application entry address available" */
  }
}
/*******************************************************************************
** Function Name        : Fbl_GetMainSwEntryPointAddress                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check Application is valid codition and jump        **
**                        software                                            **
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
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : none                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(Std_ReturnType, FOTA_CODE) Fbl_GetMainSwEntryPointAddress(
  P2VAR(uint32, AUTOMATIC, FOTA_PRIVATE_DATA) entryPointAddress)
{
  uint32 Lu32_EntryPointAddress;
  Std_ReturnType retVal = E_NOT_OK;
  uint8 swPriorityIndex;
  
  if (Fbl_SelectEntryPoint(&Lu32_EntryPointAddress)==E_OK){
  #if (FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_NON_MMU_TYPE)
    if (Fota_GetTopPrioActKey(FOTA_FLKEY_MGR, &swPriorityIndex)==E_OK)
    {
      *entryPointAddress = Fota_Gast_SwUnitTable[swPriorityIndex].StartAddress;
      retVal = E_OK;
    }
    else
    {
      /* do nothing */
    }
  #else
    if(Fota_GetSoftwareModuleBlkBySwType(FOTA_RTSW_TYPE,&swPriorityIndex)==E_OK)
    {
      #if(FOTA_IMPLEMENTATION_RULE==FOTA_OTA_ES98765_01) /* 1st Gen MMU or Single */
      if(Fota_ChkActKey(swPriorityIndex, FOTA_DIRECT_AREA)==E_OK)
      #else
	  if(Fota_ChkActKeyAllSwUnit(FOTA_DIRECT_AREA)==E_OK) /* 2nd Gen  MMU or Single */
      #endif
	  {
		  *entryPointAddress = Fota_Gast_SwUnitTable[swPriorityIndex].StartAddress;
		  retVal = E_OK;
  	  }
    }
  #endif
  }
  else{
    *entryPointAddress = Lu32_EntryPointAddress;
    retVal = E_OK;
  }

  return retVal;
}
#endif /* FOTA_MODE == FOTA_FBL_MODE */
#endif /* #if FOTA_BOOT_MANAGER_USED */

#define Fota_STOP_SEC_CODE
#include "Fota_MemMap.h"

#endif /* #ifndef FOTA_INTEGRATION_SINGLEMEM_PLATFORM */
