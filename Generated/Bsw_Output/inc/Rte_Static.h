/*******************************************************************************
**                           HYUNDAI AUTOEVER Corp.                           **
********************************************************************************
** (C) 2021 HYUNDAI AUTOEVER Corp.                                            **
** Confidential Proprietary Information. Distribution Limited.                **
** This source code is permitted to be used only in projects contracted       **
** with Hyundai Autoever, and any other use is prohibited.                    **
** If you use it for other purposes or change the source code,                **
** you may take legal responsibility.                                         **
** In this case, There is no warranty and technical support.                  **
********************************************************************************
**  Module Name : RTE                                                         **
**                                                                            **
**  File Name : Rte_Static.h                                                  **
**                                                                            **
**  Generated On : Mon Nov 11 2024 13:32:30 KST                               **
**                                                                            **
**  Generated from :                                                          **
**  Configuration\Definition\Os_ECU_Configuration_PDF_S32K312.arxml           **
**  Configuration\Ecu\ECUCD_EcucValueCollection.arxml                         **
**  Configuration\Ecu\Ecud_BswM.arxml                                         **
**  Configuration\Ecu\Ecud_CanCM.arxml                                        **
**  Configuration\Ecu\Ecud_CanIf.arxml                                        **
**  Configuration\Ecu\Ecud_CanNm.arxml                                        **
**  Configuration\Ecu\Ecud_CanSM.arxml                                        **
**  Configuration\Ecu\Ecud_CanTp.arxml                                        **
**  Configuration\Ecu\Ecud_CanTrcv.arxml                                      **
**  Configuration\Ecu\Ecud_Com.arxml                                          **
**  Configuration\Ecu\Ecud_ComM.arxml                                         **
**  Configuration\Ecu\Ecud_ComXf.arxml                                        **
**  Configuration\Ecu\Ecud_Crc.arxml                                          **
**  Configuration\Ecu\Ecud_CryIf.arxml                                        **
**  Configuration\Ecu\Ecud_Crypto_76_HaeModule.arxml                          **
**  Configuration\Ecu\Ecud_Csm.arxml                                          **
**  Configuration\Ecu\Ecud_Dcm.arxml                                          **
**  Configuration\Ecu\Ecud_Dem.arxml                                          **
**  Configuration\Ecu\Ecud_Det.arxml                                          **
**  Configuration\Ecu\Ecud_E2EXf.arxml                                        **
**  Configuration\Ecu\Ecud_EcuC.arxml                                         **
**  Configuration\Ecu\Ecud_EcuM.arxml                                         **
**  Configuration\Ecu\Ecud_FiM.arxml                                          **
**  Configuration\Ecu\Ecud_Fota.arxml                                         **
**  Configuration\Ecu\Ecud_IoHwAb.arxml                                       **
**  Configuration\Ecu\Ecud_LinIf.arxml                                        **
**  Configuration\Ecu\Ecud_LinSM.arxml                                        **
**  Configuration\Ecu\Ecud_LinTrcv.arxml                                      **
**  Configuration\Ecu\Ecud_MemIf.arxml                                        **
**  Configuration\Ecu\Ecud_Nm.arxml                                           **
**  Configuration\Ecu\Ecud_NvM.arxml                                          **
**  Configuration\Ecu\Ecud_Os.arxml                                           **
**  Configuration\Ecu\Ecud_PduR.arxml                                         **
**  Configuration\Ecu\Ecud_Rte.arxml                                          **
**  Configuration\Ecu\Ecud_StbM.arxml                                         **
**  Configuration\Ecu\Ecud_Tm.arxml                                           **
**  Configuration\Ecu\Ecud_WdgIf.arxml                                        **
**  Configuration\Ecu\Ecud_WdgM.arxml                                         **
**  Configuration\Ecu\Ecud_Wdg_76_Acw.arxml                                   **
**  Configuration\Ecu\Mcal\Ecud_Adc.arxml                                     **
**  Configuration\Ecu\Mcal\Ecud_Wdg.arxml                                     **
**  Configuration\System\Bswmd\Bswmd_Adc.arxml                                **
**  Configuration\System\Bswmd\Bswmd_BswM.arxml                               **
**  Configuration\System\Bswmd\Bswmd_Can.arxml                                **
**  Configuration\System\Bswmd\Bswmd_ComXf.arxml                              **
**  Configuration\System\Bswmd\Bswmd_Crypto.arxml                             **
**  Configuration\System\Bswmd\Bswmd_Dio.arxml                                **
**  Configuration\System\Bswmd\Bswmd_E2EXf.arxml                              **
**  Configuration\System\Bswmd\Bswmd_Fee.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Fls.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Gpt.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Icu.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Lin.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Mcl.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Mcu.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Port.arxml                               **
**  Configuration\System\Bswmd\Bswmd_Pwm.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Spi.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Wdg.arxml                                **
**  Configuration\System\Composition\EcuExtract.arxml                         **
**  Configuration\System\DBImport\DataTypes\AUTOSAR_DataTypes.arxml           **
**  Configuration\System\DBImport\DataTypes\CanStack_DataTypes.arxml          **
**  Configuration\System\DBImport\DataTypes\ComStack_DataTypes.arxml          **
**  Configuration\System\DBImport\FD_CAN1.arxml                               **
**  Configuration\System\DBImport\LIN1.arxml                                  **
**  Configuration\System\DBImport\LIN2.arxml                                  **
**  Configuration\System\Swcd_App\App_Dcm.arxml                               **
**  Configuration\System\Swcd_App\App_Dem.arxml                               **
**  Configuration\System\Swcd_App\App_E2EXf.arxml                             **
**  Configuration\System\Swcd_App\App_Lin.arxml                               **
**  Configuration\System\Swcd_App\App_Mode.arxml                              **
**  Configuration\System\Swcd_App\App_WdgM.arxml                              **
**  Configuration\System\Swcd_Bsw\MODE_PortInterfaces.arxml                   **
**  Configuration\System\Swcd_Bsw\Swcd_Bsw_BswM.arxml                         **
**  Configuration\System\Swcd_Bsw\Swcd_Lin.arxml                              **
**  Configuration\System\Transformer\Transformer.arxml                        **
**  Generated\Bsw_Output\bswmd\Bswmd_CanCM.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_CanIf.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_CanNm.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_CanSM.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_CanTp.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_CanTrcv.arxml                            **
**  Generated\Bsw_Output\bswmd\Bswmd_Com.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_ComM.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_Crc.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_CryIf.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_Crypto_76_HaeModule.arxml                **
**  Generated\Bsw_Output\bswmd\Bswmd_Csm.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_Dcm.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_Dem.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_Det.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_EcuM.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_FiM.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_Fota.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_IoHwAb.arxml                             **
**  Generated\Bsw_Output\bswmd\Bswmd_IpduM.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_KeyM.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_LinIf.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_LinSM.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_LinTrcv.arxml                            **
**  Generated\Bsw_Output\bswmd\Bswmd_MemIf.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_Mem_76_Pfls.arxml                        **
**  Generated\Bsw_Output\bswmd\Bswmd_Nm.arxml                                 **
**  Generated\Bsw_Output\bswmd\Bswmd_NvM.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_Os.arxml                                 **
**  Generated\Bsw_Output\bswmd\Bswmd_PduR.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_StbM.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_Tm.arxml                                 **
**  Generated\Bsw_Output\bswmd\Bswmd_WdgIf.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_WdgM.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_Wdg_76_Acw.arxml                         **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_ComM.arxml                             **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_Csm.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_Dcm.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_Dem.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_Det.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_EcuM.arxml                             **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_FiM.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_IoHwAb.arxml                           **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_KeyM.arxml                             **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_NvM.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_Os.arxml                               **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_StbM.arxml                             **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_WdgM.arxml                             **
**  Generated\Bsw_Output\swcd\Swcd_Fota.arxml                                 **
**  Static_Code\Modules\EcuM_R44\generator\EcuM_PortInterface.arxml           **
**  Static_Code\Modules\Rte_R44\generator\SafeRTE_PDF.arxml                   **
**                                                                            **
**  Generator version : 1.8.0.0                                               **
**                                                                            **
**  NOTE: This is a generated file, Please DO NOT EDIT manually!              **
**                                                                           **/
/******************************************************************************/
/*                 Multiple Header Inclusion Protection Start                 */
/******************************************************************************/
#ifndef RTE_STATIC_H
#define RTE_STATIC_H

/******************************************************************************/
/*                              Header Inclusion                              */
/******************************************************************************/

/******************************************************************************/
/*                Compatibility between C/C++ Languages Start                 */
/******************************************************************************/
#ifdef __cplusplus
extern "C" 
{

#endif

/******************************************************************************/
/*                                 RTE MACROS                                 */
/******************************************************************************/
/* Macro to set the flag */
#define RTE_SET                                                               1U

/* Macro to clear the flag */
#define RTE_CLEAR                                                             0U

/* Macro to initialize uint8 varaible to 0xFF value */
#define RTE_INIT_VALUE_UINT8                                                  0xFFU

/* Macro to clear the index values */
#define RTE_ZERO                                                              0U

/* Macro RTE_SOFT_MINIMUM_ERROR_VAL, to check the soft error minimum value */
#define RTE_SOFT_MINIMUM_ERROR_VAL                                            0x01U

/* Macro RTE_SOFT_MAXIMUM_ERROR_VAL, to check the soft error maximum value */
#define RTE_SOFT_MAXIMUM_ERROR_VAL                                            0x7FU

/* Macro RTE_HARD_MINIMUM_ERROR_VAL, to check the hard error minimum value */
#define RTE_HARD_MINIMUM_ERROR_VAL                                            0x80U

/* Macro RTE_ONE to check for 1 */
#define RTE_ONE                                                               1U

/* Macro RTE_E_NOT_OK to check for not equal in comparison of values */
#define RTE_E_NOT_OK                                                          202U

#define PHYSICAL(X,N0,N1,D0)\
    /*LDRA_INSPECTED 444 S ; Source: MISRA:2012 R.10.8 */\
    /*LDRA_INSPECTED 441 S ; Source: MISRA:2012 R.10.8 */\
    ((float)(N0 + (N1 * X)) / D0)

#define INTERNAL(Y,N0,N1,D0)\
    /*LDRA_INSPECTED 444 S ; Source: MISRA:2012 R.10.8 */\
    /*LDRA_INSPECTED 441 S ; Source: MISRA:2012 R.10.8 */\
    ((float)((Y * D0) - N0) / N1)

/******************************************************************************/
/*                                OS MACRO API                                */
/******************************************************************************/
/* OS error checking is ON */

/* OS API to invoke GetCounterValue API from RTE API when DET is OFF */
#define RTEAPI_M_OSGetCounterValue(counterid, tickvalueref,ReturnStatus,ServiceId)\
  do\
  {\
    if(E_OK != GetCounterValue(counterid, tickvalueref))\
    { \
      ReturnStatus = RTE_E_OS_ERROR;\
    }\
  }while(0)
/* OS API to invoke GetElapsedValue API from RTE API when DET is OFF */
#define RTEAPI_M_OSGetElapsedValue(counterid, prevtickvalueref, elapsedtickvalueref, ReturnStatus, ServiceId)\
  do\
  {\
    if(E_OK != GetElapsedValue(counterid, prevtickvalueref, elapsedtickvalueref))\
    { \
      ReturnStatus = RTE_E_OS_ERROR;\
    }\
  }while(0)
/* OS API to invoke ActivateTask API from RTE API when DET is OFF */
#define RTEAPI_M_OSActivateTask(taskid, ReturnStatus, ServiceId)\
  do\
  {\
/*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */\
    Rte_Task_Activate_Internal(taskid);\
    if(E_OK != ActivateTask(taskid))\
    { \
      ReturnStatus = RTE_E_OS_ERROR;\
    }\
  }while(0)
/* OS API to invoke ChainTask API from RTE API when DET is OFF */
#define RTEAPI_M_OSChainTask(taskid, ReturnStatus, ServiceId) \
  do\
  {\
    if(E_OK != ChainTask(taskid))\
    {\
      ReturnStatus = RTE_E_OS_ERROR;\
    }\
  }while(0)

/* OS API to invoke TerminateTask API from RTE API when DET is OFF */
#define RTEAPI_M_OSTerminateTask(ReturnStatus,ServiceId)\
  do\
  {\
    if(E_OK != TerminateTask())\
    {\
      ReturnStatus = RTE_E_OS_ERROR;\
    }\
  }while(0)

/* OS API to invoke SetEvent API from RTE API when DET is OFF */
#define RTEAPI_M_OSSetEvent(taskid, EventId, ReturnStatus,ServiceId)\
  do\
  {\
/*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */\
    Rte_Task_SetEvent_Internal(taskid, EventId);\
    if(E_OK != SetEvent(taskid, EventId))\
    {\
      ReturnStatus = RTE_E_OS_ERROR;\
    }\
  }while(0)

/* OS API to invoke ClearEvent API from RTE API when DET is OFF */
#define RTEAPI_M_OSClearEvent(EventId, ReturnStatus, ServiceId)\
  do\
  {\
    if(E_OK != ClearEvent(EventId))\
    {\
      ReturnStatus = RTE_E_OS_ERROR;\
    }\
  }while(0)

/* OS API to invoke WaitEvent API from RTE API when DET is OFF */
#define RTEAPI_M_OSWaitEvent(taskid, EventId, ReturnStatus, ServiceId)\
  do\
  {\
/*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */\
    Rte_Task_WaitEvent_Internal(taskid, EventId);\
    if(E_OK != WaitEvent(EventId))\
    {\
      ReturnStatus = RTE_E_OS_ERROR;\
    }\
    /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */\
    Rte_Task_WaitEventRet_Internal(taskid, EventId);\
  }while(0)

/* OS API to invoke GetEvent API from RTE API when DET is OFF */
#define RTEAPI_M_OSGetEvent(taskid, EventId, ReturnStatus, ServiceId) \
  do\
  {\
    if(E_OK != GetEvent(taskid, EventId))\
    {\
      ReturnStatus = RTE_E_OS_ERROR;\
    }\
  }while(0)

/* OS API to invoke SetRelAlarm API from RTE API when DET is OFF */
#define RTEAPI_M_OSSetRelAlarm(alarmid, inc, cyc, ReturnStatus, ServiceId)\
  do\
  {\
    if(E_OK != SetRelAlarm(alarmid, inc, cyc))\
    {\
      ReturnStatus = RTE_E_OS_ERROR;\
    }\
  }while(0)

/* OS API to invoke CancelAlarm API from RTE API when DET is OFF */
#define RTEAPI_M_OSCancelAlarm(alarmid, ReturnStatus, ServiceId)\
  do\
  {\
    if(E_OK != CancelAlarm(alarmid))\
    {\
      ReturnStatus = RTE_E_OS_ERROR;\
    }\
  }while(0)

/* OS API to invoke StartScheduleTableRel API from RTE API when DET is OFF */
#define RTEAPI_M_OSStartScheduleTableRel(scheduletableid, offset, ReturnStatus, ServiceId)\
  do\
  {\
    if(E_OK != StartScheduleTableRel(scheduletableid, offset))\
    {\
      ReturnStatus = RTE_E_OS_ERROR;\
    }\
  }while(0)

/* OS API to invoke StartScheduleTableAbs API from RTE API when DET is OFF */
#define RTEAPI_M_OSStartScheduleTableAbs(scheduletableid, start, ReturnStatus, ServiceId)\
  do\
  {\
    if(E_OK != StartScheduleTableAbs(scheduletableid, start))\
    {\
      ReturnStatus = RTE_E_OS_ERROR;\
    }\
  }while(0)

/* OS API to invoke StartScheduleTableSynchron API from RTE API when DET is OFF */
#define RTEAPI_M_OSStartScheduleTableSynchron(scheduletableid, ReturnStatus, ServiceId)\
  do\
  {\
    if(E_OK != StartScheduleTableSynchron(scheduletableid))\
    {\
      ReturnStatus = RTE_E_OS_ERROR;\
    }\
  }while(0)

/* OS API to invoke ActivateTask API from Task body when DET is OFF */
#define RTE_M_OSActivateTask(taskid) \
/*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */\
  Rte_Task_Activate_Internal(taskid);\
  (void)ActivateTask(taskid)

/* OS API to invoke SetRelAlarm API from Task body when DET is OFF */
#define RTE_M_OSSetRelAlarm(alarmid, inc, cyc) \
(void)SetRelAlarm(alarmid, inc, cyc)

/* OS API to invoke SetAbsAlarm API from Task body when DET is OFF */
#define RTE_M_OSSetAbsAlarm(alarmid, start, cyc) \
(void)SetAbsAlarm(alarmid, start, cyc)

/* OS API to invoke ChainTask API from Task body when DET is OFF */
#define RTE_M_OSChainTask(taskid) \
(void)ChainTask(taskid)

/* OS API to invoke TerminateTask API from Task body when DET is OFF */
#define RTE_M_OSTerminateTask() \
(void)TerminateTask()

/* OS API to invoke SetEvent API from Task body when DET is OFF */
#define RTE_M_OSSetEvent(taskid, EventId) \
/*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */\
  Rte_Task_SetEvent_Internal(taskid, EventId);\
  (void)SetEvent(taskid, EventId)

/* OS API to invoke ClearEvent API from Task body when DET is OFF */
#define RTE_M_OSClearEvent(EventId) \
(void)ClearEvent(EventId)

/* OS API to invoke WaitEvent API from Task body when DET is OFF */
#define RTE_M_OSWaitEvent(taskid, EventId) \
/*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */\
Rte_Task_WaitEvent_Internal(taskid, EventId);\
(void)WaitEvent(EventId);\
/*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */\
Rte_Task_WaitEventRet_Internal(taskid, EventId)

/* OS API to invoke GetEvent API from Task body when DET is OFF */
#define RTE_M_OSGetEvent(taskid, EventId) \
(void)GetEvent(taskid,EventId)

/* OS API to invoke Schedule API from Task Body when DET is OFF */
#define RTE_M_OSSchedule() \
(void)Schedule()

 /* OS API to invoke GetCounterValue API from Task body when DET is OFF */
  #define RTE_M_OSGetCounterValue(counterid, tickvalueref)\
  (void)GetCounterValue(counterid, tickvalueref)

/* OS API to invoke GetElapsedValue API from Task body when DET is OFF */
#define RTE_M_OSGetElapsedValue(counterid, prevtickvalueref, elapsedtickvalueref)\
(void)GetElapsedValue(counterid, prevtickvalueref, elapsedtickvalueref)

/* OS API to invoke StartScheduleTableRel API from RTE API when DET is OFF */
#define RTE_M_OSStartScheduleTableRel(scheduletableid, offset)\
(void)StartScheduleTableRel(scheduletableid, offset)

/* OS API to invoke StartScheduleTableAbs API from RTE API when DET is OFF */
#define RTE_M_OSStartScheduleTableAbs(scheduletableid, start)\
(void)StartScheduleTableAbs(scheduletableid, start)

/* OS API to invoke StartScheduleTableSynchron API from RTE API when DET is OFF */
#define RTE_M_OSStartScheduleTableSynchron(scheduletableid)\
(void)StartScheduleTableSynchron(scheduletableid)

/* OS API to invoke StartScheduleTableRel API from RTE START API when DET is OFF */
#define RTESTARTAPI_M_OSStartScheduleTableRel(scheduletableid, offset, ReturnStatus)\
  do \
  {\
    if((E_OK != StartScheduleTableRel(scheduletableid, offset)) && (RTE_E_OK == ReturnStatus))\
    {\
      ReturnStatus = RTE_E_LIMIT;\
    }\
  }while(0)

/* OS API to invoke StartScheduleTableAbs API from RTE START API when DET is OFF */
#define RTESTARTAPI_M_OSStartScheduleTableAbs(scheduletableid, start, ReturnStatus)\
  do \
  {\
    if((E_OK != StartScheduleTableAbs(scheduletableid, start)) && (RTE_E_OK == ReturnStatus))\
    {\
      ReturnStatus = RTE_E_LIMIT;\
    }\
  }while(0)

/* OS API to invoke StartScheduleTableSynchron API from RTE START API when DET is OFF */
#define RTESTARTAPI_M_OSStartScheduleTableSynchron(scheduletableid, ReturnStatus)\
  do \
  {\
    if((E_OK != StartScheduleTableSynchron(scheduletableid)) && (RTE_E_OK == ReturnStatus))\
    {\
      ReturnStatus = RTE_E_LIMIT;\
    }\
  }while(0)

  /* OS API to invoke StopScheduleTable API from RTE Stop API body when DET is OFF */
  #define RTESTOPAPI_M_OSStopScheduleTable(scheduletableid, ReturnStatus)\
  do\
  {\
    if((E_OK != StopScheduleTable(scheduletableid)) && (RTE_E_OK == ReturnStatus))\
    {\
      ReturnStatus = RTE_E_LIMIT;\
    }\
  }while(0)

  /* OS API to invoke StopScheduleTable API from Task API body when DET is OFF */
  #define RTE_M_OSStopScheduleTable(scheduletableid)\
(void)StopScheduleTable(scheduletableid)

/* OS API to invoke StopScheduleTable API from RTE API body when DET is OFF */
#define RTEAPI_M_OSStopScheduleTable(scheduletableid, ReturnStatus, ServiceId)\
  do\
  {\
    if(E_OK != StopScheduleTable(scheduletableid))\
    {\
      ReturnStatus = RTE_E_OS_ERROR;\
    }\
  }while(0)

  /* OS API to invoke CancelAlarm API from RTE Stop API body when DET is OFF */
  #define RTESTOPAPI_M_OSCancelAlarm(alarmid, ReturnStatus)\
  do\
  {\
    if((E_OK != CancelAlarm(alarmid)) && (RTE_E_OK == ReturnStatus))\
    {\
      ReturnStatus = RTE_E_LIMIT;\
    }\
  }while(0)

/* OS API to invoke ActivateTask API from RTE Start API body when DET is OFF */
#define RTESTARTAPI_M_OSActivateTask(taskid, ReturnStatus)\
  do \
  {\
  /*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */\
    Rte_Task_Activate_Internal(taskid);\
    if((E_OK != ActivateTask(taskid)) && (RTE_E_OK == ReturnStatus))\
    {\
      ReturnStatus = RTE_E_LIMIT;\
    }\
  }while(0)

/* OS API to invoke SetRelAlarm API from RTE START API when DET is OFF */
#define RTESTARTAPI_M_OSSetRelAlarm(alarmid, inc, cyc, ReturnStatus)\
  do \
  {\
    if((E_OK != SetRelAlarm(alarmid, inc, cyc)) && (RTE_E_OK == ReturnStatus))\
    {\
      ReturnStatus = RTE_E_LIMIT;\
    }\
  }while(0)

/* OS API to invoke SetAbsAlarm API from RTE START API when DET is OFF */
#define RTESTARTAPI_M_OSSetAbsAlarm(alarmid, start, cyc, ReturnStatus)\
  do \
  {\
    if((E_OK != SetAbsAlarm(alarmid, start, cyc)) && (RTE_E_OK == ReturnStatus))\
    {\
      ReturnStatus = RTE_E_LIMIT;\
    }\
  }while(0)

/* OS API to invoke StartScheduleTableRel API from SchM START API when DET is OFF */
#define SCHMSTARTAPI_M_OSStartScheduleTableRel(scheduletableid, offset)\
(void)StartScheduleTableRel(scheduletableid, offset)

/* OS API to invoke StartScheduleTableAbs API from SchM START API when DET is OFF */
#define SCHMSTARTAPI_M_OSStartScheduleTableAbs(scheduletableid, start)\
(void)StartScheduleTableAbs(scheduletableid, start)

/* OS API to invoke StartScheduleTableSynchron API from SchM START API when DET is OFF */
#define SCHMSTARTAPI_M_OSStartScheduleTableSynchron(scheduletableid)\
(void)StartScheduleTableSynchron(scheduletableid)

/* OS API to invoke StartScheduleTableRel API from SchM API when DET is OFF */
#define SCHMAPI_M_OSStartScheduleTableRel(scheduletableid, offset, ReturnStatus, ServiceId)\
  do\
  {\
    if(E_OK != StartScheduleTableRel(scheduletableid, offset))\
    {\
      ReturnStatus = RTE_E_OS_ERROR;\
    }\
  }while(0)

/* OS API to invoke StartScheduleTableAbs API from SchM API when DET is OFF */
#define SCHMAPI_M_OSStartScheduleTableAbs(scheduletableid, start, ReturnStatus, ServiceId)\
  do\
  {\
    if(E_OK != StartScheduleTableAbs(scheduletableid, start))\
    {\
      ReturnStatus = RTE_E_OS_ERROR;\
    }\
  }while(0)

/* OS API to invoke StartScheduleTableSynchron API from SchM API when DET is OFF */
#define SCHMAPI_M_OSStartScheduleTableSynchron(scheduletableid, ReturnStatus, ServiceId)\
  do\
  {\
    if(E_OK != StartScheduleTableSynchron(scheduletableid))\
    {\
      ReturnStatus = RTE_E_OS_ERROR;\
    }\
  }while(0)

/* OS API to invoke StartScheduleTableRel API from BSW Task API when DET is OFF */
#define SCHM_M_OSStartScheduleTableRel(scheduletableid, offset)\
(void)StartScheduleTableRel(scheduletableid, offset)

/* OS API to invoke StartScheduleTableAbs API from BSW Task API when DET is OFF */
#define SCHM_M_OSStartScheduleTableAbs(scheduletableid, start)\
(void)StartScheduleTableAbs(scheduletableid, start)

/* OS API to invoke StartScheduleTableSynchron API from BSW Task API when DET is OFF */
#define SCHM_M_OSStartScheduleTableSynchron(scheduletableid)\
(void)StartScheduleTableSynchron(scheduletableid)

/* OS API to invoke StopScheduleTable API from SchM API body when DET is OFF */
#define SCHMDEINITAPI_M_OSStopScheduleTable(scheduletableid) \
(void)StopScheduleTable(scheduletableid)

  /* OS API to invoke StopScheduleTable API from Task API body when DET is OFF */
  #define SCHM_M_OSStopScheduleTable(scheduletableid)\
(void)StopScheduleTable(scheduletableid)

/* OS API to invoke StopScheduleTable API from SchM API body when DET is OFF */
#define SCHMAPI_M_OSStopScheduleTable(scheduletableid, ReturnStatus, ServiceId)\
  do\
  {\
    if(E_OK != StopScheduleTable(scheduletableid))\
    {\
      ReturnStatus = RTE_E_OS_ERROR;\
    }\
  }while(0)

/* OS API to invoke ActivateTask API from SchM Start API body when DET is OFF */
#define SCHMSTARTAPI_M_OSActivateTask(taskid) \
/*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */\
  Rte_Task_Activate_Internal(taskid);\
  (void)ActivateTask(taskid)

/* OS API to invoke SetRelAlarm API from SchM START API when DET is OFF */
#define SCHMSTARTAPI_M_OSSetRelAlarm(alarmid, inc, cyc)\
(void)SetRelAlarm(alarmid, inc, cyc)

/* OS API to invoke SetAbsAlarm API from SchM START API when DET is OFF */
#define SCHMSTARTAPI_M_OSSetAbsAlarm(alarmid, start, cyc)\
(void)SetAbsAlarm(alarmid, start, cyc)

/* OS API to invoke CancelAlarm API from RTE API when DET is OFF */
#define SCHMDEINITAPI_M_OSCancelAlarm(alarmid)\
(void)CancelAlarm(alarmid)

/* OS API to invoke ActivateTask API from RTE Implicit API body when DET is OFF */
#define RTEIMPLICITAPI_M_OSActivateTask(taskid) \
/*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */\
  Rte_Task_Activate_Internal(taskid);\
  (void)ActivateTask(taskid)

/* OS API to invoke SetEvent API from RTE API when DET is OFF */
#define RTEIMPLICITAPI_M_OSSetEvent(taskid, EventId) \
/*LDRA_INSPECTED 57 S ; Source: MISRA:2012 R.2.2 */\
  Rte_Task_SetEvent_Internal(taskid, EventId);\
  (void)SetEvent(taskid, EventId)

/******************************************************************************/
/*                 Compatibility between C/C++ Languages End                  */
/******************************************************************************/
#ifdef __cplusplus
}
#endif

/******************************************************************************/
/*                  Multiple Header Inclusion Protection End                  */
/******************************************************************************/
#endif

/******************************************************************************/
/*                              End of the file                               */
/******************************************************************************/
