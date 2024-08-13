#include <assert.h>
#include <iostream>
#include <string>
using namespace std;

enum class RangeStatus { OK, LOW, HIGH, WARNING };

// Function to check for status ranges
RangeStatus checkRange(float value, float min, float max) {
    float warningTolerance = (max - min) * 0.05; // 5% tolerance

    if (value < min) {
        return RangeStatus::LOW;
    }
    if (value > max) {
        return RangeStatus::HIGH;
    }
    if (value <= min + warningTolerance) {
        return RangeStatus::WARNING; // Approaching lower limit
    }
    if (value >= max - warningTolerance) {
        return RangeStatus::WARNING; // Approaching upper limit
    }

    return RangeStatus::OK;
}

RangeStatus checkTemperature(float temperature) {
    return checkRange(temperature, 0, 45);
}

RangeStatus checkSoc(float soc) {
    return checkRange(soc, 20, 80);
}

RangeStatus checkChargeRate(float chargeRate) {
    return checkRange(chargeRate, 0, 0.8);
}

bool batteryIsOk(float temperature, float soc, float chargeRate) {
    return checkTemperature(temperature) == RangeStatus::OK &&
           checkSoc(soc) == RangeStatus::OK &&
           checkChargeRate(chargeRate) == RangeStatus::OK;
}

// Function to get status messages based on parameter name and status
string getStatusMessage(const string& parameterName, RangeStatus status, const string& language) {
    if (language == "de") { // German
        switch (status) {
            case RangeStatus::LOW: return parameterName + " ist zu niedrig!";
            case RangeStatus::HIGH: return parameterName + " ist zu hoch!";
            case RangeStatus::WARNING: return parameterName + " erreicht die Grenze!";
            default: return "";
        }
    } else { // English
        switch (status) {
            case RangeStatus::LOW: return parameterName + " is too low!";
            case RangeStatus::HIGH: return parameterName + " is too high!";
            case RangeStatus::WARNING: return parameterName + " is approaching limit!";
            default: return "";
        }
    }
}

// Simplified print function
void printStatusMessage(const string& parameterName, RangeStatus status, const string& language) {
    string message = getStatusMessage(parameterName, status, language);
    if (!message.empty()) {
        cout << message << "\n";
    }
}

// Print battery status for all parameters
void printBatteryStatus(float temperature, float soc, float chargeRate, const string& language) {
    printStatusMessage("Temperature", checkTemperature(temperature), language);
    printStatusMessage("State of Charge", checkSoc(soc), language);
    printStatusMessage("Charge Rate", checkChargeRate(chargeRate), language);
}

int main() {
    // Basic functional tests
    assert(batteryIsOk(25, 70, 0.7) == true);
    assert(batteryIsOk(50, 85, 0) == false);
    
    // Testing warning messages in English
    printBatteryStatus(42, 76, 0.75, "en"); 
    printBatteryStatus(1, 19, 0.01, "en");   

    // Testing warning messages in German
    printBatteryStatus(42, 76, 0.75, "de"); 
    printBatteryStatus(1, 19, 0.01, "de");  

    return 0;
}
