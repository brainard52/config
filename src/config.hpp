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
    typedef std::string Section;
    typedef std::string Key;

    int load();
    int load(std::string); // TODO: Validate path and pathed file.

    void set(Section section, Key key, std::string value);
    int write();
    std::string query(Section section, Key key);

    // Toolbox of useful queries.
    std::string before_delim(std::string to_search, std::string delim_str);
    std::string after_delim(std::string to_search, std::string delim_str);
    bool is_valid_resolution(std::string resolution);

    int get_x(Section section, std::string key);
    int get_y(Section section, std::string key);
}
