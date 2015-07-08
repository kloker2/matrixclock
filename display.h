#ifndef DISPLAY_H
#define DISPLAY_H

#include <inttypes.h>

#define PARAM_UP				1
#define PARAM_DOWN				-1

/* Display modes */
enum {
	MODE_MAIN,
	MODE_EDIT_TIME,
	MODE_EDIT_ALARM,
	MODE_BRIGHTNESS
};

#define MASK_HOUR_TENS			0xF8000000UL
#define MASK_HOUR_UNITS			0x07C00000UL
#define MASK_MIN_TENS			0x0007C000UL
#define MASK_MIN_UNITS			0x00003E00UL

#define MASK_BIGHOUR_TENS		0xF8000000UL
#define MASK_BIGHOUR_UNITS		0x03E00000UL
#define MASK_BIGMIN_TENS		0x0007C000UL
#define MASK_BIGMIN_UNITS		0x00001F00UL

#define MASK_EXTRAHOUR_TENS		0xFC000000UL
#define MASK_EXTRAHOUR_UNITS	0x01F80000UL
#define MASK_EXTRAMIN_TENS		0x00001F80UL
#define MASK_EXTRAMIN_UNITS		0x0000003FUL

#define MASK_SEC_TENS			0x000000F0UL
#define MASK_SEC_UNITS			0x0000000FUL

#define MASK_BR_TENS			0xF0000000UL
#define MASK_BR_UNITS			0x07800000UL

#define MASK_NONE				0x00000000UL
#define MASK_ALL				0xFFFFFFFFUL

enum {
	SCROLL_DATE = 0,
	SCROLL_TEMP,
};

void displayInit(void);
void displaySwitchBigNum(void);
void displaySwitchHourZero(void);
void startScroll(uint8_t type);

void showTime(uint32_t mask);
void showTimeMasked(void);
void showMainScreen(void);
void showTimeEdit(int8_t ch_dir);
void showAlarmEdit(int8_t ch_dir);

void changeBrightness(int8_t diff);
void showBrightness(int8_t ch_dir, uint32_t mask);
void saveMaxBrightness(void);
void checkAlarmAndBrightness(void);

#endif /* DISPLAY_H */
