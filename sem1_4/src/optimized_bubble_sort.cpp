#include "optimized_bubble_sort.h"

template <typename T>
void optimized_bubble_sort(std::vector<T>& a) {
    int n = static_cast<int>(a.size());

    for (int i = 0; i < n - 1; i++) {
        bool flag = false;

        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                T temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                flag = true;
            }
        }

        if (!flag) {
            break;
        }
    }
}

template void optimized_bubble_sort<int>(std::vector<int>&);
template void optimized_bubble_sort<double>(std::vector<double>&);