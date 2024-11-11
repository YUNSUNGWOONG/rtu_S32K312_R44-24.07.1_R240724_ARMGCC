/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**                                                                            **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Mem_Integration.h                                             **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR MemStack Integration Module                           **
**                                                                            **
**  PURPOSE   : Provision of Version information                              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:11.4,20.9,D4.9 [Justified:Low] "This is nessasary for access the H/W Register, not a defect" */

#ifndef MEMDRIVERINIT_H_
#define MEMDRIVERINIT_H_

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#include "NvM.h"
#include "HwResource.h"
#include "MemIf_Cfg.h"
#include "Mem_Integration_User.h"

/*******************************************************************************
**                      Macros                                                **
*******************************************************************************/
#define MEM_TRUE                                        (1U)
#define MEM_FALSE                                       (0U)

/* Service ID for OsTask_BSW_Mem_Process */
#define MEM_OSTASK_BSW_MEM_PROCESS_SID                  ((uint8)0x50U)


/* DET Code */
#define MEM_E_ALARM                                     0x19
#define MEM_E_EVENT                                     0x20
/* Compatible both R40 and R44 */
#if defined(MEMIF_FLS_DRIVER_INDEX) || defined(MEMIF_FEE_DRIVER_INDEX)
  #define MEM_FEE_USED          (STD_ON)

  #if (HWRESOURCE_GET_FAMILY() == HWRESOURCE_RH850F1X)
    /* in case of RH850, Fls is not used but the specific library of the renesas 
     * is included int the Fee(EEL) */
    #define MEM_FLS_USED          (STD_OFF)
  #else
    #define MEM_FLS_USED          (STD_ON)
  #endif

#else
  /* FEE is not configured */
  #define MEM_FEE_USED          (STD_OFF)
  /* FLS is not configured */
  #define MEM_FLS_USED          (STD_OFF)
#endif
/* Compatible both R40 and R44 */
#if defined(MEMIF_EEP_DRIVER_INDEX) || defined(MEMIF_EA_DRIVER_INDEX)
#define MEM_EA_USED          (STD_ON)
#else
#define MEM_EA_USED          (STD_OFF)
#endif

/* polyspace-begin CERT-C:PRE00-C [Justified:Low] "Macros use to abtract Memory Stack's functions" */

#define MEM_MAINFUNCTION_NVM()  do { NvM_MainFunction();} while(0)

#if (MEM_FEE_USED == STD_ON)
#define MEM_MAINFUNCTION_FEE()  do { Fee_MainFunction();} while(0)
#else
#define MEM_MAINFUNCTION_FEE()  do {} while(0)
#endif

#if (MEM_FLS_USED == STD_ON)
#define MEM_MAINFUNCTION_FLS()  do { Fls_MainFunction();} while(0)
#else
#define MEM_MAINFUNCTION_FLS()  do {} while(0)
#endif

#if (MEM_EA_USED == STD_ON)
#define MEM_MAINFUNCTION_EA()   do { Ea_MainFunction(); } while(0)
#define MEM_MAINFUNCTION_EEP()  do { Eep_MainFunction();} while(0)
#else
#define MEM_MAINFUNCTION_EA()   do {} while(0)
#define MEM_MAINFUNCTION_EEP()  do {} while(0)
#endif


#if (NVM_DEV_ERROR_DETECT == STD_ON)
#define MEM_REPORT_ERROR(sid,error) \
do {\
  (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID, (sid), (error));\
} while(0)
#else
#define MEM_REPORT_ERROR(sid,error)  do {} while(0)
#endif /* end of DET */

/* polyspace-end CERT-C:PRE00-C [Justified:Low] "Macros use to abtract Memory Stack's functions" */

#if ((defined(HWRESOURCE_S32K14X) && HWRESOURCE_FAMILY(HWRESOURCE_S32K14X)) || \
     (defined(HWRESOURCE_S32K31X) && HWRESOURCE_FAMILY(HWRESOURCE_S32K31X)))
/* polyspace +1 MISRA-C3:19.2 [Justified:Low] "Used to input a value into the register" */
typedef union
{
  uint8   u_uint8[2];
  uint16  u_uint16;
}InsPtrType;
#endif
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
extern uint8 ConfigIDRamBlock[2];

#ifdef NvMConf_NvMBlockDescriptor_NvMBlock_IntTst_TestBlock1
extern uint8 NvMBlock_IntTst_TestBlock1_Ram_Block[10];
#endif /* NvMConf_NvMBlockDescriptor_NvMBlock_IntTst_TestBlock1 */

#ifdef NvMConf_NvMBlockDescriptor_NvMBlock_IntTst_TestBlock2
extern uint8 NvMBlock_IntTst_TestBlock2_Ram_Block[10];
#endif /* NvMConf_NvMBlockDescriptor_NvMBlock_IntTst_TestBlock2 */

#ifdef NvMBlock_IntTst_TestBlock1
extern uint8 NvMBlock_IntTst_TestBlock1_Ram_Block[10];
#endif /* NvMBlock_IntTst_TestBlock1 */
/*******************************************************************************
**                       Function Prototypes                                  **
*******************************************************************************/
#define NVM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(void, NVM_CODE) Mem_Driver_StartUp(void);
extern FUNC(void, NVM_CODE) Mem_FlsInitPerform(void);
extern FUNC(void, NVM_CODE) Mem_FeeInitPerform(void);
extern FUNC(void, NVM_CODE) Mem_EaInitPerform(void);
extern FUNC(void, NVM_CODE) Mem_Driver_ShutDown(void);

#if ((defined(HWRESOURCE_S32K14X) && HWRESOURCE_FAMILY(HWRESOURCE_S32K14X)) || \
     (defined(HWRESOURCE_S32K31X) && HWRESOURCE_FAMILY(HWRESOURCE_S32K31X)))
/* polyspace MISRA-C3:8.5  [Justified:Low] "It must have declared external  declaration  because it is a function provided by mem_integration." */
extern FUNC(boolean, NVM_CODE) Fls_DataEccHandler(uint8 ** instr_pt2pt, volatile uint32 * addr_CFSR, uint32 * addr_BFAR);
#endif


#define NVM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-end MISRA-C3:11.4,20.9,D4.9 [Justified:Low] "This is nessasary for access the H/W Register, not a defect" */

#endif /* MEMDRIVERINIT_H_ */
