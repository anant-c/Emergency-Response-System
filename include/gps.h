#include <vector>
#include <string>
#include <TinyGPS++.h>

#ifndef GPS_H_
#define GPS_H_

std::vector<std::string> getGPSReadings(TinyGPSPlus gps);

#endif