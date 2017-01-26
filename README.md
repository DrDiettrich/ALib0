# ALib0
Arduino library for button handling and parallel execution.
It provides slick solutions for 90% of typical tasks in Arduino beginner sketches, possibly more in expert code.

Button handling includes debounce and state change detection.
Create one instance of AButton for every button (digital input), and check it for
- is(hilo) True if debounced button state matches hilo (HIGH or LOW)
- changed() True if button state changed
- changedTo(hilo) True if button changed to hilo (HIGH or LOW)

True parallel execution is impossible on an 8 bit Arduino, of course,
but these task macros allow to write cooperative tasks easily.
They add structure and readability to the "several things at the same time" pattern. Every task looks like this:

- taskBegin(); //execute following code without blocking other tasks
-   taskWaitFor(condition); //wait until condition becomes true
  - ... //do whatsoever
-   taskDelay(millis); //cooperative replacement for delay()
-   taskRestart(); //resume at taskBegin(), for conditional use: if(condition) taskRestart();
- taskEnd(); //repeat from taskBegin()

Note: A task function has to be called in every iteration of loop().
That's why local variables lose their values, use static variables instead.

If a task or something else should execute at regular time intervals, use
- every(ms) doThis; //ms is time interval in milliseconds

This macro implements the usual if(millis()-lastMillis >= ms) and hides the lastMillis variable and update.
