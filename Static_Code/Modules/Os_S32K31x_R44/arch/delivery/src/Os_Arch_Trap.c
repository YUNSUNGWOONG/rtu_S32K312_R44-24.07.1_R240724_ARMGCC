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
**  SRC-MODULE: Os_Arch_Trap.c                                                **
**                                                                            **
**  TARGET    : S32K31x                                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of Exception vector                                 **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: Yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/

/* @Trace: SRS_BSW_00003 SRS_BSW_00006 SRS_BSW_00007 SRS_BSW_00009 SRS_BSW_00301 SRS_BSW_00302 SRS_BSW_00305
 SRS_BSW_00415 SRS_BSW_00305 SRS_BSW_00307 SRS_BSW_00308 SRS_BSW_00310 SRS_BSW_00328 SRS_BSW_00441 */
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date           By            Description                         **
********************************************************************************
** 1.3.0     31-Jan-2024    HJ.Kim       Jira    CP44-4169                    **
** 1.1.0      1-Sep-2023    HJ.Kim       Jira    CP44-2528                    **
**            8-Jun-2023    HJ.Kim       Jira    CP44-2090                    **
**            7-Apr-2023    HG.Kim       Jira    CP44-1803                    **
** 1.0.2     31-Dec-2022    TinHV        Jira    CP44-856                     **
** 1.0.1     19-Sep-2022    TinHV        Jira    CP44-192                     **
** 1.0.0.1   30-Jun-2022    TinHV        Jira    CP44-333                     **
** 1.0.0     13-Jun-2022    TinHV        Redmine #24717                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<RTE:NIV:Not a defect:Justify with annotations> MCU register access */
/* polyspace:begin<RTE:ABS_ADDR:Not a defect:Justify with annotations> MCU register access */
/* polyspace:begin<RTE:IDP:Not a defect:Justify with annotations> Configured memory access index */
/* polyspace:begin<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<MISRA-C3:5.4:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<MISRA-C3:8.13:Not a defect:Justify with annotations> The pointer points const-qualified type */
/* polyspace:begin<MISRA-C3:11.1:Not a defect:Justify with annotations> Conversion is needed for vector table */
/* polyspace:begin<MISRA-C3:11.4:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace:begin<ISO-17961:intptrconv:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace:begin<MISRA-C3:11.5:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace:begin<MISRA-C3:11.6:Not a defect:Justify with annotations> Cast is needed for implementation */
/* polyspace:begin<MISRA-C3:20.1:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:begin<MISRA-C3:11.3:Not a defect:Justify with annotations> This is to access registers which are assigned to absolute address  */
/* polyspace:begin<MISRA-C3:11.8:Not a defect:Justify with annotations> Cast is needed for implementation */
/* polyspace:begin<CERT-C:INT36-C:Not a defect:Justify with annotation> This conversion cannot be modified to handle memory */

/* @Trace: SRS_PSRS_00002 SRS_Os_00097 SRS_Os_11011 */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_PortTypes.h"
#include "Os_Ram.h"
#include "Os_Shutdown.h"
/* @Trace: SRS_BSW_00410 */
#if (OS_MULTICORE == STD_ON)
#include "Os_Multicore.h"
#endif
#include "Os_Kernel.h"
#include "Os_Error.h"
#include "Os_Arch_Except.h"
#include "Os_Arch_Interrupt.h"
#include "Os_Arch_MemPro.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* @Trace: SRS_BSW_00351 */
#define OS_START_SEC_EXCEPTION_VECTOR_ASIL_D_GLOBAL
#include "MemMap.h"

CONST(T_IsrFuncPtr, OS_CONST) Os_ExceptionVectorTable[NUM_ELE_VECTOR_TABLE] =
{
    (T_IsrFuncPtr) &StackTop,                     /* 0:  Top of Stack */
    (T_IsrFuncPtr) &Reset_Handler,                /* 1:  Reset Handler */
    (T_IsrFuncPtr) &Os_NMIHandler,                /* 2:  NMI Handler */
    (T_IsrFuncPtr) &Os_FaultHandler,              /* 3:  Hard Fault Handler */
    (T_IsrFuncPtr) &Os_FaultHandler,              /* 4:  MPU Fault Handler */
    (T_IsrFuncPtr) &Os_FaultHandler,              /* 5:  Bus Fault Handler */
    (T_IsrFuncPtr) &Os_FaultHandler,              /* 6:  Usage Fault Handler */
    (T_IsrFuncPtr) NULL_PTR,       	              /* 7:  Reserved */
    (T_IsrFuncPtr) NULL_PTR,                      /* 8:  Reserved */
    (T_IsrFuncPtr) NULL_PTR,                      /* 9:  Reserved */
    (T_IsrFuncPtr) NULL_PTR,                      /* 10: Reserved */
    (T_IsrFuncPtr) &Os_SVCallHandler,             /* 11: SVCall Handler */
    (T_IsrFuncPtr) NULL_PTR,                      /* 12: Debug Monitor Handler */
    (T_IsrFuncPtr) NULL_PTR,                      /* 13: Reserved */
    (T_IsrFuncPtr) NULL_PTR,                      /* 14: PendSV Handler */
    (T_IsrFuncPtr) &Os_ISRHandler,                /* 15: SysTick Handler */
    /* External Interrupts */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 16  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 17  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 18  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 19  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 20  DMA transfer complete and error CH0 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 21  DMA transfer complete and error CH1 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 22  DMA transfer complete and error CH2 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 23  DMA transfer complete and error CH3 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 24  DMA transfer complete and error CH4 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 25  DMA transfer complete and error CH5 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 26  DMA transfer complete and error CH6 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 27  DMA transfer complete and error CH7 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 28  DMA transfer complete and error CH8 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 29  DMA transfer complete and error CH9 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 30  DMA transfer complete and error CH10 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 31  DMA transfer complete and error CH11 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 32  DMA transfer complete and error CH12 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 33  DMA transfer complete and error CH13 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 34  DMA transfer complete and error CH14 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 35  DMA transfer complete and error CH15 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 36  DMA transfer complete and error CH16 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 37  DMA transfer complete and error CH17 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 38  DMA transfer complete and error CH18 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 39  DMA transfer complete and error CH19 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 40  DMA transfer complete and error CH20 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 41  DMA transfer complete and error CH21 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 42  DMA transfer complete and error CH22 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 43  DMA transfer complete and error CH23 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 44  DMA transfer complete and error CH24 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 45  DMA transfer complete and error CH25 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 46  DMA transfer complete and error CH26 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 47  DMA transfer complete and error CH27 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 48  DMA transfer complete and error CH28 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 49  DMA transfer complete and error CH29 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 50  DMA transfer complete and error CH30 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 51  DMA transfer complete and error CH31 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 52	 Single bit ECC error */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 53	 Multi bit ECC error */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 54	 FPU ORed sources (Input Denormal, Inexact, Underflow, Overflow, Divide-by-Zero, Invalid Operand) */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 55	 Single interrupt vector for all four channels */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 56	 Single interrupt vector for all four channels */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 57	 Single interrupt vector for all four channels */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 58	 Platform watchdog initial time-out */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 59	 Platform watchdog initial time-out */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 60	 Platform watchdog initial time-out */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 61	 CTI Interrupt 0 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 62	 CTI Interrupt 1 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 63	 Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 64	 Program or erase operation is completed */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 65	 Main watchdog timeout interrupt */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 66	 Alternate watchdog timeout interrupt */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 67	 Interrupt request to the system */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 68	 One interrupt for all LVDs, One interrupt for all HVDs */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 69	 External Interrupt Vector 0 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 70	 External Interrupt Vector 1 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 71	 External Interrupt Vector 2 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 72	 External Interrupt Vector 3 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 73	 Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 74	 Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 75	 Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 76	 Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 77	 Interrupt request 23,22,21,20 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 78	 Interrupt request 19,18,17,16 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 79	 Interrupt request 15,14,13,12 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 80	 Interrupt request 11,10,9,8 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 81	 Interrupt request 7,6,5,4 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 82	 Interrupt request 3,2,1,0 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 83	 Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 84	 Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 85	 Interrupt request 23,22,21,20 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 86	 Interrupt request 19,18,17,16 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 87	 Interrupt request 15,14,13,12 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 88	 Interrupt request 11,10,9,8 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 89	 Interrupt request 7,6,5,4 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 90	 Interrupt request 3,2,1,0 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 91	 Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 92	 Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 93	 Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 94	 Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 95	 Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 96	 Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 97	 Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 98	 Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 99	 Interrupts from pad group 0,1,2,3, Interrupts from pad group 0_64, Interrupts from pad group 1_64, Interrupts from pad group 2_64, Interrupts from pad group 3_64 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 100  CMU0 interrupt */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 101  CMU1 interrupt */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 102  CMU2 interrupt */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 103  An interrupt is requested when a conversion is issued to the ADC, An interrupt is requested when new data is available from ADC0 conversion, An interrupt is requested when new data is available from ADC1 conversion, An interrupt is requested when new data is available from ADC2 conversion, An interrupt is requested when the last command of a list is issued to the ADC,An Interrupt output for FIFO1,An Interrupt output for FIFO2 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 104  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 105  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 106  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 107  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 108  Interrupt 0, Interrupt 1 Interrupt 2 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 109  Interrupt 0, Interrupt 1 Interrupt 2 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 110  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 111  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 112  Interrupt for Channel0,Interrupt for Channel1,Interrupt for Channel2,Interrupt for Channel3,Interrupt for Channel4 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 113  Interrupt for Channel0,Interrupt for Channel1,Interrupt for Channel2,Interrupt for Channel3 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 114  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 115  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 116  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 117  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 118  RTCF or ROVRF interrupt to be serviced by the system controller, APIF interrupt to be serviced by the system controller */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 119  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 120  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 121  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 122  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 123  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 124  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 125  Interrupt indicating that the CAN bus went to Bus Off state */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 126  Message Buffer Interrupt line 0-31,ORed Interrupt for Message Buffers */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 127  Message Buffer Interrupt line 32-63 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 128  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 129  Interrupt indicating that the CAN bus went to Bus Off state */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 130  Message Buffer Interrupt line 0-31 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 131  Message Buffer Interrupt line 32-63 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 132  Interrupt indicating that the CAN bus went to Bus Off state */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 133  Message Buffer Interrupt line 0-31 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 134  Message Buffer Interrupt line 32-63 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 135  Interrupt indicating that the CAN bus went to Bus Off state */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 136  Message Buffer Interrupt line 0-31 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 137  Interrupt indicating that the CAN bus went to Bus Off state */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 138  Message Buffer Interrupt line 0-31 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 139  Interrupt indicating that the CAN bus went to Bus Off state */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 140  Message Buffer Interrupt line 0-31 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 141  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 142  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 143  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 144  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 145  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 146  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 147  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 148  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 149  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 150  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 151  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 152  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 153  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 154  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 155  FlexIO Interrupt */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 156  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 157  TX and RX interrupt */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 158  TX and RX interrupt */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 159  TX and RX interrupt */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 160  TX and RX interrupt */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 161  TX and RX interrupt */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 162  TX and RX interrupt */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 163  TX and RX interrupt */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 164  TX and RX interrupt */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 165  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 166  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 167  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 168  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 169  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 170  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 171  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 172  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 173  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 174  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 175  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 176  I3C Interrupt */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 177  LPI2C Master Interrupt */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 178  LPI2C Master Interrupt */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 179  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 180  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 181  LPSPI Interrupt */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 182  LPSPI Interrupt */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 183  LPSPI Interrupt */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 184  LPSPI Interrupt */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 185  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 186  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 187  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 188  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 189  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 190  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 191  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 192  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 193  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 194  Indicates new data to be read from JIN_IPS register or can be written to JOUT_IPS register */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 195  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 196  End of conversion, Error interrupt, Watchdog interrupt */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 197  End of conversion, Error interrupt, Watchdog interrupt */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 198  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 199  Async interrupt */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 200  Async interrupt */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 201  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 202  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 203  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 204  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 205  Interrupt request(ALARM state) */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 206  Interrupt request(miscellaneous conditions) */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 207  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 208  ORed TX interrupt to MU-0 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 209  ORed RX interrupt to MU-0 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 210  ORed general purpose interrupt request to MU-0 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 211  ORed TX interrupt to MU-1 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 212  ORed RX interrupt to MU-1 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 213  ORed general purpose interrupt request to MU-1 */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 214  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 215  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 216  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 217  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 218  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 219  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 220  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 221  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 222  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 223  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 224  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 225  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 226  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 227  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 228  PLL LOL interrupt */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 229  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 230  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 231  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 232  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 233  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 234  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 235  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 236  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 237  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 238  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 239  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 240  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 241  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 242  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 243  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 244  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 245  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 246  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 247  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 248  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 249  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 250  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 251  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 252  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 253  Reserved */
    (T_IsrFuncPtr) &Os_ISRHandler,	              /* 254  Reserved */
    (T_IsrFuncPtr) 0xFFFFFFFFu                    /* 255 Reserved for user TRIM value */
};
#define OS_STOP_SEC_EXCEPTION_VECTOR_ASIL_D_GLOBAL
#include "MemMap.h"
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* @Trace: SRS_BSW_00351 */
FUNC(void, OS_CODE) Os_TrapHandler(Tdd_Os_ContextSwitch * LpAddr,
                                                         Os_TrapType LulExcNum);
FUNC(Os_TrapInfoType, OS_CODE) Os_GetLastTrapInfo(uint8 LddCoreId);
FUNC(void, OS_CODE) Os_UnusedHandler(void);
/* polyspace<MISRA-C3:8.5:Not a defect:Justify with annotations> This function is defined in other module. So external definition is not visible in Polyspace  */
extern FUNC(boolean, OS_CODE) Fls_DataEccHandler(uint8 ** instr_pt2pt,
                                        volatile uint32 * addr_BFAR, uint32 * addr_CFSR);
#define OS_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/***************************************************************************//**
 * Function             : Os_GetLastTrapInfo
 *
 * Service ID           : NA
 *
 * Description          : If CoreID is invalid, return CORE0 trap info
 *
 * Sync/Async           : NA
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]            LddCoreID - Current Core ID
 *
 * @return              : Last Trap info of current core
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GddTrapInfo
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_S32K31X_003}
 *
 * @ingroup               OS_S32K31X_ESDD_006 
 ******************************************************************************/
FUNC(Os_TrapInfoType, OS_CODE) Os_GetLastTrapInfo(uint8 LddCoreId)
{
  CoreIdType coreid;
  
  if (LddCoreId < Os_Core_Count)
  {
    /* @Trace: SafeOs_SUD_API_35801 */
    coreid = LddCoreId;
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_35802 */
    coreid = OS_CORE_ZERO;
  }
  /* @Trace: SafeOs_SUD_API_35803 */
  /* polyspace<RTE:OBAI:Not a defect:Justify with annotations> Below code is verified and not a defect. */
  return Os_GddTrapInfo[coreid];
}

/***************************************************************************//**
 * Function             : Os_TrapHandler
 *
 * Service ID           : NA
 *
 * Description          : This service is used to exception handling
 *
 * Sync/Async           : NA
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GddTrapInfo, Os_GpStaticTask, Os_GusCallevelCheck
 *                        Os_GulKernelSP, Os_GulKernelSPBase, Os_GucInKernel
 *
 *                        Function(s) invoked    :
 *                        Os_ProtectionHookService(), Os_DoContextSwitch(),
 *                        Os_ShutdownOSService()
 *
 * {Ref: SWR_OS_S32K31X_003}
 *
 * @ingroup               OS_S32K31X_ESDD_006 
 ******************************************************************************/
/* polyspace-begin DEFECT:UNMODIFIED_VAR_NOT_CONST [Not a defect:low] The pointer variable is const-qualified type*/
/* polyspace:begin<CERT-C:INT36-C:Not a defect:Justify with annotations>This conversion cannot be modified to handle memory */
/* polyspace:begin<MISRA-C3:8.13:Not a defect:Justify with annotations> The pointer points const-qualified type */
/* polyspace +2 CODE-METRICS:PATH [Not a defect:Low] "The display of specific values of the number of paths is justified" */
/* @Trace: SRS_Os_00097 SRS_Os_11009 SRS_Os_11013 SRS_Os_11011 SRS_Os_11014 SRS_Os_80007 SRS_PSRS_00002 SRS_PSRS_00003 */
FUNC(void, OS_CODE) Os_TrapHandler(Tdd_Os_ContextSwitch * LpAddr,
                                                          Os_TrapType LulExcNum)
{
  #if (OS_PROTECTION_HOOK == STD_ON)
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpNewTaskISR;
  #endif
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID = Os_MyCore();
  #endif
  StatusType LddFatalerror = E_OS_PROTECTION_EXCEPTION;
  #if (OS_APP_MEMBLK_CNT != OS_ZERO)
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask;
  uint32 LulCtrl;
  #endif

  /* @Trace: SafeOs_SUD_API_35501 */
  /* Save exception information */
  Os_GddTrapInfo[OS_CORE_ID].enTrapClass = LulExcNum;
  Os_GddTrapInfo[OS_CORE_ID].HFSR = OS_SBC_HFSR.U;  
  Os_GddTrapInfo[OS_CORE_ID].CFSR = OS_SBC_CFSR.U;
  /* polyspace-begin MISRA-C3:11.3 [Justified:Medium] "To handle saved context" */
  /* polyspace-begin MISRA-C3:11.8 [Justified:Medium] "To handle saved context" */
  /* polyspace-begin MISRA-C3:D4.14 [Justified:Medium] "To handle saved context" */  
  Os_GddTrapInfo[OS_CORE_ID].ExecCtxt  = *((Tdd_Os_ContextSwitch *)LpAddr);
  /* polyspace-begin CERT-C:INT36-C [Justified:Low] "This conversion is need" */
  Os_GddTrapInfo[OS_CORE_ID].pExecAddr = (MemoryStartAddressType)(LpAddr->ulPC);
  /* polyspace-end CERT-C:INT36-C [Justified:Low] "This conversion is need" */
  /* polyspace-end MISRA-C3:11.8 */
  /* polyspace-end MISRA-C3:11.3 */
  /* polyspace-end MISRA-C3:D4.14 */
  if ((OS_SBC_CFSR.B.MemManage & OS_MMFSR_ERROR_MASK) != OS_ZERO)               
  {
    if((OS_SBC_CFSR.B.MemManage & OS_MMFSR_VALID_MASK) != OS_ZERO)
    {
      /* @Trace: SafeOs_SUD_API_35502 */
      Os_GddTrapInfo[OS_CORE_ID].pMMFAR = (MemoryStartAddressType)OS_SBC_MMFAR;
    }
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_35503 */
    Os_GddTrapInfo[OS_CORE_ID].pMMFAR = (MemoryStartAddressType)OS_INVALID_ADDRESS;
  }
  if ((OS_SBC_CFSR.B.BusFault & OS_BFSR_ERROR_MASK) != OS_ZERO)
  {
    if ((OS_SBC_CFSR.B.BusFault & OS_BFSR_VALID_MASK) != OS_ZERO)
    {
      /* @Trace: SafeOs_SUD_API_35504 */
      Os_GddTrapInfo[OS_CORE_ID].pBFAR = (MemoryStartAddressType)OS_SBC_BFAR;
    }
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_35505 */
    Os_GddTrapInfo[OS_CORE_ID].pBFAR = (MemoryStartAddressType)OS_INVALID_ADDRESS;
  }

  #if (OS_PROTECTION_HOOK == STD_ON)
  #if (OS_MEMORY_PROTECTION == STD_ON)
  if ((LulExcNum == OS_TRAP_BUS_FAULT) || (LulExcNum == OS_TRAP_MEMORY_MNG_FAULT))
  {
    /* @Trace: SafeOs_SUD_API_35506 */
    LddFatalerror = E_OS_PROTECTION_MEMORY;
  }
  #endif
  /* @Trace: SafeOs_SUD_API_35507 */
  (void)Os_ProtectionHookService(LddFatalerror);
  /* Running Task or ISR was killed. Need Context switching */
  LpNewTaskISR = Os_GpStaticTask[OS_CORE_ID];
  /* polyspace:begin<DEFECT : DEAD_CODE : Not a defect : Justify with annotations > Checking of NULL_PTR is for fail-safety */
  if (LpNewTaskISR == NULL_PTR)
  {
    /* @Trace: SafeOs_SUD_API_35508 */
    /* Never returns! */
    #if (OS_MULTICORE == STD_ON)
	Os_SyncShutdownOSService(LddFatalerror);
	#else
    Os_ShutdownOSService(LddFatalerror);
	#endif
  }
  /* polyspace:end<DEFECT : DEAD_CODE : Not a defect : Justify with annotations > Checking of NULL_PTR is for fail-safety */
  /* polyspace +2 MISRA-C3:18.1 [Justified:Medium] "Pointer not access out of array." */
  /* polyspace +1 MISRA-C3:18.1 [Justified:Medium] "Pointer not access out of array"*/
  else if (LpNewTaskISR->usType != OS_ISR2)
  {
    /* @Trace: SafeOs_SUD_API_35509 */
    Os_GusCallevelCheck[OS_CORE_ID] = (uint16)CONTEXT_SWITCHING_NONE;

    /* Discard kernel stack(stacked by ISR) */
    Os_GulKernelSP[OS_CORE_ID] = Os_GulKernelSPBase[OS_CORE_ID];
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_35510 */
    Os_GusCallevelCheck[OS_CORE_ID] = (uint16)OS_CONTEXT_CAT2ISR;
  }
  Os_GucInKernel[OS_CORE_ID] = (uint8)OS_ZERO;

  #if (OS_APP_MEMBLK_CNT != OS_ZERO)
  /* polyspace +2 RTE:NIP [Justified:Medium] "ptr points to a valid value and code is verified manually" */
  /* polyspace +1 MISRA-C3:18.1 [Justified:Medium] "Pointer not access out of array"*/
  LpStaticTask = &Os_GaaStaticTask[Os_GpLinkTask[OS_CORE_ID]->ddTaskID];
  LulCtrl = __MRS(__CONTROL);
  /* If Application is non-trusted, set privileged mode to user */
  /* polyspace +1 MISRA-C3:18.1 [Justified:Medium] "Pointer not access out of array"*/
  if (LpStaticTask->ddAppId < (ApplicationType)Os_Trusted_Start_Indx)
  {
    /* @Trace: SafeOs_SUD_API_37002 */
    /* CTRL.nPRIV = 1 which means Thread mode has unprivileged access */
    LulCtrl |= 0x00000001u;
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_37003 */
    /* CTRL.nPRIV = 0 which means Thread mode has privileged access */
    LulCtrl &= 0xFFFFFFFEu;
  }
  __MSR(__CONTROL, LulCtrl);
  #endif
  
  /* @Trace: SafeOs_SUD_API_35511 */
  /* polyspace +1 RTE:NIP [Justified:Medium] "ptr points to a valid value and code is verified manually" */
  Os_DoContextSwitch(LpNewTaskISR->pContext);
  #else
  /* @Trace: SafeOs_SUD_API_35512 */
  /* Never returns! */
  #if (OS_MULTICORE == STD_ON)
  Os_SyncShutdownOSService(LddFatalerror);
  #else
  Os_ShutdownOSService(LddFatalerror);
  #endif /* OS_MULTICORE == STD_ON */
  #endif
}
/* polyspace:end<MISRA-C3:8.13:Not a defect:Justify with annotations> The pointer points const-qualified type */
/* polyspace-end DEFECT:UNMODIFIED_VAR_NOT_CONST [Not a defect:low] The pointer variable is const-qualified type*/
/* polyspace:end<CERT-C:INT36-C:Not a defect:Justify with annotations>This conversion cannot be modified to handle memory */
/***************************************************************************//**
 * Function             : Os_UnusedHandler
 *
 * Service ID           : NA
 *
 * Description          : This service is used to unused exception handling
 *
 * Sync/Async           : NA
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GddTrapInfo, Os_GpStaticTask, Os_GusCallevelCheck
 *                        Os_GulKernelSP, Os_GulKernelSPBase, Os_GucInKernel
 *
 *                        Function(s) invoked    :
 *                        Os_ProtectionHookService(), Os_DoContextSwitch(),
 *                        Os_ShutdownOSService()
 *
 * {Ref: SWR_OS_S32K31X_003}
 *
 * @ingroup               OS_S32K31X_ESDD_006 
 ******************************************************************************/
FUNC(void, OS_CODE) Os_UnusedHandler(void)
{

  const StatusType LddFatalerror = E_OS_SYS_PANIC;
  
  /* This routine should not be called because the exception is not registered */

  /* Never returns! */
  /* @Trace: SafeOs_SUD_API_35901 */
  Os_ShutdownOSService(LddFatalerror);
}

#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:end<RTE:NIV:Not a defect:Justify with annotations> MCU register access */
/* polyspace:end<RTE:ABS_ADDR:Not a defect:Justify with annotations> MCU register access */
/* polyspace:end<RTE:IDP:Not a defect:Justify with annotations> Configured memory access index */
/* polyspace:end<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:5.4:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:8.13:Not a defect:Justify with annotations> The pointer points const-qualified type */
/* polyspace:end<MISRA-C3:11.1:Not a defect:Justify with annotations> Conversion is needed for vector table */
/* polyspace:end<MISRA-C3:11.4:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace:end<ISO-17961:intptrconv:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace:end<MISRA-C3:11.5:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace:end<MISRA-C3:11.6:Not a defect:Justify with annotations> Cast is needed for implementation */
/* polyspace:end<MISRA-C3:20.1:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace:end<MISRA-C3:11.3:Not a defect:Justify with annotations> This is to access registers which are assigned to absolute address  */
/* polyspace:end<MISRA-C3:11.8:Not a defect:Justify with annotations> Cast is needed for implementation */
/* polyspace:end<CERT-C:INT36-C:Not a defect:Justify with annotation> This conversion cannot be modified to handle memory */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
