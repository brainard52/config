#include <fstream>
#include <iostream>
#include <string>

#include "config.hpp"


int config::load(){
    return load(settings["config"]["path"]);
}

int config::load(std::string path){
    config_file.open(path, std::fstream::in);
    if(config_file.fail())
        return 1;

    std::string line, section, key, value;
    while(std::getline(config_file, line) && !config_file.eof()){
        if(line.at(0) == '['){
            auto first = line.find('[');
            auto last = line.find(']');
            section = line.substr(first+1, last-first-1);
        } else if(!section.empty() && line.find('=') != std::string::npos){
            //checking section.empty() discards key=value pairs if they don't have a section.
            auto delim = line.find('=');
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
    config_file.open(settings["config"]["path"], std::fstream::out | std::fstream::trunc);
    if(config_file.fail())
        return 1;
    for(auto const& section : settings){
        if(section.first != "config"){
            config_file << '[' << section.first << ']' << std::endl;
            for(auto const& key : section.second){
                config_file << key.first << "=" << key.second << std::endl;
            }
        }
    }
    return 0;
}

std::string config::query(std::string section, std::string key) {
    return settings[section][key];
}


std::string before_delim(std::string to_search, std::string delim_str){
if(to_search.find(delim_str) != std::string::npos){
    auto delim = to_search.find(delim_str);
    return to_search.substr(0, delim);
}
return "";
}

std::string after_delim(std::string to_search, std::string delim_str){
if(to_search.find(delim_str) != std::string::npos){
    auto delim = to_search.find(delim_str);
    return to_search.substr(delim+1, to_search.size()+1);
}
return "";
}

bool is_valid_resolution(std::string resolution){
std::string x = before_delim(resolution, "x");
std::string y = after_delim(resolution, "x");
return (!x.empty() 
        && !y.empty() 
        && x.find_first_not_of("0123456789") == std::string::npos 
        && y.find_first_not_of("0123456789") == std::string::npos);
}

int config::get_x(std::string section, std::string key){
    std::cout << key << " " << section << " resolution: " << query(key, section) << std::endl;
    if(is_valid_resolution(query(key, section))){
        std::string x = before_delim(query(key, section), "x");
        std::string::size_type sz;
        return std::stoi(x, &sz);

    }
    return -1;
}

int config::get_y(std::string section, std::string key){
    std::cout << key << " " << section << " resolution: " << query(key, section) << std::endl;
    if(is_valid_resolution(query(section, key))){
        std::string y = after_delim(query(key, section), "x");
        std::cout << y << std::endl;
        std::string::size_type sz;
        return std::stoi(y, &sz);
    }
    return -1;
}
