// U1A4C - Telemetría ligera local (USB/Serial) en ESP32
// Mensaje mínimo: "t_ms,s"

#include <Arduino.h>

const int SENSOR_PIN = 34;        // AO del TCRT5000 -> GPIO34 (ADC)
const uint32_t FS_MS = 20;        // 20 ms => 50 Hz
uint32_t last_ms = 0;

void setup() {
  Serial.begin(115200);
  delay(300);

  // ADC en ESP32: 0–4095 (12 bits)
  analogReadResolution(12);

  // Opcional: ajustar atenuación si tu AO sube mucho
  // analogSetPinAttenuation(SENSOR_PIN, ADC_11db); // rango ~0-3.3V aprox

  // No mandes header para no complicar Node-RED:
  // Serial.println("t_ms,s");
}

void loop() {
  uint32_t now = millis();
  if (now - last_ms >= FS_MS) {
    last_ms = now;

    int s = analogRead(SENSOR_PIN); // 0–4095 (aprox)
    Serial.print(now);
    Serial.print(",");
    Serial.println(s);
  }
}