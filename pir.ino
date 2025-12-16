#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define SMOKE_SENSOR_PIN A1
#define BUZZER 5
#define DHTPIN 3
#define DHTTYPE DHT11
#define PIR_SENSOR_PIN 2
#define PIR_SENSOR_PIN 4  
DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(9600);
    lcd.init();  
    lcd.backlight(); 
    lcd.clear();

    pinMode(SMOKE_SENSOR_PIN, INPUT);
    pinMode(BUZZER, OUTPUT);
    pinMode(PIR_SENSOR_PIN, INPUT);

    dht.begin();

    lcd.setCursor(0, 0);
    lcd.print("Initializing...");
    Serial.println("System Initializing...");
    delay(2000);
    lcd.clear();
}

void loop() {
    int smokeValue = analogRead(SMOKE_SENSOR_PIN);
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    int motion = digitalRead(PIR_SENSOR_PIN);

    if (motion == HIGH) {
        Serial.println("MOTION DETECTED!");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("WARNING!");
        lcd.setCursor(0, 1);
        lcd.print("Motion Detected!");
        digitalWrite(BUZZER, HIGH);
    } else {
        digitalWrite(BUZZER, LOW);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Smoke:");
        lcd.print(smokeValue);
        
        lcd.setCursor(0, 1);
        lcd.print("T:");
        lcd.print(temperature);
        lcd.print("C H:");
        lcd.print(humidity);
        lcd.print("%");

        // Buzzer Logic for Smoke Detection
        if (smokeValue > 150) {
            Serial.println("ALERT!!! High Smoke Detected!");
            digitalWrite(BUZZER, HIGH);
            lcd.setCursor(10, 0);
            lcd.print(" HIGH!");
        } 
        else if (smokeValue > 100) {
            Serial.println("Warning!!! Moderate Smoke Detected!");
            digitalWrite(BUZZER, HIGH);
            lcd.setCursor(9, 0);
            lcd.print(" Medium");
        }
        else {
            Serial.println("Smoke Levels Normal");
            digitalWrite(BUZZER, LOW);
            lcd.setCursor(9, 0);
            lcd.print(" NORMAL");
        }
    }

    Serial.println("=================================");
    Serial.print("Smoke Level: "); Serial.println(smokeValue);
    Serial.print("Temperature: "); Serial.print(temperature); Serial.println("°C");
    Serial.print("Humidity: "); Serial.print(humidity); Serial.println("%");
    Serial.println("=================================");

    delay(2000); 
}
