#include "FSM/fsm.h"
#include "Button/button.h"
#include "Led/led.h"
#include "Event/event.h"


uint8_t level;
State state;
colour_t colourButton, colourLed;
bool check;


void init_FSM(){
    level = 1;
    state = INIT;
    check = true;
}


void update_FSM(){
    switch(state){
        case INIT:  if(okButton.getFlag()){
                        okButton.consume_flag();
                        state = GENERATE;
                    }
                    break;

        case GENERATE:  create_sequence();
                        state = WAITING;
                        break;

        case WAITING:   if(okButton.getFlag()){
                            okButton.consume_flag();
                            state = COMPARING;
                        }
                        break;

        case COMPARING: while(consult_EventQueue(&eventQueueLeds, &colourLed)){
                            consult_EventQueue(&eventQueueButtons, &colourButton);
                            if(colourLed != colourButton){
                                check = false;
                            }
                            supress_EventQueue(&eventQueueButtons);
                            supress_EventQueue(&eventQueueLeds);
                        }
                        if(check){
                            state = CORRECT;
                        }
                        else{
                            state = ERROR;
                        }
                        break;

        case ERROR: error();
                    check = true;
                    level = 1;
                    state = INIT;
                    break;

        case CORRECT:   if(level < 10){
                            level+=1;
                            state = GENERATE;
                        }
                        else{
                            state = INIT;
                            level = 1;
                        }
                        break;
    }
}