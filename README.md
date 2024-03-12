# CardSkimmerDetector

The CardSkimmerDetector is an open-source tool designed for law enforcement and security professionals to detect Bluetooth Low Energy (BLE) skimming devices. It is built using the M5StickC Plus platform and can help identify skimmers by known device names and MAC address prefixes.

## Features

- Scans for nearby BLE devices.
- Detects known skimmer module names.
- Displays detected devices on the M5StickC Plus screen.
- Alerts when a skimmer is detected.

## Usage

1. **Install the required libraries** listed in the Arduino sketch.
2. **Upload the sketch** to your M5StickC Plus device.
3. **Power on the device**, and it will start scanning for BLE devices.
4. If a known skimmer module name is detected, an alert will be displayed.
5. Press Button B to reset the scan and return to normal scanning mode.
6. Press Button A to manually trigger another scan.

## Known Skimmer Module Names

The tool comes pre-configured with a list of known skimmer module names. You can update this list in the sketch to add or remove names as needed. Look for the line in the code that looks like this to edit the list of known skimmers.

String knownSkimmerNames[] = {"HC-03", "HC-05", "HC-06"};

## Customization

You can customize various parameters in the sketch, such as scan duration, displayed device count, and stored history length.

## Disclaimer

This tool is provided for educational and law enforcement purposes only. It should be used in accordance with applicable laws and regulations. The tool may not guarantee the detection of all skimming devices, and false positives may occur.

## Contributions

Contributions to this open-source project are welcome. Feel free to fork the repository and submit pull requests to enhance its functionality.

## License

This project is licensed under the MIT License.
