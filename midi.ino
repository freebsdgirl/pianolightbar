#include "pianolightbar.h"
#include "key.h"


// read any cc events that are sent.
// we don't really need to do much with this other than
// read pedal - this can generate a TON of debug traffic.
void midi_cc ( byte channel, byte number, byte value ) {
	snprintf(debug_msg, sizeof(debug_msg), ":: midi_cc(%d,%d,%d)", channel, number, value);
	TRLN(debug_msg);

	switch (number)
	{
		case 64:
			sustain_pedal(value > 0);
			break;	
		default:
			snprintf(debug_msg, sizeof(debug_msg), "CC unknown, channel %d, number %d, value %d", channel, number, value);
			DLN(debug_msg);
	}
}


// midi callback function for when a key is pressed
void midi_note_on ( byte channel, byte pitch, byte velocity ) {
	snprintf(debug_msg, sizeof(debug_msg), ":: midi_note_on(%d,%d,%d)", channel, pitch, velocity);
	TRLN(debug_msg);
	
	uint8_t key_index = pitch - 21;

	// toggle the key as active
	// this also triggers a refresh which turns the key on with
	// the currently stored hsv, so if we need to change this,
	// do it before turning the key on.
	keys[key_index].on();
}


void midi_note_off ( byte channel, byte pitch, byte velocity ) {
	snprintf(debug_msg, sizeof(debug_msg), ":: midi_note_off(%d,%d,%d)", channel, pitch, velocity);
	TRLN(debug_msg);

	keys[pitch - 21].off();
}


void sustain_pedal(bool value) {
	if ( value ) 
		DLN("Sustain: ON");
	else 
		DLN("Sustain: OFF");
	
	st.sustain_pedal = value;
}


bool sustain_pedal() {
	return st.sustain_pedal;
}