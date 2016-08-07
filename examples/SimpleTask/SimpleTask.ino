/* Demonstrates a simple task with ALib0.
 * 
 * Connect a red, green and orange LED from the pins given below to Gnd,
 * each with a resistor of about 270 Ohm.
 */
 
#include <ALib0.h>

//traffic light pins
const int Red=5, Orange=6, Green=7;
#define ON true //assume LED to Gnd
#define OFF !ON

void setup() {
  Serial.begin(9600);
  pinMode(Red, OUTPUT);
  pinMode(Orange, OUTPUT);
  pinMode(Green, OUTPUT);
  digitalWrite(Red, ON);
  digitalWrite(Orange, OFF);
  digitalWrite(Green, OFF);
}

void loop() {
  taskBegin();
  //initial state: red
  digitalWrite(Red, ON); 
  Serial.println("Stop!");
  taskDelay(1000);
  //red-orange
  digitalWrite(Orange, ON);
  taskDelay(500);
  digitalWrite(Red, OFF);
  digitalWrite(Orange, OFF);
  //green
  digitalWrite(Green, ON);
  Serial.println("Go");
  taskDelay(2000);
  digitalWrite(Green, OFF);
  //orange
  digitalWrite(Orange, ON);
  taskDelay(500);
  digitalWrite(Orange, OFF);
  taskEnd(); //back to red
}
