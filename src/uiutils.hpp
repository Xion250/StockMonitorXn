
#ifndef UIUTILS_HPP
#define UIUTILS_HPP

#include <string>

namespace UI {

    enum PadSize {Tiny = 5, Small = 8, Medium = 16, Large = 24};

    enum InputFormat {Default, Clear, Capital};

    std::string formatStrValue(std::string str, PadSize padSize);
    std::string formatDoubleValue(double value, PadSize size);
    template<typename T> 
    std::string formatValue(T value, UI::PadSize padSize){return formatStrValue(std::to_string(value), padSize);}
    std::string decimalToString(double value);

    void formatUserInput(std::string &str, InputFormat format);
    bool promptUserInput(std::string &prompt);

    template<typename T> bool getUserInput(std::string prompt, T &var){
        if(!promptUserInput(prompt)){return false;}
        std::cin >> var;
        return true;
    }

    bool getUserInput(std::string prompt, std::string &str, InputFormat format = Default);

    bool getExit();

    struct Element {
        public:

        template<typename T> Element(const T t) : text(std::to_string(t)) {};
        Element(const std::string t) : text(t) {};
        Element(const char *t) : text(t) {};
        Element(const double t) : text(decimalToString(t)) {};

        void setPadSize(PadSize padSize);

        const char *tiny();
        const char *small();
        const char *med();
        const char *large();


        private:
        std::string text;
        std::string paddedText;
    };
}

#endif