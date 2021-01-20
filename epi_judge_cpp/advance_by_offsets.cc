#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
bool CanReachEnd(const vector<int>& max_advance_steps) {
    int furthest_reached_so_far = 0, last_pos = max_advance_steps.size() - 1;
    for (int i = 0; i <= furthest_reached_so_far && furthest_reached_so_far < last_pos; i++) {
        furthest_reached_so_far = std::max(furthest_reached_so_far, max_advance_steps[i] + i);
    }
    return furthest_reached_so_far >= last_pos;
}

bool CanReachEnd1(const vector<int>& max_advance_steps) {
    int furthest_reached_so_far = 0, last_pos = max_advance_steps.size() - 1;
    bool reached_end =false;
    for (int i = 0; i <= furthest_reached_so_far; i++) {
        furthest_reached_so_far = std::max(furthest_reached_so_far, max_advance_steps[i] + i);
        if (furthest_reached_so_far >= last_pos) {
            reached_end = true;
            break;
        }
    }
    return reached_end;
}


int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"max_advance_steps"};
  return GenericTestMain(args, "advance_by_offsets.cc",
                         "advance_by_offsets.tsv", &CanReachEnd,
                         DefaultComparator{}, param_names);
}
