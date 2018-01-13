# LaserDemo
Generate test patterns for laser galvanometer

Based on "Arduino Laser Show With Real Galvos" by DeltaFlo:

http://www.instructables.com/id/Arduino-Laser-Show-With-Real-Galvos/


## Target Device

  **Adafruit HUZZAH ESP8266**
  
Memory usage:
```
Sketch uses 483399 bytes (46%) of program storage space. Maximum is 1044464 bytes.
Global variables use 41296 bytes (50%) of dynamic memory, leaving 40624 bytes for local variables. Maximum is 81920 bytes.
```

## User Interface

  The web page allows you to select objects for display:

![Screenshot](Images/Screenshot.png)

- The Object and Generator lists are generated dynamically from the contents of the objName and genName arrays.
- **KPPS** is the speed of the scanner, Kilo Positions Per Second
- **LTD** Laser Toggle Delay, the latency of the scanner, in milliseconds
- **LQ** Laser Quality, maximum line length

## Adding Objects


