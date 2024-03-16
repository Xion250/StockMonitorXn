
#include "menu.hpp"

UI::Menu::Menu (Network &n) : network(n) {

    currentPortfolio = Portfolio("Untitled");

    menuFunctionMap = {
        {"Add",         &UI::Menu::addStock         },
        {"Help",        &UI::Menu::printHelp        },
        {"Remove",      &UI::Menu::removeStock      },
        {"Update",      &UI::Menu::updateUI         },
        {"Rename",      &UI::Menu::renamePortfolio  },
        {"Save",        &UI::Menu::savePortfolio    },
        {"Open",        &UI::Menu::loadPortfolio    },
        {"New",         &UI::Menu::createPortfolio  },
        {"Back",        &UI::Menu::resetMenu        },
        {"Autosave",    &UI::Menu::toggleAutoSave   },
        {"View",        &UI::Menu::viewStock        }
    };
}

void UI::Menu::printHelp() {

    printf("Functions: \n");
    int i = 0;
    for(auto p : menuFunctionMap){
        printf("%s", UI::Element(p.first).med());
        if(i++ > 3){printf("\n"); i = 0;}
    }
    if(i != 0){std::cout << "\n";}
}

bool UI::Menu::menuInput() {
    std::string str;
    if(!UI::getUserInput("", str)){return false;}

    std::unordered_map<std::string, void(UI::Menu::*)()>::iterator it = menuFunctionMap.find(str);

    if(it != menuFunctionMap.end()){
        void (UI::Menu::*func)() = it->second;
        (this->*func)();
        return true;
    }

    if(str == "Exit"){return false;}

    printf("Invalid Command: %s\n", str.c_str());
    std::cin.clear();
    return true;
}


void UI::Menu::updateUI() {

    for(auto &p : currentPortfolio.stocks){
        if(!network.updateStock(p.second)){
            printf("Failed to update %s, ", stockSymbolToString(p.first).c_str());
            std::string response;
            UI::getUserInput("continue anyway? (y/n)", response);
            if(response != "Y"){return;}
        }
    }

    system("clear");
    printf("Autosave: ");
    if(currentPortfolio.data.autoSaveEnabled){
        currentPortfolio.save();
        printf("On\n");
    }
    else{printf("Off\n");}

    printBar();
    printOverview(currentPortfolio);
    printBar();
    printf("\n");
}

void UI::Menu::viewStock() {
    std::string symbolStr;
    UI::getUserInput("Enter stock symbol to view", symbolStr, Uppercase);
    auto it = currentPortfolio.stocks.find(stringToStockSymbol(symbolStr));
    if(it == currentPortfolio.stocks.end()){
        printf("Could not find stock in portfolio\n");
        return;
    }
    UI::printStockView(it->second);
}

void UI::Menu::removeStock() {
    std::string symbolStr;
    UI::getUserInput("Enter stock symbol", symbolStr, Uppercase);
    auto it = currentPortfolio.stocks.find(stringToStockSymbol(symbolStr));
    if(it == currentPortfolio.stocks.end()){
        printf("Could not find stock in portfolio\n");
        return;
    }
    currentPortfolio.stocks.erase(it);
    updateUI();
}

void UI::Menu::addStock() {
    Stock stock = UI::getStock();
    if(!currentPortfolio.addStock(stock)){
        printf("Failed to add stock\n");
        return;
    }
    updateUI();
}

void UI::Menu::renamePortfolio() {
    UI::getUserInput("Enter new portfolio name", currentPortfolio.data.name, Anycase);
    updateUI();
}

void UI::Menu::savePortfolio() {
    currentPortfolio.save();
    printf("Saved %s\n", currentPortfolio.data.name.c_str());
}

void UI::Menu::loadPortfolio() {
    std::string name;
    UI::getUserInput("Enter portfolio name", name, Anycase);
    currentPortfolio.load(name);
    updateUI();
}

void UI::Menu::createPortfolio() {
    currentPortfolio = Portfolio();
    UI::getUserInput("Enter new portfolio name", currentPortfolio.data.name, Anycase);
    updateUI();
}

void UI::Menu::resetMenu() {
    system("clear");
    std::cout << "Stock Monitor\n";
    std::cout << "Current Portfolio: " << currentPortfolio.data.name << "\n";
}

void UI::Menu::toggleAutoSave() {
    std::string setFalse;
    UI::getUserInput("Autosave (On/Off) ?", setFalse);
    currentPortfolio.data.autoSaveEnabled = (setFalse != "Off");
    updateUI();
}