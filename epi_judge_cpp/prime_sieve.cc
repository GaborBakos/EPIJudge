#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
// Given n, return all primes up to and including n.
vector<int> GeneratePrimes1(int n) {
    if (n < 2) {
        return {};
    }
    std::vector<int> primes = { 2 };

    bool is_prime = true;
    for (int i = 3; i <= n; i += 2) {
        is_prime = true;
        for (auto prime : primes) {
            if (i % prime == 0) {
                is_prime = false;
            }
        }
        if (is_prime) {
            primes.push_back(i);
        }
    }

    return primes;
}

vector<int> GeneratePrimes(int n) {
    if (n < 2) {
        return {};
    }
    const int size = floor(0.5 * (n - 3)) + 1;
    vector<int> primes{ 2 };

    std::deque<bool> is_prime(size, true);
    for (int i = 0; i < size; i++) {
        if (is_prime[i]) {
            int p = (i * 2) + 3;
            primes.emplace_back(p);
            // Sieving from p^2, whose value is (4i^2 + 12i + 9). The index in is_prime is (2i^2 + 6i + 3) because is_prime[i] represents 2i + 3.
            // Note that we need to use long long for j because p^2 might overflow.

            for (long long j = 2LL * i * i + 6 * i + 3; j < size; j += p) {
                is_prime[j] = false;
            }
        }

    }

    return primes;
}




int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "prime_sieve.cc", "prime_sieve.tsv",
                         &GeneratePrimes, DefaultComparator{}, param_names);
}
