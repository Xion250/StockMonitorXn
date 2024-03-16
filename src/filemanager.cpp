
#include "filemanager.hpp"

bool FileManager::readProfile(std::string *var) {
    return readFromFile(FILE_NAME_PROFILE, var);
}

bool FileManager::readPolygonApiKey(std::string *var) {
    return readFromFile(FILE_NAME_API_KEY, var);
}

bool FileManager::readFromFile(std::string fileName, std::string *var) {
    std::ifstream file(std::string(SAVE_DATA_PATH) + fileName);
    if(!file.is_open()){return false;}
    if(file.peek() == file.eof()){return false;}
    file >> *var;
    file.close();
    return true;
}

void FileManager::createPolygonApiKey(const std::string &var) {
    std::ofstream file(std::string(SAVE_DATA_PATH) + FILE_NAME_API_KEY);
    if(!file.is_open()){printf("Error: reatePolygonApiKey could not open file\n"); return;}
    file.write(var.c_str(), var.size());
    file.close();
}