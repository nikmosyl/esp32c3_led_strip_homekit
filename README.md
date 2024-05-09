# ESP32 LED Strip WS2812 HomeKit
[ru](https://github.com/nikmosyl/esp32c3_led_strip_homekit/blob/main/Readme/README-ru.md)

Hardware and Frimware for an addressable LED strip controller based on ESP32-C3

## Hardware

<kbd>
  <img src="/Readme/Img/top.png" weight=50>
</kbd>

<kbd>
  <img src="/Readme/Img/bottom.png" weight=50>
</kbd>

[altium 365 web preview](https://365.altium.com/files/029D88F9-241C-48A4-977B-14C8D9AD6741?variant=[No+Variations])

You can order it [here](https://www.pcbway.com/project/shareproject/ws2812esp32_3_v1_792a8e86.html)

On board:
- [Input connector](https://www.digikey.com/en/products/detail/amphenol-cs-commercial-products/FLTS22WR00/20422799) for power supply of the controller and LED strip (LED strip WS2812 or similar with +5V power supply)
- [Output connector](https://www.digikey.com/en/products/detail/amphenol-cs-commercial-products/FLTS32WR00/20426575) for power supply and control signal for addressable LED strip
- USB type C for programming ESP32-C3 controller

## Frimware
Based on Espressif [SDK](https://github.com/espressif/esp-homekit-sdk)

General installation steps using sources:

### 1. Install [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/stable/esp32c3/get-started/linux-macos-setup.html)
Preferred version v5.2.1

Preferred installation location is at the root of your home directory ~/


### 2. Install [esp-homekit-sdk](https://github.com/espressif/esp-homekit-sdk)
Preferred installation location is at the root of your home directory ~/


### 3. Download the repository with the project
```bash
cd ~/
git clone https://github.com/nikmosyl/esp32c3_led_strip_homekit.git
```


### 4. Configure HomeKit device and LED strip settings
File esp32c3_led_strip_homekit/frimware/lightbulb/main/app_main.c line 162:
```C
hap_acc_cfg_t cfg = {
    .name = "Esp-Light",                  //device name displayed in the Home app
    .manufacturer = "Espressif",          
    .model = "EspLight01",
    .serial_num = "202405030213",         //when using multiple devices, the number must be unique
    .fw_rev = "0.1.0",
    .hw_rev = "1.0",
    .pv = "1.1.0",
    .identify_routine = light_identify,
    .cid = HAP_CID_LIGHTING,
};
```
File frimware/lightbulb/main/Libs/internal_led/internal_led.c line 10:
```C
#define BLUE_LED 5    //GPIO number with debug LED on the board used
```
File frimware/lightbulb/main/Libs/led_strip/led_strip_control.c line 14:
```C
#define FLOW 30               //delay in milliseconds between switching on adjacent LEDs on the strip
#define LED_STRIP_GPIO 7      //GPIO number to which the DI pin of the LED strip is connected
#define LED_COUNT 10          //number of LEDs on LED strip
```


### 5. Set environment variables (can be skipped when installing idf and sdk in preferred paths)
You can either register temporary environment variables (specify the path to esp-homekit-sdk):
```bash
export HOMEKIT_PATH=~/esp/esp-homekit-sdk 
```
Or edit the file firmware/lightbulb/CMakeLists.txt line 11:
```CMake
set(HOMEKIT_PATH ~/esp/esp-homekit-sdk)
```
Instead of ~/esp/esp-homekit-sdk, specify your path to the esp-homekit-sdk directory


### 6. Set Wi-Fi password
You can either leave everything as it is, and then upon first launch, a QR code will be displayed in the console for connecting via [Espressif Provisioning Apps](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/provisioning/provisioning.html#provisioning-tools) 

Or hardcode the Wi-Fi password into the controller:
```bash
cd ~/esp32c3_led_strip_homekit/frimware/lightbulb
. ~/esp/esp-idf/export.sh
```
Here the esp32c3 microcontroller to be flashed is selected as on the board from the Hardware section, you must specify the one that is on the board to be flashed
```bash
idf.py set-target esp32c3
idf.py menuconfig
```

In the section _**App Wi-Fi** -> **Source of Wi-Fi Credentials**_ you need to check the box for **Use Hardcoded**

In the fields that appear, you must enter the name and password of the access point

Press S (Save) and Enter after that


### 7. Flash the board
To do this, you need to connect the board to the PC, make sure that it is visible in the list of devices and there is access to its serial port;

Switch the board to firmware mode (on the board from the Hardware section this is done by pressing the RST button while holding down the BOOT button);

Build firmware:
```bash
idf.py build
```
Upload firmware to the board:
```bash
idf.py flash
```


### 8. After the firmware
Reboot the board
Wait until it connects to Wi-Fi and appears in the menu for adding new HomeKit devices (on iPhone, _**Home** app -> **+** -> **Other options** -> **select device**_ , code 11122333)






