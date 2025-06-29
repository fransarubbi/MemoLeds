#include "Button/button.h"
#include <Arduino.h>


colour_t match(int pin){
    switch(pin){
        case 2: return COLOURS[0]; 
        case 5: return COLOURS[1];
        case 4: return COLOURS[2];
        case 16: return COLOURS[3];
        default: return COLOURS[0];
    }
}


int match_led(int pin){
    switch(pin){
        case 2: return 17; 
        case 5: return 19;
        case 4: return 39;
        case 16: return 36;
        default: return 17;
    }
}



DebouncedButton :: DebouncedButton(int pin, unsigned long debounceTime, colour_t colour) : pin(pin), state(WAIT) {
    pinMode(pin, INPUT);
    lastDebounceTime = 0;
}

void DebouncedButton :: update() {
    switch (state) {
        case WAIT:
            if (digitalRead(pin)) {
                lastDebounceTime = millis();
                state = DEBOUNCE;
            }
            break;

        case DEBOUNCE:
            if ((millis() - lastDebounceTime) >= DEBOUNCE_TIME) {
                if (digitalRead(pin)) {
                    state = PRESS;
                    insert_EventQueue(&eventQueueButtons, match(pin));
                    digitalWrite(match_led(pin), HIGH);
                } else {
                    state = WAIT;
                }
            }
            break;

        case PRESS:
            if (!digitalRead(pin)) {
                digitalWrite(match_led(pin), LOW);
                state = WAIT;
            }
            break;
    }
}


DebouncedOkButton :: DebouncedOkButton(int pin, unsigned long debounceTime, bool flag) : pin(pin), state(WAIT), flag(flag) {
    pinMode(pin, INPUT);
    lastDebounceTime = 0;
}

void DebouncedOkButton :: update() {
    switch (state) {
        case WAIT:
            if (digitalRead(pin)) {
                lastDebounceTime = millis();
                state = DEBOUNCE;
            }
            break;

        case DEBOUNCE:
            if ((millis() - lastDebounceTime) >= DEBOUNCE_TIME) {
                if (digitalRead(pin)) {
                    state = PRESS;
                    flag = true;
                } else {
                    state = WAIT;
                }
            }
            break;

        case PRESS:
            if (!digitalRead(pin)) {
                state = WAIT;
            }
            break;
    }
}

void DebouncedOkButton :: consume_flag() {
    flag = false;
}

bool DebouncedOkButton :: getFlag() {
    return flag;
}