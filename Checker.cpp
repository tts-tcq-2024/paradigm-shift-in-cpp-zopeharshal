#include <assert.h>
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

enum class RangeStatus { OK, LOW, HIGH, WARNING };

// Check range and return status
RangeStatus checkRange(float value, float min, float max) {
    float warningTolerance = (max - min) * 0.05; // 5% tolerance

    if (value < min) {
        return RangeStatus::LOW;
    }
    if (value > max) {
        return RangeStatus::HIGH;
    }
    if (value <= min + warningTolerance || value >= max - warningTolerance) {
        return RangeStatus::WARNING; // Approaching limit
    }

    return RangeStatus::OK;
}

// Wrapper functions for specific checks
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

// Map status messages for different languages
unordered_map<RangeStatus, string> getStatusMessages(const string& language) {
    unordered_map<RangeStatus, string> messages;
    if (language == "de") { // German
        messages[RangeStatus::LOW] = " ist zu niedrig!";
        messages[RangeStatus::HIGH] = " ist zu hoch!";
        messages[RangeStatus::WARNING] = " erreicht die Grenze!";
    } else { // English
        messages[RangeStatus::LOW] = " is too low!";
        messages[RangeStatus::HIGH] = " is too high!";
        messages[RangeStatus::WARNING] = " is approaching limit!";
    }
    return messages;
}

// Simplified print function
void printStatusMessage(const string& parameterName, RangeStatus status, const string& language) {
    auto messages = getStatusMessages(language);
    string message = messages[status];
    if (!message.empty()) {
        cout << parameterName + message << "\n";
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
