/*
With some amount of memory optimization
*/

#include "EEPROM.h"
#include <Adafruit_NeoPixel.h>

#define WS2812_PIN 0
#define STATUS_PIN 1
#define LEFT_BUTTON_PIN 2

#define NUMPIXELS 5
const int middle_pixel = NUMPIXELS / 2 + 1;

#define PROGRAM_ADDRESS 0
#define H_LOWER_BOUND_ADDRESS 1
#define H_UPPER_BOUND_ADDRESS 2
#define H_RATE_ADDRESS 3
#define S_LOWER_BOUND_ADDRESS 4
#define S_UPPER_BOUND_ADDRESS 5
#define S_RATE_ADDRESS 6
#define V_LOWER_BOUND_ADDRESS 7
#define V_UPPER_BOUND_ADDRESS 8
#define V_RATE_ADDRESS 9

#define TICK 100

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, WS2812_PIN, NEO_RGB + NEO_KHZ800);

void HSV_to_RGB();
void update_hsv();
void generate_new_pattern();
void print_message();
void button_detect();

#define NUM_PROGRAMS 5

void left_to_right_or_right_to_left();
void meet_in_the_middle_or_spread_to_end();
void matrix();

#define MAX_H 360
#define MAX_S 100
#define MAX_V 25
#define MAX_H_RATE 20
#define MAX_S_RATE 5
#define MAX_V_RATE 5

uint8_t program;
uint8_t h;
uint8_t h_lower_bound;
uint8_t h_upper_bound;
uint8_t h_rate;
uint8_t s;
uint8_t s_lower_bound;
uint8_t s_upper_bound;
uint8_t s_rate;
uint8_t v;
uint8_t v_lower_bound;
uint8_t v_upper_bound;
uint8_t v_rate;
uint8_t r;
uint8_t g;
uint8_t b;

void setup() {
	pixels.begin(); // This initializes the NeoPixel library.
	program = EEPROM.read(PROGRAM_ADDRESS) % NUM_PROGRAMS;
	h_lower_bound = EEPROM.read(H_LOWER_BOUND_ADDRESS);
	h_upper_bound = EEPROM.read(H_UPPER_BOUND_ADDRESS);
	h_rate = EEPROM.read(H_RATE_ADDRESS) % MAX_H_RATE;
	s_lower_bound = EEPROM.read(S_LOWER_BOUND_ADDRESS);
	s_upper_bound = EEPROM.read(S_UPPER_BOUND_ADDRESS);
	s_rate = EEPROM.read(S_RATE_ADDRESS) % MAX_S_RATE;
	v_lower_bound = EEPROM.read(V_LOWER_BOUND_ADDRESS);
	v_upper_bound = EEPROM.read(V_UPPER_BOUND_ADDRESS);
	v_rate = EEPROM.read(V_RATE_ADDRESS) % MAX_V_RATE;
	pinMode(LEFT_BUTTON_PIN, INPUT);
	digitalWrite(LEFT_BUTTON_PIN, HIGH); 
}

void loop() {
	// For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
	switch(program){
		case 0:
		case 1:
			left_to_right_or_right_to_left();
			break;
		case 2:
		case 3:
			meet_in_the_middle_or_spread_to_end();
			break;
		case 4:
		default:
			matrix();
			break;
	}
}

void HSV_to_RGB()
{
	/*
	Adapted with love from hdznrrd/gist:656996
	*/

	int i;
	float f, p, q, t, h_f, s_f, v_f;
	h_f = h;
	s_f = s;
	v_f = v;

	s_f /= 100;
	v_f /= 100;

	h_f /= 60; // sector 0 to 5
	i = h_f;
	f = h_f - i; // factorial part of h_f
	p = v_f * (1 - s_f);
	q = v_f * (1 - s_f * f);
	t = v_f * (1 - s_f * (1 - f));
	switch(i) {
		case 0:
			r = 255*v_f;
			g = 255*t;
			b = 255*p;
			break;
		case 1:
			r = 255*q;
			g = 255*v_f;
			b = 255*p;
			break;
		case 2:
			r = 255*p;
			g = 255*v_f;
			b = 255*t;
			break;
		case 3:
			r = 255*p;
			g = 255*q;
			b = 255*v_f;
			break;
		case 4:
			r = 255*t;
			g = 255*p;
			b = 255*v_f;
			break;
		default: // case 5:
			r = 255*v_f;
			g = 255*p;
			b = 255*q;
	}

}

void update_hsv(){
	h += random(h_rate);
	h = (h > h_upper_bound ? h - h_upper_bound + h_lower_bound : h);
	s += random(s_rate);
	s = (s > s_upper_bound ? s - s_upper_bound + s_lower_bound : s);
	v += random(v_rate);
	v = (v > v_upper_bound ? v - v_upper_bound + v_lower_bound : v);
	HSV_to_RGB();
}

void generate_new_pattern(){
	EEPROM.write(PROGRAM_ADDRESS, program = random(0,NUM_PROGRAMS));
	EEPROM.write(H_LOWER_BOUND_ADDRESS, h_lower_bound = random(0, 1 * MAX_H_RATE));
	EEPROM.write(H_UPPER_BOUND_ADDRESS, h_upper_bound = random(MAX_H - 1 * MAX_H_RATE, MAX_H));
	EEPROM.write(H_RATE_ADDRESS, h_rate = random(0,MAX_H_RATE));
	EEPROM.write(S_LOWER_BOUND_ADDRESS, s_lower_bound = random(0, 1 * MAX_S_RATE));
	EEPROM.write(S_UPPER_BOUND_ADDRESS, s_upper_bound = random(MAX_S - 1 * MAX_S_RATE, MAX_S));
	EEPROM.write(S_RATE_ADDRESS, s_rate = random(0,MAX_S_RATE));
	EEPROM.write(V_LOWER_BOUND_ADDRESS, v_lower_bound = random(0, 1 * MAX_V_RATE));
	EEPROM.write(V_UPPER_BOUND_ADDRESS, v_upper_bound = random(MAX_V - 1 * MAX_V_RATE, MAX_V));
	EEPROM.write(V_RATE_ADDRESS, v_rate = random(0,MAX_V_RATE));
}

void left_to_right_or_right_to_left(){
	for(int i = 0; i < NUMPIXELS; i++){
		update_hsv();
		if (program == 1){
			pixels.setPixelColor(i, pixels.Color(g,r,b));
		}else{
			// program == 1
			pixels.setPixelColor(NUMPIXELS - i - 1, pixels.Color(g,r,b));
		}
		pixels.show();
		button_detect();
		delay(TICK);
	}
}

void meet_in_the_middle_or_spread_to_end(){
	for(int i = 0; i < middle_pixel; i++){
		update_hsv();
		if (program == 2){
			pixels.setPixelColor(middle_pixel + i - 1, pixels.Color(g,r,b));
			pixels.setPixelColor(middle_pixel - i - 1, pixels.Color(g,r,b));
		}else{
			pixels.setPixelColor(0 + i, pixels.Color(g,r,b));
			pixels.setPixelColor(NUMPIXELS - i - 1, pixels.Color(g,r,b));
		}
		pixels.show();
		button_detect();
		delay(TICK);
	}
}

void matrix(){
	update_hsv();
	pixels.setPixelColor(random(NUMPIXELS), pixels.Color(g,r,b));
	pixels.show();
	button_detect();
	delay(TICK);
}


void button_detect(){
	if (not digitalRead(LEFT_BUTTON_PIN)){
		generate_new_pattern();
	}
}