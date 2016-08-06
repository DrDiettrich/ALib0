#ifndef __TASKMACRO__H__
#define __TASKMACRO__H__

#define taskBegin() static int mark = 0; static unsigned long __attribute__((unused)) timeStamp = 0; switch(mark){ case 0:
//#define taskSwitch() do { mark = __LINE__; return ; case __LINE__: ; } while (0)
#define taskSwitch() mark = __LINE__; case __LINE__: ;
//#define taskPause(interval) timeStamp = millis(); while((millis() - timeStamp) < (interval)) taskSwitch();
#define taskDelay(interval) timeStamp = millis(); taskSwitch(); if((millis() - timeStamp) < (interval)) return;
//#define taskWaitFor(condition) while(!(condition)) taskSwitch();
#define taskWaitFor(condition) taskSwitch(); if (!(condition)) return;
//#define taskEnd() taskSwitch(); }
#define taskEnd() mark=0; }

#endif
