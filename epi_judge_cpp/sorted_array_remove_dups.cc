#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::vector;
// Returns the number of valid entries after deletion.
int DeleteDuplicates(vector<int>* A_ptr) {
    vector<int>& A = *A_ptr;
    int counter = 0;
    if (empty(A)) {
        return counter;
    }
    counter++;
    for (int i = 1; i < A.size(); i++) {
        // Either check if the current unique element is different compared to the ith entry
        //if (A[counter - 1] != A[i]) {
        //    A[counter++] = A[i];
        //}
        // or check if elements next to each other are different
        if (A[i - 1] != A[i]) {
            A[counter++] = A[i];
        }
    }
    return counter;
}
vector<int> DeleteDuplicatesWrapper(TimedExecutor& executor, vector<int> A) {
  int end = executor.Run([&] { return DeleteDuplicates(&A); });
  A.resize(end);
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "A"};
  return GenericTestMain(
      args, "sorted_array_remove_dups.cc", "sorted_array_remove_dups.tsv",
      &DeleteDuplicatesWrapper, DefaultComparator{}, param_names);
}
