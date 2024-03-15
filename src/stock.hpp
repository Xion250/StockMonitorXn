
#ifndef STOCK_HPP
#define STOCK_HPP

#include <cstdint>
#include <string>

typedef uint32_t StockSymbol;

StockSymbol stringToStockSymbol(std::string &str);
std::string stockSymbolToString(StockSymbol symbol);

struct Stock {
    public:
    StockSymbol symbol;
    double price;
    double lowPrice;
    double highPrice;
    double purchasePrice;
    unsigned long quantity;

    Stock() : symbol(0UL), price(0), quantity(0) {};

    std::string symbolStr(){
        return stockSymbolToString(symbol);
    }
};

namespace StockData {
    struct DailyOpenClose {
        public:
        bool validData;
        std::string from;
        std::string symbol;
        double open;
        double high;
        double low;
        double close;
        double volume;
        double afterHours;
        double preMarket;
        DailyOpenClose() {};
    };
}
#endif
