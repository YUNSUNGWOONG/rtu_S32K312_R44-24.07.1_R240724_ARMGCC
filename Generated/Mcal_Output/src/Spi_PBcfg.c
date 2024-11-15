/**   
*   @file    Spi_PBcfg.c
*   @implements Spi_PBcfg.c_Artifact
*   @version 3.0.0
*
*   @brief   AUTOSAR Spi - Post-Build(PB) configuration file code template.
*   @details Code template for Post-Build(PB) configuration file generation.
*
*   @addtogroup SPI_DRIVER_CONFIGURATION Spi Driver Configuration
*   @{
*/
/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : LPSPI
*   Dependencies         : 
*
*   Autosar Version      : 4.7.0
*   Autosar Revision     : ASR_REL_4_7_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 3.0.0
*   Build Version        : S32K3_RTD_3_0_0_P01_D2303_ASR_REL_4_7_REV_0000_20230331
*
*   Copyright 2020 - 2023 NXP Semiconductors NXP
*
*   NXP Confidential. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/
#ifdef __cplusplus
extern "C"{
#endif



/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "Spi.h"
#include "Spi_Ipw_PBcfg.h"

#if (SPI_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
#include "Dem.h"
#endif

/*==================================================================================================
*                                    SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define SPI_MODULE_ID_PBCFG_C                        83
#define SPI_VENDOR_ID_PBCFG_C                        43
#define SPI_AR_RELEASE_MAJOR_VERSION_PBCFG_C         4
#define SPI_AR_RELEASE_MINOR_VERSION_PBCFG_C         7
#define SPI_AR_RELEASE_REVISION_VERSION_PBCFG_C      0
#define SPI_SW_MAJOR_VERSION_PBCFG_C                 3
#define SPI_SW_MINOR_VERSION_PBCFG_C                 0
#define SPI_SW_PATCH_VERSION_PBCFG_C                 0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and SPI header file are of the same vendor */
#if (SPI_VENDOR_ID_PBCFG_C != SPI_VENDOR_ID)
    #error "Spi_PBCfg.c and Spi.h have different vendor ids"
#endif
/* Check if current file and SPI header file are of the same Autosar version */
#if ((SPI_AR_RELEASE_MAJOR_VERSION_PBCFG_C    != SPI_AR_RELEASE_MAJOR_VERSION) || \
     (SPI_AR_RELEASE_MINOR_VERSION_PBCFG_C    != SPI_AR_RELEASE_MINOR_VERSION) || \
     (SPI_AR_RELEASE_REVISION_VERSION_PBCFG_C != SPI_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Spi_PBCfg.c and Spi.h are different"
#endif
/* Check if current file and SPI header file are of the same Software version */
#if ((SPI_SW_MAJOR_VERSION_PBCFG_C != SPI_SW_MAJOR_VERSION) || \
     (SPI_SW_MINOR_VERSION_PBCFG_C != SPI_SW_MINOR_VERSION) || \
     (SPI_SW_PATCH_VERSION_PBCFG_C != SPI_SW_PATCH_VERSION))
    #error "Software Version Numbers of Spi_PBCfg.c and Spi.h are different"
#endif

/* Check if current file and SPI header file are of the same vendor */
#if (SPI_VENDOR_ID_PBCFG_C != SPI_IPW_VENDOR_ID_PBCFG_H)
    #error "Spi_PBCfg.c and Spi_Ipw_PBCfg.h have different vendor ids"
#endif
/* Check if current file and SPI header file are of the same Autosar version */
#if ((SPI_AR_RELEASE_MAJOR_VERSION_PBCFG_C    != SPI_IPW_AR_RELEASE_MAJOR_VERSION_PBCFG_H) || \
     (SPI_AR_RELEASE_MINOR_VERSION_PBCFG_C    != SPI_IPW_AR_RELEASE_MINOR_VERSION_PBCFG_H) || \
     (SPI_AR_RELEASE_REVISION_VERSION_PBCFG_C != SPI_IPW_AR_RELEASE_REVISION_VERSION_PBCFG_H ))
    #error "AutoSar Version Numbers of Spi_PBCfg.c and Spi_Ipw_PBCfg.h are different"
#endif
/* Check if current file and SPI header file are of the same Software version */
#if ((SPI_SW_MAJOR_VERSION_PBCFG_C != SPI_IPW_SW_MAJOR_VERSION_PBCFG_H) || \
     (SPI_SW_MINOR_VERSION_PBCFG_C != SPI_IPW_SW_MINOR_VERSION_PBCFG_H) || \
     (SPI_SW_PATCH_VERSION_PBCFG_C != SPI_IPW_SW_PATCH_VERSION_PBCFG_H))
    #error "Software Version Numbers of Spi_PBCfg.c and Spi_Ipw_PBCfg.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
#if (SPI_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
/* Check if current file and Dem.h file are of the same Autosar version */
#if ((SPI_AR_RELEASE_MAJOR_VERSION_PBCFG_C    != DEM_AR_RELEASE_MAJOR_VERSION) || \
     (SPI_AR_RELEASE_MINOR_VERSION_PBCFG_C    != DEM_AR_RELEASE_MINOR_VERSION))
    #error "AutoSar Version Numbers of Spi_PBCfg.c and Dem.h are different"
#endif
#endif
#endif

/*==================================================================================================
*                         LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/


/*==================================================================================================
*                                  LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
*                                      LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL FUNCTIONS
==================================================================================================*/
#define SPI_START_SEC_CODE
#include "Spi_MemMap.h"

/* List Of Notification Functions */
/* Job start Notifications */

/* Job End Notifications */

/* Sequence End Notifications */


#define SPI_STOP_SEC_CODE
#include "Spi_MemMap.h"
/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/
#if ((SPI_DMA_USED == STD_ON) && \
    ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2)))
    #define SPI_START_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#else
    #define SPI_START_SEC_VAR_CLEARED_UNSPECIFIED
#endif /* ((SPI_DMA_USED == STD_ON) && ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) ||
        (SPI_LEVEL_DELIVERED == SPI_LEVEL2))) */
#include "Spi_MemMap.h"

/* Buffers Descriptors for EB Channels and Allocate Buffers for IB Channels */
static Spi_DataBufferType Spi_BufferTXEEP_ADDR_CH[8];
static Spi_DataBufferType Spi_BufferRXEEP_ADDR_CH[8];
static Spi_DataBufferType Spi_BufferTXEEP_CMD_CH[8];
static Spi_DataBufferType Spi_BufferRXEEP_CMD_CH[8];
static Spi_DataBufferType Spi_BufferTXEEP_DATA_CH[8];
static Spi_DataBufferType Spi_BufferRXEEP_DATA_CH[8];


#if ((SPI_DMA_USED == STD_ON) && \
    ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2)))
    #define SPI_STOP_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#else
    #define SPI_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#endif /* ((SPI_DMA_USED == STD_ON) && ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) ||
        (SPI_LEVEL_DELIVERED == SPI_LEVEL2))) */
#include "Spi_MemMap.h"

#define SPI_START_SEC_VAR_INIT_UNSPECIFIED
#include "Spi_MemMap.h"

/* Buffers Descriptors for IB Channels */
    /*  Buffers Descriptors for IB Channels (if any) */
static Spi_BufferDescriptorType Spi_BufferEEP_ADDR_CH =
{
    (const uint8*)NULL_PTR,
    Spi_BufferTXEEP_ADDR_CH,  /* pBufferTX */
    Spi_BufferRXEEP_ADDR_CH   /* pBufferRX */
};
static Spi_BufferDescriptorType Spi_BufferEEP_CMD_CH =
{
    (const uint8*)NULL_PTR,
    Spi_BufferTXEEP_CMD_CH,  /* pBufferTX */
    Spi_BufferRXEEP_CMD_CH   /* pBufferRX */
};
static Spi_BufferDescriptorType Spi_BufferEEP_DATA_CH =
{
    (const uint8*)NULL_PTR,
    Spi_BufferTXEEP_DATA_CH,  /* pBufferTX */
    Spi_BufferRXEEP_DATA_CH   /* pBufferRX */
};



#define SPI_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Spi_MemMap.h"
/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/
#define SPI_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Spi_MemMap.h"

/* Channel Configuration */
/* Channel Configuration of EEP_ADDR_CH*/
static const Spi_ChannelConfigType Spi_ChannelConfig_EEP_ADDR_CH =
{
        /* EEP_ADDR_CH*/
        IB, /* BufferType IB or EB */
        8U, /* Frame size */
                (boolean)FALSE, /* Bite order */
        
#ifdef SPI_HALF_DUPLEX_MODE_SUPPORT
  #if (STD_ON == SPI_HALF_DUPLEX_MODE_SUPPORT)
        
        SPI_FULL_DUPLEX,
        
  #endif
#endif
        (uint32)1U, /* In the case SpiDefaultData is disabled. Set this value is 1U */
        8U, /* Length (configured in SpiIbNBuffers) */
        &Spi_BufferEEP_ADDR_CH, /* pcBufferDescriptor */
        SPI_SPURIOUS_CORE_ID_U32,
        &Spi_axSpiChannelState[0U] /* pChannelState pointer */
};
/* Channel Configuration of EEP_CMD_CH*/
static const Spi_ChannelConfigType Spi_ChannelConfig_EEP_CMD_CH =
{
        /* EEP_CMD_CH*/
        IB, /* BufferType IB or EB */
        8U, /* Frame size */
                (boolean)FALSE, /* Bite order */
        
#ifdef SPI_HALF_DUPLEX_MODE_SUPPORT
  #if (STD_ON == SPI_HALF_DUPLEX_MODE_SUPPORT)
        
        SPI_FULL_DUPLEX,
        
  #endif
#endif
        (uint32)1U, /* In the case SpiDefaultData is disabled. Set this value is 1U */
        8U, /* Length (configured in SpiIbNBuffers) */
        &Spi_BufferEEP_CMD_CH, /* pcBufferDescriptor */
        SPI_SPURIOUS_CORE_ID_U32,
        &Spi_axSpiChannelState[1U] /* pChannelState pointer */
};
/* Channel Configuration of EEP_DATA_CH*/
static const Spi_ChannelConfigType Spi_ChannelConfig_EEP_DATA_CH =
{
        /* EEP_DATA_CH*/
        IB, /* BufferType IB or EB */
        8U, /* Frame size */
                (boolean)FALSE, /* Bite order */
        
#ifdef SPI_HALF_DUPLEX_MODE_SUPPORT
  #if (STD_ON == SPI_HALF_DUPLEX_MODE_SUPPORT)
        
        SPI_FULL_DUPLEX,
        
  #endif
#endif
        (uint32)1U, /* In the case SpiDefaultData is disabled. Set this value is 1U */
        8U, /* Length (configured in SpiIbNBuffers) */
        &Spi_BufferEEP_DATA_CH, /* pcBufferDescriptor */
        SPI_SPURIOUS_CORE_ID_U32,
        &Spi_axSpiChannelState[2U] /* pChannelState pointer */
};
/* Spi_apChannelConfigList Channel Configuration of Spi*/
static const Spi_ChannelsCfgType Spi_aChannelConfigList[3] =
{
    {
    /* EEP_ADDR_CH */
    /* EEP_ADDR_CH */
    &Spi_ChannelConfig_EEP_ADDR_CH
    },
    {
    /* EEP_CMD_CH */
    /* EEP_CMD_CH */
    &Spi_ChannelConfig_EEP_CMD_CH
    },
    {
    /* EEP_DATA_CH */
    /* EEP_DATA_CH */
    &Spi_ChannelConfig_EEP_DATA_CH
    }

};

/* Channel Assignment of Jobs */

/* Channel to Job Assignment */

static const Spi_ChannelType Spi_EEP_JOB_CMD_ChannelAssignment[1] = {SpiConf_SpiChannel_EEP_CMD_CH};
static const Spi_ChannelType Spi_EEP_JOB_DATA_ChannelAssignment[3] = {SpiConf_SpiChannel_EEP_CMD_CH, SpiConf_SpiChannel_EEP_ADDR_CH, SpiConf_SpiChannel_EEP_DATA_CH};
static const Spi_ChannelType Spi_EEP_JOB_STAT_ChannelAssignment[2] = {SpiConf_SpiChannel_EEP_CMD_CH, SpiConf_SpiChannel_EEP_DATA_CH};

/* Configuration of Jobs */

/* Job Configuration of EEP_JOB_CMD*/
static const Spi_JobConfigType Spi_JobConfig_EEP_JOB_CMD =
{
        /* EEP_JOB_CMD */
        (Spi_ChannelType)1U, /* NumChannels field */
        Spi_EEP_JOB_CMD_ChannelAssignment, /* List of Channels */
        
            NULL_PTR,
        
        
            NULL_PTR,
        
        (sint8)0, /* Priority */
        SPI_SPURIOUS_CORE_ID_U32,        &Spi_axSpiJobState[0], /* JobState instance */
        CSIB0, /* HWUnit index */
        /* External Device Settings */
        SPI_SpiExternalDevice_0, /* External Device */
                &Spi_aExternalDeviceConfigList[SPI_SpiExternalDevice_0] /* pcExternalDeviceConfig - pointer to the external device configuration */        };
/* Job Configuration of EEP_JOB_DATA*/
static const Spi_JobConfigType Spi_JobConfig_EEP_JOB_DATA =
{
        /* EEP_JOB_DATA */
        (Spi_ChannelType)3U, /* NumChannels field */
        Spi_EEP_JOB_DATA_ChannelAssignment, /* List of Channels */
        
            NULL_PTR,
        
        
            NULL_PTR,
        
        (sint8)0, /* Priority */
        SPI_SPURIOUS_CORE_ID_U32,        &Spi_axSpiJobState[1], /* JobState instance */
        CSIB0, /* HWUnit index */
        /* External Device Settings */
        SPI_SpiExternalDevice_0, /* External Device */
                &Spi_aExternalDeviceConfigList[SPI_SpiExternalDevice_0] /* pcExternalDeviceConfig - pointer to the external device configuration */        };
/* Job Configuration of EEP_JOB_STAT*/
static const Spi_JobConfigType Spi_JobConfig_EEP_JOB_STAT =
{
        /* EEP_JOB_STAT */
        (Spi_ChannelType)2U, /* NumChannels field */
        Spi_EEP_JOB_STAT_ChannelAssignment, /* List of Channels */
        
            NULL_PTR,
        
        
            NULL_PTR,
        
        (sint8)0, /* Priority */
        SPI_SPURIOUS_CORE_ID_U32,        &Spi_axSpiJobState[2], /* JobState instance */
        CSIB0, /* HWUnit index */
        /* External Device Settings */
        SPI_SpiExternalDevice_0, /* External Device */
                &Spi_aExternalDeviceConfigList[SPI_SpiExternalDevice_0] /* pcExternalDeviceConfig - pointer to the external device configuration */        };
/* Spi_apJobConfigList Job Configuration of Spi*/
static const Spi_JobsCfgType Spi_aJobConfigList[3] =
{
    {
    /* EEP_JOB_CMD */
    /* EEP_JOB_CMD */
    &Spi_JobConfig_EEP_JOB_CMD
    },
    {
    /* EEP_JOB_DATA */
    /* EEP_JOB_DATA */
    &Spi_JobConfig_EEP_JOB_DATA
    },
    {
    /* EEP_JOB_STAT */
    /* EEP_JOB_STAT */
    &Spi_JobConfig_EEP_JOB_STAT
    }

};


/* Job Assignment of Sequences  */
/* Job to Sequence Assignment */

static const Spi_JobType Spi_EEP_SEQ_CMD_JobAssignment[1] = {SpiConf_SpiJob_EEP_JOB_CMD};
static const Spi_JobType Spi_EEP_SEQ_DATA_JobAssignment[1] = {SpiConf_SpiJob_EEP_JOB_DATA};
static const Spi_JobType Spi_EEP_SEQ_STAT_JobAssignment[1] = {SpiConf_SpiJob_EEP_JOB_STAT};
/* Configuration of Sequences */

/* Sequence Configuration of EEP_SEQ_CMD */
static const Spi_SequenceConfigType Spi_SequenceConfig_EEP_SEQ_CMD =
{
        /* EEP_SEQ_CMD */
        (Spi_JobType)1U,
        SPI_SPURIOUS_CORE_ID_U32,
        Spi_EEP_SEQ_CMD_JobAssignment, /* List of Jobs */
        NULL_PTR, /* End Notification */
        (uint8)FALSE /* Interruptible */
                #if ((SPI_DMA_USED == STD_ON) && (SPI_ENABLE_DMAFASTTRANSFER_SUPPORT == STD_ON))
        , (boolean)FALSE /* Enable Dma fast transfer */
        #endif
        
                #if ((SPI_DMA_USED == STD_ON) && (SPI_ENABLE_DMA_CONT_MEM_TRANSFER_SUPPORT == STD_ON))
        , (boolean)FALSE /* Enable Dma fast transfer */
        , NULL_PTR
        #endif
        
};
/* Sequence Configuration of EEP_SEQ_DATA */
static const Spi_SequenceConfigType Spi_SequenceConfig_EEP_SEQ_DATA =
{
        /* EEP_SEQ_DATA */
        (Spi_JobType)1U,
        SPI_SPURIOUS_CORE_ID_U32,
        Spi_EEP_SEQ_DATA_JobAssignment, /* List of Jobs */
        NULL_PTR, /* End Notification */
        (uint8)FALSE /* Interruptible */
                #if ((SPI_DMA_USED == STD_ON) && (SPI_ENABLE_DMAFASTTRANSFER_SUPPORT == STD_ON))
        , (boolean)FALSE /* Enable Dma fast transfer */
        #endif
        
                #if ((SPI_DMA_USED == STD_ON) && (SPI_ENABLE_DMA_CONT_MEM_TRANSFER_SUPPORT == STD_ON))
        , (boolean)FALSE /* Enable Dma fast transfer */
        , NULL_PTR
        #endif
        
};
/* Sequence Configuration of EEP_SEQ_STAT */
static const Spi_SequenceConfigType Spi_SequenceConfig_EEP_SEQ_STAT =
{
        /* EEP_SEQ_STAT */
        (Spi_JobType)1U,
        SPI_SPURIOUS_CORE_ID_U32,
        Spi_EEP_SEQ_STAT_JobAssignment, /* List of Jobs */
        NULL_PTR, /* End Notification */
        (uint8)FALSE /* Interruptible */
                #if ((SPI_DMA_USED == STD_ON) && (SPI_ENABLE_DMAFASTTRANSFER_SUPPORT == STD_ON))
        , (boolean)FALSE /* Enable Dma fast transfer */
        #endif
        
                #if ((SPI_DMA_USED == STD_ON) && (SPI_ENABLE_DMA_CONT_MEM_TRANSFER_SUPPORT == STD_ON))
        , (boolean)FALSE /* Enable Dma fast transfer */
        , NULL_PTR
        #endif
        
};
/* Spi_apSequenceConfigList Sequence Configuration of Spi*/
static const Spi_SeqsConfigType Spi_aSequenceConfigList[3] =
{
    {
    /* EEP_SEQ_CMD */
    /* EEP_SEQ_CMD */
    &Spi_SequenceConfig_EEP_SEQ_CMD
    },
    {
    /* EEP_SEQ_DATA */
    /* EEP_SEQ_DATA */
    &Spi_SequenceConfig_EEP_SEQ_DATA
    },
    {
    /* EEP_SEQ_STAT */
    /* EEP_SEQ_STAT */
    &Spi_SequenceConfig_EEP_SEQ_STAT
    }
};

/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/
/* Spi Configuration */


/** Compiler_Warning: In some cases, the partition configuration may not be used by the application. */
static const Spi_ConfigType Spi_Config=
{
    1U, /* u16MaxExternalDevice - number of external devices */
    2U, /* Spi_Max_Channel - number of channels */
    2U, /* Spi_Max_Job - number of jobs */
    2U, /* Spi_Max_Sequence - number of sequences */
    SPI_SPURIOUS_CORE_ID_U32, /* u32SpiCoreUse */
    Spi_aChannelConfigList, /* pcChannelConfig */
    Spi_aJobConfigList, /* pcJobConfig */
    Spi_aSequenceConfigList, /* pcSequenceConfig */
    Spi_aExternalDeviceConfigList, /* pcExternalDeviceConfig */
    Spi_aHwUnitConfigList /* pcHWUnitConfig */
#if (SPI_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
            ,{ (uint32)STD_OFF, (uint32)0U}/* SPI_E_HARDWARE_ERROR parameters*/         
#endif /* SPI_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF */  
};




const Spi_ConfigType * const Spi_PBCfgVariantPredefined[SPI_MAX_PARTITIONS]=
{
    &Spi_Config
};





#define SPI_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Spi_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */

