#ifndef EVENT_H
#define EVENT_H

#include <cstdint> 
#include "Led/led.h"

#define MAX 20


struct EventQueue {
	colour_t buffer[MAX];   // 0: verde, 1: amarillo, 2: azul, 3: rojo
	uint8_t top;
	uint8_t last;
	uint8_t cant;
};

extern EventQueue eventQueueButtons;
extern EventQueue eventQueueLeds;

void init_EventQueue(EventQueue*);
bool consult_EventQueue(EventQueue*, colour_t*);
bool insert_EventQueue(EventQueue*, colour_t);
void supress_EventQueue(EventQueue*);


#endif
