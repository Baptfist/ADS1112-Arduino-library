#include <ADS1112.h>
#include <Wire.h>
 
ADS1112 ads1112;

void setup() {
  Wire.begin();
  Serial.begin(9600);
   
  //pin A0, A1 tied to GND. Address: 1001000
  ads1112.init_address(ADS1112::L, ADS1112::F);
  ads1112.selectChannel(ADS1112::CHANNEL_1, ADS1112::GAIN_1, ADS1112::MODE_UNIPOLAR, ADS1112::RESOLUTION_16BIT, ADS1112::CONVERSION_CONTINUOUS);

}

void loop() {
  Serial.println(ads1112.readADC(), 3);
  delay(100);

}
