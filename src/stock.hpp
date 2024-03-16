
#ifndef STOCK_HPP
#define STOCK_HPP

#include <cstdint>
#include <string>

typedef uint32_t StockSymbol;

StockSymbol stringToStockSymbol(std::string &str);
std::string stockSymbolToString(StockSymbol symbol);

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

struct Stock {
    public:

    StockSymbol symbol;
    double purchasePrice;
    unsigned long quantity;
    
    StockData::DailyOpenClose daily;

    Stock() : symbol(0UL), purchasePrice(0), quantity(0) {};

    std::string symbolStr(){
        return stockSymbolToString(symbol);
    }

    double calculatePrice();
};

#endif
