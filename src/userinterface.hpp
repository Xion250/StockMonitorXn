
#ifndef USERINTERFACE_HPP
#define USERINTERFACE_HPP

#include "portfolio.hpp"
//#include "stock.hpp"
#include <iostream>

namespace UI {

    enum PadSize {Tiny = 5, Small = 8, Medium = 16, Large = 24};

    template<typename T> std::string formatValue(T value, PadSize size);
    std::string formatStrValue(std::string str, PadSize padSize);
    std::string formatDoubleValue(double value, PadSize size);

    template<typename T> bool getUserInput(std::string prompt, T &var);

    bool getExit();

    Stock getStock();
    void printStockLine(Stock &stock);

    class PortfolioInterface {
        public:
        Portfolio *currentPortfolio;

        void printTitle();

        void printPortfolioValue();
        void printOverview();
        void addStock();
        bool menuInput();

        void renamePortfolio();

        PortfolioInterface(Portfolio &portfolio) : currentPortfolio(&portfolio) {};
    };

}

#endif