/*********
Utilities for NMEA networks that are for ESP/Arduino chips
*********/
#include <ESPNmeaUtilities.h>

static String ESPNmeaUtilities::createBilgeNmea0183Sentence(ActivationCounter* Counter)
{
    String nmeaSentence;
    nmeaSentence = "$IIXDR";
    nmeaSentence = String(nmeaSentence + ",PUMP," + counter->getCycleCounter() + ",CYCLE," + counter->getName());
    nmeaSentence = String(nmeaSentence + ",PUMP," + counter->getDuration() + ",TOTDUR," + counter->getName());
    nmeaSentence = String(nmeaSentence + ",PUMP," + counter->getLastDuration() + ",LASTDUR," + counter->getName());
    nmeaSentence = String(nmeaSentence + ",PUMP," + counter->getLastTime() + ",LASTTIME," + counter->getName());
    nmeaSentence = String(nmeaSentence + ",PUMP," + counter->getLongestDuration() + ",LONGDUR," + counter->getName());
    nmeaSentence = String(nmeaSentence + ",PUMP," + counter->getLongestTime() + ",LONGTIME," + counter->getName());
    int checkSum = ESPNmeaUtilities::_calc_NMEA_Checksum(const_cast<char *>(nmeaSentence.c_str()), nmeaSentence.length());
    nmeaSentence = String(nmeaSentence + "*" + String(checkSum, HEX) + "\r\n");

    return nmeaSentence;
}

static String ESPNmeaUtilities::createVoltageNmea0183Sentence(VoltsandAmpsAdc1* voltMonitor)
{
    String nmeaSentence;
        nmeaSentence = "$IIXDR";
        nmeaSentence = String(nmeaSentence + ",BATT," + String(voltMonitor->getVoltage(), 2) + ",V," + voltMonitor->getName());
        nmeaSentence = String(nmeaSentence + ",BATT," + String(voltMonitor->getAmperage(), 2) + ",A," + voltMonitor->getName());
        int checkSum = ESPNmeaUtilities::_calc_NMEA_Checksum(const_cast<char *>(nmeaSentence.c_str()), nmeaSentence.length());
        nmeaSentence = String(nmeaSentence + "*" + String(checkSum, HEX) + "\r\n");

    return nmeaSentence;
}

static int ESPNmeaUtilities::_calc_NMEA_Checksum(char *buf, int cnt)
{
  char Character;
  int Checksum = 0;
  int i; // loop counter

  //foreach(char Character in sentence)
  for (i = 0; i < cnt; ++i)
  {
    Character = buf[i];
    switch (Character)
    {
    case '$':
      // Ignore the dollar sign
      break;
    case '*':
      // Stop processing before the asterisk
      i = cnt;
      continue;
    default:
      // Is this the first value for the checksum?
      if (Checksum == 0)
      {
        // Yes. Set the checksum to the value
        Checksum = Character;
      }
      else
      {
        // No. XOR the checksum with this character's value
        Checksum = Checksum ^ Character;
      }
      break;
    }
  }

  // Return the checksum
  return (Checksum);
}