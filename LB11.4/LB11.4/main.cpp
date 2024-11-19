#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <windows.h>

using namespace std;

// �������
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
        cout << "������ ��� ����: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "������ ��'� �������� �����: ";
            cin >> input_filename;
            cout << "������ ��'� ����� ��� ������ ����������: ";
            cin >> output_filename;

            AnalyzeFile(input_filename, output_filename);
            break;
        }
        case 0:
            cout << "����� �� ��������." << endl;
            break;
        default:
            cout << "������� ����! ��������� �� ���." << endl;
        }
    } while (choice != 0);

    return 0;
}

void DisplayMenu() {
    cout << "\n=== ���� ===\n";
    cout << "1. ���������� ����\n";
    cout << "0. �����\n";
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
        cout << "�� ������� ������� ���� ��� �������!" << endl;
        return;
    }

    if (!outfile.is_open()) {
        cout << "�� ������� ������� ���� ��� ������!" << endl;
        return;
    }

    string line;
    int line_number = 1;

    outfile << "����� �����: " << filename << endl;

    while (getline(infile, line)) {
        int positives, negatives, zeros, words;
        CountLineDetails(line, positives, negatives, zeros, words);

        outfile << "����� " << line_number++ << ":" << endl;
        outfile << " - �������� �����: " << positives << endl;
        outfile << " - ³�'����� �����: " << negatives << endl;
        outfile << " - �������� �����: " << zeros << endl;
        outfile << " - ���: " << words << endl;
        outfile << endl;
    }

    cout << "����� ���������. ���������� �������� � ����: " << result_filename << endl;

    infile.close();
    outfile.close();
}
