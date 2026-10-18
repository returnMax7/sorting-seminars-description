#include "natural_merge_sort.h"
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <limits>
#include <stdexcept>
using namespace std;

namespace {
// Одна строка временного файла хранит одну естественную серию.
template <typename T>
size_t distribute(const string& source, const string& first, const string& second) {
    ifstream a(source);
    if (!a) throw runtime_error("Cannot open source file");
    ofstream b(first), c(second);
    if (!b || !c) throw runtime_error("Cannot create temporary files");
    b << setprecision(numeric_limits<T>::max_digits10);
    c << setprecision(numeric_limits<T>::max_digits10);
    T previous;
    if (!(a >> previous)) return 0;
    bool to_first = true;
    size_t runs = 1;
    b << previous << ' ';
    T value;
    while (a >> value) {
        if (value < previous) {
            if (to_first) b << '\n';
            else c << '\n';
            to_first = !to_first;
            runs++;
        }
        if (to_first) b << value << ' ';
        else c << value << ' ';
        previous = value;
    }
    if (to_first) b << '\n';
    else c << '\n';
    return runs;
}

template <typename T>
bool read_from_run(ifstream& file, T& value) {
    while (file.peek() == ' ' || file.peek() == '\t' || file.peek() == '\r') {
        file.get();
    }
    if (file.peek() == '\n') {
        file.get();
        return false;
    }
    return static_cast<bool>(file >> value);
}

template <typename T>
void merge_files(const string& source, const string& first, const string& second) {
    ifstream b(first), c(second);
    if (!b || !c) throw runtime_error("Cannot open temporary files");
    ofstream a(source);
    if (!a) throw runtime_error("Cannot write result");
    a << setprecision(numeric_limits<T>::max_digits10);
    while (b.peek() != char_traits<char>::eof() || c.peek() != char_traits<char>::eof()) {
        T x, y;
        bool has_x = read_from_run(b, x);
        bool has_y = read_from_run(c, y);
        while (has_x && has_y) {
            if (x <= y) {
                a << x << '\n';
                has_x = read_from_run(b, x);
            } else {
                a << y << '\n';
                has_y = read_from_run(c, y);
            }
        }
        while (has_x) {
            a << x << '\n';
            has_x = read_from_run(b, x);
        }
        while (has_y) {
            a << y << '\n';
            has_y = read_from_run(c, y);
        }
    }
}
}

template <typename T>
void natural_merge_sort(const string& source) {
    string first = source + ".natural.left.tmp";
    string second = source + ".natural.right.tmp";
    while (true) {
        size_t runs = distribute<T>(source, first, second);
        if (runs <= 1) break;
        merge_files<T>(source, first, second);
    }
    remove(first.c_str());
    remove(second.c_str());
}

template void natural_merge_sort<int>(const string&);
template void natural_merge_sort<double>(const string&);
