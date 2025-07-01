#include <Arduino.h>
#include "Button/button.h"
#include "Event/event.h"
#include "Led/led.h"
#include "FSM/fsm.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


DebouncedButton greenButton(15, 80, GREEN);
DebouncedButton yellowButton(5, 80, YELLOW); 
DebouncedButton blueButton(4, 80, BLUE);
DebouncedButton redButton(16, 80, RED);
DebouncedOkButton okButton(18, 80, false);
EventQueue eventQueueButtons;
EventQueue eventQueueLeds;
LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);  // SDA, SCL
  lcd.init();         // Inicializa
  lcd.backlight();     // Enciende luz de fondo
  randomSeed(analogRead(23));
  init_FSM();
  init_Led();
  init_EventQueue(&eventQueueButtons);
  init_EventQueue(&eventQueueLeds);
  pinMode(2, OUTPUT);
}

void loop() {
  greenButton.update();
  yellowButton.update();
  blueButton.update();
  redButton.update();
  okButton.update();
  update_FSM();
}
