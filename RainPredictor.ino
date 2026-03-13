#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SimpleDHT.h>
#include "model.h" 

int pinDHT11 = 16; 
SimpleDHT11 dht11;
Eloquent::ML::Port::LogisticRegression classifier;
LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0, 0); // Centering the intro text
  lcd.print("AI RAIN");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Forcasting!");
  delay(3000);
  lcd.clear();
}

void loop() {
  byte temperature = 0;
  byte humidity = 0;
  
  if (dht11.read(pinDHT11, &temperature, &humidity, NULL) == SimpleDHTErrSuccess) {
    float features[] = {(float)temperature, (float)humidity};
    float probabilities[2];
    classifier.predictProbabilities(features, probabilities);
    float Rainchance = probabilities[1] * 100;

    // --- Optimized LCD Display Logic ---
    
    // Row 0: Sensors (Fixed positions avoid overprinting)
    lcd.setCursor(0, 0);
    lcd.print("T:"); 
    lcd.print((int)temperature); 
    lcd.print("C  "); // Extra spaces clear old digits if temp drops from 100 to 99
    
    lcd.setCursor(0, 1);
    lcd.print("H:"); 
    lcd.print((int)humidity); 
    lcd.print("%  ");
    delay(5000);
    lcd.clear();
    // Row 1: AI Result
    lcd.setCursor(0, 0);
    lcd.print("Rain:");
    lcd.print((int)Rainchance);
    lcd.print("%   ");
    delay(5000);
    lcd.clear(); // 3 spaces to clear any leftover characters
    // Jump to the end of the line for the status
    lcd.setCursor(0, 0); 
    if (Rainchance<=25.00) {
      lcd.print("LOW  "); // Spaces ensure "HIGH!" is fully erased
    } 
    else if (Rainchance <= 50.00) {
      lcd.print("MED  ");
    } 
    else {
      lcd.print("HIGH!");
    }

    Serial.print("Chance: "); Serial.print(Rainchance); Serial.println("%");

  } else {
    lcd.setCursor(0, 0);
    lcd.print("SENSOR ERROR!   ");
  }
  
  delay(5000); // 2 seconds is plenty for a weather monitor
}