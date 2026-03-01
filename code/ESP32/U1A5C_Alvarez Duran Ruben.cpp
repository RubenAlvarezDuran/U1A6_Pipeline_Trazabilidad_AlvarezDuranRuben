#include <WiFi.h>
#include <PubSubClient.h>

// ====== WiFi ======
const char* WIFI_SSID = "Pomni";
const char* WIFI_PASS = "123456789";

// ===== MQTT público =====
const char* mqtt_server   = "broker.hivemq.com";
const int   mqtt_port     = 1883;

// Control (Node-RED -> ESP32)
const char* mqtt_topic_sub = "meca/calibrar/control";

// Telemetría (ESP32 -> Node-RED)
const char* mqtt_topic_pub = "meca/calibrar/adc";
const char* mqtt_topic_status = "meca/calibrar/status";

// ===== Sensores (usa ADC1 si hay WiFi) =====
const int PIN_S1 = 34;
const int PIN_S2 = 35;

// ===== Muestreo =====
unsigned long SAMPLE_MS = 100;  // 10 Hz
unsigned long last_ms = 0;
uint32_t seq = 0;
bool streaming = true;          // START/STOP controlan esto

WiFiClient espClient;
PubSubClient client(espClient);

void wifiConnect() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
  }
}

void publishStatus(const char* msg) {
  client.publish(mqtt_topic_status, msg);
}

void handleControlMessage(char* topic, byte* payload, unsigned int length) {
  // payload -> String
  String cmd;
  cmd.reserve(length);
  for (unsigned int i = 0; i < length; i++) cmd += (char)payload[i];
  cmd.trim();

  // Comandos esperados (desde Node-RED):
  if (cmd.equalsIgnoreCase("START")) {
    streaming = true;
    publishStatus("OK:START");
  } else if (cmd.equalsIgnoreCase("STOP")) {
    streaming = false;
    publishStatus("OK:STOP");
  } else if (cmd.startsWith("RATE=")) {
    long v = cmd.substring(5).toInt();
    if (v >= 50 && v <= 2000) {        // límites razonables
      SAMPLE_MS = (unsigned long)v;
      publishStatus(("OK:RATE=" + String(SAMPLE_MS)).c_str());
    } else {
      publishStatus("ERR:RATE_OUT_OF_RANGE");
    }
  } else if (cmd.equalsIgnoreCase("RESETSEQ")) {
    seq = 0;
    publishStatus("OK:RESETSEQ");
  } else {
    publishStatus("ERR:UNKNOWN_CMD");
  }
}

void mqttConnect() {
  while (!client.connected()) {
    // ClientID único para evitar choques
    String clientId = "ESP32_U1A5_" + String((uint32_t)ESP.getEfuseMac(), HEX);

    if (client.connect(clientId.c_str())) {
      client.subscribe(mqtt_topic_sub);
      publishStatus("OK:MQTT_CONNECTED");
    } else {
      delay(1000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(200);

  // ADC 12-bit (0..4095)
  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);

  wifiConnect();

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(handleControlMessage);
  mqttConnect();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) wifiConnect();
  if (!client.connected()) mqttConnect();
  client.loop();

  unsigned long now = millis();
  if (streaming && (now - last_ms >= SAMPLE_MS)) {
    last_ms = now;

    int s1 = analogRead(PIN_S1);
    int s2 = analogRead(PIN_S2);

    char payload[128];
    snprintf(payload, sizeof(payload),
             "{\"t_ms\":%lu,\"seq\":%lu,\"s\":[%d,%d]}",
             (unsigned long)now, (unsigned long)seq++, s1, s2);

    client.publish(mqtt_topic_pub, payload);

    // Debug opcional
    Serial.println(payload);
  }
}