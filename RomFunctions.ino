#define ADDR_VERS 0
#ifndef TOTAL_SWT
#define TOTAL_SWT 2 // should define on main ino
#endif

void initVarsFromEEPROM()
{
  int vs = EEPROM.read(ADDR_VERS);

  if (vs == TOTAL_SWT) {
    uint8_t cnt = 1;
    for (uint8_t r = 0; r < TOTAL_SWT; r++)
    {
      for (uint8_t c = 1; c <= 2; c++) // 0=Pin, 1=On, 2=Off
      {
        Switches[r][c] = EEPROM.read(cnt);
        cnt++;
      }
    }
  }
  else {
    EEPROM.write(ADDR_VERS, TOTAL_SWT);

    uint8_t cnt = 1;
    for (uint8_t r = 0; r < TOTAL_SWT; r++)
    {
      for (uint8_t c = 1; c <= 2; c++) // 0=Pin, 1=On, 2=Off
      {
        EEPROM.write(cnt, Switches[r][c]);
        cnt++;
      }
    }
  }
}

byte getSwitchValue(byte addr)
{
  return EEPROM.read(addr);
}

void setSwitchValue(byte addr, byte val)
{
  EEPROM.write(addr, val);
}

void clearEEPROM()
{
  for (byte i = 0; i < EEPROM.length(); i++)
  {
    EEPROM.write(i, 0);
  }
}
