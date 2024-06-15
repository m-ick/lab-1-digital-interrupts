#include "mbed.h"
#include <cstdio>

/*
    This program prints to screen when the blue button on the board is pressed and released.

    The button is mapped to PC_13, the leds are mapped to green(LED1) and yellow(LED3) leds
    The while loop is an infinate loop as it is always true

    When the blue button(BUTTON1) is pressed it will call btnFall funtion, print Button pressed to the terminal, turn LED1(green) on and LED3(yellow) off
    When it is released it will print Button released to screen, turn LED1(green) off and LED3(yellow) on

*/

InterruptIn blue_btn(PC_13);
DigitalOut pressed(PA_5);
DigitalOut released(PC_9);

volatile int trig = 0;

void btnFall(){
    trig = 1;
}

void btnRise(){
    trig = 2;
}

int main()
{ 
    blue_btn.fall(&btnFall);
    blue_btn.rise(&btnRise);
    
    while(true){
        if(trig == 1){
            trig = 0;
            printf("Button pressed \r\n");
            pressed = 1;
            released = 0;
        } else if (trig == 2) {
            trig = 0;
            printf("Button released \r\n");
            pressed = 0;
            released = 1;
        }
    }

    return 0;
}
