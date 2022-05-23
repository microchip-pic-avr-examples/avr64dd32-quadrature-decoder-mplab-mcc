/**
 * CCL Generated Driver File
 * 
 * @file ccl.c
 * 
 * @ingroup  ccl
 * 
 * @brief This is the generated driver implementation file for the CCL driver. 
 *
 * @version Driver Version 1.1.1
*/

/*
© [2022] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#include "../ccl.h"
static void (*LUT0_OUT_InterruptHandler)(void);
static void (*LUT2_OUT_InterruptHandler)(void);

int8_t CCL_Initialize(void)
{
    //INTMODE0 RISING; INTMODE1 INTDISABLE; INTMODE2 RISING; INTMODE3 INTDISABLE; 
    CCL.INTCTRL0 = 0x11;

    //INT 0x0; 
    CCL.INTFLAGS = 0x0;

    //INSEL0 EVENTA; INSEL1 LINK; 
    CCL.LUT0CTRLB = 0x23;

    //INSEL2 EVENTB; 
    CCL.LUT0CTRLC = 0x4;

    //INSEL0 EVENTA; INSEL1 EVENTB; 
    CCL.LUT1CTRLB = 0x43;

    //INSEL2 MASK; 
    CCL.LUT1CTRLC = 0x0;

    //INSEL0 EVENTA; INSEL1 EVENTB; 
    CCL.LUT2CTRLB = 0x43;

    //INSEL2 LINK; 
    CCL.LUT2CTRLC = 0x2;

    //INSEL0 EVENTA; INSEL1 EVENTB; 
    CCL.LUT3CTRLB = 0x43;

    //INSEL2 MASK; 
    CCL.LUT3CTRLC = 0x0;

    //SEQSEL DISABLE; 
    CCL.SEQCTRL0 = 0x0;

    //SEQSEL DISABLE; 
    CCL.SEQCTRL1 = 0x0;

    //TRUTH 216; 
    CCL.TRUTH0 = 0xD8;

    //TRUTH 13; 
    CCL.TRUTH1 = 0xD;

    //TRUTH 228; 
    CCL.TRUTH2 = 0xE4;

    //TRUTH 11; 
    CCL.TRUTH3 = 0xB;

    //CLKSRC OSC32K; EDGEDET EN; ENABLE enabled; FILTSEL DISABLE; OUTEN enabled; 
    CCL.LUT0CTRLA = 0xCB;

    //CLKSRC OSC32K; EDGEDET EN; ENABLE enabled; FILTSEL FILTER; OUTEN disabled; 
    CCL.LUT1CTRLA = 0xAB;

    //CLKSRC OSC32K; EDGEDET EN; ENABLE enabled; FILTSEL DISABLE; OUTEN enabled; 
    CCL.LUT2CTRLA = 0xCB;

    //CLKSRC OSC32K; EDGEDET EN; ENABLE enabled; FILTSEL FILTER; OUTEN disabled; 
    CCL.LUT3CTRLA = 0xAB;

    //ENABLE enabled; RUNSTDBY disabled; 
    CCL.CTRLA = 0x1;
    
    // register default ISC callback functions at runtime; use these methods to register a custom function
    LUT0_OUT_SetInterruptHandler(LUT0_OUT_DefaultInterruptHandler);
    LUT2_OUT_SetInterruptHandler(LUT2_OUT_DefaultInterruptHandler);

    return 0;
}

/**
  Allows selecting an interrupt handler for LUT0_OUT at application runtime
*/
void LUT0_OUT_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    LUT0_OUT_InterruptHandler = interruptHandler;
}

void LUT0_OUT_DefaultInterruptHandler(void)
{
    // add your LUT0_OUT interrupt custom code
    // or set custom function using LUT0_OUT_SetInterruptHandler()
}

/**
  Allows selecting an interrupt handler for LUT2_OUT at application runtime
*/
void LUT2_OUT_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    LUT2_OUT_InterruptHandler = interruptHandler;
}

void LUT2_OUT_DefaultInterruptHandler(void)
{
    // add your LUT2_OUT interrupt custom code
    // or set custom function using LUT2_OUT_SetInterruptHandler()
}

ISR(CCL_CCL_vect)
{
    /*
    * Insert your CCL interrupt handling code
    *
    * Interrupt flag can be cleared by writing 1 to its bit location
    * in the INTFLAGS register
    */

    // Call the interrupt handler for the callback registered at runtime
    if(CCL.INTFLAGS & CCL_INT0_bm)
    {
        LUT0_OUT_InterruptHandler();
    }
    if(CCL.INTFLAGS & CCL_INT2_bm)
    {
        LUT2_OUT_InterruptHandler();
    }
    
    /* Clear interrupt flags */
    CCL.INTFLAGS = CCL_INT0_bm | CCL_INT2_bm ;
}
