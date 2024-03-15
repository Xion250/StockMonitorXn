
#include "userinterface.hpp"

/*template<typename T>
std::string UI::formatValue(T value, UI::PadSize padSize){
    std::string str = std::to_string(value);
    if(padSize > str.size()){
        str += std::string(padSize - str.size(),' ');
    }
    return str;
}*/

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



/*template<typename T>
bool UI::getUserInput(std::string prompt, T &var){
    if(std::cin.peek() == '\n' || std::cin.peek() == '\0'){
        printf("%s\n", prompt.c_str());
    }
    if(getExit()){return false;}
    std::cin >> var;
    return true;
}*/

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