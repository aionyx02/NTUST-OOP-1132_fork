#ifndef _CASE_H_
#define _CASE_H_
#define SECRET "fb8d11b4-97d5-483a-9a0d-c2f55c8e37e2"
#include "operator.h"
#include "test.h"
#include "variable.h"
#include <numeric>

TEST_CASE("Case2: Operations") {
  var a = 10.;
  var b = 5;
  var x = a + b;
  var y = x - b;
  var z = y * "2"s;

  CHECK_EQ(x.as<float>(), APPROXY(15.0));
  CHECK_EQ(y.as<float>(), APPROXY(10.0));

  CHECK_EQ(x.as<double>(), APPROXY(15.0));
  CHECK_EQ(y.as<double>(), APPROXY(10.0));

  CHECK_EQ(z, 20);

  try {
    var f = true + var(true);
  } catch (std::invalid_argument e) {
    CHECK_EQ(e.what(), "incompatible types"s);
  }

  try {
    var z = a / 0;
  } catch (std::domain_error e) {
    CHECK_EQ(e.what(), "not allow devide by 0"s);
  }

  try {
    var str = "abc"s;
    str = str * 3;
  } catch (std::invalid_argument e) {
    CHECK_EQ(e.what(), "convert failed"s);
  }
}

#endif