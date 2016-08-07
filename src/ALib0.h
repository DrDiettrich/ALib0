/* Simple debounced button object and task macros
 * by DoDi under MIT License
 */
#ifndef ALIB0_H
#define ALIB0_H

 #include <arduino.h>

//task macros, from Combie
 #define taskBegin() static int _mark = 0; static unsigned long __attribute__((unused)) time_Stamp = 0; switch(_mark){ case 0:
 //#define taskSwitch() do { _mark = __LINE__; return ; case __LINE__: ; } while (0) //okay
 #define taskSwitch() { _mark = __LINE__; return; case __LINE__: ; }
 //#define taskPause(interval) time_Stamp = millis(); while((millis() - time_Stamp) < (interval)) taskSwitch();
 //#define taskDelay(interval) time_Stamp = millis(); while((millis() - time_Stamp) < (interval)) taskSwitch();
 #define taskDelay(interval) time_Stamp = millis(); taskSwitch(); while((millis() - time_Stamp) < (interval)) return;
 //#define taskWaitFor(condition) while(!(condition)) taskSwitch(); //okay
 #define taskWaitFor(condition) taskSwitch(); if (!(condition)) return;
 //#define taskEnd() taskSwitch(); }
 #define taskEnd() _mark=0; }

//button class
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
