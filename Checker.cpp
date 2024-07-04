#include <assert.h>
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
 if (isTemperatureOutOfRange(temperature)) {
     cout << "Temperature out of range!\n";
     return false;
 }
 if (isSocOutOfRange(soc)) {
     cout << "State of Charge out of range!\n";
     return false;
 }
 if (isChargeRateOutOfRange(chargeRate)) {
     cout << "Charge Rate out of range!\n";
     return false;
 }
 return true;
}

int main() {
 assert(batteryIsOk(25, 70, 0.7) == true);
 assert(batteryIsOk(50, 85, 0) == false);
}
