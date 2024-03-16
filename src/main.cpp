
#include "menu.hpp"
#include <filesystem>

int main(int argc, char *argv[]){

    if(argc != 1){
        printf("Unexpected Number Of Arguments (%i)\n", argc);
        return 0;
    }

    std::string exePath = argv[0];

    if(exePath != "bin/main"){
        std::string path = exePath.substr(0, exePath.size() - std::string("bin/main").size());
        std::filesystem::current_path(path);
    }

    system("clear");
    UI::printAppHeader();

    Network network = Network();

    UI::Menu menu = UI::Menu(network);

    if(!network.updateApiKey()){UI::printApiKeyError();}

    while(menu.menuInput()){}

    return 0;
}