#include <DHT.h>
#include <DHT_U.h>
#include "DHT.h"

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_TSL2591.h"

#include <Event.h>
#include <Timer.h>
Timer timer;

#define DHTPIN 2
#define DHTTYPE DHT22

Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591);
DHT dht(DHTPIN, DHTTYPE);


void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
    dht.begin();

    configure_Light_Sensor();
    
   timer.every(20000, auto_send_sensor);

}

void loop() {
  // put your main code here, to run repeatedly:
  timer.update();
}

void auto_send_sensor(){
 // Serial.println("Update");
     float tempF = dht.readTemperature(true); //true=Fahrenheit
   //Serial.print("Temp= ");
   //Serial.println(tempF);
 //Humidity
   float hum = dht.readHumidity();
   Serial.print("Humidity= ");
   Serial.println(hum);

    uint32_t lum = tsl.getFullLuminosity(); //Read Luminosity
   uint16_t ir, full, visible, lux;
   
   //Convert lum
   ir = lum >> 16;
   full = lum & 0xFFFF;
   visible = full-ir;
   lux = tsl.calculateLux(full, ir);

   //Serial.print("Lux= ");
   //Serial.println(lux);
  }

  void configure_Light_Sensor()
{
  /*Set gain of the sesnor
   *LOW = 1x gain (bright light)
   *MED = 25x gain (Normal Light) Suggested in manual 
   *HIGH = 428x gain (Very very low light conditions) Pretty much a dark room
   */
   tsl.setGain(TSL2591_GAIN_MED); //(Normal light)
   
   /*Set integration time
    *Lower the time the best for dim light
    *Higher the number the best for High light
    */
    tsl.setTiming(TSL2591_INTEGRATIONTIME_100MS); //Picked suggested lowest time option
  
}//End of configure_Light_Sensor()


