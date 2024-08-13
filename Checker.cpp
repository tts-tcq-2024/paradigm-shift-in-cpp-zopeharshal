#include <iostream>
using namespace std;

enum class RangeStatus { OK, LOW, HIGH, WARNING };

// Generic function to check range and warning status
RangeStatus checkRangeWithWarning(float value, float min, float max, float warningTolerance) {
    if (value < min) {
        return RangeStatus::LOW;
    }
    if (value > max) {
        return RangeStatus::HIGH;
    }
    if (value >= (max - warningTolerance) && value <= max) {
        return RangeStatus::WARNING; // Approaching high limit
    }
    if (value >= min && value <= (min + warningTolerance)) {
        return RangeStatus::WARNING; // Approaching low limit
    }
    return RangeStatus::OK;
}

// Range limits and tolerances for parameters
const float TEMP_MIN = 0;
const float TEMP_MAX = 45;
const float TEMP_WARNING_TOLERANCE = 2.25; // 5% of 45

const float SOC_MIN = 20;
const float SOC_MAX = 80;
const float SOC_WARNING_TOLERANCE = 4; // 5% of 80

const float CHARGE_RATE_MIN = 0;
const float CHARGE_RATE_MAX = 0.8;
const float CHARGE_RATE_WARNING_TOLERANCE = 0.04; // 5% of 0.8

bool batteryIsOk(float temperature, float soc, float chargeRate) {
    return checkRangeWithWarning(temperature, TEMP_MIN, TEMP_MAX, TEMP_WARNING_TOLERANCE) == RangeStatus::OK &&
           checkRangeWithWarning(soc, SOC_MIN, SOC_MAX, SOC_WARNING_TOLERANCE) == RangeStatus::OK &&
           checkRangeWithWarning(chargeRate, CHARGE_RATE_MIN, CHARGE_RATE_MAX, CHARGE_RATE_WARNING_TOLERANCE) == RangeStatus::OK;
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

// Print status for all parameters
void printBatteryStatus(float temperature, float soc, float chargeRate) {
    printStatusMessage("Temperature", checkRangeWithWarning(temperature, TEMP_MIN, TEMP_MAX, TEMP_WARNING_TOLERANCE));
    printStatusMessage("State of Charge", checkRangeWithWarning(soc, SOC_MIN, SOC_MAX, SOC_WARNING_TOLERANCE));
    printStatusMessage("Charge Rate", checkRangeWithWarning(chargeRate, CHARGE_RATE_MIN, CHARGE_RATE_MAX, CHARGE_RATE_WARNING_TOLERANCE));
}

int main() {
    // Test cases
    cout << "Testing batteryIsOk:\n";
    cout << "Battery status (25, 70, 0.7): " << (batteryIsOk(25, 70, 0.7) ? "OK" : "NOT OK") << endl;
    cout << "Battery status (50, 85, 0): " << (batteryIsOk(50, 85, 0) ? "OK" : "NOT OK") << endl;

    cout << "\nTesting printBatteryStatus:\n";
    printBatteryStatus(25, 70, 0.7);  // Should print nothing
    printBatteryStatus(50, 85, 0);    // Should print messages for temperature and soc
    printBatteryStatus(20, 20, 0);    // Should print warning for approaching discharge
    printBatteryStatus(80, 80, 0.75);  // Should print warning for approaching charge-peak
    printBatteryStatus(43, 78, 0.78);  // Should print warnings for temperature and charge rate

    return 0;
}
