//
// Created by alex2772 on 8/28/25.
//

#include "govno.h"
#include <algorithm>

std::string govno::version() {
  return "0.0.2";
}

std::string govno::test(std::string input) {
  if (input.find("test") == std::string::npos) {
    return input;
  }
  input.replace(input.find("test"), 4, "test2");
  input.erase(std::remove(input.begin(), input.end(), ' '), input.end());
  return input;
}
