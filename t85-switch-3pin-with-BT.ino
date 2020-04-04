/* 
 * Alauddin Ansari
 * 2020-03-28
 * ATtiny85 Low-Powered Automate 3 switches
 * Dependencies:
 * 1. SoftwareSerial (for BT)
 * 2. Time Lib
 * 3. DS1307RTC Lib
 */

#include <EEPROM.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include "Watchdog.h"
#include "functions.h"
#include "TimeFunctions.h"

// Watchdog Settings
#define watchdog_mode 9  // 6=1sec (0.5sec), 7=2sec (1sec), 8=4sec (3.2sec), 9=8sec (7.4sec)
#define wtd_cnt_reset 75 // Actual task will be executed after this counter.
byte wtd_cnt = 0;        // Counter for task execution comparision.

/* 
 * Pins Setting
 * -------------------------
 * Pin0 - RTC SDA (Phy Pin5) - occupied
 * Pin2 - RTC SCL (Phy Pin7) - occupied 
 */
#define Switch_1 1
#define Switch_2 3
#define Switch_3 4
#define ModePin 1       // with 10K to Gnd. VCC to enable BT mode

// Time schedule (in Hour) -- Same on and off value means disable
byte Switch_1_on = 6;
byte Switch_1_off = 22;

byte Switch_2_on = 8;
byte Switch_2_off = 19;

byte Switch_3_on = 8;
byte Switch_3_off = 0;

byte BTenabled = 0; // indicate whether BT is enabled or not

void setup() {
  pinMode(ModePin, INPUT);
//  delay(10);

  if (digitalRead(ModePin)) {
    BTenabled = 1;
    enableBTMode();
  }
  else {
    BTenabled = 0;

    pinMode(Switch_1, OUTPUT);
    pinMode(Switch_2, OUTPUT);
    pinMode(Switch_3, OUTPUT);

    digitalWrite(Switch_1, LOW);
    digitalWrite(Switch_2, LOW);
    digitalWrite(Switch_3, LOW);

    setup_watchdog(watchdog_mode);
  }

  connectDS1307();
//  setTimeNow(1585699200); // for dummy

  initVarsFromEEPROM();

  delay(500);
}

void loop() {
  if (BTenabled == 1) {
    runBT();
  }
  else {
    if (wtd_cnt == 0) {
  
      // Watchdog sleep mode also stops Timer.
      // Get current time from RTC module
      
      setTime(RTC.get());
      delay(100);

      if (validateTime()) {
    
        byte _hour = hour();
  
        // Switch 1
        byte Swt1_sts = getOnOffStatus(_hour, Switch_1_on, Switch_1_off);
        digitalWrite(Switch_1, Swt1_sts);
        delay(100);
  
        // Switch 2
        byte Swt2_sts = getOnOffStatus(_hour, Switch_2_on, Switch_2_off);
        digitalWrite(Switch_2, Swt2_sts);
        delay(100);
        
        // Switch 3
        byte Swt3_sts = getOnOffStatus(_hour, Switch_3_on, Switch_3_off);
        digitalWrite(Switch_3, Swt3_sts);
  
        delay(500);
      }
    }
  
    wtd_cnt++;
    
    if (wtd_cnt >= wtd_cnt_reset) {
      wtd_cnt = 0;
    }
    
    system_sleep();
  }
}
