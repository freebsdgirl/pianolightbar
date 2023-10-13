#ifndef PIANOLIGHTBAR_H_  // #include guards

#define PIANOLIGHTBAR_H_

#include <MIDI.h>
#include <FastLED.h>
#include <SPI.h>

#include "mode.h"

// Hardware configuration
#define DATA_PIN    51
#define CLK_PIN   52
#define NUM_LEDS			176
#define NUM_KEYS        		88

#define LED_TYPE    APA102
#define COLOR_ORDER BRG

// config defaults
#define DEFAULT_GLOBAL_BRIGHTNESS	255
#define DEFAULT_BRIGHTNESS		255
#define DEFAULT_SATURATION		255
#define DEFAULT_HUE			128
#define _BLUR_SPEED			4
#define _FADE_SPEED			10

// debug macros
#define DEBUG   
#ifdef DEBUG    
	#define D(...)		Serial.print(__VA_ARGS__)
	#define DLN(...)	Serial.println(__VA_ARGS__)
	#define TR(...)		Serial.print(__VA_ARGS__)
	#define TRLN(...)	Serial.println(__VA_ARGS__)
#else
	#define D(...)   
	#define DLN(...)
	#define TR(...)
	#define TRLN(...)
#endif

bool needs_update = false;

// ok look. i know this is a bad practice. but oh no, don't make a buffer 
// overflow for my piano lightbar, whatever will i do?
char debug_msg[128]; 

CRGB l[NUM_LEDS];


struct piano_state {
	bool sustain_pedal;
	uint8_t brightness;
	uint8_t loop_i;

	// how often to run each mode if enabled - smaller is faster
	uint8_t blur_s;
	uint8_t fade_s;
} st;


// todo - PROGMEM
const char * pitch_to_note[] = {
	 "C", "C#",  "D", "D#",
	 "E",  "F", "F#",  "G",
	"G#",  "A", "A#",  "B" 
};
CHSV target_color = CHSV( 192, 255, 255 );
CHSV next_color = CHSV( 124, 255, 255 );


/*********** function declarations /***********



/***** midi.ino *****/


// callback for MIDI CC
void midi_cc ( byte channel, byte number, byte value );

// callback for MIDI when a key is pressed
void midi_note_off ( byte channel, byte pitch, byte velocity );

// callback for MIDI when a key is released
void midi_note_on ( byte channel, byte pitch, byte velocity );


/***** pedal.ino *****/


// set or retrieve the status of the sustain pedal
void sustain_pedal ( bool value );
bool sustain_pedal ();


// led.ino
void update_leds ();
void fade_leds ();
void blur_leds ();
void blend_palette();
void update_hue ();

/***** class definitions *****/

CRGBPalette16 currentPalette(OceanColors_p);
CRGBPalette16 targetPalette(ForestColors_p);
TBlendType    currentBlending;                                // NOBLEND or LINEARBLEND




#endif /* PIANOLIGHTBAR_H_ */