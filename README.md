
# References
[Robotic-Snake](https://github.com/WillDonaldson/Robotic-Snake.git)
# Deployment
To deploy this project run

```bash
  git clone https://github.com/anup-mhr/Viper-Vision.git
```
## For snake robot

In arduino goto “ Additional Boards Manager URLs ”, in the " Preferences" add this

```bash
  http://arduino.esp8266.com/staging/package_esp8266com_index.json
```
From "Finalized code" folder open file

```bash
 blynk_ultrasonic_modified_snake.ino
```

Goto boards and select board

```bash
  Nodemcu 1.0
```
Now select port, update wifi SSID and password and press upload.

---
## For Espcam
Goto boards and select board

```bash
  Esp32 arduino ---> AI thinker esp32-cam
```
Goto examples in Menu and select

```bash
  examples --> esp32 --> CameraWebServer
```
Go through 'Programming the ESP32-CAM' in this link


  [Programming the ESP32-CAM](https://lastminuteengineers.com/getting-started-with-esp32-cam/)

---

## Note:


Make sure all the libraries mentioned in documentation are properly installed




