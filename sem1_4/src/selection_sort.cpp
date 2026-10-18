#include "selection_sort.h"

template <typename T>
void selection_sort(std::vector<T>& a) {
    int n = static_cast<int>(a.size());

    for (int i = 0; i < n - 1; i++) {
        int min_index = i;

        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[min_index]) {
                min_index = j;
            }
        }

        if (i != min_index) {
            T temp = a[i];
            a[i] = a[min_index];
            a[min_index] = temp;
        }
    }
}

template void selection_sort<int>(std::vector<int>&);
template void selection_sort<double>(std::vector<double>&);