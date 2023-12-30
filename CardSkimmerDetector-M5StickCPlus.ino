#include <M5StickCPlus.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>

int scanTime = 10; // Duration for a BLE scan
String knownSkimmerNames[] = {"HC-03", "HC-05", "HC-06"}; // Known skimmer module names
std::vector<String> detectedDevices; // List to hold detected devices
std::vector<String> detectedSkimmers; // List to hold detected skimmers
int maxDevicesDisplayed = 12; // Adjust based on your display size
int maxDevicesStored = 12; // Adjust based on desired history length and memory constraints

// Function prototypes
void updateDisplay();
void displaySkimmers();

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
        String deviceInfo = "Name: " + String(advertisedDevice.getName().c_str()) + ", Addr: " + String(advertisedDevice.getAddress().toString().c_str());
        
        // Check if device name matches any known skimmer names
        bool isSkimmer = false;
        for (String skimmerName : knownSkimmerNames) {
            if (advertisedDevice.getName().find(skimmerName.c_str()) != std::string::npos) {
                detectedSkimmers.push_back(deviceInfo); // Add to skimmer list
                isSkimmer = true;
                displaySkimmers(); // Display only skimmers
                return; // Exit early to avoid overwriting the display with normal devices
            }
        }
        
        if (!isSkimmer) {
            if (detectedDevices.size() >= maxDevicesStored) {
                // Remove the oldest device to make room for the new one
                detectedDevices.erase(detectedDevices.begin());
            }
            detectedDevices.push_back(deviceInfo); // Add to general device list
            updateDisplay(); // Update display with all detected devices
        }
    }
};

void setup() {
    M5.begin();
    Serial.begin(115200);
    BLEDevice::init("");
    BLEScan* pBLEScan = BLEDevice::getScan();
    pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
    pBLEScan->setActiveScan(true); // Active scan uses more power, but gets more information
    pBLEScan->start(scanTime, true); // Start continuous scanning
}

void loop() {
    delay(200); // Reduced delay for responsive button detection
    M5.update(); // Update the state of all buttons
    
    // Check if Button A is pressed
    if (M5.BtnA.wasPressed()) {
        BLEScan* pBLEScan = BLEDevice::getScan();
        pBLEScan->clearResults(); // Clear previous scan results
        pBLEScan->start(scanTime, true); // Start another scan
    }
}

void updateDisplay() {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 0);
    // Display the most recent devices up to the maxDevicesDisplayed
    for (int i = std::max(0, (int)detectedDevices.size() - maxDevicesDisplayed); i < detectedDevices.size(); ++i) {
        M5.Lcd.println(detectedDevices[i]);
    }

    // Add the "Press A to scan" message at the bottom
    M5.Lcd.setCursor(0, M5.Lcd.height() - 16); // Adjust the Y position as needed
    M5.Lcd.println("Press A to scan");
}

void displaySkimmers() {
    M5.Lcd.fillScreen(RED);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.println("Alert: Skimmer Detected!");
    for (String& skimmer : detectedSkimmers) {
        M5.Lcd.println(skimmer);
    }

    // Checking for Button B to reset to scan mode
    while(true) {
        delay(200); // Delay for button check loop
        M5.update(); // Update button state
        
        // If Button B is pressed, clear skimmers and return to normal scanning mode
        if (M5.BtnB.wasPressed()) {
            detectedSkimmers.clear(); // Clear the list of detected skimmers
            updateDisplay(); // Return to normal display
            return; // Exit the function to resume scanning
        }
    }
}