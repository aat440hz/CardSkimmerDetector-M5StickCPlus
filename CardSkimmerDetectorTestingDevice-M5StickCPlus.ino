#include <M5StickCPlus.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "esp_system.h"  // Include the ESP system header for low-level control

// Your BLE UUIDs
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

void setup() {
  // Initialize the M5StickC Plus
  M5.begin();
  M5.Lcd.fillScreen(RED);
  Serial.begin(115200);

  // Change MAC here using ESP-IDF
  uint8_t newMAC[6] = {0x20, 0x24, 0x12, 0x31, 0x09, 0x04}; // Replace XX with desired values
  esp_base_mac_addr_set(newMAC);  // Set new MAC address (This is a placeholder and might not work as expected without proper setup)

  // Initialize BLE Device with a name
  BLEDevice::init("JBL Go 3"); 

  // Create the BLE Server
  BLEServer *pServer = BLEDevice::createServer();

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pService->createCharacteristic(
      CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ |
      BLECharacteristic::PROPERTY_WRITE
    );

  // Start the service
  pService->start();

  // Start advertising the BLE service
  pServer->getAdvertising()->start();
  Serial.println("Waiting a client connection to notify...");
}

void loop() {
  // Implement any additional functionality or leave it empty
  delay(1000); // Dummy delay
}
