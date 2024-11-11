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
**  SRC-MODULE: Mem_Integration_User.h                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR MemStack Integration Module                           **
**                                                                            **
**  PURPOSE   : Provision of Version information                              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: Only STD_ON or STD_OFF of the macros can  **
**                                  be modified by user                       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:11.4,20.9 [Justified:Low] "This is nessasary for access the H/W Register, not a defect" */

#ifndef MEM_INTEGRATION_USER_H_
#define MEM_INTEGRATION_USER_H_

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#include "NvM.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                       Function Prototypes                                  **
*******************************************************************************/
#define NVM_START_SEC_CODE
#include "MemMap.h"


extern FUNC(void, NVM_CODE) Mem_PostFeeInitCallback (void);

#if (HWRESOURCE_VENDOR(HWRESOURCE_INFINEON))
extern FUNC(void, NVM_CODE) Mem_Infineon_IllegalStateCallback (void);
#endif

#if (HWRESOURCE_VENDOR(HWRESOURCE_CYPRESS))
extern FUNC(boolean, NVM_CODE) Mem_Cypress_IllegalStateCallback(void);
#endif

#if (\
  (defined(HWRESOURCE_CYT2BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT2BXX)) || \
  (defined(HWRESOURCE_CYT3BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT3BXX)) || \
  (defined(HWRESOURCE_CYT4BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT4BXX)) || \
  (defined(HWRESOURCE_CYT6BXX) && HWRESOURCE_FAMILY(HWRESOURCE_CYT6BXX)))
extern FUNC(void, NVM_CODE) Mem_ErrorCalloutHandler (uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);
#endif
/*******************************************************************************
**                      Macros                                                **
*******************************************************************************/

/*******************************************************************************
 * START : Only STD_ON or STD_OFF of the macros can be modified by user        *
 ******************************************************************************/

/* STD_ON  : When WriteAll is called , mainFunctions of the NvM,Fee,Fls,Eep,Ea 
 *           are called in the while-loop 
 * STD_OFF : When WriteAll is called , mainFunctions of the NvM,Fee,Fls,Eep,Ea
 *           are called by the GPT or periodic task 
 */

/* 
 * Default  : STD_ON
 *
 * please contact us. 
 *******************************************************************************/


#define MEM_WRITEALL_FAST_MODE    (STD_ON)


/*******************************************************************************
 * END : Only STD_ON or STD_OFF of the macros can be modified by user          *
 ******************************************************************************/

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* MEM_INTEGRATION_USER_H_ */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA-C3:11.4,20.9 [Justified:Low] "This is nessasary for access the H/W Register, not a defect" */
