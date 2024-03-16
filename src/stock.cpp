
#include "stock.hpp"

StockSymbol stringToStockSymbol(std::string &str){
    uint64_t symbol = 0;
    for(int i = 0; i < 5; i++){
        if(str[i] < 'A' || str[i] > 'Z'){break;}
        symbol <<= 5;
        symbol |= (str[i] - 'A' + 1);
    }
    return symbol;
}

std::string stockSymbolToString(StockSymbol symbol){
    std::string str = "";
    for(int i = 0; i < 5; i++){
        int c = (symbol >> (5*(4-i)))&31;
        if(c != 0){
            str += (char)(c + 'A' - 1);
        }
    }
    return str;
}

double Stock::calculatePrice() {
    if(!daily.validData){return 0.0;}
    return 0.5 * (daily.open + daily.close);
}