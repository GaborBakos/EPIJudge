#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
double BuyAndSellStockOnce(const vector<double>& prices) {
    double current_min = static_cast<double>(std::numeric_limits<int>::max());
    double max_profit = 0; 
    //for (int i = 0; i < prices.size(); i++) {
    //    max_profit = std::max(prices[i] - current_min, max_profit);
    //    current_min = std::min(prices[i], current_min);
    //}

    for (double price : prices) {
        current_min = std::min(price, current_min);
        max_profit = std::max(price - current_min, max_profit);
    }

    return max_profit;
}

int main(int argc, char* argv[]) {
      std::vector<std::string> args{argv + 1, argv + argc};
      std::vector<std::string> param_names{"prices"};
      return GenericTestMain(args, "buy_and_sell_stock.cc",
                             "buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
                             DefaultComparator{}, param_names);
}
