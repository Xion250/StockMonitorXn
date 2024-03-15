
#include "userinterface.hpp"
//#include "portfolio.hpp"
//#include "stock.hpp"

int main(){
    system("clear");

    Portfolio portfolio = Portfolio();
    UI::PortfolioInterface pUI = UI::PortfolioInterface(portfolio);

    savePortfolio(portfolio);

    pUI.printTitle();

    while(pUI.menuInput()){}
    return 0;
}