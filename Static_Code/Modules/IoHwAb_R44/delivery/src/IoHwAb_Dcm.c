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
**  SRC-MODULE: IoHwAb_DigIn.c                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : APIs implementation for IoHwAb module                         **
**              IoHwAb_Dcm_DigitalSignal                                      **
**              IoHwAb_Dcm_Read_DigitalSignal                                 **
**                                                                            **
**                                                                            **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.3.0.1   30-Jun-2022  KhaLN1            #CP44-365                         **
** 1.1.0     15-Jul-2021  YangJin.Kim       R44-Redmine #18100                **
** 1.0.0     04-Dec-2020  YangJin.Kim       R40-Redmine #26992                **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb_Dcm.h"
#include "IoHwAb_DigOut.h"
#include "IoHwAb_Config.h"
#include "IoHwAb.h"
#include "Rte_IoHwAb.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : IoHwAb_Dcm_DigitalSignal                            **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This function provides control access to            **
**                          Digital ECU Signal to the DCM module              **
**                                                                            **
** Sync/Async           : None                                                **
**                                                                            **
** Re-entrancy          : None                                                **
**                                                                            **
** Input Parameters     : ChIdx, action, value                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : none                       **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_00002 */
/* @Trace: SWS_IoHwAb_00078 SWS_IoHwAb_00135 SWS_IoHwAb_00138 SWS_IoHwAb_00142 */
/* @Trace: IoHwAb_SUD_API_084 */
#if (IOHWAB_USE_DCM_DIGOUT == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_Dcm_DigitalSignal(IoHwAb_IndexType ChIdx,
                                                uint8 action, IoHwAb_LevelType Level)
{
    uint8 LucShiftBit  = (uint8)(ChIdx % 8U);
    uint8 LucResBufIdx = (uint8)(ChIdx / 8U);

    IoHwAb_LevelType DefVal = (uint8)((IoHwAb_GaaDigOutDefVal[LucResBufIdx] & (1U <<LucShiftBit)) >> LucShiftBit) ;


    switch (action)
    {
        case IOHWAB_RETURNCONTROLTOECU:
            //Clear current information
            IoHwAb_GaaDigitalSignal_Locked[LucResBufIdx] &= (uint8)(~((uint8)(1U << LucShiftBit)));
            //Update new status
            IoHwAb_GaaDigitalSignal_Locked[LucResBufIdx] |= (uint8)(IOHWAB_UNLOCKED << LucShiftBit);

            break;

        case IOHWAB_RESETTODEFAULT:
            IoHwAb_DigOutWrite(ChIdx, DefVal);
            //Clear current information
            IoHwAb_GaaDigitalSignal_Locked[LucResBufIdx] &= (uint8)(~((uint8)(1U << LucShiftBit)));
            //Update new status
            IoHwAb_GaaDigitalSignal_Locked[LucResBufIdx] |= (uint8)(IOHWAB_LOCKED << LucShiftBit);

            break;

        case IOHWAB_FREEZECURRENTSTATE:
            //Clear current information
            IoHwAb_GaaDigitalSignal_Locked[LucResBufIdx] &= (uint8)(~((uint8)(1U << LucShiftBit)));
            //Update new status
            IoHwAb_GaaDigitalSignal_Locked[LucResBufIdx] |= (uint8)(IOHWAB_LOCKED << LucShiftBit);

            break;

        case IOHWAB_SHORTTERMADJUST:
            IoHwAb_DigOutWrite(ChIdx, Level);
            IoHwAb_GaaDigitalSignal_Locked[LucResBufIdx] &= (uint8)(~((uint8)(1U << LucShiftBit)));
            //Update new status
            IoHwAb_GaaDigitalSignal_Locked[LucResBufIdx] |= (uint8)(IOHWAB_LOCKED << LucShiftBit);

            break;

        default:
            /* Do nothing, should not reach here */
            break;
    }

}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_Dcm_Read_DigitalSignal                       **
**                                                                            **
** Service ID             : None                                                **
**                                                                            **
** Description          : This function provides read access to               **
**                          Digital ECU Signal to the DCM module                  **
**                                                                            **
** Sync/Async           : None                                                   **
**                                                                            **
** Re-entrancy          : None                                                 **
**                                                                            **
** Input Parameters     : ChIdx, value                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : none                       **
**                        Function(s) invoked    :                            **
**                          IoHwAb_DigInRead                                     **
*******************************************************************************/
/* @Trace: SWS_IoHwAb_00078 SWS_IoHwAb_00139 */
/* @Trace: IoHwAb_SUD_API_085 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_Dcm_Read_DigitalSignal(IoHwAb_IndexType ChIdx, IoHwAb_LevelType* Level)
{
    IoHwAb_DigOutReadDirect(ChIdx, Level);
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of #if (IOHWAB_USE_DCM_DIGOUT == STD_ON) */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
