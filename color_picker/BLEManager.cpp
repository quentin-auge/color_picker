#include "BLEManager.h"

void BLEManager::setup() {
    BLEDevice::init(BLE_DEVICE_NAME);
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new ServerCallbacks());

    pService = pServer->createService(BLE_SERVICE_UUID);

    pRgbCharacteristic = pService->createCharacteristic(
        BLE_RGB_CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_WRITE_NR
    );
    pRgbCallbacks = new RgbCallbacks();
    pRgbCharacteristic->setCallbacks(pRgbCallbacks);

    pRtttlCharacteristic = pService->createCharacteristic(
        BLE_RTTTL_CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_WRITE_NR
    );
    pRtttlCallbacks = new RtttlCallbacks();
    pRtttlCharacteristic->setCallbacks(pRtttlCallbacks);

    pService->start();

    BLEAdvertising* pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(BLE_SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06);
    pAdvertising->setMinPreferred(0x12);

    BLEDevice::startAdvertising();

    Serial.println("BLE initialized and advertising");
}

bool BLEManager::hasColorUpdate() {
    return pRgbCallbacks->hasUpdate();
}

uint8_t BLEManager::getR() {
    return (pRgbCallbacks->getColor() >> 16) & 0xFF;
}

uint8_t BLEManager::getG() {
    return (pRgbCallbacks->getColor() >> 8) & 0xFF;
}

uint8_t BLEManager::getB() {
    return pRgbCallbacks->getColor() & 0xFF;
}

bool BLEManager::hasRtttlUpdate() {
    return pRtttlCallbacks->hasUpdate();
}

const char* BLEManager::getRtttl() {
    return pRtttlCallbacks->getRtttl();
}

void BLEManager::ServerCallbacks::onConnect(BLEServer* pServer) {
    Serial.println("BLE client connected");
}

void BLEManager::ServerCallbacks::onDisconnect(BLEServer* pServer) {
    BLEDevice::startAdvertising();
}

BLEManager::RgbCallbacks::RgbCallbacks() {}

void BLEManager::RgbCallbacks::onWrite(BLECharacteristic* pCharacteristic) {
    String value = pCharacteristic->getValue();
    if (value.length() >= 3) {
        _r = value[0];
        _g = value[1];
        _b = value[2];
        _hasUpdate = true;
    }
}

bool BLEManager::RgbCallbacks::hasUpdate() {
    if (_hasUpdate) {
        _hasUpdate = false;
        return true;
    }
    return false;
}

uint32_t BLEManager::RgbCallbacks::getColor() {
    return (_r << 16) | (_g << 8) | _b;
}

BLEManager::RtttlCallbacks::RtttlCallbacks() {}

void BLEManager::RtttlCallbacks::onWrite(BLECharacteristic* pCharacteristic) {
    String value = pCharacteristic->getValue();
    if (value.length() > 0 && value.length() <= RTTTL_BUFFER_SIZE) {
        memset(_rtttlBuffer, 0, sizeof(_rtttlBuffer));
        for (size_t i = 0; i < value.length(); i++) {
            _rtttlBuffer[i] = value[i];
        }
        _rtttlBuffer[value.length()] = '\0';
        _hasUpdate = true;
        Serial.println("Received RTTTL via BLE");
    }
}

bool BLEManager::RtttlCallbacks::hasUpdate() {
    if (_hasUpdate) {
        _hasUpdate = false;
        return true;
    }
    return false;
}

const char* BLEManager::RtttlCallbacks::getRtttl() {
    return _rtttlBuffer;
}
