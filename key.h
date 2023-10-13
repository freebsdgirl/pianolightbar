#ifndef KEY_H_  // #include guards

#define KEY_H_ 

#include "pianolightbar.h"
#include "mode.h"

// config defaults
const uint8_t _default_hue 		= 128;
const uint8_t _default_saturation	= 255;
const uint8_t _default_value	 	= 255;


// TODO
// * hue/sat/val defaults have been removed from the initializer. 
//   create a function that examines mode to assign these values.
// * move led_on/led_off to private
// * pressed/released functions
// * move more variables to private
// * rename is_on to on();
// * overload functions so calling them with no arguments gives the
// * status
// * create function to get CHSV
// * create function to get default CHSV
class Key {
	private:
		uint8_t _pitch;
		CHSV hsv_default;	// used for key on
		CHSV hsv;	// if led is updated from default, use this.

		bool _active;
	public:
		uint8_t number; // human number, not array number
		
		union {
			uint8_t hue;
			uint8_t h;
		};
		union {
			uint8_t saturation;
			uint8_t s;
		};
		union {
			uint8_t value;
			uint8_t v;
		};

		CRGB *led[2];

		Key() {
			hue = _default_hue;
			saturation = _default_saturation;
			value = _default_value;
			_active = false;
		}


		// initialize pitch, key number, led locations.
		void init ( uint8_t key_index ) {

			// MIDI values
			// ref https://computermusicresource.com/midikeys.html, 
			// https://www.inspiredacoustics.com/en/MIDI_note_numbers_and_center_frequencies
			// A0 - key index 0 - key number 1 - midi 21
			// C4 - key index 39 - key number 40 - midi 60
			number = key_index + 1;
			_pitch = number + 20;

			led[0] = &l[ key_index * 2 ];
			led[1] = &l[ ( key_index * 2 ) + 1 ];
		}

		// TODO
		void on() {

			_active = true;
			refresh();
		}

		void off() {

			_active = false;
		}


		bool active() 		{ return( _active ); }
		uint8_t pitch() 	{ return( _pitch ); }


		// if the key is marked as active (on), update the LED
		// with the current stored hsv
		void refresh() {
			if ( _active ) {
				leds_on();
			}
		}

		// changes current hsv & updates LEDs
		void set_hsv( uint8_t hue, uint8_t saturation, uint8_t value ) {
			h = hue;
			s = saturation;
			v = value;

			hsv = CHSV(h, s, v);
			refresh();
		}
		void set_hsv() {
			hsv = CHSV(h, s, v);
			refresh();
		}

		CHSV get_hsv() 			{ return( hsv ); }


		// set hue, update current hsv object.
		void set_hue(uint8_t hue) {
			h = hue;
			set_hsv();
		}
		// set saturation, update current hsv object.
		void set_saturation(uint8_t saturation) {
			s = saturation;
			set_hsv();
		}
		// set brightness level, update current hsv object.
		void set_value(uint8_t value) {
			v = value;
			set_hsv();
		}


		// changes default hsv (when key is first pressed)
		CHSV get_default_hsv() 		{ return( hsv_default ); }

		// set the default hsv to whatever is currently being used
		void set_default_hsv() {
			hsv_default = hsv;
		}

		// set the default hsv to the provided values.
		void set_default_hsv( uint8_t hue, uint8_t saturation, uint8_t value ) {
			hsv_default = CHSV( hue, saturation, value );
		}

		// update hue of default hsv.
		void set_default_hue ( uint8_t hue ) {
			set_default_hsv( hue, hsv_default.saturation, hsv_default.value );
		}

		// update saturation level of default hsv.
		void set_default_saturation ( uint8_t saturation ) {
			set_default_hsv( hsv_default.hue, saturation, hsv_default.value );
		}

		// update brightness level of default hsv.
		void set_default_value ( uint8_t value ) {
			set_default_hsv( hsv_default.hue, hsv_default.saturation, value );
		}

		// TODO - differentiate this between 'first pressed' and 'refreshes'
		void leds_on() {
			*led[0] = hsv;
			*led[1] = hsv;
		}

		void leds_off() {
			*led[0] = CRGB::Black;
			*led[1] = CRGB::Black;
		}

		void fade ( uint8_t fade_amount, bool to_black ) {
			led[0]->fadeToBlackBy(fade_amount);
			led[1]->fadeToBlackBy(fade_amount);
		}
};

Key keys[NUM_KEYS];

/*** function definitions ***/


// initialize each key and set the proper HSV()
void setup_keys ();


#endif // KEY_H_