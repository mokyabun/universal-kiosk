#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <Keypad.h>

#include "pins_arduino.h"

/*
Constant variables
*/
// Connection
const char* ssid = "<WIFI SSID>";
const char* password = "<WIFI PASSWORD>";

const char* server_url = "<SERVER URL>";

const int wifi_reconnect_delay = 1000;  // 1 second delay
const int http_delay = 10000;  // 10 second delay

// Keypad
const byte rows = 4;
const byte cols = 4;
byte row_pins[rows] = {D3, D2, D1, D0};
byte col_pins[cols] = {D7, D6, D4, D3};
char keys[rows][cols] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

/**
 * @brief send order data to server
 * 
 * @param orders
 * @return int 
 */
int send_order(int orders[]) {
    if (!(orders[0] > 0)) return -1;
    if (WiFi.status() != WL_CONNECTED) return -1;

    WiFiClient client;
    HTTPClient http;

    http.begin(client, server_url);

    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST("{}");

    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

    http.end();

    return 0;
}

/**
 * @brief setup function
 * 
 */
void setup() {
    Serial.begin(9600);
    
    // Connect WIFI
    WiFi.begin(ssid, password);
    Serial.print("Connecting to ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED) {
        delay(wifi_reconnect_delay);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("Connected to WIFI");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

/**
 * @brief main loop function
 * 
 */
void loop() {
    static unsigned long delay_count = 0;
    static Keypad keypad = Keypad(makeKeymap(keys), row_pins, col_pins, rows, cols);
    static int orders[100];
    static int order_count = 0;
    static int order_number = 0;

    if (keypad.getKeys()) {
        for (int i = 0; i < LIST_MAX; i++) {
            if (keypad.key[i].stateChanged) {
                if (keypad.key[i].kstate == RELEASED) {
                    const char key_value = keypad.key[i].kchar;
                    
                    if (key_value == 'A') {
                        if (order_number < 10) order_number = 0;
                        else order_number %= 10;
                    }
                    
                    else if (key_value == 'B') {
                        order_count++;
                    }

                    else if (key_value == 'C') {
                        order_count--;
                    }
                    
                    // http POST to server
                    else if (key_value == 'D') {
                        if (delay_count - millis() > http_delay) {
                            send_order(orders);

                            delay_count = millis();
                        }
                    }

                    else if (key_value == '*') ;
                    
                    else if (key_value == '#') ;

                    else {
                        int key_num = key_value - '0';

                        if (order_number < 100) {
                            order_number *= 10;
                            order_number += key_num;
                        }
                    }
                }
            }
        }
    }
}