#ifndef CSM_TYPES_H
#define CSM_TYPES_H

#ifdef __cplusplus
extern "C"{
#endif

#include "Csm.h"

/* AUTOSAR Key Element Index Definition */
/* MAC */
#ifndef CRYPTO_KE_MAC_KEY
#define CRYPTO_KE_MAC_KEY                               ((uint32)1U)    /* Key Material */
#endif

#ifndef CRYPTO_KE_MAC_PROOF
#define CRYPTO_KE_MAC_PROOF                             ((uint32)2U)    /* Proof (SHE) */
#endif

/* Signature */
#ifndef CRYPTO_KE_SIGNATURE_KEY
#define CRYPTO_KE_SIGNATURE_KEY                         ((uint32)1U)    /* Key Material */
#endif

/* Random */
#ifndef CRYPTO_KE_RANDOM_SEED_STATE
#define CRYPTO_KE_RANDOM_SEED_STATE                     ((uint32)3U)    /* Seed State */
#endif

#ifndef CRYPTO_KE_RANDOM_ALGORITHM
#define CRYPTO_KE_RANDOM_ALGORITHM                      ((uint32)4U)    /* Algorithm */
#endif

/* Cipher/AEAD */
#ifndef CRYPTO_KE_CIPHER_KEY
#define CRYPTO_KE_CIPHER_KEY                            ((uint32)1U)    /* Key Material */
#endif

#ifndef CRYPTO_KE_CIPHER_IV
#define CRYPTO_KE_CIPHER_IV                             ((uint32)5U)    /* Init Vector */
#endif

#ifndef CRYPTO_KE_CIPHER_PROOF
#define CRYPTO_KE_CIPHER_PROOF                          ((uint32)6U)    /* Proof (SHE) */
#endif

#ifndef CRYPTO_KE_CIPHER_2NDKEY
#define CRYPTO_KE_CIPHER_2NDKEY                         ((uint32)7U)    /* 2nd Key Material */
#endif

/* Key Exchange */
#ifndef CRYPTO_KE_KEYEXCHANGE_BASE
#define CRYPTO_KE_KEYEXCHANGE_BASE                      ((uint32)8U)    /* Base */
#endif

#ifndef CRYPTO_KE_KEYEXCHANGE_PRIVKEY
#define CRYPTO_KE_KEYEXCHANGE_PRIVKEY                   ((uint32)9U)    /* Private Key */
#endif

#ifndef CRYPTO_KE_KEYEXCHANGE_OWNPUBKEY
#define CRYPTO_KE_KEYEXCHANGE_OWNPUBKEY                 ((uint32)10U)   /* Own Public Key */
#endif

#ifndef CYRPTO_KE_KEYEXCHANGE_SHAREDVALUE
#define CYRPTO_KE_KEYEXCHANGE_SHAREDVALUE               ((uint32)1U)    /* Shared Value */
#endif

#ifndef CRYPTO_KE_KEYEXCHANGE_ALGORITHM
#define CRYPTO_KE_KEYEXCHANGE_ALGORITHM                 ((uint32)12U)   /* Algorithm */
#endif

/* Key Derivation */
#ifndef CRYPTO_KE_KEYDERIVATION_PASSWORD
#define CRYPTO_KE_KEYDERIVATION_PASSWORD                ((uint32)1U)    /* Password */
#endif

#ifndef CRYPTO_KE_KEYDERIVATION_SALT
#define CRYPTO_KE_KEYDERIVATION_SALT                    ((uint32)13U)   /* Salt */
#endif

#ifndef CRYPTO_KE_KEYDERIVATION_ITERATIONS
#define CRYPTO_KE_KEYDERIVATION_ITERATIONS              ((uint32)14U)   /* Iterations */
#endif

#ifndef CRYPTO_KE_KEYDERIVATION_ALGORITHM
#define CRYPTO_KE_KEYDERIVATION_ALGORITHM               ((uint32)15U)   /* Algorithm */
#endif
/* Key Generate */
#ifndef CRYPTO_KE_KEYGENERATE_KEY
#define CRYPTO_KE_KEYGENERATE_KEY                       ((uint32)1U)    /* Algorithm */
#endif

#ifndef CRYPTO_KE_KEYGENERATE_SEED
#define CRYPTO_KE_KEYGENERATE_SEED                      ((uint32)16U)   /* Algorithm */
#endif

#ifndef CRYPTO_KE_KEYGENERATE_ALGORITHM
#define CRYPTO_KE_KEYGENERATE_ALGORITHM                 ((uint32)17U)   /* Algorithm */
#endif
/* Certificate Parsing */
#ifndef CRYPTO_KE_CERTIFICATE_DATA
#define CRYPTO_KE_CERTIFICATE_DATA                      ((uint32)0U)    /* Certificate */
#endif

#ifndef CRYPTO_KE_CERTIFICATE_PARSING_FORMAT
#define CRYPTO_KE_CERTIFICATE_PARSING_FORMAT            ((uint32)18U)   /* Format */
#endif

#ifndef CRYPTO_KE_CERTIFICATE_CURRENT_TIME
#define CRYPTO_KE_CERTIFICATE_CURRENT_TIME              ((uint32)19U)   /* Current time */
#endif

#ifndef CRYPTO_KE_CERTIFICATE_VERSION
#define CRYPTO_KE_CERTIFICATE_VERSION                   ((uint32)20U)   /* Version */
#endif

#ifndef CRYPTO_KE_CERTIFICATE_SERIALNUMBER
#define CRYPTO_KE_CERTIFICATE_SERIALNUMBER              ((uint32)21U)   /* Serial Number */
#endif

#ifndef CRYPTO_KE_CERTIFICATE_SIGNATURE_ALGORITHM
#define CRYPTO_KE_CERTIFICATE_SIGNATURE_ALGORITHM       ((uint32)22U)   /* Signature Algorithm */
#endif

#ifndef CRYPTO_KE_CERTIFICATE_ISSUER
#define CRYPTO_KE_CERTIFICATE_ISSUER                    ((uint32)23U)   /* Issuer */
#endif

#ifndef CRYPTO_KE_CERTIFICATE_VALIDITY_NOT_BEFORE
#define CRYPTO_KE_CERTIFICATE_VALIDITY_NOT_BEFORE       ((uint32)24U)   /* Validity Start */
#endif

#ifndef CRYPTO_KE_CERTIFICATE_VALIDITY_NOT_AFTER
#define CRYPTO_KE_CERTIFICATE_VALIDITY_NOT_AFTER        ((uint32)25U)   /* Validity End */
#endif

#ifndef CRYPTO_KE_CERTIFICATE_SUBJECT
#define CRYPTO_KE_CERTIFICATE_SUBJECT                   ((uint32)26U)   /* Subject */
#endif

#ifndef CRYPTO_KE_CERTIFICATE_SUBJECT_PUBLIC_KEY
#define CRYPTO_KE_CERTIFICATE_SUBJECT_PUBLIC_KEY        ((uint32)1U)    /* Subject Public Key */
#endif

#ifndef CRYPTO_KE_CERTIFICATE_EXTENSIONS
#define CRYPTO_KE_CERTIFICATE_EXTENSIONS                ((uint32)27U)   /* Extensions */
#endif

#ifndef CRYPTO_KE_CERTIFICATE_SIGNATURE
#define CRYPTO_KE_CERTIFICATE_SIGNATURE                 ((uint32)28U)   /* Signature */
#endif

#ifdef __cplusplus
}
#endif

#endif /* CSM_TYPES_H */
