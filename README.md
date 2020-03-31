# arduino-attiny85-switch-3pin-bluetooth
Simple low powered automation to switch 3 AC sockets and controlled with Bluetooth. #ATtiny85


## Devices required
1. ATtiny85
2. DS1307 RTC module
3. HC-05 or HC-06 Bluetooth module
4. 5v power supply

## ATtiny85 pins:
```
-----------------------------------------------------------
  Pin# | Name         |     Wire connection   
-----------------------------------------------------------
  1      Reset        ->    Not connected
  2      I/O Pin 3    ->    Switch 2  |  BT Tx
  3      I/O Pin 4    ->    Switch 3  |  BT Rx
  4      GND          ->    Connected to Ground
  5      I/O Pin 0    ->    RTC SDA
  6      I/O Pin 1    ->    Switch 1  | Mode change pin
  7      I/O Pin 2    ->    RTC SCL
  8      VCC          ->    Connected to +5v
-----------------------------------------------------------
```
**Note**: Mode pin should be connected to `GND` via `10K` resistor. To enable Bluetooth mode, connect the Mode pin to `+5v` and need to restart the device.


## Default time schedule:
```
Switch 1
    On  -> 06:00
    Off -> 22:00

Switch 2
    On  -> 08:00
    Off -> 19:00

Switch 3
    On  -> 08:00
    Off -> 00:00
```
**Note**: Can be re-scheduled by changing values in `t85-switch-3pin-with-BT.ino` file.


