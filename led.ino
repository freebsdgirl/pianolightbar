#include "pianolightbar.h"
#include "key.h"


void blend_palette() {
	nblendPaletteTowardPalette(currentPalette, targetPalette, 1);
}


bool led_is_on(uint8_t led_i) {
	if ( 	l[led_i].raw[0] == 0 && 
		l[led_i].raw[1] == 0 &&
		l[led_i].raw[2] == 0) {
		return( false );
	}

	return( true );
}


void update_hue() {
	for (int i = 0; i < NUM_KEYS; i++) {
		if ( keys[i].active() ) {
			CHSV current_key = CHSV(keys[i].h, keys[i].s, keys[i].v);
			CHSV new_key = nblend(next_color, target_color, beatsin8(6, 0, 255, 0, 2500), SHORTEST_HUES);

			snprintf(debug_msg, sizeof(debug_msg), "hsv current: %d,%d,%d new: %d,%d,%d blend: %d,%d,%d", 
				keys[i].h, keys[i].s, keys[i].v, 
				target_color.h, target_color.s, target_color.v, 
				new_key.h, new_key.s, new_key.v);
			DLN(debug_msg);
			
			keys[i].h = new_key.h;
			keys[i].s = new_key.s;
			keys[i].v = new_key.v;
		} 
		/*
		else {
			if (led_is_on(led_number)) {
				CHSV current_hsv = rgb2hsv_approximate(l[led_number]);
				CHSV new_hue = rgb2hsv_approximate(ColorFromPalette(currentPalette, map(i, 0, NUM_KEYS - 1, 0, 255), current_hsv.v));
				keys[i].hue = new_hue.h;
				keys[i].saturation = new_hue.s;
				keys[i].value = new_hue.v;
				l[led_number].setHSV(new_hue.h, new_hue.s, new_hue.v);
			} else {
				CHSV new_hue = rgb2hsv_approximate(ColorFromPalette(currentPalette, map(i, 0, NUM_KEYS - 1, 0, 255), random8(10) + keys[i].v - 5 ));
				keys[i].hue = new_hue.h;
				keys[i].saturation = new_hue.s;
				keys[i].value = new_hue.v;
			}
			if (led_is_on(led_number + 1)) {
				CHSV current_hsv = rgb2hsv_approximate(l[led_number]);
				CHSV new_hue = rgb2hsv_approximate(ColorFromPalette(currentPalette, map(i, 0, NUM_KEYS - 1, 0, 255), current_hsv.v));
				keys[i].hue = new_hue.h;
				keys[i].saturation = new_hue.s;
				keys[i].value = new_hue.v;
				l[led_number + 1].setHSV(new_hue.h, new_hue.s, new_hue.v);
			}else {
				CHSV new_hue = rgb2hsv_approximate(ColorFromPalette(currentPalette, map(i, 0, NUM_KEYS - 1, 0, 255), random8(10) + keys[i].v - 5 ));
				keys[i].hue = new_hue.h;
				keys[i].saturation = new_hue.s;
				keys[i].value = new_hue.v;
			}
		}
		*/
		
	}
}
