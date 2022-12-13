#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <Keypad.h>


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
byte row_pins[rows] = {16, 5, 4, 0};
byte col_pins[cols] = {2, 14, 12, 13};
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
int send_order(int order) {
    if (WiFi.status() != WL_CONNECTED) return -1;

    WiFiClient client;
    HTTPClient http;
    String send_message = "{\"orders\":";

    String server_path = server_url+String(order);

    http.begin(client, server_path);
  
    int httpResponseCode = http.GET();
    Serial.print("Sent to :");
    Serial.println(server_path);
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
    Serial.println("hello world!");
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
                        send_order(order_number);
                        order_number = 0;
                    }

                    else if (key_value == 'C') {
                        send_order(-1);
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