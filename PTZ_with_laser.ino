#include <Servo.h>

const uint8_t PAN_PIN  = 9;
const uint8_t TILT_PIN = 10;
const int PAN_MIN  = 10;
const int PAN_MAX  = 170;
const int TILT_MIN = 20;
const int TILT_MAX = 160;

Servo panServo;
Servo tiltServo;

const int LED_PIN = 7;  // You can change this to 7 if using external LED

void setup() {
  panServo.attach(PAN_PIN);
  tiltServo.attach(TILT_PIN);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  panServo.write((PAN_MIN + PAN_MAX) / 2);
  tiltServo.write((TILT_MIN + TILT_MAX) / 2);

  Serial.begin(115200);
}

void loop() {
  static String cmd = "";
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      processCommand(cmd);
      cmd = "";
    } else {
      cmd += c;
    }
  }
}

void processCommand(const String& s) {
  if (s.startsWith("FIRE")) {
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    digitalWrite(LED_PIN, LOW);
    return;
  }

  int pIndex = s.indexOf('P');
  int tIndex = s.indexOf('T');
  if (pIndex == -1 || tIndex == -1) return;

  int panVal  = s.substring(pIndex + 1, pIndex + 4).toInt();
  int tiltVal = s.substring(tIndex + 1, tIndex + 4).toInt();

  panVal  = constrain(panVal,  PAN_MIN,  PAN_MAX);
  tiltVal = constrain(tiltVal, TILT_MIN, TILT_MAX);

  panServo.write(panVal); 
  tiltServo.write(tiltVal);
}
