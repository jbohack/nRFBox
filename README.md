<div align="center">

  <img src="https://github.com/user-attachments/assets/0eba90bc-2ff5-40df-88a1-92e23396d1d3" alt="logo" width="100" height="auto" />
  
  <h1> nyanBOX </h1>
  <p> All-in-One Gadget for BLE and 2.4GHz Networks </p>
  <p>Maintained by jbohack & zr_crackiin</a></p>


<!-- Badges -->
<a href="https://github.com/jbohack/nyanBOX" title="Go to GitHub repo"><img src="https://img.shields.io/static/v1?label=nyanBOX&message=jbohack&color=purple&logo=github" alt="nyanBOX - jbohack"></a>
<a href="https://github.com/cifertech/nrfbox" title="Original Project"><img src="https://img.shields.io/badge/original%20project-CiferTech%20nRFBox-blue" alt="Original Project"></a>
<a href="https://github.com/jbohack/nyanBOX"><img src="https://img.shields.io/github/stars/jbohack/nyanBOX?style=social" alt="stars - nyanBOX"></a>
<a href="https://github.com/jbohack/nyanBOX"><img src="https://img.shields.io/github/forks/jbohack/nyanBOX?style=social" alt="forks - nyanBOX"></a>

   
<h4>
    <a href="https://defcon.lullaby.cafe">WEBSITE</a>
  <span> · </span>
    <a href="https://discord.gg/squachtopia">DISCORD</a>
  <span> · </span>
    <a href="https://github.com/cifertech/nrfbox">ORIGINAL PROJECT</a>
  </h4>
</div>
<br/>

## 📖 About nyanBOX

nyanBOX is a fork of the original nRFBOX project by CiferTech, now maintained by jbohack & zr_crackiin. This version includes various improvements and new features while maintaining compatibility with the original hardware.

### 📚 Original Project
- Original nRFBOX by CiferTech: [GitHub](https://github.com/cifertech/nrfbox)
- Original documentation: [CiferTech](https://cifertech.net/nrfbox-your-all-in-one-gadget-for-ble-and-2-4ghz-networks/)

### 🆕 What's New in nyanBOX
- Updated UI with improved display layout
- Enhanced stability and performance
- New features and improvements to existing functionality
- Active maintenance and support
  
<div>&nbsp;</div>

<h2>🛠 Functionality Status and Reliability</h2>

<table>
  <thead>
    <tr>
      <th>Feature</th>
      <th>Status</th>
      <th>Reliability</th>
      <th>Notes</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><strong>Scanner</strong></td>
      <td>Stable</td>
      <td>High</td>
      <td>Reliably scans the 2.4 GHz band to detect active channels and nearby devices. Occasional misses in high-interference environments.</td>
    </tr>
    <tr>
      <td><strong>Analyzer</strong></td>
      <td>Stable</td>
      <td>High</td>
      <td>Provides useful insights into detected signals, but additional updates are needed for improved accuracy and detailed analysis.</td>
    </tr>
    <tr>
      <td><strong>Jammer</strong></td>
      <td>Stable</td>
      <td>High</td>
      <td>Basic jamming works but effectiveness varies by device type and signal strength. Testing on select channels is recommended.</td>
    </tr>
    <tr>
      <td><strong>BLE Jammer</strong></td>
      <td>Stable</td>
      <td>High</td>
      <td>Disrupts BLE devices inconsistently. Further improvements are needed to ensure stability and effectiveness across BLE variants.</td>
    </tr>
    <tr>
      <td><strong>BLE Spoofer</strong></td>
      <td>Stable</td>
      <td>Low</td>
      <td>Capable of simulating basic BLE signals but has limited compatibility. Best for controlled testing scenarios.</td>
    </tr>
    <tr>
      <td><strong>Sour Apple</strong></td>
      <td>Stable</td>
      <td>Low</td>
      <td>Specialized attack method with limited reliability; effective only under specific conditions. Further tuning is required.</td>
    </tr>
  </tbody>
</table>

- When using **multiple NRF24** modules, the power demands can exceed the capabilities of the onboard power supply or regulator. Running three NRF modules simultaneously may cause instability, leading to intermittent failures or causing the nyanBOX to stop functioning altogether.
- **Range Limitations**: The jammer is most effective at short range. Beyond a certain distance, the signal weakens, making it harder to consistently disrupt communication.
- **Device Variability**: Different devices react to jamming signals in varying ways. Some may be more resistant.

<div>&nbsp;</div>

<!-- About the Project -->
## :star2: About the Project
nyanBOX is a wireless toolkit designed to explore, analyze, and interact with various wireless communication protocols. Based on the original nRFBOX by CiferTech, this fork maintains all the powerful features while adding new improvements and active maintenance. The device combines the ESP32 Wroom32U, NRF24 modules, an OLED display, and other components to create a multifunctional device that can act as a scanner, analyzer, jammer, BLE jammer, BLE spoofer, and perform advanced tasks such as the "Sour Apple" attack.



<div align="center"> 
  <img src="https://github.com/user-attachments/assets/7012353c-2d09-4956-9152-937cf6a7ce18" alt="screenshot" width="Auto" height="Auto" />
</div>

<div>&nbsp;</div>

<!-- Features -->
### 🎯 Features

**Software:**
- **Scanner**: Scans the 2.4GHz frequency band to detect active channels and devices.
- **Analyzer**: Analyzes the detected signals and provides detailed information about the activity.
- **WLAN Jammer**: Jams wireless communication on selected channels to test network robustness.
- **Proto Kill Mode**: Proto Kill has evolved into a powerful tool for disrupting various protocols.
- **BLE Jammer**: Specifically targets Bluetooth Low Energy (BLE) devices to disrupt their communication.
- **BLE Spoofer**: Spoofs BLE devices to simulate various BLE signals for testing and research.
- **Sour Apple**: A specialized attack for testing security measures against specific wireless vulnerabilities.
- **BLE Scan**: Detects nearby BLE devices.
- **Flipper Scan**: Detects nearby Flipper Zero devices.
- **WiFi Scan**: Detects nearby WiFi access points.
- **WiFi Deauther**: Deauthenticates 2.4GHz WiFi devices to disrupt their communication.
- **Beacon Spam**: Broadcasts multiple fake WiFi networks to test client behavior/network scanning tools.

**Hardware:**
- ESP32 Wroom32U
- NRF24 GTmini Modules
- OLED 0.96" Display

<div>&nbsp;</div>

<!-- nRFBOX V2 -->
## :eyes: nRFBox Versions: Then and Now

<table>
  <tr>
    <td style="text-align: center;">
      <img src="https://github.com/user-attachments/assets/b121fe84-c789-409a-85f5-21f6d5854347" alt="nRFBOX V1" style="width: 600px; border: 1px solid #ccc; border-radius: 5px;">
      <p style="font-style: italic; font-size: 14px; margin-top: 5px;">nRFBox-v1 based on Arduino</p>
    </td>    
    <td style="text-align: center;">
      <img src="https://github.com/user-attachments/assets/a044ab5e-346c-415f-b1fb-f65aa04c520a" alt="nRFBOX V2" style="width: 600px; border: 1px solid #ccc; border-radius: 5px;">
      <p style="font-style: italic; font-size: 14px; margin-top: 5px;">nRFBox-v2 based on ESP32</p>
    </td>
  </tr>
</table>


<div>&nbsp;</div>

## 🔗 Prerequisites

### USB Drivers
- Install the required USB drivers for your ESP32 board:
  - For CP210x-based boards: [CP210x USB to UART Bridge VCP Drivers](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)
  - For CH340/CH341-based boards: [CH340 Drivers](https://www.wch.cn/download/CH341SER_EXE.html)

&nbsp;
## 🚀 Development with PlatformIO in VS Code

For the best development experience, we recommend using PlatformIO in Visual Studio Code:

### Prerequisites
- [Visual Studio Code](https://code.visualstudio.com/)
- [PlatformIO IDE](https://platformio.org/install/ide?install=vscode) extension

### Getting Started
1. Clone this repository
2. Open the project in VS Code:
   - Select `File > Open Folder`
   - Choose the nyanBOX directory

### Configuration
- The project is pre-configured for ESP32-DevKitC in `platformio.ini`
- For other ESP32 boards, update the `board` parameter in `platformio.ini`

### Building and Uploading
1. Build the project: Click the checkmark icon in the blue status bar
2. Connect your ESP32 via USB
3. Upload the firmware: Click the right-arrow icon
4. Monitor output: Click the plug icon to open the serial monitor

### Troubleshooting
- If upload fails, try holding the BOOT button during upload
- Verify the correct COM port is selected in the status bar
- Ensure proper USB drivers are installed (see Prerequisites)

<div>&nbsp;</div>

<!-- License -->
## :warning: License

Distributed under the MIT License. See LICENSE.txt for more information.

<div>&nbsp;</div>

<!-- Contact -->
## :handshake: Contact

▶ Support me on Patreon [patreon.com/cifertech](https://www.patreon.com/cifertech)

### Maintainers
- [jbohack](https://github.com/jbohack)
- [zr_crackiin](https://github.com/zRCrackiiN)

### Original Author
CiferTech - [@twitter](https://twitter.com/techcifer) - CiferTech@gmail.com

### Project Links
- nyanBOX Repository: [https://github.com/jbohack/nyanBOX](https://github.com/jbohack/nyanBOX)
- Original nRFBOX Project: [https://github.com/cifertech/nrfbox](https://github.com/cifertech/nrfbox)

<div>&nbsp;</div>

<!-- Acknowledgments -->
## :gem: Acknowledgements 

**The libraries and projects listed below are used in this software:**
 - [Poor Man’s 2.4 GHz Scanner](https://forum.arduino.cc/t/poor-mans-2-4-ghz-scanner/54846)
 - [arduino_oled_menu](https://github.com/upiir/arduino_oled_menu)
 - [nRF24L01-WiFi-Jammer](https://github.com/hugorezende/nRF24L01-WiFi-Jammer)
 - [Universal-RC-system](https://github.com/alexbeliaev/Universal-RC-system/tree/master)
 - [AppleJuice](https://github.com/ECTO-1A/AppleJuice)
 - [ESP32-Sour-Apple](https://github.com/RapierXbox/ESP32-Sour-Apple)

**Community Contributors**: Thanks to everyone who helped improve nyanBOX! Your support is much appreciated!

