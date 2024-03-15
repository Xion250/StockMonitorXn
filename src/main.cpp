
#include "menu.hpp"

int main(){

    Network network = Network();

    UI::Menu menu = UI::Menu(network);

    menu.resetMenu();

    while(menu.menuInput()){}

    return 0;
}

//Add STO 7.2 80 Add FANG 24.3 27