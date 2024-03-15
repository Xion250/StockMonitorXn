#pragma once
#ifndef PORTFOLIO_HPP
#define PORTFOLIO_HPP

#include "stock.hpp"
#include <fstream>
#include <iostream>
#include <map>

struct Portfolio {
    std::string name;
    std::unordered_map<StockSymbol,Stock> stocks;

    Portfolio() : name("Untitled1") {};
};

void loadPortfolio();

void savePortfolio(Portfolio &portfolio);

#endif