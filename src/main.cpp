
#include "menu.hpp"

int main(){

    Network network = Network();

    //std::string symbol = "NVDA";
    //network.getDailyOpenClose(stringToStockSymbol(symbol));
    //return 0;

    UI::Menu menu = UI::Menu(network);

    menu.resetMenu();

    while(menu.menuInput()){}

    return 0;
}