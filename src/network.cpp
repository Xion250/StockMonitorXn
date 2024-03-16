
#include "network.hpp"

bool Network::updateStock(Stock &stock){

    StockData::DailyOpenClose data = getDailyOpenClose(stock.symbol);

    if(!data.validData){return false;}

    stock.daily = data;
    return true;
}

std::string Network::makePolygonRequest(PolygonRequest &request) {
    printf("Fetching %s Stock Data...\n", request.symbolStr.c_str());
    std::string cmd = std::string("curl ") + request.getUrl() + " -s";
    std::string jsonResult = exec(cmd.c_str());
    return jsonResult;
}

std::unordered_map<std::string, std::string> stringParseJson(std::string &jsonStr, bool &error) {
    std::vector<std::pair<std::string,std::string>> words(1, {"",""});
    bool first = true;
    for(char c : jsonStr){
        if(c == '{' || c == '}' || c == '"'){continue;}
        if(c == ':' || c == ','){
            first = !first;
            if(first){
                words.push_back({"",""});
            }
        }
        else{
            if(first){words.back().first += c;}
            else{words.back().second += c;}
        }        
    }
    std::unordered_map<std::string, std::string> jsonMap(words.begin(), words.end());

    if(jsonMap.find("status") == jsonMap.end()){
        std::cout << "Error, no json status code found\n";
        error = true;
    }
    if(jsonMap["status"] != "OK"){
        std::cout << "Error parsing json with code: " << jsonMap["status"] << "\n";
        error = true;
    }

    return jsonMap;
}

void jsonTryPut(std::unordered_map<std::string, std::string> &jsonMap, std::string name, std::string &var) {
    std::unordered_map<std::string, std::string>::iterator it = jsonMap.find('"' + name + '"');
    if(it == jsonMap.end()){return;}
    var = it->second;
}

void jsonTryPut(std::unordered_map<std::string, std::string> &jsonMap, std::string name, double &var) {
    std::unordered_map<std::string, std::string>::iterator it = jsonMap.find(name);
    if(it == jsonMap.end()){return;}
    sscanf(it->second.c_str(), "%lf", &var);
}

StockData::DailyOpenClose Network::getDailyOpenClose(StockSymbol symbol) {
    StockData::DailyOpenClose data;
    PolygonRequest prequest = PolygonRequest(DailyOpenClose, symbol);
    std::string jsonStr = makePolygonRequest(prequest);

    bool error = false;
    std::unordered_map<std::string, std::string> jsonMap = stringParseJson(jsonStr, error);

    if(error){
        data.validData = false;
        return data;
    }

    jsonTryPut(jsonMap, "open", data.open);
    jsonTryPut(jsonMap, "from", data.from);
    jsonTryPut(jsonMap, "volume", data.volume);
    jsonTryPut(jsonMap, "symbol", data.symbol);
    jsonTryPut(jsonMap, "preMarket", data.preMarket);
    jsonTryPut(jsonMap, "afterHours", data.afterHours);
    jsonTryPut(jsonMap, "high", data.high);
    jsonTryPut(jsonMap, "low", data.low);
    jsonTryPut(jsonMap, "close", data.close);
    data.validData = true;

    return data;
}



std::string Network::exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

