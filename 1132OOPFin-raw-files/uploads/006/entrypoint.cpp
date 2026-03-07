#include "case.h"
#include "test.h"
#include <iostream>

int main() {
  try {
    entrypoint();
  } catch (std::exception e) {
    std::cout << e.what();
    std::cout << "[ABORTED] Exception thrown.\n";
    return EXIT_FAILURE;
  }

  if (GamelabTest::failedChecks > 0) {
    GamelabTest::print();
    return EXIT_FAILURE;
  }

  std::cout << "Test Pass:\n" << SECRET;
  return 0;
}
