/*
� [2022] Microchip Technology Inc. and its subsidiaries.

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

#include <xc.h>

// Set the EVSYS module to the options selected in the user interface.

int8_t EVSYS_Initialize(void) {
    // CHANNEL0 PORTA_PIN4; 
    EVSYS.CHANNEL0 = 0x44;
    // CHANNEL1 PORTA_PIN5; 
    EVSYS.CHANNEL1 = 0x45;
    // CHANNEL2 CCL_LUT1; 
    EVSYS.CHANNEL2 = 0x11;
    // CHANNEL3 CCL_LUT3; 
    EVSYS.CHANNEL3 = 0x13;
    // CHANNEL4 CCL_LUT0; 
    EVSYS.CHANNEL4 = 0x10;
    // CHANNEL5 CCL_LUT2; 
    EVSYS.CHANNEL5 = 0x12;
    // SWEVENTA CH0; 
    EVSYS.SWEVENTA = 0x1;
    // SWEVENTB CH8; 
    EVSYS.SWEVENTB = 0x0;
    // USER OFF; 
    EVSYS.USERADC0START = 0x0;
    // USER CHANNEL0; 
    EVSYS.USERCCLLUT0A = 0x1;
    // USER CHANNEL3; 
    EVSYS.USERCCLLUT0B = 0x4;
    // USER CHANNEL0; 
    EVSYS.USERCCLLUT1A = 0x1;
    // USER CHANNEL1; 
    EVSYS.USERCCLLUT1B = 0x2;
    // USER CHANNEL1; 
    EVSYS.USERCCLLUT2A = 0x2;
    // USER CHANNEL2; 
    EVSYS.USERCCLLUT2B = 0x3;
    // USER CHANNEL0; 
    EVSYS.USERCCLLUT3A = 0x1;
    // USER CHANNEL1; 
    EVSYS.USERCCLLUT3B = 0x2;
    // USER OFF; 
    EVSYS.USEREVSYSEVOUTA = 0x0;
    // USER OFF; 
    EVSYS.USEREVSYSEVOUTC = 0x0;
    // USER OFF; 
    EVSYS.USEREVSYSEVOUTD = 0x0;
    // USER OFF; 
    EVSYS.USEREVSYSEVOUTF = 0x0;
    // USER OFF; 
    EVSYS.USERTCA0CNTA = 0x0;
    // USER OFF; 
    EVSYS.USERTCA0CNTB = 0x0;
    // USER OFF; 
    EVSYS.USERTCB0CAPT = 0x0;
    // USER CHANNEL4; 
    EVSYS.USERTCB0COUNT = 0x5;
    // USER OFF; 
    EVSYS.USERTCB1CAPT = 0x0;
    // USER CHANNEL5; 
    EVSYS.USERTCB1COUNT = 0x6;
    // USER OFF; 
    EVSYS.USERTCB2CAPT = 0x0;
    // USER OFF; 
    EVSYS.USERTCB2COUNT = 0x0;
    // USER OFF; 
    EVSYS.USERTCD0INPUTA = 0x0;
    // USER OFF; 
    EVSYS.USERTCD0INPUTB = 0x0;
    // USER OFF; 
    EVSYS.USERUSART0IRDA = 0x0;
    // USER OFF; 
    EVSYS.USERUSART1IRDA = 0x0;
    return 0;
}
