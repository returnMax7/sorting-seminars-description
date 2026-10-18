#include "exchange_sort.h"

template <typename T>
void exchange_sort(std::vector<T>& a) {
    int n = static_cast<int>(a.size());

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] > a[j]) {
                T temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}

template void exchange_sort<int>(std::vector<int>&);
template void exchange_sort<double>(std::vector<double>&);