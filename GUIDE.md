# ESP32 LED Control via Blynk - Complete Guide

## Overview
This project enables wireless control of 4 individual LEDs and an RGB LED using the **Blynk IoT application** on an **ESP32 microcontroller**. Perfect for IoT beginners and home automation enthusiasts.

---

## Hardware Requirements

### Components Needed:
- **ESP32 DEVKIT** microcontroller
- **4x Single-color LEDs** (red, green, blue, yellow or any color)
- **1x RGB LED** (common cathode or common anode)
- **4x Resistors** (~220Ω for LEDs)
- **3x Resistors** (~220Ω for RGB LED channels)
- **Jumper wires** (male-to-male and male-to-female)
- **USB cable** (for programming and power)
- **Breadboard** (optional but recommended)
- **Power source** (USB 5V or external 5V supply)

### Pin Configuration:
```
Single LEDs:
- LED1 → GPIO 23
- LED2 → GPIO 22
- LED3 → GPIO 19
- LED4 → GPIO 18

RGB LED:
- Red   → GPIO 32
- Blue  → GPIO 33
- Green → GPIO 25
```

---

## Wiring Diagram

### Single LED Connection:
```
ESP32 GPIO Pin → 220Ω Resistor → LED Anode (+)
ESP32 GND      → LED Cathode (-)
```

### RGB LED Connection (Common Cathode):
```
ESP32 GPIO 32 → 220Ω Resistor → Red Pin
ESP32 GPIO 33 → 220Ω Resistor → Blue Pin
ESP32 GPIO 25 → 220Ω Resistor → Green Pin
ESP32 GND      → Common Cathode (-)
```

> **Note:** For common anode RGB LEDs, connect the common pin to 3.3V and reverse the logic in the code.

---

## Software Setup

### Step 1: Install Arduino IDE
1. Download from [arduino.cc](https://www.arduino.cc/en/software)
2. Install the software on your computer

### Step 2: Install ESP32 Board
1. In Arduino IDE, go to **File → Preferences**
2. Add this URL in "Additional Boards Manager URLs":
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
3. Go to **Tools → Board → Boards Manager**
4. Search for "ESP32" and install **esp32 by Espressif Systems**

### Step 3: Install Required Libraries
1. Go to **Sketch → Include Library → Manage Libraries**
2. Install the following:
   - **LiquidCrystal_I2C** (by Frank de Brabander)
   - **Blynk** (by Blynk)

3. Manual installation (if needed):
   ```
   Sketch → Include Library → Add .ZIP Library
   ```

### Step 4: Configure Board Settings
1. **Tools → Board:** Select "ESP32 Dev Module"
2. **Tools → Upload Speed:** 115200
3. **Tools → CPU Frequency:** 80 MHz
4. **Tools → Flash Size:** 4MB
5. **Tools → Partition Scheme:** Default
6. Select your **COM port** under **Tools → Port**

---

## Blynk Setup

### Step 1: Create Blynk Account
1. Download the **Blynk IoT app** from App Store or Google Play
2. Create a free account with email
3. Log in to your account

### Step 2: Create a New Device Template
1. Click **+ New Template**
2. Set up:
   - **Name:** LED Control
   - **Hardware:** ESP32
   - **Connection Type:** WiFi

### Step 3: Configure Virtual Pins
Add the following datastreams:

| Virtual Pin | Name | Widget Type | Range |
|-------------|------|-------------|-------|
| V1 | LED 1 | Button | ON/OFF |
| V2 | LED 2 | Button | ON/OFF |
| V3 | LED 3 | Button | ON/OFF |
| V4 | LED 4 | Button | ON/OFF |
| V5 | Blue Slider | Slider | 0-255 |
| V6 | Red Slider | Slider | 0-255 |
| V7 | Green Slider | Slider | 0-255 |

### Step 4: Add Widgets to Dashboard
1. Go to **Web Dashboard** or mobile app
2. Click **Edit**
3. Add:
   - 4x **Button** widgets (for V1-V4)
   - 3x **Slider** widgets (for V5-V7)
4. Configure each widget to use its corresponding Virtual Pin
5. **Save** your dashboard

### Step 5: Get Your Credentials
1. Click **Devices**
2. Select your device
3. Copy:
   - **Template ID** → `TMPL6bU9DCRzs`
   - **Auth Token** (shown in email)

---

## Code Upload

### Step 1: Update Credentials
Edit these lines in `ESP32 LED Control.ino`:

```cpp
#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "LED Control"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"

char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASSWORD";
```

### Step 2: Connect ESP32 to Computer
- Connect via USB cable
- Check that the correct COM port is selected

### Step 3: Upload Code
1. Click **Sketch → Verify** (check for errors)
2. Click **Sketch → Upload**
3. Wait for the upload to complete
4. Open **Tools → Serial Monitor** (9600 baud)

### Step 4: Verify Connection
- You should see:
  ```
  [Blynk] Connected!
  ```
- LCD display should show "Koneksi Sukses" (Connection Successful)
- LEDs should be ready to control

---

## Usage Instructions

### Controlling Single LEDs:
1. Open the **Blynk app**
2. Go to your **Dashboard**
3. Tap the buttons for LED 1-4 to toggle ON/OFF
4. LEDs on the breadboard should light up accordingly

### Controlling RGB LED:
1. Use the three **sliders** (Red, Green, Blue)
2. Adjust each slider from 0-255 to control brightness
3. Combine colors:
   - Red: 255, Green: 0, Blue: 0 = Red light
   - Red: 0, Green: 255, Blue: 0 = Green light
   - Red: 0, Green: 0, Blue: 255 = Blue light
   - Red: 255, Green: 255, Blue: 255 = White light
   - Red: 255, Green: 255, Blue: 0 = Yellow light

---

## Troubleshooting

| Issue | Solution |
|-------|----------|
| ESP32 not uploading | Check COM port, try different USB cable, hold BOOT button while uploading |
| WiFi not connecting | Verify SSID and password, check 2.4GHz band is enabled |
| Blynk app not connecting | Verify Auth Token, restart ESP32, check internet connection |
| LEDs not lighting | Check resistors and wiring, verify GPIO pin assignments |
| RGB LED shows wrong color | For common anode, connect to 3.3V instead of GND |
| Serial Monitor showing garbage | Change baud rate to 115200 |

---

## Code Explanation

### Blynk Event Handlers:
```cpp
BLYNK_WRITE(V1) { // When button in app is pressed
  int value1 = param.asInt(); // Get value (0 or 1)
  digitalWrite(LED1_PIN, value1); // Set LED pin
}
```

### RGB LED Control:
```cpp
BLYNK_WRITE(V5) { // Blue slider
  int sliderValue = param.asInt(); // Get 0-255 value
  analogWrite(RGB_BLUE_PIN, sliderValue); // Set brightness
}
```

---

## Advanced Tips

1. **Add More Sensors:** Connect temperature, humidity, or motion sensors and display values in Blynk
2. **Scheduling:** Use Blynk's automation to turn LEDs on/off at specific times
3. **Remote Access:** Control from anywhere with an internet connection
4. **Multiple Devices:** Create different templates for different projects
5. **Custom Alerts:** Receive notifications based on sensor readings

---

## Project Extensions

- Add a **temperature sensor** to display room temperature in Blynk
- Implement **PWM control** for brightness adjustment on single LEDs
- Create **automation routines** (e.g., turn on at sunset)
- Build a **mobile app** using Blynk's no-code dashboard
- Add **voice control** using Blynk's integration with Alexa

---

## References

- **Blynk Official:** [https://blynk.io](https://blynk.io)
- **ESP32 Documentation:** [https://docs.espressif.com/](https://docs.espressif.com/)
- **Arduino IDE:** [https://www.arduino.cc/](https://www.arduino.cc/)
- **Component Datasheets:** Available from suppliers

---

## License & Credits

This project is designed for educational purposes. Feel free to modify and share!

**Happy IoT Learning!** 🚀

---

**Version:** 1.0  
**Last Updated:** October 2026
