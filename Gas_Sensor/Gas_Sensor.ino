#define GAS_PIN A0
#define BUZZER_PIN 4

void setup() {
  Serial.begin(9600);
  pinMode(GAS_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // Read the gas sensor data
  int gasValue = analogRead(GAS_PIN);

  // Print the gas sensor raw value
  Serial.print("Gas Sensor Value: ");
  Serial.println(gasValue);

  // Check if the gas concentration exceeds a threshold (adjust as needed)
  if (gasValue > 200) {
    // Activate the buzzer if the concentration is above the threshold
    digitalWrite(BUZZER_PIN, HIGH);
    Serial.println("Gas Detected! Buzzer activated.");
  } else {
    // Turn off the buzzer if the concentration is below the threshold
    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(500); // Adjust the delay as needed
}

