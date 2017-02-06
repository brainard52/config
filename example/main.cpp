#include <iostream>

#include "../src/config.hpp"

int main(){
    config myconfig;

    myconfig.set("test", "testkey", "testvalue");

    std::cout << myconfig.query("test", "testkey") << std::endl;
    myconfig.write();
    return 0;
}
