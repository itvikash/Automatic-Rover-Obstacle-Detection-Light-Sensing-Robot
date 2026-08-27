/*
  Automatic Rover — Obstacle Detection & Light-Sensing Robot
  ------------------------------------------------------------
  Board: Arduino Uno
  Sensors: Ultrasonic (HC-SR04), LDR
  Actuators: 4x DC Motors via motor driver (L298N/L293D style, 2 channels)
  Control: RC Remote (manual mode) + Auto obstacle-avoidance mode

  NOTE: Pin numbers below are common defaults for this kind of build.
  Double check them against your actual wiring before uploading.
*/

// ---------- Motor Driver Pins (2-channel driver controlling 4 motors) ----------
#define ENA 5    // Left side motors speed (PWM)
#define IN1 6
#define IN2 7
#define ENB 9    // Right side motors speed (PWM)
#define IN3 8
#define IN4 10

// ---------- Ultrasonic Sensor Pins ----------
#define TRIG_PIN 12
#define ECHO_PIN 11

// ---------- LDR Sensor Pin ----------
#define LDR_PIN A0

// ---------- RC Receiver Pins (PWM signal input from FlySky receiver) ----------
#define RC_CH1 2   // Steering / Left-Right
#define RC_CH2 3   // Throttle / Forward-Backward
#define RC_MODE_CH 4  // Switch channel: toggles Auto / Manual mode

// ---------- Thresholds ----------
#define OBSTACLE_DISTANCE_CM 20
#define DARK_THRESHOLD 400   // Adjust based on LDR readings in your environment

void setup() {
  Serial.begin(9600);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(LDR_PIN, INPUT);

  pinMode(RC_CH1, INPUT);
  pinMode(RC_CH2, INPUT);
  pinMode(RC_MODE_CH, INPUT);

  stopMotors();
}

void loop() {
  int modeSignal = pulseIn(RC_MODE_CH, HIGH, 25000);
  bool manualMode = (modeSignal > 1500); // Switch flipped = manual

  int lightLevel = analogRead(LDR_PIN);
  bool isDark = (lightLevel < DARK_THRESHOLD);

  if (manualMode) {
    runManualMode();
  } else {
    runAutoMode();
  }

  // Optional: react to darkness (e.g., slow down, log, or trigger LED)
  if (isDark) {
    Serial.println("Low light detected");
  }

  delay(50);
}

// ---------------- AUTO MODE: Obstacle Avoidance ----------------
void runAutoMode() {
  long distance = getDistanceCM();
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance > 0 && distance < OBSTACLE_DISTANCE_CM) {
    stopMotors();
    delay(200);
    moveBackward();
    delay(400);
    turnRight();
    delay(400);
  } else {
    moveForward();
  }
}

// ---------------- MANUAL MODE: RC Control ----------------
void runManualMode() {
  int steering = pulseIn(RC_CH1, HIGH, 25000); // ~1000-2000us
  int throttle = pulseIn(RC_CH2, HIGH, 25000);

  if (throttle > 1600) {
    moveForward();
  } else if (throttle < 1400 && throttle > 900) {
    moveBackward();
  } else if (steering > 1600) {
    turnRight();
  } else if (steering < 1400 && steering > 900) {
    turnLeft();
  } else {
    stopMotors();
  }
}

// ---------------- Ultrasonic Distance ----------------
long getDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 25000);
  long distance = duration * 0.034 / 2;
  return distance;
}

// ---------------- Motor Control Functions ----------------
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
