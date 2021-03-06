#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>

typedef std::string Section;
typedef std::string Key;

class config{
    private:
        std::fstream config_file;

        // This is the default config file. Replace stuff as necessary 
        std::map< std::string, std::map< std::string, std::string > > settings = 
        {
            {"config",  {
                            {"name", "gimmick"},
                            {"path", "settings.conf"}
                        }
            },
            {"gimmick", {
                            {"windowmode", "windowed"},
                            {"resolution", "800x600"},
                            {"vsync", "true"},
                            {"frameratecap", "60"},
                            {"musiclevel", "100"},
                            {"voicelevel", "100"},
                            {"cinematicslevel", "100"},
                            {"audiomute", "false"},
                            {"texturelevel", "high"}
                        }
            }
        };

    public:
        config(){
            load(query("config", "path"));
        }
        config(std::string path){
            load(path);
        }

        int load(){
            return load(query("config", "path"));
        }

        int load(std::string path){
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

        std::string query(Section section, Key key){
            return settings[section][key];
        }

        void set(Section section, Key key, std::string value){
            settings[section][key] = value;
        }

        int write(){
            config_file.open(query("config", "path"), std::fstream::out | std::fstream::trunc);
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
        // Toolbox of useful queries.
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

        int get_x(Section section, std::string key){
            if(is_valid_resolution(query(section, key))){
                std::string x = before_delim(query(section, key), "x");
                std::string::size_type sz;
                return std::stoi(x, &sz);

            }
            return -1;
        }
        int get_y(Section section, std::string key){
            if(is_valid_resolution(query(section, key))){
                std::string y = after_delim(query(section, key), "x");
                std::string::size_type sz;
                return std::stoi(y, &sz);
            }
            return -1;
        }
};
