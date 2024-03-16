#pragma once
#ifndef PORTFOLIO_HPP
#define PORTFOLIO_HPP

#include "filemanager.hpp"
#include "stock.hpp"
#include <fstream>
#include <iostream>
#include <map>

struct PortfolioData {
    public:

    uint16_t stockCount;
    std::string name;
    std::string fileName;
    bool autoSaveEnabled;
    PortfolioData() {};
    PortfolioData(std::string n) : name(n), fileName(n) {};
};

struct Portfolio {
    public:
    
    PortfolioData data;
    std::unordered_map<StockSymbol,Stock> stocks;

    Portfolio() : data() {};
    Portfolio(std::string n) : data(n) {};
    Portfolio(const PortfolioData &d) : data(d) {};

    double totalStockValue() const;

    bool addStock(Stock &stock);

    void save();

    void load(std::string name);

    private:
    void loadData(std::ifstream &file);
    void saveData(std::ofstream &file);
    void loadStockData(std::ifstream &file);
    void saveStockData(std::ofstream &file);
};

void verifyPortfolio(Portfolio &portfolio);

#endif