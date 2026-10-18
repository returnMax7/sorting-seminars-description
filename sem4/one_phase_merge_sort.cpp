#include "one_phase_merge_sort.h"
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <limits>
#include <stdexcept>
#include <utility>
using namespace std;

namespace {
template <typename T>
size_t distribute(const string& source, const string& first, const string& second) {
    ifstream a(source);
    if (!a) throw runtime_error("Cannot open source file");
    ofstream b(first), c(second);
    if (!b || !c) throw runtime_error("Cannot create temporary files");
    b << setprecision(numeric_limits<T>::max_digits10);
    c << setprecision(numeric_limits<T>::max_digits10);
    T value;
    size_t count = 0;
    while (a >> value) {
        if (count % 2 == 0) b << value << '\n';
        else c << value << '\n';
        count++;
    }
    return count;
}

template <typename T>
void merge_pass(const string& first, const string& second,
                const string& third, const string& fourth, size_t k) {
    ifstream b(first), c(second);
    if (!b || !c) throw runtime_error("Cannot open temporary files");
    ofstream d(third), e(fourth);
    if (!d || !e) throw runtime_error("Cannot create output files");
    d << setprecision(numeric_limits<T>::max_digits10);
    e << setprecision(numeric_limits<T>::max_digits10);
    T x, y;
    bool has_x = static_cast<bool>(b >> x);
    bool has_y = static_cast<bool>(c >> y);
    bool to_first = true;
    while (has_x || has_y) {
        size_t i = 0, j = 0;
        ofstream& output = to_first ? d : e;
        while (has_x && has_y && i < k && j < k) {
            if (x <= y) {
                output << x << '\n';
                has_x = static_cast<bool>(b >> x);
                i++;
            } else {
                output << y << '\n';
                has_y = static_cast<bool>(c >> y);
                j++;
            }
        }
        while (has_x && i < k) {
            output << x << '\n';
            has_x = static_cast<bool>(b >> x);
            i++;
        }
        while (has_y && j < k) {
            output << y << '\n';
            has_y = static_cast<bool>(c >> y);
            j++;
        }
        to_first = !to_first;
    }
}
}

template <typename T>
void one_phase_merge_sort(const string& source) {
    string first = source + ".1.tmp", second = source + ".2.tmp";
    string third = source + ".3.tmp", fourth = source + ".4.tmp";
    size_t n = distribute<T>(source, first, second);
    size_t k = 1;
    while (k < n) {
        merge_pass<T>(first, second, third, fourth, k);
        swap(first, third);
        swap(second, fourth);
        if (k >= n - k) break;
        k *= 2;
    }
    {
        ifstream input(first);
        if (!input) throw runtime_error("Cannot open result");
        ofstream output(source);
        if (!output) throw runtime_error("Cannot write result");
        output << setprecision(numeric_limits<T>::max_digits10);
        T value;
        while (input >> value) output << value << '\n';
    }
    remove(first.c_str());
    remove(second.c_str());
    remove(third.c_str());
    remove(fourth.c_str());
}

template void one_phase_merge_sort<int>(const string&);
template void one_phase_merge_sort<double>(const string&);
