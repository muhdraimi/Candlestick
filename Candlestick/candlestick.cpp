#include "candlestick.h"
#include <iostream>
#include <map>


Candlestick::Candlestick(std::string time ,std::string product, std::string type,
        double high,double low, double open, double close) : 
        time(time),product(product),type(type),high(high),low(low),open(open),close(close){}

void Candlestick::printCandleStick()
{
std::cout   << time << "\t"
            << product << "\t"
            << type << "\t"
            << high << "\t"
            << low << "\t"
            << open << "\t"
            << close << "\t"
            <<std::endl;
}
    
    
void Candlestick::printCandlestickTable(std::vector<Candlestick> candles)
{
std::cout   << "time"<< "\t"
            << "product" << "\t"
            << "type" << "\t"
            << "high" << "\t"
            << "low" << "\t"
            << "open" << "\t"
            << "close" << "\t"
            << std::endl;

    for (Candlestick & candle : candles){
        candle.printCandleStick();
    }
}
 
std::vector<Candlestick> Candlestick::calculateCandlesticks(
        std::vector<OrderBookEntry> entries)
        {
            std::vector<Candlestick> candles;
            
            std::string product{entries[0].product},
                    time{entries[0].timestamp},
                    type{OrderBookEntry::obtToString(entries[0].orderType)};
            double high,low,open,close;
            double totalValue, totalAmount;

            std::string firstTimestamp{entries[0].timestamp};
            

            for(OrderBookEntry & entry : entries){
                if (time == entry.timestamp){
                    totalValue += entry.price * entry.amount;
                    totalAmount += entry.amount;
                    high = std::max(high,entry.price);
                    low = std::min(low,entry.price);
                }
                else{
                    
                    if(time == firstTimestamp)
                {
                    open = totalValue / totalAmount;
                }
                else{

                    close = totalValue / totalAmount;
                    candles.push_back(
                        Candlestick{time,product,type,high,low,open,close});
                    open = close;
                
                }
                    
                    
                    
                    time = entry.timestamp;
                    product = entries[0].product;
                    type = OrderBookEntry::obtToString(entries[0].orderType);

                    high = low = entries[0].price;
                    totalValue = totalAmount = 0.;
                }
            }

            return candles;
        }

void Candlestick::printCandleStickPlot(std::vector<Candlestick> candles){
    
    std::cout << "Candlestick::printCandleStickPlot" << std::endl;

    double highest = candles[0].high;
    double lowest = candles[0].low;
    for (Candlestick & candle : candles)
    {
        highest = std::max(highest, candle.high);
        lowest = std::min(lowest, candle.low);
    }

    int steps = 100;
    double yRange = highest - lowest;
    double stepSize = yRange / steps;

    for (double y = highest; y > lowest ; y-= stepSize)
    {
        std::cout << y << "\t";

        int maxSize = 10;
        if(maxSize > candles.size())
        {
            maxSize = candles.size();
        }

        for(int i=0; i < maxSize; i++)
        {
            Candlestick candle = candles[i];
             if(y > candle.high || y <candle.low){
                std::cout <<  " " ;
             }
             else if(
                (y < candle.high && y > candle.open && y > candle.close)
                || (y > candle.low && y < candle.open && y> candle.close))
             {
                std::cout << "  |  ";
             }
             else{
                if(candle.open > candle.close){
                    std::cout << "---";
                }else{
                    std::cout << " +++";
                }
             }
             std::cout << std::endl;
        }





    }
}
