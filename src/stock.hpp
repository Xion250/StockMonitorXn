
#ifndef STOCK_HPP
#define STOCK_HPP

#include <cstdint>
#include <string>

typedef uint32_t StockSymbol;

struct StockInfo {
    public:
    double price;
    unsigned long quantity;

    StockInfo() : price(0.0), quantity(0) {};
    StockInfo(double p, int q) : price(p), quantity(q) {};
};

struct Stock {
    public:
    StockSymbol symbol;
    StockInfo info;

    Stock() : symbol(0UL), info(StockInfo()) {};
    Stock(StockSymbol s, StockInfo i) : symbol(s), info(i) {};
};

StockSymbol stringToStockSymbol(std::string &str);
std::string stockSymbolToString(StockSymbol symbol);

#endif
