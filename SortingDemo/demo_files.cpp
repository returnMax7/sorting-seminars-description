#include "two_phase_merge_sort.h"
#include "one_phase_merge_sort.h"
#include "natural_merge_sort.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>
#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif
using namespace std;

void show_file(const filesystem::path& path) {
    ifstream input(path);
    if (!input) throw runtime_error("Не удалось прочитать файл");
    cout << path.string() << "\n";
    int value;
    while (input >> value) cout << value << ' ';
    cout << "\n\n";
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    try {
        cout << "Демонстрация внешних сортировок\n"
             << "1 — двухфазное слияние\n"
             << "2 — однофазное слияние\n"
             << "3 — естественное слияние\n"
             << "Выберите алгоритм: ";
        int choice;
        if (!(cin >> choice) || choice < 1 || choice > 3) {
            cerr << "Нужно выбрать 1, 2 или 3.\n";
            return 1;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        filesystem::path directory = filesystem::absolute("demo_files");
        filesystem::create_directories(directory);
        filesystem::path source = directory / "input.txt";
        filesystem::path original = directory / "before.txt";

   
        if (!filesystem::exists(source)) {
            ofstream output(source);
            if (!output) throw runtime_error("Не удалось создать input.txt");
            output << "13 9 4 16 1 11 5 20\n";
        }
        cout << "\nФайл с числами:\n" << source.string() << "\n"
             << "Сохраните файл и нажмите Enter для сортировки.\n";
        cin.get();
        filesystem::copy_file(source, original, filesystem::copy_options::overwrite_existing);
        cout << "\nДО сортировки:\n";
        show_file(original);

        string filename = source.string();
        if (choice == 1) two_phase_merge_sort<int>(filename);
        else if (choice == 2) one_phase_merge_sort<int>(filename);
        else natural_merge_sort<int>(filename);

        cout << "ПОСЛЕ сортировки:\n";
        show_file(source);
        cout << "before.txt — исходные числа, input.txt — результат.\n"
             << "Временные файлы алгоритм удалил после завершения.\n"
             << "Для следующего примера измените input.txt перед запуском сортировки.\n";
        return 0;
    } catch (const exception& error) {
        cerr << "Ошибка: " << error.what() << '\n';
        return 1;
    }
}

