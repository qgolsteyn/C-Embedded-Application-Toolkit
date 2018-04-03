#include "Touchscreen.h"

#include "Assert.h"

struct Point mouseLocation;

int putcharTouch(int c)
{
	M_Stack();
	// poll Tx bit(bit 0) in 6850 status register. Wait for it to become '1'
	while((TOUCH_STATUS >> 1) % 2 == 0);
	TOUCH_TXDATA = c;
	M_Unstack();
	return c;
}

int getcharTouch()
{
	M_Stack();
	// poll Rx bit in 6850 status register. Wait for it to become '1'
	while(TOUCH_STATUS % 2 == 0);
	M_Unstack();
	return TOUCH_RXDATA;
}

void DE1_touchInit()
{
	M_Stack();
	TOUCH_CONTROL = 0x15;
  	TOUCH_BAUD = 0x05; //9600
  	putcharTouch(0x12);
  	M_Unstack();
}

int DE1_isScreenTouched()
{
  return 0x01 & TOUCH_STATUS;
}

struct Point DE1_getLastTouchLocation()
{
	M_Stack();
	if(DE1_isScreenTouched()) {
		char byte1 = getcharTouch();
		if((byte1 & 0xff) == 0x80) {
			mouseLocation.status = RELEASED;
		} else if((byte1 & 0xff) == 0x81) {
			mouseLocation.status = PRESSED;
		} else {
			mouseLocation.status = NONE;
			M_Unstack();
			return mouseLocation;
		}

		char byte2 = getcharTouch();
		char byte3 = getcharTouch();
		char byte4 = getcharTouch();
		char byte5 = getcharTouch();

		int x = ((double) (byte2 >> 1) + (byte3 << 7)) / 4096 * 770 + 0.5;
		int y = ((double) (byte4 >> 1) + (byte5 << 7)) / 4096 * 480 + 0.5;

		if(x >= 0 && x <= 800 && y >= 0 && y <= 480) {
			mouseLocation.x = x;
			mouseLocation.y = y;
		}
		M_Unstack();
		return mouseLocation;

	} else {
		M_Unstack();
		return mouseLocation;
	}
}

void DE1_clearLastTouchLocation()
{
	M_Stack();
	mouseLocation.x = 0;
	mouseLocation.y = 0;
	mouseLocation.status = NONE;
	M_Unstack();
}
