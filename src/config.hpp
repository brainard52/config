#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>

namespace{
    std::fstream config_file;

    std::map< std::string, std::map< std::string, std::string > > settings = {
        {"config", {
            {"name", "gimmick"},
            {"path", "settings.conf"}}},
        {"gimmick", {
            {"windowmode", "windowed"},
            {"resolution", "800x600"},
            {"vsync", "true"},
            {"frameratecap", "60"},
            {"musiclevel", "100"},
            {"voicelevel", "100"},
            {"cinematicslevel", "100"},
            {"audiomute", "false"},
            {"texturelevel", "high"}}}};
}

namespace config{
    int load();
    int load(std::string path);
    void set(std::string section, std::string key, std::string value);
    int write();
    std::string query(std::string section, std::string key);

    // Toolbox of useful queries.
    std::string before_delim(std::string to_search, std::string delim_str);
    std::string after_delim(std::string to_search, std::string delim_str);
    bool is_valid_resolution(std::string resolution);

    int get_x(std::string section, std::string key);
    int get_y(std::string section, std::string key);
}
