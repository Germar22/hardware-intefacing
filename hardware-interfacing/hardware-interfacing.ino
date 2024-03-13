const int smokeAlarmPin = 21; // Digital input pin connected to the smoke alarm
const int ledPin = 22; // Digital output pin connected to an LED for indicating smoke detection

const int numReadings = 10; // Number of readings to average for noise filtering
int readings[numReadings];  // Array to store readings for averaging
int idx = 0;  // Index for storing the current reading
int total = 0;  // Total sum of readings

void setup() {
  pinMode(smokeAlarmPin, INPUT);
  pinMode(ledPin, OUTPUT);
  
  Serial.begin(115200); // Initialize serial communication
  
  // Initialize the readings array
  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }
}

void loop() {
  // Read the sensor input
  int sensorReading = digitalRead(smokeAlarmPin);

  // Subtract the oldest reading from the total
  total -= readings[idx];
  // Add the new reading to the total
  total += sensorReading;
  // Store the new reading in the readings array
  readings[idx] = sensorReading;
  // Increment the index for the next reading
  idx = (idx + 1) % numReadings;

  // Calculate the filtered value by averaging the readings
  int filteredReading = total / numReadings;

  if (filteredReading == HIGH) {
    // Smoke detected
    digitalWrite(ledPin, HIGH); // Turn on the LED
    Serial.println("Smoke detected!"); // Output to serial monitor
    // Add your additional actions here, such as sending notifications, activating alarms, etc.
  } else {
    // No smoke detected
    digitalWrite(ledPin, LOW); // Turn off the LED
    Serial.println("No smoke detected."); // Output to serial monitor
  }

  // Adjust delay as needed to avoid rapid polling
  delay(500); 
}

