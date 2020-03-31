#include <SoftwareSerial.h>

#define RxD 3 // BT Tx
#define TxD 4 // BT Rx


SoftwareSerial BT(RxD, TxD);

// Commands
// 1-6 for setting switch value
#define GETSINFO 7
#define GETTIME 8
#define SETTIME 9

String readData;
int command = 0;

void enableBTMode()
{
  delay(50);
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);

  delay(50);
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
//    delay(1000);
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
  if (command > 0 && command < 7)
  {
    int v = value.toInt();
    setSwitchValue(command, byte(v));
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
  }
}
