#define ADDR_VERS 0

void initVarsFromEEPROM()
{
  int vs = EEPROM.read(ADDR_VERS);

  if (vs > 0 && vs < 255) {
    Switch_1_on = EEPROM.read(1);
    Switch_1_off = EEPROM.read(2);

    Switch_2_on = EEPROM.read(3);
    Switch_2_off = EEPROM.read(4);

    Switch_3_on = EEPROM.read(5);
    Switch_3_off = EEPROM.read(6);
  }
  else {
//    clearEEPROM();
    delay(50);
    EEPROM.write(ADDR_VERS, 1);
    EEPROM.write(1, Switch_1_on);
    EEPROM.write(2, Switch_1_off);
    EEPROM.write(3, Switch_2_on);
    EEPROM.write(4, Switch_2_off);
    EEPROM.write(5, Switch_3_on);
    EEPROM.write(6, Switch_3_off);
  }
}

byte getSwitchValue(byte addr)
{
  return EEPROM.read(addr);
}

void setSwitchValue(byte addr, byte val)
{
  EEPROM.write(addr, val);
  delay(10);
  int vs = EEPROM.read(ADDR_VERS);
  delay(10);
  if (vs >= 250) {
    vs = 0;
  }
  EEPROM.write(ADDR_VERS, ++vs);
}

void clearEEPROM()
{
  for (byte i = 0; i < EEPROM.length(); i++)
  {
    EEPROM.write(i, 0);
  }
}
