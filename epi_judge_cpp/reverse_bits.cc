#include <bitset>
#include "test_framework/generic_test.h"


std::vector<unsigned long long> reverse_mapping(0xFFFF);

unsigned int SwapBits(unsigned int x, int i, int j) {
    if (((x >> i) & 0x1) != ((x >> j) & 0x1)) {
        unsigned int bitmask = (0x1 << i) | (0x1 << j);
        x ^= bitmask;
    }
    return x;
}


unsigned long long ReverseBits(unsigned long long x) {
    const int kMaskSize = 16;
    const int kBitMask = 0xFFFF;
    return reverse_mapping[x & kBitMask] << (3 * kMaskSize) |
        reverse_mapping[(x >> kMaskSize) & kBitMask] << (2 * kMaskSize) |
        reverse_mapping[(x >> (2 * kMaskSize)) & kBitMask] << kMaskSize |
        reverse_mapping[(x >> (3 * kMaskSize)) & kBitMask];
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  for (unsigned int i = 0; i < 0xFFFF; i++) {
      unsigned int tmp = i;
      for (int j = 0; j < 8; j++) {
          tmp = SwapBits(tmp, j, 15-j);
      }
      reverse_mapping[i] = tmp;
  }


  return GenericTestMain(args, "reverse_bits.cc", "reverse_bits.tsv",
                         &ReverseBits, DefaultComparator{}, param_names);
}
