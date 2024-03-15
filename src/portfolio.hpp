#pragma once
#ifndef PORTFOLIO_HPP
#define PORTFOLIO_HPP

#define SAVE_DATA_PATH "savedata/"

#include "stock.hpp"
#include <fstream>
#include <iostream>
#include <map>

struct PortfolioData;

struct Portfolio {
    public:
    uint16_t stockCount;

    std::string name;
    std::string fileName;
    
    std::unordered_map<StockSymbol,Stock> stocks;

    Portfolio() : name("Untitled1"), fileName("Untitled1") {};
    Portfolio(std::string n) : name(n), fileName(n) {};
    Portfolio(const PortfolioData &p);

    double totalStockValue();

    bool addStock(Stock &stock);

    void save();

    void load(std::string name);

    private:
    void loadData(std::ifstream &file);
    void saveData(std::ofstream &file);
    void loadStockData(std::ifstream &file);
    void saveStockData(std::ofstream &file);
};

struct PortfolioData {
    public:
    uint16_t stockCount;
    std::string name;
    PortfolioData(){};
    PortfolioData(const Portfolio &p) : stockCount(p.stocks.size()), name(p.name) {};
};

void verifyPortfolio(Portfolio &portfolio);

#endif