// Motor1 control pins
const int motorPin1 = 3; // IN1 on L293D
const int motorPin2 = 4; // IN2 on L293D
const int enablePin1 = 5; // EN1 on L293D
// Motor2 control pins
const int motorPin3 = 10; // IN3 on L293D
const int motorPin4 = 11; // IN4 on L293D
const int enablePin2 = 9; // EN2 on L293D
void setup() {
  // Set motor1 control pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin1, OUTPUT);
  
  // Set motor2 control pins as outputs
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(enablePin2, OUTPUT);

  // Ensure motor1 is off at the start
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(enablePin1, HIGH); // Enable the motor driver

  // Ensure motor2 is off at the start
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  digitalWrite(enablePin2, HIGH); // Enable the motor driver
}

void loop() {
  // Rotate motor1 forward
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  delay(2000); // Rotate forward for 2 seconds

  // Stop the motor1
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  delay(1000); // Stop for 1 second

  // Rotate motor2 forward
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay(2000); // Rotate forward for 2 seconds

  // Stop the motor2
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(1000); // Stop for 1 second
  
}
