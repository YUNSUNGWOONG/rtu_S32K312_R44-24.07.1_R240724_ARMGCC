/*!
  @file Crypto_76_HaeModule_Det.h
  @brief DET(Default Error Tracer) header file
  @note Copyright 2020 by HYUNDAI AUTOEVER Corp. All rights reserved.
*/
#ifndef CRYPTO_76_HAEMODULE_DET_H
#define CRYPTO_76_HAEMODULE_DET_H

#define CRYPTO_MODULE_ID        114
#define CRYPTO_INSTANCE_ID      0

typedef enum {
    CRYPTO_API_INIT                     = 0x00,
    CRYPTO_API_GETVERSIONINFO           = 0x01,
    CRYPTO_API_PROCESSJOB               = 0x03,
    CRYPTO_API_KEYELEMENTSET            = 0x04,
    CRYPTO_API_KEYSETVALID              = 0x05,
    CRYPTO_API_KEYELEMENTGET            = 0x06,
    CRYPTO_API_KEYGENERATE              = 0x07,
    CRYPTO_API_KEYDERIVE                = 0x08,
    CRYPTO_API_KEYEXCHANGECALCPUBVAL    = 0x09,
    CRYPTO_API_KEYEXCHANGECALCSECRET    = 0x0A,
    CRYPTO_API_CERTIFICATEPARSE         = 0x0B,
    CRYPTO_API_MAINFUNCTION             = 0x0C,
    CRYPTO_API_RANDOMSEED               = 0x0D,
    CRYPTO_API_CANCELJOB                = 0x0E,
    CRYPTO_API_KEYELEMENTCOPY           = 0x0F,
    CRYPTO_API_KEYCOPY                  = 0x10,
    CRYPTO_API_KEYELEMENTIDSGET         = 0x11,
    CRYPTO_API_CERTIFICATEVERIFY        = 0x12,
    CRYPTO_API_KEYELEMENTPARTIAL        = 0x13
} CRYPTO_DET_APIID;

/* [SWS_Crypto_00040] Development Error Types */
typedef enum {
    CRYPTO_DET_E_UNINIT                 = 0x00,
    CRYPTO_DET_E_INIT_FAILED            = 0x01,
    CRYPTO_DET_E_PARAM_POINTER          = 0x02,
    CRYPTO_DET_E_PARAM_HANDLE           = 0x04,
    CRYPTO_DET_E_PARAM_VALUE            = 0x05
} CRYPTO_DET_ERRORID;

/* [SWS_Crypto_00194] Runtime Error Types */
typedef enum {
    CRYPTO_DET_E_RE_SMALL_BUFFER        = 0x00,
    CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE   = 0x01,
    CRYPTO_DET_E_RE_KEY_READ_FAIL       = 0x02,
    CRYPTO_DET_E_RE_ENTROPY_EXHAUSTED   = 0x03
} CRYPTO_DET_RUNTIME_ERRORID;


Std_ReturnType HaeModule_Det_ReportError( CRYPTO_DET_APIID ApiId, CRYPTO_DET_ERRORID ErrorId );
Std_ReturnType HaeModule_Det_ReportRuntimeError( CRYPTO_DET_APIID ApiId, CRYPTO_DET_RUNTIME_ERRORID ErrorId );

#endif /* CRYPTO_76_HAEMODULE_DET_H */
