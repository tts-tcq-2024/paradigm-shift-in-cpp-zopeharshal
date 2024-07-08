#include <iostream>
#include <cassert>
using namespace std;

bool isOutOfRange(float value, float lowerBound, float upperBound) {
  return (value < lowerBound || value > upperBound);
}


void printOutOfRangeMessage(const string& parameterName) {
  cout << parameterName << " out of range!\n";
}

bool batteryIsOk(float temperature, float soc, float chargeRate) {
  if (isOutOfRange(temperature, 0, 45)) {
    printOutOfRangeMessage("Temperature");
    return false;
  }
  if (isOutOfRange(soc, 20, 80)) {
    printOutOfRangeMessage("State of Charge");
    return false;
  }
  if (isOutOfRange(chargeRate, 0, 0.8)) {
    printOutOfRangeMessage("Charge Rate");
    return false;
  }
  return true;
}

int main() {
  assert(batteryIsOk(25, 70, 0.7) == true);
  assert(batteryIsOk(50, 85, 0) == false);
}
