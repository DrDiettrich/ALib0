/* Simple debounced button object
 * by DoDi under MIT License
 */
#ifndef ALIB0_H
#define ALIB0_H

 #include <arduino.h>

 #define DEBOUNCE 20 //debounce interval in ms

 typedef enum {Stable, Changing, Changed} ButtonState;

 class AButton {
 public:
   AButton(byte buttonPin);
   bool is(bool hilo);
   bool changed();
   bool changedTo(bool hilo);
 private:
  byte pin;
  unsigned long lastChange;
 public: //for experts
  ButtonState state;
  bool pressed;
  ButtonState check();
};
#endif
