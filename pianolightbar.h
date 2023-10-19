#ifndef PIANOLIGHTBAR_H_  // #include guards

#define PIANOLIGHTBAR_H_

#include <MIDI.h>
#include <FastLED.h>
#include <SPI.h>

#include "mode.h"

// Hardware configuration
#define DATA_PIN	51
#define CLK_PIN 	52
#define NUM_LEDS	176
#define LED_TYPE    APA102
#define COLOR_ORDER BGR
#define NUM_KEYS	88

// config defaults
#define DEFAULT_GLOBAL_BRIGHTNESS	255
#define DEFAULT_BRIGHTNESS			255
#define DEFAULT_SATURATION			255
#define DEFAULT_HUE					128

#define _BLUR_SPEED		64	// used by blur1d() - 172 is max.
#define _FADE_SPEED		12  // used by fade()


// debug macros
//#define DEBUG   
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

struct piano_state {
	bool sustain_pedal;		// is the sustain pedal on?
	uint8_t brightness;
	uint8_t loop_i;

	uint8_t blur_s;			// used by blur1d()
	uint8_t fade_s;			// used by fade()
} st;

bool needs_update = false;

// ok look. i know this is a bad practice. but oh no, don't make a buffer 
// overflow for my piano lightbar, whatever will i do?
char debug_msg[128]; 

// our LED structure that is passed to fastled
CRGB l[NUM_LEDS];

// todo - PROGMEM
const char * pitch_to_note[] = {
	 "C", "C#",  "D", "D#",
	 "E",  "F", "F#",  "G",
	"G#",  "A", "A#",  "B" 
};
CHSV target_color = CHSV( 192, 255, 255 );
CHSV next_color = CHSV( 124, 255, 255 );


// callback for MIDI CC
void midi_cc ( byte channel, byte number, byte value );

// callback for MIDI when a key is pressed
void midi_note_off ( byte channel, byte pitch, byte velocity );

// callback for MIDI when a key is released
void midi_note_on ( byte channel, byte pitch, byte velocity );

// set or retrieve the status of the sustain pedal
void sustain_pedal ( bool value );
bool sustain_pedal ();

void update_leds ();
void fade_leds ();
void blur_leds ();
void blend_palette();
void update_hue ();


CRGBPalette16 currentPalette(OceanColors_p);
CRGBPalette16 targetPalette(ForestColors_p);
TBlendType    currentBlending;                                // NOBLEND or LINEARBLEND

#endif /* PIANOLIGHTBAR_H_ */