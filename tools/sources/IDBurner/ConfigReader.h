#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <stdio.h>
#include <sys/stat.h>

bool fileExists(const std::string& file_path);
bool fileCreate(std::string file_path);

class ConfigReader {

public:
    ConfigReader(std::string file_path);
    ~ConfigReader();

    std::map<std::string, std::map<std::string, std::string> > dumpConfiguration();


    int createConfig(std::map<std::string, std::string> config);
    int createConfig(std::map<std::string, std::map<std::string, std::string> > config);
    int updateConfig();
    std::string getRecord(std::string section, std::string key);
    std::string getRecord(std::string key);
    int editRecord(std::string key, std::string new_value);
    int editRecord(std::string key_section, std::string key, std::string new_value);
    int addRecord(std::string key, std::string value);
    int addRecord(std::string key_section, std::string key, std::string value);
    int deleteRecord(std::string key);
    int deleteRecord(std::string key_section, std::string key);

    bool existsValue(std::string key, std::string value);
    std::string getSectionByValue(std::string key, std::string value); // use this method only if you are sure that Value is unique for each section
    // e.g. id  (it always returns first section with specified value)
    int renameSection(std::string old_name, std::string new_name);
    int deleteSection(std::string del_section);
    bool existSection(std::string section);


private:
    std::fstream file;
    std::string file_path;
    std::map<std::string, std::map<std::string, std::string> > configuration;
    bool good;

    std::vector<std::string> parseData(std::string data);
    std::string removeSpaces(std::string data);
    std::string removeChar(std::string data, char character);
    int readConfig();
    int findOperator(std::string data);
    bool updateSection(std::string data, std::string &section);
    void mapRecord(std::string section, std::string key, std::string value);
};




#endif // CONFIGREADER_H
