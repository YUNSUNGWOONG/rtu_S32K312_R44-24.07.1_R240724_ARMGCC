/*******************************************************************************
**                                                                            **
**  (C) 2022 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Mem_76_Pfls_IntFunc.h                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Memory Driver                                         **
**                                                                            **
**  PURPOSE   :                          **
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
#ifndef MEM_76_PFLS_INTFUNC_H
#define MEM_76_PFLS_INTFUNC_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Mem_76_Pfls_Cfg.h"

/*******************************************************************************
**                           Macros                                           **
*******************************************************************************/
/* get sector address from its index - a program/erase sector consist of 8KB */
#define MEM_76_PFLS_GET_SECTOR_ADDRESS(sectorIndex)\
                   ((Mem_76_Pfls_AddressType)0x00400000 + ((sectorIndex)*8*1024))
/* Maximum number of bytes in program data register DATA0->DATA31 */
#define MEM_76_PFLS_DATA_SIZE_BYTES_U32                                     128u
/* get the sector index by address */
#define MEM_76_PFLS_GET_SECTOR_INDEX_BY_ADDR(address) \
     (((address) - Mem_76_Pfls_BlockInfor[(MEM_76_PFLS_ZERO)].BlockStartAddress)/(MEM_76_PFLS_SECTOR_SIZE))

#define SWAPWAITCNT 50000u
	/* Timeout for the Hse_Ip layer while waiting for a response from HSE for a synchronous request.
	   As the Hse component is configured in this example in Design Studio to have the type of Timeout Counter set to 'SYSTEM',
	the timeout in the variable below will be expressed in microseconds units - thus being set to 100 ms */
#define TIMEOUT_US_U32                      ((uint32)100000U)
	/* List of identifiers for the MU instances */
#define MU0_INSTANCE_U8                     ((uint8)0U)
	/* Identifier of the MU channel used by HSE to listen for administrative requests */
#define MU_ADMIN_CHANNEL_U8                 ((uint8)0U)

#define HSE_PENDING                         (hseSrvResponse_t)0x0UL

/*******************************************************************************
**                     Global Data Types                                      **
*******************************************************************************/
/* Flash Erase/Write operation */
typedef enum
{
  Mem_76_Pfls_Erase_Operation,
  Mem_76_Pfls_Write_Operation,
  Mem_76_Pfls_ExpressWrite_Operation
}Mem_76_Pfls_OperationType;
/* Voltage (EHV bit) status  */
typedef enum
{
  Mem_76_Pfls_High_Voltage,
  Mem_76_Pfls_Low_Voltage
}Mem_76_Pfls_VoltageStatus;

/* struct contains information of a Flash memory block */
typedef struct
{
  /* start address of sector */
  uint32 BlockStartAddress;
  /* end address of sector */
  uint32 BlockEndAddress;
  /* number of sector per block */
  uint32 numOfSectorPerBlock;
  /* number of sector in sector area */
  uint32 numOfSectorInSectorArea;
  /* number of sector in sector area */
  uint32 numOfSectorInSuperSectorArea;
}Mem_76_Pfls_BlockInformation;

/* Memory Block type */
typedef enum
{
  MEM_76_PFLS_STD_BLOCK = 0x0AU,
  MEM_76_PFLS_ALT_BLOCK = 0x0BU
} Mem_76_Pfls_MemoryBlockType;

/*******************************************************************************
**                     Global Data                                            **
*******************************************************************************/
#define MEM_76_PFLS_START_SEC_CONST_32
#include "MemMap.h"

/* Note: Linker scripts symbol declarations must be accessed by the use of the '&' operators */
#if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
/* Start Position of Pflash driver code in flash */
extern CONST(uint32, MEM_76_PFLS_CONST) __Mem_76_Pfls_RomStart;
/* Size of Pflash driver code in flash */
extern CONST(uint32, MEM_76_PFLS_CONST) __Mem_76_Pfls_RomSize;
/* Start Position of Pflash driver code in Ram */
extern CONST(uint32, MEM_76_PFLS_CONST) __Mem_76_Pfls_RamCode;
#endif

#define MEM_76_PFLS_STOP_SEC_CONST_32
#include "MemMap.h"

/*******************************************************************************
**                     Function Prototypes                                    **
*******************************************************************************/
#define MEM_76_PFLS_START_SEC_CODE
#include "MemMap.h"

/* Function to Copy Flash driver from ROM to RAM  */
#if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
extern FUNC(void, MEM_76_PFLS_CODE) Mem_76_Pfls_ToolBox_InternalActive(void);
#endif

extern FUNC(Mem_76_Pfls_JobResultType, MEM_76_PFLS_CODE) Mem_76_Pfls_InternalRead(\
  VAR(Mem_76_Pfls_AddressType, AUTOMATIC) Address, \
  P2VAR(Mem_76_Pfls_DataType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) DataPtr, \
  VAR(Mem_76_Pfls_LengthType, AUTOMATIC) Length, \
  CONST(uint8, MEM_76_PFLS_CONST) BurstEnable);

extern FUNC(Mem_76_Pfls_JobResultType, MEM_76_PFLS_CODE) Mem_76_Pfls_InternalErase(\
  VAR(Mem_76_Pfls_AddressType, AUTOMATIC) Address, \
  P2VAR(Mem_76_Pfls_DataType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) DataPtr, \
  VAR(Mem_76_Pfls_LengthType, AUTOMATIC) Length, \
  CONST(uint8, MEM_76_PFLS_CONST) BurstEnable);

extern FUNC(Mem_76_Pfls_JobResultType, MEM_76_PFLS_CODE) Mem_76_Pfls_InternalWrite(\
  VAR(Mem_76_Pfls_AddressType, AUTOMATIC) Address, \
  P2CONST(Mem_76_Pfls_DataType, AUTOMATIC, MEM_76_PFLS_APPL_CONST) DataPtr, \
  VAR(Mem_76_Pfls_LengthType, AUTOMATIC) WriteNormalSize, \
  VAR(Mem_76_Pfls_LengthType, AUTOMATIC) WriteBurstSize, \
  CONST(uint8, MEM_76_PFLS_CONST) BurstEnable);

extern FUNC(void, MEM_76_PFLS_CODE) Mem_76_Pfls_InternalInitialize(void);

extern FUNC(Mem_76_Pfls_AddressType, MEM_76_PFLS_CODE) Mem_76_Pfls_CalBankAddress(
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) instanceId,
  VAR(Mem_76_Pfls_AddressType, AUTOMATIC) Address);

extern FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_ActiveBankCheck(\
  P2VAR(Mem_76_Pfls_DataType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) dataPtr, \
  P2VAR(Mem_76_Pfls_LengthType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) lengthPtr);

extern FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_DirectAddressAccess(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) instanceId, \
  P2VAR(Mem_76_Pfls_DataType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) dataPtr, \
  P2VAR(Mem_76_Pfls_LengthType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) lengthPtr);

extern FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_AltAddressAccess(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) instanceId, \
  P2VAR(Mem_76_Pfls_DataType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) dataPtr, \
  P2VAR(Mem_76_Pfls_LengthType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) lengthPtr);

extern FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_SwapActive(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) instanceId, \
  P2VAR(Mem_76_Pfls_DataType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) dataPtr, \
  P2VAR(Mem_76_Pfls_LengthType, AUTOMATIC, MEM_76_PFLS_APPL_DATA) lengthPtr);

extern FUNC(Mem_76_Pfls_JobResultType, MEM_76_PFLS_CODE) Mem_76_Pfls_JobSwapProcess(\
  VAR(Mem_76_Pfls_InstanceIdType, AUTOMATIC) InstanceId);

#define MEM_76_PFLS_STOP_SEC_CODE
#include "MemMap.h"

#endif /* MEM_76_PFLS_INTFUNC_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
