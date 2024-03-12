# CardSkimmerDetector

CardSkimmerDetector is a sophisticated, open-source tool developed with the primary aim of assisting law enforcement officers and security experts in identifying and mitigating the threat posed by Bluetooth Low Energy (BLE) skimming devices. Engineered atop the versatile M5StickC Plus platform, this innovative device is adept at recognizing potential skimmers through their distinctive device names and unique MAC address prefixes, providing users with a proactive defense mechanism against digital theft.

## Features

- **Comprehensive BLE Scanning:** Automatically scans for and identifies nearby BLE devices, employing advanced algorithms to differentiate potential threats from benign devices.
- **Skimmer Identification:** Utilizes a database of known skimmer module names and MAC address patterns to accurately pinpoint skimming devices.
- **Real-Time Alerts:** Instantly alerts users upon the detection of a skimmer, displaying critical information about the threat on the M5StickC Plus screen for immediate action.
- **User-Initiated Scans:** Offers manual control over scanning operations, allowing users to initiate scans at their discretion for added security.
- **Extensive Customizability:** Provides various customization options, including adjustable scan durations, the number of devices displayed, and the length of the detection history, tailoring the tool to specific operational needs.

## Usage

1. **Library Installation:** Begin by installing the necessary libraries detailed in the Arduino sketch to ensure the device functions correctly.
2. **Sketch Upload:** Upload the provided sketch to the M5StickC Plus device to equip it with the capabilities to detect skimming devices.
3. **Device Activation:** Turn on the device to initiate automatic scanning for BLE devices. The device will continually scan for and analyze nearby Bluetooth signals.
4. **Skimmer Detection:** Should the device identify a known skimmer module, it will immediately trigger an alert and display the pertinent details on the screen.
5. **Scan Reset:** Press Button B to clear any active alerts and reset the device to its normal scanning mode.
6. **Manual Scanning:** Use Button A to manually start a new scanning cycle at any time, enhancing vigilance and response to potential threats.

## Known Skimmer Module Names

The tool is pre-loaded with a list of commonly known skimmer module names. Users are encouraged to periodically update this list to incorporate new skimmers as they are identified. Modify the `knownSkimmerNames` array within the sketch to adjust the detection capabilities of the device.

## Customization

The CardSkimmerDetector is designed for adaptability, allowing users to tailor its operation through various parameters defined within the sketch. Adjust the scan time, display settings, and device history to suit your specific operational requirements and constraints.

## Disclaimer

This tool is provided strictly for educational purposes and to assist law enforcement and security professionals in the detection of BLE skimming devices. It is imperative to use this tool in compliance with all applicable laws and guidelines. While the CardSkimmerDetector aims to provide accurate detection capabilities, users should be aware of the potential for false positives and the impossibility of guaranteeing the identification of all skimming devices.

## Contributions

We welcome contributions from the community to further enhance the CardSkimmerDetector's functionality and detection capabilities. Please feel free to fork the repository, implement your modifications, and submit pull requests to share your improvements with the community.

## License

The CardSkimmerDetector project is licensed under the MIT License, promoting open-source collaboration and sharing of knowledge and technology in the fight against digital skimming threats.
