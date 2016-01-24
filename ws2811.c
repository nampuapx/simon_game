
#include "main.h"





void color_set(unsigned char pow){

    unsigned char j;

    for(j = 0; j < 8; j++) {
        // в зависимости от того, какой текущий бит 1 или 0
        // пин, управляющий лентой, должен находится в состоянии высокого уровня разное время 
        if (pow & 0x80 ) {  // Проверяем бит
            // Если это 1, давайте подождём подольше
            WS2811 = 1;
            NOP();
            NOP();
            NOP();
            WS2811 = 0;
        } else {
            // а если 0, надо установить единицу затем ноль быстро, как только можно
            WS2811 = 1;
            WS2811 = 0;
        }
        // и теперь сдвигаем влево для доступа к следующему биту в цикле
        pow<<=1;
    }
}
 

void set_all_leds(unsigned char red, unsigned char  green, unsigned char blue){
    unsigned int count = LENTA_LENGTH;
    
    while(count){
        color_set(green);
        color_set(red);
        color_set(blue);
        count--;
    }
    
    
    
}

//void led_set_white(unsigned char pow){
//    color_set(pow);
//    color_set(pow);
//    color_set(pow);
//}
//void led_set_red(unsigned char pow){
//    color_set(pow);
//    color_set(0);
//    color_set(0);
//}
//void led_set_green(unsigned char pow){
//    color_set(0);
//    color_set(pow);
//    color_set(0);
//}







