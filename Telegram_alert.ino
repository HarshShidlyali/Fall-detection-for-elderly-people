#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

const char* ssid = "Shidlyali_F_Floor_2.4GHz";
const char* password = "Shidlyali*2025#";

// Telegram Bot Configuration
const String BOTtoken = "8584168475:AAG8lYazrM8mrz5qn5zw6HDJpW_7TeMYEzU";
const String CHAT_ID = "1640526464";

void setup() {
  Serial.begin(115200);
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  
  // Send startup message
  sendTelegramAlert("ESP32 Started!");
}

void loop() {
  // Example: Send alert every 60 seconds
  delay(60000);
  sendTelegramAlert("🔄 Regular status update - System running normally");
}

void sendTelegramAlert(String message) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;
    client.setInsecure(); // Use for simplicity, not recommended for production
    
    HTTPClient https;
    
    // Create Telegram API URL
    String url = "https://api.telegram.org/bot" + BOTtoken + "/sendMessage";
    
    https.begin(client, url);
    https.addHeader("Content-Type", "application/json");
    
    // Create JSON payload
    String payload = "{\"chat_id\":\"" + CHAT_ID + "\",\"text\":\"" + message + "\"}";
    
    // Send POST request
    int httpResponseCode = https.POST(payload);
    
    if (httpResponseCode > 0) {
      String response = https.getString();
      Serial.println("Message sent successfully");
      Serial.println("Response: " + response);
    } else {
      Serial.println("Error sending message: " + String(https.errorToString(httpResponseCode)));
    }
    
    https.end();
  } else {
    Serial.println("WiFi not connected");
  }
}
