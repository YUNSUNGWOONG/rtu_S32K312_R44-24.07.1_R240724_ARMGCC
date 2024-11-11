/*==================================================================================================
* Project              : RTD AUTOSAR 4.7
* Platform             : CORTEXM
* Peripheral           : none
* Dependencies         : Fls
*
* Autosar Version      : 4.7.0
* Autosar Revision     : ASR_REL_4_7_REV_0000
* Autosar Conf.Variant :
* SW Version           : 3.0.0
* Build Version        : S32K3_RTD_3_0_0_P01_D2303_ASR_REL_4_7_REV_0000_20230331
*
* (c) Copyright 2020 - 2023 NXP Semiconductors
* All Rights Reserved.
*
* NXP Confidential. This software is owned or controlled by NXP and may only be
* used strictly in accordance with the applicable license terms. By expressly
* accepting such terms or by downloading, installing, activating and/or otherwise
* using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms. If you do not agree to be
* bound by the applicable license terms, then you may not retain, install,
* activate or otherwise use the software.
==================================================================================================*/

/**
*   @file
*
*   @addtogroup FEE
*   @{
*/
/*   @implements Fee_Cfg.c_Artifact*/
#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Fee.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define FEE_VENDOR_ID_CFG_C                      43
#define FEE_AR_RELEASE_MAJOR_VERSION_CFG_C       4
#define FEE_AR_RELEASE_MINOR_VERSION_CFG_C       7
#define FEE_AR_RELEASE_REVISION_VERSION_CFG_C    0
#define FEE_SW_MAJOR_VERSION_CFG_C               3
#define FEE_SW_MINOR_VERSION_CFG_C               0
#define FEE_SW_PATCH_VERSION_CFG_C               0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and Fee header file are of the same vendor */
#if (FEE_VENDOR_ID_CFG_C != FEE_VENDOR_ID)
    #error "Fee_Cfg.c and Fee.h have different vendor ids"
#endif
/* Check if current file and Fee header file are of the same Autosar version */
#if ((FEE_AR_RELEASE_MAJOR_VERSION_CFG_C    != FEE_AR_RELEASE_MAJOR_VERSION) || \
     (FEE_AR_RELEASE_MINOR_VERSION_CFG_C    != FEE_AR_RELEASE_MINOR_VERSION) || \
     (FEE_AR_RELEASE_REVISION_VERSION_CFG_C != FEE_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Fee_Cfg.c and Fee.h are different"
#endif
/* Check if current file and Fee header file are of the same Software version */
#if ((FEE_SW_MAJOR_VERSION_CFG_C != FEE_SW_MAJOR_VERSION) || \
     (FEE_SW_MINOR_VERSION_CFG_C != FEE_SW_MINOR_VERSION) || \
     (FEE_SW_PATCH_VERSION_CFG_C != FEE_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Fee_Cfg.c and Fee.h are different"
#endif



/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/




#define FEE_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Fee_MemMap.h"


/* Configuration of cluster group FeeClusterGroup_0 */
static const Fee_ClusterType Fee_FeeClusterGroup_0[2] =
{
    /* FeeCluster_0 */
    {
        0U, /* Start address */
        24576U /* Size */
    },
    /* FeeCluster_1 */
    {
        24576U, /* Start address */
        24576U /* Size */
    }
};

/* Configuration of cluster group FeeClusterGroup_1 */
static const Fee_ClusterType Fee_FeeClusterGroup_1[2] =
{
    /* FeeCluster_0 */
    {
        49152U, /* Start address */
        24576U /* Size */
    },
    /* FeeCluster_1 */
    {
        73728U, /* Start address */
        16384U /* Size */
    }
};

/* Configuration of cluster group set */
const Fee_ClusterGroupType Fee_ClrGrps[FEE_NUMBER_OF_CLUSTER_GROUPS] =
{
    
    /* FeeClusterGroup_0 */
    {
        Fee_FeeClusterGroup_0, /* Cluster set */
        2U, /* Number of clusters */
        0U /* Size of the reserved area */
    },
    
    /* FeeClusterGroup_1 */
    {
        Fee_FeeClusterGroup_1, /* Cluster set */
        2U, /* Number of clusters */
        0U /* Size of the reserved area */
    }
};

/* Configuration of Fee blocks */
const Fee_BlockConfigType Fee_BlockConfig[FEE_CRT_CFG_NR_OF_BLOCKS] =
{
    /* FeeBlock_ConfigID */
    {
        FeeConf_FeeBlockConfiguration_FeeBlock_ConfigID, /* FeeBlockNumber symbol */
        4U, /* FeeBlockSize */
        0U, /* FeeClusterGroup */
        (boolean)FALSE,   /* FeeImmediateData */
#if (FEE_SWAP_FOREIGN_BLOCKS_ENABLED == STD_ON) 
        FEE_PROJECT_APPLICATION /* Fee Block Assignment to a project */
#else
        FEE_PROJECT_RESERVED
#endif
    },
    /* FeeBlock_ConfigID_copy1 */
    {
        FeeConf_FeeBlockConfiguration_FeeBlock_ConfigID_copy1, /* FeeBlockNumber symbol */
        4U, /* FeeBlockSize */
        1U, /* FeeClusterGroup */
        (boolean)FALSE,   /* FeeImmediateData */
#if (FEE_SWAP_FOREIGN_BLOCKS_ENABLED == STD_ON) 
        FEE_PROJECT_APPLICATION /* Fee Block Assignment to a project */
#else
        FEE_PROJECT_RESERVED
#endif
    },
    /* FeeBlock_DemNonVolatileData */
    {
        FeeConf_FeeBlockConfiguration_FeeBlock_DemNonVolatileData, /* FeeBlockNumber symbol */
        8U, /* FeeBlockSize */
        0U, /* FeeClusterGroup */
        (boolean)FALSE,   /* FeeImmediateData */
#if (FEE_SWAP_FOREIGN_BLOCKS_ENABLED == STD_ON) 
        FEE_PROJECT_APPLICATION /* Fee Block Assignment to a project */
#else
        FEE_PROJECT_RESERVED
#endif
    },
    /* FeeBlock_DemEventStatusNvRamBlock */
    {
        FeeConf_FeeBlockConfiguration_FeeBlock_DemEventStatusNvRamBlock, /* FeeBlockNumber symbol */
        212U, /* FeeBlockSize */
        0U, /* FeeClusterGroup */
        (boolean)FALSE,   /* FeeImmediateData */
#if (FEE_SWAP_FOREIGN_BLOCKS_ENABLED == STD_ON) 
        FEE_PROJECT_APPLICATION /* Fee Block Assignment to a project */
#else
        FEE_PROJECT_RESERVED
#endif
    },
    /* FeeBlock_DemEventStatusNvRamBlock_copy1 */
    {
        FeeConf_FeeBlockConfiguration_FeeBlock_DemEventStatusNvRamBlock_copy1, /* FeeBlockNumber symbol */
        212U, /* FeeBlockSize */
        1U, /* FeeClusterGroup */
        (boolean)FALSE,   /* FeeImmediateData */
#if (FEE_SWAP_FOREIGN_BLOCKS_ENABLED == STD_ON) 
        FEE_PROJECT_APPLICATION /* Fee Block Assignment to a project */
#else
        FEE_PROJECT_RESERVED
#endif
    },
    /* FeeBlock_DemPrimaryEventMemoryEntry_0 */
    {
        FeeConf_FeeBlockConfiguration_FeeBlock_DemPrimaryEventMemoryEntry_0, /* FeeBlockNumber symbol */
        16U, /* FeeBlockSize */
        0U, /* FeeClusterGroup */
        (boolean)FALSE,   /* FeeImmediateData */
#if (FEE_SWAP_FOREIGN_BLOCKS_ENABLED == STD_ON) 
        FEE_PROJECT_APPLICATION /* Fee Block Assignment to a project */
#else
        FEE_PROJECT_RESERVED
#endif
    },
    /* FeeBlock_DemPrimaryEventMemoryEntry_1 */
    {
        FeeConf_FeeBlockConfiguration_FeeBlock_DemPrimaryEventMemoryEntry_1, /* FeeBlockNumber symbol */
        16U, /* FeeBlockSize */
        0U, /* FeeClusterGroup */
        (boolean)FALSE,   /* FeeImmediateData */
#if (FEE_SWAP_FOREIGN_BLOCKS_ENABLED == STD_ON) 
        FEE_PROJECT_APPLICATION /* Fee Block Assignment to a project */
#else
        FEE_PROJECT_RESERVED
#endif
    },
    /* FeeBlock_DemPrimaryEventMemoryEntry_2 */
    {
        FeeConf_FeeBlockConfiguration_FeeBlock_DemPrimaryEventMemoryEntry_2, /* FeeBlockNumber symbol */
        16U, /* FeeBlockSize */
        0U, /* FeeClusterGroup */
        (boolean)FALSE,   /* FeeImmediateData */
#if (FEE_SWAP_FOREIGN_BLOCKS_ENABLED == STD_ON) 
        FEE_PROJECT_APPLICATION /* Fee Block Assignment to a project */
#else
        FEE_PROJECT_RESERVED
#endif
    },
    /* FeeBlock_Test_Native_6 */
    {
        FeeConf_FeeBlockConfiguration_FeeBlock_Test_Native_6, /* FeeBlockNumber symbol */
        7U, /* FeeBlockSize */
        0U, /* FeeClusterGroup */
        (boolean)FALSE,   /* FeeImmediateData */
#if (FEE_SWAP_FOREIGN_BLOCKS_ENABLED == STD_ON) 
        FEE_PROJECT_APPLICATION /* Fee Block Assignment to a project */
#else
        FEE_PROJECT_RESERVED
#endif
    },
    /* FeeBlock_DemUserDefinedEventMemoryEntry_0 */
    {
        FeeConf_FeeBlockConfiguration_FeeBlock_DemUserDefinedEventMemoryEntry_0, /* FeeBlockNumber symbol */
        16U, /* FeeBlockSize */
        0U, /* FeeClusterGroup */
        (boolean)FALSE,   /* FeeImmediateData */
#if (FEE_SWAP_FOREIGN_BLOCKS_ENABLED == STD_ON) 
        FEE_PROJECT_APPLICATION /* Fee Block Assignment to a project */
#else
        FEE_PROJECT_RESERVED
#endif
    },
    /* FeeBlock_DemUserDefinedEventMemoryEntry_1 */
    {
        FeeConf_FeeBlockConfiguration_FeeBlock_DemUserDefinedEventMemoryEntry_1, /* FeeBlockNumber symbol */
        16U, /* FeeBlockSize */
        0U, /* FeeClusterGroup */
        (boolean)FALSE,   /* FeeImmediateData */
#if (FEE_SWAP_FOREIGN_BLOCKS_ENABLED == STD_ON) 
        FEE_PROJECT_APPLICATION /* Fee Block Assignment to a project */
#else
        FEE_PROJECT_RESERVED
#endif
    },
    /* FeeBlock_DemUserDefinedEventMemoryEntry_2 */
    {
        FeeConf_FeeBlockConfiguration_FeeBlock_DemUserDefinedEventMemoryEntry_2, /* FeeBlockNumber symbol */
        16U, /* FeeBlockSize */
        0U, /* FeeClusterGroup */
        (boolean)FALSE,   /* FeeImmediateData */
#if (FEE_SWAP_FOREIGN_BLOCKS_ENABLED == STD_ON) 
        FEE_PROJECT_APPLICATION /* Fee Block Assignment to a project */
#else
        FEE_PROJECT_RESERVED
#endif
    },
    /* FeeBlock_DemMirrorEventMemory_0 */
    {
        FeeConf_FeeBlockConfiguration_FeeBlock_DemMirrorEventMemory_0, /* FeeBlockNumber symbol */
        16U, /* FeeBlockSize */
        0U, /* FeeClusterGroup */
        (boolean)FALSE,   /* FeeImmediateData */
#if (FEE_SWAP_FOREIGN_BLOCKS_ENABLED == STD_ON) 
        FEE_PROJECT_APPLICATION /* Fee Block Assignment to a project */
#else
        FEE_PROJECT_RESERVED
#endif
    },
    /* FeeBlock_DemMirrorEventMemory_1 */
    {
        FeeConf_FeeBlockConfiguration_FeeBlock_DemMirrorEventMemory_1, /* FeeBlockNumber symbol */
        16U, /* FeeBlockSize */
        0U, /* FeeClusterGroup */
        (boolean)FALSE,   /* FeeImmediateData */
#if (FEE_SWAP_FOREIGN_BLOCKS_ENABLED == STD_ON) 
        FEE_PROJECT_APPLICATION /* Fee Block Assignment to a project */
#else
        FEE_PROJECT_RESERVED
#endif
    },
    /* FeeBlock_DemMirrorEventMemory_2 */
    {
        FeeConf_FeeBlockConfiguration_FeeBlock_DemMirrorEventMemory_2, /* FeeBlockNumber symbol */
        16U, /* FeeBlockSize */
        0U, /* FeeClusterGroup */
        (boolean)FALSE,   /* FeeImmediateData */
#if (FEE_SWAP_FOREIGN_BLOCKS_ENABLED == STD_ON) 
        FEE_PROJECT_APPLICATION /* Fee Block Assignment to a project */
#else
        FEE_PROJECT_RESERVED
#endif
    },
    /* FeeBlock_DemPermanentEventMemory_0 */
    {
        FeeConf_FeeBlockConfiguration_FeeBlock_DemPermanentEventMemory_0, /* FeeBlockNumber symbol */
        16U, /* FeeBlockSize */
        0U, /* FeeClusterGroup */
        (boolean)FALSE,   /* FeeImmediateData */
#if (FEE_SWAP_FOREIGN_BLOCKS_ENABLED == STD_ON) 
        FEE_PROJECT_APPLICATION /* Fee Block Assignment to a project */
#else
        FEE_PROJECT_RESERVED
#endif
    },
    /* FeeBlock_DemPermanentEventMemory_1 */
    {
        FeeConf_FeeBlockConfiguration_FeeBlock_DemPermanentEventMemory_1, /* FeeBlockNumber symbol */
        16U, /* FeeBlockSize */
        0U, /* FeeClusterGroup */
        (boolean)FALSE,   /* FeeImmediateData */
#if (FEE_SWAP_FOREIGN_BLOCKS_ENABLED == STD_ON) 
        FEE_PROJECT_APPLICATION /* Fee Block Assignment to a project */
#else
        FEE_PROJECT_RESERVED
#endif
    },
    /* FeeBlock_DemPermanentEventMemory_2 */
    {
        FeeConf_FeeBlockConfiguration_FeeBlock_DemPermanentEventMemory_2, /* FeeBlockNumber symbol */
        16U, /* FeeBlockSize */
        0U, /* FeeClusterGroup */
        (boolean)FALSE,   /* FeeImmediateData */
#if (FEE_SWAP_FOREIGN_BLOCKS_ENABLED == STD_ON) 
        FEE_PROJECT_APPLICATION /* Fee Block Assignment to a project */
#else
        FEE_PROJECT_RESERVED
#endif
    }
};

#define FEE_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Fee_MemMap.h"

#ifdef __cplusplus
}
#endif
/** @}*/
