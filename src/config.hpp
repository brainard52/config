#pragma once

#include <fstream>
#include <string>
#include <map>

const std::string CONFIG_PATH = "settings.conf";

class config{
    std::fstream config_file;

    std::map< std::string, std::map< std::string, std::string > > settings;

    public:
        config();
        ~config();

        // int reload();
        // Will reloas() actually improve the program?
        int load();
        int load(std::string path);
        void set(std::string section, std::string key, std::string value); //Are there any cases in which this would fail and I'd actually need a return value?
        int write();
//        std::string query();
//        std::string query(std::string section);
//        These two are mostly useless. The first moreso than the second.
//        I guess the second could be used in some cases. Still nearly useless.
        std::string query(std::string section, std::string key);
};
