/*******************************************************************************
**                                                                            **
**  (C) 2022 HYUNDAI AUTOEVER Co., Ltd.                                       **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Fbl_Stub.h                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Header file of Fbl_SharedCfg.c                                **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     17-Nov-2022   LinhTT36     Initial version                       **
*******************************************************************************/
#ifndef FBL_STUB_H
#define FBL_STUB_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Fbl_SharedCfg.h"
/*******************************************************************************
**                      Macro definition                                     **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/


/* polyspace-begin MISRA-C3:D4.6 [Not a defect:Low] "No Impact of this rule violation" */
typedef struct
{
  unsigned int cul_StartAddr;
  unsigned int cul_EndAddr;
} T_BAIFT_TESTADDR;

typedef struct
{
  uint16 cuw_CrcValue;
  uint16 cuw_NumberOfCrcAreas;
  T_BAIFT_TESTADDR cs_Area[2];  /* The size of this structure is not relevant.   */
                                /* The real size is given by cuw_NumberOfCrcAreas */
} T_BAIFT_CRC;

typedef struct
{
  const unsigned int             ul_StartAddress;        /* Address of the first byte of the Area            */
  const unsigned int             ul_EndAddress;          /* Address of the last byte of the Area             */
  const void                     *pv_SKAddress;          /* Address of the Security Key of the Area (if any) */
  const void                     *pv_IdentificationArea; /* Address of the Identification (if any)           */
  const T_BAIFT_CRC              *ps_CRCArea;	           /* Address of the CRC structure (if any)            */
  const uint8                    ub_LogicalIdentifier;   /* Logical identifier                               */
  const uint8                    ub_AccessType;		       /* Access restrictions                              */
} T_BAIFT_SOFTWARE_MODULE;

typedef struct
{
  const uint16                   *pcauw_CRCA001_8;       /* Pointer to the CRC16 algorithm table */
  const T_BAIFT_SOFTWARE_MODULE  *pcs_SwMap;	           /* Pointer to the SW mapping Table */
  const uint8                    cub_NumberOfSwModules;  /* Number of entries in pcs_SwMap : not used */
  const uint8                    *pcs_Pubkey;            /* Pointer to the public key for secure access */
  const uint8                    *pcs_ImagePubkey;       /* Pointer to the public key for secure flash */
} T_BAIFT;
/* polyspace-end MISRA-C3:D4.6 [Not a defect:Low] "No Impact of this rule violation" */
/*******************************************************************************
**                      Macro definition                                     **
*******************************************************************************/




/* SetStartupCommand function */
#define bcore_SetStartupCommand                            Fbl_SetStartupCommand

/* GetProgConditions function */
#define bcore_GetProgConditions                     Fbl_GetProgConditionsAddress


#define FAR_DATA_REF
#define cas_FBL_BAIFT                         *((T_BAIFT *)FBL_SHARED_DATA_ADDR)
#define RESTART_BOOT_DIAG                            (FBL_STARTUP_COMMAND_VALUE)
#define ROMTST_USE_LP

#define STD_CLEAR                                                           (0U)




#endif
/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
