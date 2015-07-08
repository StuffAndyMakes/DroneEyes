/*
 * DroneEyes.c
 *
 * Created: 7/4/2015 2:16:46 PM
 *  Author: StuffAndyMakes.com
 */

#define F_CPU 4000000UL

#include <avr/io.h>
#include <util/delay.h>

#define MAX_LED 6

uint8_t matrix[MAX_LED][2] = {
    //   DDRB        PORTB
    { 0b00000011, 0b00000001 },
    { 0b00000011, 0b00000010 },
    { 0b00000110, 0b00000010 },
    { 0b00000110, 0b00000100 },
    { 0b00000101, 0b00000001 },
    { 0b00000101, 0b00000100 }
};

int ledNum = 0;

#define SCAN_RIGHT 1
#define SCAN_LEFT -1

#define STATE_OFF 0
#define STATE_ALL 1
#define STATE_BOUNCE_SLOW 2
#define STATE_BOUNCE_MED 3
#define STATE_BOUNCE_FAST 4
#define STATE_SCAN_LEFT_SLOW 5
#define STATE_SCAN_LEFT_FAST 6
#define STATE_SCAN_RIGHT_SLOW 7
#define STATE_SCAN_RIGHT_FAST 8
#define STATE_BLINK_SLOW 9
#define STATE_BLINK_MED 10
#define STATE_BLINK_FAST 11
#define STATE_MAX 12

uint8_t state = STATE_ALL; // start in all on state

int scanDir = SCAN_RIGHT;

uint8_t animationStep = 0;
uint32_t frameCounter = 0;

void turnOn(uint8_t led) {
    DDRB = matrix[led][0];
    PORTB = matrix[led][1];
}

void allOn() {
	turnOn(ledNum++);
	if (ledNum == MAX_LED) {
		ledNum = 0;
	}
}

void allOff() {
	PORTB = 0;
}

void bounce() {
    turnOn(ledNum);
    ledNum += scanDir;
    if (ledNum == 6) {
        scanDir = SCAN_LEFT;
        ledNum = 4;
    } else if (ledNum == -1) {
        scanDir = SCAN_RIGHT;
        ledNum = 1;
    }
}

void scan() {
    turnOn(ledNum);
    ledNum += scanDir;
    if (ledNum == 6) {
		ledNum = 0;
    } else if (ledNum == -1) {
	    ledNum = 5;
    }
}

void blink(uint16_t frames) {
	frameCounter++;
	if (frameCounter > frames) {
		frameCounter = 0;
		animationStep = (animationStep == 0 ? 1 : 0);
	}
	if (animationStep == 0) {
		allOn();
	} else {
		allOff();
	}
}

int main(void) {
    DDRB = (1 << PB0) | (1 << PB1) | (1 << PB2); // outputs
    PORTB |= (1 << PB4); // internal pull-up
    while(1) {
        
        // handle button
        if ((PINB & (1 << PB4)) == 0) {
			// button is pressed, wait to be sure (debounce)
            _delay_ms(25);
            if ((PINB & (1 << PB4)) == 0) {
                // button is definitely pressed
                state++;
                if (state == STATE_MAX) {
                    state = STATE_OFF;
                }
	            while ((PINB & (1 << PB4)) == 0); // wait for release
            }
        }
 
		if (state == STATE_OFF) {
			continue;
		}

        // main case for state
        switch (state) {
                
            case STATE_ALL:
				allOn();
                break;
                
            case STATE_BOUNCE_SLOW:
				bounce();
				_delay_ms(200);
                break;
                
            case STATE_BOUNCE_MED:
				bounce();
				_delay_ms(100);
                break;
                
            case STATE_BOUNCE_FAST:
				bounce();
				_delay_ms(50);
                break;
                
            case STATE_SCAN_LEFT_SLOW:
				scanDir = SCAN_LEFT;
				scan();
				_delay_ms(100);
				break;
            
            case STATE_SCAN_LEFT_FAST:
				scanDir = SCAN_LEFT;
				scan();
				_delay_ms(50);
				break;
            
            case STATE_SCAN_RIGHT_SLOW:
				scanDir = SCAN_RIGHT;
				scan();
				_delay_ms(100);
				break;
            
            case STATE_SCAN_RIGHT_FAST:
				scanDir = SCAN_RIGHT;
				scan();
				_delay_ms(50);
				break;
            
            case STATE_BLINK_SLOW:
				blink(25000);
				break;

            case STATE_BLINK_MED:
				blink(12500);
				break;

            case STATE_BLINK_FAST:
				blink(5000);
                break;
                
        }
        
    }
    
}
