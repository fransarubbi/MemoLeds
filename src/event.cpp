#include "Event/event.h"
#include <Arduino.h>


void init_EventQueue(EventQueue* eventQueue){
	eventQueue->top = 0;
	eventQueue->last = 0;
	eventQueue->cant = 0;
}


bool consult_EventQueue(EventQueue* eventQueue, colour_t* e){
	if(eventQueue->cant == 0){
		return false;
	}
	*e = eventQueue->buffer[eventQueue->top];
	return true;
}


bool insert_EventQueue(EventQueue* eventQueue, colour_t e){
	if(eventQueue->cant == MAX){
		return false;   // Cola llena
	}
	Serial.println(e);
	eventQueue->buffer[eventQueue->last] = e;
	eventQueue->last = (eventQueue->last + 1) & (MAX - 1);
	eventQueue->cant++;
	return true;
}


void supress_EventQueue(EventQueue* eventQueue){
	eventQueue->top = (eventQueue->top + 1) & (MAX - 1);
	eventQueue->cant--;
}

