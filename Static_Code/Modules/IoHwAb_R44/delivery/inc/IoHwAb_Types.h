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
**  SRC-MODULE: IoHwAb_Types.h                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : Provision of IoHwAb global definitions                        **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.3.0.1   30-Jun-2022  KhaLN1            #CP44-365                         **
** 1.3.0     16-Mar-2022  PhucNHM           R44-Redmine #24320 #24709         **
** 1.0.0     04-Dec-2020  YangJin.Kim       R40-Redmine #26992                **
*******************************************************************************/

#ifndef IOHWAB_TYPES_H
#define IOHWAB_TYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Rte_IoHwAb_Type.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* @Trace: IoHwAb_SUD_MACRO_004 */
#define IOHWAB_ZERO                                0x00U
#define IOHWAB_ONE                                 0x01U
#define IOHWAB_TWO                                 0x02U
#define IOHWAB_THREE                               0x03U
#define IOHWAB_SEVEN                               0x07U
#define IOHWAB_EIGHT                               0x08U

#define IOHWAB_POL_LOW                             ((uint8)0x00)
#define IOHWAB_POL_HIGH                            ((uint8)0x01)

#define IOHWAB_IS_SW_OFF                           ((uint8)0x00)
#define IOHWAB_IS_SW_ON                            ((uint8)0x01)

#define IOHWAB_NULL_PTR                            ((void*)0)

#define IOHWAB_LOWPOWER_PREVENT                    0U
#define IOHWAB_LOWPOWER_ALLOW                      1U

#define	IOHWAB_RETURNCONTROLTOECU 	               0U
#define	IOHWAB_RESETTODEFAULT		                   1U
#define	IOHWAB_FREEZECURRENTSTATE	                 2U
#define	IOHWAB_SHORTTERMADJUST		                 3U


#define IOHWAB_UNLOCKED		0U
#define IOHWAB_LOCKED		1U

/*******************************************************************************
**                       Global Data Types                                    **
*******************************************************************************/
/* @Trace: IoHwAb_SUD_DATATYPE_044 */
typedef enum {
  IOHWAB_ACQ_NO_ACTION = 0,
  IOHWAB_ACQ_DIGITAL,
  IOHWAB_ACQ_ANALOG,
  IOHWAB_ACQ_DIGITAL_OUT,
  IOHWAB_ACQ_ANALOG_MUX,
  IOHWAB_ACQ_ANALOG_END
}IoHwAb_AcqState;

/* @Trace: IoHwAb_SUD_DATATYPE_045 */
typedef enum {
	IOHWAB_JOB_OK = 0, // The job has been finished successfully.
	IOHWAB_JOB_FAILED, // The job has not been finished successfully
	IOHWAB_JOB_UNINIT, // The underlying abstraction module or device driver hasnot been initialized(yet).
	IOHWAB_JOB_IDLE, // The underlying abstraction module or device driver iscurrently idle.
	IOHWAB_JOB_BUSY // The underlying abstraction module or device driver is currently busy.
}IoHwAb_JobResultType;

#endif /* IOHWAB_TYPES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
