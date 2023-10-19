#include "pianolightbar.h"
#include "key.h"

// run any initialization functions for set modes.
void setup_modes() {
	if ( MODE_DEFAULT ) 		{ mode_default();		}

	if ( MODE_OCEAN )			{ mode_ocean_init();		}

	if ( MODE_SINGLE_HUE )		{ mode_single_hue_init();     	}
	if ( MODE_HUE_FROM_PITCH ) 	{ mode_hue_from_pitch_init(); 	}

	if ( MODE_BLUR )			{ mode_blur_init();     	}
	if ( MODE_FADE ) 			{ mode_fade_init(); 		}
	if ( MODE_INSTANT_OFF ) 	{ mode_instant_off_init(); 	}
}


// if a key is marked as active, set a new hue value
void mode_ocean() {
	CHSVPalette16 HSV_OceanColors_p;

	HSV_OceanColors_p = CHSVPalette16(
		CHSV( 160, 255, 180 ), // blue
		CHSV( 160, 255, 180 ),
		CHSV( 145, 255, 255 ), // ocean-y blue

		CHSV (121, 255, 255 ), // aquamarine
		CHSV( 145, 255, 255 ),
		CHSV( 145, 255, 255 ),

		CHSV( 149, 168, 255 ), // dodger blue
		CHSV( 149, 168, 255 ),
		CHSV( 149, 168, 255 ),

		CHSV( 160, 150, 255 ), // light blue
		CHSV( 160, 150, 255 ),
		CHSV( 160, 150, 255 ),

		CHSV( 160, 200, 255 ), // medium blue
		CHSV( 160, 200, 255 ),
		CHSV( 145, 200, 255 ), // sky blue)

		CHSV( 160, 255, 180 ) // blue
	);
	// change the hue
	EVERY_N_MILLISECONDS(1) {
		CHSV new_colour = ColorFromPalette(HSV_OceanColors_p, beatsin8(6, 0, 255, 0, 0), 255, LINEARBLEND);
		for ( int key_index = 0; key_index < NUM_KEYS; key_index++ ) {
			if ( keys[key_index].active() ) {
				keys[key_index].set_hsv( new_colour.h, new_colour.s, new_colour.v );
				keys[key_index].set_default_hsv( new_colour.h, new_colour.s, new_colour.v );
			}
		}
	}
}


void mode_ocean_init() {
	TRLN("mode_ocean_init()");
	MODE_BLUR = true;

	MODE_DEFAULT = false;
	MODE_SINGLE_HUE = false;
	MODE_HUE_FROM_PITCH = false;
	MODE_FADE = true;
	MODE_INSTANT_OFF = false;
}


// set up our default mode
void mode_default() {
	MODE_OCEAN = false;

	MODE_SINGLE_HUE = true;
	MODE_HUE_FROM_PITCH = false;

	MODE_BLUR = false;
	MODE_FADE = false;
	MODE_INSTANT_OFF = true;

	MODE_OCEAN = false;

}


// set each key to the same colour.
void mode_single_hue_init() {
	MODE_HUE_FROM_PITCH = false;
	for ( int key_index = 0; key_index < NUM_KEYS; key_index++ ) {
		keys[key_index].set_default_hsv(_default_hue, _default_saturation, _default_value);
	}
}


// set hue based on the note/pitch value. 
// i.e, all A keys are the same colour.
void mode_hue_from_pitch_init() {
	MODE_DEFAULT = false;
	MODE_SINGLE_HUE = false;
	for ( int key_index = 0; key_index < NUM_KEYS; key_index++ ) {
		uint8_t pitch = keys[key_index].pitch();
		keys[key_index].set_hue( pitch_to_hue[ pitch % 12 ] );
	}
}


// disable conflicting modes
void mode_blur_init() {
	MODE_DEFAULT = false;
	MODE_INSTANT_OFF = false;
}


// blur all leds
void mode_blur () {
	EVERY_N_MILLISECONDS(10) {
		blur1d( l, NUM_LEDS, st.blur_s );
	}
}


// disable conflicting modes
void mode_fade_init() {
	MODE_DEFAULT = false;
	MODE_INSTANT_OFF = false;
}


// fade any led not marked as belonging to an active key
void mode_fade() {
	if ( st.loop_i % st.fade_s )
		return;

	for ( int key_index = 0; key_index < NUM_KEYS; key_index++ ) {
		if ( ! keys[key_index].active() ) {
			keys[key_index].fade( st.fade_s, true );
		}
	}
}


void mode_instant_off_init() {
	TRLN("mode_instant_off_init()");

	MODE_FADE = false;
	MODE_BLUR = false;
}


void mode_instant_off() {
	//TRLN("mode_instant_off()");
	
	for ( int key_index = 0; key_index < NUM_KEYS; key_index++ ) {
		if ( ! keys[key_index].active() ) {
			keys[key_index].leds_off();
		}
	}
}