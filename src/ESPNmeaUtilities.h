/*********
Utilities for NMEA networks that are for ESP/Arduino chips
*********/
#ifndef ESPNmeaUtilities_h
#define ESPNmeaUtilities_h

#ifndef Arduino_h
#include <Arduino.h>
#endif

#ifndef VoltsandAmpsAdc1_h
#include <VoltsandAmpsAdc1.h>
#endif

#ifndef ActivationCounter_h
#include <ActivationCounter.h>
#endif

class ESPNmeaUtilities
{
public:
  static String createBilgeNmea0183Sentence(ActivationCounter* bilge);
  static String createVoltageNmea0183Sentence(VoltsandAmpsAdc1* voltMonitor);

private:
  static int _calc_NMEA_Checksum(char *buf, int cnt);
};
#endif
