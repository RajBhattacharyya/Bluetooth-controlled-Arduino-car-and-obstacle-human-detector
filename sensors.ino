#include <Servo.h>

// Define pin numbers
#define TRIG_PIN 2
#define ECHO_PIN 3
#define PIR_PIN 4
#define BUZZER_PIN 5
#define SERVO_PIN 6

// Define servo parameters
#define SERVO_MIN_ANGLE 15
#define SERVO_MAX_ANGLE 165
#define SERVO_DELAY_MS 30

// Define radar parameters
#define RADAR_SWEEP_DELAY_MS 20
#define RADAR_PULSE_DURATION_US 10

// Define PIR parameters
#define PIR_DELAY_MS 200

// Initialize servo and sensors
Servo servo;
long duration, distance;
int pir_state = LOW;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Initialize sensors
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  servo.attach(SERVO_PIN);

  // Move servo to starting position
  servo.write(SERVO_MIN_ANGLE);
  delay(SERVO_DELAY_MS);
}

void loop() {
  // Sweep servo back and forth
  for (int angle = SERVO_MIN_ANGLE; angle < SERVO_MAX_ANGLE; angle++) {
    // Move servo to current angle
    servo.write(angle);
    delay(SERVO_DELAY_MS);

    // Get distance from ultrasonic sensor
    distance = getDistance();

    // Check if human is detected by PIR sensor
    pir_state = digitalRead(PIR_PIN);

    if (pir_state == HIGH) {
      // Play sound through buzzer if human is detected
      tone(BUZZER_PIN, 2000, 1000);
    }

    // Print debug information
    Serial.print(angle);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
  }

  for (int angle = SERVO_MAX_ANGLE; angle > SERVO_MIN_ANGLE; angle--) {
    // Move servo to current angle
    servo.write(angle);
    delay(SERVO_DELAY_MS);

    // Get distance from ultrasonic sensor
    distance = getDistance();

    // Check if human is detected by PIR sensor
    pir_state = digitalRead(PIR_PIN);

    if (pir_state == HIGH) {
      // Play sound through buzzer if human is detected
      tone(BUZZER_PIN, 2000, 1000);
    }

    // Print debug information
    Serial.print(angle);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
  }
}

int getDistance() {
  // Send ultrasonic pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(RADAR_PULSE_DURATION_US);
  digitalWrite(TRIG_PIN, LOW);

  // Measure pulse duration
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance
  distance = duration*0.034/2;

  // Return distance in centimeters
  return distance;
}
