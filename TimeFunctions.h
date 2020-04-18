/* 
 * Alauddin Ansari
 * 2018-12-15
 * Time and DS1307 related Functions
 * Dependencies:
 * 1. TinyDS1307 : https://github.com/AlauddinTheWonder/arduino-tiny_ds1307.git
 */

#include <TinyRTC.h>

tmElements_t getTime()
{
  return RTC.getTM();
}

unsigned long getTimeNow() {
  return RTC.get();
}

bool setTimeNow(unsigned long t) {
  return RTC.set(t);
}

void connectRTC()
{
  while (!RTC.isRunning()) {
    delay(2000);
  }
}

boolean validateTime(tmElements_t tm) {
  
  if (tm.Year < 2010) {
    return false;
  }
  if (tm.Month <= 0 || tm.Month > 12) {
    return false;
  }
  if (tm.Day <= 0 || tm.Day > 31) {
    return false;
  }
  if (tm.Hour < 0 || tm.Hour > 23) {
    return false;
  }
  return true;
}

void syncDriftedTime(uint8_t sec)
{
  setTimeNow(getTimeNow() - sec);
}
