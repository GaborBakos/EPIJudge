#include "test_framework/generic_test.h"
double Power(double x, int y) {
    if (y < 0) {
        x = 1 / x;
        y *= -1;
    }

    if (y == 0) {
        return 1;
    }

    if (y == 1) {
        return x;
    }
    long long power = y;
    double result = 1.0;
    while (power) {
        if (power & 1) {
            result *= x;
        }
        x *= x, power >>= 1;
    }
  return result;
}


double Power(double x, int y) {
    double result = 1.0;
    if (y < 0) {
        x = 1 / x;
        y *= -1;
    }

    if (y == 0) {
        return result;
    }

    if (y == 1) {
        return x;
    }

    long long power = y;

    while (power) {
        if (power & 1) {
            result *= x;
        }
        x *= x, power >>= 1;
    }
    return result;
}




int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "power_x_y.cc", "power_x_y.tsv", &Power,
                         DefaultComparator{}, param_names);
}
