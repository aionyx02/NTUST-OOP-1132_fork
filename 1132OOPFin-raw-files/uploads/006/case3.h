#ifndef _CASE_H_
#define _CASE_H_
#define SECRET "9653cc82-c60c-481c-8bdb-d7d4ce91adda"
#include "operator.h"
#include "test.h"
#include "variable.h"
#include <numeric>

TEST_CASE("Case3: Mixed coercion and operations") {
  var L1 = 30;
  var L2 = 10.0 / "30"s;
  var L3 = true;
  var L4 = "10"s + "20"s;

  CHECK_EQ(L1, 30);
  CHECK_EQ(L2, 10. / 30.);
  CHECK_EQ(L3, 1);
  CHECK_EQ(L4.as<std::string>(), "1020");

  try {
    var("abc"s) + 10;
  } catch (std::invalid_argument e) {
    auto invalid_argument = true;
    CHECK_EQ(invalid_argument, true);
  } catch (std::exception e) {
    auto exception = true;
    CHECK_EQ(exception, false);
  }

  try {
    var(1 - "hello"s) + 10;
  } catch (std::invalid_argument e) {
    auto invalid_argument = true;
    CHECK_EQ(invalid_argument, true);
  } catch (std::exception e) {
    auto exception = true;
    CHECK_EQ(exception, false);
  }
}

#endif