#include "mbed.h"

DigitalOut temp(LED1);

DigitalOut output_robot(A0);
DigitalOut output_board(LED2);

InterruptIn button_robot(A1);
InterruptIn button_board(PC_13);

UnbufferedSerial pc(USBTX, USBRX);
Thread thread;

volatile char set_robot_state = 0;

void signal_high (){
    pc.write("H", 1);
}

void signal_low (){
    pc.write("L", 1);
}

void signal_from_pc(){
    char c;
    temp =! temp;
    if (pc.read(&c,1)){
        if(c=='K'){
            set_robot_state = 1;
        }
        pc.write(&c, 1);
    }
}

void toggle_output(){
    while(true){
        if(set_robot_state == 1){
            output_board = 1;
            output_robot = 1;
            thread_sleep_for(1000);
            output_board = 0;
            output_robot = 0;
            set_robot_state = 0;
        }
    }
}

int main()
{ 
    char buffer[256];  // Buffer to hold the input text

    // Prompt the user to enter a line of text
    printf("Enter a line of text: ");

    // Read a line of text from the user
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        // Print the text back to the console
        printf("You entered: %s", buffer);
    } else {
        // Handle error if reading input fails
        printf("Error reading input.\n");
    }

    return 0;
}
