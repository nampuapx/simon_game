
#include "main.h"
#include <stdio.h>


#define POWER 100

unsigned int g_seed = 20;


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

unsigned char get_next_psevdo_digit(unsigned int *Xn_1)
{
      char txt[15],*t;
      //static unsigned int Xn_1;
      unsigned int Xn,temp;
      unsigned char  summ;
    
    
  
        temp = *Xn_1;
            ///////////////////////////////////////////////////////
        Xn = (temp<<1)+37;//    ��������� ��������������� ������������������
        Xn %= 32000;      //    ����� ��������� ����������
                           //    Xn+1 = (a Xn + c) mod m
                           //    a = 2;    c = 7   mod = 0x7ff0
        ///////////////////////////////////////////////////////
        
        *Xn_1 = Xn;
        sprintf(txt,"%u",Xn);

        t = txt;
        summ = 0;

        while(*t){
            summ += *t & 0x0f;
            t++;
        }  
                
           
        summ %= 4; // 4 = ����������� ������
        
        return summ;
   
}

void error(void){
    set_all_leds(POWER,0,0);
    delay(100);
    set_all_leds(0,0,0);
    delay(50);
    set_all_leds(POWER,0,0);
    delay(100);
    set_all_leds(0,0,0);    
}
void show_color(unsigned char dig){
              switch(dig){
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
    
}



void main(){
  
    unsigned char digit,button;
    unsigned int len,i;
  
    unsigned int Xn_1;
    
    setup();
    
   
    error();
   
    len = 1;
  
    while(1){
        ///////////////////////////////////////////////
        //   ������������ ������������������
        ///////////////////////////////////////////////
        Xn_1 = g_seed;
        for(i=0;i<len;i++){

            digit = get_next_psevdo_digit(&Xn_1);
            show_color(digit);

           delay(100); 
                set_all_leds(0,0,0);
             delay(50);
        }  // �������� ������������������  
        len++;
        delay(150);
        continue;
        /////////////////////////////////////////////////////// 
        //   ���� � �������� ������������������
        ///////////////////////////////////////////////////////
        Xn_1 = g_seed;
        for(i=0;i<len;i++){
            button = 255;
            while(button==255){
                if(!BUTTON01){
                    button = 0;
                }
                if(!BUTTON02){
                    button = 1;
                }
                if(!BUTTON03){
                    button = 2;
                }
                if(!BUTTON04){
                    button = 3;
                }
            }
            digit = get_next_psevdo_digit(&Xn_1);
            if(digit!=button){
                
                error();
                break;
            }
            
            
        }//for   
        
        
        
       delay(20); 
            set_all_leds(0,0,0);
         delay(20);    
    }



}



