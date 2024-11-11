/* polyspace +1 MISRA2012:1.1 [Not a defect:Low] "The number of macros doesn't matter." */
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
**  SRC-MODULE: CanSM_Baudrate.c                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN State Manager Module                              **
**                                                                            **
**  PURPOSE   : Provision of the functionality of CanSM_SetBaudrate()         **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.0.3     25-Jul-2022   HieuTM8        CP44-511                            **
** 1.0.2     24-Mar-2022   HieuTM8        R44-Redmine #25572                  **
** 1.0.1     14-Jan-2022   HieuTM8        R44-Redmine #14419,#19306           **
** 1.0.0     04-Dec-2020   SMKwon         Initial Version                     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanSM_InternalTypes.h"        /* CanSM PCTypes header file */
#if (STD_ON == CANSM_DEV_ERROR_DETECT)
#include "Det.h"                  /* Det header file */
#endif
#include "CanSM_Ram.h"            /* CanSM_Ram header file */
#include "BswM_CanSM.h"           /* BswM_CanSM header */


/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR specification version information */
#define CANSM_BAUDRATE_C_RELEASE_MAJOR_VERSION       0x04u
#define CANSM_BAUDRATE_C_RELEASE_MINOR_VERSION       0x04u
#define CANSM_BAUDRATE_C_RELEASE_REVISION_VERSION    0x00u

/* CANSM software version information */
#define CANSM_BAUDRATE_C_SW_MAJOR_VERSION            0x01u
#define CANSM_BAUDRATE_C_SW_MINOR_VERSION            0x00u

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* CanSM version check */
#if (CANSM_AR_RELEASE_MAJOR_VERSION != CANSM_BAUDRATE_C_RELEASE_MAJOR_VERSION )
#error "CanSM_Version.c : Mismatch in Specification Major Version"
#endif

#if (CANSM_AR_RELEASE_MINOR_VERSION != CANSM_BAUDRATE_C_RELEASE_MINOR_VERSION)
#error "CanSM_Version.c : Mismatch in Specification Minor Version"
#endif

#if (CANSM_AR_RELEASE_REVISION_VERSION != \
                                      CANSM_BAUDRATE_C_RELEASE_REVISION_VERSION)
#error "CanSM_Version.c : Mismatch in Specification Patch Version"
#endif

#if (CANSM_SW_MAJOR_VERSION != CANSM_BAUDRATE_C_SW_MAJOR_VERSION)
#error "CanSM_Version.c : Mismatch in Major Version"
#endif

#if (CANSM_SW_MINOR_VERSION != CANSM_BAUDRATE_C_SW_MINOR_VERSION)
#error "CanSM_Version.c : Mismatch in Minor Version"
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : CanSM_SetBaudrate                                   **
**                                                                            **
** Service ID           : 0x0d                                                **
**                                                                            **
** Description          : This service shall start an asynchronous process to **
**                        change the baudrate for the configured CAN          **
**                        controllers of a certain CAN network.               **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : VAR(NetworkHandleType,CANSM_VAR) network,           **
**                        VAR(uint16,CANSM_VAR) BaudRateConfigID              **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked :                               **
**                                                                            **
**                                   Det_ReportError                          **
**                                   SchM_Enter_CanSM_MODE_STATUS_PROTECTION()**
**                                   SchM_Exit_CanSM_MODE_STATUS_PROTECTION() **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Can_01142 */
/* @Trace: CanSM_SUD_API_024 */
#if (STD_ON == CANSM_SET_BAUDRATE_API)
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANSM_CODE) CanSM_SetBaudrate(VAR(NetworkHandleType,CANSM_VAR) network, VAR(uint16,CANSM_VAR) BaudRateConfigID)
{

    P2VAR(CanSM_NetworkType, AUTOMATIC, CANSM_VAR) ptrNetwork;

    P2CONST(CanSM_StaticNetworkType, AUTOMATIC, CANSM_CONST) ptrStaticNetwork;

    VAR(NetworkHandleType,CANSM_VAR) networkHandle;

    VAR(Std_ReturnType, CANSM_VAR) result;

    #if(STD_ON == CANSM_DEV_ERROR_DETECT)

    /* Note: check module initialization */
    /* @Trace: CanSM_SUD_API_025 */
    CANSM_INITED_DET_CHECK(result,CANSMSERVICEID_SETBAUDRATE);

    /* Note: CanSM shall deny request if CanSM is not initialized */
    if((Std_ReturnType)E_OK == result)
    {

      /* Check whether network provided is valid or invalid */
      /* @Trace: CanSM_SUD_API_026 */
      CANSM_CHECK_INVALID_NETWORK(result,network,CANSMSERVICEID_SETBAUDRATE);
    }

    /* Note: The CanSM module shall deny the request if network is invalid */
    if((Std_ReturnType)E_OK == result)
    {
      /* check the validity of the network index  */
      /* @Trace: CanSM_SUD_API_027 */
      /* polyspace +4 RTE:UNR [Justified: Low] It can not be reach with this configuration */
      #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
      CANSM_CHECK_INVALID_NETWORK_HANDLE(result,CanSM_NwIdToIndex[network],CANSMSERVICEID_SETBAUDRATE);
      #else
      CANSM_CHECK_INVALID_NETWORK_HANDLE(result,CanSM_InternalNetwork[network],CANSMSERVICEID_SETBAUDRATE);
      #endif

      /*   MISRA C:2012 Rule   : D4.14
       *   Message             : the array is not out of bounds
       *   Reason              : the inputs fit the defined length of above array
       *   Verification        : network is already checked in advanced with a macro expansion
       */

    }


    if((Std_ReturnType)E_OK == result)
    #endif /* end of if (STD_ON == CANSM_DEV_ERROR_DETECT) */
    {
       /* get the index of the input network in the configuration */
       #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
       networkHandle = CanSM_NwIdToIndex[network];
       #else
       networkHandle = CanSM_InternalNetwork[network];
       #endif


       /*   MISRA C:2012 Rule   : D4.14
        *   Message             : the array is not out of bounds
        *   Reason              : the inputs fit the defined length of above array
        *   Verification        : However, network is already checked in advanced with a macro expansion
        */
       /* get the address of CanSM Network to local pointer */
       ptrNetwork = &CanSM_Network[CANSM_NETWORKHANDLE];

        /* Note: request shall be accepted if network is in communication mode */
        /* @Trace: CanSM_SUD_API_029 */
        if((uint8)CANSM_FULLCOMMUNICATION == ptrNetwork->ModeStatus)
        {
            /* set result to E_OK */
        	result = (Std_ReturnType)E_OK;
            /* get the address of CanSM_StaticNetwork to local pointer */
            ptrStaticNetwork = &CanSM_StaticNw[CANSM_NETWORKHANDLE];

            /* Set internal sub state to CANSM_ZERO */
            ptrNetwork->CanSMNWIntSubState = (uint8)CANSM_ZERO;

            /* reset repeat max to initialized value */
            ptrNetwork->CanSMModeReqReptMax = (uint8)CanSm_ModeReqMax;

            /* Store BaudRateConfigID to CanSM Network */
            ptrNetwork->BaudRateConfigID = (uint8)BaudRateConfigID;

            /* initialize set baudrate methodology */
            ptrNetwork->Baudrate = (CanSM_BaudrateDirect)CANSM_UNIDENTIFIED_BAUDRATE;

            /* @Trace: CanSM_SUD_API_081 */
            /* Enter protection area */
            SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

            /* Set the mode of the CanSM to CANSM_SETBAUDRATE STATE*/

            ptrNetwork->ModeStatus = (uint8)CanSM_SetBaudrateSERVICE;

            /* Exit protection area */
            SchM_Exit_CanSM_MODE_STATUS_PROTECTION();

            /* Notify internally stored network mode to BswM */
            /* @Trace: CanSM_SUD_API_080 */
	    /* polyspace +1 RTE:IDP [Not a defect:Low] It has been cover by geneeration code */
            BswM_CanSM_CurrentState(ptrStaticNetwork->CanSmNetworkHandle,(CanSM_BswMCurrentStateType)CANSM_BSWM_CHANGE_BAUDRATE);

        }
        else
        {
            /* return E_NOT_OK if it is not in Full Communication */
        	/* @Trace: CanSM_SUD_API_028 */
            result = (Std_ReturnType)E_NOT_OK;
        }
    }
    return result;
}
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON == CANSM_SET_BAUDRATE_API) */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
