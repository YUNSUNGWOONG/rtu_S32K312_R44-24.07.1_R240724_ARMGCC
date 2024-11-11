#ifndef CAN_H
#define CAN_H

#include "Can_43_FLEXCAN.h"

#if defined(MCAL_SUPPORT_MOBILGENE_2_0)
#define Can_SetControllerMode               Can_43_FLEXCAN_SetControllerMode
#define Can_Write                           Can_43_FLEXCAN_Write
#define Can_GetControllerErrorState         Can_43_FLEXCAN_GetControllerErrorState
#define Can_GetControllerRxErrorCounter     Can_43_FLEXCAN_GetControllerRxErrorCounter
#define Can_GetControllerTxErrorCounter     Can_43_FLEXCAN_GetControllerTxErrorCounter
#define Can_GetControllerMode               Can_43_FLEXCAN_GetControllerMode

#define CAN_AR_RELEASE_MAJOR_VERSION        CAN_43_FLEXCAN_AR_RELEASE_MAJOR_VERSION
#define CAN_AR_RELEASE_MINOR_VERSION        CAN_43_FLEXCAN_AR_RELEASE_MINOR_VERSION
#endif /* #if defined(MCAL_SUPPORT_MOBILGENE_2_0) */

#endif /* CAN_H */

