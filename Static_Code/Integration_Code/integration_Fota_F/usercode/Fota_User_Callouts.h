/*******************************************************************************
**                                                                            **
**  (C) 2022 HYUNDAI AUTOEVER Co., Ltd.                                       **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE:                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   :          **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
*******************************************************************************/

#ifndef FOTA_USER_CALLOUTS_H
#define FOTA_USER_CALLOUTS_H
/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.9 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:D4.9,2.2 [Justified:Low] "use function like-macro for reduce execution time and stack" */
/* polyspace-begin MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
* the register value can be read via the address" */
#include "Std_Types.h"

#ifdef FOTA_INTEGRATION_SINGLEMEM_PLATFORM

  #define    FBL_COMMON_RAM_ADDRESS                        (0x2800A010U)
  #define    FBL_STARTUP_COMMAND_ADDRESS                   (0x2800A000U)
  #define    FBL_STARTUP_COMMAND_VALUE                     (0xA5430911U)
  #define    FOTA_SECURITY_KEY_VALUE                       (0x90482442U)
  #define    FOTA_CPD_KEY_VALUE                            (0x19801217U)
  #define    FOTA_ZERO                            (0x0u)

#else /* #ifdef FOTA_INTEGRATION_SINGLEMEM_PLATFORM */

#include "HwResource.h"
#include "Dcm_Types.h"


#if (HWRESOURCE_MCU(HWRESOURCE_RH850F1KM))
#include "Iocommon_Defines.h"
#elif (HWRESOURCE_FAMILY(HWRESOURCE_TC21X) ||\
       HWRESOURCE_FAMILY(HWRESOURCE_TC22X) ||\
       HWRESOURCE_FAMILY(HWRESOURCE_TC23X) ||\
       HWRESOURCE_FAMILY(HWRESOURCE_TC26X) ||\
       HWRESOURCE_FAMILY(HWRESOURCE_TC27X) ||\
       HWRESOURCE_FAMILY(HWRESOURCE_TC29X) ||\
       HWRESOURCE_FAMILY(HWRESOURCE_TC33X) ||\
       HWRESOURCE_FAMILY(HWRESOURCE_TC36X) ||\
       HWRESOURCE_FAMILY(HWRESOURCE_TC37X) ||\
       HWRESOURCE_FAMILY(HWRESOURCE_TC38X) ||\
       HWRESOURCE_FAMILY(HWRESOURCE_TC39X))
#include "IfxScu_reg.h"
#elif ((HWRESOURCE_FAMILY(HWRESOURCE_SPC58XC)) ||\
       (HWRESOURCE_FAMILY(HWRESOURCE_SPC58XB)) ||\
       (HWRESOURCE_FAMILY(HWRESOURCE_SPC58XG)) ||\
       (HWRESOURCE_FAMILY(HWRESOURCE_SPC58XH)))
#include "Reg_eSys.h"
#elif ((HWRESOURCE_FAMILY(HWRESOURCE_MPC5606X)) ||\
       (HWRESOURCE_FAMILY(HWRESOURCE_MPC5606X)) ||\
       (HWRESOURCE_FAMILY(HWRESOURCE_MPC5607X)))
#include "Reg_eSys.h"
#include "Reg_eSys_MagicCarpet.h"
#include "Mcu_LLD.h"
#elif (HWRESOURCE_FAMILY(HWRESOURCE_S32K14X))
#include "Reg_eSys_CortexM4.h"
#include "StdRegMacros.h"
#include "Reg_eSys_RCM.h"
#include "Mcal.h"
#endif

/*******************************************************************************
**                            Global Data Types                               **
*******************************************************************************/
/* rollback case (OEUK)*/
#define FOTA_SECURITY_ROW_L10                              (10u)

#if ((HWRESOURCE_FAMILY(HWRESOURCE_MPC5606X)) ||\
     (HWRESOURCE_FAMILY(HWRESOURCE_MPC5606X)) ||\
     (HWRESOURCE_FAMILY(HWRESOURCE_MPC5607X)))

#define RGM_FES_F_SOFT                (*(volatile uint32*)MC_RGM_FES_R)
/* Register Address */
#define MC_ME_GS                      (*(volatile uint32*)MC_ME_GS_R)
#endif /* #if (HWRESOURCE_FAMILY(HWRESOURCE_MPC560XB)) */

#if ((HWRESOURCE_FAMILY(HWRESOURCE_SPC58XC)) ||\
      (HWRESOURCE_FAMILY(HWRESOURCE_SPC58XB)) ||\
      (HWRESOURCE_FAMILY(HWRESOURCE_SPC58XG)) ||\
      (HWRESOURCE_FAMILY(HWRESOURCE_SPC58XH)))

#define SYST_MC_DES_REG_OFFSET                                            0x00UL
#define SYST_MC_FPOR                                                0x00000001UL
#define SYST_MC_FPORST                                              0x00000002UL
#define SYST_MC_FSOFT_DEST                                          0x00000008UL
#define SYST_MC_FFFRR                                               0x00000010UL
#define SYST_MC_FSUF                                                0x00000020UL
#define SYST_MC_FEDR                                                0x00000100UL
#define SYST_MC_FFIF                                                0x00000200UL
#define SYST_MC_FJTAGDEST                                           0x00000400UL
#define SYST_MC_FSSCMDEST                                           0x00004000UL
#define SYST_MC_FHSMDEST                                            0x00008000UL
#define SYST_MC_FTSRDEST                                            0x00800000UL
#define SYST_MC_FVORDEST                                            0x01000000UL
#define SYST_MC_FVORSTDBY                                           0x02000000UL

/* 0x0380C73BUL */
#define SYST_MC_FALLDES \
                                                      ((SYST_MC_FPOR      ) | \
                                                      (SYST_MC_FSOFT_DEST ) | \
                                                      (SYST_MC_FFFRR      ) | \
                                                      (SYST_MC_FSUF       ) | \
                                                      (SYST_MC_FEDR       ) | \
                                                      (SYST_MC_FFIF       ) | \
                                                      (SYST_MC_FJTAGDEST  ) | \
                                                      (SYST_MC_FSSCMDEST  ) | \
                                                      (SYST_MC_FHSMDEST   ) | \
                                                      (SYST_MC_FTSRDEST   ) | \
                                                      (SYST_MC_FVORDEST   ) | \
                                                      (SYST_MC_FVORSTDBY  ))

#define SYST_MC_REG(SYST_MC_REG_OFFSET)     \
  *(uint32 *)((MC_RGM_BASEADDR + SYST_MC_REG_OFFSET))

#define SYST_MC_POWER_ON_START()             \
  ((SYST_MC_REG(SYST_MC_DES_REG_OFFSET) & SYST_MC_FALLDES))

#define MC_ME_MCTL                   (*(volatile uint32 *) (MC_ME_BASEADDR + 0x004UL))

#endif /* #if (HWRESOURCE_FAMILY(HWRESOURCE_SPC58XC)) */

#if ((HWRESOURCE_FAMILY(HWRESOURCE_CYT2BXX)) ||\
     (HWRESOURCE_FAMILY(HWRESOURCE_CYT3BXX)) ||\
     (HWRESOURCE_FAMILY(HWRESOURCE_CYT4BXX)) ||\
     (HWRESOURCE_FAMILY(HWRESOURCE_CYT6BXX)))
#define CYTXXX_SRSS_RES_CAUSE                  (0x40260000UL + 0x00001800)
/* 0x40260000 */
#define CYTXXX_SRSS                 ((volatile uint32*) CYTXXX_SRSS_RES_CAUSE)
/** The CPU requested a system reset through it's SYSRESETREQ. This can be done via a debugger probe or in firmware. */
#define CY_SYSRESET_SOFT                (0x00000010u)
#define CY_SYSRESET_MASK                (0x00000010u)

#define CYTXXX_SCB_AIRCR            ((volatile uint32*) (0xE000E000UL + 0x0D00UL + 0x00C))
#define SCB_AIRCR_VECTKEY_Pos              16U
#define SCB_AIRCR_PRIGROUP_Pos              8U                                            /*!< SCB AIRCR: PRIGROUP Position */
#define SCB_AIRCR_PRIGROUP_Msk             (7UL << SCB_AIRCR_PRIGROUP_Pos)                /*!< SCB AIRCR: PRIGROUP Mask */
#define SCB_AIRCR_SYSRESETREQ_Pos           2U                                            /*!< SCB AIRCR: SYSRESETREQ Position */
#define SCB_AIRCR_SYSRESETREQ_Msk          (1UL << SCB_AIRCR_SYSRESETREQ_Pos)             /*!< SCB AIRCR: SYSRESETREQ Mask */
#endif

#if (HWRESOURCE_MCU(HWRESOURCE_RH850F1KM))
#define SYST_MC_SOFT_RESET_ON_START()             \
  ((RESFREG.ulRESF & (uint32)0x00000001) == (uint32)0x00000001)

/* protected write register */
#define protected_write(preg,pstatus,reg,value)   do{\
                                                  (preg)=0xa5u;\
                                                  (reg)=(value);\
                                                  (reg)=~(value);\
                                                  (reg)=(value);\
                                                  }while((pstatus)==1u)
#endif /* #if (HWRESOURCE_MCU(HWRESOURCE_RH850F1KM)) */

#if ((HWRESOURCE_MCU(HWRESOURCE_RH850F1K)) |\
     (HWRESOURCE_MCU(HWRESOURCE_RH850F1L)))

#define SWRESA  (*((volatile unsigned long*)0xFFF80A04))
#define PROTCMD0  (*((volatile unsigned long*)0xFFF80000))
#define RESF  (*((volatile unsigned long*)0xFFF80760))
#define SYST_MC_POWER_ON_START_F1X()          (( RESF & 0x200UL) == 0x200UL)

#endif

/* RSA public key modulus length */
#define SEC_RSA_PUBLIC_KEY_MODULUS_LENGTH                                 (256U)

#define FBL_SIGN_ASIMS_DELIMITER_NUM                                         (8)
#define FBL_SIGN_FST_DELIMITER_NUM                                          (10)

/* HSM Version of SecureBoot for FOTA */
#define FOTA_SUP_HSM_VER                                           (0x00020800UL)

typedef enum
{
  FOTA_STD_ADDR_CALL_OUT = 0x00U,
  FOTA_ALT_ADDR_CALL_OUT = 0x01U
} Fota_HwSpSvAddrType_CallOut;

typedef enum
{
  /* The last job has been finished successfully */
  FOTA_JOB_OK_CALL_OUT = 0x00U,
  /* A job is currently being processed */
  FOTA_JOB_PENDING_CALL_OUT,
  /* Job failed for some unspecific reason */
  FOTA_JOB_FAILED_CALL_OUT
} Fota_JobResultType_CallOut;

/* Asynchronous job result type */
typedef enum
{
  /* The last job has been finished successfully */
  MEM_JOB_OK_CALL_OUT = 0x00U,
  /* A job is currently being processed */
  MEM_JOB_PENDING_CALL_OUT,
  /* Job failed for some unspecific reason */
  MEM_JOB_FAILED_CALL_OUT,
  /* The checked page is not blank */
  MEM_INCONSISTENT_CALL_OUT,
  /* Uncorrectable ECC errors occurred during memory access */
  MEM_ECC_UNCORRECTED_CALL_OUT,
  /* Correctable ECC errors occurred during memory access */
  MEM_ECC_CORRECTED_CALL_OUT
} Mem_76_Pfls_JobResultType_CallOut;

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
extern const uint8 Fota_MetadataBlock_Length_64[4];
extern const uint8 Fota_MetadataBlock_Length_32[1];
extern const uint8 Fota_MetadataBlock_Delimiter[4];

extern const uint8 Sec_Gau8_Signature_Length[4];
extern const uint8 Sec_Gau8_Asims_Delimiter[FBL_SIGN_ASIMS_DELIMITER_NUM][4];
extern const uint8 Sec_Gau8_Fst_Delimiter[FBL_SIGN_FST_DELIMITER_NUM][4];
extern const uint8 Fota_Sec_Gau8_ImageServPubKeyAsims[
	                                   SEC_RSA_PUBLIC_KEY_MODULUS_LENGTH + 4U];
extern const uint8 Fota_Sec_Gau8_ImageServPubKeyFst[
	                                   SEC_RSA_PUBLIC_KEY_MODULUS_LENGTH + 4U];
extern const uint16 Fota_Gau16_CRCA001_8[256];



extern FUNC(void, FOTA_CODE) Fota_S32k3_Hse_Psk_injection(void);

extern FUNC(Fota_JobResultType_CallOut, FOTA_CODE) Fota_S32k3_SecureBootProcess(void);

extern FUNC(Std_ReturnType, FOTA_CODE) Fota_DecryptStart_Callout
(
  P2CONST(uint8, AUTOMATIC, FOTA_CODE) iv,
  P2CONST(uint8, AUTOMATIC, FOTA_CODE) firmwareKey,
  CONST(uint8, AUTOMATIC) firmwareKeyLen,
  P2CONST(uint8, AUTOMATIC, FOTA_CODE) macOfFirmwareKey,
  P2CONST(uint8, AUTOMATIC, FOTA_CODE) macKey,
  CONST(uint8, AUTOMATIC) macKeyLen
);
extern FUNC(Std_ReturnType, FOTA_CODE) Fota_DecryptUpdate_Callout
(
  P2VAR(uint8, AUTOMATIC, FOTA_CODE) output,
  P2CONST(uint8, AUTOMATIC, FOTA_CODE) input,
  CONST(uint32, AUTOMATIC) dataLen
);
extern FUNC(Std_ReturnType, FOTA_CODE) Fota_DecryptFinish_Callout
(
  P2VAR(uint32, AUTOMATIC, FOTA_CODE) totalLen
);

extern FUNC(Std_ReturnType, FOTA_CODE) Fota_DeriveKeyRequest_Callout
(
  uint8 *Lpu8_MetaDataBuffer,
  uint8 MDBlockId,
  uint32 KDFKeyId,
  uint32 KDFResultKeyId,
  uint32 Csm_Meta_Header_Length,
  uint32 Csm_Meta_SK_Length
);

extern FUNC(Std_ReturnType, FOTA_CODE) Fota_IsWarmReset(void);

extern FUNC(void, FOTA_CODE) Fota_RequestReset(void);

extern FUNC(uint16, FOTA_CODE) Fota_OutDelayTime_Callout(void);

extern FUNC(Std_ReturnType, FOTA_CODE) Fota_DualMemDownGradeChk_Callout(void);

extern FUNC(Std_ReturnType, FOTA_CODE) Fota_DualMemSwUnitsVerDependChk_Callout(void);

extern FUNC(Std_ReturnType, FOTA_CODE) Fota_SvcCheckVersion(uint8 *newVer, uint8 lengthNewVer,
                                           uint8 *currentVersion, uint8 lengthCurrent);

extern FUNC(void, FOTA_CODE) Fota_DestructiveResetSet(void);

extern FUNC(Fota_JobResultType_CallOut, FOTA_CODE) Fota_SecureBootMacUpdate(void);

extern FUNC(void, FOTA_CODE) Fota_BeforeFlashReadFunc(void);

extern FUNC(void, FOTA_CODE) Fota_AfterFlashReadFunc(void);


extern FUNC (Std_ReturnType, FOTA_CODE) Fota_ProcessReadActiveArea_UserCallout
(
  VAR(uint16, AUTOMATIC) InEcuSwUnit,
  VAR(uint8, AUTOMATIC) OpStatus,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpOut_MemoryArea,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpErrorCode
);

extern FUNC (Std_ReturnType, FOTA_CODE) Fota_ProcessActivate_UserCallout
(
  VAR(uint8, AUTOMATIC) InMemArea,
  VAR(uint16, AUTOMATIC) InEcuSwUnit,
  VAR(uint8, AUTOMATIC) OpStatus,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpErrorCode
);

extern FUNC (Std_ReturnType, FOTA_CODE) Fota_ProcessEraseTargetArea_UserCallout
(
  VAR(uint8, AUTOMATIC) InMemArea,
  VAR(uint16, AUTOMATIC) InEcuSwUnit,
  VAR(uint8, AUTOMATIC) OpStatus,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpOut_MemoryArea,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpErrorCode
);

extern FUNC(Std_ReturnType, FOTA_CODE) Fota_ProcessRequestDownload_UserCallout
(
  Dcm_OpStatusType OpStatus,
  uint8 DataFormatIdentifier,
  uint32 MemoryAddress,
  uint32 MemorySize,
  P2VAR(uint32, AUTOMATIC, FOTA_PRIVATE_DATA) LpBlockLength,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpErrorCode
);

extern FUNC(Dcm_ReturnWriteMemoryType, FOTA_CODE) Fota_ProcessTransferDataWrite_UserCallout
(
  Dcm_OpStatusType OpStatus,
  uint8 MemoryIdentifier /* Not Supported Argument */,
  uint32 MemoryAddress,
  uint32 MemoryWriteLen,
  P2CONST(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) pWriteData
);

extern FUNC (Std_ReturnType, FOTA_CODE) Fota_ProcessRequestTransferExit_UserCallout
(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpMemoryData,
  uint32* LulParameterRecordSize,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, FOTA_PRIVATE_DATA)LpErrorCode
);

extern FUNC (Std_ReturnType, FOTA_CODE) Fota_ProcessVerify_UserCallout
(
  VAR(uint8, AUTOMATIC) InMemArea,
  VAR(uint16, AUTOMATIC) InEcuSwUnit,
  VAR(uint8, AUTOMATIC) OpStatus,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpOut_MemoryArea,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpErrorCode
);

extern FUNC (Std_ReturnType, FOTA_CODE) Fbl_SelectEntryPoint
(
  P2VAR(uint32, AUTOMATIC, FOTA_PRIVATE_DATA) Lu32_EntryPointAddress
);

/* Start Pfls user callout */
extern FUNC (void, FOTA_CODE) Fota_PflsInit_UserCallout
(
  P2VAR(boolean, AUTOMATIC, FOTA_PRIVATE_DATA) pPflsUserCalloutUse
);

extern FUNC (void, FOTA_CODE) Fota_PflsDeinit_UserCallout
(
  void
);

extern FUNC (Std_ReturnType, FOTA_CODE) Fota_PflsCancelReq_UserCallout
(
  VAR(uint32, AUTOMATIC) rul_MemoryInstance
);

extern FUNC(Std_ReturnType, FOTA_CODE) Fota_PflsEraseRequest_UserCallout
(
  VAR(uint32, AUTOMATIC) In_MemoryArea,
  VAR(uint32, AUTOMATIC) areaAddress,
  VAR(uint32, AUTOMATIC) eraseLen
);

extern FUNC(Std_ReturnType, FOTA_CODE) Fota_PflsWriteRequest_UserCallout
(
  VAR(uint32, AUTOMATIC) In_MemoryArea,
  VAR(uint32, AUTOMATIC) rul_WriteStartAddr,
  P2CONST(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) rup_Write_buff,
  VAR(uint32, AUTOMATIC) rul_write_size
);

extern FUNC (Std_ReturnType, FOTA_CODE) Fota_PflsReadRequest_UserCallout
(
  VAR(uint32, AUTOMATIC) In_MemoryArea,
  VAR(uint32, AUTOMATIC) rul_ReadStartAddr,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) rup_Read_buff,
  VAR(uint32, AUTOMATIC) rul_read_size
);

extern FUNC (Std_ReturnType, FOTA_CODE) Fota_PflsSwapBankRequest_UserCallout
(
  void
);

extern FUNC (Mem_76_Pfls_JobResultType_CallOut, FOTA_CODE) Fota_PflsGetJobResult_UserCallout
(
  VAR(uint32, AUTOMATIC) In_MemoryArea
);

extern FUNC (Std_ReturnType, FOTA_CODE) Fota_PflsGetActiveBank_UserCallout
(
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) pReadBank
);

extern FUNC (Std_ReturnType, FOTA_CODE) Fota_PflsGetCovAddr_UserCallout
(
  VAR(uint32, AUTOMATIC) rul_MemoryInstance,
  VAR(Fota_HwSpSvAddrType_CallOut, AUTOMATIC) ren_Fota_HwSpSvAddrType,
  P2VAR(uint32, AUTOMATIC, FOTA_PRIVATE_DATA) rup_StdAddr,
  P2VAR(uint32, AUTOMATIC, FOTA_PRIVATE_DATA) rup_length
);

extern FUNC (Std_ReturnType, FOTA_CODE) Fota_PflsTgtAreaSet_UserCallout
(
  VAR(uint32, AUTOMATIC) rul_MemoryInstance,
  VAR(Fota_HwSpSvAddrType_CallOut, AUTOMATIC) rue_HwSpSvAddrType
);

extern FUNC (Std_ReturnType, FOTA_CODE) Fota_PflsGetFlashAlignment_UserCallout
(
  VAR(uint32, AUTOMATIC) rul_MemoryInstance,
  P2VAR(uint32, AUTOMATIC, FOTA_PRIVATE_DATA) rup_AlineVal
);

extern FUNC (Std_ReturnType, FOTA_CODE) Fota_PflsGetSectorSize_UserCallout
(
  VAR(uint32, AUTOMATIC) rul_MemoryInstance,
  P2VAR(uint32, AUTOMATIC, FOTA_PRIVATE_DATA) rup_AlineVal,
  VAR(uint32, AUTOMATIC) address
);
/* End Pfls user callout */

#endif /* #ifdef FOTA_INTEGRATION_SINGLEMEM_PLATFORM */

#endif /* FOTA_USER_CALLOUTS_H */

/* polyspace-end MISRA-C3:20.9 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:D4.9,2.2 [Justified:Low] "use function like-macro for reduce execution time and stack" */
/* polyspace-end MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
* the register value can be read via the address" */
/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
