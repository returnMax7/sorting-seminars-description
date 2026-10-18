#include "quick_sort.h"
using namespace std;

template <typename T>
int partiton(vector<T>& a, int low, int high) {
    T pivot = a[high];
    int i = low - 1;

    for (int j = low;j < high;j++) {
        if (a[j] < pivot) {
            i ++;
            T q = a[j];
            a[j] = a[i];
            a[i] = q;
        }
    }
    T q = a[high];
    a[high] = a[i + 1];
    a[i + 1] = q;
    return i + 1;
}
template <typename T>
void quick_sort_range(vector<T>& a, int low, int high) {

    if (low < high){
        int p_ind = partiton(a, low, high);
        quick_sort_range(a, low, p_ind - 1);
        quick_sort_range(a, p_ind+1, high);
    }
    
}
template <typename T>
void quick_sort(vector<T>& a) {
    int n = static_cast<int>(a.size());
    quick_sort_range(a, 0, n-1 );
}

template void quick_sort<int>(vector<int>&);
template void quick_sort<double>(vector<double>&);