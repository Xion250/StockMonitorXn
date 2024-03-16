
#ifndef MENU_HPP
#define MENU_HPP

#include "userinterface.hpp"
#include "network.hpp"
#include <functional>
#include <map>

namespace UI {

    class Menu {
        public:
        Portfolio currentPortfolio;
        Network &network;

        Menu(Network &n);
        bool menuInput();
        void resetMenu();

        private:
        std::unordered_map<std::string, void(UI::Menu::*)()> menuFunctionMap;

        void updateUI();
        void addStock();
        void printHelp();
        void removeStock();
        void renamePortfolio();
        void createPortfolio();
        void savePortfolio();
        void loadPortfolio();
        void toggleAutoSave();
        void viewStock();
        void setApiKey();
    };
}


#endif