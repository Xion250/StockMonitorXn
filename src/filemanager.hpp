
#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#define SAVE_DATA_PATH "savedata/"
#define FILE_NAME_PROFILE "profile.txt"
#define FILE_NAME_API_KEY "polygonApiKey"
#include <fstream>
#include <string>

namespace FileManager {
    bool readProfile(std::string *var);
    bool readPolygonApiKey(std::string *var);
    bool readFromFile(std::string fileName, std::string *var);

    void createPolygonApiKey(const std::string &var);
}

#endif