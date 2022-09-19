#include <Arduino.h>
  #include <WiFi.h>
  #include <ESPAsyncWebServer.h>
  #include <SPIFFS.h>
  #include <AsyncTCP.h>
  #include <AsyncElegantOTA.h>


AsyncWebServer server(80);


String STM_Data = "m 20 0 100 5 200 10 300 15 400 20 500 25 600 30 490 30 350 29 320 28 300 27 200 22 100 20 20 19";
  
String data_from_stm;

void setup()
{
  Serial.begin(115200);
  Serial2.begin(115200);

  Serial2.println("Serial 2 init success");

  if (!SPIFFS.begin())
  {
    Serial2.println("An Error has occurred while mounting SPIFFS");
    return;
  }
 // SPIFFS.begin();
  WiFi.mode(WIFI_AP);
  WiFi.softAP("My Portal");
  

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              request->send(SPIFFS, "/index.html");
            });

  server.on("/wotafak", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send_P(200, "text/plain", data_from_stm.c_str()); });
            
  AsyncElegantOTA.begin(&server);
  server.begin();
   
  Serial2.println("Server started");
}

void loop() {


  if(Serial.available() > 0)
  {
    data_from_stm = Serial.readStringUntil('#');
    Serial2.println("Data from stm32 received:");
    Serial2.println(data_from_stm);
  }
  // put your main code here, to run repeatedly:
}