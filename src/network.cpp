
#include "network.hpp"

void Network::updateStock(Stock &stock){
    // Random noise;

    double testNoise = 0.8 + 0.4 * ((double)rand() / INT_MAX);

    std::cout << "Noise: " << testNoise << "\n";

    stock.price = stock.purchasePrice * testNoise;
}

std::string Network::makePolygonRequest(PolygonRequest &request) {
    std::string cmd = std::string("curl -s ") + request.getUrl();
    std::cout << "CMD Size: " << cmd.size() << "\n";
    std::cout << "CMD: " << cmd.c_str() << "\n";
    std::string jsonResult = exec(cmd.c_str());
    std::cout << "JSON: " << jsonResult << "\n";
    return jsonResult;
}

StockData::DailyOpenClose Network::getDailyOpenClose(StockSymbol symbol) {
    StockData::DailyOpenClose data;
    PolygonRequest prequest = PolygonRequest(DailyOpenClose, symbol);
    std::string jsonStr = makePolygonRequest(prequest);

    sscanf(jsonStr.c_str(), "%s %s %lf %lf %lf %lf %lu %lf %lf",
        &data.from[0],
        &data.symbol[0],
        &data.open,
        &data.high,
        &data.low,
        &data.close,
        &data.volume,
        &data.afterHours,
        &data.preMarket
    );

    /*
        sscanf(jsonStr.c_str(), '"{
        "status": "OK",
        "from": "2023-01-09",
        "symbol": "AAPL",
        "open": 130.465,
        "high": 133.41,
        "low": 129.89,
        "close": 130.15,
        "volume": 70790813,
        "afterHours": 129.85,
        "preMarket": 129.6
        }"',
    */

    std::cout << data.volume << ", " << data.open << ", " << data.symbol << "\n";

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

