#include <Arduino.h>
#include "Button/button.h"
#include "Event/event.h"
#include "Led/led.h"
#include "FSM/fsm.h"


DebouncedButton greenButton(2, 80, GREEN);
DebouncedButton yellowButton(5, 80, YELLOW); 
DebouncedButton blueButton(4, 80, BLUE);
DebouncedButton redButton(16, 80, RED);
DebouncedOkButton okButton(18, 80, false);
EventQueue eventQueueButtons;
EventQueue eventQueueLeds;


void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(23));
  init_FSM();
  init_Led();
  init_EventQueue(&eventQueueButtons);
  init_EventQueue(&eventQueueLeds);
}

void loop() {
  greenButton.update();
  yellowButton.update();
  blueButton.update();
  redButton.update();
  okButton.update();
  update_FSM();
}
