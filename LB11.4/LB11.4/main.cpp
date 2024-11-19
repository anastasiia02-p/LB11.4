#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <windows.h>

using namespace std;

// Функції
void DisplayMenu();
void AnalyzeFile(const string& filename, const string& result_filename);
bool IsNumber(const string& str);
void CountLineDetails(const string& line, int& positives, int& negatives, int& zeros, int& words);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string input_filename, output_filename;
    int choice;

    do {
        DisplayMenu();
        cout << "Введіть ваш вибір: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Введіть ім'я вхідного файлу: ";
            cin >> input_filename;
            cout << "Введіть ім'я файлу для запису результатів: ";
            cin >> output_filename;

            AnalyzeFile(input_filename, output_filename);
            break;
        }
        case 0:
            cout << "Вихід із програми." << endl;
            break;
        default:
            cout << "Невірний вибір! Спробуйте ще раз." << endl;
        }
    } while (choice != 0);

    return 0;
}

void DisplayMenu() {
    cout << "\n=== Меню ===\n";
    cout << "1. Аналізувати файл\n";
    cout << "0. Вийти\n";
    cout << "============\n";
}

bool IsNumber(const string& str) {
    if (str.empty()) return false;
    size_t i = 0;
    if (str[0] == '-' || str[0] == '+') i++;
    for (; i < str.size(); i++) {
        if (!isdigit(str[i])) return false;
    }
    return true;
}

void CountLineDetails(const string& line, int& positives, int& negatives, int& zeros, int& words) {
    positives = negatives = zeros = words = 0;

    istringstream stream(line);
    string word;

    while (stream >> word) {
        if (IsNumber(word)) {
            int num = stoi(word);
            if (num > 0) positives++;
            else if (num < 0) negatives++;
            else zeros++;
        }
        else {
            words++;
        }
    }
}

void AnalyzeFile(const string& filename, const string& result_filename) {
    ifstream infile(filename);
    ofstream outfile(result_filename);

    if (!infile.is_open()) {
        cout << "Не вдалося відкрити файл для читання!" << endl;
        return;
    }

    if (!outfile.is_open()) {
        cout << "Не вдалося відкрити файл для запису!" << endl;
        return;
    }

    string line;
    int line_number = 1;

    outfile << "Аналіз файлу: " << filename << endl;

    while (getline(infile, line)) {
        int positives, negatives, zeros, words;
        CountLineDetails(line, positives, negatives, zeros, words);

        outfile << "Рядок " << line_number++ << ":" << endl;
        outfile << " - Додатних чисел: " << positives << endl;
        outfile << " - Від'ємних чисел: " << negatives << endl;
        outfile << " - Нульових чисел: " << zeros << endl;
        outfile << " - Слів: " << words << endl;
        outfile << endl;
    }

    cout << "Аналіз завершено. Результати записано у файл: " << result_filename << endl;

    infile.close();
    outfile.close();
}
