#include <AES.h>
#include <string.h>
#include <stdlib.h> 
#include "task6.h"
#include "task7.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "config.h"

AES128 aes128;
AES192 aes192;
AES256 aes256;


ESP8266WebServer server(80);  // Create a web server on port 80


void setup_wifi() {
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    // Define HTTP route to serve the file
    server.on("/download", HTTP_GET, []() {
        File file = LittleFS.open("/data.csv", "r");
        if (!file) {
            server.send(404, "text/plain", "File not found");
            return;
        }
        server.streamFile(file, "text/plain");
        file.close();
    });
    server.on("/", HTTP_GET, []() {
        server.send(200, "text/plain", "Hello, World! The server is working.");
    });

    server.begin();  // Start the web server
    Serial.println("Starting to serve.");
}

void setup_file_sytem(){
  if (!LittleFS.begin()) {
      Serial.println("LittleFS Mount Failed, trying to format...");
      LittleFS.format();
      if (!LittleFS.begin()) {
          Serial.println("Reformatting failed!");
          return;
      }
  }
  Serial.println("Setup successfull");
}

void run_tests(){
    compareAESPerformanceTask6(&aes128, &aes192, &aes256, 1000);
    delay(500); 
    compareAESPerformanceTask7(&aes128, &aes192, &aes256, 1000);
    delay(500); 
}

void setup() {
    delay(1000);
    Serial.begin(9600);
    setup_file_sytem();
    delay(500); 
    run_tests();
    setup_wifi();
}

void loop() {
    server.handleClient();  // Handle incoming client requests
}