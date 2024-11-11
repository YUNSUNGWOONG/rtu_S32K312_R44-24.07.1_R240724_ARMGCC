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
**  SRC-MODULE: Mem_76_Pfls_Globals.h                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Memory Driver                                         **
**                                                                            **
**  PURPOSE   : Provides all the Global Variables of a Mem Driver module      **
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
#ifndef MEM_76_PFLS_INTTYPES_H
#define MEM_76_PFLS_INTTYPES_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Mem_76_Pfls.h"
#include "Mem_76_Pfls_Cfg.h"
/*******************************************************************************
**                     Global Data                                            **
*******************************************************************************/
#define MEM_76_PFLS_INSTANCE_ID                                          (0x00U)
#define E_MEM_SERVICE_NOT_AVAIL                                          (0x0AU)
#define MEM_76_PFLS_TRUE                                                 (0x01U)
#define MEM_76_PFLS_FALSE                                                (0x00U)
#define MEM_76_PFLS_ZERO                                                 (0x00U)
#define MEM_76_PFLS_ONE                                                  (0x01U)
#define MEM_76_PFLS_TWO                                                  (0x02U)
#define MEM_76_PFLS_THREE                                                (0x03U)
#define MEM_76_PFLS_FOUR                                                 (0x04U)
#define MEM_76_PFLS_FIVE                                                 (0x05U)
#define MEM_76_PFLS_SIX                                                  (0x06U)
#define MEM_76_PFLS_SEVEN                                                (0x07U)
#define MEM_76_PFLS_EIGHT                                                (0x08U)
#define MEM_76_PFLS_THIRTYTWO                                            (0x20U)

#define MEM_76_PFLS_UNUSED(x)                                            (void)x
/* get end address with start and length */
#define MEM_76_PFLS_GET_END_ADDRESS(addr, length)          (addr + length - 1UL)
/* get length with start and end address */
#define MEM_76_PFLS_GET_LENGTH(startAddr, endAddr)   (endAddr - startAddr + 1UL)

/* Watchdog trigger routine */
typedef void (*Mem_WDTriggerFct)(void);

/* Service Function Pointer Table re-define */
typedef void (*InitServiceFunctionPtr)(const Mem_76_Pfls_ConfigType *);

typedef void (*DeInitServiceFunctionPtr)(void);

typedef Std_ReturnType (*SuspendServiceFunctionPtr)(Mem_76_Pfls_InstanceIdType);

typedef Std_ReturnType (*ResumeServiceFunctionPtr)(Mem_76_Pfls_InstanceIdType);

typedef void (*PropagateErrorServiceFunctionPtr)(Mem_76_Pfls_InstanceIdType);

typedef Mem_76_Pfls_JobResultType (*GetJobResultServiceFunctionPtr)(
  Mem_76_Pfls_InstanceIdType);

typedef Std_ReturnType (*ReadServiceFunctionPtr)(\
  Mem_76_Pfls_InstanceIdType, \
  Mem_76_Pfls_AddressType, \
  Mem_76_Pfls_DataType *, \
  Mem_76_Pfls_LengthType);

typedef Std_ReturnType (*WriteServiceFunctionPtr)(\
  Mem_76_Pfls_InstanceIdType, Mem_76_Pfls_AddressType, \
  const Mem_76_Pfls_DataType *, \
  Mem_76_Pfls_LengthType);

typedef Std_ReturnType (*EraseServiceFunctionPtr)(\
  Mem_76_Pfls_InstanceIdType, \
  Mem_76_Pfls_AddressType, \
  Mem_76_Pfls_LengthType);

typedef Std_ReturnType (*BlankCheckServiceFunctionPtr)(\
  Mem_76_Pfls_InstanceIdType, \
  Mem_76_Pfls_AddressType, \
  Mem_76_Pfls_LengthType);

typedef Std_ReturnType (*HwSpecificServiceFunctionPtr)(\
  Mem_76_Pfls_InstanceIdType, \
  Mem_76_Pfls_HwServiceIdType, \
  Mem_76_Pfls_DataType *, \
  Mem_76_Pfls_LengthType *);

typedef Mem_76_Pfls_JobResultType (*FunctionRamPtr) (Mem_76_Pfls_AddressType, \
  Mem_76_Pfls_DataType *, Mem_76_Pfls_LengthType, const uint8);

typedef Mem_76_Pfls_JobResultType (*WriteFunctionRamPtr) (Mem_76_Pfls_AddressType, \
  const Mem_76_Pfls_DataType *, Mem_76_Pfls_LengthType, Mem_76_Pfls_LengthType, \
  const uint8);

typedef Std_ReturnType (*Mem_76_Pfls_CallOutFunctionPtr)(Mem_76_Pfls_InstanceIdType instanceID);

typedef struct
{
  InitServiceFunctionPtr            InitServFuncPtr;
  DeInitServiceFunctionPtr          DeInitServFuncPtr;
  GetJobResultServiceFunctionPtr    GetJobResultServFuncPtr;
  ReadServiceFunctionPtr            ReadServFuncPtr;
  WriteServiceFunctionPtr           WriteServFuncPtr;
  EraseServiceFunctionPtr           EraseServFuncPtr;
  PropagateErrorServiceFunctionPtr  PropagateErrorServFuncPtr;
  BlankCheckServiceFunctionPtr      BlankCheckServFuncPtr;
  SuspendServiceFunctionPtr         SuspendServFuncPtr;
  ResumeServiceFunctionPtr          ResumeServFuncPtr;
  HwSpecificServiceFunctionPtr      HwSpecificServFuncPtr;
} Mem_76_Pfls_FuncPtrTableType;

typedef struct
{
  uint32 EraseBurstSize;
  uint32 ReadBurstSize;
  uint32 WriteBurstSize;
} Mem_76_Pfls_BurstSettingsType;

typedef struct
{
  uint32 NumberOfSectors;
  uint32 EraseSectorSize;
  uint32 ReadPageSize;
  uint32 StartAddress;
  uint32 EndAddress;
  uint32 AltStartAddress;
  uint32 AltEndAddress;
  uint32 SpecifiedEraseCycles;
  uint32 WritePageSize;
  const Mem_76_Pfls_BurstSettingsType * BurstSettingsPtr;
} Mem_76_Pfls_SectorBatchType;

typedef struct
{
  uint32                  NumberOfPreCallout;
  Mem_76_Pfls_CallOutFunctionPtr      PreCalloutFunction[MEM_76_PFLS_MAX_NUMBER_OF_PRECALLOUT];
} Mem_76_Pfls_PreCalloutType;
/* @Trace: Mem_76_Pfls_SUD_MACRO_014 */
typedef struct
{
  uint32                  NumberOfPostCallout;
  Mem_76_Pfls_CallOutFunctionPtr      PostCalloutFunction[MEM_76_PFLS_MAX_NUMBER_OF_POSTCALLOUT];
} Mem_76_Pfls_PostCalloutType;

typedef struct
{
  uint32                                NumberOfSectors;
  const Mem_76_Pfls_PreCalloutType *            PreCalloutInfo;
  Mem_76_Pfls_SectorBatchType           SectorBatchesInfo[\
		MEM_76_PFLS_MAX_NUMBER_OF_SECTOR_PER_INSTANCE];
  const Mem_76_Pfls_PostCalloutType *          PostCalloutInfo;
} Mem_76_Pfls_InstanceType;

typedef enum
{
  MEM_76_PFLS_JOB_IDLE = 0x00U,
  MEM_76_PFLS_JOB_READ,
  MEM_76_PFLS_JOB_WRITE,
  MEM_76_PFLS_JOB_ERASE,
  MEM_76_PFLS_JOB_SWAP
} Mem_76_Pfls_JobType;

typedef struct
{
  Mem_76_Pfls_AddressType       SrcAddress;
  Mem_76_Pfls_AddressType       DestAddress;
  Mem_76_Pfls_LengthType        Length;
  Mem_76_Pfls_DataType   *      DestPtr;
  const Mem_76_Pfls_DataType *  SrcPtr;
  uint32                        NormalSize;
  uint32                        BurstSize;
} Mem_76_Pfls_SectorInfoType;

typedef struct
{
  Mem_76_Pfls_JobType         CurrentJob;
  Mem_76_Pfls_JobResultType   JobResult;
  uint32                      NumberOfSectorRemain;
  boolean                     AltAddressAccess;
  boolean                     CancelJob;
  Mem_76_Pfls_SectorInfoType  SectorInfo[\
    MEM_76_PFLS_MAX_NUMBER_OF_SECTOR_PER_INSTANCE];
  uint8                      SectorIndex;
} Mem_76_Pfls_InstanceInfoType;

#endif /* MEM_76_PFLS_INTTYPES_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
