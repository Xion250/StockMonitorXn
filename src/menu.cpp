
#include "menu.hpp"

UI::Menu::Menu () {

    currentPortfolio = Portfolio("Untitled");

    menuFunctionMap = {
        {"Add",         &UI::Menu::addStock         },
        {"Remove",      &UI::Menu::removeStock      },
        {"Print",       &UI::Menu::updateUI         },
        {"Rename",      &UI::Menu::renamePortfolio  },
        {"Save",        &UI::Menu::savePortfolio    },
        {"Open",        &UI::Menu::loadPortfolio    },
        {"New",         &UI::Menu::createPortfolio  },
        {"Back",        &UI::Menu::resetMenu        },
        {"Autosave",    &UI::Menu::toggleAutoSave   }
    };
}

bool UI::Menu::menuInput(){
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
    system("clear");
    printf("Autosave: ");
    if(currentPortfolio.data.autoSaveEnabled){
        currentPortfolio.save();
        printf("On\n");
    }
    else{printf("Off\n");}

    std::cout << std::string(80, '_') << "\n";
    printOverview(currentPortfolio);
    std::cout << std::string(80, '_') << "\n";
    printf("\n");
}

void UI::Menu::removeStock() {
    std::string symbolStr;
    std::cin >> symbolStr;
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
    UI::getUserInput("Enter new portfolio name", currentPortfolio.data.name, Clear);
    updateUI();
}

void UI::Menu::savePortfolio(){
    currentPortfolio.save();
    printf("Saved %s\n", currentPortfolio.data.name.c_str());
}

void UI::Menu::loadPortfolio(){
    std::string name;
    UI::getUserInput("Enter portfolio name", name, Clear);
    currentPortfolio.load(name);
    updateUI();
}

void UI::Menu::createPortfolio(){
    currentPortfolio = Portfolio();
    UI::getUserInput("Enter new portfolio name", currentPortfolio.data.name, Clear);
    updateUI();
}

void UI::Menu::resetMenu(){
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