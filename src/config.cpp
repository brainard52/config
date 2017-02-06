#include <fstream>
#include <string>

#include "config.hpp"

config::config(){
    load();
}

config::~config(){
}

int config::load(){
    return load(CONFIG_PATH);
}

int config::load(std::string path){
    config_file.open(path, std::fstream::in);
    if(config_file.fail())
        return 1;

    std::string line, section, key, value;
    while(std::getline(config_file, line) && !config_file.eof()){
        if(line.at(0) == '['){
            unsigned first = line.find('['), last = line.find(']');
            section = line.substr(first+1, last-first-1);
        } else if(line.find('=') != std::string::npos && !section.empty()){
            unsigned delim = line.find('=');
            key = line.substr(0, delim);
            value = line.substr(delim+1, line.length());
            set(section, key, value);
        }
    }
    config_file.close();
    return 0;
}

void config::set(std::string section, std::string key, std::string value){
    settings[section][key] = value;
}

int config::write(){
    config_file.open(CONFIG_PATH, std::fstream::out | std::fstream::trunc);
    if(config_file.fail())
        return 1;
    for(auto const& section : settings){
        config_file << '[' << section.first << ']' << std::endl;
        for(auto const& key : section.second){
            config_file << key.first << "=" << key.second << std::endl;
        }
    }
    return 0;
}

std::string config::query(std::string section, std::string key) {
    return settings[section][key];
}
