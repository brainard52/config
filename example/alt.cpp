#include "../src/newconfig.hpp"
#include <iostream>

int main() {
    config Config;
    std::cout << Config.query("gimmick", "resolution") << std::endl;
    std::cout << Config.get_x("gimmick", "resolution") << std::endl;
    std::cout << Config.get_y("gimmick", "resolution") << std::endl;
    return 0;
}
