/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: User_MemMap.h                                                 **
**                                                                            **
**  TARGET    : 3rd Party Module which need to be integrated in SWP.          **
**                                                                            **
**  PRODUCT   :                                                               **
**                                                                            **
**  PURPOSE   : Provision for sections for memory mapping.                    **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: yes                                       **
**                                                                            **
*******************************************************************************/
/* Write own memory mapping section.*/



/*******************************************************************************
**                      Module section mapping                                **
*******************************************************************************/
#if defined (USER_DO_NOT_RAISE_ERROR)
#else
  #define SECTION_NOT_FOUND
#endif
/* Refer to BUGCLASSIC-936 */
#if defined (SECTION_NOT_FOUND)
	#undef SECTION_NOT_FOUND
	#include "Crypto_76_HaeModule_MemMap.h"
#endif


/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

