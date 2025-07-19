#include "C_Connection.h"

ESPNowData Connection::data = {false, false, false, false};

volatile bool Connection::statusData = false;

Connection::Connection() {}

void Connection::espNowInit()
{

    WiFi.mode(WIFI_STA);
    Serial.print("MAC Address: ");
    Serial.println(WiFi.macAddress());

    if (esp_now_init() != ESP_OK)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    esp_now_register_send_cb(OnDataSent);
    esp_now_register_recv_cb(OnDataRecv);

    peerInfo.channel = 0;
    peerInfo.encrypt = false;
}

void Connection::setPeer(const uint8_t macAddress[6])
{
    memcpy(peerInfo.peer_addr, macAddress, 6);
    if (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
        Serial.println("Failed to add peer!");
        return;
    }
}

void Connection::OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    statusData = status == ESP_NOW_SEND_SUCCESS ? true : false;
}

void Connection::OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len)
{
    memcpy(&data, incomingData, sizeof(data));
}

void Connection::resetData()
{
    memset(&data, 0, sizeof(data));
}

bool Connection::sendData(const uint8_t macAddress[6], ESPNowData toSendData)
{
    esp_err_t result = esp_now_send(macAddress, (uint8_t *)&toSendData, sizeof(toSendData));
    return statusData ? true : false;
}

bool Connection::getConnection()
{
    return this->statusData;
}

ESPNowData Connection::getReceivedData()
{
    return this->data;
}
