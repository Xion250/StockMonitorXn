
#ifndef NETWORK_HPP
#define NETWORK_HPP

#define POLYGON_HTTP "https://api.polygon.io"
#define POLYGON_API_KEY "apiKey=rdvte1AYfeh1QdHl2pkpmkVgvKyhhTcw"

#include "stock.hpp"
#include <iostream>
#include <array>

struct PolygonRequest;

class Network {
    public:

    Network() {};

    void updateStock(Stock &stock);
    std::string makePolygonRequest(PolygonRequest &request);
    std::string exec(const char* cmd);

    StockData::DailyOpenClose getDailyOpenClose(StockSymbol symbol);
};

enum PolygonRequestType {DailyOpenClose};

struct PolygonRequest {
    std::string type;
    std::string symbolStr;
    std::string params;
    std::string getUrl(){return POLYGON_HTTP + type + symbolStr + params + POLYGON_API_KEY;}

    PolygonRequest(PolygonRequestType requestType, StockSymbol symbol){
        switch(requestType){
            case PolygonRequestType::DailyOpenClose : {
                type = "/v1/open-close/";
                symbolStr = stockSymbolToString(symbol);
                params = "/2023-01-09?adjusted=true&";
                break;
            }
            default : {};
        }
    }
};

#endif