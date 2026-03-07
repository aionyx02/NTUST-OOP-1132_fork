#ifndef _TEST_H_
#define _TEST_H_

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#define DELIMITER "\t"

namespace GamelabTest {

inline std::string escape_string(const std::string& input) {
  std::ostringstream oss;
  for (char ch : input) {
    // clang-format off
    switch (ch) {
    case '\t': oss << "\\t"; break;
    case '\n': oss << "\\n"; break;
    case '\r': oss << "\\r"; break;
    case '\b': oss << "\\b"; break;
    case '\f': oss << "\\f"; break;
    case '\v': oss << "\\v"; break;
    case '\a': oss << "\\a"; break;
    case '\\': oss << "\\\\"; break;
    case '\"': oss << "\\\""; break;
    case '\'': oss << "\\\'"; break;
    default:
      if (std::isprint(static_cast<unsigned char>(ch)))
        oss << ch;
      else
        oss << "\\x" << std::hex << std::uppercase << static_cast<int>(static_cast<unsigned char>(ch));
    }
  }
  return oss.str();
}

struct Approxy {
  double expected;
  double epsilon;

  explicit Approxy(double val, double eps = 1e-6)
      : expected(val), epsilon(eps) {}

  inline friend bool operator==(double actual, const Approxy& approx) {
    return std::fabs(actual - approx.expected) <= approx.epsilon;
  }

  inline friend bool operator==(const Approxy& approx, double actual) {
    return actual == approx;
  }

  inline friend bool operator!=(double actual, const Approxy& approx) {
    return !(actual == approx);
  }

  inline friend bool operator!=(const Approxy& approx, double actual) {
    return !(approx == actual);
  }

  inline friend std::ostream& operator<<(std::ostream& os, const Approxy& a) {
    return os << "~=" << a.expected;
  }
};

std::stringstream serr;

int failedChecks = 0;

inline void failureLog(const char* expr, std::string a, std::string b, int line) {
  serr << "[FAIL] " << expr << ", got: `" << escape_string(a) << "`, expected: `" << escape_string(b) << "`" << DELIMITER;
  failedChecks++;
}

template <typename T, typename U>
inline void failureLog(const char* expr, const T& a, const U& b, int line) {
  serr << "[FAIL] " << expr << ", got: `" << a << "`, expected: `" << b << "`" << DELIMITER;
  failedChecks++;
}

inline void print() {
  std::cout << serr.str() << "\n"
            << "Test Failed: " << failedChecks << " cases.";
}

} // namespace GamelabTest

template <typename A, typename B>
void check_eq(const A& a, const B& b, const char* exprA, const char* exprB, int line) {
    if (!(a == b)) {
      GamelabTest::serr << "[FAIL] " << expr << ", got: `" << escape_string(a) << "`, expected: `" << escape_string(b) << "`" << DELIMITER;
      GamelabTest::failedChecks++;
    }
}

#define CHECK_EQ(a, b) check_eq((a), (b), #a, #b, __LINE__)

#define APPROXY(floating) GamelabTest::Approxy(floating)

#define TEST_CASE(name) inline void entrypoint()

#endif // _TEST_H_