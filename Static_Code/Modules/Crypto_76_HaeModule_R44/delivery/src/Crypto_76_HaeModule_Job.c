/*!
  @file Crypto_76_HaeModule_Job.c
  @brief Job Processing Interface source file
  @note Copyright 2020 by HYUNDAI AUTOEVER Corp. All rights reserved.
*/
#include "Crypto_76_HaeModule_Crypto.h"
#include "Crypto_76_HaeModule_Common.h"
#include "Crypto_76_HaeModule_General.h"
#include "Crypto_76_HaeModule_Job.h"
#include "Crypto_76_HaeModule_Key.h"
#include "Crypto_76_HaeModule_Det.h"
#include "Crypto_76_HaeModule_HsmPrimitive.h"

extern const CryptoPrimitiveList gHaeModule_CryptoPrimitiveList[HAEMODULE_CRYPTOOBJECTS_NUM];
extern CryptoDriverObject gHaeModule_CryptoDriverObjects[HAEMODULE_CRYPTOOBJECTS_NUM];


#define CRYPTO_76_HAEMODULE_START_SEC_CODE
#include "Crypto_76_HaeModule_MemMap.h"
static CryptoDriverObject* HaeModule_Crypto_Get_Object(uint32 CryptoDriverObjectId)
{
    CryptoDriverObject *Object;
    CryptoDriverObject *FindObject = NULL;
    uint32 i;

    for(i = 0; i < (uint32)HAEMODULE_CRYPTOOBJECTS_NUM; i++)
    {
        Object = &gHaeModule_CryptoDriverObjects[i];
        if(Object->CryptoDriverObjectId == CryptoDriverObjectId)
        {
            FindObject = Object;
            break;
        }
    }

    return FindObject;
}

static const CryptoPrimitive* HaeModule_Crypto_Get_Primitive(const CryptoDriverObject *Object, const Crypto_PrimitiveInfoType *PrimitiveInfo)
{
    const CryptoPrimitive *Primitive;
    const CryptoPrimitive *FindPrimitive = NULL;
    uint32 i;

    for(i = 0; i < Object->CryptoPrimitiveNum; i++)
    {
        Primitive = &Object->CryptoPrimitiveRef[i];

        if((Primitive->CryptoPrimitiveService == PrimitiveInfo->service)
            && (Primitive->CryptoPrimitiveAlgorithmFamily == PrimitiveInfo->algorithm.family)
            && (Primitive->CryptoPrimitiveAlgorithmSecondaryFamily == PrimitiveInfo->algorithm.secondaryFamily)
            && (Primitive->CryptoPrimitiveAlgorithmMode == PrimitiveInfo->algorithm.mode)
        )
        {
            FindPrimitive = Primitive;
            break;
        }
    }

    return FindPrimitive;
}

static const CryptoPrimitiveList* HaeModule_Crypto_Get_PrimitiveList(const uint32 CryptoDriverObjectId)
{
    const CryptoPrimitiveList *PrimitiveList = NULL;
    uint32 i;

    for(i = 0; i < (uint32)HAEMODULE_CRYPTOOBJECTS_NUM; i++)
    {
        if(gHaeModule_CryptoPrimitiveList[i].CryptoDriverObjectId == CryptoDriverObjectId)
        {
            PrimitiveList = (const CryptoPrimitiveList *)&gHaeModule_CryptoPrimitiveList[i];
            break;
        }
    }

    return PrimitiveList;
}

static void Object_Queue_SetInitValue( CryptoObjectQueue *Queue )
{
    Queue->jobPriority = 0;
    Queue->job  = NULL;
    Queue->next = NULL;
}

static void Object_Queue_Init( CryptoDriverObject *Object )
{
    uint32 i;

    for(i = 0; i < Object->CryptoQueueSize; i++)
    {
        Object_Queue_SetInitValue(&Object->Queue[i]);
    }

    Object->QHead = NULL;
}

static CryptoObjectQueue* Object_Queue_GetEmpty( CryptoDriverObject *Object, Crypto_JobType* job )
{
    CryptoObjectQueue* EmptyQueue = NULL;
    uint32 i;

    for(i = 0; i < Object->CryptoQueueSize; i++)
    {
        if(Object->Queue[i].job == NULL)
        {
            Object->Queue[i].jobPriority = job->jobInfo->jobPriority;
            Object->Queue[i].job = job;
            Object->Queue[i].next = NULL;

            EmptyQueue = &Object->Queue[i];
            break;
        }
    }

    return EmptyQueue;
}

static CryptoObjectQueue* Object_Queue_Find( const CryptoDriverObject *Object, const Crypto_JobInfoType *jobInfo )
{
    CryptoObjectQueue* FindQueue = NULL;
    uint32 i;

    for(i = 0; i < Object->CryptoQueueSize; i++)
    {
        if((Object->Queue[i].job != NULL)
            && (Object->Queue[i].job->jobInfo != NULL)
            && (Object->Queue[i].job->jobInfo->jobId == jobInfo->jobId)
        )
        {
            FindQueue = &Object->Queue[i];
            break;
        }
    }

    return FindQueue;
}

static void Object_Queue_Add( CryptoDriverObject *Object, CryptoObjectQueue *NewQueue )
{
    CryptoObjectQueue *PrevQueue = NULL;
    CryptoObjectQueue *Queue;

    /*
     * [SWS_Crypto_00030] The queue shall sort the jobs according to the configured jobs’ priority.
     */
    for(Queue = (CryptoObjectQueue *)Object->QHead; Queue != NULL; Queue = (CryptoObjectQueue *)Queue->next)
    {
        /* The higher the job priority value, the higher the job’s priority */
        if(Queue->jobPriority < NewQueue->jobPriority)
        {
            break;
        }

        PrevQueue = Queue;
    }

    if(PrevQueue == NULL)
    {
        Object->QHead = NewQueue;
    }
    else
    {
        PrevQueue->next = NewQueue;
    }

    NewQueue->next = Queue;
}

static void Object_Queue_Del( CryptoDriverObject *Object, CryptoObjectQueue *TargetQueue )
{
    CryptoObjectQueue *PrevQueue = NULL;
    CryptoObjectQueue *Queue;

    for(Queue = (CryptoObjectQueue *)Object->QHead; Queue != NULL; Queue = (CryptoObjectQueue *)Queue->next)
    {
        if(Queue == TargetQueue)
        {
            break;
        }

        PrevQueue = Queue;
    }

    if(Queue != NULL)
    {
        if(PrevQueue == NULL)
        {
            Object->QHead = (CryptoObjectQueue *)Queue->next;
        }
        else
        {
            PrevQueue->next = Queue->next;
        }

        Object_Queue_SetInitValue(Queue);
    }
    else
    {
        /* It is abnormal state */
        Object_Queue_SetInitValue(TargetQueue);
    }
}

static void HaeModule_Object_SetCurrentJob( CryptoDriverObject *Object, Crypto_JobType* job,
                                        uint32 mode,
                                        uint32 state,
                                        uint32 newJobState)
{
    const CryptoPrimitiveList *PrimitiveList;
    uint32 oldJobState = Object->CurrentJob.jobState;

    if((oldJobState == (uint32)HAEMODULE_JOBSTATE_IDLE) && (newJobState == (uint32)HAEMODULE_JOBSTATE_ACTIVE))
    {
        Object->CurrentJob.jobState         = (uint32)HAEMODULE_JOBSTATE_ACTIVE;
        Object->CurrentJob.jobId            = job->jobInfo->jobId;
        Object->CurrentJob.job              = job;
        Object->CurrentJob.Oldmode          = 0; /* It means that there is not any completed modes yet */
        Object->CurrentJob.Primitive        = HaeModule_Crypto_Get_Primitive(Object, job->jobPrimitiveInfo->primitiveInfo);
        Object->CurrentJob.PrimitiveMode    = mode;
        Object->CurrentJob.mode             = mode;
        Object->CurrentJob.state            = state;

        job->jobState = CRYPTO_JOBSTATE_ACTIVE;
    }
    else if((oldJobState == (uint32)HAEMODULE_JOBSTATE_ACTIVE) && (newJobState == (uint32)HAEMODULE_JOBSTATE_PROCESSING))
    {
        Object->CurrentJob.jobState         = (uint32)HAEMODULE_JOBSTATE_PROCESSING;
        Object->CurrentJob.mode             = mode;
        Object->CurrentJob.state            = state;
    }
    else if((oldJobState == (uint32)HAEMODULE_JOBSTATE_PROCESSING) && (newJobState == (uint32)HAEMODULE_JOBSTATE_PROCESSING))
    {
        Object->CurrentJob.mode             = mode;
        Object->CurrentJob.state            = state;
    }
    else if((oldJobState == (uint32)HAEMODULE_JOBSTATE_PROCESSING) && (newJobState == (uint32)HAEMODULE_JOBSTATE_ACTIVE))
    {
        Object->CurrentJob.jobState         = (uint32)HAEMODULE_JOBSTATE_ACTIVE;
        Object->CurrentJob.Oldmode          = Object->CurrentJob.PrimitiveMode;
        Object->CurrentJob.PrimitiveMode    = 0;
        Object->CurrentJob.mode             = 0;
        Object->CurrentJob.state            = 0;
    }
    else if((oldJobState == (uint32)HAEMODULE_JOBSTATE_ACTIVE) && (newJobState == (uint32)HAEMODULE_JOBSTATE_ACTIVE))
    {
        if(mode == 0)
        {
            Object->CurrentJob.job              = NULL;
            Object->CurrentJob.Oldmode          = Object->CurrentJob.PrimitiveMode;
            Object->CurrentJob.PrimitiveMode    = 0;
            Object->CurrentJob.mode             = 0;
            Object->CurrentJob.state            = 0;
        }
        else
        {
            Object->CurrentJob.job              = job;
            Object->CurrentJob.PrimitiveMode    = mode;
            Object->CurrentJob.mode             = mode;
            Object->CurrentJob.state            = state;
        }
    }
    else if(newJobState == (uint32)HAEMODULE_JOBSTATE_CANCEL)
    {
        if((uint32)Object->CurrentJob.PrimitiveMode != (uint32)0)
        {
            PrimitiveList = HaeModule_Crypto_Get_PrimitiveList(Object->CryptoDriverObjectId);
            if(PrimitiveList != NULL)
            {
                (void)PrimitiveList->CryptoPrimitive_CancelJob(Object->PrimitiveData, NULL);
            }
        }

        Object->CurrentJob.jobState         = (uint32)HAEMODULE_JOBSTATE_IDLE;
        Object->CurrentJob.job              = NULL;
        Object->CurrentJob.Oldmode          = 0; /* It means that there is not any completed modes yet */
        Object->CurrentJob.PrimitiveMode    = 0;
        Object->CurrentJob.mode             = 0;
        Object->CurrentJob.state            = 0;

        job->jobState = CRYPTO_JOBSTATE_IDLE;
    }
    else
    {
        /* Clear current job state */
        Object->CurrentJob.jobState         = (uint32)HAEMODULE_JOBSTATE_IDLE;
        Object->CurrentJob.jobId            = 0;
        Object->CurrentJob.job              = NULL;
        Object->CurrentJob.Oldmode          = 0; /* It means that there is not any completed modes yet */
        Object->CurrentJob.Primitive        = NULL;
        Object->CurrentJob.PrimitiveMode    = 0;
        Object->CurrentJob.mode             = 0;
        Object->CurrentJob.state            = 0;

        if(job != NULL)
        {
            job->jobState = CRYPTO_JOBSTATE_IDLE;
        }
    }
}

static void HaeModule_Crypto_ObjectInit(void)
{
    CryptoDriverObject *Object;
    const CryptoPrimitiveList *PrimitiveList;
    uint32 i;

    for(i = 0; i < (uint32)HAEMODULE_CRYPTOOBJECTS_NUM; i++)
    {
        Object = HaeModule_Crypto_Get_Object( i );
        if (Object != NULL)
        {
            Object_Queue_Init(Object);
            HaeModule_Object_SetCurrentJob(Object, NULL, 0, 0, (uint32)HAEMODULE_JOBSTATE_IDLE);

            PrimitiveList = HaeModule_Crypto_Get_PrimitiveList( i );
            if(PrimitiveList != NULL)
            {
                PrimitiveList->CryptoPrimitive_Init( Object );
            }
        }
    }
}

void HaeModule_Crypto_JobInit(void)
{
    HaeModule_Crypto_ObjectInit();
}

static Std_ReturnType HaeModule_Crypto_JobProcessing( CryptoDriverObject *Object, Crypto_JobType* job )
{
    Std_ReturnType Result;
    const CryptoPrimitive *Primitive;
    const CryptoPrimitiveList *PrimitiveList = HaeModule_Crypto_Get_PrimitiveList(Object->CryptoDriverObjectId);
    uint32 mode;
    uint32 state;
    boolean JobProcessing;
    uint32 newJobState;

    if((Object->CurrentJob.Primitive != NULL) && (PrimitiveList != NULL))
    {
        Primitive = (const CryptoPrimitive *)Object->CurrentJob.Primitive;
        mode  = Object->CurrentJob.mode;
        state = Object->CurrentJob.state;
        JobProcessing = TRUE;

        do
        {
            PrimitiveList->CryptoPrimitive_SetState(mode, state);

            /* Implement Crypto Primitive */
            Result = Primitive->CryptoPrimitiveProcess((CryptoPrimitiveData *)Object->PrimitiveData, job);

            /*
            * [SWS_Crypto_00025] If an internal error occurs, the corresponding job state shall be set to "Idle" and all input data and intermediate results shall be discarded.
            * [SWS_Crypto_00119] If an internal error occurs while processing an asynchronous job, the corresponding job state shall be set to "Idle" and all input data and
            *                    intermediate results shall be discarded. Further, the callback notification shall be called with an appropriate error code.
            */
            PrimitiveList->CryptoPrimitive_GetState(&mode, &state);
            if((Object->CurrentJob.PrimitiveMode == mode) && (state == (uint32)HAEMODULE_PRIMITIVESTATE_INIT))
            {
                /* In this case, it is considered a primitive function that does not use this feature, 
                   and a return value is given to ensure compatibility with existing operations. */
                mode = 0;
                state = (uint32)HAEMODULE_PRIMITIVESTATE_END;
            }

            /* If the state is HAEMODULE_PRIMITIVESTATE_END, it indicates that the current mode has ended. */
            /* [Caution] The return value is valid only when the state of the primitive is HAEMODULE_PRIMITIVESTATE_END. */
            if(state == (uint32)HAEMODULE_PRIMITIVESTATE_END)
            {
                if(job->jobPrimitiveInfo->processingType == CRYPTO_PROCESSING_ASYNC)
                {
                    if(Result == E_OK)
                    {
                        if (mode == 0)
                        {
                            /* End Async Job */
                            newJobState = ((Object->CurrentJob.PrimitiveMode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) ? (uint32)HAEMODULE_JOBSTATE_IDLE : (uint32)HAEMODULE_JOBSTATE_ACTIVE;
                            HaeModule_Object_SetCurrentJob(Object, job, 0, 0, newJobState);
                            JobProcessing = FALSE;

                            /*
                            * [SWS_Crypto_00028] For each asynchronous request the Crypto Driver shall notify CRYIF about the completion of the job
                            * by calling the CRYIF_CallbackNotification function passing on the job information and the result of cryptographic operation.
                            * void CryIf_CallbackNotification( Crypto_JobType* job, Std_ReturnType result )
                            */
                            CryIf_CallbackNotification(job, Result);
                        }
                        else
                        {   
                            /* Try to run the mode next time */
                            HaeModule_Object_SetCurrentJob(Object, job, mode, HAEMODULE_PRIMITIVESTATE_INIT, (uint32)HAEMODULE_JOBSTATE_PROCESSING);
                            JobProcessing = FALSE;
                        }
                    }
                    else
                    {
                        /* This is a case where an error occurred and the job was terminated */
                        HaeModule_Object_SetCurrentJob(Object, job, 0, 0, (uint32)HAEMODULE_JOBSTATE_CANCEL);
                        JobProcessing = FALSE;

                        /*
                        * [SWS_Crypto_00028] For each asynchronous request the Crypto Driver shall notify CRYIF about the completion of the job
                        * by calling the CRYIF_CallbackNotification function passing on the job information and the result of cryptographic operation.
                        * void CryIf_CallbackNotification( Crypto_JobType* job, Std_ReturnType result )
                        */
                        CryIf_CallbackNotification(job, Result);
                    }
                }
                else /* CRYPTO_PROCESSING_SYNC */
                {
                    if(Result == E_OK)
                    {
                        if (mode == 0)
                        {
                            /* End Sync Job */
                            newJobState = ((Object->CurrentJob.PrimitiveMode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) ? (uint32)HAEMODULE_JOBSTATE_IDLE : (uint32)HAEMODULE_JOBSTATE_ACTIVE;
                            HaeModule_Object_SetCurrentJob(Object, job, 0, 0, newJobState);
                            JobProcessing = FALSE;
                        }
                        else
                        {
                            /* Continue until primitive mode ends */
                            state = HAEMODULE_PRIMITIVESTATE_INIT;
                        }
                    }
                    else
                    {
                        /* This is a case where an error occurred and the job was terminated */
                        HaeModule_Object_SetCurrentJob(Object, job, 0, 0, (uint32)HAEMODULE_JOBSTATE_CANCEL);
                        JobProcessing = FALSE;
                    }
                }
            }
            else
            {
                if(job->jobPrimitiveInfo->processingType == CRYPTO_PROCESSING_ASYNC)
                {
                    /* Try again next time */
                    HaeModule_Object_SetCurrentJob(Object, job, mode, state, (uint32)HAEMODULE_JOBSTATE_PROCESSING);
                    JobProcessing = FALSE;
                }
                else
                {
                    /* Continue until primitive state ends */
                }                
            }
        } while ( JobProcessing == TRUE );
    }
    else
    {
        HaeModule_Object_SetCurrentJob(Object, job, 0, 0, (uint32)HAEMODULE_JOBSTATE_CANCEL);
        Result = E_NOT_OK;
    }

    return Result;
}

static Std_ReturnType HaeModule_Crypto_SyncJob( CryptoDriverObject *Object, Crypto_JobType* job )
{
    Std_ReturnType Result = E_OK;
    boolean JobProcessing = FALSE;

    /*
     * [SWS_Crypto_00199] If the Crypto Driver has a queue and if a synchronous job is issued and the priority is greater
     * than the highest priority available in the queue, the Crypto Driver shall disable processing new jobs from the queue
     * until the next call of the main function has finished that follows after completion of the currently processed job.
     */
    if(CRYPTO_GET_RESOURCE(&Object->ResType_Object) == TRUE)
    {
        if((Object->CryptoQueueSize == 0) || (Object->QHead == NULL) || (Object->QHead->jobPriority < job->jobInfo->jobPriority))
        {
            /*
            * [SWS_Crypto_00034] If Crypto_ProcessJob() is called with synchronous job processing and the queue is not full,
            * but the Crypto Driver Object is busy, the Crypto Driver Object shall not queue the job and return CRYPTO_E_BUSY.
            * No job shall be put in any queue.
            */
            if(Object->CurrentJob.jobState == (uint32)HAEMODULE_JOBSTATE_IDLE)
            {
                HaeModule_Object_SetCurrentJob(Object, job, (uint32)job->jobPrimitiveInputOutput.mode, (uint32)HAEMODULE_PRIMITIVESTATE_INIT, (uint32)HAEMODULE_JOBSTATE_ACTIVE);
                JobProcessing = TRUE;
            }
            else
            {
                Result = CRYPTO_E_BUSY;
            }
        }
        else
        {
            Result = E_NOT_OK;
        }

        if(JobProcessing == TRUE)
        {
            Result = HaeModule_Crypto_JobProcessing(Object, job);
        }

        CRYPTO_RELEASE_RESOURCE(&Object->ResType_Object);
    }
    else
    {
        Result = CRYPTO_E_BUSY;
    }

    return Result;
}

static Std_ReturnType HaeModule_Crypto_ASyncJob( CryptoDriverObject *Object, Crypto_JobType* job )
{
    Std_ReturnType Result = E_OK;
    CryptoObjectQueue *Queue;

    if(Object->CryptoQueueSize > 0)
    {
        /*
        * [SWS_Crypto_00031] If Crypto_ProcessJob() is called, when the queue is empty and the Crypto Driver Object is not busy
        * the Job shall switch to the state ‘active’ and execute the crypto primitive.
        */
        /* 2021.12.22. Async job is always put into the queue although the queue is empty and the Crypto Driver Object is not busy */
        if(CRYPTO_GET_RESOURCE(&Object->ResType_Object) == TRUE)
        {
            Queue = Object_Queue_GetEmpty(Object, job);
            if(Queue != NULL)
            {
                Object_Queue_Add(Object, Queue);
                Result = E_OK;
            }
            else
            {
                Result = CRYPTO_E_QUEUE_FULL;
            }

            CRYPTO_RELEASE_RESOURCE(&Object->ResType_Object);
        }
        else
        {
            Result = CRYPTO_E_BUSY;
        }
    }
    else
    {
        /* Object does not support a queue */
        Result = E_NOT_OK;
    }

    return Result;
}

static Std_ReturnType HaeModule_Crypto_StartJob( CryptoDriverObject *Object, Crypto_JobType* job )
{
    Std_ReturnType Result = E_OK;
    const CryptoPrimitive *Primitive = NULL;

    if((job->jobPrimitiveInfo == NULL)
    || (job->jobPrimitiveInfo->primitiveInfo == NULL)
    || (job->jobInfo == NULL)
    )
    {
        HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
        Result = E_NOT_OK;
    }
    else
    {
        Primitive = HaeModule_Crypto_Get_Primitive(Object, job->jobPrimitiveInfo->primitiveInfo);
        if(Primitive == NULL)
        {
            /* [SWS_Crypto_00064] */
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_HANDLE);
            Result = E_NOT_OK;
        }
        else
        {
            /*
            * [SWS_Crypto_00201] If the parameter job->jobPrimitiveInfo->primitiveInfo->service is set to CRYPTO_KEYSETVALID,
            * CRYPTO_RANDOMSEED, CRYPTO_KEYGENERATE, CRYPTO_KEYDERIVE, CRYPTO_KEYEXCHANGECALCPUBVAL, CRYPTO_KEYEXCHANGECALCSECRET, CRYPTO_CERTIFICATEPARSE or CRYPTO_CERTIFICATEVERIFY,
            * the parameter job->cryptoKeyId must be in range; else the function Crypto_ProcessJob shall report CRYPTO_E_PARAM_HANDLE to DET and return E_NOT_OK.
            */
            if((Primitive->CryptoPrimitiveService == CRYPTO_KEYSETVALID)
                || (Primitive->CryptoPrimitiveService == CRYPTO_RANDOMSEED)
                || (Primitive->CryptoPrimitiveService == CRYPTO_KEYGENERATE)
                || (Primitive->CryptoPrimitiveService == CRYPTO_KEYDERIVE)
                || (Primitive->CryptoPrimitiveService == CRYPTO_KEYEXCHANGECALCPUBVAL)
                || (Primitive->CryptoPrimitiveService == CRYPTO_KEYEXCHANGECALCSECRET)
                || (Primitive->CryptoPrimitiveService == CRYPTO_CERTIFICATEPARSE)
                || (Primitive->CryptoPrimitiveService == CRYPTO_CERTIFICATEVERIFY)
            )
            {
                if(HaeModule_Crypto_Get_Key(job->cryptoKeyId) == NULL)
                {
                    HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_HANDLE);
                    Result = E_NOT_OK;
                }
            }

            if(Result == E_OK)
            {
                /*
                * [SWS_Crypto_00202] If the parameter job->jobPrimitiveInfo->primitiveInfo->service is set to CRYPTO_KEYDERIVE
                * or CRYPTO_CERTIFICATEVERIFY, the parameter job->cryptoTargetKeyId must be in range;
                * else the function Crypto_ProcessJob shall report CRYPTO_E_PARAM_HANDLE to DET and return E_NOT_OK
                */
                if((Primitive->CryptoPrimitiveService == CRYPTO_KEYDERIVE)
                    || (Primitive->CryptoPrimitiveService == CRYPTO_CERTIFICATEVERIFY)
                )
                {
                    if(HaeModule_Crypto_Get_Key(job->targetCryptoKeyId) == NULL)
                    {
                        HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_HANDLE);
                        Result = E_NOT_OK;
                    }
                }
            }

            if(Result == E_OK)
            {
                /*
                * [SWS_Crypto_00020] If Crypto_ProcessJob() is called while in “Idle” or “Active” state and with the operation mode “START”,
                * the previous request shall be cancelled. That means, that all previously buffered data for this job shall be reset,
                * and the job shall switch to “Active” state and process the new one.
                */
                Result = HaeModule_Crypto_CancelJob(Object->CryptoDriverObjectId, job);
                if(Result == E_OK)
                {
                    if(job->jobPrimitiveInfo->processingType == CRYPTO_PROCESSING_SYNC)
                    {
                        Result = HaeModule_Crypto_SyncJob(Object, job);
                    }
                    else if(job->jobPrimitiveInfo->processingType == CRYPTO_PROCESSING_ASYNC)
                    {
                        Result = HaeModule_Crypto_ASyncJob(Object, job);
                    }
                    else
                    {
                        Result = E_NOT_OK;
                    }
                }
            }
        }
    }

    return Result;
}

static Std_ReturnType HaeModule_Crypto_IdlestateJob( CryptoDriverObject *Object, Crypto_JobType* job )
{
    Std_ReturnType Result;

    if((job->jobPrimitiveInputOutput.mode == CRYPTO_OPERATIONMODE_START)
    || (job->jobPrimitiveInputOutput.mode == CRYPTO_OPERATIONMODE_STREAMSTART)
    || (job->jobPrimitiveInputOutput.mode == CRYPTO_OPERATIONMODE_SINGLECALL)
    )
    {
        Result = HaeModule_Crypto_StartJob(Object, job);
    }
    else
    {
        /*
         * [SWS_Crypto_00118] If Crypto_ProcessJob() is called while the job is in state “Idle” and the “START” flag in the operation mode is not set,
         * the function shall return with E_NOT_OK.
         */
        Result = E_NOT_OK;
    }

    return Result;
}

static Std_ReturnType HaeModule_Crypto_ActivestateJob( CryptoDriverObject *Object, Crypto_JobType* job )
{
    Std_ReturnType Result = E_OK;
    boolean JobProcessing = FALSE;

    /* If job is same as current active job, process it */
    /* [SWS_Crypto_00121] If Crypto_ProcessJob() is called and the Job is in “ACTIVE” state,
     * the Crypto_ProcessJob() shall check if the requested job matches the current job in the Crypto Driver Object and if yes,
     * bypass it from queueing.
     */
    if(CRYPTO_GET_RESOURCE(&Object->ResType_Object) == TRUE)
    {
        if((Object->CurrentJob.jobState == (uint32)HAEMODULE_JOBSTATE_ACTIVE)
            && (Object->CurrentJob.jobId == job->jobInfo->jobId)
            && (Object->CurrentJob.PrimitiveMode == 0)
        )
        {
            if(((Object->CurrentJob.Oldmode == (uint32)CRYPTO_OPERATIONMODE_START) && (job->jobPrimitiveInputOutput.mode == CRYPTO_OPERATIONMODE_UPDATE))
            || ((Object->CurrentJob.Oldmode == (uint32)CRYPTO_OPERATIONMODE_UPDATE) && ((job->jobPrimitiveInputOutput.mode == CRYPTO_OPERATIONMODE_UPDATE) || (job->jobPrimitiveInputOutput.mode == CRYPTO_OPERATIONMODE_FINISH)))
            || ((Object->CurrentJob.Oldmode == (uint32)CRYPTO_OPERATIONMODE_STREAMSTART) && ((job->jobPrimitiveInputOutput.mode == CRYPTO_OPERATIONMODE_UPDATE) || (job->jobPrimitiveInputOutput.mode == CRYPTO_OPERATIONMODE_FINISH)))
            )
            {
                HaeModule_Object_SetCurrentJob(Object, job, (uint32)job->jobPrimitiveInputOutput.mode, (uint32)HAEMODULE_PRIMITIVESTATE_INIT, (uint32)HAEMODULE_JOBSTATE_ACTIVE);
                JobProcessing = TRUE;
            }
            else
            {
                HaeModule_Object_SetCurrentJob(Object, job, 0, 0, (uint32)HAEMODULE_JOBSTATE_CANCEL);
                Result = E_NOT_OK;
            }
        }
        else
        {
            Result = E_NOT_OK;
        }

        if(JobProcessing == TRUE)
        {
            Result = HaeModule_Crypto_JobProcessing(Object, job);
        }

        CRYPTO_RELEASE_RESOURCE(&Object->ResType_Object);
    }
    else
    {
        Result = CRYPTO_E_BUSY;
    }

    return Result;
}

/*!
  @brief Performs the crypto primitive, that is configured in the job parameter.
  @details Service ID[hex]: 0x03 \n
        Sync/Async: Sync or Async, depends on the job configuration \n
        Reentrancy: Reentrant \n
        [SWS_Crypto_00057] If the module is not initialized and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_ProcessJob shall report CRYPTO_E_UNINIT to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00058] If the parameter objectId is out of range and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_ProcessJob shall report CRYPTO_E_PARAM_HANDLE to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00059] If the parameter job is a null pointer and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_ProcessJob shall report CRYPTO_E_PARAM_POINTER to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00064] If the parameter job->jobPrimitiveInfo->primitiveInfo->service is not supported by the Crypto Driver Object \n
            and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_ProcessJob shall report CRYPTO_E_PARAM_HANDLE to the DET and return E_NOT_OK \n
        [SWS_Crypto_00201] If the parameter job->jobPrimitiveInfo->primitiveInfo->service is set to \n
            CRYPTO_KEYSETVALID, CRYPTO_RANDOMSEED, CRYPTO_KEYGENERATE, CRYPTO_KEYDERIVE, CRYPTO_KEYEXCHANGECALCPUBVAL, \n
            CRYPTO_KEYEXCHANGECALCSECRET, CRYPTO_CERTIFICATEPARSE of CRYPTO_CERTIFICATEVERIFY, the parameter job->cryptoKeyId must be in range; \n
            else the function Crypto_ProcessJob shall report CRYPTO_E_PARAM_HANDLE to DET and return E_NOT_OK. \n
        [SWS_Crypto_00202] If the parameter job->jobPrimitiveInfo->primitiveInfo->service is set to CRYPTO_KEYDERIVE or CRYPTO_CERTIFICATEVERIFY, \n
            the parameter job->cryptoTargetKeyId must be in range; else the function Crypto_ProcessJob shall report CRYPTO_E_PARAM_HANDLE to DET and return E_NOT_OK \n
        [SWS_Crypto_00065] If job->jobPrimitiveInfo->primitiveInfo->service is set to CRYPTO_HASH or CRYPTO_MACGENERATE, \n
            the parameter job->jobPrimitiveInfo->primitiveInfo->resultLength is required. \n
            If the configured result length of the job is smaller than the result length of the chosen algorithm, \n
            the most significant bits of the result shall be truncated to the configured result length. \n
        [SWS_Crypto_00067] If the parameter job->jobPrimitiveInfo->primitiveInfo->algorithm (with its variation in family, keyLength and mode) \n
            is not supported by the Crypto Driver Object and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_ProcessJob shall report CRYPTO_E_PARAM_HANDLE to the DET and return E_NOT_OK. \n
            Depending of the crypto service configured in job->jobPrimitiveInfo-> primitiveInfo->service, different parameters of job->jobPrimitiveInput are required to be set with valid values. \n
            The table in SWS_Crypto_00071 specifies which parameters are required or optional for a service in different modes. The following requirements specify the behavior if a required member is a null pointer. \n
        [SWS_Crypto_00070] If a pointer to a buffer is required as an argument, but it is a null pointer, the Crypto_ProcessJob() function shall report CRYPTO_E_PARAM_POINTER to the DET \n
            if development error detection for the Crypto Driver is enabled, and return E_NOT_OK. \n
        [SWS_Crypto_00142] If a length pointer is required as an argument, but the value, which is pointed by the length pointer is zero, and if development error detection for the Crypto Driver is enabled, \n
            the Crypto_ProcessJob() function report CRYPTO_E_PARAM_VALUE to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00072] All crypto services listed in Crypto_ServiceInfoType except of CRYPTO_HASH, and CRYPTO_RANDOMGENERATE \n
            require a key represented as a key identifier. \n
        [SWS_Crypto_00134] If the crypto primitive requires input data, its memory location is referred by the pointer job->jobPrimitiveInput.inputPtr. \n
            On calling Crypto_ProcessJob, the length of this data is stored in job->jobPrimitiveInput.inputLength. \n
        [SWS_Crypto_00203] If job->jobRedirectionInfoRef is not a NULLPTR and the configuration bit for the inputRedirection, \n
            secondaryInputRedirection and/or tertiaryInputRedirection is set within job-> jobRedirectionInfoRef->redirectionConfig, \n
            then the corresponding key element buffer located by job-> jobRedirectionInfoRef->inputKeyId+ job-> jobRedirectionInfoRef->inputKeyElementId, \n
            job-> jobRedirectionInfoRef->secondaryInputKeyId+ job-> jobRedirectionInfoRef->secondaryInputKeyElementId, and/or jobRedirectionInfoRef->tertiaryInputKeyId+ job-> jobRedirectionInfoRef->tertiaryInputKeyElementId \n
            and its length shall be used. If in addition input data is provided together with valid re-direction information \n
            and the crypto operation allows a data operation on both input data and key element data (e.g. for hash or MAC operation), \n
            then both data shall be processed. The key element data is always processed first, followed by the input data. \n
        [SWS_Crypto_00135] If the crypto primitive requires a buffer for the result, its memory location is referred by the pointer job->jobPrimitiveInput.outputPtr. \n
            On calling this function, job->jobPrimitiveInput. outputLengthPtr shall contain the size of the associated buffer. \n
            When the request has finished, the actual length of the returned value shall be stored. \n
        [SWS_Crypto_00136] If the buffer job->jobPrimitiveInput.outputPtr or job->jobPrimitiveInput.secondaryOutputPtr is too small, \n
            or in case of input/output re-direction the corresponding key element buffer is too small, to store the result of the request, \n
            CRYPTO_E_SMALL_BUFFER shall be returned and the function shall additionally report the runtime error CRYPTO_E_RE_SMALL_BUFFER. \n
        [SWS_Crypto_00204] If job->jobRedirectionInfoRef is not a NULLPTR and the configuration bit for the outputRedirection and/or secondaryoutputRedirection is set within job-> jobRedirectionInfoRef->redirectionConfig, \n
            then the corresponding key element buffer located by job-> jobRedirectionInfoRef->outputKeyId + job-> jobRedirectionInfoRef->outputKeyElementId and/or job-> jobRedirectionInfoRef->secondaryOutputKeyId + job-> jobRedirectionInfoRef->secondaryOutputKeyElementId \n
            shall be used as output. The length of the respective key element shall be set according to the length of the output.
        [SWS_Crypto_00141] If the random generator service is chosen and the corresponding entropy, the function shall return CRYPTO_E_ENTROPY_EXHAUSTED. \n
            The function Crypto_ProcessJob shall additionally report the runtime error CRYPTO_E_RE_ENTROPY_EXHAUSTED.
  @param[in] objectId       Holds the identifier of the Crypto Driver Object.
  @param[in, out] job       Pointer to the configuration of the job. \n
                            Contains structures with job and primitive relevant information but also pointer to result buffers.
  @return E_OK: Request successful \n
        E_NOT_OK: Request failed \n
        CRYPTO_E_BUSY: Request failed, Crypro Driver Object is busy \n
        CRYPTO_E_KEY_NOT_VALID: Request failed, the key is not valid \n
        CRYPTO_E_KEY_SIZE_MISMATCH: Request failed, a key element has the wrong size \n
        CRYPTO_E_QUEUE_FULL: Request failed, the queue is full \n
        CRYPTO_E_KEY_READ_FAIL: The service request failed, because key element extraction is not allowed \n
        CRYPTO_E_KEY_WRITE_FAIL: The service request failed because the writing access failed \no
        CRYPTO_E_KEY_NOT_AVAILABLE: The service request failed because the key is not available \n
        CRYPTO_E_ENTROPY_EXHAUSTION: Request failed, the entropy is exhausted \n
        CRYPTO_E_SMALL_BUFFER: The provided buffer is too small to store the result \n
        CRYPTO_E_JOB_CANCELED: The service request failed because the synchronous Job has been canceled \n
        CRYPTO_E_KEY_EMPTY: Request failed because of uninitialized source key element
*/
Std_ReturnType HaeModule_Crypto_ProcessJob( uint32 objectId, Crypto_JobType* job )
{
    Std_ReturnType Result = E_OK;
    CryptoDriverObject *Object = NULL;

    if(HaeModule_Is_Crypto_Init() != TRUE)
    {
        /* [SWS_Crypto_00057] */
        HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_UNINIT);
        Result = E_NOT_OK;
    }
    else
    {
        Object = HaeModule_Crypto_Get_Object(objectId);
        if(Object == NULL)
        {
            /* [SWS_Crypto_00058] */
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_HANDLE);
            Result = E_NOT_OK;
        }
        else if(job == NULL)
        {
            /* [SWS_Crypto_00059] */
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            Result = E_NOT_OK;
        }
        else
        {
            if(job->jobState == CRYPTO_JOBSTATE_IDLE)
            {
                Result = HaeModule_Crypto_IdlestateJob(Object, job);
            }
            else
            {
                Result = HaeModule_Crypto_ActivestateJob(Object, job);
            }
        }
    }

    return Result;
}

/*!
  @brief This interface removes the provided job from the queue and cancels the processing of the job if possible.
  @details Service ID[hex]: 0x0E \n
        Sync/Async: Synchronous \n
        Reentrancy: Reentrant, but not for same Crypto Driver Object \n
        [SWS_Crypto_00123] If development error detection for the Crypto Driver is enabled, \n
            The function Crypto_CancelJob shall raise the error CRYPTO_E_UNINIT and return E_NOT_OK if the module is not yet initialized. \n
        [SWS_Crypto_00124] If development error detection for the Crypto Driver is enabled: \n
            The function Crypto_CancelJob shall raise the error CRYPTO_E_PARAM_HANDLE and return E_NOT_OK if the parameter objectId is out or range. \n
        [SWS_Crypto_00125] If development error detection for the Crypto Driver is enabled: \n
            The function Crypto_CancelJob shall raise the error CRYPTO_E_PARAM_POINTER and return E_NOT_OK if the parameter job is a null pointer. \n
        [SWS_Crypto_00214] If no errors are detected by Crypto Driver and the driver does currently not process this job, \n
            the service Crypto_CancelJob() shall return E_OK without any processing. \n
        [SWS_Crypto_00143] If no errors are detected by Crypto Driver and the driver is able to cancel the job immediately, \n
            the service Crypto_CancelJob() shall remove the job from the queue and cancel the job in the hardware. \n
            If the cancellation is successful E_OK shall be returned, otherwise it shall return E_NOT_OK. \n
        [SWS_Crypto_00183] If no errors are detected by Crypto Driver and the driver is not able to cancel the job (e.g. due to hardware limitations), \n
            the service Crypto_CancelJob() shall return CRYPTO_E_JOB_CANCELED.
  @param[in] objectId       Holds the identifier of the Crypto Driver Object.
  @param[in,out] job        Pointer to the configuration of the job. Contains structures with job and primitive relevant information.
  @return E_OK: Request successful, job has been removed. \n
        E_NOT_OK: Request failed, job couldn't be removed. \n
        CRYPTO_E_JOB_CANCELED[not returned]: The job has been cancelled but is still processed. No results will be returned to the application.
*/
Std_ReturnType HaeModule_Crypto_CancelJob( uint32 objectId, Crypto_JobType* job )
{
    Std_ReturnType Result = E_OK;
    CryptoDriverObject *Object = NULL;
    const Crypto_JobInfoType *jobInfo = NULL;
    CryptoObjectQueue *Queue;

    if (HaeModule_Is_Crypto_Init() != TRUE)
    {
        HaeModule_Det_ReportError(CRYPTO_API_CANCELJOB, CRYPTO_DET_E_UNINIT);
        Result = E_NOT_OK;
    }
    else
    {
        Object = HaeModule_Crypto_Get_Object(objectId);
        if(Object == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_CANCELJOB, CRYPTO_DET_E_PARAM_HANDLE);
            Result = E_NOT_OK;
        }
        else if(job == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_CANCELJOB, CRYPTO_DET_E_PARAM_POINTER);
            Result = E_NOT_OK;
        }
        else
        {
            if(job->jobInfo == NULL)
            {
                Result = E_NOT_OK;
            }
            else
            {
                jobInfo = job->jobInfo;
            }

            if(Result == E_OK)
            {
                if(CRYPTO_GET_RESOURCE(&Object->ResType_Object) == TRUE)
                {
                    if(((Object->CurrentJob.jobState == (uint32)HAEMODULE_JOBSTATE_ACTIVE) || (Object->CurrentJob.jobState == (uint32)HAEMODULE_JOBSTATE_PROCESSING))
                    && (Object->CurrentJob.jobId == jobInfo->jobId))
                    {
                        Result = E_NOT_OK;
                    }
                    else
                    {
                        Queue = Object_Queue_Find(Object, jobInfo);
                        if(Queue == NULL)
                        {
                            /*
                            * [SWS_Crypto_00214] If no errors are detected by Crypto Driver and the driver does currently not process this job,
                            * the service Crypto_CancelJob() shall return E_OK without any processing.
                            */
                            Result = E_OK;
                        }
                        else
                        {
                            Object_Queue_Del(Object, Queue);
                            Result = E_OK;
                        }
                    }

                    CRYPTO_RELEASE_RESOURCE(&Object->ResType_Object);
                }
                else
                {
                    Result = E_NOT_OK;
                }
            }
        }
    }

    return Result;
}

/*!
  @brief If asynchronous job processing is configured and there are job queues, the function is called cyclically to process queued jobs.
  @details Service ID[hex]: 0x0C \n
        It is necessary for asynchronous job processing. For synchronous job processing providing the main function is optional.
  @param[in] objectIndex    Holds the index of the Crypto Driver Object.
  @return None
*/
void HaeModule_Crypto_MainFunction( uint32 objectIndex )
{
    CryptoDriverObject *Object;
    Crypto_JobType* job = NULL;
    CryptoObjectQueue  *Queue;
    boolean JobProcessing;

    /* Call the Job stored in the Crypto Driver Queue periodically */
    if((HaeModule_Is_Crypto_Init() == TRUE)
        && (objectIndex < (uint32)HAEMODULE_CRYPTOOBJECTS_NUM))
    {
        Object = &gHaeModule_CryptoDriverObjects[objectIndex];

        if(((Object->CurrentJob.jobState == (uint32)HAEMODULE_JOBSTATE_IDLE) && (Object->CryptoQueueSize > 0) && (Object->QHead != NULL))
        || (Object->CurrentJob.jobState == (uint32)HAEMODULE_JOBSTATE_PROCESSING))
        {
            JobProcessing = FALSE;

            if(CRYPTO_GET_RESOURCE(&Object->ResType_Object) == TRUE)
            {
                if(Object->CurrentJob.jobState == (uint32)HAEMODULE_JOBSTATE_IDLE)
                {
                    if(Object->QHead != NULL)
                    {
                        Queue = Object->QHead;
                        job = Queue->job;
                        Object_Queue_Del(Object, Queue);
                        HaeModule_Object_SetCurrentJob(Object, job, (uint32)job->jobPrimitiveInputOutput.mode, (uint32)HAEMODULE_PRIMITIVESTATE_INIT, (uint32)HAEMODULE_JOBSTATE_ACTIVE);
                        JobProcessing = TRUE;
                    }
                }
                else if(Object->CurrentJob.jobState == (uint32)HAEMODULE_JOBSTATE_PROCESSING)
                {
                    if(Object->CurrentJob.job != NULL)
                    {
                        if((Object->CurrentJob.job->jobPrimitiveInfo->processingType == CRYPTO_PROCESSING_ASYNC)
                        && ((Object->CurrentJob.PrimitiveMode & (uint32)CRYPTO_OPERATIONMODE_START) != 0)
                        && (Object->CurrentJob.mode != 0))
                        {
                            job = Object->CurrentJob.job;
                            JobProcessing = TRUE;
                        }
                    }
                }
                else
                {
                    /* Nothing to do */
                }

                if(JobProcessing == TRUE)
                {
                    /* The return value is passed by the callback function inside HaeModule_Crypto_JobProcessing. 
                       Therefore, there is no need to process the return value separately here. */
                    (void)HaeModule_Crypto_JobProcessing(Object, job);
                }

                CRYPTO_RELEASE_RESOURCE(&Object->ResType_Object);
            }
        }
    }
}
#define CRYPTO_76_HAEMODULE_STOP_SEC_CODE
#include "Crypto_76_HaeModule_MemMap.h"
