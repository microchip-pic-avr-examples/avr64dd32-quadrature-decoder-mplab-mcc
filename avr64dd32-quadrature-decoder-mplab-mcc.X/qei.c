/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS.
 */

#include <util/atomic.h>
#include "mcc_generated_files/system/system.h"
#include "qei.h"

#if ENABLE_DETECT_CB == 1
#if POLLED_CB == 1
static uint8_t QEI_CW_flag = 0;
static uint8_t QEI_CCW_flag = 0;
static uint8_t QEI_CW_OVF_flag = 0;
static uint8_t QEI_CCW_OVF_flag = 0;
#endif

void (*QEI_HandlerCW)(void);
void QEI_SetHandlerCW(void (* HandlerCW)(void))
{
    QEI_HandlerCW = HandlerCW;
}

void (*QEI_HandlerCCW)(void);
void QEI_SetHandlerCCW(void (* HandlerCCW)(void))
{
    QEI_HandlerCCW = HandlerCCW;
}

void (*QEI_HandlerCW_OVF)(void);
void QEI_SetHandlerCW_OVF(void (* HandlerCW_OVF)(void))
{
    QEI_HandlerCW_OVF = HandlerCW_OVF;
}

void (*QEI_HandlerCCW_OVF)(void);
void QEI_SetHandlerCCW_OVF(void (* HandlerCCW_OVF)(void))
{
    QEI_HandlerCCW_OVF = HandlerCCW_OVF;
}

static void QEI_CW(void);
static void QEI_CCW(void);
static void QEI_CW_OVF(void);
static void QEI_CCW_OVF(void);

static void QEI_CW(void) {
#if POLLED_CB == 1
    QEI_CW_flag = 1;
#else
    QEI_HandlerCW();
#endif
}

static void QEI_CCW(void) {
#if POLLED_CB == 1
    QEI_CCW_flag = 1;
#else
    QEI_HandlerCCW();
#endif
}

static void QEI_CW_OVF(void) {
#if POLLED_CB == 1
    QEI_CW_OVF_flag = 1;
#else
    QEI_HandlerCW_OVF();
#endif
}

static void QEI_CCW_OVF(void) {
#if POLLED_CB == 1
    QEI_CCW_OVF_flag = 1;
#else
    QEI_HandlerCCW_OVF();
#endif
}

#if POLLED_CB == 1
void QEI_CallbackHandler()
{
    if(QEI_CW_flag == 1)
    {
        QEI_HandlerCW();
        QEI_CW_flag = 0;
    }

    if(QEI_CCW_flag == 1)
    {
        QEI_HandlerCCW();
        QEI_CCW_flag = 0;
    }
    
    if(QEI_CW_OVF_flag == 1)
    {
        QEI_HandlerCW_OVF();
        QEI_CW_OVF_flag = 0;
    }

    if(QEI_CCW_OVF_flag == 1)
    {
        QEI_HandlerCCW_OVF();
        QEI_CCW_OVF_flag = 0;
    }
}
#endif
#endif

void QEI_Initialize()
{
    TCB0.CNT = 0;
    TCB1.CNT = 0;
    LUT0_OUT_SetInterruptHandler(QEI_CW);
    LUT2_OUT_SetInterruptHandler(QEI_CCW);
    TCB0_OverflowCallbackRegister(QEI_CW_OVF);
    TCB1_OverflowCallbackRegister(QEI_CCW_OVF);
}

int32_t QEI_GetVelocity()
{
    int32_t CW_pulses = 0;
    int32_t CCW_pulses = 0;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        CW_pulses = TCB0.CNT;
        TCB0.CNT = 0;
        
        CCW_pulses = TCB1.CNT;
        TCB1.CNT = 0;
    }

    return CW_pulses - CCW_pulses;
}