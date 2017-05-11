#include <iostream>

#include "../src/newconfig.hpp"

int main(){
    config Config;
    Config.set("test", "testkey", "testvalue");

    std::cout << Config.query("test", "testkey") << std::endl << Config.query("config", "path") << std::endl;
    Config.write();
    return 0;
}
