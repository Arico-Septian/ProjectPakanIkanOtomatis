#define BLYNK_TEMPLATE_ID "TMPL61OqGvhvc"
#define BLYNK_TEMPLATE_NAME "Pakan Ikan Otomatis"
#define BLYNK_AUTH_TOKEN "VuDltJ8iRYndoLFppK_fG0uS6-L4ll4I"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>
#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>

// WiFi credentials
char ssid[] = "Samboru";        // Your WiFi SSID
char pass[] = "iloveyou";     // Your WiFi password

// RTC instance
RTC_DS3231 rtc;

// LCD instance (address: 0x27, size: 16x2)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Servo variables
Servo myServo;
int servoPin = 15;          // GPIO pin for the servo
bool servoMoving = false;   // Status to check if the servo is moving
unsigned long lastServoTime = 0; // Timestamp for the last servo movement
const unsigned long interval = 15000; // 15 seconds interval

// Blynk control variables
bool servoAutoEnabled = false;  // Servo auto-mode state (default: off)

// Function to print RTC time to LCD
void displayRTCTime() {
  DateTime now = rtc.now();  // Get current time
  char timeBuffer[17];       // Buffer for time string
  snprintf(timeBuffer, sizeof(timeBuffer), "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  
  lcd.setCursor(0, 0);  // Set cursor to the first line
  lcd.print("Time: ");
  lcd.print(timeBuffer);
}

// Function to print a message on the second line of the LCD
void displayMessage(const char* message) {
  lcd.setCursor(0, 1);  // Set cursor to the second line
  lcd.print(message);
  lcd.print("                ");  // Clear any remaining characters
}

// Blynk function to enable/disable servo auto-mode (V2)
BLYNK_WRITE(V1) {
  servoAutoEnabled = param.asInt();  // Get value from Blynk app (0 = off, 1 = on)
  if (servoAutoEnabled) {
    Serial.println("Servo auto-mode: ON");
    displayMessage("Servo: ON");
  } else {
    Serial.println("Servo auto-mode: OFF");
    displayMessage("Servo: OFF");
  }
}

void setup() {
  // Start serial communication
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");

  // Initialize Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Attach the servo to the specified pin with PWM range (500-2400 us)
  myServo.attach(servoPin, 500, 2400);
  myServo.write(90); // Set servo to the neutral position initially

  // Initialize RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Gunakan waktu kompilasi
  }

  // Initialize LCD
  lcd.init();
  lcd.backlight();  // Turn on LCD backlight
  displayRTCTime();
}

void loop() {
  // Handle Blynk events
  Blynk.run();

  // Update RTC time on LCD every second
  static unsigned long lastUpdateTime = 0;
  if (millis() - lastUpdateTime >= 1000) {
    displayRTCTime();
    lastUpdateTime = millis();
  }

  // Check if auto-mode is enabled and it's time to move the servo
  if (servoAutoEnabled && millis() - lastServoTime >= interval) {
    myServo.write(0);  // Move the servo to the "feeding" position
    displayMessage("Pakan diberikan");
    servoMoving = true;
    lastServoTime = millis();
    Serial.println("Servo moved to feeding position.");
  }

  // Return servo to neutral position after 3 seconds
  if (servoMoving && millis() - lastServoTime >= 3000) {
    myServo.write(90);  // Return servo to the neutral position
    servoMoving = false;
    displayMessage(" ");
    Serial.println("Servo returned to neutral position.");
  }
}