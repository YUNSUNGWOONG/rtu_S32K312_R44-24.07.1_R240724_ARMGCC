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
**  SRC-MODULE: Mem_76_Pfls_Cfg.c                                             **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Memory Driver                                         **
**                                                                            **
**  PURPOSE   : Define configuration datas                                    **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: yes                                       **
**                                                                            **
********************************************************************************

********************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  Framework version : 1.1.5                                                **
**                                                                            **
**  Module version : 0.0.6.7                                                  **
**                                                                            **
**  Tool Version: 4.4.7                                                       **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            **
********************************************************************************
**                      File Generation Information                           **
*******************************************************************************/
/*
* INPUT FILE:      Configuration\Ecu\Ecud_Mem_76_Pfls.arxml     
*                  Generated\Bsw_Output\bswmd\Bswmd_Mem_76_Pfls.arxml
*                  Static_Code\Modules\Mem_R44\generator\Mem_76_Pfls_ECU_Configuration_PDF.arxml
* GENERATED ON: The time-stamp is removed
*/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#include "Mem_76_Pfls.h"
#include "Mem_76_Pfls_Cfg.h"
#include "Mem_76_Pfls_Types.h"
#include "Mem_76_Pfls_Globals.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

#if (MEM_76_PFLS_PRE_CALLOUT_FUNCTION_SUPPORT == STD_ON)
#define MEM_76_PFLS_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
CONST(Mem_76_Pfls_PreCalloutType, MEM_76_PFLS_CONST) Mem_76_Pfls_PreCallout[MEM_76_PFLS_NUMBER_OF_INSTANCES] = \
{
  /* MemInstance0 */
  {
    /* NumberOfPreCallout */
    1UL,
    /* PreCalloutInfo */
    {
      Mem_76_Pfls_CacheControlDisable_Callout
    }
  }
};
#define MEM_76_PFLS_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif
#if (MEM_76_PFLS_POST_CALLOUT_FUNCTION_SUPPORT == STD_ON)
#define MEM_76_PFLS_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
CONST(Mem_76_Pfls_PostCalloutType, MEM_76_PFLS_CONST) Mem_76_Pfls_PostCallout[MEM_76_PFLS_NUMBER_OF_INSTANCES] = \
{
  /* MemInstance0 */
  {
    /* NumberOfPostCallout */
    1UL,
    /* PostCalloutInfo */
    {
      Mem_76_Pfls_CacheControlEnable_Callout
    }
  }
};
#define MEM_76_PFLS_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#define MEM_76_PFLS_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
CONST(Mem_76_Pfls_InstanceType, MEM_76_PFLS_CONST) Mem_76_Pfls_InstancesConfiguration[MEM_76_PFLS_NUMBER_OF_INSTANCES] = \
{

  /* MemInstance0 */
  {
    /* Number Of Sectors */
    .NumberOfSectors = 1UL,
    /* Pre-Callout  Function  */
    &Mem_76_Pfls_PreCallout[0],
    /* Sector batches information */
    .SectorBatchesInfo = 
    {
      /* MemInstance0_MemSectorBatch0 */
      {
        /* Number of sectors */
        186UL,
        /* Erase sector size */
        8192UL,
        /* Read page size */
        1UL,
        /* Start address */
        0x460000UL,
        /* End Address */
        6111231UL,
        /* Alt Start Address */
        0x460000UL,
        /* Alt End Address   */
        6111231UL,
        /* Specified erase cycles */
        4294967295UL,
        /* Write page size */
        8UL,
        /* Burst settings structure */
        NULL_PTR
      }

    },
    /* Post-Callout Function */
    &Mem_76_Pfls_PostCallout[0]
  }

};
#define MEM_76_PFLS_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
