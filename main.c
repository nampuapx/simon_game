
#include "main.h"

#define LENTA_LENGTH 5


void interrupt hi_int(void)
{

}

void interrupt low_priority tc_clr(void) 
{

}





void delay(unsigned char inp){
unsigned int count;
    for(;inp;inp--){
        for(count = 0x600; count>2; count--){
            Nop();	
        }	
    }
}	



void main(){
    
 	RCONbits.IPEN = 1;
    ADCON1 = 0xff;
    
    WS2811_TRIS = 0;
    
    BUTTON01_TRIS = 1;
    BUTTON02_TRIS = 1;
    BUTTON03_TRIS = 1;
    BUTTON04_TRIS = 1;
    
    
    
    
    while(1){
        if(!BUTTON01){
            led_set_red(100);
        }else{
            led_set_white(0);
        }
        if(!BUTTON02){
            led_set_red(100);
        }else{
            led_set_white(0);
        }
        if(!BUTTON03){
            led_set_red(100);
        }else{
            led_set_white(0);
        }
        if(!BUTTON04){
            led_set_red(100);
        }else{
            led_set_white(0);
        }
        
        
        
        
        
        
       delay(10); 
    }



}



