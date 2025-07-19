#ifndef CONNECTION_H
#define CONNECTION_H

#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

#include "H_StructConstants.h"

class Connection
{
private:
    esp_now_peer_info_t peerInfo;
    static ESPNowData data;
    static volatile bool statusData;

public:
    Connection();
    void espNowInit();
    void setPeer(const uint8_t macAddress[6]);
    static void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
    static void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);
    void resetData();
    bool sendData(const uint8_t macAddress[6], ESPNowData toSendData);
    bool getConnection();
    ESPNowData getReceivedData();
};

#endif