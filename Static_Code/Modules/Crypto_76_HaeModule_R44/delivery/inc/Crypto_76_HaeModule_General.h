/*!
  @file Crypto_76_HaeModule_General.h
  @brief General API header file
  @note Copyright 2020 by HYUNDAI AUTOEVER Corp. All rights reserved.
*/
#ifndef CRYPTO_76_HAEMODULE_GENERAL_H
#define CRYPTO_76_HAEMODULE_GENERAL_H

boolean HaeModule_Is_Crypto_Init(void);
void HaeModule_Crypto_Init( const Crypto_76_HaeModule_ConfigType* configPtr );
void HaeModule_Crypto_GetVersionInfo( Std_VersionInfoType* versioninfo );

#endif /* CRYPTO_76_HAEMODULE_GENERAL_H */
