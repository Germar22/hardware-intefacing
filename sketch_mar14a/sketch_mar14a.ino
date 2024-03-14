#include <WiFi.h>
#include <HTTPClient.h>

const char WIFI_SSID[] = "CMOICTD";
const char WIFI_PASSWORD[] = "@CMOictd2022";

const int BUZZER_PIN = 12; // Define the pin for the buzzer (GPIO12)
const int SENSOR_PIN = 32; // Define the analog pin connected to the gas sensor (GPIO32)

String HOST_NAME = "afas.atwebpages.com"; // change to your server's domain name
String PATH_NAME = "/dashboard/db/alert.php";
String queryString = "?coordinates";
String coordinates = "6.07479, 125.14123";

void setup() {
  Serial.begin(9600); 

  pinMode(BUZZER_PIN, OUTPUT); // Set buzzer pin as output
  digitalWrite(BUZZER_PIN, LOW); // Ensure buzzer is initially off
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting to WiFi...");
  while(WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  int sensorValue = analogRead(SENSOR_PIN); // Read analog value from sensor
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);

  // You need to calibrate the sensor and set the threshold accordingly
  // For demonstration purposes, I'm setting an arbitrary threshold of 500
  int threshold = 500;

  if (sensorValue > threshold) {
    // If gas concentration exceeds the threshold, activate the beeping sound
    beep();
    Serial.println("Fire detected!");

    // Now, send the data and coordinates
    sendHttpRequest();

    delay(5000); // Wait for 5 seconds before checking again
  } else {
    // Otherwise, turn off the buzzer
    digitalWrite(BUZZER_PIN, LOW);
    Serial.println("No fire detected.");
    delay(1000); // Delay for stability
  }
}

// Function to produce beeping sound
void beep() {
  for (int i = 0; i < 3; i++) { // Beep three times
    digitalWrite(BUZZER_PIN, HIGH); // Turn buzzer on
    delay(200); // Beep duration
    digitalWrite(BUZZER_PIN, LOW); // Turn buzzer off
    delay(200); // Delay between beeps
  }
}

// Function to send HTTP request
void sendHttpRequest() {
  HTTPClient http;
  String url = "http://" + HOST_NAME + PATH_NAME + queryString + coordinates;
  Serial.print("Sending HTTP GET request to: ");
  Serial.println(url);

  if (http.begin(url)) {
    int httpCode = http.GET();

    if (httpCode > 0) {
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.println("Server response:");
        Serial.println(payload);
      } else {
        Serial.print("[HTTP] GET... HTTP Code: ");
        Serial.println(httpCode);
      }
    } else {
      Serial.print("[HTTP] GET... failed, error: ");
      Serial.println(http.errorToString(httpCode).c_str());
    }

    http.end();
  } else {
    Serial.println("[HTTP] Unable to connect to server");
  }
}
