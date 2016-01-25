
#include "main.h"
#include <stdio.h>


#define POWER 100


      union _sound_init
      {
        unsigned int Int;
        char Char[2];
      }sound_init;


void interrupt hi_int(void)
{
//  TMR0H = (char)((0xffff-sound_value)>>8);
//	TMR0L = (char)(0xffff-sound_value);
    
    TMR0H = sound_init.Char[1];
	TMR0L = sound_init.Char[0]; 

    SOUND_OUT = !SOUND_OUT;
    
    TMR0IF = 0;
}

//void interrupt low_priority tc_clr(void) 
//{
//
//    TMR1H = 0xec; //приблизительно 1mS при 5MHz
//	TMR1L = 0x77;
//    
//    
//    if(sound_enable){
//        sound_enable--;
//    }
//    if(!sound_enable){
//        TMR0ON = 0;
//    }
//        
//    TMR1IF = 0;
//}


unsigned int get_seed(void){
    unsigned int seed;
    
    *(char*)(&seed) = TMR1L;           //Получение значения таймера 1
    *(((char*)(&seed))+sizeof(char)) = TMR1H;
    return seed>>1;    // делю на 2 чтобы в формуле ПСП не перегружалось
}

void sound_start(unsigned char freq){
    
    switch(freq){
        case 0:
            sound_init.Int = 0xf6a4; // до
            break;
        case 1:    
            sound_init.Int = 0xf893; // ми
            break;
        case 2:    
            sound_init.Int = 0xf8fe; // фа
            break;
        case 3:    
            sound_init.Int = 0xfa6f; // ля
            break;
        case 4:    
            sound_init.Int = 0xd000; // ля
            break;           
    }

    TMR0ON = 1;
}

void sound_stop(){
    
    TMR0ON = 0;
    SOUND_OUT = 0;
}

void delay(unsigned char inp){
unsigned int count;
    for(;inp;inp--){
        for(count = 0x600; count>2; count--){
            Nop();	
        }	
    }
}	

void int_off(void){
    
    GIEH = 0;
    GIEL = 0;
}
void int_on(void){
    
    GIEH = 1;
    GIEL = 1;
}


void setup(void){
 
	RCONbits.IPEN = 1;
    ADCON1 = 0xff;
    
    WS2811_TRIS = 0;
    BUTTON01_TRIS = 1;
    BUTTON02_TRIS = 1;
    BUTTON03_TRIS = 1;
    BUTTON04_TRIS = 1;
    SOUND_OUT_TRIS = 0;
    
    T0CON = 0b00001000;


    TMR1H = 0xec; //приблизительно 1mS при 5MHz
	TMR1L = 0x77;
    T1CON = 0b10000001;
    
    TMR0IP = 1;
    TMR0IF = 0;
    TMR0IE = 1;
    
    //TMR1IP = 0;
    //TMR1IF = 0;
    //TMR1IE = 1; 
    
}

unsigned char get_next_psevdo_digit(unsigned int *Xn_1)
{
      char txt[15],*t;
      //static unsigned int Xn_1;
      unsigned int Xn,temp;
      unsigned char  summ;
    
    
  
        temp = *Xn_1;
            ///////////////////////////////////////////////////////
        Xn = (temp<<1)+37;//    генерация псевдослучайной последовательности
        Xn %= 32000;      //    метод линейного конгруента
                           //    Xn+1 = (a Xn + c) mod m
                           //    a = 2;    c = 7   mod = 0x7ff0
        ///////////////////////////////////////////////////////
        
        *Xn_1 = Xn;

        sprintf(txt,"%u",Xn);   // Вычисление суммы всех цифр в числе
        t = txt;
        summ = 0;
        while(*t){
            summ += *t & 0x0f;
            t++;
        }  
                
           
        summ %= 4; // 4 = колличество кнопок
        
        return summ;
   
}

void error(void){
    set_all_leds(POWER,0,0);
    sound_start(4);
    delay(100);
    sound_stop();
    set_all_leds(0,0,0);
    delay(50);
    set_all_leds(POWER,0,0);
    sound_start(4);
    delay(100);
    sound_stop();
    set_all_leds(0,0,0); 
    delay(10);
}
void start_flash(void){
    unsigned char i,pos=0;
    
	while(pos<20){
        
        for(i=0;i<LENTA_LENGTH;i++){
            if(i==pos){
                led_set_white(70);
            }else if(i==pos-1){
                led_set_white(30);
            }else if(i==pos-2){
                led_set_white(10);
            }else if(i==pos-3){
                led_set_white(5);            
            }else{
                led_set_white(0);  
            }
        }    
        pos++;
        delay(10);
    }
}



void show_color(unsigned char dig){
          
              switch(dig){
                case 0:
                 led_set_yellow(POWER);   
                 led_set_black();
                 led_set_black();
                 led_set_black();
                 led_set_black();
                 sound_start(dig);
                 break;
                case 1:
                 led_set_black();
                 led_set_red(POWER);
                 led_set_black();
                 led_set_black();
                 led_set_black();
                 sound_start(dig);
                 break;
                case 2:
                 led_set_black();
                 led_set_black(); 
                 led_set_green(POWER);
                 led_set_black();
                 led_set_black();
                 sound_start(dig);
                 break;
                case 3:
                 led_set_black();
                 led_set_black();
                 led_set_black(); 
                 led_set_blue(POWER);
                 led_set_black();
                 sound_start(dig);
                 break;
                 
            }  
    
}

unsigned char wait_button(void){
    unsigned char button = 255;
    
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
    return button;
}

/////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void main(){
  
    unsigned char digit,button;
    unsigned int len,i;
    unsigned int g_seed;
    unsigned int Xn_1;
    
    setup();
    
    set_all_leds(0,0,0);
    delay(5);
    set_all_leds(0,0,0);
    delay(5);   
    
    wait_button();      // Ожидание нажатия для начала раунда
    start_flash();      // Стартовое приветствие
    g_seed = get_seed(); // Захват стартового значения для ПСП
    delay(150);
    len = 1;            // Установка длинны последовательности
    

    while(1){
        ///////////////////////////////////////////////
        //   Демонстрация последовательности
        ///////////////////////////////////////////////
        Xn_1 = g_seed;
        for(i=0;i<len;i++){

            digit = get_next_psevdo_digit(&Xn_1);
            show_color(digit);

            delay(100); 
            sound_stop();
            set_all_leds(0,0,0);
            delay(50);
        }  // Показали Последовательность  

        /////////////////////////////////////////////////////// 
        //   ВВод и проверка последовательности
        ///////////////////////////////////////////////////////
        Xn_1 = g_seed;
        for(i=0;i<len;i++){
            
            digit = get_next_psevdo_digit(&Xn_1);
             button = wait_button();
            if(digit != button){
                error();            //  Ошибка
                break;      
            }else{                  // Ответ верен
                show_color(digit);  // Индикация правильного ответа
                delay(100); 
                sound_stop();
                set_all_leds(0,0,0);
                delay(10);
            }
        }//for   
        
        if(digit == button){        // Если Всё верно
            delay(30);          
            set_all_leds(10,10,10); // Индикация, что ответ был правильный
            delay(5);
            set_all_leds(0,0,0);
            delay(100);
            len++;                  // Увеличение длинны последовательности
            continue;
        }else{
            wait_button();          // Ожидание нажатия для начала следующего раунда
            start_flash();          // Стартовое приветствие
            g_seed = get_seed();    // Захват стартового значения для ПСП
            delay(10);
            len = 1;                // Установка длинны последовательности
        }
        
    
    }



}



