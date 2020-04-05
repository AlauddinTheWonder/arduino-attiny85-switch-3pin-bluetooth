#include <SoftwareSerial.h>

#ifndef RxD
#define RxD 3 // BT Tx
#define TxD 4 // BT Rx
#endif

#ifndef TOTAL_SWT
#define TOTAL_SWT 2 // should define on main ino
#endif


SoftwareSerial BT(RxD, TxD);

// Commands
// 1-6 for setting switch value
#define PINGBACK 999
#define GETSWITCHNUM 99
#define GETSINFO 7
#define GETTIME 8
#define SETTIME 9

String readData;
int command = 0;

void enableBTMode()
{
//  delay(50);
//  pinMode(RxD, INPUT);
//  pinMode(TxD, OUTPUT);
//  delay(50);
  
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

void executeCommand(int command, String value)
{
  if (command == PINGBACK)
  {
    // Should use on BT connected
    BT.println(PINGBACK);
  }
  else if (command == GETSWITCHNUM)
  {
    BT.println(TOTAL_SWT);
  }
  
  else if (command > 0 && command < 7)
  {
    int v = value.toInt();
    setSwitchValue(command, byte(v));
    delay(50);
    BT.println(getSwitchValue(byte(command)));
  }
  else if (command == GETSINFO)
  {
    int v = value.toInt();
    BT.println(getSwitchValue(byte(v)));
  }
  else if (command == GETTIME)
  {
    BT.println(getTimeNow());
  }
  else if (command == SETTIME) {
    long t = value.toInt();
    if (t > 0) {
      setTimeNow(t);
      delay(100);
      BT.println(getTimeNow());
    }
    else {
      BT.println(-1);
    }
  }
}
