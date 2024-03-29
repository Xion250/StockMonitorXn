
#ifndef NETWORK_HPP
#define NETWORK_HPP

#define POLYGON_HTTP "https://api.polygon.io"
#define POLYGON_KEYREQ "apiKey="

#include "stock.hpp"
#include "filemanager.hpp"
#include <iostream>
#include <array>
#include <vector>
#include <map>

struct PolygonRequest;

class Network {
    public:
    Network() {};

    bool updateApiKey();

    bool updateStock(Stock &stock);
    
    std::string makePolygonRequest(PolygonRequest &request);
    std::string exec(const char* cmd);

    StockData::DailyOpenClose getDailyOpenClose(StockSymbol symbol);

    static const std::string getDate() {
        return "2024-02-01";
    }

    private:
    std::string polygonApiKey;
};

enum PolygonRequestType {DailyOpenClose};

struct PolygonRequest {
    std::string type;
    std::string symbolStr;
    std::string params;
    std::string getUrl(){return POLYGON_HTTP + type + symbolStr + params + POLYGON_KEYREQ;}

    PolygonRequest(PolygonRequestType requestType, StockSymbol symbol){
        switch(requestType){
            case PolygonRequestType::DailyOpenClose : {
                type = "/v1/open-close/";
                symbolStr = stockSymbolToString(symbol);
                params = "/" + Network::getDate() + "?";
                break;
            }
            default : {};
        }
    }
};

#endif