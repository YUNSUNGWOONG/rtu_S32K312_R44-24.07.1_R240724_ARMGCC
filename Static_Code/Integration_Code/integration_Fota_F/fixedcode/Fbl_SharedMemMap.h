/* polyspace-begin MISRA-C3:D4.10 [Not a defect:Low] "No Impact of this rule violation" */
/*******************************************************************************
**  FILE-NAME: Fbl_SharedMemMap.h                                             **
**                                                                            **
**  MODULE-NAME: AUTOSAR FBL Module                                           **
**                                                                            **
**  NOTE: This file is auto generated, do not edit this file manually.        **
**                                                                            **
********************************************************************************

********************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  Tool Version: 2.2.0.0                                                       **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            **
********************************************************************************
**                      File Generation Information                           **
*******************************************************************************/
/*
 * INPUT FILE:    Configuration\Ecu\Ecud_Fbl.arxml
 * GENERATED ON: The time-stamp is removed
 */


/* polyspace-begin MISRA-C3:D1.1,20.5 [Not a Defect:Medium] "#pragma is used for assembler" */
#if defined (MAINSW_START_SEC_CRC)
  #undef MAINSW_START_SEC_CRC
  #ifdef __TASKING__
    #pragma section farrom "MAINSW_CRC"
  #elif defined __GHS__
    // TEST //#pragma ghs section rodata="MAINSW_CRC"
  #endif
#elif defined (MAINSW_STOP_SEC_CRC)
  #undef MAINSW_STOP_SEC_CRC
  #ifdef __TASKING__
    #pragma section farrom restore
  #elif defined __GHS__
    // TEST //#pragma ghs section
  #endif

#else
/**
 * Error ...! no memory section is found
 */
  #error "Fbl_SharedMemMap.h: No valid section define found...!"

/**
 * End of START_FBL_SHARED_MEMMAP
 */
#endif
/* polyspace-end MISRA-C3:D1.1,20.5 [Not a Defect:Medium] "#pragma is used for assembler" */
/* polyspace-end MISRA-C3:D4.10 [Not a defect:Low] "No Impact of this rule violation" */
/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
