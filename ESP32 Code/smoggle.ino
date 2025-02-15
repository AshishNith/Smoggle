#include "WiFi.h"
#include "esp_camera.h"
#include <ArduinoJson.h>
#include <HTTPClient.h>

// WiFi Credentials
const char* ssid = "your_WiFi_SSID";
const char* password = "your_WiFi_PASSWORD";
const char* server_url = "http://your_server_ip:5000/analyze";  // Flask server URL

// Camera Pins (ESP32-CAM AI-Thinker module)
#define PWDN_GPIO     -1
#define RESET_GPIO    -1
#define XCLK_GPIO      0
#define SIOD_GPIO     26
#define SIOC_GPIO     27
#define Y9_GPIO       35
#define Y8_GPIO       34
#define Y7_GPIO       39
#define Y6_GPIO       36
#define Y5_GPIO       21
#define Y4_GPIO       19
#define Y3_GPIO       18
#define Y2_GPIO        5
#define VSYNC_GPIO    25
#define HREF_GPIO     23
#define PCLK_GPIO     22

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(1000);
    }
    Serial.println("\nWiFi connected!");
  
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO;
    config.pin_d1 = Y3_GPIO;
    config.pin_d2 = Y4_GPIO;
    config.pin_d3 = Y5_GPIO;
    config.pin_d4 = Y6_GPIO;
    config.pin_d5 = Y7_GPIO;
    config.pin_d6 = Y8_GPIO;
    config.pin_d7 = Y9_GPIO;
    config.pin_xclk = XCLK_GPIO;
    config.pin_pclk = PCLK_GPIO;
    config.pin_vsync = VSYNC_GPIO;
    config.pin_href = HREF_GPIO;
    config.pin_sccb_sda = SIOD_GPIO;
    config.pin_sccb_scl = SIOC_GPIO;
    config.pin_pwdn = PWDN_GPIO;
    config.pin_reset = RESET_GPIO;
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;
  
    if (psramFound()) {
        config.frame_size = FRAMESIZE_QVGA;
        config.jpeg_quality = 10;
        config.fb_count = 2;
    } else {
        config.frame_size = FRAMESIZE_QVGA;
        config.jpeg_quality = 12;
        config.fb_count = 1;
    }

    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        Serial.println("Camera initialization failed");
        return;
    }

    Serial.println("Camera ready!");
}

void loop() {
    WiFiClient client;
    HTTPClient http;
  
    camera_fb_t * fb = esp_camera_fb_get();
    if (!fb) {
        Serial.println("Camera capture failed");
        return;
    }
  
    http.begin(client, server_url);
    http.addHeader("Content-Type", "image/jpeg");
  
    int httpResponseCode = http.POST(fb->buf, fb->len);
    if (httpResponseCode > 0) {
        Serial.println("Image sent successfully!");
        String response = http.getString();
        Serial.println(response);
    } else {
        Serial.println("Error sending image");
    }

    esp_camera_fb_return(fb);
    http.end();
  
    delay(5000); // Capture every 5 seconds
}
