#ifndef LED_H
#define LED_H

#include <cstdint> 

typedef enum { GREEN = 0, YELLOW = 1, BLUE = 2, RED = 3 } colour_t;
extern const colour_t COLOURS[4];

void create_sequence();
uint8_t match(colour_t );
void init_Led();
void error();

#endif
