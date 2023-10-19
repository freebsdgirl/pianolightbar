#include "controls.h"
#include "pianolightbar.h"


void readinputs ( struct inputStates *data ) {
	data->button[0] = ( digitalRead( PIN_BTN0 ) == LOW );
	data->button[1] = ( digitalRead( PIN_BTN1 ) == LOW );
	data->button[2] = ( digitalRead( PIN_BTN2 ) == LOW );

	data->pot[0] = analogRead( PIN_POT0 ) >> 2;
	data->pot[1] = analogRead( PIN_POT1 ) >> 2;
}


void compareinputs ( inputStates *old_p, inputStates *new_p ) {
	uint8_t idx;
	
	for ( idx = 0; idx < 3; idx++ ) {
		if ( old_p->button[idx] != new_p->button[idx] ) {
			old_p->button[idx] = new_p->button[idx];
		}
	}

	for ( idx = 0; idx < 2; idx++ ) {
		if ( old_p->pot[idx] != new_p->pot[idx] ) {
			old_p->pot[idx] = new_p->pot[idx];
			if ( idx == 0 ) {
				// st.blur_s is used by fastLED's blur1d - 172 is the max value we want to have.
				st.blur_s = ( old_p->pot[idx] / 3 );
			}
			else if ( idx == 1 ) {
					st.fade_s = ( old_p->pot[idx] / 10 );
			}
		}
	}
}


void updateLEDs ( inputStates * data ) {
	digitalWrite( PIN_LED_GRN, !data->button[0] );
	digitalWrite( PIN_LED_RED, !data->button[1] );
}

void setup_controls () {
	pinMode( PIN_BTN0, INPUT_PULLUP );
	pinMode( PIN_BTN1, INPUT_PULLUP );
	pinMode( PIN_BTN2, INPUT_PULLUP );

	pinMode( PIN_LED_GRN, OUTPUT );
	pinMode( PIN_LED_RED, OUTPUT );

	readinputs( &lastdata );
}


void loop_controls() {
	readinputs( &newdata );
	compareinputs( &lastdata, &newdata );
	updateLEDs( &newdata );
}