#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <regex>

// Undefine min and max macros to avoid conflicts
#undef min
#undef max

#include <M5StickCPlus.h> // Include after undefining macros

int scanTime = 10; // Duration for a BLE scan
String knownSkimmerNames[] = {"HC-03", "HC-05", "HC-06", "HC-08", "RNBT"}; // Known skimmer module names
std::vector<String> detectedDevices; // List to hold detected devices
std::vector<String> detectedSkimmers; // List to hold detected skimmers
int maxDevicesDisplayed = 12; // Adjust based on your display size
int maxDevicesStored = 12; // Adjust based on desired history length and memory constraints

// Function prototypes
void updateDisplay();
void displaySkimmers();

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
        String deviceInfo = "Name: " + String(advertisedDevice.getName().c_str()) +
                            ", Addr: " + String(advertisedDevice.getAddress().toString().c_str());
        
        // Regular expression to match "RNBT-xxxx" pattern (xxxx being any alphanumeric characters)
        std::regex rnbtPattern("RNBT-[A-Za-z0-9]{4}");

        // Check for RN modules with the prefix 00:06:66 in the MAC address
        String macPrefix = "00:06:66";
        String deviceAddress = String(advertisedDevice.getAddress().toString().c_str());
        bool isRnSkimmer = deviceAddress.startsWith(macPrefix);

 // Assume MAC format is YY:YY:MM:DD:XX:XX for manufacturing date check
        int year1 = (deviceAddress.charAt(0) - '0') * 10 + (deviceAddress.charAt(1) - '0');
        int year2 = (deviceAddress.charAt(3) - '0') * 10 + (deviceAddress.charAt(4) - '0');
        int month = (deviceAddress.charAt(6) - '0') * 10 + (deviceAddress.charAt(7) - '0');
        int day = (deviceAddress.charAt(9) - '0') * 10 + (deviceAddress.charAt(10) - '0');
        int year = year1 * 100 + year2;

        // Update to the current year as the upper limit for year check
        int currentYear = 2024; // Replace 20XX with the current year or fetch dynamically

        // Convert the device name to std::string for regex matching
        std::string devName = advertisedDevice.getName();

        // Check if device name matches any known skimmer names or the RNBT pattern
        bool isSkimmer = false;
        for (String skimmerName : knownSkimmerNames) {
            if (devName.find(skimmerName.c_str()) != std::string::npos || 
                std::regex_search(devName, rnbtPattern) || 
                isRnSkimmer || 
                (year >= 2013 && year <= currentYear && month >= 1 && month <= 12 && day >= 1 && day <= 31)) {
                detectedSkimmers.push_back(deviceInfo); // Add to skimmer list
                isSkimmer = true;
                displaySkimmers(); // Display only skimmers
                return; // Exit early to avoid overwriting the display with normal devices
            }
        }

        // If not a skimmer, add to general device list
        if (!isSkimmer) {
            if (detectedDevices.size() >= maxDevicesStored) {
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
