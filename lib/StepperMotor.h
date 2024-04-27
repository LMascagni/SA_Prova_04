#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

#include <FastAccelStepper.h>

class StepperMotor {
public:
    // Public constructor for flexibility
    StepperMotor(int stepPin, int dirPin, int enablePin = -1);

    // Public methods for control
    void setMicrostep(int microsteps);
    int angleToStep(int angle);
    void moveStepper(int angle, float speed, float acceleration);

private:
    FastAccelStepperEngine engine;
    FastAccelStepper *stepper;
    int microstep;
    int stepPin, dirPin, enablePin;

    // Private helper functions (optional for better organization)
    void configurePins();
    void configureStepper();
};

#endif
