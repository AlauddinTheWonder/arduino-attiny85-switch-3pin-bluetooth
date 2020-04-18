Arduino ATtiny85 Switch 
=======================
> 3pin with bluetooth control


Simple low powered automation to switch 3 AC sockets and controlled with Bluetooth. #ATtiny85

---

## Devices required
1. ATtiny85
2. DS1307 RTC module
3. HC-05 or HC-06 Bluetooth module
4. 5v power supply

---

## ATtiny85 pins:


| Pin   | Name         | Wire connection               |
| ----- | ------------ | ----------------------------- |
| 1     | Reset        | Not connected                 |
| 2     | I/O Pin 3    | Switch 2  |  BT Tx            |
| 3     | I/O Pin 4    | Switch 3  |  BT Rx            |
| 4     | GND          | Connected to Ground           |
| 5     | I/O Pin 0    | RTC SDA                       |
| 6     | I/O Pin 1    | Switch 1  | Mode change pin   |
| 7     | I/O Pin 2    | RTC SCL                       |
| 8     | VCC          | Connected to +3.3v to +5v     |



> **Note**: Mode pin should be connected to `GND` via `10K` resistor. To enable
> Bluetooth mode, connect the Mode pin to `VCC` and need to restart the device.

---

## Default time schedule:

| Desc     | On       | Off       |
| -------- | -------- | --------- |
| Switch 1 | 06:00    | 23:00     |
| Switch 2 | 09:00    | 19:00     |
| Switch 3 | 08:00    | 00:00     |

> **Note**: Can be re-scheduled by changing values in `t85-switch-3pin-with-BT.ino` file or via Bluetooth Application.

---
## Bluetooth Mode

To access device from bluetooth, start device in BT mode by connecting MODE pin with VCC.

For commands, have to send two bytes with 50ms gap.
```
-> First byte will be COMMAND
-> Second byte will be PARAMS (Values)
```

Command details:

| Sr No  | Command  | Param      | Return      | Description
| ------ | -------- | -----------| ----------- | ----------------------------------------------------
| 1      | 255      | 0          | SAME_PARAM  | Pingback. To recognize this device
| 2      | 254      | 0          | PIN_COUNT   | Get number of switch device support. Ex. 3
| 3      | 253      | 0          | TIMESTAMP   | Get RTC time in timestamp (UTC)
| 4      | 252      | TIMESTAMP  | SAME_PARAM  | Set RTC time, value in timestampt (UTC). Return the same as Param if success
| 5      | 251      | ROM_ADDR   | 0-255       | Read value from EEPROM. To read switch value. ROM_ADDR will be between 0 and (PIN_COUNT * 2)
| 6      | 251      | 250        | 0-59        | Get time drift in second(s)
| 7      | 250      | 0-59       | SAME_PARAM  | Set time drift in second(s)
| 8      | 0-60     | 0-23       | SAME_PARAM  | Write value to EEPROM. Set hours to switches. Ex. Command: 0=On (Swt 1), 1=Off (Swt 1), 2=On (Swt 2), 3=Off (Swt 2), so on...




---

Thanks & Regards,
Alauddin Ansari
https://github.com/AlauddinTheWonder