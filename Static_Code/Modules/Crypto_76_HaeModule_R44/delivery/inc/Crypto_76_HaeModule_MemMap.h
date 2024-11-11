/*!
  @file Crypto_76_HaeModule_MemMap.h
  @brief Memory Map Protection header file
  @note Copyright 2020 by HYUNDAI AUTOEVER Corp. All rights reserved.
*/
#ifdef __cplusplus
extern "C"
{
#endif
/******************************************************************************/
/*                           Memory Map Protection                            */
/******************************************************************************/
#if   defined (CRYPTO_76_HAEMODULE_START_ROM_CONST)
  #undef CRYPTO_76_HAEMODULE_START_ROM_CONST
  #if defined(__TASKING__)
  #pragma section all "CRYPTO_76_HAEMODULE_ROM_CONST_UNSPECIFIED"
  #elif defined(__DCC__)
  #pragma section CONST "CRYPTO_76_HAEMODULE_ROM_CONST_UNSPECIFIED"
  #elif defined(__ghs__)
  // TEST //#pragma ghs section rodata=".rodata.CRYPTO_76_HAEMODULE_ROM_CONST_UNSPECIFIED"
  #else
  //#error "Please specify compiler."
  #endif
#elif defined (CRYPTO_76_HAEMODULE_STOP_ROM_CONST)
  #undef CRYPTO_76_HAEMODULE_STOP_ROM_CONST
  #if defined(__TASKING__)
  #pragma section all restore
  #elif defined(__DCC__)
  #pragma section CONST
  #elif defined(__ghs__)
  // TEST //#pragma ghs section rodata=default
  #else
  //#error "Please specify compiler."
  #endif
#elif defined (CRYPTO_76_HAEMODULE_START_RAM_VAR_CLEARED)
  #undef CRYPTO_76_HAEMODULE_START_RAM_VAR_CLEARED
  #if defined(__TASKING__)
  #pragma section all "CRYPTO_76_HAEMODULE_RAM_VAR_CLEARED_UNSPECIFIED"
  #elif defined(__DCC__)
  #pragma section DATA "CRYPTO_76_HAEMODULE_RAM_VAR_INIT_UNSPECIFIED" "CRYPTO_76_HAEMODULE_RAM_VAR_CLEARED_UNSPECIFIED"
  #elif defined(__ghs__)
  // TEST //#pragma ghs section bss=".bss.CRYPTO_76_HAEMODULE_RAM_VAR_CLEARED_UNSPECIFIED"
  #else
  //#error "Please specify compiler."
  #endif
#elif defined (CRYPTO_76_HAEMODULE_STOP_RAM_VAR_CLEARED)
  #undef CRYPTO_76_HAEMODULE_STOP_RAM_VAR_CLEARED
  #if defined(__TASKING__)
  #pragma section all restore
  #elif defined(__DCC__)
  #pragma section DATA
  #elif defined(__ghs__)
  // TEST //#pragma ghs section bss=default
  #else
  //#error "Please specify compiler."
  #endif
#elif defined (CRYPTO_76_HAEMODULE_START_RAM_VAR_INIT)
  #undef CRYPTO_76_HAEMODULE_START_RAM_VAR_INIT
  #if defined(__TASKING__)
  #pragma section all "CRYPTO_76_HAEMODULE_RAM_VAR_INIT_UNSPECIFIED"
  #elif defined(__DCC__)
  #pragma section DATA "CRYPTO_76_HAEMODULE_RAM_VAR_INIT_UNSPECIFIED" "CRYPTO_76_HAEMODULE_RAM_VAR_CLEARED_UNSPECIFIED"
  #elif defined(__ghs__)
  // TEST //#pragma ghs section data=".data.CRYPTO_76_HAEMODULE_RAM_VAR_INIT_UNSPECIFIED"
  #else
  //#error "Please specify compiler."
  #endif
#elif defined (CRYPTO_76_HAEMODULE_STOP_RAM_VAR_INIT)
  #undef CRYPTO_76_HAEMODULE_STOP_RAM_VAR_INIT
  #if defined(__TASKING__)
  #pragma section all restore
  #elif defined(__DCC__)
  #pragma section DATA
  #elif defined(__ghs__)
  // TEST //#pragma ghs section data=default
  #else
    //#error "Please specify compiler."
  #endif
#elif defined (CRYPTO_76_HAEMODULE_START_SEC_CODE)
  #undef CRYPTO_76_HAEMODULE_START_SEC_CODE
  #if defined(__TASKING__)
  #pragma section code "CRYPTO_76_HAEMODULE_SEC_CODE"
  #elif defined(__DCC__)
  #pragma section CODE "CRYPTO_76_HAEMODULE_SEC_CODE"
  #elif defined(__ghs__)
  // TEST //#pragma ghs section text=".text.CRYPTO_76_HAEMODULE_SEC_CODE"
  #else
  //#error "Please specify compiler."
  #endif
#elif defined (CRYPTO_76_HAEMODULE_STOP_SEC_CODE)
  #undef CRYPTO_76_HAEMODULE_STOP_SEC_CODE
  #if defined(__TASKING__)
  #pragma section code restore
  #elif defined(__DCC__)
  #pragma section CODE
  #elif defined(__ghs__)
  // TEST //#pragma ghs section text=default
  #else
  //#error "Please specify compiler."
  #endif
#else

/*To be used if no memory section is found */
#define SECTION_NOT_FOUND

#endif
/******************************************************************************/
/*                 Compatibility between C/C++ Languages End                  */
/******************************************************************************/
#ifdef __cplusplus
}
#endif
/******************************************************************************/
/*                              End of the file                               */
/******************************************************************************/
