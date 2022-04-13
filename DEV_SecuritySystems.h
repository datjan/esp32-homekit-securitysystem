
//////////////////////////
//   DEVICE-SPECIFIC    //
//////////////////////////

struct DEV_SecuritySystem : Service::SecuritySystem {     // A Security System

  SpanCharacteristic *current;            // reference to the SecuritySystemCurrentState Characteristic (specific to SecuritySystem)
  SpanCharacteristic *target;             // reference to the SecuritySystemTargetState Characteristic (specific to SecuritySystem)  

  DEV_SecuritySystem() : Service::SecuritySystem(){       // constructor() method
        
    current=new Characteristic::SecuritySystemCurrentState(1);              // initial value of 3 means disarmed
    target=new Characteristic::SecuritySystemTargetState(1);                // initial value of 3 means disarmed
    
    Serial.print("Configuring Security Sensor");   // initialization message
    Serial.print("\n");

  } // end constructor

  boolean update(){                              // update() method

    // see HAP Documentation for details on what each value represents
    
     // Security Status
    uint8_t securitystate = 3; // Default: 3 Disarm (Stay=0 / Away=1 / Night=2 / Disarmed=3 / Triggered=4)

    // Pins
    int pinStatusAway = 16;
    int pinStatusTriggered = 17;
    int pinStatusNight = 18;
    int pinStatusStay = 19;

    // Get state
    if (digitalRead(pinStatusTriggered) == HIGH) { securitystate = 4; LOG1("State: Triggered"); } // Triggered - Ausgeloest
    else if (digitalRead(pinStatusAway) == HIGH) { securitystate = 1; LOG1("State: Away"); } // Away - Abwesend
    else if (digitalRead(pinStatusNight) == HIGH) { securitystate = 2; LOG1("State: Night"); } // Night - Nacht
    else if (digitalRead(pinStatusStay) == HIGH) { securitystate = 0; LOG1("State: Stay"); } // Stay - Zuhause
    else { securitystate = 3; } // Disarmed - Aus

    // Change state
    if (securitystate == 4) { current->setVal(securitystate); LOG1("State triggered"); }  // If state triggered
    else { target->setVal(securitystate); delay(200); current->setVal(securitystate); LOG1("State normal"); }   // If state normal
       
    
    return(true);                               // return true
  
  } // update

  void loop(){                                     // loop() method

    // Security Status
    uint8_t securitystate = 3; // Default: 3 Disarm (Stay=0 / Away=1 / Night=2 / Disarmed=3 / Triggered=4)

    // Pins
    int pinStatusAway = 16;
    int pinStatusTriggered = 17;
    int pinStatusNight = 18;
    int pinStatusStay = 19;

    // Get state
    if (digitalRead(pinStatusTriggered) == HIGH) { securitystate = 4; LOG1("State: Triggered"); } // Triggered - Ausgeloest
    else if (digitalRead(pinStatusAway) == HIGH) { securitystate = 1; LOG1("State: Away"); } // Away - Abwesend
    else if (digitalRead(pinStatusNight) == HIGH) { securitystate = 2; LOG1("State: Night"); } // Night - Nacht
    else if (digitalRead(pinStatusStay) == HIGH) { securitystate = 0; LOG1("State: Stay"); } // Stay - Zuhause
    else { securitystate = 3; } // Disarmed - Aus

    // Exit in case of no state changes
    if(current->getVal()==securitystate) { return; }        // if current-state matches target-state there is nothing do -- exit loop()

    // Change state
    if (securitystate == 4) { current->setVal(securitystate); LOG1("State triggered"); }  // If state triggered
    else { target->setVal(securitystate); delay(200); current->setVal(securitystate); LOG1("State normal"); }   // If state normal
       
  } // loop
  
};
