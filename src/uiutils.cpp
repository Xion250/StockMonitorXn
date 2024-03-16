
#include "userinterface.hpp"

std::string UI::formatPadStr(std::string str, UI::PadSize padSize, UI::PadType padType){

    if(padSize == str.size()){return str;}

    bool overflow = padSize < str.size();

    if(!overflow){
        return str + std::string(padSize - str.size(),' ');
    }

    if(padType == PadType::Strict){
        str = str.substr(0, padSize);
    }

    return str;
}

std::string UI::toDecimalStr(double value){
    int centsInt = (int)(100 * value);
    std::string cents = std::to_string(centsInt);
    switch(cents.size()){
        case 1 : {cents = "0.0" + cents;} break;
        case 2 : {cents = "0." + cents;} break;
        default : {cents.insert(cents.size()-2, ".");}
    }
    return cents;
}

std::string UI::toDecimalStr(char prefix, double value){
    bool sign = value < 0;
    return std::string(sign ? "-" : " ") + prefix + toDecimalStr(abs(value));
}

std::string UI::toDecimalStr(double value, char suffix){
    bool sign = value < 0;
    return std::string(sign ? "-" : " ") + toDecimalStr(abs(value)) + suffix;
}

void UI::formatUserInput(std::string &str, InputFormat format){
    if(str.size() == 0){return;}
    switch(format){

        case InputFormat::Anycase : {
        } break;

        case InputFormat::Uppercase : {
            for(int i = 0; i < str.size(); i++) {str[i] = toupper(str[i]);}
        } break;

        case InputFormat::Propercase : {
            str[0] = toupper(str[0]);
            for(int i = 1; i < str.size(); i++) {str[i] = tolower(str[i]);}
        } break;

        case InputFormat::Lowercase : {
            for(int i = 0; i < str.size(); i++) {str[i] = tolower(str[i]);}
        } break;

        default : {
            for(int i = 0; i < str.size(); i++) {str[i] = tolower(str[i]);}
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
    paddedText = formatPadStr(text, padSize);
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