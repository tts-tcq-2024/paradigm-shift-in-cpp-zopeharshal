#ifndef BATTERYSTATUSCHECKER_HPP
#define BATTERYSTATUSCHECKER_HPP

#include <map>
#include <string>
 
enum Language { ENGLISH, GERMAN }; 
extern Language currentLanguage;

const char* getErrorMessage(const char* errorMessage);
bool isValueInRange(float value, float min, float max, const char* errorMessage);
bool isBatteryOk(float temperature, float soc, float chargeRate);

#endif //BATTERYSTATUSCHECKER_HPP
