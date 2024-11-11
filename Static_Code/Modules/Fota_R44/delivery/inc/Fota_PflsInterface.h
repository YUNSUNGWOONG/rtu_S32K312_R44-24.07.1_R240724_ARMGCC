/*******************************************************************************
**                                                                            **
**  (C) 2021~2022 HYUNDAI AUTOEVER Co., Ltd.                                  **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Fota_Diag.c                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   :                                                               **
**                                                                            **
**  PURPOSE   :                                                               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     30-Mar-2022   jys          Initial version                       **
*******************************************************************************/

#ifndef FOTA_CODEFLASHINTERFACE_H
#define FOTA_CODEFLASHINTERFACE_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#include "Mem_76_Pfls.h"
/*******************************************************************************
**                      Types                                                 **
*******************************************************************************/

typedef enum
{
  CODEFLASH_DEINITIALIZED             = 0,
  CODEFLASH_INITIALIZED               = 1,
} CodeFlash_InitType;

#define FOTA_HWSPEC_BUFF_SIZE 16u
#define FOTA_PFLS_INT_ZERO    0u
#define FOTA_PFLS_INT_ONE     1u
#define FOTA_PFLS_INT_TWO     2u
#define FOTA_PFLS_INT_THREE   3u
#define FOTA_PFLS_INT_FOUR    4u

typedef enum
{
  FOTA_BANK_UNKNOWN = 0x00U,
  FOTA_BANK_A = 0x0AU,
  FOTA_BANK_B = 0x0BU
} Fota_HwSpSvBankType;

typedef enum
{
  FOTA_STD_ADDR = 0x00U,
  FOTA_ALT_ADDR = 0x01U
} Fota_HwSpSvAddrType;


typedef union
{

  uint8  rub_u8;
  uint16 ruw_u16;
  uint32 rul_u32;
  uint8  Bytes[FOTA_HWSPEC_BUFF_SIZE];

} Fota_HwSpSvBfType;

/*******************************************************************************
**                      Configure                                             **
*******************************************************************************/

/*******************************************************************************
**                      Macros                                                **
*******************************************************************************/

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/

extern FUNC(void, FOTA_CODE) Fota_PflsInit(void);
extern FUNC(void, FOTA_CODE) Fota_PflsDeinit(void);

extern FUNC(Std_ReturnType, FOTA_CODE) Fota_PflsCancelReq
(
	VAR(uint32, AUTOMATIC) rul_MemoryInstance
);

extern FUNC(Std_ReturnType, FOTA_CODE) Fota_PflsEraseRequest
(
  VAR(uint32, AUTOMATIC) In_MemoryArea,
  VAR(uint32, AUTOMATIC) areaAddress,
  VAR(uint32, AUTOMATIC) eraseLen
);

extern FUNC(Std_ReturnType, FOTA_CODE) Fota_PflsWriteRequest
(
  VAR(uint32, AUTOMATIC) In_MemoryArea,
  VAR(uint32, AUTOMATIC) rul_WriteStartAddr,
  P2CONST(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) rup_Write_buff,
  VAR(uint32, AUTOMATIC) rul_write_size
);

extern FUNC(Std_ReturnType, FOTA_CODE) Fota_PflsReadRequest
(
  VAR(uint32, AUTOMATIC) In_MemoryArea,
  VAR(uint32, AUTOMATIC) rul_ReadStartAddr,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) rup_Read_buff,
  VAR(uint32, AUTOMATIC) rul_read_size
);

extern FUNC(Std_ReturnType, FOTA_CODE) Fota_PflsSwapBankRequest
(
	void
);

extern FUNC(Mem_76_Pfls_JobResultType, FOTA_CODE) Fota_PflsGetJobResult
(
  VAR(uint32, AUTOMATIC) In_MemoryArea
);


extern FUNC(Std_ReturnType, FOTA_CODE) Fota_PflsGetActiveBank
(
	  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) pReadBank
);

extern FUNC(Std_ReturnType, FOTA_CODE) Fota_PflsGetCovAddr
(
	  VAR(uint32, AUTOMATIC) rul_MemoryInstance,
	  VAR(Fota_HwSpSvAddrType,AUTOMATIC) ren_Fota_HwSpSvAddrType,
	  P2VAR(uint32, AUTOMATIC, FOTA_PRIVATE_DATA) rup_StdAddr,
	  P2VAR(uint32, AUTOMATIC, FOTA_PRIVATE_DATA) rup_length
);

extern FUNC(Std_ReturnType, FOTA_CODE) Fota_PflsTgtAreaSet
(
	  VAR(uint32, AUTOMATIC) rul_MemoryInstance,
	  VAR(Fota_HwSpSvAddrType, AUTOMATIC) rue_HwSpSvAddrType
);

extern FUNC(Std_ReturnType, FOTA_CODE) Fota_PflsGetFlashAlignment
(
	  VAR(uint32, AUTOMATIC) rul_MemoryInstance,
	  P2VAR(uint32, AUTOMATIC, FOTA_PRIVATE_DATA) rup_AlineVal
);

extern FUNC(Std_ReturnType, FOTA_CODE) Fota_PflsGetSectorSize
(
  VAR(uint32, AUTOMATIC) rul_MemoryInstance,
  P2VAR(uint32, AUTOMATIC, FOTA_PRIVATE_DATA) rup_AlineVal,
  VAR(uint32, AUTOMATIC) address
);

#endif /* End FOTA_EXT_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
