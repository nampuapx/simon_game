
#include "main.h"





void color_set(unsigned char pow){

    unsigned char j;

    for(j = 0; j < 8; j++) {
        // � ����������� �� ����, ����� ������� ��� 1 ��� 0
        // ���, ����������� ������, ������ ��������� � ��������� �������� ������ ������ ����� 
        if (pow & 0x80 ) {  // ��������� ���
            // ���� ��� 1, ������� ������� ��������
            WS2811 = 1;
            NOP();
            NOP();
            NOP();
            WS2811 = 0;
        } else {
            // � ���� 0, ���� ���������� ������� ����� ���� ������, ��� ������ �����
            WS2811 = 1;
            WS2811 = 0;
        }
        // � ������ �������� ����� ��� ������� � ���������� ���� � �����
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







