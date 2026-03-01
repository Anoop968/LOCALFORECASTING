#include <SimpleDHT.h>
#include "model.h" // The file you just generated

// Hardware Setup
int pinDHT11 = 16; // D0 on NodeMCU
SimpleDHT11 dht11;
Eloquent::ML::Port::LogisticRegression classifier;

void setup() {
  Serial.begin(115200);
}

void loop() {
  byte temperature = 0;
  byte humidity = 0;
  
  // Read sensor
  if (dht11.read(pinDHT11, &temperature, &humidity, NULL) == SimpleDHTErrSuccess) {
    
    // Convert current readings into an array for the AI
    float features[] = {(float)temperature, (float)humidity};
    
    // AI Prediction
    const char* prediction = classifier.predictLabel(features);
    
    // Display results
    Serial.print("Current: ");
    Serial.print((int)temperature); Serial.print("*C, ");
    Serial.print((int)humidity); Serial.println("%");
    
    Serial.print("AI Prediction: ");
    Serial.println(prediction); // Will print "Rain" or "No Rain"
    
  } else {
    Serial.println("DHT11 Read Failed!");
  }
  
  delay(5000); // Wait 5 seconds
}