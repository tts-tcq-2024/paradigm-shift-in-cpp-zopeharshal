#include <iostream>
#include <cassert>

using namespace std;

class BatteryChecker {
private:
    float temperature;
    float soc;
    float chargeRate;

public:
    BatteryChecker(float temp, float soc, float chargeRate)
        : temperature(temp), soc(soc), chargeRate(chargeRate) {}

    bool isTemperatureOk() const {
        return (temperature >= 0 && temperature <= 45);
    }

    bool isSOCOk() const {
        return (soc >= 20 && soc <= 80);
    }

    bool isChargeRateOk() const {
        return (chargeRate <= 0.8);
    }

    bool isBatteryOk() const {
        return isTemperatureOk() && isSOCOk() && isChargeRateOk();
    }

    void printWarnings() const {
        if (!isTemperatureOk()) {
            cout << "Temperature out of range!\n";
        }
        if (!isSOCOk()) {
            cout << "State of Charge out of range!\n";
        }
        if (!isChargeRateOk()) {
            cout << "Charge Rate out of range!\n";
        }
    }
};

int main() {
    BatteryChecker battery1(25, 70, 0.7);
    assert(battery1.isBatteryOk() == true);
    battery1.printWarnings();

    BatteryChecker battery2(50, 85, 0);
    assert(battery2.isBatteryOk() == false);
    battery2.printWarnings();
}
