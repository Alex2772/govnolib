#pragma once

#include <string>
#include <concepts>


namespace govno {
std::string version();
std::string test(std::string input);

template<std::integral T>
void test2(T&& t) {

}
}
