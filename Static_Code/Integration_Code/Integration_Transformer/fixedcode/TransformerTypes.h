/*******************************************************************************
**                                                                            **
**  SRC-MODULE: TransformerTypes.h                                            **
**                                                                            **
**                                                                            **
**  PRODUCT   : AUTOSAR Transformer General module                            **
**                                                                            **
**  PURPOSE   : Provision of external declaration of APIs and Service IDs     **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision Date           By              Description                        **
********************************************************************************
**                                                                            **
** 1.0.1    29-Sep-2020    Saemi Kwon      Redmine #25908                     **
** 1.0.0    12-Jan-2017    Gongbin Lim     Initial Version                    **
*******************************************************************************/

#ifndef TRANSFORMERTYPES_H
#define TRANSFORMERTYPES_H

/* polyspace-begin MISRA-C3:2.5 [Not a defect:Low] "These macro definition is implemented based on the autosar specification. It is not a defect" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define TRANSFORMERTYPE_AR_RELEASE_MAJOR_VERSION        4
#define TRANSFORMERTYPE_AR_RELEASE_MINOR_VERSION        2
#define TRANSFORMERTYPE_AR_RELEASE_REVISION_VERSION     2

/* Software Patch Version Information */
#define TRANSFORMERTYPE_SW_MAJOR_VERSION     1
#define TRANSFORMERTYPE_SW_MINOR_VERSION     0
#define TRANSFORMERTYPE_SW_PATCH_VERSION     0

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

#define E_SAFETY_VALID_REP             ((uint8)0x01)
#define E_SAFETY_VALID_SEQ             ((uint8)0x02)
#define E_SAFETY_VALID_ERR             ((uint8)0x03)
#define E_SAFETY_VALID_NND             ((uint8)0x05)
#define E_SAFETY_NODATA_OK             ((uint8)0x20)
#define E_SAFETY_NODATA_REP            ((uint8)0x21)
#define E_SAFETY_NODATA_SEQ            ((uint8)0x22)
#define E_SAFETY_NODATA_ERR            ((uint8)0x23)
#define E_SAFETY_NODATA_NND            ((uint8)0x25)
#define E_SAFETY_INIT_OK               ((uint8)0x30)
#define E_SAFETY_INIT_REP              ((uint8)0x31)
#define E_SAFETY_INIT_SEQ              ((uint8)0x32)
#define E_SAFETY_INIT_ERR              ((uint8)0x33)
#define E_SAFETY_INIT_NND              ((uint8)0x35)
#define E_SAFETY_INVALID_OK            ((uint8)0x40)
#define E_SAFETY_INVALID_REP           ((uint8)0x41)
#define E_SAFETY_INVALID_SEQ           ((uint8)0x42)
#define E_SAFETY_INVALID_ERR           ((uint8)0x43)
#define E_SAFETY_INVALID_NND           ((uint8)0x45)
#define E_SAFETY_SOFT_RUNTIMEERROR     ((uint8)0x77)
#define E_SAFETY_HARD_RUNTIMEERROR     ((uint8)0xFF)

/* Errors of Serializer Transformers */
#define E_NO_DATA                      ((uint8)0x01)
#define E_SER_GENERIC_ERROR            ((uint8)0x81)
#define E_SER_MALFORMED_MESSAGE        ((uint8)0x89)
#define E_SER_WRONG_PROTOCOL_VERSION   ((uint8)0x87)
#define E_SER_WRONG_INTERFACE_VERSION  ((uint8)0x88)
#define E_SER_WRONG_MESSAGE_TYPE       ((uint8)0x8a)

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/


/*******************************************************************************
**                      Extern declarations for Global Data                   **
*******************************************************************************/


/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

/* polyspace-end MISRA-C3:2.5 */

#endif /* TRANSFORMERTYPES_H */
