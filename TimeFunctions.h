/* 
 * Alauddin Ansari
 * 2018-12-15
 * Time and DS1307 related Functions
 * Dependencies:
 * 1. TinyDS1307 : https://github.com/AlauddinTheWonder/arduino-tiny_ds1307.git
 */

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

void connectDS1307()
{
  while (!RTC.isRunning()) {
    delay(2000);
  }
}

int getDriftedTime() {
  tmElements_t tm = getTime();
  
  switch(tm.Month) {
    case 11:
      return 1;
    case 12:
    case 1:
      return 2;
    case 2:
      return 1;
    default:
      return 0;
  }
}

void syncDriftedTime(int sec)
{
  if (sec <= 0 && sec >= 60) {
    return;
  }

  tmElements_t tm = getTime();

  int yy, mmm, dd, hh, mm, ss;
  
  hh = tm.Hour;
  mm = tm.Minute;
  ss = tm.Second;
  dd = tm.Day;
  mmm = tm.Month;
  yy = tm.Year;

  // Increased 1 sec only to avoid callback loop.
  sec++;
  ss++;

  delay(sec * 1000);

  // correct time
  if (ss >= 60) {
    ss = ss - 60;
    mm++;
    if (mm == 60) {
      mm = 0;
      hh++;
      if (hh == 24) {
        hh = 0;
        dd++;
      }
    }
  }

  RTC.set(hh, mm, ss, dd, mmm, yy);
}
