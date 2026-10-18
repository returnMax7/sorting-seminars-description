#include "two_phase_merge_sort.h"

#include <cstdio>
#include <fstream>
#include <iomanip>
#include <limits>
#include <stdexcept>

using namespace std;
namespace {

template <typename T>
size_t distribute(const string& source,
    const string& first,
    const string& second,
    size_t k) {
    ifstream a(source);

    if (!a) {
        throw runtime_error("Не удалось открыть основной файл");
    }

    ofstream b(first);
    ofstream c(second);

    if (!b || !c) {
        throw runtime_error("Не удалось создать временные файлы");
    }

    b << setprecision(numeric_limits<T>::max_digits10);
    c << setprecision(numeric_limits<T>::max_digits10);

    T value;
    size_t count = 0;

    while (a >> value) {
        if ((count / k) % 2 == 0) {
            b << value << '\n';
        }
        else {
            c << value << '\n';
        }

        count++;
    }

    return count;
}

template <typename T>
void merge_files(const string& source,
    const string& first,
    const string& second,
    size_t k) {
    ifstream b(first);
    ifstream c(second);

    if (!b || !c) {
        throw runtime_error("Не удалось открыть временные файлы");
    }

    ofstream a(source);

    if (!a) {
        throw runtime_error("Не удалось открыть файл для записи");
    }

    a << setprecision(numeric_limits<T>::max_digits10);

    T x, y;
    bool has_x = false;
    if (b >> x) {
        has_x = true;
    }
    bool has_y = false;
    if (c >> y) {
        has_y = true;
    }
    while (has_x || has_y) {
        size_t i = 0;//для б
        size_t j = 0;// для с

        while (has_x && has_y && i < k && j < k) {
            if (x <= y) {
                a << x << '\n';
                has_x = static_cast<bool>(b >> x);
                i++;
            }
            else {
                a << y << '\n';
                has_y = static_cast<bool>(c >> y);
                j++;
            }
        }

        while (has_x && i < k) {
            a << x << '\n';
            has_x = static_cast<bool>(b >> x);
            i++;
        }

        while (has_y && j < k) {
            a << y << '\n';
            has_y = static_cast<bool>(c >> y);
            j++;
        }
    }

}

} 

template <typename T>
void two_phase_merge_sort(const string & source) {
        string first = source + ".left.tmp";
        string second = source + ".right.tmp";

        size_t k = 1;

        while (true) {
            size_t n = distribute<T>(source, first, second, k);

            if (n <= k) {
                break;
            }

            merge_files<T>(source, first, second, k);

            if (k >= n - k) {
                break;
            }

            k *= 2;
        }

        remove(first.c_str());
        remove(second.c_str());
    }

template void two_phase_merge_sort<int>(const string&);
template void two_phase_merge_sort<double>(const string&);
