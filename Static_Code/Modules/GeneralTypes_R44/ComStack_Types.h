/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: ComStack_Types.h                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR BSW R4.4.0 Modules                                    **
**                                                                            **
**  PURPOSE   : Provision for Communication Stack dependent types             **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: yes                                       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By          Description                            **
********************************************************************************
** 1.0.0     29-Apr-2019   Khanh Le    Initial Version                        **
**           16-Mar-2020   HieuNV15    Minor correction                       **
*******************************************************************************/

#ifndef COMSTACK_TYPES_H
#define COMSTACK_TYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/* GENERAL_COMTYPE_002 */
#include "Std_Types.h"                  /* standard AUTOSAR types */
#include "ComStack_Cfg.h"               /* AUTOSAR type definition of the PduIdType and PduLengthType */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR specification version information */
#define COMSTACK_TYPES_AR_RELEASE_MAJOR_VERSION             4
#define COMSTACK_TYPES_AR_RELEASE_MINOR_VERSION             4

/* File version information */
#define COMSTACK_TYPES_SW_MAJOR_VERSION                     1
#define COMSTACK_TYPES_SW_MINOR_VERSION                     0
#define COMSTACK_TYPES_SW_PATCH_VERSION                     0

/*******************************************************************************
**                      Global Data Types (ECU dependent)                     **
*******************************************************************************/

/* SWS_COMTYPE_00038 */
/* Variables of the type NetworkHandleType shall be used to store the identifier of a communication channel. */
typedef uint8 NetworkHandleType;

/* SWS_COMTYPE_00039 */
/* IcomConfigIdType defines the configuration ID. */
typedef uint8 IcomConfigIdType;

/* SWS_COMTYPE_00036 */
/* Used to store the identifier of a partial network cluster. */
typedef uint16 PNCHandleType;

/*******************************************************************************
**                      Global Data Types (ECU independent)                   **
*******************************************************************************/

/* SWS_COMTYPE_00011 */
/* Variables of this type shall be used to store the basic information about a PDU of any type, namely a pointer variable pointing to its SDU (payload) and the corresponding length of the SDU in bytes. */
typedef struct
{
  P2VAR(uint8, AUTOMATIC, AUTOSAR_COMSTACKDATA) SduDataPtr;
  P2VAR(uint8, AUTOMATIC, AUTOSAR_COMSTACKDATA) MetaDataPtr;
  PduLengthType SduLength;
} PduInfoType;

/* SWS_COMTYPE_00031 */
/* Variables of this type shall be used to store the state of TP buffer. */
typedef enum
{
  TP_STMIN,           /* Separation Time */
  TP_BS,              /* Block Size */
  TP_BC               /* The Band width control parameter used in FlexRay transport protocol module. */
} TPParameterType;

/* SWS_COMTYPE_00012 */
/* Variables of this type shall be used to store the result of a buffer request. */
typedef enum                          
{
  BUFREQ_OK,           /* Buffer request accomplished successful */
  BUFREQ_E_NOT_OK,     /* Buffer request not successful. Buffer cannot be accessed */
  BUFREQ_E_BUSY,       /* Temporarily no buffer available. It's up the requestor to retry request for a certain time */
  BUFREQ_E_OVFL        /* No Buffer of the required length can be provided */
} BufReq_ReturnType;

/* SWS_COMTYPE_00027 */
/* Variables of this type shall be used to store the state of TP buffer. */
typedef enum                          
{
  TP_DATACONF,         /* TP_DATACONF  indicates  that  all  data,  that  have been  copied  so  far,  are  confirmed  and  can  be 
                          removed  from  the  TP  buffer.  Data  copied  by  this API call are excluded and will be confirmed later. */
  TP_DATARETRY,        /* TP_DATARETRY  indicates  that  this  API  call  shall copy already copied data in order to recover from 
                          an  error.  In  this  case  TxTpDataCnt  specifies  the offset of the first byte to be copied by the API call.  */
  TP_CONFPENDING
} TpDataStateType;

/* SWS_COMTYPE_00037 */
/* Variables of this type shall be used to store the information about Tp buffer handling. */
typedef struct 
{
  TpDataStateType TpDataState;
  PduLengthType TxTpDataCnt;
} RetryInfoType;

/* SWS_COMTYPE_00040 */
/* IcomSwitch_ErrorType defines the errors which can occur when activating or deactivating Pretended Networking. */
typedef enum
{
  ICOM_SWITCH_E_OK,       /* The activation of Pretended Networking was successful. */     
  ICOM_SWITCH_E_FAILED   /* The activation of Pretended Networking was not successful. */
} IcomSwitch_ErrorType;

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* COMSTACK_TYPES_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
