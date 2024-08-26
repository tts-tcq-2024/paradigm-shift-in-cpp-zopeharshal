#include <assert.h>
#include <iostream>
#include "BatteryStatusChecker.hpp"

using namespace std;

Language currentLanguage = ENGLISH;
 
const char* getErrorMessage(const char* errorMessage) {
  static map<string, map<Language, string>> errorMessages = {
    {"Temperature out of range!", {
      {ENGLISH, "Temperature out of range!"},
      {GERMAN, "Temperatur außerhalb des zulässigen Bereichs!"}
    }},
    {"State of Charge out of range!", {
      {ENGLISH, "State of Charge out of range!"},
      {GERMAN, "Ladezustand außerhalb des zulässigen Bereichs!"}
    }},
    {"Charge Rate out of range!", {
      {ENGLISH, "Charge Rate out of range!"},
      {GERMAN, "Laderate außerhalb des zulässigen Bereichs!"}
    }}
  };
  return errorMessages[errorMessage][currentLanguage].c_str();
}

bool isValueInRange(float value, float min, float max, const char* errorMessage){
  if(value < min || value > max) {
    cout << getErrorMessage(errorMessage) << endl;
    return false;
  }
  return true;
}
 
bool isBatteryOk(float temperature, float soc, float chargeRate) {
  bool isTemperatureOk = isValueInRange(temperature, 0, 45, "Temperature out of range!");
  bool isSocOk = isValueInRange(soc, 20, 80, "State of Charge out of range!");
  bool isChargeRateOk = isValueInRange(chargeRate, 0, 0.8, "Charge Rate out of range!");
  return isTemperatureOk && isSocOk && isChargeRateOk;
}
