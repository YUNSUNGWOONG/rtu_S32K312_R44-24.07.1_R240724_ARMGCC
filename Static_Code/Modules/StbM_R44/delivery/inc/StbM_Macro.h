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
**  SRC-MODULE: StbM_Macro.h                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Synchronized Time-Base Manager Module                 **
**                                                                            **
**  PURPOSE   : Provision of internal macro functions and their functionality.**
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision        Date                By              Description            **
********************************************************************************
** 1.0.3           21-Jul-2022         ThuanVT         JIRA BUGCLASSIC-152,   **
**												  	   R44-Redmine #633	      **
** 1.0.1           15-Sep-2021         SHKim           #20096                 **
** 1.0.0     	   16-Dec-2020         SHKim           Initial Version        **
*******************************************************************************/
#ifndef STBM_MACRO_H
#define STBM_MACRO_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Numeric Constants                                     **
*******************************************************************************/

/* StbM numeric constant */
/* @Trace: StbM_SDD_MACRO_011 */
#define STBM_ZERO                               0x00
#define STBM_ONE                                0x01
#define STBM_TWO                                0x02
#define STBM_SIXTEEN                            0x10
#define STBM_THIRTY_TWO                         0x20
#define STBM_TWO_HUNDRED_AND_FIVE            0xFF

/* StbM boolean constant */
/* @Trace: StbM_SDD_MACRO_012 */
#define STBM_TRUE                            ((boolean) 0x01)
#define STBM_FALSE                           ((boolean) 0x00)

/* StbM invalid configuration identifier */
#define STBM_INVALID                         (0xFF)

#define STBM_SEC_IN_NANOSEC                      1000000000u

#define STBM_SEC_IN_MICROSEC                     1000000u

#define STBM_MICROSEC_IN_NANOSEC                 1000u

#define STBM_ONE_SEC_IN_NANOSEC                0.000000001u

#define STBM_ONE_MICROSEC_IN_NANOSEC     0.001

#define STBM_ONE_SEC                                       0x01

#define STBM_MAX_OF_UINT32                           ((uint32)4294967295)

/* @Trace: StbM_SDD_DATATYPE_022 */
/* macros for Leap check function */
#define STBM_LEAP_CHECK_IGNORED         (0x00u)
#define STBM_SET_TIMELEAP_FUTURE        (0x01u)
#define STBM_SET_TIMELEAP_PAST          (0x02u)
#define STBM_CLEAR_TIMELEAP_FUTURE      (0x03u)
#define STBM_CLEAR_TIMELEAP_PAST        (0x04u)


#define STBM_BASE_INVAILD                ((uint8)0xFF)

/*******************************************************************************
**                      Macro Definitions                                     **
*******************************************************************************/
/* StbM boolean constant */
#define STBM_UNINITIALIZED             ((boolean) 0x00)
#define STBM_INITIALIZED               ((boolean) 0x01)

/* Time base status masks to reset the status */
#define STBM_TIMEOUT_RESET             (0xFEu)
#define STBM_Reserved_RESET            (0xFDu)
#define STBM_SYNC_TO_GATEWAY_RESET     (0xFBu)
#define STBM_GLOBAL_TIME_BASE_RESET    (0xF7u)
#define STBM_TIMELEAP_FUTURE_RESET     (0xEFu)
#define STBM_TIMELEAP_PAST_RESET       (0xDFu)

/* Time base status masks to set the status */
#define STBM_STATE_TIMEOUT             ((uint8)0x01u)
#define STBM_STATE_Reserved            ((uint8)0x02u)
#define STBM_STATE_SYNC_TO_GATEWAY     ((uint8)0x04u)
#define STBM_STATE_GLOBAL_TIME_BASE    ((uint8)0x08u)
#define STBM_STATE_TIMELEAP_FUTURE     ((uint8)0x10u)
#define STBM_STATE_TIMELEAP_PAST       ((uint8)0x20u)

/* Time base event status masks to set the status */
#define STBM_EV_GLOBAL_TIME                 ((uint16)0x00000001u)
#define STBM_EV_TIMEOUT_OCCURRED            ((uint16)0x00000002u)
#define STBM_EV_TIMEOUT_REMOVED             ((uint16)0x00000004u)
#define STBM_EV_TIMELEAP_FUTURE             ((uint16)0x00000008u)
#define STBM_EV_TIMELEAP_FUTURE_REMOVED     ((uint16)0x00000010u)
#define STBM_EV_TIMELEAP_PAST               ((uint16)0x00000020u)
#define STBM_EV_TIMELEAP_PAST_REMOVED       ((uint16)0x00000040u)
#define STBM_EV_SYNC_TO_SUBDOMAIN           ((uint16)0x00000080u)
#define STBM_EV_SYNC_TO_GLOBAL_MASTER       ((uint16)0x00000100u)
#define STBM_EV_RESYNC                      ((uint16)0x00000200u)
#define STBM_EV_RATECORRECTION              ((uint16)0x00000400u)
#define STBM_EV_ALL_STATUS_MASK             ((uint16)0x000001FFu)

/* This type indicates if an ECU is configured for a system wide master */
/* for a given Time Base is available or not. */
#define STBM_SYSTEM_WIDE_MASTER_DISABLED        ((uint8)0x00u)
#define STBM_SYSTEM_WIDE_MASTER_ENABLED         ((uint8)0x01u)

#define STBM_64BIT_LSB_MASK        (0x00000000FFFFFFFFu)
#define STBM_64BIT_MSB_MASK        (0xFFFFFFFF00000000u)

#define STBM_RATE_CORRECTION_ZERO      (0x00000000)
#define STBM_RATE_CORRECTION_ONE       (0x000F4240)

#define STBM_RATE_CORRECTION_ALLOW_MAX       (0x000FC23F)
#define STBM_RATE_CORRECTION_ALLOW_MIN       (0x000EC240)

#define STBM_RATE_DEVIATION_MAX        (0x7FFF)
#define STBM_RATE_DEVIATION_MIN        (0x8000)

#define STBM_NANOSEC_SEC_IN_ONE_SEC      (0x3B9ACA00)

#define STBM_TIMELEAP_MAX             (0x7FFFFFFF)
#define STBM_TIMELEAP_MIN             (0x80000000u)

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#endif /* STBM_MACRO_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

