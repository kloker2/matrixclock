#include "max7219.h"

#include <avr/pgmspace.h>

#if !defined(MAX7219MOD)
static uint8_t max7219SwapBits(uint8_t data)
{
	data = (data & 0xF0) >> 4 | (data & 0x0F) << 4;
	data = (data & 0xCC) >> 2 | (data & 0x33) << 2;
	data = (data & 0xAA) >> 1 | (data & 0x55) << 1;

	return data;
}
#endif

static void max7219SendByte(uint8_t data)
{
	uint8_t i;

	for(i = 0; i < 8; i++) {
		if (data & 0x80)
			PORT(MAX7219_DIN) |= MAX7219_DIN_LINE;
		else
			PORT(MAX7219_DIN) &= ~MAX7219_DIN_LINE;
		data <<= 1;

		PORT(MAX7219_CLK) &= ~MAX7219_CLK_LINE;
		asm("nop");
		asm("nop");
		PORT(MAX7219_CLK) |= MAX7219_CLK_LINE;
	}

	return;
}

void max7219SendCmd(uint8_t reg, uint8_t data)
{
	uint8_t j;

	PORT(MAX7219_LOAD) &= ~MAX7219_LOAD_LINE;
	for (j = 0; j < MATRIX_NUMBER; j++) {
		max7219SendByte(reg);
		max7219SendByte(data);
	}
	PORT(MAX7219_LOAD) |= MAX7219_LOAD_LINE;

	return;
}

void max7219SendDataBuf(uint8_t *buf, uint8_t rotate)
{
	uint8_t i, j, data;
	for (i = 0; i < 8; i++) {
		PORT(MAX7219_LOAD) &= ~MAX7219_LOAD_LINE;
		for (j = 0; j < MATRIX_NUMBER; j++) {
#if defined(MAX7219MOD)
			data = 0;
			uint8_t k;
			for (k = 0; k < 8; k++) {
				if (buf[8 * (rotate ? j : 3 - j) + k] & (1 << i))
					data |= (rotate ? 0x01 << k : 0x80 >> k);
			}
#else
			data = (rotate ? max7219SwapBits(buf[8 * j + i]) : buf[8 * (3 - j) + i]);
#endif
			max7219SendByte(rotate ? MAX7219_DIGIT_7 - i : MAX7219_DIGIT_0 + i);
			max7219SendByte(data);
		}
		PORT(MAX7219_LOAD) |= MAX7219_LOAD_LINE;
	}

	return;
}

void max7219Init(void)
{
	DDR(MAX7219_LOAD) |= MAX7219_LOAD_LINE;
	DDR(MAX7219_DIN) |= MAX7219_DIN_LINE;
	DDR(MAX7219_CLK) |= MAX7219_CLK_LINE;

	PORT(MAX7219_LOAD) |= MAX7219_LOAD_LINE;
	PORT(MAX7219_DIN) &= ~MAX7219_DIN_LINE;
	PORT(MAX7219_CLK) &= ~MAX7219_CLK_LINE;

	max7219SendCmd(MAX7219_SHUTDOWN, 1);		/* Power on */
	max7219SendCmd(MAX7219_DISP_TEST, 0);		/* Test mode off */
	max7219SendCmd(MAX7219_DEC_MODE, 0);		/* Use led matrix */
	max7219SendCmd(MAX7219_INTENSITY, 0);		/* Set brightness */
	max7219SendCmd(MAX7219_SCAN_LIMIT, 7);		/* Scan all 8 digits (cols) */

	return;
}
