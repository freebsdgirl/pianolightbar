#ifndef CONTROLS_H_  // #include guards

#define CONTROLS_H_ 

static const uint8_t PIN_BTN0 = 2;
static const uint8_t PIN_BTN1 = 3;
static const uint8_t PIN_BTN2 = 4;

static const uint8_t PIN_POT0 = 0;
static const uint8_t PIN_POT1 = 1;

static const uint8_t PIN_LED_GRN = 6;
static const uint8_t PIN_LED_RED = 7;

typedef struct inputStates
{
  uint8_t button[3];
  uint8_t pot[2];
}inputStates;

inputStates lastdata;
inputStates newdata;

void setup_controls();
void loop_controls();
#endif