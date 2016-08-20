#include "ALib0.h"

AButton button(4);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Button Change Test");
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (button.changedTo(HIGH)) {
    digitalWrite(13, !digitalRead(13));
    Serial.println("changed");
  }
}
