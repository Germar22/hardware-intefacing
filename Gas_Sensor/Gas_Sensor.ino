#define BUZZER_PIN 5 // Define the pin for the buzzer (GPIO12)
#define SENSOR_PIN 32 // Define the analog pin connected to the gas sensor (GPIO32)

void setup() {
  pinMode(BUZZER_PIN, OUTPUT); // Set buzzer pin as output
  digitalWrite(BUZZER_PIN, LOW); // Ensure buzzer is initially off
  pinMode(SENSOR_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(SENSOR_PIN); // Read analog value from sensor
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);

  // You need to calibrate the sensor and set the threshold accordingly
  // For demonstration purposes, I'm setting an arbitrary threshold of 500
  int threshold = 500;

  if (sensorValue > threshold) {
    // If gas concentration exceeds the threshold, activate the buzzer
    digitalWrite(BUZZER_PIN, HIGH);
    Serial.println("Gas detected!");
  } else {
    // Otherwise, turn off the buzzer
    digitalWrite(BUZZER_PIN, LOW);
    Serial.println("No gas detected.");
  }

  delay(5000); // Delay for stability
}


//Buzzer pin 5
//A0 pin 32
//D0 pin 14

