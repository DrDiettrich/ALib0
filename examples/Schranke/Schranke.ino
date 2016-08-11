/* Schranke mit Andreaskreuz langsam öffnen und schließen.
 * Servo Ansteuerung nach Bedarf einbauen.
 */

#include <ALib0.h>

//LED
const int ledPin = 13;
const millis_t interval = 700;
bool blinken = false; //Aktivierung per Code

//Schranke
const millis_t ServoInterval = 20; //typischer Abstand zwischen Impulsen
const millis_t SchrankeInterval = 2*ServoInterval;
const int PosZu = 110;
const int SchrankeStep = 1; //Dauer = PosZu*SchrankeStep*SchrankeInterval = 4400ms
int SchrankePos = 0; //aktuelle Position, 0=offen, PosZu=geschlossen
bool SchrankeZu = false; //Status
bool SchrankeSchliessen = false; //Aktivierung per Code

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  SchrankeSchliessen=true; //gleich anfangen
}

void AndreasKreuz() {
  taskBegin();
  taskWaitFor(blinken);
  Serial.println("blink!");
  digitalWrite(ledPin, HIGH); //ein
  taskDelay(interval);
  digitalWrite(ledPin, LOW); //aus
  taskDelay(interval);
  //LED bleibt aus wenn blinken=false wird
  taskEnd();  
}
void Schranke() {
  taskBegin();
  taskWaitFor(SchrankeSchliessen != SchrankeZu);
  if (SchrankeSchliessen) {
    //blinken vor Schließen
    blinken = true;
    taskDelay(6*interval); //3*blinken
    //Schranke schließen
    while (SchrankePos < PosZu) {
      SchrankePos += SchrankeStep;
      //Servo.write(SchrankePos);
      Serial.println(SchrankePos);
      taskDelay(SchrankeInterval);
    }
  } else { //öffnen
    while (SchrankePos > 0) {
      SchrankePos -= SchrankeStep;
      //Servo.write(SchrankePos);
      Serial.println(SchrankePos);
      taskDelay(SchrankeInterval);
    }
    blinken = false;
  }
  SchrankeZu = SchrankePos >= PosZu;
  taskEnd();
}

void loop() {
  AndreasKreuz();
  Schranke();
  every(20000) SchrankeSchliessen = !SchrankeSchliessen;
}

