#include <ESP8266WiFi.h>
#include <espnow.h>
#include <Keypad.h>

/* Constants */
// Recv MAC address
uint8_t MAC_address[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

// Delays
const unsigned long send_delay = 3000;

struct order_data {
    int order_number;
};

/* Functions */
void on_data_sent(uint8_t *mac_addr, uint8_t send_status) {
    Serial.print("Order data send status: ");
    if (send_status == 0) Serial.println("Success");
    else Serial.println("Fail");
}

void setup() {
    Serial.begin(9600);

    WiFi.mode(WIFI_STA);

    if (esp_now_init() != 0) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
    esp_now_register_send_cb(on_data_sent);

    esp_now_add_peer(MAC_address, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}

void loop() {
    // Keypad
    static const byte rows = 4;
    static const byte cols = 4;
    static byte row_pins[rows] = {16, 5, 4, 0};
    static byte col_pins[cols] = {2, 14, 12, 13};
    static char keys[rows][cols] = {
        {'1','2','3','A'},
        {'4','5','6','B'},
        {'7','8','9','C'},
        {'*','0','#','D'}
    };
    static Keypad keypad = Keypad(makeKeymap(keys), row_pins, col_pins, rows, cols);

    // Order number
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
                        struct order_data data = {order_number};
                        esp_now_send(MAC_address, (uint8 *) &data, sizeof(order_data));
                        order_number = 0;
                    }

                    else if (key_value == 'C') {
                        struct order_data data = {-1};
                        esp_now_send(MAC_address, (uint8 *) &data, sizeof(order_data));
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