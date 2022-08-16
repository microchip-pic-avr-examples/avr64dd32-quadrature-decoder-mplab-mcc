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


static qei_handler_t QEI_HandlerCW = NULL;
static qei_handler_t QEI_HandlerCCW = NULL;
static qei_handler_t QEI_HandlerCCW_OVF = NULL;
static qei_handler_t QEI_HandlerCW_OVF = NULL;

void QEI_SetHandlerCW(qei_handler_t handler)
{
    QEI_HandlerCW = handler;
}

void QEI_SetHandlerCCW(qei_handler_t handler)
{
    QEI_HandlerCCW = handler;
}

void QEI_SetHandlerCW_OVF(qei_handler_t handler)
{
    QEI_HandlerCW_OVF = handler;
}

void QEI_SetHandlerCCW_OVF(qei_handler_t handler)
{
    QEI_HandlerCCW_OVF = handler;
}

static void QEI_CW(void)
{
    if(QEI_HandlerCW != NULL)
        QEI_HandlerCW();
}

static void QEI_CCW(void)
{
    if(QEI_HandlerCCW != NULL)
        QEI_HandlerCCW();
}

static void QEI_CW_OVF(void)
{
    if(QEI_HandlerCW_OVF != NULL)
        QEI_HandlerCW_OVF();
}

static void QEI_CCW_OVF(void)
{
    if(QEI_HandlerCCW_OVF != NULL)
        QEI_HandlerCCW_OVF();
}

void QEI_Initialize(void)
{
    QEI_HandlerCW = NULL;
    QEI_HandlerCCW = NULL;
    QEI_HandlerCCW_OVF = NULL;
    QEI_HandlerCW_OVF = NULL;

    TCB0_Write(0);
    TCB1_Write(0);
    LUT0_OUT_SetInterruptHandler(QEI_CW);
    LUT2_OUT_SetInterruptHandler(QEI_CCW);
    TCB0_OverflowCallbackRegister(QEI_CW_OVF);
    TCB1_OverflowCallbackRegister(QEI_CCW_OVF);
}

int32_t QEI_GetVelocity(void)
{
    int32_t CW_pulses = 0;
    int32_t CCW_pulses = 0;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        CW_pulses = TCB0_Read();
        TCB0_Write(0);
        
        CCW_pulses = TCB1_Read();
        TCB1_Write(0);
    }

    return CW_pulses - CCW_pulses;
}
