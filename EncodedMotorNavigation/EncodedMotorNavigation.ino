// Motor1 control pins
const int motorPin1 = 3; // IN1 on L293D
const int motorPin2 = 4; // IN2 on L293D
const int enablePin1 = 5; // EN1 on L293D
// Motor2 control pins
const int motorPin3 = 10; // IN3 on L293D
const int motorPin4 = 11; // IN4 on L293D
const int enablePin2 = 9; // EN2 on L293D

// Encoder pins
const int motor1_encoderA = 6;
const int motor1_encoderB = 2;
const int motor2_encoderA = 8;
const int motor2_encoderB = 12;

// Encoder counts
volatile long motor1_position = 0;
volatile long motor2_position = 0;

// For counting time increments
enum {stop, moveForward, moveRight, moveLeft, moveBackward};
unsigned char roboState;

void setup() {
  // Set motor1 control pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin1, OUTPUT);
  
  // Set motor2 control pins as outputs
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(enablePin2, OUTPUT);
  
  // Encoder pins as inputs
  pinMode(motor1_encoderA, INPUT);
  pinMode(motor1_encoderB, INPUT);
  pinMode(motor2_encoderA, INPUT);
  pinMode(motor2_encoderB, INPUT);

  // Attach interrupts for encoders
  attachInterrupt(digitalPinToInterrupt(motor1_encoderA), updateMotorA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(motor2_encoderA), updateMotorB, CHANGE);

  // Ensure motor1 is off at the start
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  //digitalWrite(enablePin1, HIGH); // Enable the motor driver

  // Ensure motor2 is off at the start
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  //digitalWrite(enablePin2, HIGH); // Enable the motor driver
  
  // Start Serial communication for debugging
  Serial.begin(9600);
  
  roboState = moveForward;
}

void loop() {
    // Example: Move both motors forward at full speed
  analogWrite(enablePin1, 255); // Full speed
  analogWrite(enablePin2, 255); // Full speed
  switch(roboState){
    case stop:   
    	Serial.println("Motor Stopping");
    	digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, LOW);
    	
    	digitalWrite(motorPin3, LOW);
        digitalWrite(motorPin4, LOW);
    	
    	break;
    
    case moveForward:
    	Serial.println("Motor Moving Forward");
    	// Rotate motor1 forward
        digitalWrite(motorPin1, HIGH);
        digitalWrite(motorPin2, LOW);
    	
    	 // Rotate motor2 forward
        digitalWrite(motorPin3, HIGH);
        digitalWrite(motorPin4, LOW);
   
    	delay(5000);
    	
    	roboState = moveRight;
        break;
    
    case moveRight:
    	Serial.println("Motor Moving Right");
    	// Rotate motor1 forward
        digitalWrite(motorPin1, HIGH);
        digitalWrite(motorPin2, LOW);
    	
    	 // Rotate motor2 backward
        digitalWrite(motorPin3, LOW);
        digitalWrite(motorPin4, HIGH);
          
        delay(5000);
        roboState = moveLeft; 
        break;
    
     case moveLeft:
    	Serial.println("Motor Moving Left");
    	// Rotate motor1 backward
        digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, HIGH);
    	
    	 // Rotate motor2 forward
        digitalWrite(motorPin3, HIGH);
        digitalWrite(motorPin4, LOW);
          
        delay(5000);
        roboState = moveBackward; 
        break;
    
    case moveBackward:
    	Serial.println("Motor Moving Backward");
    	// Rotate motor1 backward
        digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, HIGH);
    	
    	 // Rotate motor2 backward
        digitalWrite(motorPin3, LOW);
        digitalWrite(motorPin4, HIGH);
          
        delay(5000);
        roboState = stop; 
        break;
    
    default:
    	Serial.println("\n We hit the default");      	
      	roboState = moveForward;
  }

  // Print encoder positions to Serial Monitor
  Serial.print("Motor 1 Position: ");
  Serial.println(motor1_position);
  Serial.print("Motor 2 Position: ");
  Serial.println(motor2_position);

  delay(500); // Adjust delay as needed
}

void updateMotorA() {
  int stateA = digitalRead(motor1_encoderA);
  int stateB = digitalRead(motor1_encoderB);

  if (stateA == stateB) {
    motor1_position++;
  } else {
    motor1_position--;
  }
}

void updateMotorB() {
  int stateA = digitalRead(motor2_encoderA);
  int stateB = digitalRead(motor2_encoderB);

  if (stateA == stateB) {
    motor2_position++;
  } else {
    motor2_position--;
  }
}

