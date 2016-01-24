

void color_set(unsigned char pow);
void led_set_white(unsigned char pow);


#define led_set_green(pow)    color_set(pow);color_set(0);color_set(0);
#define led_set_red(pow)  color_set(0);color_set(pow);color_set(0);
#define led_set_blue(pow)   color_set(0);color_set(0);color_set(pow);
#define led_set_yellow(pow)   color_set(pow>>1);color_set(pow>>1);color_set(0);

#define led_set_black() color_set(0);color_set(0);color_set(0);