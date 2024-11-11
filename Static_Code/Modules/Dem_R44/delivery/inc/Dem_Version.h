/*******************************************************************************
**                                                                            **
** (C) 2021 HYUNDAI AUTOEVER Corp.                                            **
** Confidential Proprietary Information. Distribution Limited.                **
** This source code is permitted to be used only in projects contracted       **
** with Hyundai Autoever, and any other use is prohibited.                    **
** If you use it for other purposes or change the source code,                **
** you may take legal responsibility.                                         **
** In this case, There is no warranty and technical support.                  **
**                                                                            **
**  SRC-MODULE: Dem_Version.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Event Manager                              **
**                                                                            **
**  PURPOSE   : C header for Dem_Version                                      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By            Description                          **
********************************************************************************
** 1.0.1.0   07-May-2021   HaoLT6        R44-Redmine #18724                   **
** 1.0.0     26-Feb-2021   EK Kim        Initial version                      **
*******************************************************************************/

#ifndef DEM_VERSION_H
#define DEM_VERSION_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
/* @Trace: Dem_SUD_MACRO_123 */
#define DEM_VERSION_AR_MAJOR_VERSION            DEM_AR_RELEASE_MAJOR_VERSION
/* @Trace: Dem_SUD_MACRO_124 */
#define DEM_VERSION_AR_MINOR_VERSION            DEM_AR_RELEASE_MINOR_VERSION
/* @Trace: Dem_SUD_MACRO_125 */
#define DEM_VERSION_AR_REVISION_VERSION         DEM_AR_RELEASE_REVISION_VERSION

/* Software Version Information */
#define DEM_VERSION_SW_MAJOR_VERSION            DEM_SW_MAJOR_VERSION
#define DEM_VERSION_SW_MINOR_VERSION            DEM_SW_MINOR_VERSION

/* This means the version of structure of the event memory
 * when ECU is reprogrammed by Scanner, Dem shall initialize the event memory
 * after checking the event memory version */
#define DEM_EVMEM_VERSION_SIGNATURES                   (0xA5U)

/* Note: The each version should not be equal.
 * Ex) 0x01 00 01(X),0x01 01 01(X),0x01 02 03(O)*/
#define DEM_EVMEM_VERSION_MAJOR                        (0x01U)
#define DEM_EVMEM_VERSION_MINOR                        (0x00U)
#define DEM_EVMEM_VERSION_REVISION                     (0x02U)

#if(DEM_DEV_ERROR_DETECT == STD_ON)
#define DEM_DET_AR_RELEASE_MAJOR_VERSION               4
#define DEM_DET_AR_RELEASE_MINOR_VERSION               4
#endif

#define DEM_NVM_AR_RELEASE_MAJOR_VERSION               4
#define DEM_NVM_AR_RELEASE_MINOR_VERSION               4

#define DEM_RTE_AR_RELEASE_MAJOR_VERSION               4
#define DEM_RTE_AR_RELEASE_MINOR_VERSION               4

#define DEM_DCM_AR_RELEASE_MAJOR_VERSION               4
#define DEM_DCM_AR_RELEASE_MINOR_VERSION               4

#if (DEM_FIM_INTEGRATED == STD_ON)
#define DEM_FIM_AR_RELEASE_MAJOR_VERSION               4
#define DEM_FIM_AR_RELEASE_MINOR_VERSION               4
#endif

#endif /*DEM_VERSION_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
