#include <AES.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "task6.h"
#include "task7.h"
#include "task8.h"

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
    server.on("/task8", HTTP_GET, []() {
        File file = LittleFS.open("/task8.csv", "r");
        if (!file) {
            server.send(404, "text/plain", "File not found");
            return;
        }
        server.streamFile(file, "text/plain");
        file.close();
    });
    server.on("/task7", HTTP_GET, []() {
        File file = LittleFS.open("/task7.csv", "r");
        if (!file) {
            server.send(404, "text/plain", "File not found");
            return;
        }
        server.streamFile(file, "text/plain");
        file.close();
    });
    server.on("/task6", HTTP_GET, []() {
        File file = LittleFS.open("/task6.csv", "r");
        if (!file) {
            server.send(404, "text/plain", "File not found");
            return;
        }
        server.streamFile(file, "text/plain");
        file.close();
    });
    server.begin();
    Serial.println("Starting to serve.");
}

void setup_file_sytem() {
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

void run_tests() {
    // compareAESPerformanceTask6(&aes128, &aes192, &aes256, 1000);
    // delay(500);
    // compareAESPerformanceTask7(&aes128, &aes192, &aes256, 1000);
    // delay(500);
    performBenchmark();
}

void setup() {
    delay(1000);
    Serial.begin(9600);
    Serial.println();
    setup_file_sytem();
    delay(500);
    run_tests();
    delay(500);
    setup_wifi();
    delay(100);
}

void loop() {
    server.handleClient();
    yield();
}