#ifndef ADS1112_H
#define ADS1112_H

#include <Arduino.h>

/*
 * ADS1112 Library
 * Inspired from Kerry D. Wong http://www.kerrywong.com
 * Modified by Baptiste PAULMIER
 * 2019
 */

class ADS1112 {
public:
	static const byte L = 0;
	static const byte H = 1;
	static const byte F = 2;

	static const byte MODE_UNIPOLAR = 0;
	static const byte MODE_BIPOLAR = 1;
	
	static const byte CONVERSION_CONTINUOUS = 0;
	static const byte CONVERSION_SINGLE = 1;

	static const byte CHANNEL_0 = 0;
	static const byte CHANNEL_1 = 1;
	static const byte CHANNEL_2 = 2;

	static const byte GAIN_1 = 0;
	static const byte GAIN_2 = 1;
	static const byte GAIN_4 = 2;
	static const byte GAIN_8 = 3; 
	
	static const byte RESOLUTION_12BIT = 0;
	static const byte RESOLUTION_14BIT = 1;
	static const byte RESOLUTION_15BIT = 2;
	static const byte RESOLUTION_16BIT = 3;
	
	

	byte init_address(byte A0, byte A1);
	void writeADC(byte channel, byte gain = GAIN_1, byte mode = MODE_UNIPOLAR, byte resolution = RESOLUTION_16BIT, byte conversion = CONVERSION_CONTINUOUS);
	double readADC();
private:
	//communication register
	static const byte BIT_ST_DRDY = 7; //data ready
	static const byte BIT_INP1 = 6; //input channel select
	static const byte BIT_INP0 = 5; //input channel select
	static const byte BIT_SC = 4; //conversion mode (single/continuous)
	static const byte BIT_DR1 = 3; //data rate
	static const byte BIT_DR0 = 2; //data rate
	static const byte BIT_PGA1 = 1; //gain
	static const byte BIT_PGA0 = 0; //gain

	const double VRef = 2.048;
	byte I2C_ADDRESS;
};
#endif
