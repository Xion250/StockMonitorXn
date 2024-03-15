
#include "userinterface.hpp"
//#include "portfolio.hpp"
//#include "stock.hpp"

int main(){

    Portfolio portfolio = Portfolio("Untitled");

    UI::PortfolioInterface pUI = UI::PortfolioInterface(portfolio);

    while(pUI.menuInput()){}
    return 0;
}

//Add STO 7.2 80 Add FANG 24.3 27