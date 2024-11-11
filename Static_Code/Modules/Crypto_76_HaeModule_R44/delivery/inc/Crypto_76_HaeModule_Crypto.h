#ifndef CRYPTO_76_HAEMODULE_CRYPTO_H
#define CRYPTO_76_HAEMODULE_CRYPTO_H

#include "Crypto_76_HaeModule.h"
#ifdef HAEMODULE_CRYPTOOBJECT_HAEHSM_SUPPORT
#include "Hsm_Types.h"
#include "Hsm_KeyTypes.h"
#include "Hsm_HostAPI.h"
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

typedef void                        CryptoPrimitiveData;
typedef Crypto_AlgorithmFamilyType  Crypto_PrimitiveAlgorithmFamilyType;
typedef Crypto_AlgorithmModeType    Crypto_PrimitiveAlgorithmModeType;
typedef Std_ReturnType (*Crypto_PrimitiveProcess)( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
typedef Crypto_ServiceInfoType      Crypto_PrimitiveServiceInfoType;

typedef struct _CryptoObjectQueue {
    uint32                          jobPriority;
    Crypto_JobType                  *job;
    struct _CryptoObjectQueue       *next;
} CryptoObjectQueue;

typedef struct {
    uint32                          jobState;
    uint32                          jobId;
    Crypto_JobType                  *job;
    uint32                          Oldmode;        /* Saves the mode completed just before. */
    const void                      *Primitive;
    uint32                          PrimitiveMode;  /* Saves the original mode requested. */
    uint32                          mode;           /* Saves the current mode that the primitive is executing. */
    uint32                          state;          /* Saves the current state that the primitive is executing. */
} CryptoObjectJobInfo;

typedef struct {
    Crypto_PrimitiveServiceInfoType         CryptoPrimitiveService;
    Crypto_PrimitiveAlgorithmFamilyType     CryptoPrimitiveAlgorithmFamily;
    Crypto_PrimitiveAlgorithmFamilyType     CryptoPrimitiveAlgorithmSecondaryFamily;
    Crypto_PrimitiveAlgorithmModeType       CryptoPrimitiveAlgorithmMode;
    Crypto_PrimitiveProcess                 CryptoPrimitiveProcess;
} CryptoPrimitive;

typedef struct {
    uint32                          CryptoDriverObjectId;
    uint32                          CryptoQueueSize;
    const CryptoPrimitive*          CryptoPrimitiveRef;
    const uint32                    CryptoPrimitiveNum;
    void*                           CryptoDriverObjectEcucPartitionRef;
    CryptoObjectQueue               *Queue;
    CryptoObjectQueue               *QHead;
    CryptoObjectJobInfo             CurrentJob;
    CryptoPrimitiveData             *PrimitiveData;
    uint32                          ResType_Object;
} CryptoDriverObject;

/*
 * List of service functions for managing Crypto Objects
 */
typedef void (*Crypto_PrimitiveInit)( CryptoDriverObject *Object );
typedef void (*Crypto_PrimitiveGetState)(uint32 *mode, uint32 *state);
typedef void (*Crypto_PrimitiveSetState)(uint32 mode, uint32 state);

typedef struct {
    uint32                      CryptoDriverObjectId;
    Crypto_PrimitiveInit		CryptoPrimitive_Init;
	Crypto_PrimitiveProcess		CryptoPrimitive_CancelJob;
    Crypto_PrimitiveGetState    CryptoPrimitive_GetState;
    Crypto_PrimitiveSetState    CryptoPrimitive_SetState;
} CryptoPrimitiveList;


#define CRYPTO_KE_MAC_KEY                   1
#define CRYPTO_KE_MAC_PROOF                 2
#define CRYPTO_KE_MAC_IV                    1005
#define CRYPTO_KE_KEYGENERATE_SEED          16
#define CRYPTO_KE_SIGNATURE_KEY             1
#define CRYPTO_KE_SIGNATURE_SALT            1013
#define CRYPTO_KE_SIGNATURE_CURVETYPE       29
#define CRYPTO_KE_RANDOM_SEED_STATE         3
#define CRYPTO_KE_RANDOM_ALGORITHM          4
#define CRYPTO_KE_CIPHER_KEY                1
#define CRYPTO_KE_CIPHER_IV                 5
#define CRYPTO_KE_CIPHER_PROOF              6
#define CRYPTO_KE_CIPHER_2NDKEY             7
#define CRYPTO_KE_CIPHER_SEED               1016
#define CRYPTO_KE_KEYEXCHANGE_BASE          8
#define CRYPTO_KE_KEYEXCHANGE_PRIVKEY       9
#define CRYPTO_KE_KEYEXCHANGE_OWNPUBKEY     10
#define CYRPTO_KE_KEYEXCHANGE_SHAREDVALUE   1
#define CRYPTO_KE_KEYEXCHANGE_ALGORITHM     12
#define CRYPTO_KE_KEYEXCHANGE_CURVETYPE     29
#define CRYPTO_KE_KEYDERIVATION_HSMKEYINDEX (1001)
#define CRYPTO_KE_KEYDERIVATION_PASSWORD    1
#define CRYPTO_KE_KEYDERIVATION_SALT        13
#define CRYPTO_KE_KEYDERIVATION_ITERATIONS  14
#define CRYPTO_KE_KEYDERIVATION_ALGORITHM   15
#define CRYPTO_KE_KEYDERIVATION_CURVETYPE   29
#define CRYPTO_KE_KEYGENERATE_KEY           1
#define CRYPTO_KE_KEYGENERATE_SEED          16
#define CRYPTO_KE_KEYGENERATE_ALGORITHM     17
#define CRYPTO_KE_KEYGENERATE_CURVETYPE     29


typedef enum {
    CRYPTO_RA_DENIED        = 0x01,
    CRYPTO_RA_INTERNAL_COPY = 0x02,
    CRYPTO_RA_ALLOWED       = 0x03,
    CRYPTO_RA_ENCRYPTED     = 0x04
} Crypto_ReadAccessType;

typedef enum {
    CRYPTO_WA_DENIED        = 0x01,
    CRYPTO_WA_INTERNAL_COPY = 0x02,
    CRYPTO_WA_ALLOWED       = 0x03,
    CRYPTO_WA_ENCRYPTED     = 0x04
} Crypto_WriteAccessType;

typedef enum {
    CRYPTO_KE_FORMAT_BIN_OCTET                  = 0x01,
    CRYPTO_KE_FORMAT_BIN_SHEKEYS                = 0x02,
    CRYPTO_KE_FORMAT_BIN_IDENT_PRIVATEKEY_PKCS8 = 0x03,
    CRYPTO_KE_FORMAT_BIN_IDENT_PUBLICKEY        = 0x04,
    CRYPTO_KE_FORMAT_BIN_RSA_PRIVATEKEY         = 0x05,
    CRYPTO_KE_FORMAT_BIN_RSA_PUBLICKEY          = 0x06,
    CRYPTO_KE_FORMAT_BIN_CERT_X509_V3           = 0x07,
    CRYPTO_KE_FORMAT_BIN_CERT_CVC               = 0x08
} Crypto_KeyFormatType;

typedef enum {
    HAEHSM_KEY_TYPE_NONE                        = 0x00,
    HAEHSM_KEY_TYPE_AES                         = 0x01,
    HAEHSM_KEY_TYPE_RSA                         = 0x02,
    HAEHSM_KEY_TYPE_ECC                         = 0x03,
    HAEHSM_KEY_TYPE_ECC_P521R1                  = 0x04,
    HAEHSM_KEY_TYPE_ECC_ED448                   = 0x05,
    HAEHSM_KEY_TYPE_ECC_X448                    = 0x06
} Crypto_HaeHsmKeyType;

typedef struct _Crypto_KeyElement {
    uint32                      CryptoKeyElementId;
    uint32                      CryptoKeyElementSize;
    const uint8*                CryptoKeyElementInitValue;
    Crypto_ReadAccessType       CryptoKeyElementReadAccess;
    boolean                     CryptoKeyElementAllowPartialAccess;
    boolean                     CryptoKeyElementPersist;
    Crypto_WriteAccessType      CryptoKeyElementWriteAccess;
    Crypto_KeyFormatType        CryptoKeyElementFormat;
    boolean                     CryptoKeyElementValueState;
    uint32                      CryptoKeyElementValueSize;
    uint8*                      CryptoKeyElementValue;
    Crypto_HaeHsmKeyType        CryptoKeyElementHsmKeyType;
    uint16                      CryptoKeyElementHsmKeyIndex;
} CryptoKeyElement;

typedef struct  {
    CryptoKeyElement**          CryptoKeyElementRef;
    uint32                      CryptoKeyElementNum;
} CryptoKeyType;

typedef struct {
    uint32                      CryptoKeyId;
    CryptoKeyType*              CryptoKeyTypeRef;
    boolean                     CryptoKeyState;
} CryptoKey;


#endif /* CRYPTO_76_HAEMODULE_CRYPTO_H */

