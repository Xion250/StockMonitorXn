
#ifndef USERINTERFACE_HPP
#define USERINTERFACE_HPP

#include "portfolio.hpp"
#include "uiutils.hpp"
#include <iostream>

namespace UI {
    Stock getStock();
    void printStockLine(Stock &stock);
    void printPortfolioValue(const Portfolio &portfolio);
    void printOverview(const Portfolio &portfolio);
}

#endif