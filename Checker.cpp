#include <assert.h>
#include <iostream>
using namespace std;

enum class RangeStatus { OK, LOW, HIGH, WARNING };

RangeStatus checkRange(float value, float min, float max) {
    float warningTolerance = (max - min) * 0.05; // 5% tolerance
    if (value < min) {
        return RangeStatus::LOW;
    }
    if (value > max) {
        return RangeStatus::HIGH;
    }
    if (value >= max - warningTolerance) {
        return RangeStatus::WARNING; // Approaching upper limit
    }
    if (value <= min + warningTolerance) {
        return RangeStatus::WARNING; // Approaching lower limit
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

void printStatusMessage(const char* parameterName, RangeStatus status) {
    if (status == RangeStatus::LOW) {
        cout << parameterName << " is too low!\n";
    } else if (status == RangeStatus::HIGH) {
        cout << parameterName << " is too high!\n";
    } else if (status == RangeStatus::WARNING) {
        cout << parameterName << " is approaching limit!\n";
    }
}

void printTemperatureStatus(float temperature) {
    printStatusMessage("Temperature", checkTemperature(temperature));
}

void printSocStatus(float soc) {
    printStatusMessage("State of Charge", checkSoc(soc));
}

void printChargeRateStatus(float chargeRate) {
    printStatusMessage("Charge Rate", checkChargeRate(chargeRate));
}

void printBatteryStatus(float temperature, float soc, float chargeRate) {
    printTemperatureStatus(temperature);
    printSocStatus(soc);
    printChargeRateStatus(chargeRate);
}

int main() {
    assert(batteryIsOk(25, 70, 0.7) == true);
    assert(batteryIsOk(50, 85, 0) == false);
    
    printBatteryStatus(25, 70, 0.7);  // Should print nothing
    printBatteryStatus(50, 85, 0);    // Should print messages for temperature and soc
    
    // Testing warnings
    printBatteryStatus(42, 76, 0.75);  // Should print warnings for Temperature and State of Charge
    printBatteryStatus(1, 19, 0.01);    // Should print warnings for Temperature and State of Charge
}

