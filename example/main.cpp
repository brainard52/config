#include <iostream>

#include "../src/config.hpp"

int main(){
    config::set("test", "testkey", "testvalue");

    std::cout << config::query("test", "testkey") << std::endl;
    config::write();
    return 0;
}
