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
**  SRC-MODULE: Os_Peripheral.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of Peripheral access functionality.                 **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/* @Trace: SRS_BSW_00003 SRS_BSW_00006 SRS_BSW_00007 SRS_BSW_00009 SRS_BSW_00301 SRS_BSW_00302 SRS_BSW_00305
 SRS_BSW_00415 SRS_BSW_00305 SRS_BSW_00307 SRS_BSW_00308 SRS_BSW_00310 SRS_BSW_00328 SRS_BSW_00441 */
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.5.3     16-Feb-2024   HG.Kim           Jira CP44-3828                    **
** 1.5.0     13-Sep-2023   HJ.Kim           Jira CP44-2965                    **
**            1-Sep-2023   HJ.Kim           Jira CP44-2528                    **
**           26-Jun-2023   HJ.Kim           Jira CP44-2459                    **
**           26-Apr-2023   SH.Yoo           Jira CP44-1987                    **
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.3     23-Dec-2021   DatNXT           R44-Redmine #22670                **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.0.6.0   23-Mar-2021   Thao             Redmine #18032                    **
** 1.0.5     23-Mar-2021   Thao             Redmine #18032 (1.0.6.0)          **
** 1.0.4     14-Sep-2020   TamNN1           R44-Redmine #15236 Fixed warning  **
**                                          when Compile with SIT and SQT     **
** 1.0.3     26-Aug-2020   TamNN1           R44-Redmine #12870                **
**                                          Add Comment Misra-C 11.4          **
** 1.0.2     25-Aug-2020   TamNN1           R44-Redmine #12870                **
**                                          Fixed Misra-C 15.7                **
** 1.0.1     14-Aug-2020   Thao             R44-Redmine #13463                **
**                                          Add SRS Traceability              **
** 1.0.0     15-Dec-2019   Paul             R44-Redmine #1505 Initial version **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin RTE:IDP [Not a defect:Low] "configured memory access index" */
/* polyspace-begin RTE:OBAI [Not a defect:Low] "configured array index" */
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-begin MISRA-C3:D4.1 [Justified:Low] "Ptr points to a valid value and code is verified manually" */
/* polyspace:begin<MISRA-C3:11.3:Not a defect:Justify with annotations> Cast is needed for implementation */
/* polyspace-begin MISRA-C3:18.1 [Justified:Low] "Array index has been configured inside bounds and code is verified manually" */
/* polyspace:begin<ISO-17961:intptrconv:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace:begin<CERT-C:EXP39-C:Not a defect:Justify with annotation> Pointer arithmatic used to achieve better throughput. */
/* polyspace:begin<CERT-C:INT36-C:Not a defect:Justify with annotation> This conversion cannot be modified to handle memory */
/* polyspace-begin DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
/* polyspace-begin CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
/* polyspace-begin MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_InternalTypes.h"     /* Os InternalTypes header file */
#include "Os_PortTypes.h"         /* Os PortTypes header file */
#include "Os_Ram.h"               /* Os Ram header file */
#include "Os_Kernel.h"            /* Os Kernel header file */
#include "Os_Error.h"             /* Os Error header file */
#include "Os_Peripheral.h"        /* Os Peripheral header file */
#include "Os_SystemCallTable.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* @Trace: SRS_BSW_00351 */
#define OS_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Os_KernReadPeripheral8                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service returns the content of a               **
**                        given memory location (<Address>).                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : Area, Address                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : ReadValue                                           **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Os_GddAppId, Os_GaaStaticPeripheralArea             **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11005 SRS_Os_11001 SRS_BSW_00410 */
#if ((OS_TRUSTED_START_INDX != OS_ZERO) && (OS_PERIPHERAL == STD_ON))
FUNC(StatusType, OS_CODE) Os_KernReadPeripheral8(AreaIdType Area,
                  P2CONST(uint8, AUTOMATIC, OS_CONST) Address, uint8* Readvalue)
{
    StatusType LenStatusReturn;
    P2CONST(uint32, AUTOMATIC, OS_CONST) LpBaseAddress;
    uint32 LulOffset;
    uint32 LpReadvalue;

    #if (OS_MULTICORE == STD_ON)
    CoreIDType OS_CORE_ID;
    #endif
    LenStatusReturn = E_OK;

    /* Get Core Id*/
    OS_GET_CORE_ID(OS_CORE_ID);
    #if (OS_STATUS == EXTENDED)
    /* Check for call level */
    OS_CHECK_E_OS_CALLEVEL(READPERIPHERAL, LenStatusReturn);
        /* Check for NULL_PTR */
    OS_CHECK_NULL_PTR(Address, LenStatusReturn);
        /* Check for NULL_PTR */
    OS_CHECK_NULL_PTR(Readvalue, LenStatusReturn);
    /* Check area ID */
    OS_CHECK_AREA_ID(Area, &LenStatusReturn);
    /* Check peripheral address */
    OS_CHECK_PERIPHERAL_ADDRESS((P2CONST(uint32, AUTOMATIC, OS_CONST))Address, &LenStatusReturn, OS_PERIPHERAL_UINT8);
    /* Check peripheral range */
    OS_CHECK_PERIPHERAL_AREA(Area,(P2CONST(uint32, AUTOMATIC, OS_CONST))Address, &LenStatusReturn, OS_PERIPHERAL_UINT8);
    /* polyspace +2 CERT-C:EXP39-C MISRA-C3:11.3 MISRA-C3:18.4 [Justified:Low] "Pointer arithmatic used to achieve better throughput." */
    /* Check NULL pointer */
    OS_CHECK_PERIPHERAL_READOUT_VALUE((uint32*)Readvalue, &LenStatusReturn);
    #endif
    /* Check peripheral access */
    /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "Area have been checked before using" */
    /* polyspace +1 RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
    OS_CHECK_PERIPHERAL_APPLICATION_ACCESS(LenStatusReturn, Area);
    if (LenStatusReturn == E_OK)
    {
      /* @Trace: SafeOs_SUD_API_16401 */
      /* Get the Base Address */
      /* polyspace-begin CERT-C:INT36-C [Justified:Low] "This conversion cannot be modified to handle memory" */
      /* polyspace +1 MISRA-C3:11.4 [Justified:Low] "The conversion to get the Base address and has no impact" */
      LpBaseAddress = (uint32 *) ((uint32)Address & OS_MASK_BASE_ADDRESS);
      /* polyspace-end CERT-C:INT36-C [Justified:Low] "This conversion cannot be modified to handle memory" */

      /* Get the Offset */
      /* polyspace +1 MISRA-C3:11.4 [Justified:Low] "The conversion to get the Offset of address and has no impact" */
      LulOffset = (uint32)Address & OS_MASK_OFFSET;

      /* polyspace +2 RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
      /* Return LpReadvalue of base address to local */
      LpReadvalue = *LpBaseAddress;
      /* Return Readvalue of point address*/
      /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "ptr Readvalue have been checked before using" */
      *Readvalue =(uint8) ((LpReadvalue) >> (LulOffset << OS_MASK_OFFSET));
    }
    #if (OS_STATUS == EXTENDED)
    else
    {
      /* @Trace: SafeOs_SUD_API_16402 */
      /* Store the service ID of ReadPeripheral8 */
      OS_STORE_SERVICE(OSServiceId_ReadPeripheral8);
      /* Store the parameter 1 - Area */
      OS_STORE_PARAM1_AREA(Area);
      /* Store the parameter 2 - Address */
      OS_STORE_PARAM2_READADDRESS((const uint32 *)Address);
      /* Store the parameter 3 - Readvalue */
      OS_STORE_PARAM3_READVALUE((uint32 *)Readvalue);
      /* Report an error to error hook */
      OS_PROCESS_ERROR(LenStatusReturn);
    } /* End of else */
    #endif /* End of if (OS_STATUS == EXTENDED) */

    /* Return the value */
    return LenStatusReturn;
}
#endif

/*******************************************************************************
** Function Name        : Os_KernReadPeripheral16                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service returns the content of a               **
**                        given memory location (<Address>).                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : Area, Address                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : ReadValue                                           **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Os_GddAppId, Os_GaaStaticPeripheralArea             **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11005 SRS_Os_11001 SRS_BSW_00410 */
#if ((OS_TRUSTED_START_INDX != OS_ZERO) && (OS_PERIPHERAL == STD_ON))
FUNC(StatusType, OS_CODE) Os_KernReadPeripheral16(AreaIdType Area,
                P2CONST(uint16, AUTOMATIC, OS_CONST) Address, uint16* Readvalue)
{
    StatusType LenStatusReturn;
    P2CONST(uint32, AUTOMATIC, OS_CONST) LpBaseAddress;
    uint32 LulOffset;
    uint32 LpReadvalue;

    #if (OS_MULTICORE == STD_ON)
    CoreIDType OS_CORE_ID;
    #endif
    LenStatusReturn = E_OK;

    /* Get Core Id*/
    OS_GET_CORE_ID(OS_CORE_ID);
    #if (OS_STATUS == EXTENDED)
    /* Check for call level */
    OS_CHECK_E_OS_CALLEVEL(READPERIPHERAL, LenStatusReturn);
        /* Check for NULL_PTR */
    OS_CHECK_NULL_PTR(Address, LenStatusReturn);
        /* Check for NULL_PTR */
    OS_CHECK_NULL_PTR(Readvalue, LenStatusReturn);
    /* Check area ID */
    OS_CHECK_AREA_ID(Area, &LenStatusReturn);
    /* Check peripheral address */
    OS_CHECK_PERIPHERAL_ADDRESS((P2CONST(uint32, AUTOMATIC, OS_CONST))Address, &LenStatusReturn, OS_PERIPHERAL_UINT16);
    /* Check peripheral range */
    OS_CHECK_PERIPHERAL_AREA(Area, (P2CONST(uint32, AUTOMATIC, OS_CONST))Address, &LenStatusReturn, OS_PERIPHERAL_UINT16);
    /* Check NULL pointer */
    /* polyspace +1 CERT-C:EXP39-C MISRA-C3:11.3 MISRA-C3:18.4 [Justified:Low] "Pointer arithmatic used to achieve better throughput." */
    OS_CHECK_PERIPHERAL_READOUT_VALUE((uint32*)Readvalue, &LenStatusReturn);
    #endif
    /* Check peripheral access */
    /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "Area have been checked before using" */
    /* polyspace +1 RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
    OS_CHECK_PERIPHERAL_APPLICATION_ACCESS(LenStatusReturn, Area);
    if (LenStatusReturn == E_OK)
    {
      /* @Trace: SafeOs_SUD_API_55701 */
      /* Get the Base Address */
      /* polyspace +1 MISRA-C3:11.4 CERT-C:INT36-C [Justified:Low] "The conversion to get the Base address and has no impact" */
      LpBaseAddress = (uint32 *) ((uint32)Address & OS_MASK_BASE_ADDRESS);

      /* Get the Offset */
      /* polyspace +1 MISRA-C3:11.4 [Justified:Low] "The conversion to get the Offset of address and has no impact" */
      LulOffset = (uint32)Address & OS_MASK_OFFSET;

      /* polyspace +2 RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
      /* Return LpReadvalue of base address to local */
      LpReadvalue = *LpBaseAddress;
      /* Return Readvalue of point address*/
      /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "ptr Readvalue have been checked before using" */
      *Readvalue = (uint16)((LpReadvalue) >> (LulOffset << OS_MASK_OFFSET));
    }
    #if (OS_STATUS == EXTENDED)
    else
    {
      /* @Trace: SafeOs_SUD_API_55702 */
      /* Store the service ID of ReadPeripheral16 */
      OS_STORE_SERVICE(OSServiceId_ReadPeripheral16);
      /* Store the parameter 1 - Area */
      OS_STORE_PARAM1_AREA(Area);
      /* Store the parameter 2 - Address */
      /* polyspace +1 CERT-C:EXP39-C MISRA-C3:11.3 MISRA-C3:18.4 [Justified:Low] "Pointer arithmatic used to achieve better throughput." */
      OS_STORE_PARAM2_READADDRESS((const uint32 *)Address);
      /* Store the parameter 3 - Readvalue */
      OS_STORE_PARAM3_READVALUE((uint32 *)Readvalue);
      /* Report an error to error hook */
      OS_PROCESS_ERROR(LenStatusReturn);
    } /* End of else */
    #endif /* End of if (OS_STATUS == EXTENDED) */

    /* Return the value */
    return LenStatusReturn;
}
#endif

/*******************************************************************************
** Function Name        : Os_KernReadPeripheral32                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service returns the content of a               **
**                        given memory location (<Address>).                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : Area, Address                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : ReadValue                                           **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Os_GddAppId, Os_GaaStaticPeripheralArea             **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11005 SRS_Os_11001 SRS_BSW_00410 */
#if ((OS_TRUSTED_START_INDX != OS_ZERO) && (OS_PERIPHERAL == STD_ON))
FUNC(StatusType, OS_CODE) Os_KernReadPeripheral32(AreaIdType Area,
                P2CONST(uint32, AUTOMATIC, OS_CONST) Address, uint32* Readvalue)
{
    StatusType LenStatusReturn;
    P2CONST(uint32, AUTOMATIC, OS_CONST) LpBaseAddress;
    uint32 LulOffset;
    uint32 LpReadvalue;

    #if (OS_MULTICORE == STD_ON)
    CoreIDType OS_CORE_ID;
    #endif
    LenStatusReturn = E_OK;

    /* Get Core Id*/
    OS_GET_CORE_ID(OS_CORE_ID);
    #if (OS_STATUS == EXTENDED)
    /* Check for call level */
    OS_CHECK_E_OS_CALLEVEL(READPERIPHERAL, LenStatusReturn);
        /* Check for NULL_PTR */
    OS_CHECK_NULL_PTR(Address, LenStatusReturn);
        /* Check for NULL_PTR */
    OS_CHECK_NULL_PTR(Readvalue, LenStatusReturn);
    /* Check area ID */
    OS_CHECK_AREA_ID(Area, &LenStatusReturn);
    /* Check peripheral address */
    OS_CHECK_PERIPHERAL_ADDRESS((P2CONST(uint32, AUTOMATIC, OS_CONST))Address, &LenStatusReturn, OS_PERIPHERAL_UINT32);
    /* Check peripheral range */
    OS_CHECK_PERIPHERAL_AREA(Area, (P2CONST(uint32, AUTOMATIC, OS_CONST))Address, &LenStatusReturn, OS_PERIPHERAL_UINT32);
    /* Check NULL pointer */
    OS_CHECK_PERIPHERAL_READOUT_VALUE((uint32*)Readvalue, &LenStatusReturn);
    #endif
    /* Check peripheral access */
    /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "Area have been checked before using" */
    /* polyspace +1 RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
    OS_CHECK_PERIPHERAL_APPLICATION_ACCESS(LenStatusReturn, Area);
    if (LenStatusReturn == E_OK)
    {
      /* @Trace: SafeOs_SUD_API_55801 */
      /* Get the Base Address */
      /* polyspace +1 MISRA-C3:11.4 CERT-C:INT36-C [Justified:Low] "The conversion to get the Base address and has no impact" */
      LpBaseAddress = (uint32 *) ((uint32)Address & OS_MASK_BASE_ADDRESS);

      /* Get the Offset */
      /* polyspace +1 MISRA-C3:11.4 [Justified:Low] "The conversion to get the Offset of address and has no impact" */
      LulOffset = (uint32)Address & OS_MASK_OFFSET;

      /* polyspace +2 RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
      /* Return LpReadvalue of base address to local */
      LpReadvalue = *LpBaseAddress;
      /* Return Readvalue of point address*/
      /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "ptr Readvalue have been checked before using" */
      *Readvalue = ((LpReadvalue) >> (LulOffset << OS_MASK_OFFSET));

      /* @Trace: SafeOs_SUD_API_55802 */
      *Readvalue = LpReadvalue;
    }
    #if (OS_STATUS == EXTENDED)
    else
    {
      /* @Trace: SafeOs_SUD_API_55803 */
      /* Store the service ID of ReadPeripheral32 */
      OS_STORE_SERVICE(OSServiceId_ReadPeripheral32);
      /* Store the parameter 1 - Area */
      OS_STORE_PARAM1_AREA(Area);
      /* Store the parameter 2 - Address */
      OS_STORE_PARAM2_READADDRESS(Address);
      /* Store the parameter 3 - Readvalue */
      OS_STORE_PARAM3_READVALUE(Readvalue);
      /* Report an error to error hook */
      OS_PROCESS_ERROR(LenStatusReturn);
    } /* End of else */
    #endif /* End of if (OS_STATUS == EXTENDED) */

    /* Return the value */
    return LenStatusReturn;
}
#endif

/*******************************************************************************
** Function Name        : Os_KernWritePeripheral8                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service writes the <value> to a given          **
**                        memory location (<memory address>).                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : Area, Address                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : WriteValue                                          **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Os_GddAppId, Os_GaaStaticPeripheralArea             **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11005 */
#if ((OS_TRUSTED_START_INDX != OS_ZERO) && (OS_PERIPHERAL == STD_ON))
/* polyspace +2 MISRA-C3:8.13 [Not a defect:Low] "Write memory address to allocate memory location" */
FUNC(StatusType, OS_CODE) Os_KernWritePeripheral8(AreaIdType Area,
                      P2VAR(uint8, AUTOMATIC, OS_VAR) Address, uint8 WriteValue)
{
    StatusType LenStatusReturn;
    P2VAR(uint32, AUTOMATIC, OS_VAR) LpBaseAddress;
    uint32 LulOffset;
    uint32 LulWriteValue;
    uint32 LpMaskWriteValue;

    #if (OS_MULTICORE == STD_ON)
    CoreIDType OS_CORE_ID;
    #endif
    LenStatusReturn = E_OK;

    /* Get Core Id*/
    OS_GET_CORE_ID(OS_CORE_ID);
    #if (OS_STATUS == EXTENDED)
    /* Check for call level */
    OS_CHECK_E_OS_CALLEVEL(WRITEPERIPHERAL, LenStatusReturn);
    /* Check area ID */
    OS_CHECK_AREA_ID(Area, &LenStatusReturn);
    /* Check peripheral address */
    OS_CHECK_PERIPHERAL_ADDRESS((P2VAR(uint32, AUTOMATIC, OS_VAR))Address, &LenStatusReturn, OS_PERIPHERAL_UINT8);
    /* Check peripheral range */
    OS_CHECK_PERIPHERAL_AREA(Area,(P2VAR(uint32, AUTOMATIC, OS_VAR))Address, &LenStatusReturn, OS_PERIPHERAL_UINT8);
    #endif
    /* polyspace +3 MISRA-C3:D4.14 [Justified:Low] "CoreID have been checked before using" */
    /* polyspace +2 RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
    /* Check peripheral access */
    OS_CHECK_PERIPHERAL_APPLICATION_ACCESS(LenStatusReturn, Area);

    if (LenStatusReturn == E_OK)
    {
      /* @Trace: SafeOs_SUD_API_16501 */
      /* Get the Base Address */
      /* polyspace-begin CERT-C:INT36-C [Justified:Low] "This conversion cannot be modified to handle memory" */
      /* polyspace +1 MISRA-C3:11.4 [Justified:Low] "The conversion to get the Base address and has no impact" */
      LpBaseAddress = (uint32 *) ((uint32)Address & OS_MASK_BASE_ADDRESS);
      /* polyspace-end CERT-C:INT36-C [Justified:Low] "This conversion cannot be modified to handle memory" */

      /* Get the Offset */
      /* polyspace +1 MISRA-C3:11.4 [Justified:Low] "The conversion to get the Offset of address and has no impact" */
      LulOffset = (uint32)Address & OS_MASK_OFFSET;

      /* Move WriteValue to point address update */
      LulWriteValue = (uint32)((uint32)(WriteValue) << (LulOffset << OS_MASK_OFFSET));

      /* @Trace: SafeOs_SUD_API_16502 */
      /* Initialize first peripheral block for writing */
      LpMaskWriteValue = OS_MASK_PERIPHERAL_8BIT;

      /* Shift to the Peripheral block need to write */
      LpMaskWriteValue = LpMaskWriteValue << (LulOffset * OS_MASK_PERIPHERAL_SUB_BLOCKZIZE);
      /* polyspace +2 RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
      /* Update mask before write */
      LpMaskWriteValue = ~LpMaskWriteValue;
      /* polyspace +2 RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
      /* Write WriteValue to the expected address */
      *LpBaseAddress = (((*LpBaseAddress) & LpMaskWriteValue)|LulWriteValue);
    }
    #if (OS_STATUS == EXTENDED)
    else
    {
      /* @Trace: SafeOs_SUD_API_16503 */
      /* Store the service ID of WritePeripheral8 */
      OS_STORE_SERVICE(OSServiceId_WritePeripheral8);
      /* Store the parameter 1 - Area */
      OS_STORE_PARAM1_AREA(Area);
      /* Store the parameter 2 - Address */
      OS_STORE_PARAM2_WRITEADDRESS((P2VAR(uint32, AUTOMATIC, OS_VAR))Address);
      /* Store the parameter 3 - WriteValue */
      OS_STORE_PARAM3_WRITEVALUE(WriteValue);
      /* Report an error to error hook */
      OS_PROCESS_ERROR(LenStatusReturn);
    } /* End of else */
    #endif /* End of if (OS_STATUS == EXTENDED) */

    /* Return the value */
    return LenStatusReturn;
}
#endif

/*******************************************************************************
** Function Name        : Os_KernWritePeripheral16                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service writes the <value> to a given          **
**                        memory location (<memory address>).                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : Area, Address                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : WriteValue                                          **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Os_GddAppId, Os_GaaStaticPeripheralArea             **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11005 */
#if ((OS_TRUSTED_START_INDX != OS_ZERO) && (OS_PERIPHERAL == STD_ON))
/* polyspace +2 MISRA-C3:8.13 [Not a defect:Low] "Write memory address to allocate memory location" */
FUNC(StatusType, OS_CODE) Os_KernWritePeripheral16(AreaIdType Area,
                    P2VAR(uint16, AUTOMATIC, OS_VAR) Address, uint16 WriteValue)
{
    StatusType LenStatusReturn;
    P2VAR(uint32, AUTOMATIC, OS_VAR) LpBaseAddress;
    uint32 LulOffset;
    uint32 LulWriteValue;
    uint32 LpMaskWriteValue;

    #if (OS_MULTICORE == STD_ON)
    CoreIDType OS_CORE_ID;
    #endif
    LenStatusReturn = E_OK;

    /* Get Core Id*/
    OS_GET_CORE_ID(OS_CORE_ID);
    #if (OS_STATUS == EXTENDED)
    /* Check for call level */
    OS_CHECK_E_OS_CALLEVEL(WRITEPERIPHERAL, LenStatusReturn);
    /* Check area ID */
    OS_CHECK_AREA_ID(Area, &LenStatusReturn);
    /* Check peripheral address */
    OS_CHECK_PERIPHERAL_ADDRESS((P2VAR(uint32, AUTOMATIC, OS_VAR))Address, &LenStatusReturn, OS_PERIPHERAL_UINT16);
    /* Check peripheral range */
    /* polyspace +1 CERT-C:EXP39-C MISRA-C3:11.3 MISRA-C3:18.4 [Justified:Low] "Pointer arithmatic used to achieve better throughput." */
    OS_CHECK_PERIPHERAL_AREA(Area, (P2VAR(uint32, AUTOMATIC, OS_VAR))Address, &LenStatusReturn, OS_PERIPHERAL_UINT16);
    #endif
    /* polyspace +3 MISRA-C3:D4.14 [Justified:Low] "CoreID have been checked before using" */
    /* polyspace +2 RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
    /* Check peripheral access */
    OS_CHECK_PERIPHERAL_APPLICATION_ACCESS(LenStatusReturn, Area);

    if (LenStatusReturn == E_OK)
    {
      /* @Trace: SafeOs_SUD_API_55901 */
      /* Get the Base Address */
      /* polyspace +1 MISRA-C3:11.4 CERT-C:INT36-C [Justified:Low] "The conversion to get the Base address and has no impact" */
      LpBaseAddress = (uint32 *) ((uint32)Address & OS_MASK_BASE_ADDRESS);

      /* Get the Offset */
      /* polyspace +1 MISRA-C3:11.4 [Justified:Low] "The conversion to get the Offset of address and has no impact" */
      LulOffset = (uint32)Address & OS_MASK_OFFSET;

      /* Move WriteValue to point address update */
      LulWriteValue = (uint32)((uint32)(WriteValue) << (LulOffset << OS_MASK_OFFSET));

      /* @Trace: SafeOs_SUD_API_55902 */
      /* Initialize first peripheral block for writing */
      LpMaskWriteValue = OS_MASK_PERIPHERAL_16BIT;

      /* Shift to the Peripheral block need to write */
      LpMaskWriteValue = LpMaskWriteValue << (LulOffset * OS_MASK_PERIPHERAL_SUB_BLOCKZIZE);

      /* Update mask before write */
      LpMaskWriteValue = ~LpMaskWriteValue;
      /* polyspace +2 RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
      /* Write WriteValue to the expected address */
      *LpBaseAddress = (((*LpBaseAddress) & LpMaskWriteValue)|LulWriteValue);
    }
    #if (OS_STATUS == EXTENDED)
    else
    {
      /* @Trace: SafeOs_SUD_API_55903 */
      /* Store the service ID of WritePeripheral16 */
      OS_STORE_SERVICE(OSServiceId_WritePeripheral16);
      /* Store the parameter 1 - Area */
      OS_STORE_PARAM1_AREA(Area);
      /* Store the parameter 2 - Address */
      OS_STORE_PARAM2_WRITEADDRESS((P2VAR(uint32, AUTOMATIC, OS_VAR))Address);
      /* Store the parameter 3 - WriteValue */
      OS_STORE_PARAM3_WRITEVALUE(WriteValue);
      /* Report an error to error hook */
      OS_PROCESS_ERROR(LenStatusReturn);
    } /* End of else */
    #endif /* End of if (OS_STATUS == EXTENDED) */

    /* Return the value */
    return LenStatusReturn;
}
#endif

/*******************************************************************************
** Function Name        : Os_KernWritePeripheral32                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service writes the <value> to a given          **
**                        memory location (<memory address>).                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : Area, Address                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : WriteValue                                          **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Os_GddAppId, Os_GaaStaticPeripheralArea             **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11005 */
#if ((OS_TRUSTED_START_INDX != OS_ZERO) && (OS_PERIPHERAL == STD_ON))
/* polyspace +2 MISRA-C3:8.13 [Not a defect:Low] "Write memory address to allocate memory location" */
FUNC(StatusType, OS_CODE) Os_KernWritePeripheral32(AreaIdType Area,
                    P2VAR(uint32, AUTOMATIC, OS_VAR) Address, uint32 WriteValue)
{
    StatusType LenStatusReturn;
    P2VAR(uint32, AUTOMATIC, OS_VAR) LpBaseAddress;
    uint32 LulOffset;
    uint32 LulWriteValue;

    #if (OS_MULTICORE == STD_ON)
    CoreIDType OS_CORE_ID;
    #endif
    LenStatusReturn = E_OK;

    /* Get Core Id*/
    OS_GET_CORE_ID(OS_CORE_ID);
    #if (OS_STATUS == EXTENDED)
    /* Check for call level */
    OS_CHECK_E_OS_CALLEVEL(WRITEPERIPHERAL, LenStatusReturn);
    /* Check area ID */
    OS_CHECK_AREA_ID(Area, &LenStatusReturn);
    /* Check peripheral address */
    OS_CHECK_PERIPHERAL_ADDRESS(Address, &LenStatusReturn, OS_PERIPHERAL_UINT32);
    /* Check peripheral range */
    OS_CHECK_PERIPHERAL_AREA(Area, Address, &LenStatusReturn, OS_PERIPHERAL_UINT32);
    #endif
    /* polyspace +3 MISRA-C3:D4.14 [Justified:Low] "CoreID have been checked before using" */
    /* polyspace +2 RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
    /* Check peripheral access */
    OS_CHECK_PERIPHERAL_APPLICATION_ACCESS(LenStatusReturn, Area);

    if (LenStatusReturn == E_OK)
    {
      /* @Trace: SafeOs_SUD_API_56001 */
      /* Get the Base Address */
      /* polyspace +1 MISRA-C3:11.4 CERT-C:INT36-C [Justified:Low] "The conversion to get the Base address and has no impact" */
      LpBaseAddress = (uint32 *) ((uint32)Address & OS_MASK_BASE_ADDRESS);

      /* Get the Offset */
      /* polyspace +1 MISRA-C3:11.4 [Justified:Low] "The conversion to get the Offset of address and has no impact" */
      LulOffset = (uint32)Address & OS_MASK_OFFSET;

      /* Move WriteValue to point address update */
      LulWriteValue = (uint32)((WriteValue) << (LulOffset << OS_MASK_OFFSET));

      /* @Trace: SafeOs_SUD_API_56002 */
      /* polyspace +2 RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
      /* Write WriteValue to the expected address */
      *LpBaseAddress = LulWriteValue;
    }
    #if (OS_STATUS == EXTENDED)
    else
    {
      /* @Trace: SafeOs_SUD_API_56003 */
      /* Store the service ID of WritePeripheral32 */
      OS_STORE_SERVICE(OSServiceId_WritePeripheral32);
      /* Store the parameter 1 - Area */
      OS_STORE_PARAM1_AREA(Area);
      /* Store the parameter 2 - Address */
      OS_STORE_PARAM2_WRITEADDRESS(Address);
      /* Store the parameter 3 - WriteValue */
      OS_STORE_PARAM3_WRITEVALUE(WriteValue);
      /* Report an error to error hook */
      OS_PROCESS_ERROR(LenStatusReturn);
    } /* End of else */
    #endif /* End of if (OS_STATUS == EXTENDED) */

    /* Return the value */
    return LenStatusReturn;
}
#endif

/*******************************************************************************
** Function Name        : Os_KernModifyPeripheral8                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service modifies a given memory location       **
**                        (<memory address>) with the formula:                **
**                       *<Address> = ((*<Address> & <clearmask>) | <setmask>)**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : Area, Address, Clearmask, Setmask                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Os_GddAppId, Os_GaaStaticPeripheralArea             **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11005 */
#if ((OS_TRUSTED_START_INDX != OS_ZERO) && (OS_PERIPHERAL == STD_ON))
/* polyspace +2 MISRA-C3:8.13 [Not a defect:Low] "Modify memory address to allocate memory location" */
FUNC(StatusType, OS_CODE) Os_KernModifyPeripheral8(AreaIdType Area,
        P2VAR(uint8, AUTOMATIC, OS_VAR) Address, uint8 Clearmask, uint8 Setmask)
{
    StatusType LenStatusReturn;
    P2VAR(uint32, AUTOMATIC, OS_CONST) LpBaseAddress;
    uint32 LulOffset;
    uint32 LulClearmask;
    uint32 LulSetmask;
    uint32 LpMaskAddress;

    #if (OS_MULTICORE == STD_ON)
    CoreIDType OS_CORE_ID;
    #endif
    LenStatusReturn = E_OK;

    /* Get Core Id*/
    OS_GET_CORE_ID(OS_CORE_ID);
    #if (OS_STATUS == EXTENDED)
    /* Check for call level */
    OS_CHECK_E_OS_CALLEVEL(MODIFYPERIPHERAL, LenStatusReturn);
    /* Check area ID */
    OS_CHECK_AREA_ID(Area, &LenStatusReturn);
    /* Check peripheral address */
    OS_CHECK_PERIPHERAL_ADDRESS((P2VAR(uint32, AUTOMATIC, OS_VAR))Address, &LenStatusReturn, OS_PERIPHERAL_UINT8);
    /* Check peripheral range */
    /* polyspace +1 CERT-C:EXP39-C MISRA-C3:11.3 MISRA-C3:18.4 [Justified:Low] "Pointer arithmatic used to achieve better throughput." */
    OS_CHECK_PERIPHERAL_AREA(Area, (P2VAR(uint32, AUTOMATIC, OS_VAR))Address, &LenStatusReturn, OS_PERIPHERAL_UINT8);
    #endif
    /* Check peripheral access */
    /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "Area have been checked before using" */
    /* polyspace +1 RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
    OS_CHECK_PERIPHERAL_APPLICATION_ACCESS(LenStatusReturn, Area);

    if (LenStatusReturn == E_OK)
    {
      /* @Trace: SafeOs_SUD_API_16601 */
      /* Get the Base Address */
      /* polyspace-begin CERT-C:INT36-C [Justified:Low] "This conversion cannot be modified to handle memory" */
      /* polyspace +1 MISRA-C3:11.4 [Justified:Low] "The conversion to get the Base address and has no impact" */
      LpBaseAddress = (uint32 *) ((uint32)Address & OS_MASK_BASE_ADDRESS);
      /* polyspace-end CERT-C:INT36-C [Justified:Low] "This conversion cannot be modified to handle memory" */

      /* Get the Offset */
      /* polyspace +1 MISRA-C3:11.4 [Justified:Low] "The conversion to get the Offset of address and has no impact" */
      LulOffset = (uint32)Address & OS_MASK_OFFSET;

      /* Move Clearmask to point address  */
      LulClearmask = (uint32)((uint32)(Clearmask) << (LulOffset << OS_MASK_OFFSET));
      /* Move Setmask to point address  */
      LulSetmask = (uint32)((uint32)(Setmask) << (LulOffset << OS_MASK_OFFSET));

      /* @Trace: SafeOs_SUD_API_16602 */
      /* Initialize first peripheral block for modifying */
      LpMaskAddress = OS_MASK_PERIPHERAL_8BIT;

      /* Shift to the Peripheral block need to write */
      LpMaskAddress = (uint32)LpMaskAddress << (LulOffset * OS_MASK_PERIPHERAL_SUB_BLOCKZIZE);

      /* Update mask before modify */
      LpMaskAddress = (~LpMaskAddress);

      /* Update LulClearmask for expected address */
      LulClearmask = (LulClearmask | LpMaskAddress);
      /* polyspace +2 RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
      /* Update to the expected address */
      *LpBaseAddress = (((*LpBaseAddress) & LulClearmask) | LulSetmask);
    }
    #if (OS_STATUS == EXTENDED)
    else
    {
      /* @Trace: SafeOs_SUD_API_16603 */
      /* Store the service ID of ModifyPeripheral8 */
      OS_STORE_SERVICE(OSServiceId_ModifyPeripheral8);
      /* Store the parameter 1 - Area */
      OS_STORE_PARAM1_AREA(Area);
      /* Store the parameter 2 - Address */
      /* polyspace +2 CERT-C:EXP39-C MISRA-C3:11.3 MISRA-C3:18.4 [Justified:Low] "Pointer arithmatic used to achieve better throughput." */
      /* polyspace +1 MISRA-C3:11.8 [Not a defect:Low] "Inline function store address parameter 2" */
      OS_STORE_PARAM2_MODIFYADDRESS((P2VAR(uint32, AUTOMATIC, OS_VAR))Address);
      /* Store the parameter 3 - Clearmask */
      OS_STORE_PARAM3_CLEARMASK(Clearmask);
      /* Store the parameter 4 - Setmask */
      OS_STORE_PARAM4_SETMASK(Setmask);
      /* Report an error to error hook */
      OS_PROCESS_ERROR(LenStatusReturn);
    } /* End of else */
    #endif /* End of if (OS_STATUS == EXTENDED) */

    /* Return the value */
    return LenStatusReturn;
}
#endif

/*******************************************************************************
** Function Name        : Os_KernModifyPeripheral16                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service modifies a given memory location       **
**                        (<memory address>) with the formula:                **
**                       *<Address> = ((*<Address> & <clearmask>) | <setmask>)**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : Area, Address, Clearmask, Setmask                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Os_GddAppId, Os_GaaStaticPeripheralArea             **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11005 */
#if ((OS_TRUSTED_START_INDX != OS_ZERO) && (OS_PERIPHERAL == STD_ON))
/* polyspace +2 MISRA-C3:8.13 [Not a defect:Low] "Modify memory address to allocate memory location" */
FUNC(StatusType, OS_CODE) Os_KernModifyPeripheral16(AreaIdType Area,
     P2VAR(uint16, AUTOMATIC, OS_VAR) Address, uint16 Clearmask, uint16 Setmask)
{
    StatusType LenStatusReturn;
    P2VAR(uint32, AUTOMATIC, OS_CONST) LpBaseAddress;
    uint32 LulOffset;
    uint32 LulClearmask;
    uint32 LulSetmask;
    uint32 LpMaskAddress;

    #if (OS_MULTICORE == STD_ON)
    CoreIDType OS_CORE_ID;
    #endif
    LenStatusReturn = E_OK;

    /* Get Core Id*/
    OS_GET_CORE_ID(OS_CORE_ID);
    #if (OS_STATUS == EXTENDED)
    /* Check for call level */
    OS_CHECK_E_OS_CALLEVEL(MODIFYPERIPHERAL, LenStatusReturn);
    /* Check area ID */
    OS_CHECK_AREA_ID(Area, &LenStatusReturn);
    /* Check peripheral address */
    /* polyspace +1 CERT-C:EXP39-C MISRA-C3:11.3 MISRA-C3:18.4 [Justified:Low] "Pointer arithmatic used to achieve better throughput." */
    OS_CHECK_PERIPHERAL_ADDRESS((P2VAR(uint32, AUTOMATIC, OS_VAR))Address, &LenStatusReturn, OS_PERIPHERAL_UINT16);
    /* Check peripheral range */
    /* polyspace +1 CERT-C:EXP39-C MISRA-C3:11.3 MISRA-C3:18.4 [Justified:Low] "Pointer arithmatic used to achieve better throughput." */
    OS_CHECK_PERIPHERAL_AREA(Area, (P2VAR(uint32, AUTOMATIC, OS_VAR))Address, &LenStatusReturn, OS_PERIPHERAL_UINT16);
    #endif
    /* Check peripheral access */
    /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "Area have been checked before using" */
    /* polyspace +1 RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
    OS_CHECK_PERIPHERAL_APPLICATION_ACCESS(LenStatusReturn, Area);

    if (LenStatusReturn == E_OK)
    {
      /* @Trace: SafeOs_SUD_API_56201 */
      /* Get the Base Address */
      /* polyspace +1 MISRA-C3:11.4 CERT-C:INT36-C [Justified:Low] "The conversion to get the Base address and has no impact" */
      LpBaseAddress = (uint32 *) ((uint32)Address & OS_MASK_BASE_ADDRESS);

      /* Get the Offset */
      /* polyspace +1 MISRA-C3:11.4 [Justified:Low] "The conversion to get the Offset of address and has no impact" */
      LulOffset = (uint32)Address & OS_MASK_OFFSET;

      /* Move Clearmask to point address  */
      LulClearmask = (uint32)((uint32)(Clearmask) << (LulOffset << OS_MASK_OFFSET));
      /* Move Setmask to point address  */
      LulSetmask = (uint32)((uint32)(Setmask) << (LulOffset << OS_MASK_OFFSET));

      /* @Trace: SafeOs_SUD_API_56202 */
      /* Initialize first peripheral block for modifying */
      LpMaskAddress = OS_MASK_PERIPHERAL_16BIT;

      /* Shift to the Peripheral block need to write */
      LpMaskAddress = LpMaskAddress << (LulOffset * OS_MASK_PERIPHERAL_SUB_BLOCKZIZE);
      /* polyspace +2 RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
      /* Update mask before modify */
      LpMaskAddress = ~LpMaskAddress;

      /* Update LulClearmask for expected address */
      LulClearmask = LulClearmask | LpMaskAddress;
      /* polyspace +2 RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
      /* Update to the expected address */
      *LpBaseAddress = (((*LpBaseAddress) & LulClearmask) | LulSetmask);
    }
    #if (OS_STATUS == EXTENDED)
    else
    {
      /* @Trace: SafeOs_SUD_API_56203 */
      /* Store the service ID of ModifyPeripheral16 */
      OS_STORE_SERVICE(OSServiceId_ModifyPeripheral16);
      /* Store the parameter 1 - Area */
      OS_STORE_PARAM1_AREA(Area);
      /* Store the parameter 2 - Address */
      /* polyspace +1 CERT-C:EXP39-C MISRA-C3:11.3 MISRA-C3:18.4 [Justified:Low] "Pointer arithmatic used to achieve better throughput." */
      /* polyspace +1 MISRA-C3:11.8 [Not a defect:Low] "Inline function store address parameter 2" */
      OS_STORE_PARAM2_MODIFYADDRESS((P2VAR(uint32, AUTOMATIC, OS_VAR))Address);
      /* Store the parameter 3 - Clearmask */
      OS_STORE_PARAM3_CLEARMASK(Clearmask);
      /* Store the parameter 4 - Setmask */
      OS_STORE_PARAM4_SETMASK(Setmask);
      /* Report an error to error hook */
      OS_PROCESS_ERROR(LenStatusReturn);
    } /* End of else */
    #endif /* End of if (OS_STATUS == EXTENDED) */

    /* Return the value */
    return LenStatusReturn;
}
#endif

/*******************************************************************************
** Function Name        : Os_KernModifyPeripheral32                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service modifies a given memory location       **
**                        (<memory address>) with the formula:                **
**                       *<Address> = ((*<Address> & <clearmask>) | <setmask>)**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : Area, Address, Clearmask, Setmask                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Os_GddAppId, Os_GaaStaticPeripheralArea             **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11005 */
#if ((OS_TRUSTED_START_INDX != OS_ZERO) && (OS_PERIPHERAL == STD_ON))
/* polyspace +2 MISRA-C3:8.13 [Not a defect:Low] "Modify memory address to allocate memory location" */
FUNC(StatusType, OS_CODE) Os_KernModifyPeripheral32(AreaIdType Area,
     P2VAR(uint32, AUTOMATIC, OS_VAR) Address, uint32 Clearmask, uint32 Setmask)
{
    StatusType LenStatusReturn;
    P2VAR(uint32, AUTOMATIC, OS_CONST) LpBaseAddress;
    uint32 LulOffset;
    uint32 LulClearmask;
    uint32 LulSetmask;

    #if (OS_MULTICORE == STD_ON)
    CoreIDType OS_CORE_ID;
    #endif
    LenStatusReturn = E_OK;

    /* Get Core Id*/
    OS_GET_CORE_ID(OS_CORE_ID);
    #if (OS_STATUS == EXTENDED)
    /* Check for call level */
    OS_CHECK_E_OS_CALLEVEL(MODIFYPERIPHERAL, LenStatusReturn);
    /* Check area ID */
    OS_CHECK_AREA_ID(Area, &LenStatusReturn);
    /* Check peripheral address */
    OS_CHECK_PERIPHERAL_ADDRESS(Address, &LenStatusReturn, OS_PERIPHERAL_UINT32);
    /* Check peripheral range */
    OS_CHECK_PERIPHERAL_AREA(Area, Address, &LenStatusReturn, OS_PERIPHERAL_UINT32);
    #endif
    /* Check peripheral access */
    /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "Area have been checked before using" */
    /* polyspace +1 RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
    OS_CHECK_PERIPHERAL_APPLICATION_ACCESS(LenStatusReturn, Area);

    if (LenStatusReturn == E_OK)
    {
      /* @Trace: SafeOs_SUD_API_56301 */
      /* Get the Base Address */
      /* polyspace +1 MISRA-C3:11.4 CERT-C:INT36-C [Justified:Low] "The conversion to get the Base address and has no impact" */
      LpBaseAddress = (uint32 *) ((uint32)Address & OS_MASK_BASE_ADDRESS);

      /* Get the Offset */
      /* polyspace +1 MISRA-C3:11.4 [Justified:Low] "The conversion to get the Offset of address and has no impact" */
      LulOffset = (uint32)Address & OS_MASK_OFFSET;

      /* Move Clearmask to point address  */
      LulClearmask = (uint32)((Clearmask) << (LulOffset << OS_MASK_OFFSET));
      /* Move Setmask to point address  */
      LulSetmask = (uint32)((Setmask) << (LulOffset << OS_MASK_OFFSET));

      /* @Trace: SafeOs_SUD_API_56302 */
      /* polyspace +2 RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
      *LpBaseAddress = (uint32)((uint32)((*LpBaseAddress) & LulClearmask) | LulSetmask);
    }
    #if (OS_STATUS == EXTENDED)
    else
    {
      /* @Trace: SafeOs_SUD_API_56303 */
      /* Store the service ID of ModifyPeripheral32 */
      OS_STORE_SERVICE(OSServiceId_ModifyPeripheral32);
      /* Store the parameter 1 - Area */
      OS_STORE_PARAM1_AREA(Area);
      /* Store the parameter 2 - Address */
      /* polyspace +1 MISRA-C3:11.8 [Not a defect:Low] "Inline function store address parameter 2" */
      OS_STORE_PARAM2_MODIFYADDRESS(Address);
      /* Store the parameter 3 - Clearmask */
      OS_STORE_PARAM3_CLEARMASK(Clearmask);
      /* Store the parameter 4 - Setmask */
      OS_STORE_PARAM4_SETMASK(Setmask);
      /* Report an error to error hook */
      OS_PROCESS_ERROR(LenStatusReturn);
    } /* End of else */
    #endif /* End of if (OS_STATUS == EXTENDED) */

    /* Return the value */
    return LenStatusReturn;
}
#endif
#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:end<ISO-17961:intptrconv:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace-end RTE:IDP [Not a defect:Low] "configured memory access index" */
/* polyspace-end RTE:OBAI [Not a defect:Low] "configured array index" */
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-end MISRA-C3:D4.1 [Justified:Low] "Ptr points to a valid value and code is verified manually" */
/* polyspace:end<MISRA-C3:11.3:Not a defect:Justify with annotations> Cast is needed for implementation */
/* polyspace-end MISRA-C3:18.1 [Justified:Low] "Array index has been configured inside bounds and code is verified manually" */
/* polyspace:end<CERT-C:EXP39-C:Not a defect:Justify with annotation> Pointer arithmatic used to achieve better throughput. */
/* polyspace:end<CERT-C:INT36-C:Not a defect:Justify with annotation> This conversion cannot be modified to handle memory */
/* polyspace-end DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
/* polyspace-end CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
/* polyspace-end MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
