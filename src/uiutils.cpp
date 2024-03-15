
#include "userinterface.hpp"

std::string UI::formatStrValue(std::string str, UI::PadSize padSize){
    if(padSize > str.size()){
        str += std::string(padSize - str.size(),' ');
    }
    return str;
}

std::string UI::formatDoubleValue(double value, UI::PadSize padSize){
    std::string str = std::to_string((int)value) + '.' + std::to_string((int)(100*value)%100);
    if(padSize > str.size()){
        str += std::string(padSize - str.size(),' ');
    }
    return str;
}

std::string UI::decimalToString(double value){
    return std::to_string((int)value) + '.' + std::to_string((int)(100*value)%100);
}

void UI::formatUserInput(std::string &str, InputFormat format){
    if(str.size() == 0){return;}
    switch(format){
        case UI::Clear : {
            break;
        }
        case UI::Capital : {
            for(int i = 0; i < str.size(); i++) {str[i] = toupper(str[i]);}
            break;
        }
        default : {
            str[0] = toupper(str[0]);
            for(int i = 1; i < str.size(); i++) {str[i] = tolower(str[i]);}
            break;
        }
    }
}

bool UI::getUserInput(std::string prompt, std::string &str, InputFormat format){
    if(!UI::promptUserInput(prompt)){return false;}
    std::cin >> str;
    formatUserInput(str, format);
    return true;
}

bool UI::getExit(){
    const char exitStr[] = "Exit";
    char str[4];
    // TODO : Implement Exit Code
    return false;
}

bool UI::promptUserInput(std::string &prompt){
    if(std::cin.peek() == '\n' || std::cin.peek() == '\0'){
        printf("%s\n", prompt.c_str());
    }
    return !getExit();
}

void UI::Element::setPadSize(PadSize padSize){
    paddedText = formatStrValue(text, padSize);
}

const char *UI::Element::tiny() {
    setPadSize(Tiny);
    return paddedText.c_str();
}

const char *UI::Element::small() {
    setPadSize(Small);
    return paddedText.c_str();
}

const char *UI::Element::med() {
    setPadSize(Medium);
    return paddedText.c_str();
}

const char *UI::Element::large() {
    setPadSize(Large);
    return paddedText.c_str();
}