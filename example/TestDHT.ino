// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain
// Modified by ADiea for libDHT
//Status: UNTESTED on hardware

#include "DHT.h"

#define DHTPIN 2     // what pin the sensor is connected to

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor. 

// Initialize DHT sensor.
DHT dht(DHTPIN);

TempAndHumidity th;

ComfortState cf;

void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");

  dht.begin();
  
  Serial.println("---Begin CSV data---");
  Serial.println("Humidity,Temperature(C),HeatIndex(C),DewPoint(C),ComfortRatio(%%),ComfortText");
  
}

void loop() 
{
  // Wait a few seconds between measurements.
  delay(2000);

  if(!dht.readTempAndHumidity(th))
  {
    Serial.print("Failed to read from DHT sensor for reason: ");
	switch(dht.getLastError())
	{
	  case errDHT_Timeout:
	     Serial.print("TIMEOUT (no sensor?) \n");
	  break;
	  case errDHT_Checksum:
	     Serial.print("CHECKSUM (are cables secured?) \n");
	  break;
	  case errDHT_Other:
	     Serial.print("UNKNOWN \n");
	  break;
	};
	return;
  }

  // Compute heat index in Celsius (the default)
  float hic = dht.getHeatIndex();
  
  // Compute dew point in Celsius (the default) using the ACCURATE algorithm
  double dp = dht.getDewPoint(DEW_ACCURATE);
  
  //Compute comfort ratio in percents
  float cr = dht.getComfortRatio(cf);

  //Print line comma separrated values
  Serial.print(th.humid);
  Serial.print(",");
  Serial.print(th.temp);
  Serial.print(",");
  Serial.print(hic);
  Serial.print(",");
  Serial.print(dp);
  Serial.print(",");
  Serial.print(cr); 
  Serial.print(",");

  switch(cf)
  {
  case Comfort_OK:
	Serial.print("Comfort_OK");
	break;
  case Comfort_TooHot:
	Serial.print("Comfort_TooHot");
	break;
  case Comfort_TooCold:
	Serial.print("Comfort_TooCold");
	break;
  case Comfort_TooDry:
	Serial.print("Comfort_TooDry");
	break;
  case Comfort_TooHumid:
	Serial.print("Comfort_TooHumid");
	break;
  case Comfort_HotAndHumid:
	Serial.print("Comfort_HotAndHumid");
	break;
  case Comfort_HotAndDry:
	Serial.print("Comfort_HotAndDry");
	break;
  case Comfort_ColdAndHumid:
	Serial.print("Comfort_ColdAndHumid");
	break;
  case Comfort_ColdAndDry:
	Serial.print("Comfort_ColdAndDry");
	break;
  default:
	Serial.print("Unknown:");
	Serial.print((int)cf);
	break;
  };
 
  Serial.print("\n");
}
