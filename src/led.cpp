#include "Led/led.h"
#include "FSM/fsm.h"
#include "Event/event.h"
#include <Arduino.h>

const colour_t COLOURS[4] = { GREEN, YELLOW, BLUE, RED };
unsigned long timeLed = 0;


uint8_t match(colour_t colour){
    switch(colour){
        case GREEN: return 17; 
        case YELLOW: return 19;
        case BLUE: return 13;
        case RED: return 12;
        default: return 17;
    }
}


void create_sequence() {
    uint8_t i, number;
    for (i = 0; i < level+1; i++) {
        number = random(0, 4);
        insert_EventQueue(&eventQueueLeds, COLOURS[number]);
        uint8_t pin = match(COLOURS[number]);
        digitalWrite(pin, HIGH);
        delay(500); 
        digitalWrite(pin, LOW);
        delay(500);  
    }
}


void error(){
    uint8_t i;
    for(i = 0; i < 8; i++){
        digitalWrite(17, HIGH);
        digitalWrite(19, HIGH);
        digitalWrite(13, HIGH);
        digitalWrite(12, HIGH);
        delay(250);
        digitalWrite(17, LOW);
        digitalWrite(19, LOW);
        digitalWrite(13, LOW);
        digitalWrite(12, LOW);
        delay(250);  
    }
}


void init_Led(){
    pinMode(17, OUTPUT);
    pinMode(19, OUTPUT);
    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
}
