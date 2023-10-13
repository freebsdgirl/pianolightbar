#include "pianolightbar.h"
#include "key.h"

// read any cc events that are sent.
// we don't really need to do much with this other than
// read pedal - this can generate a TON of debug traffic.
void midi_cc ( byte channel, byte number, byte value ) {
	TR(":: midi_cc(");
	TR(channel);
	TR(",");
	TR(number);
	TR(",");
	TR(value);
	TRLN(")");

	switch (number)
	{
		case 64:
			sustain_pedal(value > 0);
			break;	
		default:
			D( "CC unknown, channel: " );
			D( channel );
			D( ", number: " );
			D( number );
			D( ", value: " );
			DLN( value );
	}
}


// midi callback function for when a key is pressed
void midi_note_on ( byte channel, byte pitch, byte velocity ) {
	TR(":: midi_note_on (");
	TR(channel);
	TR(",");
	TR(pitch);
	TR(",");
	TR(velocity);
	TRLN(")");
	
	uint8_t key_index = pitch - 21;

	// toggle the key as active
	// this also triggers a refresh which turns the key on with
	// the currently stored hsv, so if we need to change this,
	// do it before turning the key on.
	keys[key_index].on();
}

void midi_note_off ( byte channel, byte pitch, byte velocity ) {
	TR(":: midi_note_off (");
	TR(channel);
	TR(",");
	TR(pitch);
	TR(",");
	TR(velocity);
	TRLN(")");

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