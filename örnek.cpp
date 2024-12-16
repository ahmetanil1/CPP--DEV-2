#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Öğrenci bilgilerini tutacak yapı
struct Student
{
    string name;
    int student_id;
    char gender;
    int age;
    string courses[10];   // Ders adı ve kodlarını tutacak dizi (max 10 ders)
    int course_count = 0; // Ders sayısı
};

int main()
{
    ifstream file("input.txt"); // Dosya adı
    string line;
    Student students[50];  // Öğrencileri tutacak dizi (max 50 öğrenci)
    int student_count = 0; // Öğrenci sayısı

    if (file.is_open())
    {
        while (getline(file, line))
        {
            stringstream ss(line);
            string name, gender, course_name, course_code, grade;
            int student_id, age, credits;

            // İlk satırda öğrenci bilgilerini al
            if (line.find(" ") != string::npos)
            {
                ss >> name >> student_id >> gender >> age;
                Student student;
                student.name = name;
                student.student_id = student_id;
                student.gender = gender[0]; // İlk karakteri al
                student.age = age;

                // Öğrencinin derslerini oku
                while (getline(file, line) && !line.empty())
                {
                    stringstream course_stream(line);
                    course_stream >> course_name >> course_code >> credits >> grade;
                    student.courses[student.course_count++] = course_name + " " + course_code; // Ders adı ve kodunu ekle
                }

                students[student_count++] = student; // Öğrenciyi ekle
            }
        }
        file.close();

        // Okunan verileri yazdır
        for (int i = 0; i < student_count; ++i)
        {
            cout << "Student: " << students[i].name << ", ID: " << students[i].student_id
                 << ", Gender: " << students[i].gender << ", Age: " << students[i].age << endl;
            for (int j = 0; j < students[i].course_count; ++j)
            {
                cout << "Course: " << students[i].courses[j] << endl;
            }
            cout << "--------------------------" << endl;
        }
    }
    else
    {
        cout << "Dosya açılamadı!" << endl;
    }

    return 0;
}
