#include "../src/config.hpp"
#include <iostream>

int main() {
    std::cout << config::query("gimmick", "resolution") << std::endl;
    std::cout << config::get_x("gimmick", "resolution") << std::endl;
    std::cout << config::get_y("gimmick", "resolution") << std::endl;
    return 0;
}
