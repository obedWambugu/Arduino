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

// Ultrasonic sensor pins
const int trigPin = 13;
const int echoPin = 7;

// Encoder counts
volatile long motor1_position = 0;
volatile long motor2_position = 0;

// For counting time increments
enum{STOP, MOVE_FORWARD, MOVE_RIGHT, MOVE_LEFT, MOVE_BACKWARD};
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
  
  // Ultrasonic sensor pins as outputs/inputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Attach interrupts for encoders
  attachInterrupt(digitalPinToInterrupt(motor1_encoderA), updateMotorA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(motor2_encoderA), updateMotorB, CHANGE);
  
  roboState = STOP;
  // Start Serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  long distance = measureDistance();

  if (distance > 20){
    roboState = MOVE_FORWARD;
  }else if(distance > 10 && distance <= 20){
    roboState = MOVE_RIGHT;
  }else if(distance > 5 && distance <= 10){
    roboState = MOVE_LEFT;
  }else{
    roboState = STOP;
  }

  switch(roboState){
    case STOP:   
    	stop();
    	break;
    
    case MOVE_FORWARD: 
    	moveForward();
    	break;
    
    case MOVE_RIGHT:
    	moveRight();
        break;
    
    case MOVE_LEFT:
    	moveLeft();
        break;
    
    case MOVE_BACKWARD:
    	moveBackward();
        break;
  }

  // Print encoder positions to Serial Monitor
  Serial.print("Motor 1 Position: ");
  Serial.println(motor1_position);
  Serial.print("Motor 2 Position: ");
  Serial.println(motor2_position);

  delay(500); // Adjust delay as needed
}

long measureDistance() {
  // Send a 10us pulse to trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the time it takes for the echo to return
  long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in cm (Speed of sound is 34300 cm/s)
  long distance = duration * 0.034 / 2;

  return distance;
}

void moveForward(){
  // Example: Move both motors forward at full speed
  analogWrite(enablePin1, 255); // Full speed
  analogWrite(enablePin2, 255); // Full speed

  Serial.println("Robot Moving Forward");
  // Rotate motor1 forward
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);

  // Rotate motor2 forward
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
}

void moveRight(){
  Serial.println("Robot Moving Right");
  analogWrite(enablePin1, 255); 
  analogWrite(enablePin2, 150);
  // Rotate motor1 forward
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);

  // Rotate motor2 backward
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
}

void moveLeft(){
  Serial.println("Robot Moving Left");
  analogWrite(enablePin1, 150); 
  analogWrite(enablePin2, 255);
  // Rotate motor1 backward
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);

  // Rotate motor2 forward
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
}

void moveBackward(){
  Serial.println("Robot Moving Backward");
  analogWrite(enablePin1, 255); 
  analogWrite(enablePin2, 255);
  // Rotate motor1 backward
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);

  // Rotate motor2 backward
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
}


void stop(){
  Serial.println("Robot Stopped");
  analogWrite(enablePin1, 0); // Stop motor 1
  analogWrite(enablePin2, 0); // Stop motor 2
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

