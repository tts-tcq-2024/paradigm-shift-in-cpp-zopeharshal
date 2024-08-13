#include <iostream>
using namespace std;

enum class RangeStatus { OK, LOW, HIGH, WARNING };

// Define a struct for parameters to improve clarity
struct ParameterLimits {
    float min;
    float max;
    float warningTolerance;
};

// Function to check the status of a value based on defined limits
RangeStatus checkValue(float value, const ParameterLimits& limits) {
    if (value < limits.min) {
        return RangeStatus::LOW;
    }
    if (value > limits.max) {
        return RangeStatus::HIGH;
    }
    return RangeStatus::OK;
}

// Function to check for warning status
RangeStatus checkWarning(float value, const ParameterLimits& limits) {
    if (value < limits.min) {
        return RangeStatus::LOW;
    }
    if (value > limits.max) {
        return RangeStatus::HIGH;
    }
    if (value >= (limits.max - limits.warningTolerance)) {
        return RangeStatus::WARNING; // Approaching high limit
    }
    if (value <= (limits.min + limits.warningTolerance)) {
        return RangeStatus::WARNING; // Approaching low limit
    }
    return RangeStatus::OK;
}

// Define limits for each parameter
const ParameterLimits TEMP_LIMITS = {0, 45, 2.25};   // 5% of 45
const ParameterLimits SOC_LIMITS = {20, 80, 4};       // 5% of 80
const ParameterLimits CHARGE_RATE_LIMITS = {0, 0.8, 0.04}; // 5% of 0.8

bool batteryIsOk(float temperature, float soc, float chargeRate) {
    return checkValue(temperature, TEMP_LIMITS) == RangeStatus::OK &&
           checkValue(soc, SOC_LIMITS) == RangeStatus::OK &&
           checkValue(chargeRate, CHARGE_RATE_LIMITS) == RangeStatus::OK;
}

// Function to print status messages based on range and warning checks
void printStatusMessage(const char* parameterName, float value, const ParameterLimits& limits) {
    RangeStatus status = checkWarning(value, limits);
    switch (status) {
        case RangeStatus::LOW:
            cout << parameterName << " is too low!\n";
            break;
        case RangeStatus::HIGH:
            cout << parameterName << " is too high!\n";
            break;
        case RangeStatus::WARNING:
            cout << parameterName << " is approaching limit!\n";
            break;
        default:
            break; // OK state does not require any output
    }
}

// Print status for all parameters
void printBatteryStatus(float temperature, float soc, float chargeRate) {
    printStatusMessage("Temperature", temperature, TEMP_LIMITS);
    printStatusMessage("State of Charge", soc, SOC_LIMITS);
    printStatusMessage("Charge Rate", chargeRate, CHARGE_RATE_LIMITS);
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
