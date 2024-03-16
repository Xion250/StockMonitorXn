
#include "userinterface.hpp"

Stock UI::getStock(){

    Stock stock;

    std::string symbolStr;

    if(!getUserInput("Enter stock symbol", symbolStr, Uppercase)){return Stock();}
    if(!getUserInput("Enter stock purchase price", stock.purchasePrice)){return Stock();}
    if(!getUserInput("Enter stock quantity", stock.quantity)){return Stock();}

    stock.symbol = stringToStockSymbol(symbolStr);

    if(stock.symbol == 0){
        std::cout << symbolStr << "\n";
        std::cout << "Invalid stock symbol\n";
        return Stock();
    }

    return stock;
}

void UI::printStockLineHeader() {
    printf(" %s | %s | %s | %s | %s | %s\n",
        UI::Element("SYMB").tiny(),
        UI::Element("Units").small(),
        UI::Element(" Price").small(),
        UI::Element(" Value").med(),
        UI::Element(" P/L%").small(),
        UI::Element(" P/L").small()
    );
}

void UI::printBar() {
    std::cout << std::string(TERMINAL_WIDTH, '_') + "\n";
}

void UI::printStockLine(Stock &stock){

    double price = stock.calculatePrice();

    double totalValue = price * stock.quantity;
    double purchaseValue = stock.purchasePrice * stock.quantity;

    double profitLoss = totalValue - purchaseValue;

    double profitLossPercent = 100 - 100*(totalValue / purchaseValue);

    printf(" %s | %s | %s | %s | %s | %s\n",
        UI::Element(stock.symbolStr()).tiny(),
        UI::Element(stock.quantity).small(),
        UI::Element('$', price).small(),
        UI::Element('$', totalValue).med(),
        UI::Element(profitLossPercent, '%').small(),
        UI::Element('$', profitLoss).small()
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

    printStockLineHeader();

    for(auto p : portfolio.stocks){
        printStockLine(p.second);
    }
}

void UI::printStockView(Stock &stock) {
    system("clear");
    printBar();
    printStockLineHeader();
    printStockLine(stock);
    printBar();
    printf("Open: %s | Close: %s | Low: %s | High: %s",
        UI::Element('$', stock.daily.open).small(),
        UI::Element('$', stock.daily.close).small(),
        UI::Element('$', stock.daily.low).small(),
        UI::Element('$', stock.daily.high).small()
    );
    printf("\n");
}