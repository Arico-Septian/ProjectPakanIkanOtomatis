// Blynk Configuration
#define BLYNK_TEMPLATE_ID "TMPL61OqGvhvc"
#define BLYNK_TEMPLATE_NAME "Pakan Ikan Otomatis"
#define BLYNK_AUTH_TOKEN "VuDltJ8iRYndoLFppK_fG0uS6-L4ll4I"

#include <BlynkSimpleEsp32.h>
#include <WiFi.h>
#include <WebServer.h>
#include <WiFiClient.h>
#include "src/OV2640.h"

// Select camera model
#define CAMERA_MODEL_AI_THINKER
#include "camera_pins.h"

// WiFi Credentials
#define SSID1 "KOST BERSAMA"
#define PWD1 "JOKOWI5D"

// Camera object
OV2640 cam;
WebServer server(80);

// Pin for controlling the LED Flash (Use any available GPIO pin, for example, GPIO 4)
#define FLASH_PIN 4

// HTTP Header for MJPEG stream
const char HEADER[] = "HTTP/1.1 200 OK\r\n"
                      "Access-Control-Allow-Origin: *\r\n"
                      "Content-Type: multipart/x-mixed-replace; boundary=123456789000000000000987654321\r\n";
const char BOUNDARY[] = "\r\n--123456789000000000000987654321\r\n";
const char CTNTTYPE[] = "Content-Type: image/jpeg\r\nContent-Length: ";
const int hdrLen = strlen(HEADER);
const int bdrLen = strlen(BOUNDARY);
const int cntLen = strlen(CTNTTYPE);

// Function to handle MJPEG stream
void handle_jpg_stream(void) {
  char buf[32];
  int s;
  WiFiClient client = server.client();

  client.write(HEADER, hdrLen);
  client.write(BOUNDARY, bdrLen);

  while (true) {
    if (!client.connected()) break;
    cam.run();
    s = cam.getSize();
    client.write(CTNTTYPE, cntLen);
    sprintf(buf, "%d\r\n\r\n", s);
    client.write(buf, strlen(buf));
    client.write((char *)cam.getfb(), s);
    client.write(BOUNDARY, bdrLen);
  }
}

// Function to handle single JPG capture
void handle_jpg(void) {
  WiFiClient client = server.client();

  cam.run();
  if (!client.connected()) return;

  const char JHEADER[] = "HTTP/1.1 200 OK\r\n"
                         "Content-disposition: inline; filename=capture.jpg\r\n"
                         "Content-type: image/jpeg\r\n\r\n";
  client.write(JHEADER, strlen(JHEADER));
  client.write((char *)cam.getfb(), cam.getSize());
}

// Handle 404
void handleNotFound() {
  String message = "Server is running!\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  server.send(200, "text/plain", message);
}

// Handle Blynk Button press for Flash
BLYNK_WRITE(V2) { // Virtual Pin 2 for Flash toggle
  int pinValue = param.asInt();
  if (pinValue == 1) {
    digitalWrite(FLASH_PIN, HIGH);  // Turn on flash
    Serial.println("Flash On");
  } else {
    digitalWrite(FLASH_PIN, LOW);   // Turn off flash
    Serial.println("Flash Off");
  }
}

// Setup function
void setup() {
  Serial.begin(115200);

  // Initialize camera
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  // Frame parameters
  config.frame_size = FRAMESIZE_QVGA;
  config.jpeg_quality = 12;
  config.fb_count = 2;

  cam.init(config);

  // Initialize Flash pin
  pinMode(FLASH_PIN, OUTPUT);
  digitalWrite(FLASH_PIN, LOW);  // Ensure flash is off initially

  // Initialize WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID1, PWD1);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println(F("\nWiFi connected"));
  Serial.print(F("IP Address: "));
  Serial.println(WiFi.localIP());
  Serial.print(F("Stream Link: http://"));
  Serial.print(WiFi.localIP());
  Serial.println(F("/mjpeg/1"));

  // Initialize Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, SSID1, PWD1);

  // Setup server routes
  server.on("/mjpeg/1", HTTP_GET, handle_jpg_stream);
  server.on("/jpg", HTTP_GET, handle_jpg);
  server.onNotFound(handleNotFound);
  server.begin();
}

// Main loop
void loop() {
  server.handleClient();
  Blynk.run();
}