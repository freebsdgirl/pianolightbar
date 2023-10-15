#include "pianolightbar.h"
#include "key.h"


/* 
			if (st.m == 4 ) {
				led[0]->fadeToBlackBy(10);
				led[1]->fadeToBlackBy(10);
			}
*/


// initialize keys
void setup_keys() {
	for (int i = 0; i < NUM_KEYS; i++) {
		keys[i].init(i);
	}
}


// called during the main loop, this function should update the values of 
// active LEDs if needed based on mode
// this does NOT refresh the contents of the LEDS with FastLED.show(), however.
void update_leds() {
	// mode functions!
	// each mode will verify that there are no conflicting modes enabled,
	// i.e., a fade mode won't run if a blur mode is enabled.
	// TODO - instant off shouldn't be a mode, we should just check
	// to see if blur or fade is enabled, and if not, turn any inactive keys off.
	if ( MODE_OCEAN )	{ mode_ocean(); }
	if ( MODE_FADE )	{ mode_fade(); }
	if ( MODE_BLUR ) 	{ mode_blur(); }
	if ( MODE_INSTANT_OFF ) { mode_instant_off(); }

	// sometimes we drop an update because of a lot of MIDI data. 
	// ensure that each LED is in the state we expect it to be in.
	for (int i = 0; i < NUM_KEYS; i++) {
		if ( keys[i].active() ) {
			keys[i].leds_on();
		}
	}
	// todo - processing for hue changes
	// do we need to update the current hsv object?
}

