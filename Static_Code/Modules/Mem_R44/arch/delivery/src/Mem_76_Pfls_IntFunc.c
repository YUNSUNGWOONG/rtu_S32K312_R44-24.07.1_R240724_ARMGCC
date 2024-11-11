/*******************************************************************************
**                                                                            **
**  (C) 2022 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Mem_76_Pfls_IntFunc.c                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Memory Driver                                         **
**                                                                            **
**  PURPOSE   :                           **
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

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#include "Mem_76_Pfls_Cfg.h"
#include "Mem_76_Pfls_Types.h"
#include "Mem_76_Pfls_IntFunc.h"
#include "Mem_76_Pfls_Globals.h"
#include "Mem_76_Pfls_Regs.h"
#include "Hse_Ip.h"
#if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
#include "SchM_Mem_76_Pfls.h"
#endif
/* polyspace-begin MISRA-C3:8.4,8.9,20.9 [Not a defect: Justify with annotations] "No Impact of this rule violation" */

/*******************************************************************************
**                         Macros                                             **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
static hseSrvDescriptor_t   Mem_76_Pfls_HseSrvDescriptor;
static Hse_Ip_ReqType Mem_76_Pfls_HseIpRequest;
static hseSrvResponse_t Mem_76_Pfls_HseSrvResponse;

#define MEM_76_PFLS_START_SEC_CONST_32
#include "MemMap.h"


#define MEM_76_PFLS_STOP_SEC_CONST_32
#include "MemMap.h"


#define MEM_76_PFLS_START_SEC_VAR_INIT_32
#include "MemMap.h"



#define MEM_76_PFLS_STOP_SEC_VAR_INIT_32
#include "MemMap.h"

#define MEM_76_PFLS_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Code Flash Memory Block Information */
#if(MEM_76_PFLS_SUPPORT_MCU ==MEM_76_PFLS_MCU_S32K311)
static const VAR(Mem_76_Pfls_BlockInformation, MEM_76_PFLS_VAR_INIT) Mem_76_Pfls_BlockInfor[MEM_76_PFLS_BLOCK_COUNT]=
{
  {0x00400000UL, 0x0047FFFFUL,64UL,32UL,32UL},
  {0x00500000UL, 0x0057FFFFUL,64UL,32UL,32UL}
};
const VAR(uint32, MEM_76_PFLS_VAR_INIT) Mem_76_Pfls_Reg_DcmStat=0x402AC000UL;
#elif(MEM_76_PFLS_SUPPORT_MCU ==MEM_76_PFLS_MCU_S32K312)
static const VAR(Mem_76_Pfls_BlockInformation, MEM_76_PFLS_VAR_INIT) Mem_76_Pfls_BlockInfor[MEM_76_PFLS_BLOCK_COUNT]=
{
  {0x00400000UL, 0x004FFFFFUL,128UL,32UL,96UL},
  {0x00500000UL, 0x005FFFFFUL,128UL,32UL,96UL}
};
const VAR(uint32, MEM_76_PFLS_VAR_INIT) Mem_76_Pfls_Reg_DcmStat=0x402AC000UL;
#elif(MEM_76_PFLS_SUPPORT_MCU ==MEM_76_PFLS_MCU_S32K314)
static const VAR(Mem_76_Pfls_BlockInformation, MEM_76_PFLS_VAR_INIT) Mem_76_Pfls_BlockInfor[MEM_76_PFLS_BLOCK_COUNT]=
{
  {0x00400000UL, 0x004FFFFFUL,128UL,32UL,96UL},
  {0x00500000UL, 0x005FFFFFUL,128UL,32UL,96UL},
  {0x00600000UL, 0x006FFFFFUL,128UL,32UL,96UL},
  {0x00700000UL, 0x007FFFFFUL,128UL,32UL,96UL}
};
const VAR(uint32, MEM_76_PFLS_VAR_INIT) Mem_76_Pfls_Reg_DcmStat=0x402AC000UL;
#endif
#define MEM_76_PFLS_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"


/*******************************************************************************
**                      Function Declaration                                  **
*******************************************************************************/
#define MEM_76_PFLS_START_SEC_CODE
#include "MemMap.h"

#define MEM_76_PFLS_STOP_SEC_CODE
#include "MemMap.h"

#if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
#define MEM_76_PFLS_START_SEC_RAM_CODE
#else
#define MEM_76_PFLS_START_SEC_CODE
#endif
#include "MemMap.h"




/* Function to perform pre-Write check */
FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_PreWriteConditionCheck
(
  VAR(Mem_76_Pfls_OperationType, AUTOMATIC) OperationType
);

/* Function to peform pre-Erase check */
FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_PreEraseConditionCheck(void);

/* Function to clear all error flags */
FUNC(void, MEM_76_PFLS_CODE) Mem_76_Pfls_ClearAllErrorFlags(void);

/* Function to unlock sector and super sector */
FUNC(void, MEM_76_PFLS_CODE) Mem_76_Pfls_SectorUnlock(\
    VAR(uint32, AUTOMATIC) sectorIndex);

/* Function to lock sector and super sector */
FUNC(void, MEM_76_PFLS_CODE) Mem_76_Pfls_Sectorlock(\
    VAR(uint32, AUTOMATIC) sectorIndex);

/* Function to prepare for program/erase operation  */
FUNC(void, MEM_76_PFLS_CODE) Mem_76_Pfls_PrepareOperation(\
    VAR(Mem_76_Pfls_OperationType, AUTOMATIC) OperationType,\
	P2VAR(Mem_76_Pfls_AddressType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) SrcAddress, \
    VAR(Mem_76_Pfls_AddressType, AUTOMATIC) DesAddress);
/* Function to Execute program/erase operation  */
FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_ExecuteOperation(\
    VAR(Mem_76_Pfls_OperationType, AUTOMATIC) OperationType);


#if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
#define MEM_76_PFLS_STOP_SEC_RAM_CODE
#else
#define MEM_76_PFLS_STOP_SEC_CODE
#endif
#include "MemMap.h"
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Mem_76_Pfls_CalBankAddress                          **
**                                                                            **
** Description          : This function calculate B-bank address              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : Address                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Mem_76_Pfls_AddressType                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
#define MEM_76_PFLS_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Mem_MemHwAb_14038 */
/* polyspace-begin MISRA-C3:2.7 [Justified:Low] "Not a defect" */
FUNC(Mem_76_Pfls_AddressType, MEM_76_PFLS_CODE) Mem_76_Pfls_CalBankAddress(\
  Mem_76_Pfls_InstanceIdType instanceId,
  VAR(Mem_76_Pfls_AddressType, AUTOMATIC) Address)
/* polyspace-end MISRA-C3:2.7 [Justified:Low] "Not a defect" */
{
  Mem_76_Pfls_AddressType targetAddress;
  /* @Trace: Mem_76_Pfls_SUD_FUNC_086 */ 
  targetAddress = Address;

  return targetAddress;
}

#define MEM_76_PFLS_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Mem_76_Pfls_InternalInitialize                      **
**                                                                            **
** Description          : The function aims to initialize Pflash for specific **
**                        MCU                                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : void                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
#define MEM_76_PFLS_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Mem_MemHwAb_14037 */
FUNC(void, MEM_76_PFLS_CODE) Mem_76_Pfls_InternalInitialize(void)
{
  /* @Trace: Mem_76_Pfls_SUD_FUNC_067 */
  /* Disable high voltage operation
   * MCR->EHV = 0b - Flash memory is not  able to perform a high voltage operation */
  MEM_76_PFLS_FLASH->MCR = MEM_76_PFLS_FLASH->MCR & ~MEM_76_PFLS_FLASH_MCR_EHV_MASK;
  /* wait until modify operation is done
   * MCRS->DONE = 1b - Not executing a high voltage operation */
  while(MEM_76_PFLS_FLASH_MCRS_DONE_MASK != (MEM_76_PFLS_FLASH->MCRS & MEM_76_PFLS_FLASH_MCRS_DONE_MASK)) {};
  /* terminate on-going erase operation
   * MCR->ERS = 0b - Flash memory not executing an erase operation */
  MEM_76_PFLS_FLASH->MCR = MEM_76_PFLS_FLASH->MCR & ~MEM_76_PFLS_FLASH_MCR_ERS_MASK;
  /* terminate on-going program operation
   * MCR->PGM = 0b - Flash memory not executing a program operation */
  MEM_76_PFLS_FLASH->MCR = MEM_76_PFLS_FLASH->MCR & ~MEM_76_PFLS_FLASH_MCR_PGM_MASK;
  /* clear possible EER, RWE events by writing a 1 to the bit
   * EER = 0b - Read occur normally
   * RWE = 0b - Read occur normally */
  MEM_76_PFLS_FLASH->MCRS = MEM_76_PFLS_FLASH->MCRS | MEM_76_PFLS_FLASH_MCRS_EER_MASK;
  MEM_76_PFLS_FLASH->MCRS = MEM_76_PFLS_FLASH->MCRS | MEM_76_PFLS_FLASH_MCRS_RWE_MASK;
  /* Disable UTest operation
   * UT0[UTE] = 0b - U-Test mode is not enabled */
  MEM_76_PFLS_FLASH->UT0 = MEM_76_PFLS_FLASH->UT0 & ~MEM_76_PFLS_FLASH_UT0_UTE_MASK;
  /* Disable watchdog interrupt */
  MEM_76_PFLS_FLASH->MCR = MEM_76_PFLS_FLASH->MCR & ~MEM_76_PFLS_FLASH_MCR_WDIE_MASK;
  /* Disable express watchdog interrupt */
  MEM_76_PFLS_FLASH->XMCR = MEM_76_PFLS_FLASH->XMCR & ~MEM_76_PFLS_FLASH_XMCR_XWDI_MASK;
  /* No interrupt request will be generated when the DONE flag is set */
  MEM_76_PFLS_FLASH->MCR = MEM_76_PFLS_FLASH->MCR & ~MEM_76_PFLS_FLASH_MCR_PECIE_MASK;
  /** Clear all error flags for main interface */
  MEM_76_PFLS_FLASH->MCRS &= MEM_76_PFLS_FLASH_MCRS_SBC_MASK |  \
                    MEM_76_PFLS_FLASH_MCRS_AEE_MASK |  \
                    MEM_76_PFLS_FLASH_MCRS_EEE_MASK |  \
                    MEM_76_PFLS_FLASH_MCRS_RVE_MASK |  \
                    MEM_76_PFLS_FLASH_MCRS_RRE_MASK |  \
                    MEM_76_PFLS_FLASH_MCRS_PES_MASK |  \
                    MEM_76_PFLS_FLASH_MCRS_PEP_MASK;

}
#define MEM_76_PFLS_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Mem_76_Pfls_InternalRead                            **
**                                                                            **
** Description          : This function used to read data from memory to data **
**                        buffer using Flash register                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : Address                                             **
**                        DataPtr                                             **
**                        Length                                              **
**                        BurstEnable                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Mem_76_Pfls_JobResultType                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
#if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
#define MEM_76_PFLS_START_SEC_RAM_CODE
#else
#define MEM_76_PFLS_START_SEC_CODE
#endif
#include "MemMap.h"
/* @Trace: SRS_Mem_MemHwAb_14038 */
FUNC(Mem_76_Pfls_JobResultType, MEM_76_PFLS_CODE) Mem_76_Pfls_InternalRead(\
  VAR(Mem_76_Pfls_AddressType, AUTOMATIC) Address, \
  P2VAR(Mem_76_Pfls_DataType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) DataPtr, \
  VAR(Mem_76_Pfls_LengthType, AUTOMATIC) Length, \
  CONST(uint8, MEM_76_PFLS_CONST) BurstEnable)
{
  VAR(Mem_76_Pfls_LengthType, AUTOMATIC)                        dataLength;
  P2VAR(Mem_76_Pfls_DataType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) dataPtr;
  VAR(Mem_76_Pfls_AddressType, AUTOMATIC)                       memoryAddress;
  VAR(Mem_76_Pfls_JobResultType, AUTOMATIC)                     retVal;
  /* @Trace: Mem_76_Pfls_SUD_FUNC_087 */ 
  if(NULL_PTR == DataPtr)
  {
    retVal = MEM_JOB_FAILED;
  }
  else
  {
    /* copy input */
    dataLength      = Length;
    memoryAddress   = Address;
    dataPtr         = DataPtr;

    /* Read from flash memory */
    while( MEM_76_PFLS_ZERO < dataLength )
    {
      /* get data from memory */
      /* polyspace-begin CERT-C:INT36-C, MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
       * the register value can be read via the address" */
      * dataPtr = * (Mem_76_Pfls_DataType *) memoryAddress;
      /* polyspace-end CERT-C:INT36-C, MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
       * the register value can be read via the address" */
      /* point to the next address */
      dataPtr++;
      memoryAddress++;
      /* decrease data length */
      dataLength--;
    }
    retVal  = MEM_JOB_OK;
  }

  MEM_76_PFLS_UNUSED(BurstEnable);

  return retVal;
}

#if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
#define MEM_76_PFLS_STOP_SEC_RAM_CODE
#else
#define MEM_76_PFLS_STOP_SEC_CODE
#endif
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Mem_76_Pfls_InternalErase                           **
**                                                                            **
** Description          : The function performs erase operation               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : Address                                             **
**                        DataPtr                                             **
**                        Length                                              **
**                        BurstEnable                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Mem_76_Pfls_JobResultType                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
#if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
#define MEM_76_PFLS_START_SEC_RAM_CODE
#else
#define MEM_76_PFLS_START_SEC_CODE
#endif
#include "MemMap.h"

/* polyspace-begin MISRA-C3:2.7,8.13 [Justified:Low] "Not a defect" */
/* @Trace: SRS_Mem_MemHwAb_14038 */
FUNC(Mem_76_Pfls_JobResultType, MEM_76_PFLS_CODE) Mem_76_Pfls_InternalErase(\
  VAR(Mem_76_Pfls_AddressType, AUTOMATIC) Address, \
  P2VAR(Mem_76_Pfls_DataType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) DataPtr, \
  VAR(Mem_76_Pfls_LengthType, AUTOMATIC) Length, \
  CONST(uint8, MEM_76_PFLS_CONST) BurstEnable)
/* polyspace-end MISRA-C3:2.7,8.13 [Justified:Low] "Not a defect" */
{
  VAR(uint32, AUTOMATIC)                            sectorStart;
  VAR(uint32, AUTOMATIC)                            sectorIndex;
  VAR(Mem_76_Pfls_JobResultType, AUTOMATIC)         retVal;


  /* @Trace: Mem_76_Pfls_SUD_FUNC_088 */
  MEM_76_PFLS_UNUSED(DataPtr);
  MEM_76_PFLS_UNUSED(BurstEnable);

  /* Check the pre-erase conditions  */
  if(E_OK != Mem_76_Pfls_PreEraseConditionCheck())
  {
	  /* The write operation shall be terminated if the pre-condtion check is failed */
	  retVal = MEM_JOB_FAILED;
  }
  else
  {
	  retVal = MEM_JOB_OK;
  }
   /* get virtual sector Index by address */
   sectorStart = MEM_76_PFLS_GET_SECTOR_INDEX_BY_ADDR(Address);

   /* The Erase operation can only be executed when the voltage (EHV bit) is low */
   if(retVal != MEM_JOB_FAILED)
   {
     /* clear all error lags before executing an Erase operation */
     Mem_76_Pfls_ClearAllErrorFlags();

     /* Initialize sectorIndex */
     sectorIndex = sectorStart;

     /* Unlock sector for erase operation */
     Mem_76_Pfls_SectorUnlock(sectorIndex);

     /* preparation for erase operation */
     Mem_76_Pfls_PrepareOperation(Mem_76_Pfls_Erase_Operation,NULL_PTR,
         (Mem_76_Pfls_AddressType)MEM_76_PFLS_GET_SECTOR_ADDRESS(sectorIndex));

     /* Execute the erase operation */
     if(E_OK == Mem_76_Pfls_ExecuteOperation(Mem_76_Pfls_Erase_Operation))
     {
       retVal = MEM_JOB_OK;
     }
     else
     {
       retVal = MEM_JOB_FAILED;
     }


     /* lock sector after erase operation */
     Mem_76_Pfls_Sectorlock(sectorIndex);
   }

  return retVal;
}

#if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
#define MEM_76_PFLS_STOP_SEC_RAM_CODE
#else
#define MEM_76_PFLS_STOP_SEC_CODE
#endif
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Mem_76_Pfls_InternalWrite                           **
**                                                                            **
** Description          : The function performs write operation               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : Address                                             **
**                        DataPtr                                             **
**                        Length                                              **
**                        BurstEnable                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : retVal                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/

#if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
#define MEM_76_PFLS_START_SEC_RAM_CODE
#else
#define MEM_76_PFLS_START_SEC_CODE
#endif
#include "MemMap.h"
/* @Trace: SRS_Mem_MemHwAb_14038 */
FUNC(Mem_76_Pfls_JobResultType, MEM_76_PFLS_CODE) Mem_76_Pfls_InternalWrite(\
  VAR(Mem_76_Pfls_AddressType, AUTOMATIC) Address, \
  P2CONST(Mem_76_Pfls_DataType, AUTOMATIC, MEM_76_PFLS_APPL_CONST) DataPtr, \
  VAR(Mem_76_Pfls_LengthType, AUTOMATIC) WriteNormalSize, \
  VAR(Mem_76_Pfls_LengthType, AUTOMATIC) WriteBurstSize, \
  CONST(uint8, MEM_76_PFLS_CONST) BurstEnable)
{
  VAR(Mem_76_Pfls_JobResultType, AUTOMATIC)         retVal;
  VAR(Std_ReturnType, AUTOMATIC)                    checkResult;
  VAR(uint32, AUTOMATIC)                            SectorIndex;
  VAR(Mem_76_Pfls_AddressType, AUTOMATIC)  updatedTargetAddress;
  P2VAR(Mem_76_Pfls_AddressType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) \
                                                    pdataPtr;
  /* @Trace: Mem_76_Pfls_SUD_FUNC_092 */ 
  /* unused arguments */
  MEM_76_PFLS_UNUSED(WriteNormalSize);
  MEM_76_PFLS_UNUSED(WriteBurstSize);

  /* get the argument to local variable */
  updatedTargetAddress  = Address;

  /* Fetch the data */
  /* polyspace +1 CERT-C:EXP36-C, MISRA-C3:11.5,11.8 [Justified:Low] "Cast void* to struct* is no impact" */
  pdataPtr = (Mem_76_Pfls_AddressType *)(void *)(DataPtr);

  /* Check the pre-write conditions depend write operation  */
  if (MEM_76_PFLS_FALSE == BurstEnable)
  {
    checkResult = Mem_76_Pfls_PreWriteConditionCheck(Mem_76_Pfls_Write_Operation);
  }
  else
  {
    checkResult = Mem_76_Pfls_PreWriteConditionCheck(Mem_76_Pfls_ExpressWrite_Operation);
  }

  if(E_OK != checkResult)
  {
	  /* The write operation shall be terminated if the pre-condtion check is failed */
	  retVal = MEM_JOB_FAILED;
  }
  else
  {
	  retVal = MEM_JOB_OK;
  }

  if(MEM_JOB_FAILED != retVal)
  {
     /* clear all error lags before executing a write operation */
     Mem_76_Pfls_ClearAllErrorFlags();

     /* get virtual sector Index by address */
     SectorIndex = MEM_76_PFLS_GET_SECTOR_INDEX_BY_ADDR(updatedTargetAddress);

     /* Unlock Sector or super sector for a write operation */
     Mem_76_Pfls_SectorUnlock(SectorIndex);

     if(MEM_76_PFLS_FALSE == BurstEnable)
     {
       /* prepare for a write operation */
       Mem_76_Pfls_PrepareOperation(Mem_76_Pfls_Write_Operation,pdataPtr,updatedTargetAddress);
       /* Execute the write operation */
       if(E_OK == Mem_76_Pfls_ExecuteOperation(Mem_76_Pfls_Write_Operation))
       {
          retVal = MEM_JOB_OK;
       }
       else
       {
          retVal = MEM_JOB_FAILED;
       }
     }
     else
     {
       /* prepare for a write operation */
       Mem_76_Pfls_PrepareOperation(Mem_76_Pfls_ExpressWrite_Operation,pdataPtr,updatedTargetAddress);
       /* Execute the write operation */
       if(E_OK == Mem_76_Pfls_ExecuteOperation(Mem_76_Pfls_ExpressWrite_Operation))
       {
          retVal = MEM_JOB_OK;
       }
       else
       {
          retVal = MEM_JOB_FAILED;
       }
     }
     /* Lock sector or super sector after a write operation */
     Mem_76_Pfls_Sectorlock(SectorIndex);
  }

  return retVal;
}
#if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
#define MEM_76_PFLS_STOP_SEC_RAM_CODE
#else
#define MEM_76_PFLS_STOP_SEC_CODE
#endif
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Mem_76_Pfls_PrepareOperation                        **
**                                                                            **
** Description          : This function Execute Erase/Program operation       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : OperationType                                       **
**                        SrcAddress                                          **
**                        DesAddress                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
#if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
#define MEM_76_PFLS_START_SEC_RAM_CODE
#else
#define MEM_76_PFLS_START_SEC_CODE
#endif
#include "MemMap.h"
/* @Trace: SRS_Mem_MemHwAb_14038 */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "Not a defect" */
FUNC(void, MEM_76_PFLS_CODE) Mem_76_Pfls_PrepareOperation(\
    VAR(Mem_76_Pfls_OperationType, AUTOMATIC) OperationType,\
	P2VAR(Mem_76_Pfls_AddressType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) SrcAddress, \
    VAR(Mem_76_Pfls_AddressType, AUTOMATIC) DesAddress)
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "Not a defect" */
{
  VAR(uint32, AUTOMATIC) count;
  VAR(uint32, AUTOMATIC) locationOfDataWriteRegs;
  /* @Trace: Mem_76_Pfls_SUD_FUNC_081 */
  if(Mem_76_Pfls_Erase_Operation == OperationType)
  {
      /* Write to the sector of block address to be erased using logical address registers located in the PFC */
      MEM_76_PFLS_PFLASH->PFCPGM_PEADR_L = (Mem_76_Pfls_AddressType)DesAddress;
      /* Write a default value to DATA register - this is referred as an interlock write */
      MEM_76_PFLS_FLASH->DATA[MEM_76_PFLS_ZERO] = 0xFFFFFFFFu;

      /* unused argument */
      MEM_76_PFLS_UNUSED(SrcAddress);
  }
  else if(Mem_76_Pfls_Write_Operation == OperationType)
  {
	  locationOfDataWriteRegs = (DesAddress & (MEM_76_PFLS_DATA_SIZE_BYTES_U32 - MEM_76_PFLS_ONE)) >> MEM_76_PFLS_TWO;
      /* Write the address to be programmed using logical address located in the PFC */
      MEM_76_PFLS_PFLASH->PFCPGM_PEADR_L = (Mem_76_Pfls_AddressType)DesAddress;
      /* data programmed must be written in the appropriate DATAX register
       * - doubleword is written in a write operation */
      /* polyspace-begin MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation" */
      MEM_76_PFLS_FLASH->DATA[locationOfDataWriteRegs+ MEM_76_PFLS_ZERO] = SrcAddress[MEM_76_PFLS_ZERO];

      MEM_76_PFLS_FLASH->DATA[locationOfDataWriteRegs + MEM_76_PFLS_ONE] = SrcAddress[MEM_76_PFLS_ONE];
      /* polyspace-end MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation" */
  }
  else
  {
      /* Write the address to be express programmed using logical address located in the PFC */
      MEM_76_PFLS_PFLASH->PFCPGM_XPEADR_L = (Mem_76_Pfls_AddressType)DesAddress;
      /* wait until XMCR[XDOK] goes high
       * XMCR[XDOK] = 1b - Express write OK - write to DATA register allowed  */
      while(MEM_76_PFLS_FLASH_XMCR_XDOK_MASK != (MEM_76_PFLS_FLASH->XMCR & MEM_76_PFLS_FLASH_XMCR_XDOK_MASK)){};
      /* write DATA register with the data desired to be programmed. Up to 128 bytes (32 words) may be programmed with express program */
      for(count = MEM_76_PFLS_ZERO;count < MEM_76_PFLS_THIRTYTWO;count++)
      {
          MEM_76_PFLS_FLASH->DATA[count] = SrcAddress[count];
      }

  }
}

#if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
#define MEM_76_PFLS_STOP_SEC_RAM_CODE
#else
#define MEM_76_PFLS_STOP_SEC_CODE
#endif
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Mem_76_Pfls_ExecuteOperation                        **
**                                                                            **
** Description          : This function Execute Erase/Program operation       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : OperationType                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : retVal                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
#if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
#define MEM_76_PFLS_START_SEC_RAM_CODE
#else
#define MEM_76_PFLS_START_SEC_CODE
#endif
#include "MemMap.h"
/* @Trace: SRS_Mem_MemHwAb_14038 */
FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_ExecuteOperation(\
    VAR(Mem_76_Pfls_OperationType, AUTOMATIC) OperationType)
{
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  /* @Trace: Mem_76_Pfls_SUD_FUNC_082 */
  if(Mem_76_Pfls_Erase_Operation == OperationType)
  {
     /* Change the value of MCR[ERS] from a 0 to a 1
     - MCR[ERS] = 1b - Flash memory executing an erase sequence */
     MEM_76_PFLS_FLASH->MCR =  MEM_76_PFLS_FLASH->MCR | MEM_76_PFLS_FLASH_MCR_ERS_MASK;

     /* Select the size of erase using MCR[ESS]
     - MCR[ESS] = 0b - Flash memory erase is on a sector */
     MEM_76_PFLS_FLASH->MCR =  MEM_76_PFLS_FLASH->MCR & ~MEM_76_PFLS_FLASH_MCR_ESS_MASK;

      /* write a 1 to MCR[EHV] to start the internal erase operation
     - MCR[EHV] = 1b - Flash memory is enabled to perform a high voltage operation */
     MEM_76_PFLS_FLASH->MCR = MEM_76_PFLS_FLASH->MCR | MEM_76_PFLS_FLASH_MCR_EHV_MASK;

     /* wait until MCRS[DONE] becomes 1 - state machine status
     - MCRS[DONE] = 1b - not executing a high voltage operation */
     while(MEM_76_PFLS_FLASH_MCRS_DONE_MASK != (MEM_76_PFLS_FLASH->MCRS & MEM_76_PFLS_FLASH_MCRS_DONE_MASK))
     {
        /* Watchdog trigger */    
        #if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
        #if (MEM_76_PFLS_WDG_CALLOUT_FUNCTION_SUPPORT == STD_ON)     

        Mem_76_Pfls_WDTriggerFct();

        #endif /* MEM_76_PFLS_WDG_CALLOUT_FUNCTION_SUPPORT == STD_ON */
        #endif
     };

     /* Confirm MCRS[PEG] = 1b - Program or erase operation successful */
     if(MEM_76_PFLS_FLASH_MCRS_PEG_MASK == (MEM_76_PFLS_FLASH->MCRS & MEM_76_PFLS_FLASH_MCRS_PEG_MASK))
     {
       /* disable high voltage bit by writing 0 to MCR[EHV] */
    	 MEM_76_PFLS_FLASH->MCR = MEM_76_PFLS_FLASH->MCR & ~MEM_76_PFLS_FLASH_MCR_EHV_MASK;
       /* writing 0 to MCR[ERS] to terminate the erase */
    	 MEM_76_PFLS_FLASH->MCR = MEM_76_PFLS_FLASH->MCR & ~MEM_76_PFLS_FLASH_MCR_ERS_MASK;
       /* return E_OK */
       retVal = E_OK;
     }
     else
     {
       /* disable high voltage bit by writing 0 to MCR[EHV] */
       MEM_76_PFLS_FLASH->MCR = MEM_76_PFLS_FLASH->MCR & ~MEM_76_PFLS_FLASH_MCR_EHV_MASK;
       /* writing 0 to MCR[ERS] to terminate the erase */
       MEM_76_PFLS_FLASH->MCR = MEM_76_PFLS_FLASH->MCR & ~MEM_76_PFLS_FLASH_MCR_ERS_MASK;
       /* return E_OK */
       retVal = E_NOT_OK;
     }
  }
  else if(Mem_76_Pfls_Write_Operation == OperationType)
  {
    /* Change the value of MCR[PGM] from a 0 to a 1
    - MCR[PGM] = 1b - Flash memory executing a program sequence */
	  MEM_76_PFLS_FLASH->MCR =  MEM_76_PFLS_FLASH->MCR | MEM_76_PFLS_FLASH_MCR_PGM_MASK;

     /* write a 1 to MCR[EHV] to start the internal write operation
     - MCR[EHV] = 1b - Flash memory is enabled to perform a high voltage operation */
	  MEM_76_PFLS_FLASH->MCR = MEM_76_PFLS_FLASH->MCR | MEM_76_PFLS_FLASH_MCR_EHV_MASK;

      /* wait until MCRS[DONE] becomes 1 - state machine status
      - MCRS[DONE] = 1b - not executing a high voltage operation */
      while(MEM_76_PFLS_FLASH_MCRS_DONE_MASK != (MEM_76_PFLS_FLASH->MCRS & MEM_76_PFLS_FLASH_MCRS_DONE_MASK))
      {
        /* Watchdog trigger */    
        #if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
        #if (MEM_76_PFLS_WDG_CALLOUT_FUNCTION_SUPPORT == STD_ON)     

        Mem_76_Pfls_WDTriggerFct();

        #endif /* MEM_76_PFLS_WDG_CALLOUT_FUNCTION_SUPPORT == STD_ON */
        #endif
      };

      /* Confirm MCRS[PEG] = 1b - Program or erase operation successful */
      if(MEM_76_PFLS_FLASH_MCRS_PEG_MASK == (MEM_76_PFLS_FLASH->MCRS & MEM_76_PFLS_FLASH_MCRS_PEG_MASK))
      {
        /* disable high voltage bit by writing 0 to MCR[EHV] */
        MEM_76_PFLS_FLASH->MCR = MEM_76_PFLS_FLASH->MCR & ~MEM_76_PFLS_FLASH_MCR_EHV_MASK;
        /* writing 0 to MCR[PGM] to  terminate the program operation */
        MEM_76_PFLS_FLASH->MCR = MEM_76_PFLS_FLASH->MCR & ~MEM_76_PFLS_FLASH_MCR_PGM_MASK;
        /* return E_OK */
        retVal = E_OK;
      }
      else
      {
        /* disable high voltage bit by writing 0 to MCR[EHV] */
    	MEM_76_PFLS_FLASH->MCR = MEM_76_PFLS_FLASH->MCR & ~MEM_76_PFLS_FLASH_MCR_EHV_MASK;
        /* writing 0 to MCR[PGM] to  terminate the program operation */
    	MEM_76_PFLS_FLASH->MCR = MEM_76_PFLS_FLASH->MCR & ~MEM_76_PFLS_FLASH_MCR_PGM_MASK;
        /* return E_OK */
        retVal = E_NOT_OK;
      }
  }
  else
  {
    /* Change the value in XMCR[XPGM] from 0 to 1
     * XMCR[XPGM] = 1b - Flash memory executing an express programming sequence */
     MEM_76_PFLS_FLASH->XMCR = MEM_76_PFLS_FLASH->XMCR | MEM_76_PFLS_FLASH_XMCR_XPGM_MASK;
    /* Write a 1 to XMCR[XEHV] to start internal express program sequence */
    MEM_76_PFLS_FLASH->XMCR = MEM_76_PFLS_FLASH->XMCR | MEM_76_PFLS_FLASH_XMCR_XEHV_MASK;
    /* wait until XMCR[XDONE] become 1
     * XMCR[XDONE] = 1b - Not executing an express program sequence */
    while(MEM_76_PFLS_FLASH_XMCR_XDONE_MASK != (MEM_76_PFLS_FLASH->XMCR & MEM_76_PFLS_FLASH_XMCR_XDONE_MASK))
    {
        /* Watchdog trigger */    
        #if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
        #if (MEM_76_PFLS_WDG_CALLOUT_FUNCTION_SUPPORT == STD_ON)     

        Mem_76_Pfls_WDTriggerFct();

        #endif /* MEM_76_PFLS_WDG_CALLOUT_FUNCTION_SUPPORT == STD_ON */
        #endif
    };
    /* confirm XMCR[XPEG] = 1
     *  XMCR[XPEG] = 1b - program operation successful */
    if(MEM_76_PFLS_FLASH_XMCR_XPEG_MASK == (MEM_76_PFLS_FLASH->XMCR & MEM_76_PFLS_FLASH_XMCR_XPEG_MASK))
    {
        /* Write 0 to XMCR[XEHV]*/
        MEM_76_PFLS_FLASH->XMCR = MEM_76_PFLS_FLASH->XMCR & ~MEM_76_PFLS_FLASH_XMCR_XEHV_MASK;
        /* Write 0 to XMCR[XPGM] to terminate express program sequence */
        MEM_76_PFLS_FLASH->XMCR = MEM_76_PFLS_FLASH->XMCR & ~MEM_76_PFLS_FLASH_XMCR_XPGM_MASK;
        /* return E_OK */
        retVal = E_OK;
     }
     else
     {
        /* Write 0 to XMCR[XEHV]*/
        MEM_76_PFLS_FLASH->XMCR = MEM_76_PFLS_FLASH->XMCR & ~MEM_76_PFLS_FLASH_XMCR_XEHV_MASK;
        /* Write 0 to XMCR[XPGM] to terminate express program sequence */
        MEM_76_PFLS_FLASH->XMCR = MEM_76_PFLS_FLASH->XMCR & ~MEM_76_PFLS_FLASH_XMCR_XPGM_MASK;
        /* return E_NOT_OK */
        retVal = E_NOT_OK;
     }
  }
  return retVal;
}


#if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
#define MEM_76_PFLS_STOP_SEC_RAM_CODE
#else
#define MEM_76_PFLS_STOP_SEC_CODE
#endif
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Mem_76_Pfls_PreWriteConditionCheck                  **
**                                                                            **
** Description          : Check conditions before a Write operation           **
**                       is executed                                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : sectorIndex                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
#if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
#define MEM_76_PFLS_START_SEC_RAM_CODE
#else
#define MEM_76_PFLS_START_SEC_CODE
#endif
#include "MemMap.h"
FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_PreWriteConditionCheck
(
  VAR(Mem_76_Pfls_OperationType, AUTOMATIC) OperationType
)
{
  VAR(Std_ReturnType,AUTOMATIC) retVal;
  /* Initalize retVal as E_OK */
  retVal = E_OK;
  if (Mem_76_Pfls_Write_Operation == OperationType)
  {
    /* check whether the voltage status is high*/
    if(MEM_76_PFLS_FLASH_MCR_EHV_MASK == (MEM_76_PFLS_FLASH->MCR & MEM_76_PFLS_FLASH_MCR_EHV_MASK))
    {
    /* The job fails if the voltage status is high */
      retVal = E_NOT_OK;
    }
    /* Check whether any on-going program operation is in progress   */
    if(MEM_76_PFLS_FLASH_MCR_PGM_MASK == (MEM_76_PFLS_FLASH->MCR & MEM_76_PFLS_FLASH_MCR_PGM_MASK))
    {
    /* The job fails if the voltage status is high */
      retVal = E_NOT_OK;
    }
    /* check whether UTest has been disabled */
    if(MEM_76_PFLS_FLASH_UT0_UTE_MASK == (MEM_76_PFLS_FLASH->UT0 & MEM_76_PFLS_FLASH_UT0_UTE_MASK))
    {
    /* The job fails if the voltage status is high */
      retVal = E_NOT_OK;
    }
  }
  else
  {
    /* check whether the voltage status is high*/
    if(MEM_76_PFLS_FLASH_XMCR_XEHV_MASK == (MEM_76_PFLS_FLASH->XMCR & MEM_76_PFLS_FLASH_XMCR_XEHV_MASK))
    {
    /* The job fails if the voltage status is high */
      retVal = E_NOT_OK;
    }
    /* Check whether any on-going program operation is in progress   */
    if(MEM_76_PFLS_FLASH_XMCR_XPGM_MASK == (MEM_76_PFLS_FLASH->XMCR & MEM_76_PFLS_FLASH_XMCR_XPGM_MASK))
    {
    /* The job fails if any on-going program operation is in-process */
      retVal = E_NOT_OK;
    }
    /* check whether UTest has been disabled */
    if(MEM_76_PFLS_FLASH_UT0_UTE_MASK == (MEM_76_PFLS_FLASH->UT0 & MEM_76_PFLS_FLASH_UT0_UTE_MASK))
    {
    /* The job fails if the voltage status is high */
      retVal = E_NOT_OK;
    }
  }
  return retVal;
}
#if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
#define MEM_76_PFLS_STOP_SEC_RAM_CODE
#else
#define MEM_76_PFLS_STOP_SEC_CODE
#endif
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Mem_76_Pfls_PreEraseConditionCheck                  **
**                                                                            **
** Description          : Check conditions before an Erase operation          **
**                       is executed                                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
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
*******************************************************************************/
#if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
#define MEM_76_PFLS_START_SEC_RAM_CODE
#else
#define MEM_76_PFLS_START_SEC_CODE
#endif
#include "MemMap.h"
/* @Trace: SRS_Mem_MemHwAb_14038 */
FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_PreEraseConditionCheck(void)
{
  VAR(Std_ReturnType,AUTOMATIC) retVal;
  /* @Trace: Mem_76_Pfls_SUD_FUNC_090 */
  /* Initalize retVal as E_OK */
  retVal = E_OK;
  /* check whether the voltage status is high*/
  if(MEM_76_PFLS_FLASH_MCR_EHV_MASK == (MEM_76_PFLS_FLASH->MCR & MEM_76_PFLS_FLASH_MCR_EHV_MASK))
  {
     /* The job fails if the voltage status is high */
	  retVal = E_NOT_OK;
  }
  /* Check whether any on-going program operation is in progress   */
  if(MEM_76_PFLS_FLASH_MCR_ERS_MASK == (MEM_76_PFLS_FLASH->MCR & MEM_76_PFLS_FLASH_MCR_ERS_MASK))
  {
     /* The job fails if the voltage status is high */
	  retVal = E_NOT_OK;
  }
   /* check whether UTest has been disabled */
  if(MEM_76_PFLS_FLASH_UT0_UTE_MASK == (MEM_76_PFLS_FLASH->UT0 & MEM_76_PFLS_FLASH_UT0_UTE_MASK))
  {
     /* The job fails if the voltage status is high */
	  retVal = E_NOT_OK;
  }

  return retVal;
}
#if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
#define MEM_76_PFLS_STOP_SEC_RAM_CODE
#else
#define MEM_76_PFLS_STOP_SEC_CODE
#endif
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Mem_76_Pfls_ClearAllErrorFlags                      **
**                                                                            **
** Description          : clear all error flags of embedded flash             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
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
*******************************************************************************/
#if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
#define MEM_76_PFLS_START_SEC_RAM_CODE
#else
#define MEM_76_PFLS_START_SEC_CODE
#endif
#include "MemMap.h"
/* @Trace: SRS_Mem_MemHwAb_14038 */
FUNC(void, MEM_76_PFLS_CODE) Mem_76_Pfls_ClearAllErrorFlags(void)
{
  /* @Trace: Mem_76_Pfls_SUD_FUNC_091 */
    /** Clear all error flags for main interface */
    MEM_76_PFLS_FLASH->MCRS &= MEM_76_PFLS_FLASH_MCRS_EER_MASK |  \
                               MEM_76_PFLS_FLASH_MCRS_SBC_MASK |  \
                               MEM_76_PFLS_FLASH_MCRS_AEE_MASK |  \
                               MEM_76_PFLS_FLASH_MCRS_EEE_MASK |  \
                               MEM_76_PFLS_FLASH_MCRS_RVE_MASK |  \
                               MEM_76_PFLS_FLASH_MCRS_RRE_MASK |  \
                               MEM_76_PFLS_FLASH_MCRS_RWE_MASK |  \
                               MEM_76_PFLS_FLASH_MCRS_PES_MASK |  \
                               MEM_76_PFLS_FLASH_MCRS_PEP_MASK;
}
#if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
#define MEM_76_PFLS_STOP_SEC_RAM_CODE
#else
#define MEM_76_PFLS_STOP_SEC_CODE
#endif
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Mem_76_Pfls_SectorUnlock                            **
**                                                                            **
** Description          : Unlock sector/super sector for Program and Erase    **
**                        Operation                                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : sectorIndex                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
#if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
#define MEM_76_PFLS_START_SEC_RAM_CODE
#else
#define MEM_76_PFLS_START_SEC_CODE
#endif
#include "MemMap.h"
/* @Trace: SRS_Mem_MemHwAb_14038 */
FUNC(void, MEM_76_PFLS_CODE) Mem_76_Pfls_SectorUnlock(\
    VAR(uint32, AUTOMATIC) sectorIndex)
{
  VAR(uint32, AUTOMATIC) sectorIndexPerBlock;
  VAR(uint32, AUTOMATIC) blockIndex;
  VAR(uint32, AUTOMATIC) bitPosition;
  VAR(Mem_76_Pfls_AddressType,AUTOMATIC) Address;
  VAR(uint32,AUTOMATIC) icount;
  /* @Trace: Mem_76_Pfls_SUD_FUNC_080 */
  /* get the start address of the sector */
  Address = (Mem_76_Pfls_AddressType)MEM_76_PFLS_GET_SECTOR_ADDRESS(sectorIndex);

  /* get Block Index by address */
  for(icount = MEM_76_PFLS_ZERO;icount < MEM_76_PFLS_BLOCK_COUNT;icount++)
  {
     if((Address >= Mem_76_Pfls_BlockInfor[icount].BlockStartAddress)&&
         (Address < Mem_76_Pfls_BlockInfor[icount].BlockEndAddress))
     {
    	 blockIndex = icount;
     }
  }

  /* get sector index within a Code Flash Block */
  sectorIndexPerBlock = (Address - Mem_76_Pfls_BlockInfor[blockIndex].BlockStartAddress)/MEM_76_PFLS_SECTOR_SIZE;

  /* determine whether the sector belong to area or super sector address of the block */
  if(sectorIndexPerBlock >= Mem_76_Pfls_BlockInfor[blockIndex].numOfSectorInSuperSectorArea)
  {
    /* the sector belong to the sector area of the block */
    /* get the bit position of sector within register */
    bitPosition =  sectorIndexPerBlock - Mem_76_Pfls_BlockInfor[blockIndex].numOfSectorInSuperSectorArea;
    /* Unlock the set sector lock register */
    MEM_76_PFLS_PFLASH->PFCBLK_SETSLOCK[blockIndex] &= ~(uint32)((uint32)1 << bitPosition);

    /* Unlock the sector lock register */
    MEM_76_PFLS_PFLASH->PFCBLK_SPELOCK[blockIndex] &= ~(uint32)((uint32)1 << bitPosition);
  }
  else
  {
    /* the sector belong to the super sector area of the block
    - 1 super sector 64KB = 8 sector 8KB */
    bitPosition =  (sectorIndexPerBlock)/(MEM_76_PFLS_SUPER_SECTOR_SIZE/MEM_76_PFLS_SECTOR_SIZE);

    /* Unlock the set super sector lock register */
    MEM_76_PFLS_PFLASH->PFCBLK_SSETSLOCK[blockIndex] &= ~(uint32)((uint32)1 << bitPosition);

    /* Unlock the super sector lock register */
    MEM_76_PFLS_PFLASH->PFCBLK_SSPELOCK[blockIndex] &= ~(uint32)((uint32)1 << bitPosition);


  }
}
#if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
#define MEM_76_PFLS_STOP_SEC_RAM_CODE
#else
#define MEM_76_PFLS_STOP_SEC_CODE
#endif
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Mem_76_Pfls_Sectorlock                              **
**                                                                            **
** Description          : lock sector/super sector after Program and Erase    **
**                        Operation                                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : sectorIndex                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
#if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
#define MEM_76_PFLS_START_SEC_RAM_CODE
#else
#define MEM_76_PFLS_START_SEC_CODE
#endif
#include "MemMap.h"
/* @Trace: SRS_Mem_MemHwAb_14038 */
FUNC(void, MEM_76_PFLS_CODE) Mem_76_Pfls_Sectorlock(\
    VAR(uint32, AUTOMATIC) sectorIndex)
{
  VAR(uint32, AUTOMATIC) sectorIndexPerBlock;
  VAR(uint32, AUTOMATIC) blockIndex;
  VAR(uint32, AUTOMATIC) bitPosition;
  VAR(Mem_76_Pfls_AddressType,AUTOMATIC) Address;
  VAR(uint32,AUTOMATIC) icount;
  /* @Trace: Mem_76_Pfls_SUD_FUNC_083 */
  /* get the start address of the sector */
  Address = (Mem_76_Pfls_AddressType)MEM_76_PFLS_GET_SECTOR_ADDRESS(sectorIndex);

  /* get Block Index by address */
  for(icount = MEM_76_PFLS_ZERO;icount < MEM_76_PFLS_BLOCK_COUNT;icount++)
  {
     if((Address >= Mem_76_Pfls_BlockInfor[icount].BlockStartAddress)&&
         (Address < Mem_76_Pfls_BlockInfor[icount].BlockEndAddress))
     {
    	 blockIndex = icount;
     }
  }

  /* get sector index within a Code Flash Block */
  sectorIndexPerBlock = (Address - Mem_76_Pfls_BlockInfor[blockIndex].BlockStartAddress)/MEM_76_PFLS_SECTOR_SIZE;

  /* determine whether the sector belong to area or super sector address of the block */
  if(sectorIndexPerBlock >= Mem_76_Pfls_BlockInfor[blockIndex].numOfSectorInSuperSectorArea)
  {
    /* the sector belong to the sector area of the block */
    /* get the bit position of sector within register */
    bitPosition =  sectorIndexPerBlock- Mem_76_Pfls_BlockInfor[blockIndex].numOfSectorInSectorArea;
	
    /* polyspace-begin CERT-C:INT34-C, MISRA-C3:12.2 [Justified:Low] "No Impact of this rule violation"
     * sectorIndexPerBlock < 128, numOfSectorInSuperSectorArea < 96, bitPosition value 0..31. */
    /* lock the sector lock register */
    MEM_76_PFLS_PFLASH->PFCBLK_SPELOCK[blockIndex] = MEM_76_PFLS_PFLASH->PFCBLK_SPELOCK[blockIndex] | ((uint32)1 << bitPosition);

    /* lock the set sector lock register */
    MEM_76_PFLS_PFLASH->PFCBLK_SETSLOCK[blockIndex] = MEM_76_PFLS_PFLASH->PFCBLK_SETSLOCK[blockIndex] | ((uint32)1 << bitPosition);
    /* polyspace-end CERT-C:INT34-C, MISRA-C3:12.2 [Justified:Low] "No Impact of this rule violation"
     * sectorIndexPerBlock < 128, numOfSectorInSuperSectorArea < 96, bitPosition value 0..31. */


  }
  else
  {
    /* the sector belong to the super sector area of the block
    - 1 super sector 64KB= 8 sector 8KB */
    bitPosition =  (sectorIndexPerBlock)/(MEM_76_PFLS_SUPER_SECTOR_SIZE/MEM_76_PFLS_SECTOR_SIZE);

    /* lock the super sector lock register */
    MEM_76_PFLS_PFLASH->PFCBLK_SSPELOCK[blockIndex] = MEM_76_PFLS_PFLASH->PFCBLK_SSPELOCK[blockIndex] | ((uint32)1 << bitPosition);

    /* lock the set super sector lock register */
    MEM_76_PFLS_PFLASH->PFCBLK_SSETSLOCK[blockIndex] = MEM_76_PFLS_PFLASH->PFCBLK_SSETSLOCK[blockIndex] |((uint32)1 << bitPosition);



  }
}
#if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
#define MEM_76_PFLS_STOP_SEC_RAM_CODE
#else
#define MEM_76_PFLS_STOP_SEC_CODE
#endif
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Mem_76_Pfls_ToolBox_InternalActive                  **
**                                                                            **
** Description          : Function to Copy flash driver from ROM to RAM       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
#if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
#define MEM_76_PFLS_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Mem_MemHwAb_14038 SRS_Mem_MemHwAb_14039 SRS_Mem_MemHwAb_14056 */
/* Function to Copy Flash driver from ROM to RAM  */
FUNC(void, MEM_76_PFLS_CODE) Mem_76_Pfls_ToolBox_InternalActive(void)
{
  P2VAR(Mem_76_Pfls_AddressType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) DestAddr;
  P2VAR(Mem_76_Pfls_AddressType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) SrcAddr;
  VAR(uint32,AUTOMATIC) CopySize;
  VAR(uint32,AUTOMATIC) count;
  /* @Trace: Mem_76_Pfls_SUD_FUNC_103 */
  /* polyspace-begin MISRA-C3:11.8 [Justified:Low]"Not a defect. Type cast for memcpy is safe" */
  /* get the start address of Flash driver Part that will be copied to RAM */
  SrcAddr = (Mem_76_Pfls_AddressType *)&__Mem_76_Pfls_RomStart;

  /* get the end address of Flash driver Part that will be copied to RAM */
  DestAddr = (Mem_76_Pfls_AddressType *)&__Mem_76_Pfls_RamCode;
  /* polyspace-end MISRA-C3:11.8 [Justified:Low]"Not a defect. Type cast for memcpy is safe" */

  /* Size of Flash driver part which will be copied to RAM */
  /* polyspace-begin MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
   * the register value can be read via the address" */
  CopySize = (uint32)&__Mem_76_Pfls_RomSize;
  /* polyspace-end MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
   * the register value can be read via the address" */

  /* polyspace-begin CERT-C:INT36-C, MISRA-C3:11.1,11.4 [Justified:Low] "Copy a Part of Flash driver from ROM to RAM" */
  for (count = MEM_76_PFLS_ZERO;count < CopySize;count++)
  {
      DestAddr[count] = SrcAddr[count];
  }
  /* polyspace-end CERT-C:INT36-C, MISRA-C3:11.1,11.4 [Justified:Low] "Copy a Part of Flash driver from ROM to RAM" */
  Mem_76_Pfls_InternalReadRamFunction  = &Mem_76_Pfls_InternalRead;
  Mem_76_Pfls_InternalWriteRamFunction = &Mem_76_Pfls_InternalWrite;
  Mem_76_Pfls_InternalEraseRamFunction = &Mem_76_Pfls_InternalErase;

  #if (MEM_76_PFLS_WDG_CALLOUT_FUNCTION_SUPPORT == STD_ON)
  Mem_76_Pfls_WDTriggerFct             = MEM_76_PFLS_WDG_TRIGGER_CALLOUT_FUNCTION;
  #endif
}
#define MEM_76_PFLS_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name        : Mem_76_Pfls_ActiveBankCheck                         **
**                                                                            **
** Description          : This function used to check active bank from pfls   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : instanceId                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : dataPtr                                             **
**                        lengthPtr                                           **
**                                                                            **
** Return parameter     : uint8                                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Mem_MemHwAb_14038 SRS_Mem_MemHwAb_14039 SRS_Mem_MemHwAb_14056 */
#define MEM_76_PFLS_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_ActiveBankCheck(\
  P2VAR(Mem_76_Pfls_DataType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) dataPtr, \
  P2VAR(Mem_76_Pfls_LengthType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) lengthPtr)
{
  /* @Trace: Mem_76_Pfls_SUD_DATATYPE_009  */
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  /* @Trace: Mem_76_Pfls_SUD_FUNC_077 */ 
  retVal = E_OK;
  
  /* polyspace-begin CERT-C:INT36-C, MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
   * the register value can be read via the address" */
  if ((((*((uint32*)Mem_76_Pfls_Reg_DcmStat)) >> MEM_76_PFLS_PFLASH_DCMSTAT_DCMOTAR_SHIFT) &
    MEM_76_PFLS_PFLASH_DCMSTAT_DCMOTAR_MASK)==MEM_76_PFLS_PFLASH_DCMSTAT_DCMOTAR_MASK)
  {
    *dataPtr=(Mem_76_Pfls_DataType)MEM_76_PFLS_ALT_BLOCK;
  }
  else
  {
    *dataPtr=(Mem_76_Pfls_DataType)MEM_76_PFLS_STD_BLOCK;
  }
  /* polyspace-end CERT-C:INT36-C, MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
   * the register value can be read via the address" */
  *lengthPtr = MEM_76_PFLS_ONE;

  return retVal;
}
#define MEM_76_PFLS_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Mem_76_Pfls_DirectAddressAccess                     **
**                                                                            **
** Description          : This function used to access direct address         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : dataPtr                                             **
**                        lengthPtr                                           **
**                                                                            **
** Return parameter     : uint8                                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
#define MEM_76_PFLS_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Mem_MemHwAb_14038 SRS_Mem_MemHwAb_14039 SRS_Mem_MemHwAb_14056 */
FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_DirectAddressAccess(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) instanceId, \
  P2VAR(Mem_76_Pfls_DataType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) dataPtr, \
  P2VAR(Mem_76_Pfls_LengthType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) lengthPtr)
{
  /* @Trace: Mem_76_Pfls_SUD_DATATYPE_009  */
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  P2VAR(Mem_76_Pfls_InstanceInfoType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) instanceInforPtr;
  /* @Trace: Mem_76_Pfls_SUD_FUNC_110 */
  retVal = E_OK;

  instanceInforPtr  = &Mem_76_Pfls_InstanceInfo[instanceId];

  instanceInforPtr->AltAddressAccess = FALSE;

  *dataPtr=(Mem_76_Pfls_DataType)instanceInforPtr->AltAddressAccess;
  *lengthPtr=sizeof(boolean);

  return retVal;
}
#define MEM_76_PFLS_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Mem_76_Pfls_AltAddressAccess                        **
**                                                                            **
** Description          : This function used to access alt address            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : dataPtr                                             **
**                        lengthPtr                                           **
**                                                                            **
** Return parameter     : uint8                                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Mem_MemHwAb_14038 SRS_Mem_MemHwAb_14039 SRS_Mem_MemHwAb_14056 */
#define MEM_76_PFLS_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_AltAddressAccess(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) instanceId, \
  P2VAR(Mem_76_Pfls_DataType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) dataPtr, \
  P2VAR(Mem_76_Pfls_LengthType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) lengthPtr)
{
  /* @Trace: Mem_76_Pfls_SUD_DATATYPE_009  */
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  P2VAR(Mem_76_Pfls_InstanceInfoType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) instanceInforPtr;
  /* @Trace: Mem_76_Pfls_SUD_FUNC_111 */
  retVal = E_OK;

  instanceInforPtr  = &Mem_76_Pfls_InstanceInfo[instanceId];

  instanceInforPtr->AltAddressAccess = TRUE;

  *dataPtr=(Mem_76_Pfls_DataType)instanceInforPtr->AltAddressAccess;
  *lengthPtr=sizeof(boolean);

  return retVal;
}
#define MEM_76_PFLS_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Mem_76_Pfls_Swap_HSENotification                    **
**                                                                            **
** Description          : This function used to notify result of Swap request **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : instanceId                                          **
**                                                                            **
** InOut parameter      : None	                                              **
**                                                                            **
** Output Parameters    : dataPtr                                             **
**                        lengthPtr                                           **
**                                                                            **
** Return parameter     : uint8                                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
#define MEM_76_PFLS_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Mem_MemHwAb_14038 SRS_Mem_MemHwAb_14039 SRS_Mem_MemHwAb_14056 */
/* polyspace-begin MISRA-C3:2.7,8.13 [Justified:Low] "Not a defect" */
static FUNC(void, MEM_76_PFLS_CODE)Mem_76_Pfls_Swap_HSENotification(uint8 u8MuInstance, uint8 u8MuChannel, hseSrvResponse_t HseResponse, void* pCallbackParam)
/* polyspace-end MISRA-C3:2.7,8.13 [Justified:Low] "Not a defect" */
{
  /* @Trace: Mem_76_Pfls_SUD_FUNC_085 */
  Mem_76_Pfls_HseSrvResponse=HseResponse;
}

#define MEM_76_PFLS_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Mem_76_Pfls_SwapActive                              **
**                                                                            **
** Description          : This function used to request SwapActive to HSE     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : instanceId                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : dataPtr                                             **
**                        lengthPtr                                           **
**                                                                            **
** Return parameter     : uint8                                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
#define MEM_76_PFLS_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Mem_MemHwAb_14038 SRS_Mem_MemHwAb_14039 SRS_Mem_MemHwAb_14056 */
/* polyspace-begin MISRA-C3:2.7,8.13 [Justified:Low] "Not a defect" */
FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_SwapActive(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) instanceId, \
  P2VAR(Mem_76_Pfls_DataType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) dataPtr, \
  P2VAR(Mem_76_Pfls_LengthType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) lengthPtr)
/* polyspace-end MISRA-C3:2.7,8.13 [Justified:Low] "Not a defect" */
{
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  hseSrvResponse_t hseRequestResult;
  /* @Trace: Mem_76_Pfls_SUD_FUNC_112 */
  retVal = E_NOT_OK;

  /* Fill the descriptor for the HSE request */
  Mem_76_Pfls_HseSrvDescriptor.srvId  = HSE_SRV_ID_ACTIVATE_PASSIVE_BLOCK;

  /* Build the request to be sent to Hse Ip layer */
#if 0	/* Sync */
  Mem_76_Pfls_HseIpRequest.eReqType   = HSE_IP_REQTYPE_SYNC;
  Mem_76_Pfls_HseIpRequest.u32Timeout = TIMEOUT_US_U32; //for HSE_IP_REQTYPE_SYNC
#else	/* Async(IRQ or Polling) */
  Mem_76_Pfls_HseIpRequest.eReqType   = HSE_IP_REQTYPE_ASYNC_POLL;
  Mem_76_Pfls_HseIpRequest.pfCallback = Mem_76_Pfls_Swap_HSENotification;
#endif

  Mem_76_Pfls_HseSrvResponse = HSE_PENDING;

  hseRequestResult = Hse_Ip_ServiceRequest(MU0_INSTANCE_U8, MU_ADMIN_CHANNEL_U8, &Mem_76_Pfls_HseIpRequest, &Mem_76_Pfls_HseSrvDescriptor);

  dataPtr[MEM_76_PFLS_ZERO]  = (Mem_76_Pfls_DataType)(hseRequestResult & 0xFFu);
  dataPtr[MEM_76_PFLS_ONE]   = (Mem_76_Pfls_DataType)((hseRequestResult >> 8) & 0xFFu);
  dataPtr[MEM_76_PFLS_TWO]   = (Mem_76_Pfls_DataType)((hseRequestResult >> 16) & 0xFFu);
  dataPtr[MEM_76_PFLS_THREE] = (Mem_76_Pfls_DataType)((hseRequestResult >> 24) & 0xFFu);

  *lengthPtr=sizeof(hseSrvResponse_t);

  if(HSE_SRV_RSP_OK == hseRequestResult)
  {
    /* Set Job result */
    Mem_76_Pfls_InstanceInfo[instanceId].JobResult  = MEM_JOB_PENDING;
    /* Set current job */
    Mem_76_Pfls_InstanceInfo[instanceId].CurrentJob = MEM_76_PFLS_JOB_SWAP;
  	retVal=E_OK;
  }

  return retVal;
}
#define MEM_76_PFLS_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Mem_76_Pfls_JobSwapProcess                          **
**                                                                            **
** Description          : This function used to check result of Swap request  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : instanceId                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint8                                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
#define MEM_76_PFLS_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Mem_MemHwAb_14038 */
/* polyspace-begin MISRA-C3:2.7 [Justified:Low] "Not a defect" */
FUNC(Mem_76_Pfls_JobResultType, MEM_76_PFLS_CODE) Mem_76_Pfls_JobSwapProcess(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) InstanceId)
/* polyspace-end MISRA-C3:2.7 [Justified:Low] "Not a defect" */
{
  VAR(Mem_76_Pfls_JobResultType, AUTOMATIC) retVal;
  /* @Trace: Mem_76_Pfls_SUD_FUNC_072 */ 

  if(Mem_76_Pfls_HseSrvResponse == HSE_SRV_RSP_OK)
  {
    retVal = MEM_JOB_OK;
  }
  else if(Mem_76_Pfls_HseSrvResponse == HSE_PENDING)
  {
    retVal = MEM_JOB_PENDING;
  }
  else
  {
    retVal = MEM_JOB_FAILED;
  }

  return retVal;
}
#define MEM_76_PFLS_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace-end MISRA-C3:8.4,8.9,20.9 [Not a defect: Justify with annotations] "No Impact of this rule violation" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
