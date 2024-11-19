#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include "../LB11.4/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            ofstream infile("test_input.txt");
            infile << "10 -5 0 hello world\n";
            infile << "+15 -20\n";
            infile << "0 0 0 0\n";
            infile << "text only here\n";
            infile << "-1 -1 -1 3\n";
            infile.close();

            // Виклик функції аналізу
            AnalyzeFile("test_input.txt", "test_output.txt");

            // Перевірка результатів
            ifstream outfile("test_output.txt");
            Assert::IsTrue(outfile.is_open(), L"Не вдалося відкрити test_output.txt для читання");

            string line;

            // Перевірка результатів для кожного рядка
            getline(outfile, line);
            Assert::AreEqual(string("Аналіз файлу: test_input.txt"), line);

            getline(outfile, line);
            Assert::AreEqual(string("Рядок 1:"), line);
            getline(outfile, line);
            Assert::AreEqual(string(" - Додатних чисел: 1"), line);
            getline(outfile, line);
            Assert::AreEqual(string(" - Від'ємних чисел: 1"), line);
            getline(outfile, line);
            Assert::AreEqual(string(" - Нульових чисел: 1"), line);
            getline(outfile, line);
            Assert::AreEqual(string(" - Слів: 2"), line);

            getline(outfile, line);
            Assert::AreEqual(string(""), line);
            getline(outfile, line);
            Assert::AreEqual(string("Рядок 2:"), line);
            getline(outfile, line);
       
            

            // Аналогічні перевірки для інших рядків можна додати далі...

            outfile.close();
        
		}
	};
}
