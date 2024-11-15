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
**  FILE-NAME: LinTrcv_Cfg.c                                                  **
**                                                                            **
**  MODULE-NAME: AUTOSAR LIN Transceiver Driver Module                        **
**                                                                            **
**  NOTE: This file is auto generated, do not edit this file manually.        **
**                                                                            **
********************************************************************************

********************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  Framework version : 1.1.5                                                 **
**  Module version    : 1.0.7.0                                                **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            **
********************************************************************************
**                      File Generation Information                           **
*******************************************************************************/
/* polyspace +1 MISRA-C3:D4.4 [Not a defect:Low] "This section is not code." */
/*
* INPUT FILE:      Configuration\Definition\Dio_s32k312_mqfp172.epd
*                  Configuration\Definition\ECUConfigurationParameters.arxml
*                  Configuration\Ecu\Ecud_EcuM.arxml            
*                  Configuration\Ecu\Ecud_LinTrcv.arxml         
*                  Configuration\Ecu\Mcal\Ecud_Dio.arxml        
*                  Generated\Bsw_Output\bswmd\Bswmd_LinTrcv.arxml
*                  Static_Code\Modules\EcuM_R44\generator\EcuM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\LinTrcv_R44\generator\LinTrcv_ECU_Configuration_PDF.arxml
* GENERATED ON: The time-stamp is removed
*/ 

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "LinTrcv_PCTypes.h"

/*******************************************************************************
**                      Initialization Structure                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define LINTRCV_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* LIN Transceiver Driver Network Structure */
CONST(LinTrcv_ConfigType, LINTRCV_CONST)LinTrcv_GaaNetworkInfo[LINTRCV_NUM_OF_NETWORKS] =
{
    /* Network 0 - LIN1_0 */
    {
        /* ddWakeupSourceId */
        LINTRCV_INVALID_WKSOURCE,

        /* ddENPin */
        {LINTRCV_DIO_CHANNEL, {DioConf_DioChannel_DioChannel_PTD10}},

        /* ddWkPin */
        {LINTRCV_DIO_UNCONFIGURED, {LINTRCV_INVALID}},

        /* ddTxDPin */
        {LINTRCV_DIO_CHANNEL, {DioConf_DioChannel_DioChannel_PTB1}},

        /* ddRxDPin */
        {LINTRCV_DIO_CHANNEL, {DioConf_DioChannel_DioChannel_PTB0}},

        /* blLinTrcvWakeupByBusUsed */
        LINTRCV_FALSE,

        /* blChannelUsed */
        LINTRCV_TRUE,

        /* blStandbyModeUsed */
        LINTRCV_FALSE
    },
    /* Network 1 - LIN2_1 */
    {
        /* ddWakeupSourceId */
        LINTRCV_INVALID_WKSOURCE,

        /* ddENPin */
        {LINTRCV_DIO_CHANNEL, {DioConf_DioChannel_DioChannel_PTD11}},

        /* ddWkPin */
        {LINTRCV_DIO_UNCONFIGURED, {LINTRCV_INVALID}},

        /* ddTxDPin */
        {LINTRCV_DIO_CHANNEL, {DioConf_DioChannel_DioChannel_PTB27}},

        /* ddRxDPin */
        {LINTRCV_DIO_CHANNEL, {DioConf_DioChannel_DioChannel_PTB28}},

        /* blLinTrcvWakeupByBusUsed */
        LINTRCV_FALSE,

        /* blChannelUsed */
        LINTRCV_TRUE,

        /* blStandbyModeUsed */
        LINTRCV_FALSE
    }
};


#define LINTRCV_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
