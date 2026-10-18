#include "binary_insertion_sort.h"

template <typename T>
void binary_insertion_sort(std::vector<T>& a) {
    int n = static_cast<int>(a.size());

    for (int i = 1; i < n; i++) {
        T key = a[i];
        int left = 0;
        int right = i;

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (key < a[mid]) {
                right = mid;
            }
            else {
                left = mid + 1;
            }
        }

        for (int j = i; j > left; j--) {
            a[j] = a[j - 1];
        }

        a[left] = key;
    }
}

template void binary_insertion_sort<int>(std::vector<int>&);
template void binary_insertion_sort<double>(std::vector<double>&);