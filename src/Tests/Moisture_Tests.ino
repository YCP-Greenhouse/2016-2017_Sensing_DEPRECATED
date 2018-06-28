#include <Event.h>
#include <Timer.h>
Timer timer;

#define DHTPIN 2
int MOISTUREPIN = A0;



void setup() {
  // put your setup code here, to run once:

 Serial.begin(9600);

  timer.every(20000, auto_send_sensor);

}

void loop() {
   timer.update();
}

 
void auto_send_sensor(){
 // put your main code here, to run repeatedly:
 float calibrationValue = 240; //Not going to be 1024!
   int moistureRead = analogRead(MOISTUREPIN);
   //moisture percentage
   float moistureValue = (moistureRead/calibrationValue) *100;
   Serial.println("Moisture Value:");
   Serial.println(moistureValue);
}
