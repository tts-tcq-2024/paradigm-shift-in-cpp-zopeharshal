#include <assert.h>
#include <iostream>
using namespace std;

enum class RangeStatus { OK, LOW, HIGH, WARNING };
 
// Generic function to check range and return status
RangeStatus checkRange(float value, float min, float max) {
    if (value < min) {
        return RangeStatus::LOW;
    }
    if (value > max) {
        return RangeStatus::HIGH;
    }
    return RangeStatus::OK;
}

// Generic function to check for warnings based on the upper limit
RangeStatus checkWarning(float value, float min, float max, float warningTolerance) {
    if (value < min) {
        return RangeStatus::LOW;
    }
    if (value > max) {
        return RangeStatus::HIGH;
    }
    if (value >= (max - warningTolerance) && value <= max) {
        return RangeStatus::WARNING;
    }
    if (value >= min && value <= (min + warningTolerance)) {
        return RangeStatus::WARNING;
    }
    return RangeStatus::OK;
}
 
// Specific range check functions using the generic function
RangeStatus checkTemperature(float temperature) {
    return checkRange(temperature, 0, 45);
}

RangeStatus checkSoc(float soc) {
    return checkRange(soc, 20, 80);
}

RangeStatus checkChargeRate(float chargeRate) {
    return checkRange(chargeRate, 0, 0.8);
}

// Specific warning check functions
RangeStatus checkTemperatureWarning(float temperature) {
    return checkWarning(temperature, 0, 45, 2.25); // 5% of 45 is 2.25
}

RangeStatus checkSocWarning(float soc) {
    return checkWarning(soc, 20, 80, 4); // 5% of 80 is 4
}

RangeStatus checkChargeRateWarning(float chargeRate) {
    return checkWarning(chargeRate, 0, 0.8, 0.04); // 5% of 0.8 is 0.04
}

bool batteryIsOk(float temperature, float soc, float chargeRate) {
    return checkTemperature(temperature) == RangeStatus::OK &&
           checkSoc(soc) == RangeStatus::OK &&
           checkChargeRate(chargeRate) == RangeStatus::OK;
}

// Generic function to print status messages
void printStatusMessage(const char* parameterName, RangeStatus status) {
    if (status == RangeStatus::LOW) {
        cout << parameterName << " is too low!\n";
    } else if (status == RangeStatus::HIGH) {
        cout << parameterName << " is too high!\n";
    } else if (status == RangeStatus::WARNING) {
        cout << parameterName << " is approaching limit!\n";
    }
}

// Specific status print functions using the generic function
void printTemperatureStatus(float temperature) {
    printStatusMessage("Temperature", checkTemperatureWarning(temperature));
}

void printSocStatus(float soc) {
    printStatusMessage("State of Charge", checkSocWarning(soc));
}

void printChargeRateStatus(float chargeRate) {
    printStatusMessage("Charge Rate", checkChargeRateWarning(chargeRate));
}

void printBatteryStatus(float temperature, float soc, float chargeRate) {
    printTemperatureStatus(temperature);
    printSocStatus(soc);
    printChargeRateStatus(chargeRate);
}

int main() {
    assert(batteryIsOk(25, 70, 0.7) == true);
    assert(batteryIsOk(50, 85, 0) == false);
    
    // Testing with print statements
    printBatteryStatus(25, 70, 0.7);  // Should print nothing
    printBatteryStatus(50, 85, 0);    // Should print messages for temperature and soc
    printBatteryStatus(20, 20, 0);    // Should print warning for approaching discharge
    printBatteryStatus(80, 80, 0.75);  // Should print warning for approaching charge-peak
    printBatteryStatus(43, 78, 0.78);  // Should print warnings for temperature and charge rate
}

