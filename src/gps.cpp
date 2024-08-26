#include <TinyGPS++.h>
#include <Arduino.h>
#include "gps.h"

float Latitude, Longitude;
int year, month, date, hour, minute, second;

std::vector<std::string> getGPSReadings(TinyGPSPlus gps)
{
    std::vector<std::string> values;
    String s;
    String DateString, TimeString, LatitudeString, LongitudeString;
    
    // Get location
    if (gps.location.isValid())
    {
        Latitude = gps.location.lat();
        LatitudeString = String(Latitude, 6);
        Longitude = gps.location.lng();
        LongitudeString = String(Longitude, 6);
        Serial.print("Latitude: ");
        Serial.println(LatitudeString);
        Serial.print("Longitude: ");
        Serial.println(LongitudeString);

        s += "http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=";
        s += LatitudeString;
        s += "+";
        s += LongitudeString;

        Serial.print(s);
    }

    // Get date
    if (gps.date.isValid())
    {
        DateString = "";
        date = gps.date.day();
        month = gps.date.month();
        year = gps.date.year();

        if (date < 10)
            DateString += '0';
        DateString += String(date);

        DateString += " / ";

        if (month < 10)
            DateString += '0';
        DateString += String(month);
        DateString += " / ";

        DateString += String(year);

        Serial.print("Date: ");
        Serial.println(DateString);
    }

    // Get time
    if (gps.time.isValid())
    {
        TimeString = "";
        hour = gps.time.hour(); // no adjustment initially
        minute = gps.time.minute();
        second = gps.time.second();

        // Adjust for time zone offset
        hour += 5;    // adjust by adding 5 hours for UTC+5 (adjust according to your time zone)
        minute += 30; // add 30 minutes for UTC+5:30

        // Handle wrap around if minute goes over 60
        if (minute >= 60)
        {
            minute -= 60; // subtract 60 minutes to bring it back within 60-minute format
            hour += 1;    // add 1 hour since 60 minutes is an hour
        }

        // Handle wrap around if hour goes over 24
        if (hour >= 24)
        {
            hour -= 24; // subtract 24 hours to bring it back within 24-hour format
        }

        if (hour < 10)
            TimeString += '0';
        TimeString += String(hour);
        TimeString += " : ";

        if (minute < 10)
            TimeString += '0';
        TimeString += String(minute);
        TimeString += " : ";

        if (second < 10)
            TimeString += '0';
        TimeString += String(second);

        Serial.print("Time: ");
        Serial.println(TimeString);
    }

    values.push_back(s.c_str());
    values.push_back(DateString.c_str());
    values.push_back(TimeString.c_str());
    
    return values;
}