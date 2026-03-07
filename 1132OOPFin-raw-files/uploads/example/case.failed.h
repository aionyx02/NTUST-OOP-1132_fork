#ifndef _CASE_H_
#define _CASE_H_
#define SECRET "EXAMPLE"
#include "test.h"

TEST_CASE(Case1) {
  int a = 5, b = 10;
  double x = 3.14, y = 2.71;
  bool flag = true;
  std::string s1 = "apple", s2 = "orange";

  CHECK_EQ(a, b);                  // 5 != 10
  CHECK_EQ(x, y);                  // 3.14 != 2.71
  CHECK_EQ(a + b, 20);             // 15 != 20
  CHECK_EQ(a * 2, b);              // 10 == 10, pass
  CHECK_EQ(flag, false);           // true != false
  REQUIRE_EQ(!flag, true);           // false != true
  CHECK_EQ(s1, s2);                // "apple" != "orange"
  CHECK_EQ(s1.size(), 4);          // 5 != 4
  CHECK_EQ(s2[0], 'a');            // 'o' != 'a'
  CHECK_EQ(x + 1, 4.0);            // 4.14 != 4.0
  CHECK_EQ(x - y, 1.0);            // 0.43 != 1.0
  CHECK_EQ(a - b, 0);              // -5 != 0
  CHECK_EQ(a + 100, 90);           // 105 != 90
  CHECK_EQ((int)(x * 2), 6);       // 6 != 6, actually passes
  CHECK_EQ(a % 3, 0);              // 2 != 0
  CHECK_EQ(!!flag, false);         // true != false
  CHECK_EQ(0.1 + 0.2, GamelabTest::Approxy(0.3));        // 浮點陷阱（不精確）
  CHECK_EQ(s1 + s2, "appleapple"); // appleorange != appleapple
  CHECK_EQ(s1.empty(), true);      // false != true
  CHECK_EQ(s2.find('z'), 0);       // npos != 0
}

#endif