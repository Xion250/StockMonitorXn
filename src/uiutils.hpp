
#ifndef UIUTILS_HPP
#define UIUTILS_HPP

#define TERMINAL_WIDTH 80

#define PAD_TYPE Strict

#include <string>

namespace UI {

    enum PadSize {Tiny = TERMINAL_WIDTH/16, Small = TERMINAL_WIDTH/8, Medium = TERMINAL_WIDTH/5, Large = TERMINAL_WIDTH/2};

    enum PadType {Overflow, Strict};

    enum InputFormat {Propercase, Anycase, Uppercase, Lowercase};

    std::string formatPadStr(std::string str, PadSize padSize, PadType padType = Overflow);
    std::string toDecimalStr(double value);
    std::string toDecimalStr(double value, char suffix);
    std::string toDecimalStr(char prefix, double value);

    void formatUserInput(std::string &str, InputFormat format);
    bool promptUserInput(std::string &prompt);

    template<typename T> bool getUserInput(std::string prompt, T &var){
        if(!promptUserInput(prompt)){return false;}
        std::cin >> var;
        return true;
    }

    bool getUserInput(std::string prompt, std::string &str, InputFormat format = Propercase);

    bool getExit();

    struct Element {
        public:

        template<typename T> Element(const T t) : text(std::to_string(t)) {};
        Element(const std::string t) : text(t) {};
        Element(const char *t) : text(t) {};
        Element(const double t) : text(toDecimalStr(t)) {};
        Element(const double t, char currencySymbol) : text(toDecimalStr(t, currencySymbol)) {};
        Element(char currencySymbol, const double t) : text(toDecimalStr(currencySymbol, t)) {};

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