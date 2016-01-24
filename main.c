
#include "main.h"
#include <stdio.h>

#define LENTA_LENGTH 5
#define POWER 100

unsigned int seed = 1234;


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


void sound_driver_init(void){
    
    
    
}
void setup(void){
 
	RCONbits.IPEN = 1;
    ADCON1 = 0xff;
    
    WS2811_TRIS = 0;
    BUTTON01_TRIS = 1;
    BUTTON02_TRIS = 1;
    BUTTON03_TRIS = 1;
    BUTTON04_TRIS = 1;
}


void main(){
  
    char txt[15],*t;
    char i;

    unsigned int Xn,Xn_1;
    
    unsigned char  summ;
    

    setup();
    
    Xn_1 = seed;
    
    while(1){
        ///////////////////////////////////////////////////////
        Xn = (Xn_1<<1)+37;//    генерация псевдослучайной последовательности
        Xn %= 32000;      //    метод линейного конгруента
                           //    Xn+1 = (a Xn + c) mod m
                           //    a = 2;    c = 7   mod = 0x7ff0
        ///////////////////////////////////////////////////////
        
        Xn_1 = Xn;
        sprintf(txt,"%u",Xn);

        t = txt;
        summ = 0;

        while(*t){
            summ += *t & 0x0f;
            t++;
        }  
                
           
        summ %= 4; // 4 = колличество кнопок
        
        switch(summ){
            case 0:
             led_set_yellow(POWER);   
             led_set_black();
             led_set_black();
             led_set_black();
             break;
            case 1:
             led_set_black();
             led_set_red(POWER);
             led_set_black();
             led_set_black();
             break;
            case 2:
             led_set_black();
             led_set_black(); 
             led_set_green(POWER);
             led_set_black();
            case 3:
             led_set_black();
             led_set_black();
             led_set_black(); 
             led_set_blue(POWER);
                
        }
        
     
     
//        if(!BUTTON01){
//            led_set_red(100);
//        }else{
//            led_set_black();
//        }
//        if(!BUTTON02){
//            led_set_red(100);
//        }else{
//            led_set_white(0);
//        }
//        if(!BUTTON03){
//            led_set_blue(100);
//        }else{
//            led_set_white(0);
//        }
//        if(!BUTTON04){
//            led_set_blue(100);
//        }else{
//            led_set_white(0);
//        }
        
        
        
        
        
        
       delay(20); 
             led_set_black();
             led_set_black();
             led_set_black();
             led_set_black();
             led_set_black();
         delay(20);    
    }



}



