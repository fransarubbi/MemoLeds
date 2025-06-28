#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>
#include "Event/event.h"

#define DEBOUNCE_TIME 80


enum ButtonState { WAIT, DEBOUNCE, PRESS };


class DebouncedButton {
public:
    DebouncedButton(int pin, unsigned long debounceTime, colour_t colour);
    void update();

private:
    int pin;
    unsigned long lastDebounceTime;
    ButtonState state;
    colour_t colour;
};


class DebouncedOkButton {
public:
    DebouncedOkButton(int pin, unsigned long debounceTime, bool flag);
    void update();
    void consume_flag();
    bool getFlag(); 

private:
    int pin;
    unsigned long lastDebounceTime;
    ButtonState state;
    bool flag;
};


extern DebouncedButton greenButton;
extern DebouncedButton yellowButton; 
extern DebouncedButton blueButton;
extern DebouncedButton redButton;
extern DebouncedOkButton okButton;


#endif