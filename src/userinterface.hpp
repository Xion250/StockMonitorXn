
#ifndef USERINTERFACE_HPP
#define USERINTERFACE_HPP

#include "portfolio.hpp"
#include "uiutils.hpp"
#include <iostream>

namespace UI {

    Stock getStock();
    void printStockLine(Stock &stock);

    class PortfolioInterface {
        public:
        Portfolio &currentPortfolio;

        void printPortfolioValue();
        void printOverview();
        void addStock();
        bool menuInput();

        void resetMenu();

        void renamePortfolio();
        void createPortfolio();
        void savePortfolio();
        void loadPortfolio();

        PortfolioInterface(Portfolio &portfolio) : currentPortfolio(portfolio) {};
    };

}

#endif