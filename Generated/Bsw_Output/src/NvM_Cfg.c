/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  FILE-NAME: NvM_Cfg.c                                                      **
**                                                                            **
**  MODULE-NAME: AUTOSAR NvM Module                                           **
**                                                                            **
**  NOTE: This file is auto generated, do not edit this file manually.        **
**                                                                            **
********************************************************************************

********************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  Framework version: 1.1.5                                                 **
**                                                                            **
**  Module version: 1.3.2.0                                                   **
**                                                                            **
**  Tool version:                                                        **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            **
********************************************************************************
**                      File Generation Information                           **
*******************************************************************************/
/*
* INPUT FILE:      Configuration\Definition\ECUConfigurationParameters.arxml
*                  Configuration\Definition\Fls_s32k312_mqfp172.epd
*                  Configuration\Definition\Os_ECU_Configuration_PDF_S32K312.arxml
*                  Configuration\Ecu\Ecud_Dem.arxml             
*                  Configuration\Ecu\Ecud_NvM.arxml             
*                  Configuration\Ecu\Ecud_Os.arxml              
*                  Configuration\Ecu\Mcal\Ecud_Fee.arxml        
*                  Configuration\Ecu\Mcal\Ecud_Fls.arxml        
*                  Generated\Bsw_Output\bswmd\Bswmd_NvM.arxml   
*                  Static_Code\Modules\b_mcal_nxp_S32K3xx\b_mcal_Fee_nxp_S32K3xx\autosar\Fee.epd
*                  Static_Code\Modules\Dem_R44\generator\Dem_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\NvM_R44\generator\NvM_ECU_Configuration_PDF.arxml
* GENERATED ON: The time-stamp is removed
*/


/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin VARIABLE:* [Justified:Low] "This variable will be used in code" */
/* polyspace-begin MISRA-C3:11.8 [Justified:Low] "Because NvM does not need to know about the final data type, the passed variables need to be cast to void to adapt the various kinds of data types" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "NvM_Cfg.h"
#include "NvM_IntTypes.h"

#include  "Mem_Integration.h"
#include  "Rte_NvM.h"
#include  "Dem_Ram.h"
#include  "KeyM_Cfg.h"
#include  "Mem_76_Pfls.h"

/*******************************************************************************
**                      Callback Prototypes                                   **
*******************************************************************************/
/* SingleBlockCallback */

/* InitBlockCallback */

/* ReadRamBlockFromNvCallback */

/* WriteRamBlockFromNvCallback */



/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define NVM_START_SEC_CONST_16
#include "MemMap.h"

CONST(uint16, NVM_CONST) NvM_ReadAllBlocks[NVM_TOTAL_NUM_OF_READALL_BLOCKS] = {1,2,3,4,5,6,8,9,10,11,12,13};

CONST(uint16, NVM_CONST) NvM_NotReadAll[NVM_BLOCKS_NOT_CONFIG_READALL] = {7,14,15,16};

CONST(uint16, NVM_CONST) NvM_NotWriteAll[NVM_BLOCKS_NOT_CONFIG_WRITEALL] = {7,14,15,16};

CONST(uint16, NVM_CONST) NvM_WriteAllBlocks[NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS] = {2,3,4,5,6,8,9,10,11,12,13,1};

#define NVM_STOP_SEC_CONST_16
#include "MemMap.h"
#define NVM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

CONST(NvM_BlkDescTbl, NVM_CONST)
          NvM_BlkDescTbls[NVM_TOTAL_NUM_OF_NVRAM_BLOCKS] =
{
  /* NvM 0 - Default_Block_0*/
  {
     /* *pRamBlkData */
     NULL_PTR,
     /* *pRomBlkData */
     NULL_PTR,
     /* ddBlockId */
     0x0000,
     /* enBlkMngmntType */
     NVM_BLOCK_NATIVE,
     /* usNvBlkBaseNumber */
     0x0000,
     /* Block Data Length */
     0x00,
     /* Write Verification Data Size */
     0x00,
     /* usBlkParams */
     0x00,
     /* NVRAM device ID value */
     0x00,
     /* Crc length */
     0x00,
     /* Number of NV blocks */
     0x00,
     /* Number of ROM blocks */
     0x00,
     /* Max Number of Read Retries */
     0x00,
     /* Max Number of Write Retries */
     0x00,
     /* Block Priority:0-Immediate other than 0-Standard   */
     0x00
  },
  /* NvM 1 - Default_Block_1*/
  {
     /* *pRamBlkData */
     (void *)ConfigIDRamBlock,
     /* *pRomBlkData */
     NULL_PTR,
     /* ddBlockId */
     0x1,
     /* enBlkMngmntType */
     NVM_BLOCK_REDUNDANT,
     /* usNvBlkBaseNumber */
     0x4,
     /* Block Data Length */
     0x2,
     /* Write Verification Data Size */
     0x2,
     /* usBlkParams */
     0x1B1,
     /* NVRAM device ID value */
     0x0,
     /* Crc length */
     0x2,
     /* Number of NV blocks */
     0x2,
     /* Number of ROM blocks */
     0x0,
     /* Max Number of Read Retries */
     0x1,
     /* Max Number of Write Retries */
     0x1,
     /* Block Priority:0-Immediate other than 0-Standard   */
     0x1
  },
  /* NvM 2 - Default_Block_2*/
  {
     /* *pRamBlkData */
     (void *)&Dem_NonVolatileData,
     /* *pRomBlkData */
     NULL_PTR,
     /* ddBlockId */
     0x2,
     /* enBlkMngmntType */
     NVM_BLOCK_NATIVE,
     /* usNvBlkBaseNumber */
     0x8,
     /* Block Data Length */
     0x8,
     /* Write Verification Data Size */
     0x00,
     /* usBlkParams */
     0x90,
     /* NVRAM device ID value */
     0x0,
     /* Crc length */
     0x0,
     /* Number of NV blocks */
     0x1,
     /* Number of ROM blocks */
     0x0,
     /* Max Number of Read Retries */
     0x1,
     /* Max Number of Write Retries */
     0x1,
     /* Block Priority:0-Immediate other than 0-Standard   */
     0x1
  },
  /* NvM 3 - Default_Block_3*/
  {
     /* *pRamBlkData */
     (void *)&Dem_EventStatusNvRamData,
     /* *pRomBlkData */
     NULL_PTR,
     /* ddBlockId */
     0x3,
     /* enBlkMngmntType */
     NVM_BLOCK_REDUNDANT,
     /* usNvBlkBaseNumber */
     0xC,
     /* Block Data Length */
     0xD4,
     /* Write Verification Data Size */
     0x00,
     /* usBlkParams */
     0x90,
     /* NVRAM device ID value */
     0x0,
     /* Crc length */
     0x0,
     /* Number of NV blocks */
     0x2,
     /* Number of ROM blocks */
     0x0,
     /* Max Number of Read Retries */
     0x1,
     /* Max Number of Write Retries */
     0x1,
     /* Block Priority:0-Immediate other than 0-Standard   */
     0x1
  },
  /* NvM 4 - Default_Block_4*/
  {
     /* *pRamBlkData */
     (void *)&Dem_PrimaryEventMemory[0],
     /* *pRomBlkData */
     NULL_PTR,
     /* ddBlockId */
     0x4,
     /* enBlkMngmntType */
     NVM_BLOCK_NATIVE,
     /* usNvBlkBaseNumber */
     0x10,
     /* Block Data Length */
     0x10,
     /* Write Verification Data Size */
     0x00,
     /* usBlkParams */
     0x90,
     /* NVRAM device ID value */
     0x0,
     /* Crc length */
     0x0,
     /* Number of NV blocks */
     0x1,
     /* Number of ROM blocks */
     0x0,
     /* Max Number of Read Retries */
     0x1,
     /* Max Number of Write Retries */
     0x1,
     /* Block Priority:0-Immediate other than 0-Standard   */
     0x1
  },
  /* NvM 5 - Default_Block_5*/
  {
     /* *pRamBlkData */
     (void *)&Dem_PrimaryEventMemory[1],
     /* *pRomBlkData */
     NULL_PTR,
     /* ddBlockId */
     0x5,
     /* enBlkMngmntType */
     NVM_BLOCK_NATIVE,
     /* usNvBlkBaseNumber */
     0x14,
     /* Block Data Length */
     0x10,
     /* Write Verification Data Size */
     0x00,
     /* usBlkParams */
     0x90,
     /* NVRAM device ID value */
     0x0,
     /* Crc length */
     0x0,
     /* Number of NV blocks */
     0x1,
     /* Number of ROM blocks */
     0x0,
     /* Max Number of Read Retries */
     0x1,
     /* Max Number of Write Retries */
     0x1,
     /* Block Priority:0-Immediate other than 0-Standard   */
     0x1
  },
  /* NvM 6 - Default_Block_6*/
  {
     /* *pRamBlkData */
     (void *)&Dem_PrimaryEventMemory[2],
     /* *pRomBlkData */
     NULL_PTR,
     /* ddBlockId */
     0x6,
     /* enBlkMngmntType */
     NVM_BLOCK_NATIVE,
     /* usNvBlkBaseNumber */
     0x18,
     /* Block Data Length */
     0x10,
     /* Write Verification Data Size */
     0x00,
     /* usBlkParams */
     0x90,
     /* NVRAM device ID value */
     0x0,
     /* Crc length */
     0x0,
     /* Number of NV blocks */
     0x1,
     /* Number of ROM blocks */
     0x0,
     /* Max Number of Read Retries */
     0x1,
     /* Max Number of Write Retries */
     0x1,
     /* Block Priority:0-Immediate other than 0-Standard   */
     0x1
  },
  /* NvM 7 - Default_Block_7*/
  {
     /* *pRamBlkData */
     NULL_PTR,
     /* *pRomBlkData */
     NULL_PTR,
     /* ddBlockId */
     0x7,
     /* enBlkMngmntType */
     NVM_BLOCK_NATIVE,
     /* usNvBlkBaseNumber */
     0x1C,
     /* Block Data Length */
     0x7,
     /* Write Verification Data Size */
     0x00,
     /* usBlkParams */
     0x0,
     /* NVRAM device ID value */
     0x0,
     /* Crc length */
     0x0,
     /* Number of NV blocks */
     0x1,
     /* Number of ROM blocks */
     0x0,
     /* Max Number of Read Retries */
     0x1,
     /* Max Number of Write Retries */
     0x1,
     /* Block Priority:0-Immediate other than 0-Standard   */
     0x1
  },
  /* NvM 8 - Default_Block_8*/
  {
     /* *pRamBlkData */
     (void *)&Dem_UserDefinedEventMemory[0],
     /* *pRomBlkData */
     NULL_PTR,
     /* ddBlockId */
     0x8,
     /* enBlkMngmntType */
     NVM_BLOCK_NATIVE,
     /* usNvBlkBaseNumber */
     0x20,
     /* Block Data Length */
     0x10,
     /* Write Verification Data Size */
     0x00,
     /* usBlkParams */
     0x90,
     /* NVRAM device ID value */
     0x0,
     /* Crc length */
     0x0,
     /* Number of NV blocks */
     0x1,
     /* Number of ROM blocks */
     0x0,
     /* Max Number of Read Retries */
     0x1,
     /* Max Number of Write Retries */
     0x1,
     /* Block Priority:0-Immediate other than 0-Standard   */
     0x1
  },
  /* NvM 9 - Default_Block_9*/
  {
     /* *pRamBlkData */
     (void *)&Dem_UserDefinedEventMemory[1],
     /* *pRomBlkData */
     NULL_PTR,
     /* ddBlockId */
     0x9,
     /* enBlkMngmntType */
     NVM_BLOCK_NATIVE,
     /* usNvBlkBaseNumber */
     0x24,
     /* Block Data Length */
     0x10,
     /* Write Verification Data Size */
     0x00,
     /* usBlkParams */
     0x90,
     /* NVRAM device ID value */
     0x0,
     /* Crc length */
     0x0,
     /* Number of NV blocks */
     0x1,
     /* Number of ROM blocks */
     0x0,
     /* Max Number of Read Retries */
     0x1,
     /* Max Number of Write Retries */
     0x1,
     /* Block Priority:0-Immediate other than 0-Standard   */
     0x1
  },
  /* NvM 10 - Default_Block_10*/
  {
     /* *pRamBlkData */
     (void *)&Dem_UserDefinedEventMemory[2],
     /* *pRomBlkData */
     NULL_PTR,
     /* ddBlockId */
     0xA,
     /* enBlkMngmntType */
     NVM_BLOCK_NATIVE,
     /* usNvBlkBaseNumber */
     0x28,
     /* Block Data Length */
     0x10,
     /* Write Verification Data Size */
     0x00,
     /* usBlkParams */
     0x90,
     /* NVRAM device ID value */
     0x0,
     /* Crc length */
     0x0,
     /* Number of NV blocks */
     0x1,
     /* Number of ROM blocks */
     0x0,
     /* Max Number of Read Retries */
     0x1,
     /* Max Number of Write Retries */
     0x1,
     /* Block Priority:0-Immediate other than 0-Standard   */
     0x1
  },
  /* NvM 11 - Default_Block_11*/
  {
     /* *pRamBlkData */
     (void *)&Dem_MirrorEventMemory[0],
     /* *pRomBlkData */
     NULL_PTR,
     /* ddBlockId */
     0xB,
     /* enBlkMngmntType */
     NVM_BLOCK_NATIVE,
     /* usNvBlkBaseNumber */
     0x2C,
     /* Block Data Length */
     0x10,
     /* Write Verification Data Size */
     0x00,
     /* usBlkParams */
     0x90,
     /* NVRAM device ID value */
     0x0,
     /* Crc length */
     0x0,
     /* Number of NV blocks */
     0x1,
     /* Number of ROM blocks */
     0x0,
     /* Max Number of Read Retries */
     0x1,
     /* Max Number of Write Retries */
     0x1,
     /* Block Priority:0-Immediate other than 0-Standard   */
     0x1
  },
  /* NvM 12 - Default_Block_12*/
  {
     /* *pRamBlkData */
     (void *)&Dem_MirrorEventMemory[1],
     /* *pRomBlkData */
     NULL_PTR,
     /* ddBlockId */
     0xC,
     /* enBlkMngmntType */
     NVM_BLOCK_NATIVE,
     /* usNvBlkBaseNumber */
     0x30,
     /* Block Data Length */
     0x10,
     /* Write Verification Data Size */
     0x00,
     /* usBlkParams */
     0x90,
     /* NVRAM device ID value */
     0x0,
     /* Crc length */
     0x0,
     /* Number of NV blocks */
     0x1,
     /* Number of ROM blocks */
     0x0,
     /* Max Number of Read Retries */
     0x1,
     /* Max Number of Write Retries */
     0x1,
     /* Block Priority:0-Immediate other than 0-Standard   */
     0x1
  },
  /* NvM 13 - Default_Block_13*/
  {
     /* *pRamBlkData */
     (void *)&Dem_MirrorEventMemory[2],
     /* *pRomBlkData */
     NULL_PTR,
     /* ddBlockId */
     0xD,
     /* enBlkMngmntType */
     NVM_BLOCK_NATIVE,
     /* usNvBlkBaseNumber */
     0x34,
     /* Block Data Length */
     0x10,
     /* Write Verification Data Size */
     0x00,
     /* usBlkParams */
     0x90,
     /* NVRAM device ID value */
     0x0,
     /* Crc length */
     0x0,
     /* Number of NV blocks */
     0x1,
     /* Number of ROM blocks */
     0x0,
     /* Max Number of Read Retries */
     0x1,
     /* Max Number of Write Retries */
     0x1,
     /* Block Priority:0-Immediate other than 0-Standard   */
     0x1
  },
  /* NvM 14 - Default_Block_14*/
  {
     /* *pRamBlkData */
     NULL_PTR,
     /* *pRomBlkData */
     NULL_PTR,
     /* ddBlockId */
     0xE,
     /* enBlkMngmntType */
     NVM_BLOCK_NATIVE,
     /* usNvBlkBaseNumber */
     0x38,
     /* Block Data Length */
     0x10,
     /* Write Verification Data Size */
     0x00,
     /* usBlkParams */
     0x0,
     /* NVRAM device ID value */
     0x0,
     /* Crc length */
     0x0,
     /* Number of NV blocks */
     0x1,
     /* Number of ROM blocks */
     0x0,
     /* Max Number of Read Retries */
     0x1,
     /* Max Number of Write Retries */
     0x1,
     /* Block Priority:0-Immediate other than 0-Standard   */
     0x1
  },
  /* NvM 15 - Default_Block_15*/
  {
     /* *pRamBlkData */
     NULL_PTR,
     /* *pRomBlkData */
     NULL_PTR,
     /* ddBlockId */
     0xF,
     /* enBlkMngmntType */
     NVM_BLOCK_NATIVE,
     /* usNvBlkBaseNumber */
     0x3C,
     /* Block Data Length */
     0x10,
     /* Write Verification Data Size */
     0x00,
     /* usBlkParams */
     0x0,
     /* NVRAM device ID value */
     0x0,
     /* Crc length */
     0x0,
     /* Number of NV blocks */
     0x1,
     /* Number of ROM blocks */
     0x0,
     /* Max Number of Read Retries */
     0x1,
     /* Max Number of Write Retries */
     0x1,
     /* Block Priority:0-Immediate other than 0-Standard   */
     0x1
  },
  /* NvM 16 - Default_Block_16*/
  {
     /* *pRamBlkData */
     NULL_PTR,
     /* *pRomBlkData */
     NULL_PTR,
     /* ddBlockId */
     0x10,
     /* enBlkMngmntType */
     NVM_BLOCK_NATIVE,
     /* usNvBlkBaseNumber */
     0x40,
     /* Block Data Length */
     0x10,
     /* Write Verification Data Size */
     0x00,
     /* usBlkParams */
     0x0,
     /* NVRAM device ID value */
     0x0,
     /* Crc length */
     0x0,
     /* Number of NV blocks */
     0x1,
     /* Number of ROM blocks */
     0x0,
     /* Max Number of Read Retries */
     0x1,
     /* Max Number of Write Retries */
     0x1,
     /* Block Priority:0-Immediate other than 0-Standard   */
     0x1
  }
};

#define NVM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"


/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA-C3:11.8 [Justified:Low] "Because NvM does not need to know about the final data type, the passed variables need to be cast to void to adapt the various kinds of data types" */
/* polyspace-end VARIABLE:* */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
