#include <Servo.h>

Servo dustbinServo;

// Ultrasonic sensor pins
const int trigPin = 9;
const int echoPin = 10;

// Servo pin
const int servoPin = 6;

// Variables
long duration;
int distance;

// Servo angles
int openAngle = 90;    // lid open
int closeAngle = 0;   // lid close

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  dustbinServo.attach(servoPin);
  dustbinServo.write(closeAngle);   // start closed

  Serial.begin(9600);
}

void loop() {
  // Ultrasonic trigger pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo time
  duration = pulseIn(echoPin, HIGH);

  // Convert to distance (cm)
  distance = duration * 0.034 / 2;

  // Print distance (optional)
  Serial.print("Distance: ");
  Serial.println(distance);

  // MAIN LOGIC
  if (distance > 0 && distance < 15) {
    dustbinServo.write(openAngle);   // open immediately
  } else {
    dustbinServo.write(closeAngle);  // close immediately
  }

  delay(100); // small delay for stability
}
