#include <Arduino.h>
#include <FastAccelStepper.h>

FastAccelStepperEngine engine = FastAccelStepperEngine();
FastAccelStepper *stepper = NULL;

#define dirPinStepper 18
#define enablePinStepper 16
#define stepPinStepper 17

#define M0 21
#define M1 22
#define M2 23

int microstep;
volatile bool stopped = false;

bool setStep(int steps_in)
{
   microstep = steps_in;
   int steps = log10(steps_in) / log10(2);
   digitalWrite(M0, steps & 0b00000001);
   digitalWrite(M1, (steps >> 1) & 0b00000001);
   digitalWrite(M2, (steps >> 2) & 0b00000001);
   return true;
}

int angleToStep(int angle)
{
   return int(200 * microstep * (angle / 360.0));
}

void moveStepper(int angle, float speed, float acceleration, int microsteps) {
   while(stopped){}
   stepper->setSpeedInHz(speed*microsteps);
   stepper->setAcceleration(acceleration*microsteps);
   setStep(microsteps);
   stepper->moveTo(angleToStep(angle), true);
}

void IRAM_ATTR interruptStop()
{
   stepper->forceStop();
   stopped = true;
}

void IRAM_ATTR interruptAck()
{
   stopped = false;
}

void setup()
{
   pinMode(M0, OUTPUT);
   pinMode(M1, OUTPUT);
   pinMode(M2, OUTPUT);

   pinMode(15, INPUT_PULLUP);
   attachInterrupt(15, interruptStop, FALLING);
   pinMode(4, INPUT_PULLUP);
   attachInterrupt(4, interruptAck, FALLING);

   Serial.begin(115200);
   
   engine.init();
   stepper = engine.stepperConnectToPin(stepPinStepper);
   stepper->setDirectionPin(dirPinStepper);
   stepper->setEnablePin(enablePinStepper);
   stepper->setAutoEnable(true);
   
}

void loop() {
   Serial.println("movimento 1");
   moveStepper(7200, 500, 100, 4);//ang, vel, acc, mic
   Serial.println("movimento 2");
   moveStepper(-7200, 500, 200, 4);
   Serial.println("movimento 3");
   moveStepper(3600, 1000, 200, 8);
}
