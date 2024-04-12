#include <WiFi.h>
#include <HTTPClient.h>

const char WIFI_SSID[] = "Pocho";
const char WIFI_PASSWORD[] = "chocolatelami";

String HOST_NAME = "http://afas.atwebpages.com"; // change to your PC's IP address
String PATH_NAME   = "/dashboard/db/alert.php";
String queryString = "?latitude";
String coordinates = "=6.123&longitude=125.123&alert_time=2024-03-15%2012:00:00";

void setup() {
  Serial.begin(9600); 

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  
  HTTPClient http;

  http.begin(HOST_NAME + PATH_NAME + queryString + coordinates) ; //HTTP
  int httpCode = http.GET();

  // httpCode will be negative on error
  if(httpCode > 0) {
    // file found at server
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    } else {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
}

void loop() {

}
