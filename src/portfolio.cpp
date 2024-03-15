
#include "portfolio.hpp"

Portfolio::Portfolio(const PortfolioData &p) : name(p.name), fileName(p.name), stockCount(p.stockCount) {};

double Portfolio::totalStockValue(){
    double value = 0;
    for(auto p : stocks){
        value += p.second.price * p.second.quantity;
    }
    return value;
}

bool Portfolio::addStock(Stock &stock){
    if(stock.symbol == 0){return false;}
    if(stocks.find(stock.symbol) != stocks.end()){return false;}
    stocks[stock.symbol] = stock;
    return true;
}

void Portfolio::load(std::string name){

    std::ifstream file(SAVE_DATA_PATH + name);

    if(!file.is_open()){std::cerr << "Failed to open file\n"; return;}

    loadData(file);

    loadStockData(file);

    file.close();

    verifyPortfolio(*this);
}

void Portfolio::save() {

    verifyPortfolio(*this);

    std::string filePath = SAVE_DATA_PATH + fileName;
    
    std::ofstream file(filePath.c_str());

    if(!file.is_open()){std::cerr << "Failed to open file\n"; return;}

    saveData(file);

    saveStockData(file);

    file.close();

    if(fileName != name){
        std::string newFilePath = SAVE_DATA_PATH + name;
        std::rename(filePath.c_str(), newFilePath.c_str());
    }
}

void Portfolio::loadData(std::ifstream &file) {
    PortfolioData saveData;
    file.seekg(0);
    char *saveDataPtr = (char*)&saveData;
    file.read(saveDataPtr, sizeof(PortfolioData));
    *this = Portfolio(saveData);
}

void Portfolio::saveData(std::ofstream &file) {
    PortfolioData saveData(*this);
    file.seekp(0);
    char *saveDataPtr = (char*)&saveData;
    file.write(saveDataPtr, sizeof(PortfolioData));
}


void Portfolio::loadStockData(std::ifstream &file) {
    const int byteSize = stockCount * sizeof(std::pair<StockSymbol,Stock>);

    std::vector<std::pair<StockSymbol,Stock>> tempStocks(stockCount);

    file.seekg(sizeof(PortfolioData));
    char *stockPtr = (char*)&tempStocks[0];
    file.read(stockPtr, byteSize);

    for(std::pair<StockSymbol,Stock> p : tempStocks){
        stocks[p.first] = p.second;
    }
}
void Portfolio::saveStockData(std::ofstream &file) {
    const int byteSize = stocks.size() * sizeof(std::pair<StockSymbol,Stock>);

    std::vector<std::pair<StockSymbol,Stock>> tempStocks;

    for(std::pair<const StockSymbol,Stock> p : stocks){
        tempStocks.push_back(p);
    }

    file.seekp(sizeof(PortfolioData));
    char *stockPtr = (char*)&tempStocks[0].first;

    file.write(stockPtr, byteSize);
}

void verifyPortfolio(Portfolio &portfolio) {
    if(portfolio.name.size() == 0){
        portfolio.name = "Untitled";
    }
    if(portfolio.fileName.size() == 0){
        portfolio.fileName = portfolio.name;
    }

    portfolio.stockCount = portfolio.stocks.size();
}