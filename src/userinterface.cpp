
#include "userinterface.hpp"

Stock UI::getStock(){

    Stock stock;

    std::string symbolStr;

    if(!getUserInput("Enter stock symbol", symbolStr, Capital)){return Stock();}
    if(!getUserInput("Enter stock price", stock.price)){return Stock();}
    if(!getUserInput("Enter stock quantity", stock.quantity)){return Stock();}

    stock.symbol = stringToStockSymbol(symbolStr);

    if(stock.symbol == 0){
        std::cout << symbolStr << "\n";
        std::cout << "Invalid stock symbol\n";
        return Stock();
    }

    return stock;
}

void UI::printStockLine(Stock &stock){

    double value = stock.price * stock.quantity;
    
    printf("%s| %s Units @ $%s | total value $%s\n",
        UI::Element(stock.symbolStr()).tiny(),
        UI::Element(stock.quantity).small(),
        UI::Element(stock.price).small(),
        UI::Element(value).small()
    );
}

void UI::printPortfolioValue(const Portfolio &portfolio) {

    printf("Portfolio Overview\n\n");

    printf("Name : %s\n", 
        UI::Element(portfolio.data.name.c_str()).med()
    );

    printf("Value $%s | Stocks %s\n\n", 
        UI::Element(portfolio.totalStockValue()).small(), 
        UI::Element(portfolio.stocks.size()).small()
    );
}

void UI::printOverview(const Portfolio &portfolio) {
    
    printPortfolioValue(portfolio);

    printf("Stocks:\n");

    for(auto p : portfolio.stocks){
        printStockLine(p.second);
    }
}