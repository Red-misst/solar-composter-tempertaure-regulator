#include <DHT.h>

#define DHTPIN 2        // DHT22 data pin
#define DHTTYPE DHT22
#define RELAY_PIN 7     // Relay control pin

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);  // heater OFF initially
}

void loop() {
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temp)) {
    Serial.println("Failed to read from DHT");
    return;
  }

  Serial.print("Temp: "); Serial.print(temp);
  Serial.print("  Humidity: "); Serial.println(humidity);

  // Heater ON if temp < 55°C
  if (temp < 55) {
    digitalWrite(RELAY_PIN, HIGH);
  }
  // Heater OFF if temp > 70°C
  else if (temp > 70) {
    digitalWrite(RELAY_PIN, LOW);
  }

  delay(3000); // wait 3 seconds
}
