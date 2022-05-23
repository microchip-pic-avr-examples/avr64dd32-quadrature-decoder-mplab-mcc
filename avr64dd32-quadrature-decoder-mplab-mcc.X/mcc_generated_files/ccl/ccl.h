/**
 * CCL Generated Header File
 * 
 * @file ccl.h
 * 
 * @defgroup  ccl CCL
 * 
 * @brief This is the generated header file for the CCL driver. 
 *
 * @version Driver Version  1.1.0
*/

#include <stdint.h>
#include <stdbool.h>

#ifndef CCL_H_INCLUDED
#define CCL_H_INCLUDED

#include "../system/utils/compiler.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @ingroup  ccl
 * @brief Initializes the CCL.
 *        This routine should only be called once during system initialization.
 * @pre none
 * @param none.
 * @return none
 */
int8_t CCL_Initialize(void);
void LUT0_OUT_DefaultInterruptHandler(void);
void LUT0_OUT_SetInterruptHandler(void (* interruptHandler)(void)) ; 
void LUT2_OUT_DefaultInterruptHandler(void);
void LUT2_OUT_SetInterruptHandler(void (* interruptHandler)(void)) ; 

#ifdef __cplusplus
}
#endif

#endif /* CCL_H_INCLUDED */
