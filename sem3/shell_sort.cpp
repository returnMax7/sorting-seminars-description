#include "shell_sort.h"
using namespace std;

template <typename T>
void shell_sort(vector<T>& a) {
    int n = static_cast<int>(a.size());
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            T key = a[i];
            int j = i;
            while (j >= gap && a[j - gap] > key) {
                a[j] = a[j - gap];
                j -= gap;
            }
            a[j] = key;
        }
    }
}

template void shell_sort<int>(vector<int>&);
template void shell_sort<double>(vector<double>&);
