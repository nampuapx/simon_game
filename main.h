


        #pragma config OSC     =  HS
        #pragma config FSCM    = OFF
        #pragma config IESO     = OFF
        #pragma config PWRT     = OFF
        #pragma config BOR    = OFF
        #pragma config WDT      = OFF

//		#pragma config RETEN		= OFF
//		#pragma config INTOSCSEL	= HIGH
//		#pragma config SOSCSEL		= DIG
	//	#pragma config XINST    	= OFF


 //       #pragma config PLLCFG	= OFF
		#pragma config LVP = OFF
        #pragma config MCLRE    = ON

////#ifdef	__DEBUG
////		#pragma config DEBUG    = ON
////        #pragma config CP0      = OFF
////        #pragma config CP1      = OFF
////        #pragma config CPB      = OFF
////        #pragma config CPD      = OFF
////        #pragma config WRT0     = OFF
////        #pragma config WRT1     = OFF
////        #pragma config WRTB     = OFF       // Boot Block Write Protection
////        #pragma config WRTC     = OFF
////        #pragma config WRTD     = OFF
////        #pragma config EBTR0    = OFF
////        #pragma config EBTRB    = OFF
////
////#else

		#pragma config DEBUG    = OFF
        #pragma config CP0      = ON
        #pragma config CP1      = ON
        #pragma config CPB      = ON
        #pragma config CPD      = ON
        #pragma config WRT0     = ON
        #pragma config WRT1     = ON
        #pragma config WRTB     = ON       // Boot Block Write Protection
        #pragma config WRTC     = ON
        #pragma config WRTD     = ON

        #pragma config EBTR0    = OFF
        #pragma config EBTR1    = OFF
        #pragma config EBTRB    = OFF

////#endif


#include <stdlib.h>
#include <p18f1320.h>
    
#include "ws2811.h"
//#include <pwm_sound.h>
//#include <uart.h>
//   #include "uart.h"
//#include <midi.h>
  
#define     LENTA_LENGTH 5

#define     WS2811          LATBbits.LATB2
#define     WS2811_TRIS     TRISBbits.TRISB2

#define     BUTTON01          PORTAbits.RA2
#define     BUTTON01_TRIS     TRISAbits.TRISA2
#define     BUTTON02          PORTBbits.RB0
#define     BUTTON02_TRIS     TRISBbits.TRISB0
#define     BUTTON03          PORTBbits.RB1
#define     BUTTON03_TRIS     TRISBbits.TRISB1
#define     BUTTON04          PORTBbits.RB3
#define     BUTTON04_TRIS     TRISBbits.TRISB3


