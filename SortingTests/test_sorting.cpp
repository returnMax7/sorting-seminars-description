#include "quick_sort.h"
#include "shell_sort.h"
#include "two_phase_merge_sort.h"
#include "one_phase_merge_sort.h"
#include "natural_merge_sort.h"
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <limits>
#include <chrono>
#include <stdexcept>
#include <catch2/catch_test_macros.hpp>
#include "insertion_sort.h"
#include "selection_sort.h"
#include "exchange_sort.h"
#include "bubble_sort.h"
#include "optimized_bubble_sort.h"
#include "shaker_sort.h"
#include "binary_insertion_sort.h"
#include <algorithm>
#include <random>
#include <vector>
#include <catch2/catch_session.hpp>
using namespace std;

int main(int argc, char* argv[]) {
    return Catch::Session().run(argc, argv);
}
#define BOUNDARY_TESTS_MACRO(x) \
    TEST_CASE("Boundary: " #x, "[sorting][boundary]") { \
        vector<int> empty_int; \
        x(empty_int); \
        REQUIRE(empty_int.empty()); \
        vector<double> empty_double; \
        x(empty_double); \
        REQUIRE(empty_double.empty()); \
        vector<int> single_int = {7}; \
        x(single_int); \
        REQUIRE(single_int == vector<int>{7}); \
        vector<double> single_double = {7.5}; \
        x(single_double); \
        REQUIRE(single_double == vector<double>{7.5}); \
    }

#define BASE_TESTS_MACRO(x) \
    TEST_CASE("Base: " #x, "[sorting][base]") { \
        vector<int> expected = {1, 2, 3, 4}; \
        vector<int> sorted = expected; \
        x(sorted); \
        REQUIRE(sorted == expected); \
        vector<int> reversed = {4, 3, 2, 1}; \
        x(reversed); \
        REQUIRE(reversed == expected); \
        vector<double> expected_double = {-1.5, 0.0, 2.5, 4.5}; \
        vector<double> sorted_double = expected_double; \
        x(sorted_double); \
        REQUIRE(sorted_double == expected_double); \
        vector<double> reversed_double = {4.5, 2.5, 0.0, -1.5}; \
        x(reversed_double); \
        REQUIRE(reversed_double == expected_double); \
    }

#define DUPLICATE_TESTS_MACRO(x) \
    TEST_CASE("Duplicates: " #x, "[sorting][duplicates]") { \
        vector<int> a = {3, -2, 3, 0, -2}; \
        vector<int> expected = {-2, -2, 0, 3, 3}; \
        x(a); \
        REQUIRE(a == expected); \
        vector<double> b = {2.5, -1.5, 2.5, 0.0}; \
        vector<double> expected_double = {-1.5, 0.0, 2.5, 2.5}; \
        x(b); \
        REQUIRE(b == expected_double); \
    }

#define INDIVIDUAL_TESTS_MACRO(x) \
    TEST_CASE("Individual variant 15: " #x, "[sorting][individual]") { \
        vector<int> a = {13, 9, 4, 16, 1, 11, 5, 20}; \
        vector<int> expected = {1, 4, 5, 9, 11, 13, 16, 20}; \
        x(a); \
        REQUIRE(a == expected); \
        vector<double> b = {13, 9, 4, 16, 1, 11, 5, 20}; \
        vector<double> expected_double = {1, 4, 5, 9, 11, 13, 16, 20}; \
        x(b); \
        REQUIRE(b == expected_double); \
    }

#define RANDOM_TESTS_MACRO(x) \
    TEST_CASE("Random: " #x, "[sorting][random]") { \
        mt19937 gen(15); \
        uniform_int_distribution<int> dist(-100, 100); \
        for (int size = 1; size <= 100; size++) { \
            CAPTURE(size); \
            vector<int> a; \
            vector<double> b; \
            for (int i = 0; i < size; i++) { \
                a.push_back(dist(gen)); \
                b.push_back(dist(gen) / 4.0); \
            } \
            auto expected = a; \
            auto expected_double = b; \
            sort(expected.begin(), expected.end()); \
            sort(expected_double.begin(), expected_double.end()); \
            x(a); \
            x(b); \
            REQUIRE(a == expected); \
            REQUIRE(b == expected_double); \
        } \
    }

#define ALL_SORT_TESTS(x) \
    BOUNDARY_TESTS_MACRO(x) \
    BASE_TESTS_MACRO(x) \
    DUPLICATE_TESTS_MACRO(x) \
    INDIVIDUAL_TESTS_MACRO(x) \
    RANDOM_TESTS_MACRO(x)

ALL_SORT_TESTS(insertion_sort)
ALL_SORT_TESTS(selection_sort)
ALL_SORT_TESTS(exchange_sort)
ALL_SORT_TESTS(bubble_sort)
ALL_SORT_TESTS(optimized_bubble_sort)
ALL_SORT_TESTS(shaker_sort)
ALL_SORT_TESTS(binary_insertion_sort)



ALL_SORT_TESTS(quick_sort)
ALL_SORT_TESTS(shell_sort)

namespace {
struct TestFiles {
    filesystem::path directory;

    TestFiles() {
        auto stamp = chrono::steady_clock::now().time_since_epoch().count();
        for (int attempt = 0; attempt < 1000; attempt++) {
            auto candidate = filesystem::temp_directory_path() /
                ("sorting_tests_" + to_string(stamp) + "_" + to_string(attempt));
            if (filesystem::create_directory(candidate)) {
                directory = candidate;
                return;
            }
        }
        throw runtime_error("Cannot create test directory");
    }

    ~TestFiles() {
        error_code error;
        filesystem::remove_all(directory, error);
    }
};
}

#define FILE_SORT_ADAPTER(x) \
    template <typename T> \
    void x##_vector(vector<T>& a) { \
        TestFiles files; \
        string source = (files.directory / "input.txt").string(); \
        { \
            ofstream output(source); \
            REQUIRE(output.is_open()); \
            output << setprecision(numeric_limits<T>::max_digits10); \
            for (const T& value : a) output << value << '\n'; \
            output.close(); \
            REQUIRE(static_cast<bool>(output)); \
        } \
        x<T>(source); \
        vector<T> result; \
        { \
            ifstream input(source); \
            REQUIRE(input.is_open()); \
            T value; \
            while (input >> value) result.push_back(value); \
            REQUIRE(input.eof()); \
        } \
        a = result; \
        size_t remaining_files = 0; \
        for (const auto& entry : filesystem::directory_iterator(files.directory)) { \
            (void)entry; \
            remaining_files++; \
        } \
        REQUIRE(remaining_files == 1); \
    }

FILE_SORT_ADAPTER(two_phase_merge_sort)
FILE_SORT_ADAPTER(one_phase_merge_sort)
FILE_SORT_ADAPTER(natural_merge_sort)

ALL_SORT_TESTS(two_phase_merge_sort_vector)
ALL_SORT_TESTS(one_phase_merge_sort_vector)
ALL_SORT_TESTS(natural_merge_sort_vector)

#define MERGE_TESTS_MACRO(x) \
    TEST_CASE("Merge runs: " #x, "[sorting][external][merge]") { \
        vector<vector<int>> inputs = { \
            {2, 1}, {3, 1, 2}, {5, 4, 3, 2, 1}, \
            {2, 5, 8, 1, 4, 7, 3, 6}, \
            {1, 2, 3, 4, 5, -1, 0}, \
            {1, 1, 2, 0, 0, 2, -1}, {4, 4, 4, 4, 4} \
        }; \
        for (auto input : inputs) { \
            CAPTURE(input); \
            auto expected = input; \
            sort(expected.begin(), expected.end()); \
            x##_vector(input); \
            REQUIRE(input == expected); \
        } \
        vector<double> precise = {1.2345678901234567, -0.12345678901234567, 1e-100, 1e100, 0.0}; \
        auto expected = precise; \
        sort(expected.begin(), expected.end()); \
        x##_vector(precise); \
        REQUIRE(precise == expected); \
    } \
    TEST_CASE("File whitespace: " #x, "[sorting][external][file]") { \
        TestFiles files; \
        string source = (files.directory / "input.txt").string(); \
        { \
            ofstream output(source); \
            REQUIRE(output.is_open()); \
            output << "  13\t9\n4 16\n1\t11 5 20  \n"; \
        } \
        x<int>(source); \
        ifstream input(source); \
        REQUIRE(input.is_open()); \
        vector<int> result; \
        int value; \
        while (input >> value) result.push_back(value); \
        REQUIRE(input.eof()); \
        vector<int> expected = {1, 4, 5, 9, 11, 13, 16, 20}; \
        REQUIRE(result == expected); \
    } \
    TEST_CASE("Missing source: " #x, "[sorting][external][errors]") { \
        TestFiles files; \
        string source = (files.directory / "missing.txt").string(); \
        REQUIRE_THROWS_AS(x<int>(source), runtime_error); \
        REQUIRE_FALSE(filesystem::exists(source)); \
    }

MERGE_TESTS_MACRO(two_phase_merge_sort)
MERGE_TESTS_MACRO(one_phase_merge_sort)
MERGE_TESTS_MACRO(natural_merge_sort)
