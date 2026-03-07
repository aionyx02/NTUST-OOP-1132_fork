#ifndef _CASE_H_
#define _CASE_H_
#define SECRET "95cbed6b-fd08-48ad-a729-0f9309ce7a35"
#include "operator.h"
#include "test.h"
#include "variable.h"
#include <numeric>
#include <string>
#include <vector>

TEST_CASE("Case: Full test") {
  // + operator
  CHECK_EQ(var(1) + var(2), var(3));
  CHECK_EQ(var(1.5) + var(2), var(3.5));
  CHECK_EQ(var("123"s) + var("456"s), var("123456"s));
  CHECK_EQ(var("abc"s) + var("def"s), var("abcdef"s));

  try {
    var("123"s) + var(456);
    var("abc"s) + var(123);
    var(123) + var("456"s);
    var(123) + var("abc"s);
  } catch (std::invalid_argument e) {
    CHECK_EQ(e.what(), "convert failed"s);
  }

  try {
    var(true) + var(false);
  } catch (std::invalid_argument e) {
    CHECK_EQ(e.what(), "incompatible types"s);
  }

  try {
    var(true) + var("1"s);
  } catch (std::invalid_argument e) {
    CHECK_EQ(e.what(), "incompatible types"s);
  }

  // - operator
  CHECK_EQ(var(5) - var(3), var(2));
  CHECK_EQ(var(10.5) - var(0.5), var(10.0));
  CHECK_EQ(var("100"s) - var("50"s), var(50.0));

  try {
    var(true) - var(false);
  } catch (std::invalid_argument e) {
    CHECK_EQ(e.what(), "incompatible types"s);
  }

  try {
    var("abc"s) - var("123"s);
  } catch (std::invalid_argument e) {
    CHECK_EQ(e.what(), "convert failed"s);
  }

  try {
    var("xyz"s) - var(1);
  } catch (std::invalid_argument e) {
    CHECK_EQ(e.what(), "convert failed"s);
  }

  try {
    var(300) - var("oops"s);
  } catch (std::invalid_argument e) {
    CHECK_EQ(e.what(), "convert failed"s);
  }

  // * operator
  CHECK_EQ(var(6) * var(7), var(42));
  CHECK_EQ(var(2.5) * var(4), var(10.0));
  CHECK_EQ(var("10"s) * var("2"s), var(20.0));

  try {
    var(true) * var(10);
  } catch (std::invalid_argument e) {
    CHECK_EQ(e.what(), "incompatible types"s);
  }

  try {
    var("abc"s) * var("3"s);
  } catch (std::invalid_argument e) {
    CHECK_EQ(e.what(), "convert failed"s);
  }

  try {
    var("oops"s) * var(5);
  } catch (std::invalid_argument e) {
    CHECK_EQ(e.what(), "convert failed"s);
  }
  CHECK_EQ(var(3) * var("2"s), var(6.0));

  try {
    var(3) * var("nope"s);
  } catch (std::invalid_argument e) {
    CHECK_EQ(e.what(), "convert failed"s);
  }

  // / operator
  CHECK_EQ(var(10) / var(2), var(5.0));
  CHECK_EQ(var(9.0) / var(3), var(3.0));
  CHECK_EQ(var("100"s) / var("4"s), var(25.0));
  CHECK_EQ(var("50"s) / var(2), var(25.0));
  CHECK_EQ(var(100) / var("4"s), var(25.0));

  try {
    var(true) / var(true);
  } catch (std::invalid_argument e) {
    CHECK_EQ(e.what(), "incompatible types"s);
  }

  try {
    var("abc"s) / var("2"s);
  } catch (std::invalid_argument e) {
    CHECK_EQ(e.what(), "convert failed"s);
  }
  
  try {
    var("xyz"s) / var(2);
  } catch (std::invalid_argument e) {
    CHECK_EQ(e.what(), "convert failed"s);
  }

  try {
    var(100) / var("0"s);
  } catch (std::domain_error e) {
    CHECK_EQ(e.what(), "not allow devide by 0"s);
  }
}

#endif