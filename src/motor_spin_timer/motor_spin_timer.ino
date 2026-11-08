/*
  Leonardo + IBT-2: physical timer and three-position selector, NO encoder.
  Open-loop PWM: these are duty-cycle values, NOT regulated RPM.

  CONNECTIONS (verify board labels, never infer terminal order):
  Leonardo 5V -> IBT-2 VCC. Leonardo GND -> IBT-2 GND and supply negative.
  D9 -> RPWM; LPWM -> GND; D8 -> BOTH R_EN and L_EN.
  Fit 10k ohm from D8 to GND and another 10k from D9 to GND.
  R_IS and L_IS unused. Regulated 6V positive -> fuse -> B+.
  Supply negative -> B-. Motor wires -> M+ and M-.
  Power Leonardo separately by USB; never power motor from Arduino.
  Size supply and fuse from motor startup/stall current and wire rating.

  Timer must be an isolated, unpowered dry contact, closed while counting:
  one lead -> D4, other -> GND. Never connect mains to this circuit.
  Verify continuity with ALL power disconnected: open at zero, closed running.

  Selector assumption: two independent NO contacts, maintained 3 positions:
  LEFT: left contact closed only. CENTER: both open. RIGHT: right closed only.
  Left contact: D5 to GND. Right contact: D6 to GND.
  Identify contact pairs by continuity; verify all 3 positions before wiring.
  Both closed is invalid and stops the motor. A disconnected selector can
  look like CENTER; this arrangement cannot detect that wiring fault.

  Timer opening disables drive immediately (motor coasts).
  Stable closure starts after 40 ms, including if timer is active at power-up.
  Selector changes briefly disable drive, then select the new speed.
  Start unloaded and guarded. Calibrate PWM under expected load using an
  external tachometer if RPM matters. This is not a safety-rated controller.
*/
#include <Arduino.h>

const uint8_t TIMER_PIN = 4;
const uint8_t LEFT_PIN = 5;
const uint8_t RIGHT_PIN = 6;
const uint8_t ENABLE_PIN = 8;
const uint8_t PWM_PIN = 9;

// EXAMPLES ONLY: 0=off, 255=full duty. Edit after calibration.
// Position:                    left  center  right
const uint8_t SPEED_PWM[3] = {     80,   140,   200 };
const unsigned long DEBOUNCE_MS = 40;

uint8_t lastInputs = 255;
unsigned long changedAt = 0;

void stopMotor() {
  digitalWrite(ENABLE_PIN, LOW);
  analogWrite(PWM_PIN, 0);
}

void setup() {
  // Set output latches LOW before switching pins to outputs.
  digitalWrite(ENABLE_PIN, LOW);
  digitalWrite(PWM_PIN, LOW);
  pinMode(ENABLE_PIN, OUTPUT);
  pinMode(PWM_PIN, OUTPUT);
  stopMotor();
  pinMode(TIMER_PIN, INPUT_PULLUP);
  pinMode(LEFT_PIN, INPUT_PULLUP);
  pinMode(RIGHT_PIN, INPUT_PULLUP);
}

void loop() {
  const bool timerOn = digitalRead(TIMER_PIN) == LOW;
  const bool left = digitalRead(LEFT_PIN) == LOW;
  const bool right = digitalRead(RIGHT_PIN) == LOW;
  const uint8_t inputs = (timerOn ? 1 : 0) |
                         (left ? 2 : 0) | (right ? 4 : 0);
  const unsigned long now = millis();

  if (inputs != lastInputs) {
    lastInputs = inputs;
    changedAt = now;
  }

  // Immediate OFF; delayed ON rejects contact bounce.
  if (!timerOn || (left && right) ||
      (unsigned long)(now - changedAt) < DEBOUNCE_MS) {
    stopMotor();
    return;
  }

  const uint8_t position = left ? 0 : (right ? 2 : 1);
  const uint8_t pwm = SPEED_PWM[position];
  if (pwm == 0) {
    stopMotor();
  } else {
    analogWrite(PWM_PIN, pwm);
    digitalWrite(ENABLE_PIN, HIGH);
  }
}
