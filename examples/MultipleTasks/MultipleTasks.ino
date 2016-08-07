/* Demonstrates concurrent tasks with ALib0.
 * 
 * Optional: Connect a red, green and orange LED from the pins given below to Gnd,
 * each with a resistor of about 270 Ohm.
 * 
 * Watch in Serial Monitor how cars break on red light, or pass by otherwise.
 */
 
#include <ALib0.h>

//traffic light pins
const int Red=5, Orange=6, Green=7;
#define ON true //assume LED to Gnd
#define OFF !ON
bool GreenLight = false;

void setup() {
  Serial.begin(9600);
  pinMode(Red, OUTPUT);
  pinMode(Orange, OUTPUT);
  pinMode(Green, OUTPUT);
  digitalWrite(Red, ON);
  digitalWrite(Orange, OFF);
  digitalWrite(Green, OFF);
}

void trafficLight() {
  taskBegin();
  //initial state: red
  digitalWrite(Red, ON); 
  GreenLight = false;
  Serial.println("Stop!");
  taskDelay(2000);
  //red-orange
  digitalWrite(Orange, ON);
  taskDelay(500);
  digitalWrite(Red, OFF);
  digitalWrite(Orange, OFF);
  //green
  digitalWrite(Green, ON);
  Serial.println("Go");
  GreenLight = true;
  taskDelay(4000);
  digitalWrite(Green, OFF);
  //orange
  digitalWrite(Orange, ON);
  taskDelay(500);
  digitalWrite(Orange, OFF);
  taskEnd(); //back to red
}

void cars() {
//Variables must be static, to preserve their values across invocations.
  static unsigned long wait;
  
  taskBegin();
  wait = random(500, 1200);
  Serial.print("wait "); Serial.print(wait); Serial.print(' ');
  //taskSwitch();
  taskDelay(wait);
  if (!GreenLight)
  {
    Serial.println("queeeek");
    taskWaitFor(GreenLight);
  }
  Serial.println("wrooommm");
  taskEnd();
}

void loop() {
  trafficLight();
  cars();
}

