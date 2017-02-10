#pragma once

#include <fstream>
#include <string>
#include <map>

namespace {
const std::string CONFIG_PATH = "settings.conf"; // TODO: think about whether this is the best solution
    static std::fstream config_file;
    static std::map< std::string, std::map< std::string, std::string > > settings;
}


namespace config{
        int load();
        int load(std::string path);
        void set(std::string section, std::string key, std::string value);
        int write();
        std::string query(std::string section, std::string key);
};
