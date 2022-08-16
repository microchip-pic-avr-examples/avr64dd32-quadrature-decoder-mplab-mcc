 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
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
#include "mcc_generated_files/system/system.h"
#include <util/delay.h>
#include "qei.h"
#include <stdio.h>

volatile static bool flag_OVF_CW = false;
volatile static bool flag_OVF_CCW = false;
volatile static bool flag_1_sec = false;

void onCW(void)
{
    LED_SetHigh();
}

void onCCW(void)
{
    LED_SetLow();
}

void onCW_OVF(void)
{
    flag_OVF_CW = true;
}

void onCCW_OVF(void)
{
    flag_OVF_CCW = true;
}

void onOneSecond(void)
{
    flag_1_sec = true;
}

void main(void)
{
    SYSTEM_Initialize();

    QEI_Initialize();
    QEI_SetHandlerCW(onCW);
    QEI_SetHandlerCCW(onCCW);
    QEI_SetHandlerCW_OVF(onCW_OVF);
    QEI_SetHandlerCCW_OVF(onCCW_OVF);
    TCA0_OverflowCallbackRegister(onOneSecond);
    
    while (1)
    {       
    
        if(flag_OVF_CW == true)
        {
            flag_OVF_CW = false;
            printf("CW OVF\n\r");
        }

        if(flag_OVF_CCW == true)
        {
            flag_OVF_CCW = false;
            printf("CCW OVF\n\r");
        }
        
        if(flag_1_sec == true)
        {
            flag_1_sec = false;
            printf("Counter value is: %ld\n\r", QEI_GetVelocity());
        }
    }
}
