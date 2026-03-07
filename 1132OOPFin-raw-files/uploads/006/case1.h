#ifndef _CASE_H_
#define _CASE_H_
#define SECRET "550f176f-ece7-4c63-91bd-ac8194444e50"
#include "operator.h"
#include "test.h"
#include "variable.h"
#include <numeric>

TEST_CASE("Case1") {
  var a = 10;
  var b = 10.;
  var c = 10.f;
  var d = true;
  var str1 = "1234"s;
  var str2 = str1 + "5678"s;

  CHECK_EQ(str2, "12345678"s);
  CHECK_EQ(str1 + 100, 1334);
}

#endif