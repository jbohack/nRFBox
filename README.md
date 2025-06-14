<div align="center">
  <img src="https://github.com/user-attachments/assets/0eba90bc-2ff5-40df-88a1-92e23396d1d3" alt="logo" width="100" height="auto" />
  
  <h1>nyanBOX</h1>
  <p>All-in-One Gadget for BLE and 2.4GHz Networks</p>
  <p>Maintained by jbohack & zr_crackiin</p>

  <!-- Badges -->
  <p>
    <a href="https://github.com/jbohack/nyanBOX" title="GitHub repo">
      <img src="https://img.shields.io/static/v1?label=nyanBOX&message=jbohack&color=purple&logo=github" alt="nyanBOX - jbohack">
    </a>
    <a href="https://github.com/cifertech/nrfbox" title="Original Project">
      <img src="https://img.shields.io/badge/original%20project-CiferTech%20nRFBox-blue" alt="Original Project">
    </a>
    <a href="https://github.com/jbohack/nyanBOX">
      <img src="https://img.shields.io/github/stars/jbohack/nyanBOX?style=social" alt="stars - nyanBOX">
    </a>
    <a href="https://github.com/jbohack/nyanBOX">
      <img src="https://img.shields.io/github/forks/jbohack/nyanBOX?style=social" alt="forks - nyanBOX">
    </a>
  </p>

  <p>
    <a href="https://defcon.lullaby.cafe">Website</a> ·
    <a href="https://discord.gg/squachtopia">Discord</a> ·
    <a href="https://github.com/cifertech/nrfbox">Original Project</a>
  </p>
</div>

---


## 📖 About nyanBOX

nyanBOX is a fork of the original nRFBOX project by CiferTech, now maintained by jbohack & zr_crackiin. This version includes various improvements and new features while maintaining compatibility with the original hardware.

### 🆕 What's New
- Updated UI with improved display layout
- Enhanced stability and performance
- New features and improvements to existing functionality
- Active maintenance and support

## :star2: Project Overview

nyanBOX is a wireless toolkit designed to explore, analyze, and interact with various wireless communication protocols. Based on the original nRFBOX by CiferTech, this fork retains all the powerful features while introducing new improvements and providing ongoing maintenance.

The device combines the ESP32 Wroom32U, NRF24 modules, an OLED display, and other components to create a multifunctional device that can act as a scanner, analyzer, jammer, BLE jammer, BLE spoofer, and perform advanced tasks such as the "Sour Apple" attack.

<div align="center">
  <img src="https://github.com/user-attachments/assets/4bbf6b7f-f413-4a68-825e-c39e9e3ec596" alt="nyanBOX Interface" width="650" />
</div>


## 🎯 Features

### 🔵 Bluetooth (BLE) Tools
- **BLE Scanner** – Detects nearby BLE devices
- **BLE Jammer** – Disrupts BLE device communication
- **BLE Spammer** – Broadcasts BLE advertisement packets for testing
- **BLE Spoofer** – Simulates BLE devices for testing and research
- **Sour Apple** – Mimics Apple Bluetooth signals like AirPods pairing pop-up to test device resilience against protocol exploits.
- **Flipper Scanner** – Detects nearby Flipper Zero devices

### 📶 WiFi Tools
- **WiFi Scanner** – Detects nearby WiFi access points
- **WiFi Deauther** – Disrupts 2.4GHz WiFi device communication
- **Beacon Spam** – Broadcasts multiple fake WiFi networks for testing
- **WLAN Jammer** – Jams wireless communication on selected channels

### 📡 Signal & Protocol Tools
- **Scanner** – Scans the 2.4GHz frequency band to detect active channels and devices
- **Analyzer** – Analyzes detected signals and provides detailed activity information
- **Proto Kill Mode** – Advanced tool for disrupting various wireless protocols

---

## 📟 Hardware
- **Main Controller**: ESP32 Wroom32U
- **Wireless Modules**: NRF24 GTmini
- **Display**: 0.96" OLED
- **Connectivity**: USB-C, UART

---

## 🔧 Prerequisites

### USB Drivers
Install the required USB drivers for your ESP32 board:
- **CP210x-based boards**: [CP210x USB to UART Bridge VCP Drivers](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)
- **CH340/CH341-based boards**: [CH340 Drivers](https://www.wch.cn/download/CH341SER_EXE.html)

---
## 🚀 Development Setup

### Prerequisites
- [Visual Studio Code](https://code.visualstudio.com/)
- [PlatformIO IDE](https://platformio.org/install/ide?install=vscode) extension

### Getting Started
1. Clone this repository:
   ```bash
   git clone https://github.com/jbohack/nyanBOX.git
   ```
2. Open the project in VS Code:
   - Select `File > Open Folder`
   - Choose the nyanBOX directory

### Configuration
- Pre-configured for ESP32-DevKitC in `platformio.ini`
- For other ESP32 boards, update the `board` parameter in `platformio.ini`

### Build and Upload
1. **Build**: Click the checkmark icon in the status bar
2. **Connect**: Plug in your ESP32 via USB
3. **Upload**: Click the right-arrow icon
4. **Monitor**: Click the plug icon to open the serial monitor

### Troubleshooting
- **Upload Failing?** Try holding the BOOT button during upload
- **Connection Issues?** Verify the correct COM port is selected
- **Driver Problems?** Ensure proper USB drivers are installed (see Prerequisites)

---

## 📜 License

Distributed under the MIT License. See [LICENSE.txt](LICENSE.txt) for more information.

---

## 💝 Support & Contact

If you find nyanBox useful, please consider supporting the project:
- [jbohack's Ko-fi](https://ko-fi.com/jbohack)
- [zr_crackiin's Ko-fi](https://ko-fi.com/zrcrackiin)

### Maintainers
- [jbohack](https://github.com/jbohack)
- [zr_crackiin](https://github.com/zRCrackiiN)

## 🙏 Acknowledgements 

### Open Source Projects Used
- [Poor Man's 2.4 GHz Scanner](https://forum.arduino.cc/t/poor-mans-2-4-ghz-scanner/54846)
- [arduino_oled_menu](https://github.com/upiir/arduino_oled_menu)
- [nRF24L01-WiFi-Jammer](https://github.com/hugorezende/nRF24L01-WiFi-Jammer)
- [Universal-RC-system](https://github.com/alexbeliaev/Universal-RC-system)
- [AppleJuice](https://github.com/ECTO-1A/AppleJuice)
- [ESP32-Sour-Apple](https://github.com/RapierXbox/ESP32-Sour-Apple)
- [Original nRFBOX Project](https://github.com/cifertech/nrfbox)

### Community
A big thank you to all contributors and community members who have helped improve nyanBOX!
