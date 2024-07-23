#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// Configuración de la red WiFi
const char* ssid = "BLIZZARNET2.4 GODO";
const char* password = "/Godo8513/2024";

// Configuración de ThingsBoard
const char* mqtt_server = "thingsboard.cloud";
const char* access_token = "vygTpEUOJQ79Y3URBgLX";

// Pines de los potenciómetros, pulsador y LEDs
const int pot1Pin = 34;
const int pot2Pin = 35;
const int buttonPin = 32;
const int ledPin = 26;
const int pwmLedPin = 25;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  
  // Configuración de los pines
  pinMode(pot1Pin, INPUT);
  pinMode(pot2Pin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(pwmLedPin, OUTPUT);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);


  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando a ThingsBoard...");
    if (client.connect("ESP32Client", access_token, NULL)) {
      Serial.println("conectado");
      client.subscribe("v1/devices/me/attributes");
    } else {
      Serial.print("falló, rc=");
      Serial.print(client.state());
      Serial.println(" intentando nuevamente en 5 segundos");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload, length);

  if (String(topic) == "v1/devices/me/attributes") {
    if (doc.containsKey("boton")) {
      digitalWrite(ledPin, doc["boton"]);
      Serial.print("Estado del LED actualizado: ");
      Serial.println(doc["boton"] ? "Encendido" : "Apagado");
    }

    if (doc.containsKey("slide")) {
      int pwmValue = doc["slide"];
      analogWrite(pwmLedPin, pwmValue);
      Serial.print("Valor del PWM actualizado: ");
      Serial.println(pwmValue);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Leer valores de los potenciómetros y el botón
  int pot1Value = analogRead(pot1Pin);
  int pot2Value = analogRead(pot2Pin);
  int buttonState = digitalRead(buttonPin);

  // Crear un JSON con los datos
  StaticJsonDocument<200> jsonBuffer;
  JsonObject root = jsonBuffer.to<JsonObject>();
  root["pot1"] = pot1Value;
  root["pot2"] = pot2Value;
  root["button"] = buttonState;

  char buffer[512];
  size_t n = serializeJson(root, buffer);
  client.publish("v1/devices/me/telemetry", buffer, n);

  delay(1000);
}
