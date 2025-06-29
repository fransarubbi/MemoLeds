#include "FSM/fsm.h"
#include "Button/button.h"
#include "Led/led.h"
#include "Event/event.h"



uint8_t level;
State state;
colour_t colourButton, colourLed;
bool check, onEntry = true;


void init_FSM(){
    level = 1;
    state = INIT;
    check = true;
}


void clear_row(uint8_t row) {
    lcd.setCursor(0, row);  
    lcd.print("                ");  
    lcd.setCursor(0, row);  
}



void match_string(uint8_t level){
    switch(level){
        case 1: clear_row(1);
                lcd.print("Nivel 1");
                break;
        case 2: clear_row(1);
                lcd.print("Nivel 2");
                break;
        case 3: clear_row(1);
                lcd.print("Nivel 3");
                break;
        case 4: clear_row(1);
                lcd.print("Nivel 4");
                break;
        case 5: clear_row(1);
                lcd.print("Nivel 5");
                break;
        case 6: clear_row(1);
                lcd.print("Nivel 6");
                break;
        case 7: clear_row(1);
                lcd.print("Nivel 7");
                break;
        case 8: clear_row(1);
                lcd.print("Nivel 8");
                break;
        case 9: clear_row(1);
                lcd.print("Nivel 9");
                break;
        case 10:clear_row(1);
                lcd.print("Nivel 10");
                break;
    }
}


void update_FSM(){
    switch(state){
        case INIT:  if(onEntry){
                        lcd.setCursor(0, 0);
                        lcd.print("MemoLeds!");
                        clear_row(1);
                        lcd.print("Pulsa para jugar");
                        onEntry = false;
                    }
                    if(okButton.getFlag()){
                        okButton.consume_flag();
                        state = GENERATE;
                    }
                    break;

        case GENERATE:  match_string(level);
                        create_sequence();
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
                    clear_row(1);
                    lcd.print("Game over :(");
                    check = true;
                    level = 1;
                    state = INIT;
                    break;

        case CORRECT:   if(level < 10){
                            level+=1;
                            state = GENERATE;
                        }
                        else{
                            clear_row(1);
                            lcd.print("Ganaste :)");
                            state = INIT;
                            level = 1;
                        }
                        break;
    }
}