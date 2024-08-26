#include <assert.h>
#include <iostream>
#include "BatteryStatusChecker.hpp"

using namespace std;

void testAllConditions(){

  // Case 1: All values within the range and Battery is Ok
  assert(isBatteryOk(25, 70, 0.7) == true);

  // Case 2: Temperature Out of Range when temperature value is low
  assert(isBatteryOk(-1, 50, 0.5) == false);

  // Case 3: Temperature Out of Range when temperature value is high
  assert(isBatteryOk(46, 50, 0.5) == false);

  // Case 4: SOC Out of Range when soc value is low
  assert(isBatteryOk(25, 19, 0.5) == false);

  // Case 5: SOC Out of Range when soc value is high
  assert(isBatteryOk(25, 81, 0.5) == false);

  // Case 6: Charge Rate Out of Range
  assert(isBatteryOk(25, 50, 0.9) == false);

  // Case 7: Multiple parameter Out of Range
  assert(isBatteryOk(-1, 81, 0.9) == false);

  // Case 8: Minimum Boundary value for Temperature
  assert(isBatteryOk(0, 50, 0.5) == true);

  // Case 9: Maximum Boundary value for Temperature
  assert(isBatteryOk(45, 50, 0.5) == true);

  // Case 10: Minimum Boundary for SOC
  assert(isBatteryOk(25, 20, 0.5) == true);

  // Case 11: Maximum Boundary value for SOC
  assert(isBatteryOk(25, 80, 0.5) == true);

  // Case 12: Maximum Boundary value for Charge Rate
  assert(isBatteryOk(25, 50, 0.8) == true);
}

void testForEnglish(){
  currentLanguage = ENGLISH;
  testAllConditions();
  cout << "All tests passed!" << endl;
}

void testForGerman(){
  currentLanguage = GERMAN;
  testAllConditions();
  cout << "Alle tests bestanden!" << endl;
}

int main() {
  testForEnglish();
  testForGerman();
}
