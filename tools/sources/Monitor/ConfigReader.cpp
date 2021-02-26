#include "ConfigReader.h"

bool fileExists(const std::string& file_path) {
  struct stat buffer;
  return (stat (file_path.c_str(), &buffer) == 0);
}


ConfigReader::ConfigReader(std::string file_path) {

    this->file_path = file_path;
    good = false;

    file.open( file_path, std::ios::in);
    if(file.good() == true) {
        good = true;
        readConfig();
    }
    file.close();
}

ConfigReader::~ConfigReader() {
    file.close();
}


int ConfigReader::readConfig() {
    std::string temp, section="";
    int pos;



    while(std::getline(file, temp)) {
        temp = removeSpaces(temp);
        if(updateSection(temp, section)) continue;
        pos  = findOperator(temp);
        if(pos != -1) {
            temp = removeChar(temp, '\"');
            mapRecord(section, temp.substr(0, pos), temp.substr(pos+1, temp.length()-pos));
        }
    }
    return 0;
}

int ConfigReader::createConfig(std::map<std::string, std::string> config) {
    std::map<std::string, std::map<std::string, std::string>> temporary_config;
    temporary_config[""] = config;
    return createConfig(temporary_config);
}

int ConfigReader::createConfig(std::map<std::string, std::map<std::string, std::string>> config) {
    int result=0;
    file.open( file_path, std::ios::out | std::ios::trunc);
    if(file.good()) {

        std::string config_line="";

        for(auto const &element1 : config) {
            if(element1.first != "") {
                config_line = "[" + element1.first + "]\n";
                file.write(&config_line[0], config_line.length());
            }
            for(auto const &element2 : element1.second) {
                std::string config_line = element2.first + "=\"" + element2.second + "\"\n";
                file.write(&config_line[0], config_line.length());
            }
        }
        if(file.fail()) {
            result = -1;
        }
    } else result = -1;

    file.close();

    file.open(file_path, std::ios::in);
    configuration.clear();
    readConfig();
    file.close();

    return result;
}

int ConfigReader::editRecord(std::string key, std::string new_value) {
    return editRecord("", key, new_value);
}

int ConfigReader::editRecord(std::string key_section, std::string key, std::string new_value) {

    bool keyfound = false;
    int result = 0;
    std::vector<std::string> temp_data, temp_line;
    std::string line, section="";


    file.open(file_path, std::ios::out | std::ios::app);
    file.close();

    file.open( file_path, std::ios::in);
    if(!file.good()) { file.close(); return -1; }
    while(std::getline(file, line)) {

        if(updateSection(removeSpaces(line), section)) {
            temp_data.push_back("["+section+"]\n");
            continue;
        }

        temp_line = parseData(line);

        if(temp_line.size() >= 1) {
            if(section == key_section && temp_line[0] == key) {
                temp_data.push_back(key+"=\""+new_value+"\"\n");
                keyfound = true;
            } else
                temp_data.push_back(line+"\n");
        } else
            temp_data.push_back(line+"\n");
    }

    file.close();
    file.clear();
    file.open( file_path+".tmp", std::ios::out | std::ios::trunc);
    if(!file.good()) { file.close(); return -1; }
    for(unsigned int x=0; x<temp_data.size(); x++) {
        file.write(&temp_data[x][0], temp_data[x].length());
        if(file.fail()) { result = -1; }
    }

    file.close();

    std::string temp_name = file_path + ".tmp";

    remove(&file_path[0]);
    rename(&temp_name[0], &file_path[0]);


    if(!keyfound)
        return addRecord(key_section, key, new_value);

    return result;
}

int ConfigReader::addRecord(std::string key, std::string value) {
    return addRecord("", key, value);
}

int ConfigReader::addRecord(std::string key_section, std::string key, std::string value) {
    int result=0;
    std::string line, section="";
    std::vector<std::string> temp_data;

    if( configuration.find(key_section) != configuration.end() ) {
        if( configuration[ key_section ].find(key) != configuration[ key_section ].end()) {
            return -1;
        }
    }

    if(configuration.find(key_section) == configuration.end() && key_section != "") {
        file.open( file_path, std::ios::out | std::ios::in);
        if(file.good()) {
            file.clear();
            file.seekg(-1, std::ios::end);
            char character;
            file.get(character);
            std::string temp = "";
            if(character != '\n') temp+="\n";
            temp += "[" + key_section + "]\n" + key + "=\"" + value + "\"\n";
            file.write(&temp[0], temp.length());
            if(file.fail()) result = -1;
        } else result = -1;

        file.close();
    } else {

    file.open(file_path, std::ios::out | std::ios::app);
    file.close();

    file.open( file_path, std::ios::in);
    if(!file.good()) { file.close(); return -1; }

    bool added = false;

    while(std::getline(file, line)) {

        if(key_section == "" && section == "" && !added) {
            temp_data.push_back(key+"=\""+value+"\"\n");
            added = true;
        }

        if(updateSection(removeSpaces(line), section)) {
            temp_data.push_back("["+section+"]\n");
            if(section == key_section)
                temp_data.push_back(key+"=\""+value+"\"\n");
            continue;
        }

        temp_data.push_back(line+"\n");
    }

    if(!added) {    // exception for adding record to empty file
        temp_data.push_back(key+"=\""+value+"\"\n");
        added = true;
    }

    file.close();
    file.clear();
    file.open( file_path+".tmp", std::ios::out | std::ios::trunc);
    if(!file.good()) { file.close(); return -1; }
    for(unsigned int x=0; x<temp_data.size(); x++) {
        file.write(&temp_data[x][0], temp_data[x].length());
        if(file.fail()) { result = -1; }
    }

    file.close();


    std::string temp_name = file_path + ".tmp";

    remove(&file_path[0]);
    rename(&temp_name[0], &file_path[0]);

    }

    return result;
}

int ConfigReader::deleteRecord(std::string key) {
    return deleteRecord("", key);
}

int ConfigReader::deleteRecord(std::string key_section, std::string key) {

    int result = 0;
    std::vector<std::string> temp_data, temp_line;
    std::string line, section="";

    file.open( file_path, std::ios::in);
    if(!file.good()) { file.close(); return -1; }


    while(std::getline(file, line)) {

        if(updateSection(removeSpaces(line), section)) {
            temp_data.push_back("["+section+"]");
            continue;
        }

        temp_line = parseData(line);

        if(temp_line.size() >= 1) {
            if(section == key_section && temp_line[0] == key) {
                continue;
            } else
                temp_data.push_back(line+"\n");
        } else
            temp_data.push_back(line+"\n");
    }

    file.close();
    file.clear();
    file.open( file_path+".tmp", std::ios::out | std::ios::trunc);
    for(unsigned int x=0; x<temp_data.size(); x++) {
        file.write(&temp_data[x][0], temp_data[x].length());
        if(file.fail()) { result = -1; }
    }

    file.close();
    std::string temp_name = file_path + ".tmp";

    remove(&file_path[0]);
    rename(&temp_name[0], &file_path[0]);
    return result;
}

std::string ConfigReader::getRecord(std::string section, std::string key) {
    if(configuration[ section ].find(key) == configuration[ section ].end()){
        return "";
    }

    return configuration[ section ][ key ];
}

std::string ConfigReader::getRecord(std::string key) {
    if(configuration[ "" ].find(key) == configuration[ "" ].end()){
        return "";
    }

    return configuration[ "" ][ key ];
}

std::vector<std::string> ConfigReader::parseData(std::string data) {
    int pos;
    std::vector<std::string> keyPair;

    data = removeSpaces(data);
    pos  = findOperator(data);
    if(pos != -1) {
        data = removeChar(data, '\"');
        keyPair.push_back(data.substr(0, pos));
        keyPair.push_back(data.substr(pos+1, data.length()-pos));
    }
    return keyPair;
}

std::string ConfigReader::removeSpaces(std::string data) {

    bool quote = false;
    int y=0;

    for(unsigned int x=0; x<data.length(); x++) {
        if(data[x] == '#') { // start of the commment
            data.resize(y);
            break;
        }

        if(data[x] != ' ' || quote) {
            data[y] = data[x];
            y++;
        }
        if(data[x] == '\"') quote = !quote;
    }

    data.resize(y);

    return data;
}

std::string ConfigReader::removeChar(std::string data, char character) {

    int y=0;

    for(unsigned int x=0; x<data.length(); x++) {
        if(data[x] != character) {
            data[y] = data[x];
            y++;
        }
    }

    data.resize(y);

    return data;
}

int ConfigReader::findOperator(std::string data) {

    int pos = data.find("=", 1);
    while(data[pos-1] == '\\' && pos != -1) {
        pos = data.find("=", pos+1);
    }
    return pos;
}

bool ConfigReader::updateSection(std::string data, std::string &section) {
    if(data[0] == '[' && data[data.length() - 1] == ']') {
        section = data.substr(1, data.length()-2);
        return 1;
    }
    return 0;
}

void ConfigReader::mapRecord(std::string section, std::string key, std::string value) {
    configuration[ section ][ key ] = value;
}
