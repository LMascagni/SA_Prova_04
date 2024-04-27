#include <Arduino.h>
#include "StepperMotor.h"

#define M0 21
#define M1 22
#define M2 23

StepperMotor myStepper(17, 18, 16); // Assuming step, dir, enable pin assignments

void setup() {
    Serial.begin(115200);
    myStepper.setMicrostep(4);  // Set microsteps in your sketch
}

void loop() {
    myStepper.moveStepper(1800, 500, 100);
    myStepper.moveStepper(-1800, 500, 200);
    myStepper.moveStepper(0, 1000, 200);
    // ... add more loop commands if needed
}
