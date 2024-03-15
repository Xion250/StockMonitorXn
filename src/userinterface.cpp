
#include "userinterface.hpp"

Stock UI::getStock(){

    Stock stock;

    std::string symbolStr;

    if(!getUserInput("Enter stock symbol", symbolStr)){return Stock();}
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

void UI::PortfolioInterface::printPortfolioValue(){

    printf("Portfolio Overview\n\n");

    printf("Name : %s\n", 
        UI::Element(currentPortfolio.name.c_str()).med()
    );

    printf("Value $%s | Stocks %s\n\n", 
        UI::Element(currentPortfolio.totalStockValue()).small(), 
        UI::Element(currentPortfolio.stocks.size()).small()
    );
}

void UI::PortfolioInterface::printOverview(){
    system("clear");
    
    printPortfolioValue();

    printf("Stocks:%s\n", std::string(Tiny + 3*Small, '_').c_str());

    for(auto p : currentPortfolio.stocks){
        printStockLine(p.second);
    }
}

void UI::PortfolioInterface::addStock(){
    Stock stock = UI::getStock();

    if(currentPortfolio.addStock(stock)){
        printf("%s added\n", stockSymbolToString(stock.symbol).c_str());
    }
    else{
        printf("Failed to add stock\n");
    }
}

void UI::PortfolioInterface::renamePortfolio(){
    UI::getUserInput("Enter new portfolio name", currentPortfolio.name);
    printf("Portfolio name changed to %s\n", currentPortfolio.name.c_str());
}

void UI::PortfolioInterface::savePortfolio(){
    currentPortfolio.save();
    printf("Saved %s\n", currentPortfolio.name.c_str());
}

void UI::PortfolioInterface::loadPortfolio(){
    currentPortfolio.load("CommSec");
    printf("Loaded %s\n", currentPortfolio.name.c_str());
}

void UI::PortfolioInterface::createPortfolio(){
    currentPortfolio = Portfolio();
    UI::getUserInput("Enter new portfolio name", currentPortfolio.name);
}

void UI::PortfolioInterface::resetMenu(){
    system("clear");
    std::cout << "Stock Monitor\n";
    std::cout << "Current Portfolio: " << currentPortfolio.name << "\n";
}

bool UI::PortfolioInterface::menuInput(){
    std::string str;
    std::cin >> str;
    if(str == "Add"){addStock(); return true;}
    if(str == "Print"){printOverview(); return true;}
    if(str == "Rename"){renamePortfolio(); return true;}
    if(str == "Save"){savePortfolio(); return true;}
    if(str == "Open"){loadPortfolio(); return true;}
    if(str == "New"){createPortfolio(); return true;}
    if(str == "Exit"){return false;}

    printf("Invalid Command\n");
    std::cin.clear();
    return true;
}