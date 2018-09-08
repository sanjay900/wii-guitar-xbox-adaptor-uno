#ifndef UNOJOY_H
#define UNOJOY_H
    #include <stdint.h>
    #include <util/atomic.h>
    #include <Arduino.h>
    #include "WiiExtension.h"
    
    // Call setupUnoJoy in the setup block of your program.
    //  It sets up the hardware UnoJoy needs to work properly
    void setupUnoJoy(void);
    
    // This sets the controller to reflect the button and
    // joystick positions you input (as a dataForController_t).
    // The controller will just send a zeroed (joysticks centered)
    // signal until you tell it otherwise with this function.
    void setControllerData(WiiController);
    
    // This function gives you a quick way to get a fresh
    //  dataForController_t with:
    //    No buttons pressed
    //    Joysticks centered
    // Very useful for starting each loop with a blank controller, for instance.
    // It returns a dataForController_t, so you want to call it like:
    //    myControllerData = getBlankDataForController();
    WiiController getBlankDataForController(void);
    
    // You can also call the setup function with an integer argument
    //  declaring how often, in  milliseconds, the buffer should send its data 
    //  via the serial port.  Use it if you need to do a lot of processing and
    //  the serial stuff is messing you up, but it'll make your controller
    //  more laggy.
    // IMPORTANT - you can't make this value greater than 20 or so - the code
    //  on the communications chip times out on each serial read after 25ms.
    //  If you need more time than 20ms, you'll have to alter the code for the
    //  ATmega8u2 as well
    void setupUnoJoy(int);
    
    
//----- End of the interface code you should be using -----//
//----- Below here is the actual implementation of
    
  // This dataForController_t is used to store
  //  the controller data that you want to send
  //  out to the controller.  You shouldn't mess
  //  with this directly - call setControllerData instead
  WiiController controllerDataBuffer;

  // This updates the data that the controller is sending out.
  //  The system actually works as following:
  //  The UnoJoy firmware on the ATmega8u2 regularly polls the
  //  Arduino chip for individual bytes of a dataForController_t.
  //  
  void setControllerData(WiiController controllerData){
    // Probably unecessary, but this guarantees that the data
    //  gets copied to our buffer all at once.
    ATOMIC_BLOCK(ATOMIC_FORCEON){
      controllerDataBuffer = controllerData;
    }
  }
  
  // serialCheckInterval governs how many ms between
  //  checks to the serial port for data.
  //  It shouldn't go above 20 or so, otherwise you might
  //  get unreliable data transmission to the UnoJoy firmware,
  //  since after it sends a request, it waits 25 ms for a response.
  //  If you really need to make it bigger than that, you'll have to
  //  adjust that timeout in the UnoJoy ATmega8u2 firmware code as well.
  volatile int serialCheckInterval = 1;
  // This is an internal counter variable to count ms between
  //  serial check times
  int serialCheckCounter = 0;
  
  // This is the setup function - it sets up the serial communication
  //  and the timer interrupt for actually sending the data back and forth.
  void setupUnoJoy(void){
    // First, let's zero out our controller data buffer (center the sticks)
    controllerDataBuffer = getBlankDataForController();
  
    // Start the serial port at the specific, low-error rate UnoJoy uses.
    //  If you want to change the rate, you'll have to change it in the
    //  firmware for the ATmega8u2 as well.  250,000 is actually the best rate,
    //  but it's not supported on Macs, breaking the processing debugger.
    Serial.begin(38400);
    
    // Now set up the Timer 0 compare register A
    //  so that Timer0 (used for millis() and such)
    //  also fires an interrupt when it's equal to
    //  128, not just on overflow.
    // This will fire our timer interrupt almost
    //  every 1 ms (1024 us to be exact).
    OCR0A = 128;
    TIMSK0 |= (1 << OCIE0A);
  }
  
  // If you really need to change the serial polling
  //  interval, use this function to initialize UnoJoy.
  //  interval is the polling frequency, in ms.
  void setupUnoJoy(int interval){
    serialCheckInterval = interval;
    setupUnoJoy();
  }
  
  // This interrupt gets called approximately once per ms.
  //  It counts how many ms between serial port polls,
  //  and if it's been long enough, polls the serial
  //  port to see if the UnoJoy firmware requested data.
  //  If it did, it transmits the appropriate data back.
  ISR(TIMER0_COMPA_vect){
    serialCheckCounter++;
    if (serialCheckCounter >= serialCheckInterval){
      serialCheckCounter = 0;
      // If there is incoming data stored in the Arduino serial buffer
      while (Serial.available() > 0) {
        //pinMode(13, OUTPUT);
        //digitalWrite(13, HIGH);
        // Get incoming byte from the ATmega8u2
        byte inByte = Serial.read();
        // That number tells us which byte of the dataForController_t struct
        //  to send out.
        Serial.write(((uint8_t*)&controllerDataBuffer)[inByte]);
        //digitalWrite(13, LOW);
      }
    }
  }
  
  // Returns a zeroed out (joysticks centered) 
  //  dataForController_t variable
  WiiController getBlankDataForController(void){
    // Create a dataForController_t
    WiiController controllerData;
    // And return the data!
    return controllerData;
  }

#endif
