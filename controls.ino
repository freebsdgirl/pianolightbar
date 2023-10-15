#include "controls.h"
#include "pianolightbar.h"


void readinputs(struct inputStates * data)
{
  // A bit of a funny statement below.
  // digitalRead return HIGH or LOW.
  // We want boolean (true/false) indicators of whether the button are
  // pushed.
  // And button inputs are active low - when a button is pushed, it'll read "LOW"
  // The right side of the expression checks if the input is equal to LOW, converting
  // that into a boolean indicator, stored in the array.  
  data->button[0] = (digitalRead(PIN_BTN0) == LOW);
  data->button[1] = (digitalRead(PIN_BTN1) == LOW);
  data->button[2] = (digitalRead(PIN_BTN2) == LOW);

  // Analog inputs have an LSB (out of 10 bits) or so noise, 
  // leading to "chatter" in the change detector logic.
  // Shifting off the 2 LSBs to remove it
  data->pot[0] = analogRead(PIN_POT0) >> 2;
  data->pot[1] = analogRead(PIN_POT1) >> 2;
}

void compareinputs(inputStates * old_p, inputStates * new_p)
{
  uint8_t idx;
  
  for(idx = 0; idx < 3; idx++)
  {
    if(old_p->button[idx] != new_p->button[idx])
    {
      old_p->button[idx] = new_p->button[idx];
      Serial.print("Button #");
      Serial.print(idx);
      Serial.print(" changed to ");
      Serial.println(old_p->button[idx]);
    }
  }

  for(idx = 0; idx < 2; idx++)
  {
    if(old_p->pot[idx] != new_p->pot[idx])
    {
      old_p->pot[idx] = new_p->pot[idx];
      if ( idx == 0 ) {
          st.blur_s = ( old_p->pot[idx] / 10 );
      }
      else if ( idx == 1 ) {
          st.fade_s = ( old_p->pot[idx] / 10 );
      }
    }
  }
}

void updateLEDs(inputStates * data)
{
  digitalWrite(PIN_LED_GRN, !data->button[0]);
  digitalWrite(PIN_LED_RED, !data->button[1]);
}

void setup_controls() {
  pinMode(PIN_BTN0, INPUT_PULLUP);
  pinMode(PIN_BTN1, INPUT_PULLUP);
  pinMode(PIN_BTN2, INPUT_PULLUP);

  pinMode(PIN_LED_GRN, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);

  readinputs(&lastdata);
}

void loop_controls() {
  // put your main code here, to run repeatedly:

  readinputs(& newdata);
  compareinputs(& lastdata, & newdata);
  updateLEDs(&newdata);
}