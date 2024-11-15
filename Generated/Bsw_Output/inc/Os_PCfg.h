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
**  FILE-NAME: Os_PCfg.h                                                      **
**                                                                            **
**  MODULE-NAME: AUTOSAR Os Module                                            **
**                                                                            **
**  NOTE: This file is auto generated, do not edit this file manually.        **
**                                                                            **
********************************************************************************

********************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  Framework version : 1.1.5                                                 **
**  Module version : 1.3.0.0                                                  **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            **
********************************************************************************
**                      File Generation Information                           **
*******************************************************************************/

/*
* INPUT FILE:      Configuration\Ecu\Ecud_Os.arxml              
*                  Generated\Bsw_Output\bswmd\Bswmd_Os.arxml    
*                  Configuration\Ecu\Ecud_EcuC.arxml            
*                  Configuration\Definition\ECUConfigurationParameters.arxml
*                  Static_Code\Modules\Os_S32K31x_R44\generator\Bswmdt_Os.template
*                  Static_Code\Modules\Os_S32K31x_R44\generator\Swcdt_Bsw_Os.template
*                  Configuration\Definition\Os_ECU_Configuration_PDF_S32K312.arxml
* @Trace: SRS_BSW_00334 SRS_BSW_00423
* GENERATED ON: The time-stamp is removed
*/

#ifndef  OS_PCFG_H
#define  OS_PCFG_H


/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#ifndef VAR_CHECK
#include "Platform_Types.h"
#endif

/* @Trace: SRS_BSW_00318 SRS_BSW_00374 SRS_BSW_00379 */
#define    OS_AR_RELEASE_MAJOR_VERSION                   0x04u
#define    OS_AR_RELEASE_MINOR_VERSION                   0x04u
#define    OS_AR_RELEASE_REVISION_VERSION                0x00u
#define    OS_SW_MAJOR_VERSION                           0x01u
#define    OS_SW_MINOR_VERSION                           0x03u
#define    OS_SW_PATCH_VERSION                           0x00u
#define    OS_VENDOR_ID                                  0x004Cu
#define    OS_MODULE_ID                                  0x0001u
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Extern declarations                                   **
*******************************************************************************/

/*******************************************************************************
**                      Configuration Set Handles                             **
*******************************************************************************/

/*******************************************************************************
**                      Pre-compile options/Macros                            **
*******************************************************************************/
/* External Oscillator Clock(MHz) */
/* @Trace: SafeOs_SUD_API_000280 */
#define OS_TIMER_CLOCK                      120u

/* Least Priority In Cat 2 Interrupts */
/* @Trace: SafeOs_SUD_API_000278 */
#define OS_CAT2_MAX_PRIORITY                2

/* Number of CAT1 interrupts configured */
/* @Trace: SafeOs_SUD_API_000274 */
#define OS_CAT1_ISR_COUNT                   0

/* Least Priority In Cat 1 Interrupts */
/* @Trace: SafeOs_SUD_API_000277 */
#define OS_CAT1_LEAST_PRIORITY              1

/* Total number of Category 2 Isrs */
/* @Trace: SafeOs_SUD_API_000275 */
#define OS_CAT2_ISR_COUNT                   20

/* Total number of Isrs */
/* @Trace: SafeOs_SUD_API_000276 */
#define OS_ISR_COUNT                        20

/* @Trace: SafeOs_SUD_API_000474 */
#define OS_FPU_SUPPORT                      STD_ON

/* @Trace: SafeOs_SUD_API_000477 */
#define OS_NUM_OF_CORES  				    1



/* Count for Nesting Level of CAT2 ISR */
/* @Trace: SafeOs_SUD_API_000052 */
#define OS_MAX_NEST_LEVEL                   2


/* Total number of memory blocks */
/* Total number of memory blocks(MPU Regions) */
#define OS_MEMBLK_COUNT                     0


/* Total number of application memory blocks */
/* @Trace: SafeOs_SUD_API_000053 */
#define OS_APP_MEMBLK_CNT                     0


/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/


/* @Trace: SafeOs_SUD_API_000279 */
#ifndef VAR_CHECK
typedef uint32 Os_StackType ;
#endif


#endif /* OS_PCFG_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

