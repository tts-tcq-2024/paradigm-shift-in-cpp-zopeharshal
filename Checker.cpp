#include <iostream>
#include <cassert>
using namespace std;

// Pure functions for checking conditions
bool isTemperatureOutOfRange(float temperature) {
  return (temperature < 0 || temperature > 45);
}

bool isSOCOutOfRange(float soc) {
  return (soc < 20 || soc > 80);
}

bool isChargeRateOutOfRange(float chargeRate) {
  return (chargeRate > 0.8);
}

// IO function to print error messages
void printOutOfRangeMessage(const string& parameterName) {
  cout << parameterName << " out of range!\n";
}

// Function to check battery status using pure functions
bool batteryIsOk(float temperature, float soc, float chargeRate) {
  if (isTemperatureOutOfRange(temperature)) {
    printOutOfRangeMessage("Temperature");
    return false;
  }
  if (isSOCOutOfRange(soc)) {
    printOutOfRangeMessage("State of Charge");
    return false;
  }
  if (isChargeRateOutOfRange(chargeRate)) {
    printOutOfRangeMessage("Charge Rate");
    return false;
  }
  return true;
}

// Main function to demonstrate functionality with assertions
int main() {
  assert(batteryIsOk(25, 70, 0.7) == true);
  assert(batteryIsOk(50, 85, 0) == false);
}
