
#ifndef MENU_HPP
#define MENU_HPP

#include "userinterface.hpp"
#include <functional>
#include <map>

namespace UI {

    class Menu {
        public:
        Portfolio currentPortfolio;
        Menu();
        bool menuInput();
        void resetMenu();

        private:
        std::unordered_map<std::string, void(UI::Menu::*)()> menuFunctionMap;

        void updateUI();
        void addStock();
        void removeStock();
        void renamePortfolio();
        void createPortfolio();
        void savePortfolio();
        void loadPortfolio();
        void toggleAutoSave();
    };
}


#endif