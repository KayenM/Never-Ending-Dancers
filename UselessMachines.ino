include <AccelStepper.h>

// Stepper Motor Variables and Setup
#define HALFSTEP 4                                                            // Defines the type of motor as a 4 wire motor
#define motorPin1  9                                                          // IN1 on the ULN2003 driver 1
#define motorPin2  10                                                         // IN2 on the ULN2003 driver 1
#define motorPin3  11                                                         // IN3 on the ULN2003 driver 1
#define motorPin4  12    
  
const int wire1 = 2;
const int wire2 =  3;

const int input1 = 7;
const int input2 = 8;

// IN4 on the ULN2003 driver 1
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);  // Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48 Motor

// Setup Loop
void setup() {                                                                // Start Setup Loop
// Set motor's maximum speed and acceleration
  stepper1.setMaxSpeed(2000);                                               // Set the maximum speed of the motor
  stepper1.setAcceleration(300000.0);                                         // Set the maximum acceleration of the motor

  pinMode(wire1, INPUT_PULLUP);
  pinMode(wire2, INPUT_PULLUP);

  pinMode(input1, INPUT);
  pinMode(input2, INPUT);

  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
 
// Setup the Arudino's on board LED pin so it can be used to indicate when 
// the system is ready to process a signal
  pinMode(LED_BUILTIN, OUTPUT);                                               // Set the pin connected to the arduino's on board LED to an output so it can turn that LED on or off. The Pin is Digital Pin #13

  stepper1.disableOutputs();                                                  // Shut off all power to the motor to extend battery life

  pinMode(2, INPUT_PULLUP);   
  Serial.begin(9600);
  // Set the Switch Pin as an input pin that is normally pulled high

}                                                                             // End Setup Loop

void spin_function()
{
  stepper1.disableOutputs();                                                  // Shut off all power to the motor
    stepper1.enableOutputs();                                                 //   Enable the motor controller's outputs
    for (int k = 0; k < 4250; k++) {                                           //   Start For loop: Move the motor counterclockwise one step at a time
      stepper1.move(-1);                                                      //     Set desired position relating to current position -1 = one step counterclockwise from current location
      stepper1.run();                                                         //     Move motor one step towards desired location
      delay (1);                                                              //     Delay 1ms to give the motor time to complete the move
    }                                                                         //   End For loop: Move the hand counterclockwise one step at a time
    //digitalWrite(13,LOW);                                                     //   Turn off on-board LED to indicate that the hand has stopped moving
    stepper1.disableOutputs();                                                //   Shut off all power to the motor 
   delay(1000);
  // }
}

void loop() {                                                                 // Start Main Loop

  if ((digitalRead(wire1) == HIGH) && (digitalRead(wire2) == HIGH)){
    Serial.println("ARMED");
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);

    //spin_function();

    if ((digitalRead(input1) == LOW) && (digitalRead(input2) == HIGH)){
      Serial.println("SPINNING BOTH");
      spin_function();
    }
  }

  else if ((digitalRead(wire1) == HIGH) && (digitalRead(wire2) == LOW)){
    Serial.println("OFF");
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW); 
  }

  else if ((digitalRead(wire1) == LOW) && (digitalRead(wire2) == HIGH)){
    Serial.println("ON");
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);

    spin_function();
  }
  else {
    Serial.println("ERROR");
  }                                                              
}                                                                             // End Main Loop
