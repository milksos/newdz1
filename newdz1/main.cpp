// main.cpp
#include <iostream>
#include <locale>
#include "TDMassive.h"

// Функция для проверки условий и вывода результата
void assertEqual(bool condition, const std::string& message, int& totalTests, int& passedTests) {
    totalTests++;
    if (condition) {
        std::cout << "[ПРОЙДЕНО] " << message << "\n";
        passedTests++;
    }
    else {
        std::cout << "[НЕ ПРОЙДЕНО] " << message << "\n";
    }
}

void runTests() {
    int totalTests = 0;
    int passedTests = 0;

    // Тест базового конструктора и добавления элементов
    {
        TDMassive<int> massive;
        assertEqual(massive.empty(), "Массив должен быть пуст в начале", totalTests, passedTests);

        massive.push_back(10);
        assertEqual(massive.size() == 1, "Размер должен быть равен 1 после добавления одного элемента", totalTests, passedTests);
        assertEqual(!massive.empty(), "Массив не должен быть пуст после добавления элемента", totalTests, passedTests);
        assertEqual(massive[0] == 10, "Первый элемент должен быть равен 10", totalTests, passedTests);

        massive.push_back(20);
        assertEqual(massive.size() == 2, "Размер должен быть равен 2 после добавления второго элемента", totalTests, passedTests);
        assertEqual(massive[1] == 20, "Второй элемент должен быть равен 20", totalTests, passedTests);
    }

    // Тест на увеличение вместимости
    {
        TDMassive<int> massive(2);
        massive.push_back(1);
        massive.push_back(2);

        assertEqual(massive.full(), "Массив должен быть полон", totalTests, passedTests);

        massive.push_back(3); // Увеличиваем вместимость и добавляем элемент
        assertEqual(!massive.full(), "Массив не должен быть полон после увеличения вместимости", totalTests, passedTests);
        assertEqual(massive.size() == 3, "Размер должен быть равен 3 после добавления третьего элемента", totalTests, passedTests);
        assertEqual(massive[2] == 3, "Третий элемент должен быть равен 3", totalTests, passedTests);
    }

    // Тест метода clear
    {
        TDMassive<int> massive;
        massive.push_back(10);
        massive.push_back(20);

        massive.clear();
        assertEqual(massive.empty(), "Массив должен быть пуст после очистки", totalTests, passedTests);
        assertEqual(massive.size() == 0, "Размер должен быть равен 0 после очистки", totalTests, passedTests);

        massive.push_back(30);
        assertEqual(massive.size() == 1, "Массив должен позволять добавлять элементы после очистки", totalTests, passedTests);
    }

    // Тест метода replace
    {
        TDMassive<int> massive;
        massive.push_back(10);
        massive.push_back(20);

        massive.replace(1, 99);
        assertEqual(massive[1] == 99, "Элемент должен быть заменен на 99", totalTests, passedTests);
    }

    // Тест на перепаковку массива
    {
        TDMassive<int> massive;
        massive.push_back(10);
        massive.push_back(20);
        massive.push_back(30);

        massive.remove_by_index(1); // Удаляем элемент с индексом 1
        massive.repacking(); // Выполняем перепаковку
        assertEqual(massive.size() == 2, "Размер должен быть равен 2 после перепаковки", totalTests, passedTests);
        assertEqual(massive[1] == 30, "Второй элемент должен быть равен 30 после перепаковки", totalTests, passedTests);
    }

    // Тест метода find_first
    {
        TDMassive<int> massive;
        massive.push_back(10);
        massive.push_back(20);
        massive.push_back(10);

        size_t index = massive.find_first(10);
        assertEqual(index == 0, "Первый элемент со значением 10 должен быть на индексе 0", totalTests, passedTests);
    }

    // Тест метода find_last
    {
        TDMassive<int> massive;
        massive.push_back(10);
        massive.push_back(20);
        massive.push_back(10);

        size_t index = massive.find_last(10);
        assertEqual(index == 2, "Последний элемент со значением 10 должен быть на индексе 2", totalTests, passedTests);
    }

    // Итоговый результат тестов
    std::cout << "\nИтого тестов: " << totalTests << "\n";
    std::cout << "Пройдено тестов: " << passedTests << "\n";
    std::cout << "Не пройдено тестов: " << (totalTests - passedTests) << "\n";
}

int main() {
    // Устанавливаем локаль для поддержки русского языка
    std::locale::global(std::locale("Russian"));
    // Также меняем кодировку консоли на UTF-8, чтобы отображались русские символы корректно
    system("chcp 65001 > nul");

    // Проверка работы локали
    std::cout << "Проверка отображения русского текста.\n";

    runTests();
    return 0;
}
