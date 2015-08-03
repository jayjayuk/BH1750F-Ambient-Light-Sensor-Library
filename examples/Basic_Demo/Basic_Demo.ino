// BASIC DEMO
// ----------
// Setup resolution, sensitivity and power save mode. Then read the ambient light level and print it
// to the serial montior
//
// The library makes use of evey feature of the sensor and this Basic_Demo makes use of all the
// functions in the library
//
// Read the BH1750F_Readme.txt and BH1750F_Function_Info.txt included in this libraries folder for
// more information on how resolution, sensitivity and power save mode work as the higher the
// resolution, the longer it will take to return.


#include <Wire.h>
#include "BH1750F.h"

BH1750F bh1750Addr1(1);

void setup()
{
  Serial.begin(115200);
  while(!Serial);
  Wire.begin();

Serial.println("Set Resolution To      = 3 (default=2)");
bh1750Addr1.setResolution(3);
Serial.print("Get Resolution         = ");
Serial.println(bh1750Addr1.getResolution());

Serial.println("Set Sensitivity To     = 254 (default=69)");
bh1750Addr1.setSensitivity(254);
Serial.print("Get Sensitivity        = ");
Serial.println(bh1750Addr1.getSensitivity());

Serial.println("Set Power Save Mode To = 1 (default=1)");
bh1750Addr1.setPowerSaveMode(1);
Serial.print("Get Power Save Mode    = ");
Serial.println(bh1750Addr1.getPowerSaveMode());


uint32_t startMillis, endMillis;
float reading;
startMillis = millis();
reading = bh1750Addr1.readAmbientLight();
endMillis = millis();
Serial.println("Resolution = 0.11lx");
Serial.print("Read Time  = ");
Serial.println(endMillis - startMillis);

Serial.println();
Serial.println("Start Reading Sensor...");
}

void loop()
{
  float reading = bh1750Addr1.readAmbientLight();
  Serial.print("Lux = ");
  Serial.println(reading);
}






