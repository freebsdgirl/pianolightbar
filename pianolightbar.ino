#include "pianolightbar.h"
#include "key.h"
#include "mode.h"


MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

uint8_t current_pal = 0;
void setup() {
	/***** initialize default state  *****/
	st.brightness = DEFAULT_GLOBAL_BRIGHTNESS;
	st.sustain_pedal = false;
	st.loop_i = 0;
	st.blur_s = _BLUR_SPEED;
	st.fade_s = _FADE_SPEED;

	/***** Serial *****/
	Serial.begin(115200);

	/***** LEDs *****/
	FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(l, NUM_LEDS);

	FastLED.clear();
	FastLED.show();


  	currentBlending = LINEARBLEND;

	/***** MIDI *****/
	MIDI.begin(1);	// channel 1 only
	MIDI.setHandleNoteOn(midi_note_on); 
	MIDI.setHandleNoteOff(midi_note_off);
	MIDI.setHandleControlChange(midi_cc);

	setup_keys();

	MODE_OCEAN = true;
	setup_modes();
}


void loop() {
	MIDI.read();

	// track loop iterations - this is used by mode functions
	// to see how often they should run, set by the value in
	// st.<mode>_s, which defaults to _<MODE>_SPEED
	st.loop_i++;

	update_leds();
	FastLED.show();

	// reset loop counter if it hits 255 since this is just a uint8_t.
	if ( st.loop_i == 255 ) {
		st.loop_i = 0;
	}
}