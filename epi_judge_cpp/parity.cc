#include "test_framework/generic_test.h"

std::vector<short> kPrecomputedPartity(0xFFFF);


short Parity_inefficient(unsigned long long x) {
    short parity = 0;
    while (x) {
        parity ^= x & 1;
        x >>= 1;
    }
  return parity;
}


short Parity_fast(unsigned short x) {
    short parity = 0;
    while (x) {
        parity ^= 1;
        x &= (x - 1);
    }
    return parity;
}


short Parity_xor(unsigned long long x) {
    const int kMaskSize = 16;
    const int kBitMask = 0xFFFF;
    x ^= x >> 32;
    x ^= x >> 16;
    return kPrecomputedPartity[x  & kBitMask];
}


short Parity_short(unsigned short x) {
    short parity = 0;
    while (x) {
        parity ^= (x & 1);
        x >>= 1;
    }
    return parity;
}


short Parity(unsigned long long x) {
    const int kMaskSize = 16;
    const int kBitMask = 0xFFFF;
    return (
        kPrecomputedPartity[x >> (3 * kMaskSize)] ^
        kPrecomputedPartity[(x >> (2 * kMaskSize)) & kBitMask] ^
        kPrecomputedPartity[(x >> kMaskSize) & kBitMask] ^
        kPrecomputedPartity[x & kBitMask]
        );
}


unsigned long long RightPropagate(unsigned long long x) {
    // 1011000 -> 1011111 (since 1000 - 1 = 111)
    return x | (x - 1);
}


unsigned long long ModPowerofTwo(unsigned long long x, unsigned long long d) {
    // d needs to be a power of 2
    return x & (d - 1);
}

bool TestPowerofTwo(unsigned long long x) {
    return x && (!(x & (x - 1)));
}




int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  for (unsigned short i = 0; i < 0xFFFF; i++) {
      kPrecomputedPartity[i] = Parity_fast(i);
  }

  return GenericTestMain(args, "parity.cc", "parity.tsv", &Parity_xor,
                         DefaultComparator{}, param_names);
}
