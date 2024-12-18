#include "function.h"

int main()
{
    StudentType students[MAX_STUDENTS];
    int studentCount = 0;

    for (int i = 0; i < MAX_STUDENTS; i++)
    {
        students[i].readFromTxt(students, studentCount, "input.txt");
    }

    while (1)
    {
        cout << "1. Print all students\n";
        cout << "2.Print students who are paid for tuition\n";
        cout << "3. Print all students to file\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 1)
        {
            for (int i = 0; i < studentCount; ++i)
            {
                students[i].print();
            }
        }
        else if (choice == 2)
        {
            for (int i = 0; i < studentCount; ++i)
            {
                if (students[i].getIsTuitionPaid())
                {
                    students[i].print(1);
                }
            }
        }
        else if (choice == 3)
        {
            string fileName;
            cout << "Enter file name: ";
            cin >> fileName;

            for (int i = 0; i < studentCount; ++i)
            {
                students[i].print(1, fileName);
            }
        }
        else if (choice == 4)
        {
            break;
        }
        else
        {
            cout << "Invalid choice\n";
        }
    }

    return 0;
}