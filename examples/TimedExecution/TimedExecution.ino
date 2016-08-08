/* Logging at fixed time intervals.
 *  
 * See how taskDelay() cannot compensate the time shift caused by lengthy computations or blocking I/O
 */
 
#include <ALib0.h>

//#define CALC
#define CALC delay(1) //simulate lengthy calculations

void setup() {
  Serial.begin(9600);
}

void logEvery(millis_t ms) {
  taskBegin();
  Serial.print(millis());
  CALC; //simulate computations
  Serial.println(" - regular log");
  taskDelay(ms); //time spent in logging will increase this interval!
  taskEnd();
}

void timedLog() {
  Serial.print(millis());
  CALC; //simulate computations
  Serial.println(" - timed log");
}

void conditionalLog(bool &on) {
  taskBegin();
  taskWaitFor(on);
  Serial.print(millis());
  CALC; //simulate computations
  Serial.println(" - conditional");
  on = false; //done, don't repeat
  taskEnd();
}

 void loop() {
  static bool logFlag = false;
  logEvery(3000);
  every(4000) logFlag = true;
  conditionalLog(logFlag);
  every(10000) timedLog();
}
