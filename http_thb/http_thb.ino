#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Configuración de la red WiFi
const char* ssid = "BLIZZARNET2.4 GODO";
const char* password = "/Godo8513/2024";

// Configuración de ThingsBoard
const char* thingsboard_server = "http://thingsboard.cloud";
const char* access_token = "c1l1cnbu9xmuhuh318dh";

// Pines de los potenciómetros, pulsador y LEDs
const int pot1Pin = 34;
const int pot2Pin = 35;
const int buttonPin = 32;
const int ledPin = 26;
const int pwmLedPin = 25;

// Variables para almacenar el estado de los atributos
bool ledState = false;
int pwmValue = 0;

void setup() {
  Serial.begin(115200);

  // Configuración de los pines
  pinMode(pot1Pin, INPUT);
  pinMode(pot2Pin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(pwmLedPin, OUTPUT);

  setup_wifi();

  // Configurar el estado inicial del LED y el PWM
  digitalWrite(ledPin, ledState);
  analogWrite(pwmLedPin, pwmValue);
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

void sendTelemetry() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Crear URL para la solicitud POST
    String url = String(thingsboard_server) + "/api/v1/" + access_token + "/telemetry";

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

    String payload;
    serializeJson(root, payload);

    // Iniciar solicitud HTTP
    http.begin(url);
    http.addHeader("Content-Type", "application/json");

    // Enviar solicitud POST
    int httpResponseCode = http.POST(payload);
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error en la solicitud POST: ");
      Serial.println(http.errorToString(httpResponseCode).c_str());
    }

    // Terminar solicitud
    http.end();
  } else {
    Serial.println("WiFi no conectado");
  }
}

void checkAttributes() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Crear URL para la solicitud GET de atributos
    String url = String(thingsboard_server) + "/api/v1/" + access_token + "/attributes?sharedKeys=boton,slide";

    // Iniciar solicitud HTTP
    http.begin(url);

    // Enviar solicitud GET
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);

      // Parsear la respuesta JSON
      StaticJsonDocument<200> doc;
      deserializeJson(doc, response);
      JsonObject sharedAttributes = doc["shared"];

      if (sharedAttributes.containsKey("boton")) {
        bool newLedState = sharedAttributes["boton"];
        if (newLedState != ledState) {
          ledState = newLedState;
          digitalWrite(ledPin, ledState);
          Serial.print("Estado del LED actualizado: ");
          Serial.println(ledState ? "Encendido" : "Apagado");
        }
      }

      if (sharedAttributes.containsKey("slide")) {
        int newPwmValue = sharedAttributes["slide"];
        if (newPwmValue != pwmValue) {
          pwmValue = newPwmValue;
          analogWrite(pwmLedPin, pwmValue);
          Serial.print("Valor del PWM actualizado: ");
          Serial.println(pwmValue);
        }
      }
    } else {
      Serial.print("Error en la solicitud GET de atributos: ");
      Serial.println(http.errorToString(httpResponseCode).c_str());
    }

    // Terminar solicitud
    http.end();
  } else {
    Serial.println("WiFi no conectado");
  }
}

void loop() {
  sendTelemetry();
  checkAttributes();
  delay(1000); // Esperar 10 segundos antes de la siguiente solicitud
}
