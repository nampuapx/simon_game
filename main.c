
#include "main.h"

#define LENTA_LENGTH 5


void interrupt hi_int(void)
{

}

void interrupt low_priority tc_clr(void) 
{

}





void delay(void){
unsigned int count;

    for(count = 0x6000; count>2; count--){
        Nop();	
    }	
}	



void main(){
    
 	RCONbits.IPEN = 1;
    ADCON1 = 0xff;
    
    WS2811_TRIS = 0;



}



