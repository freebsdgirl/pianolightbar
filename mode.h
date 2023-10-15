#ifndef MODE_H_  // #include guards

#define MODE_H_

// TODO - PROGMEM
// TODO - array of bools
typedef bool mode;

mode MODE_DEFAULT;
mode MODE_HUE_FROM_PITCH;
mode MODE_SINGLE_HUE;		// default: keys are set to a single colour ( set in key.h )
mode MODE_BLUR;
mode MODE_FADE;
mode MODE_INSTANT_OFF; 		// default: keys immediately turn off when released.
mode MODE_OCEAN;

// hue values for each pitch
// TODO - move to PROGMEM
const uint8_t pitch_to_hue[] = {
	147, 168, 189, 210, 
	231,   0,  20,  41,
	 62,  83, 105, 126
};

/* functions */
void setup_modes();
void mode_blur();
void mode_fade();
void mode_instant_off();
void mode_ocean();

#endif
