#include <string>
#include <Wire.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include "ESP8266WiFi.h"
#include <TinyGPS++.h>

#include "sendMail.h"
#include "ultrasonic.h"
#include "button.h"
#include "gps.h"
#include "gyro.h"

// Select SDA and SCL pins for I2C communication
const uint8_t scl = D1;
const uint8_t sda = D2;

// Configure Wifi
const char *ssid = "YOUR_WIFI_SSID";
const char *password = "YOUR_WIFI_PASSWORD";

// Initializations
TinyGPSPlus gps;
SoftwareSerial SerialGPS(4, 5);

float distance;
bool done = false;
bool button = false;
const int BUTTON_PIN = 16;
std::vector<double> values(4);

// Define warning and SOS thresholds
int TEMPERATURE_WARNING_TH = 51;
int DISTANCE_WARNING_TH = 30;
int TEMPERATURE_SOS_TH = 54;
int DISTANCE_SOS_TH = 2;

bool SOS(std::string msg)
{
  if (Serial.available() <= 0)
  {
    Serial.print("No GPS module connected!");
    return false;
  }
  std::string sos_msg;

  while (SerialGPS.available() > 0)
  {
    if (gps.encode(SerialGPS.read()))
    {
      std::vector<std::string> GPSReadings = getGPSReadings(gps);
      sos_msg = msg + "\n" + "Location: " + GPSReadings[0] + "\n" + "Time: " + GPSReadings[2] + "\n" + "Date: " + GPSReadings[1] + "\n";
      sendSOS(msg);
      break;
    }
    else
    {
      Serial.print("Trying to Get location.\n");
      break;
    }
  }
  return true;
}

void setup()
{
  Serial.begin(115200);
  Wire.begin(sda, scl);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
  Serial.println();

  delay(2000);
  i2cScanner();
  MPU6050_Init(); // SCL-> D1 && SDA-> D2
  configUltraSonic(); // Echo-> D5 && Trig-> D6
  configButton();     // D0
}

void loop()
{
  while (!done)
  {
    // Get sensor values
    button = digitalRead(BUTTON_PIN);
    distance = getUltraSonicValue();
    values = getGyroValues();
    
    // Check if button pressed
    if (button == LOW)
    {
      Serial.print("Button pressed! Sending SOS...");
      std::string msg = "IM IN DANGER!";
      if (SOS(msg))
      {
        Serial.println("SOS email sent!");
      }
      else
      {
        sendSOS(msg);
        Serial.println("SOS email sent without location!");
      }
      done = true;
      break;
    }

    // Check distance thresholds
    if (distance < DISTANCE_WARNING_TH)
    {
      Serial.print("Close proximity (cm) WARNING: ");
      Serial.println(distance);
      Serial.print("Click button to send SOS!");
      Serial.println("");
      delay(100);
      if (distance <= DISTANCE_SOS_TH)
      {
        Serial.print("Possible crash detected!\n");
        std::string msg = "Very close proximity!\n";
        if (SOS(msg))
        {
          Serial.println("SOS email sent!\n");
        }
        else
        {
          sendSOS(msg);
          Serial.println("SOS email sent without location!\n");
        }
        done = true;
        break;
      }
    }

    // Check gyro thresholds
    if ((abs(values[0]) >= 0.75) || (abs(values[1]) >= 0.75) || (values[2] < 0))
    {
      Serial.print("Roll-over detected! Sending SOS...");
      Serial.println("");
      // Send SOS
      std::string msg = "Vehicle roll-over detected!";
      if (SOS(msg))
      {
        Serial.println("SOS email sent!");
      }
      else
      {
        sendSOS(msg);
        Serial.println("SOS email sent without location!");
      }
      Serial.println("SOS email sent!");
      done = true;
      break;
    }

    // Check temperature thresholds
    if (abs(values[3]) >= TEMPERATURE_WARNING_TH)
    {
      // Temperature warning
      Serial.print("High temperature (degrees) WARNING!: ");
      Serial.println(values[3]);
      Serial.print("Click button to send SOS!");

      if (values[3] <= TEMPERATURE_SOS_TH)
      {
        Serial.print("Fire detected!");
        std::string msg = "Temperature threshold exceeded! Possible Fire!";
        if (SOS(msg))
        {
          Serial.println("SOS email sent!");
        }
        else
        {
          sendSOS(msg);
          Serial.println("SOS email sent without location!");
        }
        Serial.println("SOS email sent!");
        done = true;
        break;
      }
    }

    delay(500);
  }
  done=true;
}