#include "bubble_sort.h"

template <typename T>
void bubble_sort(std::vector<T>& a) {
    int n = static_cast<int>(a.size());

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (a[j] > a[j + 1]) {
                T temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

template void bubble_sort<int>(std::vector<int>&);
template void bubble_sort<double>(std::vector<double>&);