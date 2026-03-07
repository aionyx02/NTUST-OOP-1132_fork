#ifndef _CASE_H_
#define _CASE_H_
#define SECRET "EXAMPLE"
#include "test.h"

TEST_CASE(Case1) {
  int a = 10, b = 20;
  double pi = 3.14, two = 2.0;
  bool truth = true;
  std::string hello = "hello", world = "world";

  CHECK_EQ(a, 10);
  CHECK_EQ(b, 20);
  CHECK_EQ(a + b, 30);
  CHECK_EQ(pi * 2, 6.28);
  CHECK_EQ(truth, true);
  CHECK_EQ(!truth, false);
  CHECK_EQ(hello, "hello");
  CHECK_EQ(hello.size(), 5);
  CHECK_EQ(world[0], 'w');
  CHECK_EQ(hello + world, "helloworld");
  CHECK_EQ((int)(pi * 3), 9); // 3.14 * 3 ≈ 9.42 ⇒ int = 9
  CHECK_EQ(a % 3, 1);
  CHECK_EQ((a > 0), true);
  CHECK_EQ((b >= a), true);
  CHECK_EQ((a == 10 && b == 20), true);
  CHECK_EQ((a < b), true);
  CHECK_EQ(std::string("test").size(), 4);
  CHECK_EQ(std::string("abc").find('b'), 1);
  CHECK_EQ(0.1 + 0.2, GamelabTest::Approxy(0.3)); // 避開精度陷阱
  CHECK_EQ(0.1 + 0.2, GamelabTest::Approxy(0.3000001)); // 避開精度陷阱
  CHECK_EQ(0.1 + 0.2, GamelabTest::Approxy(0.2999999)); // 避開精度陷阱
  CHECK_EQ(std::to_string(a), "10");
}

#endif