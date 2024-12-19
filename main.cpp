#include "function.h"
#include <cstdio>
#include <windows.h>
#include <fstream>
#include <iostream>

using namespace std;

void writeToFileAndPrint(StudentType students[], int studentCount, int choice, const string &fileName)
{
    // Dosyayı temizle
    ofstream clearFile(fileName, ios::trunc);
    clearFile.close();

    // Öğrencileri terminale yazdır
    for (int i = 0; i < studentCount; ++i)
    {
        students[i].print(choice);
    }

    // Öğrencileri dosyaya yazdır
    for (int i = 0; i < studentCount; ++i)
    {
        students[i].print(choice, fileName);
    }
}

int main()
{
    SetConsoleOutputCP(65001); // Türkçe karakterleri destekler

    StudentType students[MAX_STUDENTS];
    int studentCount = 0;

    // Öğrencileri dosyadan oku
    for (int i = 0; i < MAX_STUDENTS; i++)
    {
        students[i].readFromTxt(students, studentCount, "input.txt");
    }

    while (true)
    {
        cout << "0. Print all students\n";
        cout << "1. Print students who paid for tuition\n";
        cout << "2. Print students who did not pay for tuition\n";

        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cout << "Kayıtlı Öğrenci sayısı: " << studentCount;
        cout << "       Ders saati başına ödenmesi gereken ücret: " << "300" << endl;
        string fileName = "output.txt";

        switch (choice)
        {
        case 0:
            // Tüm öğrencileri yazdır ve dosyaya yaz
            writeToFileAndPrint(students, studentCount, choice, fileName);
            break;

        case 1:
            // Harç ödemiş öğrencileri yazdır ve dosyaya yaz
            writeToFileAndPrint(students, studentCount, choice, fileName);
            break;

        case 2:
            // Harç ödemeyen öğrencileri yazdır ve dosyaya yaz
            writeToFileAndPrint(students, studentCount, choice, fileName);
            break;

        case 3:
            // Çıkış yap
            return 0;

        default:
            cout << "Invalid choice\n";
            break;
        }
    }

    return 0;
}
