#include "insertion_sort.h"

template <typename T>
void insertion_sort(std::vector<T>& a) {
    int n = static_cast<int>(a.size());

    for (int i = 1; i < n; i++) {
        T key = a[i];
        int j = i - 1;

        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = key;
    }
}

template void insertion_sort<int>(std::vector<int>&);
template void insertion_sort<double>(std::vector<double>&);