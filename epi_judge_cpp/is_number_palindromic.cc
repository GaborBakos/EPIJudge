#include "test_framework/generic_test.h"
bool IsPalindromeNumber_oN_space(int x) {
    if (x < 0) {
        return false;
    }
    if (x < 10) {
        return true;
    }

    std::vector<int> values(32);
    int counter = 0;
    while (x) {
        values[counter] = x % 10;
        x /= 10;
        counter++;
    }
    counter--;

    for (int i = 0; i <= counter / 2; i++) {
        if (values[i] != values[counter - i]) {
            return false;
        }
    }
    return true;
}


long long Reverse(int x) {
    long long res = 0;
    while (x) {
        res = res * 10 + x % 10;
        x /= 10;
    }
    return res;
}
bool IsPalindromeNumber_with_reverse(int x) {
    if (x < 0) {
        return false;
    }
    return Reverse(x) == x;

}

bool IsPalindromeNumber(int x) {
    if (x <= 0) {
        return x==0;
    }
    const int num_digits = static_cast<int>(floor(log10(x))) + 1;
    int msd_mask = static_cast<int>(pow(10, num_digits - 1));
    for (int i = 0; i < (num_digits / 2); i++) {
        if (x / msd_mask != x % 10) {
            return false;
        }
        x %= msd_mask;
        x /= 10;
        msd_mask /= 100;
    }
    return true;

}



int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "is_number_palindromic.cc",
                         "is_number_palindromic.tsv", &IsPalindromeNumber,
                         DefaultComparator{}, param_names);
}
