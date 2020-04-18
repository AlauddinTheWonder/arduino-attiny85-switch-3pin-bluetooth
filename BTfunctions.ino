#include <SoftwareSerial.h>

#ifndef RxD
#define RxD 3 // BT Tx
#define TxD 4 // BT Rx
#endif

#ifndef TOTAL_SWT
#define TOTAL_SWT 2 // should define on main ino
#endif

SoftwareSerial BT(RxD, TxD);

#define MAX_ROM_VAL 255

// Commands
#define PINGBACK 255
#define GET_NUM_SWITCH 254
#define GET_TIME 253
#define SET_TIME 252
#define GET_ROM_VAL 251
#define DRIFT_TIME 250 // must be same as defined in DRIFT_ADDR on RomFunctions.ino

String readData;
int command = 0;

void enableBTMode()
{
  BT.begin(9600);

  delay(500);
}

void runBT()
{
  while (!BT.available());
  
  while(BT.available())
  {
    char c = BT.read();
    readData += c;
    delay(10);
  }

  if(readData.length() > 0)
  {
    analyzeData(readData);
    readData = "";
  }
}

void analyzeData(String str)
{
  if (command > 0) {
    executeCommand(command, str);
    command = 0;
  }
  else {
    command = str.toInt();
  }
}

void printError()
{
  BT.println(-1);
}

void executeCommand(int command, String value)
{
  long val = value.toInt();

  // Indicates BT is connected with master device
  // A callback to connected device for identification of this program
  if (command == PINGBACK)
  {
    BT.println(PINGBACK);
  }
  
  // Get num of switch device support
  else if (command == GET_NUM_SWITCH)
  {
    BT.println(TOTAL_SWT);
  }
  
  // Get current time from RTC in timestamp
  else if (command == GET_TIME)
  {
    BT.println(getTimeNow());
  }
  // Set RTC time, value in timestamp
  else if (command == SET_TIME && val > 0) {
    setTimeNow(val);
    delay(100);
    BT.println(getTimeNow());
  }

  // Read value from EEPROM
  else if (command == GET_ROM_VAL && (val >= 0 && val <= MAX_ROM_VAL))
  {
    BT.println(getROMvalue(byte(val)));
  }

  // Write value to EEPROM
  else if (command >= 0 && command <= MAX_ROM_VAL && val >= 0 && val < MAX_ROM_VAL)
  {
    setROMvalue(command, byte(val));
    delay(50);
    BT.println(getROMvalue(byte(command)));
  }
  else {
    printError();
  }
}
