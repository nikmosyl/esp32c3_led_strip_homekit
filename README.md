# ESP32 LED Strip WS2812 HomeKit
Hardware и Frimware для контроллера адресной светодиодной ленты на базе ESP32-C3

## Hardware

<kbd>
  <img src="/Readme/Img/top.png" weight=50>
</kbd>

<kbd>
  <img src="/Readme/Img/bottom.png" weight=50>
</kbd>

[веб превью altium 365](https://365.altium.com/files/029D88F9-241C-48A4-977B-14C8D9AD6741?variant=[No+Variations])

На плате:
- [Входной разъём](https://www.digikey.com/en/products/detail/amphenol-cs-commercial-products/FLTS22WR00/20422799) для питание контролера и светодиодной ленты (светодиодная лента WS2812 или аналогичная с питанием +5V)
- [Выходной разъём](https://www.digikey.com/en/products/detail/amphenol-cs-commercial-products/FLTS32WR00/20426575) для питания и управляющего сигнала адресной светодиодной лентой
- USB type C для программирования контроллера ESP32-C3

## Frimware
Основано на [SDK](https://github.com/espressif/esp-homekit-sdk) от Espressif 

Общие шаги по установке c использованием исходников:

### 1. Установить [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/stable/esp32c3/get-started/linux-macos-setup.html)
Предпочительная версия v5.2.1

Предпочтительное место установки в корень домашней директории ~/


### 2. Установить [esp-homekit-sdk](https://github.com/espressif/esp-homekit-sdk)
Предпочтительное место установки в корень домашней директории ~/


### 3. Скачать репозиторий с проектом
```bash
cd ~/
git clone https://github.com/nikmosyl/esp32c3_led_strip_homekit.git
```


### 4. Настроить параметры HomeKit устройства и светодиодной ленты
Файл esp32c3_led_strip_homekit/frimware/lightbulb/main/app_main.c строка 162:
```C
hap_acc_cfg_t cfg = {
    .name = "Esp-Light",                  //отображаемое в приложении Дом название устройства
    .manufacturer = "Espressif",          
    .model = "EspLight01",
    .serial_num = "202405030213",         //при использовании нескольких устройств номер должен быть уникальным
    .fw_rev = "0.1.0",
    .hw_rev = "1.0",
    .pv = "1.1.0",
    .identify_routine = light_identify,
    .cid = HAP_CID_LIGHTING,
};
```
Файл frimware/lightbulb/main/Libs/internal_led/internal_led.c строка 10:
```C
#define BLUE_LED 5    //номер GPIO с отладочным свтодиодом на используемой плате
```
Файл frimware/lightbulb/main/Libs/led_strip/led_strip_control.c строка 14:
```C
#define FLOW 30               //задержка в милесекундах между включениями соседних сетодиодов на ленте
#define LED_STRIP_GPIO 7      //номер GPIO к которому подлючен контакт DI светодиодной ленты
#define LED_COUNT 10          //количество светодиодов на светодиодной ленте
```


### 5. Прописать переменные окружения (можно пропустить при установке idf и sdk по предпочтительным путям)
Можно либо прописать временные переменные окружения (указать путь до esp-homekit-sdk):
```bash
export HOMEKIT_PATH=~/esp/esp-homekit-sdk 
```
Либо отредоктировать файл frimware/lightbulb/CMakeLists.txt строка 11:
```CMake
set(HOMEKIT_PATH ~/esp/esp-homekit-sdk)
```
вместо ~/esp/esp-homekit-sdk указать свой путь к каталогу esp-homekit-sdk


### 6. Установить пароль Wi-Fi
Можно либо оставить всё как есть и тогда при первом запуске в консоль выведется QR код для подключения через [Espressif Provisioning Apps](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/provisioning/provisioning.html#provisioning-tools) 

Либо зашить пароль от Wi-Fi в контроллер жёстко:
```bash
cd ~/esp32c3_led_strip_homekit/frimware/lightbulb
. ~/esp/esp-idf/export.sh
```
Здесь выбран прошиваемый микроконтроллер esp32c3 как на плате из раздела Hardware, необходимо указать тот, который стоит на прошиваемой плате
```bash
idf.py set-target esp32c3
idf.py menuconfig
```

В разделе _**App Wi-Fi** -> **Source of Wi-Fi Credentials**_ нужно установить галочку на **Use Hardcoded**

В появившиеся поля необходимо ввести имя и пароль точки доступа

Нажать S (Save) и Enter после этого


### 7. Прошить плату
Для этого нужно подключить плату к ПК, убедиться, что она видна в списке устройств и к её последовательному порту есть доступ;

Перевести плату в режим прошивки (на плате из раздела Hardware это делается путём нажатия кнопки RST при удерживании кнопки BOOT);

Собрать прошивку:
```bash
idf.py build
```
Загрузить прошивку на плату:
```bash
idf.py flash
```


### 8. После прошивки
Перезагрузить плату
Дождаться пока она подключится к Wi-Fi и отобразится в меню добавления новых устройств HomeKit (на iPhone приложение _**Дом** -> **+** -> **Другие параметры** -> **выберете устройство**_, код 11122333) 






