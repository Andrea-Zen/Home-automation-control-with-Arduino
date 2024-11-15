// Importazione delle librerie necessarie
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Definizione dei pin dei moduli
#define PIR_PIN 2                  // Sensore di movimento PIR
#define DOOR_SENSOR_PIN 3          // Sensore di porta aperta
#define WINDOW_SENSOR_PIN 4        // Sensore di finestra
#define GAS_SENSOR_PIN A0          // Sensore di gas
#define SMOKE_SENSOR_PIN A1        // Sensore di fumo
#define RELAY_LIGHTS_PIN 5         // Relè per accendere le luci
#define RELAY_FAN_PIN 6            // Relè per accendere il ventilatore
#define RELAY_DOOR_PIN 7           // Relè per porta elettronica
#define TEMP_HUMIDITY_PIN 8        // Sensore di temperatura e umidità
#define LIGHT_SENSOR_PIN A2        // Sensore di luminosità
#define VIBRATION_SENSOR_PIN 9     // Sensore di vibrazione
#define RAIN_SENSOR_PIN A3         // Sensore di pioggia
#define SOUND_SENSOR_PIN 10        // Sensore di suono
#define WATER_SENSOR_PIN 11        // Sensore di rilevamento acqua
#define FAN_SPEED_CONTROL_PIN 12   // Controllo della velocità del ventilatore
#define RGB_LED_R_PIN 13           // Pin LED RGB Rosso
#define RGB_LED_G_PIN 14           // Pin LED RGB Verde
#define RGB_LED_B_PIN 15           // Pin LED RGB Blu
#define SERVO_PIN 16               // Servo motore per tende
#define LCD_SDA A4                 // SDA per LCD I2C
#define LCD_SCL A5                 // SCL per LCD I2C

// Inizializzazione componenti specifici
DHT dht(TEMP_HUMIDITY_PIN, DHT11);       // Inizializza il sensore DHT11
LiquidCrystal_I2C lcd(0x27, 16, 2);      // Inizializza LCD
Servo servoMotor;                        // Inizializza servo per tende

// Variabili di stato
bool motionDetected = false;
bool doorOpen = false;
bool windowOpen = false;
bool rainDetected = false;

void setup() {
    Serial.begin(9600);
    lcd.begin();
    dht.begin();
    servoMotor.attach(SERVO_PIN);

    // Definizione modalità pin
    pinMode(PIR_PIN, INPUT);
    pinMode(DOOR_SENSOR_PIN, INPUT);
    pinMode(WINDOW_SENSOR_PIN, INPUT);
    pinMode(GAS_SENSOR_PIN, INPUT);
    pinMode(SMOKE_SENSOR_PIN, INPUT);
    pinMode(RELAY_LIGHTS_PIN, OUTPUT);
    pinMode(RELAY_FAN_PIN, OUTPUT);
    pinMode(RELAY_DOOR_PIN, OUTPUT);
    pinMode(LIGHT_SENSOR_PIN, INPUT);
    pinMode(RAIN_SENSOR_PIN, INPUT);
    pinMode(SOUND_SENSOR_PIN, INPUT);
    pinMode(WATER_SENSOR_PIN, INPUT);
    pinMode(FAN_SPEED_CONTROL_PIN, OUTPUT);
    pinMode(RGB_LED_R_PIN, OUTPUT);
    pinMode(RGB_LED_G_PIN, OUTPUT);
    pinMode(RGB_LED_B_PIN, OUTPUT);

    // Messaggio di avvio su LCD
    lcd.print("Home Automation");
    delay(2000);
    lcd.clear();
}

void loop() {
    // **1. Rilevamento movimento e controllo luci**
    motionDetected = digitalRead(PIR_PIN);
    if (motionDetected) {
        digitalWrite(RELAY_LIGHTS_PIN, HIGH);
        lcd.setCursor(0, 0);
        lcd.print("Movimento: Rilevato ");
    } else {
        digitalWrite(RELAY_LIGHTS_PIN, LOW);
        lcd.setCursor(0, 0);
        lcd.print("Movimento: Assente  ");
    }

    // **2. Sensori di porta e finestra**
    doorOpen = digitalRead(DOOR_SENSOR_PIN);
    windowOpen = digitalRead(WINDOW_SENSOR_PIN);
    lcd.setCursor(0, 1);
    if (doorOpen) lcd.print("Porta Aperta     ");
    else lcd.print("Porta Chiusa     ");
    
    if (windowOpen) lcd.print("Fin. Aperta      ");
    else lcd.print("Fin. Chiusa      ");

    // **3. Sensore di temperatura e umidità**
    float temp = dht.readTemperature();
    float humidity = dht.readHumidity();
    Serial.print("Temperatura: "); Serial.print(temp); Serial.print("C ");
    Serial.print("Umidità: "); Serial.print(humidity); Serial.println("%");

    // **4. Sensore di gas e fumo**
    int gasLevel = analogRead(GAS_SENSOR_PIN);
    int smokeLevel = analogRead(SMOKE_SENSOR_PIN);
    if (gasLevel > 300 || smokeLevel > 300) {
        digitalWrite(RELAY_FAN_PIN, HIGH); // Accende il ventilatore
        Serial.println("Allarme: Gas/Fumo rilevato!");
    } else {
        digitalWrite(RELAY_FAN_PIN, LOW);
    }

    // **5. Controllo LED RGB per condizioni atmosferiche**
    if (temp < 20) {
        digitalWrite(RGB_LED_R_PIN, LOW);
        digitalWrite(RGB_LED_G_PIN, LOW);
        digitalWrite(RGB_LED_B_PIN, HIGH); // Blu (freddo)
    } else if (temp >= 20 && temp <= 25) {
        digitalWrite(RGB_LED_R_PIN, LOW);
        digitalWrite(RGB_LED_G_PIN, HIGH); // Verde (temperatura ideale)
        digitalWrite(RGB_LED_B_PIN, LOW);
    } else {
        digitalWrite(RGB_LED_R_PIN, HIGH); // Rosso (caldo)
        digitalWrite(RGB_LED_G_PIN, LOW);
        digitalWrite(RGB_LED_B_PIN, LOW);
    }

    // **6. Sensore di pioggia e chiusura automatica delle tende**
    rainDetected = digitalRead(RAIN_SENSOR_PIN);
    if (rainDetected) {
        servoMotor.write(0); // Chiude le tende
        Serial.println("Pioggia rilevata: tende chiuse.");
    } else {
        servoMotor.write(90); // Apre le tende
        Serial.println("Nessuna pioggia: tende aperte.");
    }

    // **7. Controllo della velocità del ventilatore in base alla temperatura**
    if (temp > 25) {
        analogWrite(FAN_SPEED_CONTROL_PIN, 255); // Velocità massima
    } else if (temp > 20) {
        analogWrite(FAN_SPEED_CONTROL_PIN, 128); // Velocità media
    } else {
        analogWrite(FAN_SPEED_CONTROL_PIN, 0); // Ventilatore spento
    }

    // **8. Controllo luci automatiche con sensore di luminosità**
    int lightLevel = analogRead(LIGHT_SENSOR_PIN);
    if (lightLevel < 500) {
        digitalWrite(RELAY_LIGHTS_PIN, HIGH); // Accende le luci
        Serial.println("Ambiente buio: luci accese.");
    } else {
        digitalWrite(RELAY_LIGHTS_PIN, LOW); // Spegne le luci
        Serial.println("Ambiente luminoso: luci spente.");
    }

    delay(1000); // Pausa di aggiornamento
}
