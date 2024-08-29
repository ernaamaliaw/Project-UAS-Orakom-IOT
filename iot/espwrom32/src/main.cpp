#include <Arduino.h>
#include <SoftwareSerial.h>
#include <WiFiManager.h>
// #include <ESP8266HTTPClient.h>
#include <HTTPClient.h>

#define pinTx 12
#define pinRx 14

SoftwareSerial serialPort;
WiFiManager wm;

String sendingData;

bool postDataSend = false;  // Flag untuk sendtoHTTPS

unsigned long currentMillis;
unsigned long prevMillis = 0;

String serverName = "https://tugas-iot.demo-web.my.id/add.php?";

void setup() {
  Serial.begin(115200);
  serialPort.begin(115200,SWSERIAL_8N1,pinRx,pinTx,false);
  if (!serialPort){
    Serial.println("Invalid SoftwareSerial pin configuration, check config"); 
    while (1) { // Don't continue with invalid configuration
      delay (1000);
      Serial.print('.');
    }
  }
  WiFi.mode(WIFI_STA);
  bool res;
  res = wm.autoConnect("IOT_ESP32");
}

void send() {

  while (postDataSend)
  {
    
    if(WiFi.status()== WL_CONNECTED){
      Serial.print("kirim");
      HTTPClient http;

      String type = "satisfied";

      String serverPath = serverName + "type=" + sendingData;

      Serial.print(serverPath);

      http.begin(serverPath.c_str());

      int httpResponseCode = http.GET();

      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        postDataSend = false;
      } else {
        Serial.print("Error code: ");
        postDataSend = false;
      }
      // Free resources
      sendingData = "";
      http.end();

    }
    postDataSend = false;
  }
}

void loop() {
  currentMillis = millis();
  while(serialPort.available()){
    char data;
    data = serialPort.read();

    Serial.write(data);

    // sendingData = data;
    sendingData += data;


    prevMillis = currentMillis;
    postDataSend = true;
  }

  // if ((currentMillis - prevMillis >= 5000) && (sendingData.length() > 0))

  if(sendingData == "satisfied" || sendingData == "very_satisfied" || sendingData == "less_satisfied")
  {
    if(WiFi.status()== WL_CONNECTED){
      Serial.print("kirim");
      HTTPClient http;

      String type = "satisfied";

      String serverPath = serverName + "type=" + sendingData;

      Serial.print(serverPath);

      http.begin(serverPath.c_str());

      int httpResponseCode = http.GET();

      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        postDataSend = false;
      } else {
        Serial.print("Error code: ");
        postDataSend = false;
      }
      // Free resources
      
      http.end();

    }

    
    postDataSend = false;
  }

  sendingData = "";
}

