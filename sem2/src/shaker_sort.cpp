#include "shaker_sort.h"

template <typename T>
void shaker_sort(std::vector<T>& a) {
    int left = 0;
    int right = static_cast<int>(a.size()) - 1;

    while (left < right) {
        bool flag = false;

        for (int j = left; j < right; j++) {
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

        right--;
        flag = false;

        for (int j = right; j > left; j--) {
            if (a[j] < a[j - 1]) {
                T temp = a[j];
                a[j] = a[j - 1];
                a[j - 1] = temp;
                flag = true;
            }
        }

        if (!flag) {
            break;
        }

        left++;
    }
}

template void shaker_sort<int>(std::vector<int>&);
template void shaker_sort<double>(std::vector<double>&);