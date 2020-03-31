/* 
 * Alauddin Ansari
 * 2018-12-15
 * Time and DS1307 related Functions
 * Dependencies:
 * 1. Time Lib
 * 2. DS1307RTC Lib
 */

byte retries = 0;

boolean validateTime() {
  int yy = year();
  int mon = month();
  int dd = day();
  int hh = hour();
  
  if (yy < 2010) {
    return false;
  }
  if (mon <= 0 || mon > 12) {
    return false;
  }
  if (dd <= 0 || dd > 31) {
    return false;
  }
  if (hh < 0 || hh > 23) {
    return false;
  }
  return true;
}

void connectDS1307() {
  
  while(timeStatus() != timeSet && retries < 3) {
    setSyncProvider(RTC.get);
    retries++;
    delay(500);
  }
  if (!validateTime()) {
    setTime(1585699200); // Setting dummy as 1 April 2020 00:00:00 GMT
  }
//   setSyncInterval(3600);
}

unsigned long getTimeNow() {
  return now();
}

void setTimeNow(unsigned long t) {
  setTime(t);
  delay(500);
  if (validateTime()) {
    RTC.set(now());
  }
}

int getDriftedTime() {
  int mmm = month();

  switch(mmm) {
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

void syncDriftedTime(int sec) {
  int yy, mmm, dd, hh, mm, ss;

  if (sec <= 0 && sec >= 60) {
    return;
  }
  
  yy = year();
  mmm = month();
  dd = day();
  hh = hour();
  mm = minute();
  ss = second();

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

  setTime(hh, mm, ss, dd, mmm, yy);
}
