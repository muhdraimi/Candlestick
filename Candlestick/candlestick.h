#include <string>
#include <vector>
#include "OrderBookEntry.h"

class Candlestick
{
public:
    std::string time, product,type;
    double high,low,open,close;

    Candlestick(std::string time ,std::string product, std::string type,
        double high,double low, double open, double close);

    void printCandleStick();
    
    static void printCandlestickTable(std::vector<Candlestick> candles);

    static std::vector<Candlestick> calculateCandlesticks(
        std::vector<OrderBookEntry> entries
        );

    static void printCandleStickPlot(std::vector<Candlestick> candles);

};