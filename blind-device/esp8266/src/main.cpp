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
byte row_pins[rows] = {D0, D1, D2, D3};
byte col_pins[cols] = {D4, D5, D6, D7};
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
int send_order(int orders[], int order_count) {
    if (!(orders[0] > 0)) return -1;
    if (WiFi.status() != WL_CONNECTED) return -1;

    WiFiClient client;
    HTTPClient http;
    String send_message = "{\"orders\":";

    for (int i = 0; i < order_count; i++) {
        send_message += "[";
        send_message += (char) order_count+'0';
        send_message += ",";
    }
    send_message += "]}";

    http.begin(client, server_url);

    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST("{\"test\":\"test message\"}");

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
                        orders[order_count] = order_number;
                        order_count++;
                    }

                    else if (key_value == 'C') {
                        order_count--;
                    }
                    
                    // http POST to server
                    else if (key_value == 'D') {
                        if (delay_count - millis() > http_delay) {
                            if (send_order(orders, order_count) == -1) Serial.println("send error");
                            else Serial.println("sended");

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