#include <Stepper.h>
#include <Servo.h>

const int stepsPerRevolution = 2048;
const int motSpeed = 12;
const int dt = 1500;

class Motor {
  protected:
    int pin;
  
  public:
    Motor(int pin) : pin(pin) {}
    
    virtual void setup() = 0;
    virtual void move() = 0;
};

class StepperMotor : public Motor {
  private:
    Stepper stepper;
  
  public:
    StepperMotor(int pin1, int pin2, int pin3, int pin4) : Motor(pin1), stepper(stepsPerRevolution, pin1, pin2, pin3, pin4) {}
    
    void setup() override {
      stepper.setSpeed(motSpeed);
    }
    
    void move() override {
      stepper.step(stepsPerRevolution);
      delay(dt);
      stepper.step(-stepsPerRevolution);
      delay(dt);
    }
};

class ServoMotor : public Motor {
  private:
    Servo servo;
  
  public:
    ServoMotor(int pin) : Motor(pin), servo() {}
    
    void setup() override {
      servo.attach(pin);
    }
    
    void move() override {
      servo.write(0);
      delay(3000);

      servo.write(90);
      delay(3000);

      servo.write(180);
      delay(3000);
    }
};

StepperMotor myStepper(8, 10, 9, 11);
ServoMotor myservo(2);

void setup() {
  myStepper.setup();
  myservo.setup();
}

void loop() {
  myservo.move();
  myStepper.move();
}



