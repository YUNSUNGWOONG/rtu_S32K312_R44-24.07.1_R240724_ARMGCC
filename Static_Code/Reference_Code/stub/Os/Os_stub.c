#include "Rte_Type.h"
#include "Os_Imp_Cfg.h"
#include "Os.h"
/*******************************************************************************
**  stub file									                          **
**                                                                            **
** 						                                                	  **
**                                                                            **
**                                                                            **
*******************************************************************************/
void Os_CallBackNMInterrupt(void)
{

}

#if(OS_DEBUG_CPULOAD == STD_OFF)
void Os_MeasureCPULoad(void) __attribute__((weak)){/* do nothing */}
#endif

