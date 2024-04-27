#include "StepperMotor.h"

StepperMotor::StepperMotor(int stepPin, int dirPin, int enablePin) :
    stepPin(stepPin), dirPin(dirPin), enablePin(enablePin) {
    engine.init();
    stepper = engine.stepperConnectToPin(stepPin);
}

void StepperMotor::setMicrostep(int microsteps) {
    this->microstep = microsteps;
}

int StepperMotor::angleToStep(int angle) {
    return int(200 * microstep * (angle / 360.0));
}

void StepperMotor::moveStepper(int angle, float speed, float acceleration) {
    configurePins();  // Ensure pins are set correctly
    configureStepper();  // Set direction, enable (if provided), speed, and acceleration

    stepper->moveTo(angleToStep(angle), true);  // Move and block until complete
}

void StepperMotor::configurePins() {
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    if (enablePin >= 0) {
        pinMode(enablePin, OUTPUT);
    }
}

void StepperMotor::configureStepper() {
    stepper->setDirectionPin(dirPin);
    if (enablePin >= 0) {
        stepper->setEnablePin(enablePin);
        stepper->setAutoEnable(true);
    }
    stepper->setSpeedInHz(speed);
    stepper->setAcceleration(acceleration);
}
