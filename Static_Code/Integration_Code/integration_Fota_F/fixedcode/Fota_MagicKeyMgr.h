/*******************************************************************************
**                                                                            **
**  (C) 2022 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: FOTA_NonMmuSubFunc.h                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR FOTA                                                  **
**                                                                            **
**  PURPOSE   : Provides all of the user type define                          **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By                        Description              **
********************************************************************************
*******************************************************************************/
#ifndef FOTA_MAGICKEYMGR_H
#define FOTA_MAGICKEYMGR_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#include "Fota_User_Callouts.h"
#include "HwResource.h"

#ifndef FOTA_INTEGRATION_SINGLEMEM_PLATFORM
  #include "Fota_Cfg.h"
  #include "Fota_IntTypes.h"
  #include "Fota_IntFunc.h"
#endif /* #ifndef FOTA_INTEGRATION_SINGLEMEM_PLATFORM */

/*******************************************************************************
**                          Macros                                            **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.9 [Justified:Low] "Not a defect" */
#if(HWRESOURCE_FAMILY(HWRESOURCE_RH850F1X))
#define FOTA_MAGICKEY_PAGE_SIZE 256U
#elif (HWRESOURCE_FAMILY(HWRESOURCE_TC36X)) || (HWRESOURCE_FAMILY(HWRESOURCE_TC37X)) || \
      (HWRESOURCE_FAMILY(HWRESOURCE_TC38X)) || (HWRESOURCE_FAMILY(HWRESOURCE_TC39X)) || \
      (HWRESOURCE_FAMILY(HWRESOURCE_TC27X))
#define FOTA_MAGICKEY_PAGE_SIZE 32U
#else
#define FOTA_MAGICKEY_PAGE_SIZE 16U
#endif

#define FOTA_ACTKEY_MAX_CNT   15U
#define FOTA_BUFF_ONE          1U

#ifndef FOTA_INTEGRATION_SINGLEMEM_PLATFORM

#define FOTA_VERIFY_SECURITY_KEY_VALUE  FOTA_CPD_KEY_VALUE
#define FOTA_BM_SECURITY_KEY_VALUE      FOTA_SECURITY_KEY_VALUE /* Not yet support updater */
#define FOTA_FL_SECURITY_KEY_VALUE      FOTA_SECURITY_KEY_VALUE /* Not yet support updater */

#define FOTA_E_NOT_OK_STORIGE_FULL 0xF0u

#endif /* #ifndef FOTA_INTEGRATION_SINGLEMEM_PLATFORM */
/* polyspace-end MISRA-C3:20.9 [Justified:Low] "Not a defect" */

/*******************************************************************************
**                          Data Types                                        **
*******************************************************************************/

/* polyspace-begin CERT-C:DCL38-C, MISRA-C3:19.2 [Justified:Low] "This union is used to fixed address area" */
typedef union
{
  struct
  {
	  uint32 OrgKey;
	  uint32 OrgKey_Prio;
	  uint32 CpyKey;
	  uint32 CpyKey_Prio;
  } KeyElement;

  uint8 KeyBytes[FOTA_MAGICKEY_PAGE_SIZE];

} Fota_KeyAreaInfoType;

/* for runtime check */
typedef struct
{
  Fota_KeyAreaInfoType VfyKeyPage;
  Fota_KeyAreaInfoType ActKeyPage[FOTA_ACTKEY_MAX_CNT];
} Fota_MagicKeyAreaType;

/* for image build */
typedef struct
{
  Fota_KeyAreaInfoType VfyKeyPage;
  Fota_KeyAreaInfoType ActKeyPage[FOTA_BUFF_ONE];
} Fota_MagicKeyAreaType_forImage;
/* polyspace-end CERT-C:DCL38-C, MISRA-C3:19.2 [Justified:Low] "This union is used to fixed address area" */

#ifndef FOTA_INTEGRATION_SINGLEMEM_PLATFORM

typedef enum
{
  FOTA_BMKEY_MGR = 0x00U,
  FOTA_FLKEY_MGR = 0x01U
} Fota_KeyMgrType;

typedef enum
{
  FOTA_SETMAGICKEY_OK      = 0x00U,
  FOTA_SETMAGICKEY_PENDING = 0x01U,
  FOTA_SETMAGICKEY_FAILED  = 0x02U
} Fota_SetKeyResultType;

typedef enum
{
  FOTA_TARGET_AREA         = 0x00U,
  FOTA_DIRECT_AREA         = 0x01U
} Fota_ChkKeyAreaType;


/*******************************************************************************
**                     Global Data                                            **
*******************************************************************************/
extern FUNC(Std_ReturnType,FOTA_CODE) Fota_GetTopPrioActKey(
		     VAR(Fota_KeyMgrType,AUTOMATIC) KeyMgr,
		     P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) pEcuSwUnitIdx);

extern FUNC(Std_ReturnType,FOTA_CODE) Fota_SetTopPrioActKey_Request(
		     VAR(Fota_KeyMgrType,AUTOMATIC) KeyMgr,
		     VAR(uint8,AUTOMATIC) EcuSwUnitIdx);

extern FUNC(Std_ReturnType,FOTA_CODE) Fota_ChkActKeyAllSwUnit(
			 VAR(Fota_ChkKeyAreaType,AUTOMATIC) KeyArea);

extern FUNC(Std_ReturnType,FOTA_CODE) Fota_ChkActKey(
		     VAR(uint8,AUTOMATIC) EcuSwUnitIdx,
			 VAR(Fota_ChkKeyAreaType,AUTOMATIC) KeyArea);

extern FUNC(Std_ReturnType,FOTA_CODE) Fota_SetActKey_Request(
	         VAR(Fota_KeyMgrType,AUTOMATIC) KeyMgr,
		     VAR(uint8,AUTOMATIC) EcuSwUnitIdx);

extern FUNC(Std_ReturnType,FOTA_CODE) Fota_ChkVfyKeyAllSwUnit(
			 VAR(Fota_ChkKeyAreaType,AUTOMATIC) KeyArea);

extern FUNC(Std_ReturnType,FOTA_CODE) Fota_ChkVfyKey(
		     VAR(uint8,AUTOMATIC) EcuSwUnitIdx,
			 VAR(Fota_ChkKeyAreaType,AUTOMATIC) KeyArea);

extern FUNC(Std_ReturnType,FOTA_CODE) Fota_SetVfyKey_Request(
		     VAR(uint8,AUTOMATIC) EcuSwUnitIdx);

extern FUNC(Fota_SetKeyResultType,FOTA_CODE) Fota_SetKey_Result(void);

#endif /* #ifndef FOTA_INTEGRATION_SINGLEMEM_PLATFORM */

#endif /* FOTA_MAGICKEYMGR_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
