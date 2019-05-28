#include "ADS1112.h"
#include <Wire.h>

/*
 * ADS1112 Library
 * inspired from Kerry D. Wong http://www.kerrywong.com
 * modified by Baptiste PAULMIER
 * 2019
 */

void ADS1112::init_address(byte A0, byte A1)
{
	if (A0 == L && A1 == L) I2C_ADDRESS = B1001000;
	else if (A0 == L && A1 == F) I2C_ADDRESS = B1001001;
	else if (A0 == L && A1 == H) I2C_ADDRESS = B1001010;
	else if (A0 == H && A1 == L) I2C_ADDRESS = B1001100;
	else if (A0 == H && A1 == F) I2C_ADDRESS = B1001101;
	else if (A0 == H && A1 == H) I2C_ADDRESS = B1001110;
	else if (A0 == F && A1 == L) I2C_ADDRESS = B1001011;
	else if (A0 == F && A1 == H) I2C_ADDRESS = B1001111;
}

void ADS1112::selectChannel(byte channel, byte gain, byte mode, byte resolution, byte convertion)
{
    /*
		INP controls which two of the four analog inputs are used
		to measure data in the ADC.
		
		INP1   INP0   V IN+   V IN−
		0      0      AIN0    AIN1
		0      1      AIN2    AIN3
		1      0      AIN0    AIN3
		1      1      AIN1    AIN3
	
	*/
	
	byte INP1 = 0, INP0 = 0; //default setting

    if (mode == MODE_UNIPOLAR) {
		if (channel == CHANNEL_0) {
			INP1 = 1;
			INP0 = 0;
		} else if (channel == CHANNEL_1) {
			INP1 = 1;
			INP0 = 1;
		} else if (channel == CHANNEL_2) {
			INP1 = 0;
			INP0 = 1;
		}				
    } else { //bipolar
		if (channel == CHANNEL_0) {
			INP1 = 0;
			INP0 = 0;
		} else if (channel == CHANNEL_1) {
			INP1 = 0;
			INP0 = 1;
		}		
	}
	
	/*
		Bits DR1 and DR2 control the ADS1112 data rate and resolution
		
		DR1   DR0   DATA RATE   RESOLUTION
        0     0     240SPS      12 Bits
        0     1     60SPS       14 Bits
        1     0     30SPS       15 Bits
        1     1     15SPS       16 Bits
	
	*/
	
	/*
	byte BR1 = 1, BR2 = 1; //Default setting
	
	if (resolution == RESOLUTION_12BIT) {
		BR1 = 0;
		BR0 = 0;
	}else if(resolution == RESOLUTION_14BIT){
		BR1 = 0;
		BR0 = 1;
	}else if (resolution == RESOLUTION_15BIT){
		BR1 = 1;
		BR0 = 0;
	}else if (resolution == RESOLUTION_16BIT){
		BR1 = 1;
		BR0 = 1;
	}
	*/
	
	/*
		Bits PGA1 and PGA0 control the ADS1112 ADS1112 gain setting
		
		PGA1    PGA0    GAIN
        0       0       1
        0       1       2
        1       0       4
        1       1       8
	
	*/

    //configuration register
	byte reg = 1 << BIT_ST_DRDY |
			INP1 << BIT_INP1 |
			INP0 << BIT_INP0 |
			resolution << BIT_DR0 |
			gain;
	
	
	
	Wire.beginTransmission(I2C_ADDRESS);
	Wire.write(reg);
	Wire.endTransmission();			   
}

double ADS1112::readADC()
{
  	Wire.requestFrom(I2C_ADDRESS, (byte) 3);
  	
	int h = Wire.read();
  	int l = Wire.read();
  	int r = Wire.read();
	
	Serial.print("H :");Serial.println(h, BIN);
	Serial.print("L :");Serial.println(l, BIN);
	Serial.print("R :");Serial.println(r, BIN);
  
  	long t = h << 8 |  l;
  	
	if (t >= 32768) t -= 65536l;
  	
	double v = (double) t * 2.048/32768.0;

	return v;
}
