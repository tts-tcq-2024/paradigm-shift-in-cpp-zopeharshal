#include <iostream>
using namespace std;

bool isTemperatureOutOfRange(float temperature) {
  return (temperature < 0 || temperature > 45);
}

bool isSocOutOfRange(float soc) {
  return (soc < 20 || soc > 80);
}

bool isChargeRateOutOfRange(float chargeRate) {
  return (chargeRate > 0.8);
}

bool batteryIsOk(float temperature, float soc, float chargeRate) {
  return !isTemperatureOutOfRange(temperature) &&
         !isSocOutOfRange(soc) &&
         !isChargeRateOutOfRange(chargeRate);
}

void printOutOfRangeMessage(const string& parameter) {
  cout << parameter << " out of range!\n";
}

void checkBatteryStatus(float temperature, float soc, float chargeRate) {
  if (isTemperatureOutOfRange(temperature)) {
    printOutOfRangeMessage("Temperature");
  }
  
  if (isSocOutOfRange(soc)) {
    printOutOfRangeMessage("State of Charge");
  }
  
  if (isChargeRateOutOfRange(chargeRate)) {
    printOutOfRangeMessage("Charge Rate");
  }
}

int main() {
  // Example usage:
  checkBatteryStatus(25, 70, 0.7);  // Should not print anything
  checkBatteryStatus(50, 85, 0);    // Should print messages for all parameters
}
