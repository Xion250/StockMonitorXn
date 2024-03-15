
#include "userinterface.hpp"

template<typename T>
std::string UI::formatValue(T value, UI::PadSize padSize){
    std::string str = std::to_string(value);
    if(padSize > str.size()){
        str += std::string(padSize - str.size(),' ');
    }
    return str;
}

std::string UI::formatStrValue(std::string str, UI::PadSize padSize){
    if(padSize > str.size()){
        str += std::string(padSize - str.size(),' ');
    }
    return str;
}

std::string UI::formatDoubleValue(double value, UI::PadSize padSize){
    std::string str = std::to_string((int)value) + '.' + std::to_string((int)(100*value)%100);
    if(padSize > str.size()){
        str += std::string(padSize - str.size(),' ');
    }
    return str;
}

template<typename T>
bool UI::getUserInput(std::string prompt, T &var){
    if(std::cin.peek() == '\n' || std::cin.peek() == '\0'){
        printf("%s\n", prompt.c_str());
    }
    if(getExit()){return false;}
    std::cin >> var;
    return true;
}

bool UI::getExit(){
    const char exitStr[] = "Exit";
    char str[4];
    // TODO : Implement Exit Code
    return false;
}

Stock UI::getStock(){

    Stock stock;
    std::string symbolStr = "";

    if(!getUserInput("Enter stock symbol", symbolStr)){return Stock();}
    if(!getUserInput("Enter stock price", stock.info.price)){return Stock();}
    if(!getUserInput("Enter stock quantity", stock.info.quantity)){return Stock();}

    stock.symbol = stringToStockSymbol(symbolStr);

    if(stock.symbol == 0){
        std::cout << symbolStr << "\n";
        std::cout << "Invalid stock symbol\n";
        return Stock();
    }

    return stock;
}

void UI::printStockLine(Stock &stock){
    double value = stock.info.price * stock.info.quantity;
    
    std::string paddedSymbol = formatStrValue(stockSymbolToString(stock.symbol), Tiny);
    std::string paddedQuantity = formatValue(stock.info.quantity, Small);
    std::string paddedPrice = formatDoubleValue(stock.info.price, Small);
    std::string paddedCentValue = formatDoubleValue(value, Small);

    printf("%s| %s Units @ $%s | total value $%s\n", paddedSymbol.c_str(), paddedQuantity.c_str(), paddedPrice.c_str(), paddedCentValue.c_str());
}

void UI::PortfolioInterface::printPortfolioValue(){
    double value = 0;
    for(auto p : currentPortfolio->stocks){
        value += p.second.info.price * p.second.info.quantity;
    }

    std::string paddedValue = formatDoubleValue(value, Small);
    std::string paddedCount = formatValue(currentPortfolio->stocks.size(), Small);

    printf("Portfolio Overview\n\n");

    printf("Name : %s\n", currentPortfolio->name.c_str());

    printf("Value $%s | Stocks %s\n\n", paddedValue.c_str(), paddedCount.c_str());
}

void UI::PortfolioInterface::printOverview(){
    system("clear");
    
    printPortfolioValue();

    printf("Stocks:%s\n", std::string(Tiny + 3*Small, '_').c_str());

    for(auto p : currentPortfolio->stocks){
        printStockLine(p.second);
    }
}

void UI::PortfolioInterface::addStock(){
    Stock stock = UI::getStock();
    if(stock.symbol == 0){return;}
    if(currentPortfolio->stocks.find(stock.symbol) != currentPortfolio->stocks.end()){
        std::cout << "Stock symbol already exists\n";
        return;
    }
    currentPortfolio->stocks[stock.symbol] = stock;
    printf("%s added\n", stockSymbolToString(stock.symbol).c_str());
}

void UI::PortfolioInterface::printTitle(){
    std::cout << "Stock Monitor\n";
    std::cout << "Current Portfolio: " << currentPortfolio->name << "\n";
}

void UI::PortfolioInterface::renamePortfolio(){
    if(std::cin.peek() == '\n' || std::cin.peek() == '\0'){
        printf("Enter new portfolio name\n");
    }
    std::cin >> currentPortfolio->name;
    printf("Portfolio name changed to %s\n", currentPortfolio->name.c_str());
}

bool UI::PortfolioInterface::menuInput(){
    std::string str;
    std::cin >> str;
    if(str == "Add"){addStock(); return true;}
    if(str == "Print"){printOverview(); return true;}
    if(str == "Rename"){renamePortfolio(); return true;}
    if(str == "Exit"){return false;}

    printf("Invalid Command\n");
    std::cin.clear();
    return true;
}