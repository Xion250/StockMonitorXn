
#include "portfolio.hpp"

void savePortfolio(Portfolio &portfolio){

    std::ofstream file("savedata/UntitledPortfolio1");

    if(!file.is_open()){std::cerr << "Failed to open file\n";}

    file.seekp(0);
    const char* pPtr = (const char*)&portfolio;
    file.write(pPtr, sizeof(Portfolio));
    file.close();

    std::cout << "Written to file\n";
}