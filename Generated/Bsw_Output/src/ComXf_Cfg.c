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
**  Generate On : The time-stamp is removed                                   **
**                                                                            **
**  SRC-MODULE:           ComXf_Cfg.c                                         **
**                                                                            **
**  PRODUCT   :           AUTOSAR COM Based Transformer Module                **
**                                                                            **
**  PURPOSE   :           This file contain function body for generic public  **
**                        API's.                                              **
**                                                                            **
**  HARDWARE DEPENDANT [Yes/No]: No                                           **
**                                                                            **
**  AUTOSAR RELEASE:  4.4.0                                                   **
*******************************************************************************/

/*******************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  FrameWork  Version: 1.1.5                                                 **
**                                                                            **
**  Module Version: 1.0.11.1                                                   **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            ** 
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "see SWS_MemMap_00003 of AUTOSAR" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: SafeComXf_SUD_FILE_001 */
/*include for ComXf.h*/
#include "ComXf.h"
/*include for ComXf_Cfg.h*/
#include "ComXf_Cfg.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

#if (COMXF_PRECOMPILE_CONFIG == STD_ON)
/* @Trace: SafeComXf_SUD_CONSTANT_002 */

#define COMXF_START_SEC_CONFIG_DATA_ASIL_D_UNSPECIFIED
#include "MemMap.h"
CONST(ComXf_PackSigType, COMXF_CONST) ComXf_Kast_SigPackInfo[COMXF_PACK_INFO_COUNT] =
{
/* ComXf_FD_CAN1_TCU_01_10ms_P11_TCU_EngRpmDisSta_Tx_P11 */
  {
    /* startORClearBitMask */
    0xfcU,
    
    /* setOREndMsk */
    0xfcU,
    
    /* noOfBytes */
    1U,
    
    /* shiftBits */
    0U

  }
};
#define COMXF_STOP_SEC_CONFIG_DATA_ASIL_D_UNSPECIFIED
#include "MemMap.h"

/* @Trace: SafeComXf_SUD_CONSTANT_003 */
#define COMXF_START_SEC_CONFIG_DATA_ASIL_D_UNSPECIFIED
#include "MemMap.h"
CONST(ComXf_UnPackSigType, COMXF_CONST) ComXf_Kast_SigUnPackInfo[COMXF_UNPACK_INFO_COUNT] =
{
/* ComXf_FD_CAN1_BSD_01_50ms_P11_TCU_EngRpmDisSta_Rx_P11 */
  {
    /* sigSignMsk64 */
    0x00U,

    /* sigSignMsk32 */
    0x00U,

    /* rxEndMsk */
    0x3U,

    /* noOfBytes */
    1U,
    
    /* shiftBits */
    0U   
    
  }
};
#define COMXF_STOP_SEC_CONFIG_DATA_ASIL_D_UNSPECIFIED
#include "MemMap.h"


#endif /*End of (COMXF_PRECOMPILE_CONFIG == STD_ON)*/
/* polyspace-end MISRA2012:20.1*/
/*******************************************************************************
**                      Initialization Structure                              **
*******************************************************************************/

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA RULE CHECKER)                   **
*******************************************************************************/
/* polyspace-end MISRA-C3:20.1 */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
