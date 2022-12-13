#include <ESP8266WiFi.h>
#include <espnow.h>

struct order_data {
    int order_number;
};

void on_data_recv(uint8_t *mac_addr, uint8_t *recv_data, uint8_t len) {
    struct order_data data;

    memcpy(&data, recv_data, sizeof(order_data));

    Serial.println(data.order_number);
}

void setup() {
    Serial.begin(9600);

    WiFi.mode(WIFI_STA);

    if (esp_now_init() != 0) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
    esp_now_register_recv_cb(on_data_recv);
}