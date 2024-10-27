// main.cpp
#include <iostream>
#include <locale>
#include "TDMassive.h"

// ������� ��� �������� ������� � ������ ����������
void assertEqual(bool condition, const std::string& message, int& totalTests, int& passedTests) {
    totalTests++;
    if (condition) {
        std::cout << "[��������] " << message << "\n";
        passedTests++;
    }
    else {
        std::cout << "[�� ��������] " << message << "\n";
    }
}

void runTests() {
    int totalTests = 0;
    int passedTests = 0;

    // ���� �������� ������������ � ���������� ���������
    {
        TDMassive<int> massive;
        assertEqual(massive.empty(), "������ ������ ���� ���� � ������", totalTests, passedTests);

        massive.push_back(10);
        assertEqual(massive.size() == 1, "������ ������ ���� ����� 1 ����� ���������� ������ ��������", totalTests, passedTests);
        assertEqual(!massive.empty(), "������ �� ������ ���� ���� ����� ���������� ��������", totalTests, passedTests);
        assertEqual(massive[0] == 10, "������ ������� ������ ���� ����� 10", totalTests, passedTests);

        massive.push_back(20);
        assertEqual(massive.size() == 2, "������ ������ ���� ����� 2 ����� ���������� ������� ��������", totalTests, passedTests);
        assertEqual(massive[1] == 20, "������ ������� ������ ���� ����� 20", totalTests, passedTests);
    }

    // ���� �� ���������� �����������
    {
        TDMassive<int> massive(2);
        massive.push_back(1);
        massive.push_back(2);

        assertEqual(massive.full(), "������ ������ ���� �����", totalTests, passedTests);

        massive.push_back(3); // ����������� ����������� � ��������� �������
        assertEqual(!massive.full(), "������ �� ������ ���� ����� ����� ���������� �����������", totalTests, passedTests);
        assertEqual(massive.size() == 3, "������ ������ ���� ����� 3 ����� ���������� �������� ��������", totalTests, passedTests);
        assertEqual(massive[2] == 3, "������ ������� ������ ���� ����� 3", totalTests, passedTests);
    }

    // ���� ������ clear
    {
        TDMassive<int> massive;
        massive.push_back(10);
        massive.push_back(20);

        massive.clear();
        assertEqual(massive.empty(), "������ ������ ���� ���� ����� �������", totalTests, passedTests);
        assertEqual(massive.size() == 0, "������ ������ ���� ����� 0 ����� �������", totalTests, passedTests);

        massive.push_back(30);
        assertEqual(massive.size() == 1, "������ ������ ��������� ��������� �������� ����� �������", totalTests, passedTests);
    }

    // ���� ������ replace
    {
        TDMassive<int> massive;
        massive.push_back(10);
        massive.push_back(20);

        massive.replace(1, 99);
        assertEqual(massive[1] == 99, "������� ������ ���� ������� �� 99", totalTests, passedTests);
    }

    // ���� �� ����������� �������
    {
        TDMassive<int> massive;
        massive.push_back(10);
        massive.push_back(20);
        massive.push_back(30);

        massive.remove_by_index(1); // ������� ������� � �������� 1
        massive.repacking(); // ��������� �����������
        assertEqual(massive.size() == 2, "������ ������ ���� ����� 2 ����� �����������", totalTests, passedTests);
        assertEqual(massive[1] == 30, "������ ������� ������ ���� ����� 30 ����� �����������", totalTests, passedTests);
    }

    // ���� ������ find_first
    {
        TDMassive<int> massive;
        massive.push_back(10);
        massive.push_back(20);
        massive.push_back(10);

        size_t index = massive.find_first(10);
        assertEqual(index == 0, "������ ������� �� ��������� 10 ������ ���� �� ������� 0", totalTests, passedTests);
    }

    // ���� ������ find_last
    {
        TDMassive<int> massive;
        massive.push_back(10);
        massive.push_back(20);
        massive.push_back(10);

        size_t index = massive.find_last(10);
        assertEqual(index == 2, "��������� ������� �� ��������� 10 ������ ���� �� ������� 2", totalTests, passedTests);
    }

    // �������� ��������� ������
    std::cout << "\n����� ������: " << totalTests << "\n";
    std::cout << "�������� ������: " << passedTests << "\n";
    std::cout << "�� �������� ������: " << (totalTests - passedTests) << "\n";
}

int main() {
    // ������������� ������ ��� ��������� �������� �����
    std::locale::global(std::locale("Russian"));
    // ����� ������ ��������� ������� �� UTF-8, ����� ������������ ������� ������� ���������
    system("chcp 65001 > nul");

    // �������� ������ ������
    std::cout << "�������� ����������� �������� ������.\n";

    runTests();
    return 0;
}
