/*!
  @file Crypto_76_HaeModule_Job.h
  @brief Job Processing Interface header file
  @note Copyright 2020 by HYUNDAI AUTOEVER Corp. All rights reserved.
*/
#ifndef CRYPTO_76_HAEMODULE_JOB_H
#define CRYPTO_76_HAEMODULE_JOB_H

typedef enum
{
    HAEMODULE_JOBSTATE_IDLE       = 0x00,
    HAEMODULE_JOBSTATE_ACTIVE     = 0x01,
    HAEMODULE_JOBSTATE_PROCESSING = 0x02,
    HAEMODULE_JOBSTATE_CANCEL     = 0x03
} HaeModule_JobStateType;

typedef enum
{
    HAEMODULE_PRIMITIVESTATE_INIT = 0,
    HAEMODULE_PRIMITIVESTATE_START,
    HAEMODULE_PRIMITIVESTATE_UPDATE,
    HAEMODULE_PRIMITIVESTATE_UPDATE_WAITRESP,
    HAEMODULE_PRIMITIVESTATE_UPDATE_READRXBUFF,
    HAEMODULE_PRIMITIVESTATE_FINISH,
    HAEMODULE_PRIMITIVESTATE_END
} HaeModule_PrimitiveState;

void HaeModule_Crypto_JobInit(void);
Std_ReturnType HaeModule_Crypto_ProcessJob( uint32 objectId, Crypto_JobType* job );
Std_ReturnType HaeModule_Crypto_CancelJob( uint32 objectId, Crypto_JobType* job );
void HaeModule_Crypto_MainFunction( uint32 objectId );

#endif /* CRYPTO_76_HAEMODULE_JOB_H */
