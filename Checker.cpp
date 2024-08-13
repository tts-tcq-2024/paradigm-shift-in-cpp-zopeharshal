#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

// Language support
enum class Language { ENGLISH, GERMAN };
Language currentLanguage = Language::ENGLISH;

// Status enumeration
enum class RangeStatus { OK, LOW, HIGH, LOW_WARNING, HIGH_WARNING };

// Parameter boundaries structure
struct ParameterRange {
    float min;
    float max;
    float warningTolerance;
};

// Define the ranges and warning tolerances
const ParameterRange temperatureRange = {0, 45, 2.25};  // 5% of 45
const ParameterRange socRange = {20, 80, 4};            // 5% of 80
const ParameterRange chargeRateRange = {0, 0.8, 0.04};  // 5% of 0.8

// Generic function to check range and return status
RangeStatus checkRange(float value, const ParameterRange& range) {
    if (value < range.min) return RangeStatus::LOW;
    if (value > range.max) return RangeStatus::HIGH;

    // Check for warning levels
    bool isLowWarning = (value <= (range.min + range.warningTolerance));
    bool isHighWarning = (value >= (range.max - range.warningTolerance));

    if (isLowWarning) return RangeStatus::LOW_WARNING;
    if (isHighWarning) return RangeStatus::HIGH_WARNING;

    return RangeStatus::OK;
}

// Specific range check functions using the generic function
RangeStatus checkTemperature(float temperature) {
    return checkRange(temperature, temperatureRange);
}

RangeStatus checkSoc(float soc) {
    return checkRange(soc, socRange);
}

RangeStatus checkChargeRate(float chargeRate) {
    return checkRange(chargeRate, chargeRateRange);
}

bool batteryIsOk(float temperature, float soc, float chargeRate) {
    return checkTemperature(temperature) == RangeStatus::OK &&
           checkSoc(soc) == RangeStatus::OK &&
           checkChargeRate(chargeRate) == RangeStatus::OK;
}

// Generic function to get status messages
string getStatusMessage(const char* parameterName, RangeStatus status) {
    static unordered_map<RangeStatus, string> messagesEN = {
        {RangeStatus::LOW, string(parameterName) + " is too low!"},
        {RangeStatus::HIGH, string(parameterName) + " is too high!"},
        {RangeStatus::LOW_WARNING, string(parameterName) + " is approaching discharge!"},
        {RangeStatus::HIGH_WARNING, string(parameterName) + " is approaching charge-peak!"},
        {RangeStatus::OK, ""}
    };

    static unordered_map<RangeStatus, string> messagesDE = {
        {RangeStatus::LOW, string(parameterName) + " ist zu niedrig!"},
        {RangeStatus::HIGH, string(parameterName) + " ist zu hoch!"},
        {RangeStatus::LOW_WARNING, string(parameterName) + " nähert sich der Entladung!"},
        {RangeStatus::HIGH_WARNING, string(parameterName) + " nähert sich dem Ladevorgang!"},
        {RangeStatus::OK, ""}
    };

    return (currentLanguage == Language::ENGLISH) ? messagesEN[status] : messagesDE[status];
}

// Unified status printing function
void printStatus(const char* parameterName, RangeStatus status) {
    string message = getStatusMessage(parameterName, status);
    if (!message.empty()) {
        cout << message << "\n";
    }
}

void printBatteryStatus(float temperature, float soc, float chargeRate) {
    printStatus("Temperature", checkTemperature(temperature));
    printStatus("State of Charge", checkSoc(soc));
    printStatus("Charge Rate", checkChargeRate(chargeRate));
}

int main() {
    // Tests
    assert(batteryIsOk(25, 70, 0.7) == true);
    assert(batteryIsOk(50, 85, 0) == false);
    assert(batteryIsOk(0, 19, 0.7) == false);  // Low Temperature
    assert(batteryIsOk(20, 20, 0.9) == false);  // Low SoC and High Charge Rate

    // Testing with print statements
    printBatteryStatus(25, 70, 0.7);  // Should print nothing
    printBatteryStatus(50, 85, 0);    // Should print messages for temperature and soc
    printBatteryStatus(2, 22, 0.5);    // Should print warning for temperature
    printBatteryStatus(2, 18, 0.5);    // Should print error for temperature and soc

    // Test language change
    currentLanguage = Language::GERMAN;
    printBatteryStatus(2, 18, 0.5); // Should print German messages

    return 0;
}
