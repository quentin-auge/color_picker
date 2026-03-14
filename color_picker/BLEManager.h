#pragma once

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#include "pins.h"

#define BLE_DEVICE_NAME "ColorPicker"
#define BLE_SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define BLE_CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

class BLEManager {
public:
    void setup();
    bool hasColorUpdate();
    uint8_t getR();
    uint8_t getG();
    uint8_t getB();

private:
    BLEServer* pServer = nullptr;
    BLEService* pService = nullptr;
    BLECharacteristic* pRgbCharacteristic = nullptr;

    class ServerCallbacks : public BLEServerCallbacks {
        public:
            void onConnect(BLEServer* pServer) override;
            void onDisconnect(BLEServer* pServer) override;
    };

    class RgbCallbacks : public BLECharacteristicCallbacks {
        public:
            RgbCallbacks();
            void onWrite(BLECharacteristic* pCharacteristic) override;
            bool hasUpdate();
            uint32_t getColor();

        private:
            uint8_t _r = 0;
            uint8_t _g = 0;
            uint8_t _b = 0;
            bool _hasUpdate = false;
    };

    RgbCallbacks* pRgbCallbacks = nullptr;
};
