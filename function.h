#include "class.h"
#include <iostream>
#include <fstream>
#include <string>
#include <istream>
#include <iomanip>
using namespace std;

// TODO => ÖĞRENCİ İLE İLGİLİ FONKSİYONLAR

void StudentType::readFromTxt(StudentType students[], int &studentCount, const string &fileName)
{
    ifstream file(fileName);
    if (!file)
    {
        cout << "File not found" << endl;
        return;
    }

    studentCount = 0; // Öğrenci sayısını sıfırla

    string fName, lName, cName, cCode;
    int sId, credits, numberOfCourses;
    char tempIsPaid; //? 'y' veya 'n' değerini tutacak
    char grade;

    while (file >> fName >> lName >> sId >> tempIsPaid >> numberOfCourses)
    {
        bool isPaid;

        //? 'y' veya 'n' değerini kontrol edip bool türüne dönüştür
        if (tempIsPaid == 'y' || tempIsPaid == 'Y')
            isPaid = true;
        else if (tempIsPaid == 'n' || tempIsPaid == 'N')
            isPaid = false;
        else
        {
            cerr << "Invalid tuition paid status for student " << fName << " " << lName << ". Skipping student.\n";
            continue; //! Geçersiz veri varsa öğrenciyi atla
        }

        students[studentCount].setStudentInfo(fName, lName, sId, isPaid, numberOfCourses);

        for (int i = 0; i < numberOfCourses; i++)
        {
            file >> cName >> cCode >> credits >> grade;

            CourseType newCourse(cName, cCode, credits, grade);
            students[studentCount].addNewCourse(i, newCourse);
        }

        studentCount++;
        //! STUDENT COUNT & İŞARETİ İLE ÇAĞIRILDIĞI İÇİN MAİN İÇERİSİNDE BURADAKİ SON DEĞER ALINIR
        file.ignore(); //! Alt satıra geç
    }

    file.close();
}

void StudentType::setStudentInfo(string fName, string lName, int sId, bool isPaid, int noOfCourses)
{
    firstName = fName;
    lastName = lName;
    studentId = sId;
    isTuitionPaid = isPaid;
    numberOfCourses = noOfCourses;
}

void StudentType::addNewCourse(int index, const CourseType &course)
{
    if (index < MAX_COURSES)
    {
        courseEnrolled[index] = course;
    }
}

int StudentType::getHoursEnrolled() //! Toplam kaç saat kredi aldığı
{
    int totalHours = 0;
    for (int i = 0; i < numberOfCourses; i++)
    {
        totalHours += courseEnrolled[i].getCourseCredits();
    }
    return totalHours;
}

int StudentType::billingAmount() //! Toplam ödenen harç parası (Ders Başı 345 TL)
{
    int totalAmount = 0;
    for (int i = 0; i < numberOfCourses; i++)
    {
        totalAmount += courseEnrolled[i].getCourseCredits() * 300;
    }
    return totalAmount;
}
bool StudentType::getIsTuitionPaid() //! Harç ödendi mi
{
    return isTuitionPaid;
}

float StudentType::getCourseGradeAsNumber(char grade)
{
    switch (grade)
    {
    case 'A':
        return 4.0;
    case 'B':
        return 3.0;
    case 'C':
        return 2.0;
    case 'D':
        return 1.0;
    case 'F':
        return 0.0;
    default:
        return 0.0; // Geçersiz not durumunda.
    }
}

float StudentType::getGpa() //! Not ortalaması
{
    float totalCredits = 0;
    float totalPoints = 0;

    for (int i = 0; i < numberOfCourses; i++)
    {
        char grade = courseEnrolled[i].getCourseGrade();  // Char olarak alınan not.
        float gradeValue = getCourseGradeAsNumber(grade); // Sayısal karşılık.
        float credits = courseEnrolled[i].getCourseCredits();

        totalCredits += credits;
        totalPoints += gradeValue * credits;
    }

    return totalPoints / totalCredits;
}

void StudentType::print(int arg) //! terminale yazdırma
{
    if (arg == 0) //! Tüm öğrencileri yazdırma
    {
        cout << left; //? Soldan hizalama

        cout << "First Name:       " << setw(20) << firstName << endl;
        cout << "Last Name:        " << setw(20) << lastName << endl;
        cout << "Student ID:       " << setw(20) << studentId << endl;
        cout << "Tuition Paid:     " << setw(20) << (isTuitionPaid ? "Y" : "N") << endl;
        cout << "Number of Courses:" << setw(20) << numberOfCourses << endl;

        //? Ders bilgilerini yazdırma

        if (getIsTuitionPaid())
        {
            cout << "GPA:              " << setw(20) << fixed << setprecision(2) << getGpa() << endl;
            cout << "Courses Enrolled:" << endl;

            for (int i = 0; i < numberOfCourses; i++)
            {
                cout << "  Course Name:    " << setw(20) << courseEnrolled[i].getCourseName() << endl;
                cout << "  Course Code:    " << setw(20) << courseEnrolled[i].getCourseCode() << endl;
                cout << "  Course Grade:   " << setw(20) << courseEnrolled[i].getCourseGrade() << endl;
                cout << "  Course Credits: " << setw(20) << courseEnrolled[i].getCourseCredits() << endl;
                cout << "---------------------------" << endl;
            }
            cout << "-----------------------------------------------------------------------------------" << endl;
        }
        else
        {
            cout << "Student didn't pay the tuition and that's why we can't show informations of courses" << endl;
            cout << "-----------------------------------------------------------------------------------" << endl;
        }
        cout << endl; //! Diğer öğrenciye geçmeden önce bir satır boşluk bırak
    }
    if (arg == 1 && isTuitionPaid) //? Harç ödemiş öğrencileri yazdırma
    {
        cout << left; //? Soldan hizalama
        cout << "First Name:       " << setw(20) << firstName << endl;
        cout << "Last Name:        " << setw(20) << lastName << endl;
        cout << "Student ID:       " << setw(20) << studentId << endl;
        cout << "Tuition Paid:     " << setw(20) << (isTuitionPaid ? "Y" : "N") << endl;
        cout << "Number of Courses:" << setw(20) << numberOfCourses << endl;
        cout << "GPA:              " << setw(20) << fixed << setprecision(2) << getGpa() << endl;

        //? Ders bilgilerini yazdırma
        cout << "Courses Enrolled:" << endl;
        for (int i = 0; i < numberOfCourses; i++)
        {
            cout << "  Course Name:    " << setw(20) << courseEnrolled[i].getCourseName() << endl;
            cout << "  Course Code:    " << setw(20) << courseEnrolled[i].getCourseCode() << endl;
            cout << "  Course Grade:   " << setw(20) << courseEnrolled[i].getCourseGrade() << endl;
            cout << "  Course Credits: " << setw(20) << courseEnrolled[i].getCourseCredits() << endl;
            cout << "---------------------------" << endl;
        }
        cout << "-----------------------------------------------------------------------------------" << endl;
        cout << endl; //! Diğer öğrenciye geçmeden önce bir satır boşluk bırak
    }

    if (arg == 2 && !isTuitionPaid) //! Harç ödememiş öğrencileri yazdırma
    {
        cout << left; //? Soldan hizalama
        cout << "First Name:       " << setw(20) << firstName << endl;
        cout << "Last Name:        " << setw(20) << lastName << endl;
        cout << "Student ID:       " << setw(20) << studentId << endl;
        cout << "Tuition Paid:     " << setw(20) << (isTuitionPaid ? "Y" : "N") << endl;
        cout << "Number of Courses:" << setw(20) << numberOfCourses << endl;

        //? Ders bilgilerini yazdırma
        cout << "Student didn't pay the tuition and that's why we can't show informations of courses" << endl;
        cout << "-----------------------------------------------------------------------------------" << endl;
    }
}

void StudentType::print(int arg, const string &outputFileName)
{
    ofstream file(outputFileName, ios::app);
    //! TÜM ÖĞRENCİLERİ PAKETLER HALİNCE BİR ARRAYİN İNDEXLERİ ŞEKLİNDE ALDIĞIMIZ VE AYNI DOSYAYA YAZMAMIZ İÇİN  İOS::APP KULLANMAMIZ GEREKTİ

    //! EĞER KULLANMASAAYDIK HER BİR STUDENT İNDEXİ İÇİN DOSYAYI TEKRAR TEKRAR OKUYACAĞI İÇİN ::TRUNC GİBİ YAZILAN VERİLERİ ÜSTÜNE YAZMA İŞLEMİ OLACKATI VE EN SON HALİNDE SADECE SON VERİ YAZILACAKTI
    if (arg == 0)
    {
        file << left; //? Soldan hizalama
        file << "First Name:       " << setw(20) << firstName << endl;
        file << "Last Name:        " << setw(20) << lastName << endl;
        file << "Student ID:       " << setw(20) << studentId << endl;
        file << "Tuition Paid:     " << setw(20) << (isTuitionPaid ? "Y" : "N") << endl;
        file << "Number of Courses:" << setw(20) << numberOfCourses << endl;

        //? Ders bilgilerini yazdırma
        if (isTuitionPaid)
        {
            file << "GPA               " << setw(20) << fixed << setprecision(2) << getGpa() << endl;
            file << "Courses Enrolled:" << endl;

            for (int i = 0; i < numberOfCourses; i++)
            {
                file << "  Course Name:    " << setw(20) << courseEnrolled[i].getCourseName() << endl;
                file << "  Course Code:    " << setw(20) << courseEnrolled[i].getCourseCode() << endl;
                file << "  Course Grade:   " << setw(20) << courseEnrolled[i].getCourseGrade() << endl;
                file << "  Course Credits: " << setw(20) << courseEnrolled[i].getCourseCredits() << endl;
                file << "---------------------------" << endl;
            }
            file << "-----------------------------------------------------------------------------------" << endl;
        }
        if (!isTuitionPaid)
        {
            file << "Student didn't pay the tuition and that's why we can't show informations of courses" << endl;
            file << "-----------------------------------------------------------------------------------" << endl;
        }

        file << endl; //! Diğer öğrenciye geçmeden önce bir satır boşluk bırak
    }
    if (arg == 1 && isTuitionPaid)
    {
        file << left; //? Soldan hizalama
        file << "First Name:       " << setw(20) << firstName << endl;
        file << "Last Name:        " << setw(20) << lastName << endl;
        file << "Student ID:       " << setw(20) << studentId << endl;
        file << "Tuition Paid:     " << setw(20) << (isTuitionPaid ? "Y" : "N") << endl;
        file << "Number of Courses:" << setw(20) << numberOfCourses << endl;
        file << "GPA:              " << setw(20) << fixed << setprecision(2) << getGpa() << endl;

        file
            << "Courses Enrolled:" << endl;
        for (int i = 0; i < numberOfCourses; i++)
        {
            file << "  Course Name:    " << setw(20) << courseEnrolled[i].getCourseName() << endl;
            file << "  Course Code:    " << setw(20) << courseEnrolled[i].getCourseCode() << endl;
            file << "  Course Grade:   " << setw(20) << courseEnrolled[i].getCourseGrade() << endl;
            file << "  Course Credits: " << setw(20) << courseEnrolled[i].getCourseCredits() << endl;
            file << "---------------------------" << endl;
        }
        file << "-----------------------------------------------------------------------------------" << endl;

        file << endl; //! Diğer öğrenciye geçmeden önce bir satır boşluk bırak
    }
    if (arg == 2 && !isTuitionPaid)
    {
        file << left; //? Soldan hizalama
        file << "First Name:       " << setw(20) << firstName << endl;
        file << "Last Name:        " << setw(20) << lastName << endl;
        file << "Student ID:       " << setw(20) << studentId << endl;
        file << "Tuition Paid:     " << setw(20) << (isTuitionPaid ? "Y" : "N") << endl;
        file << "Number of Courses:" << setw(20) << numberOfCourses << endl;

        file << "Student didn't pay the tuition and that's why we can't show informations of courses" << endl;
        file << "-----------------------------------------------------------------------------------" << endl;

        file << endl; //! Diğer öğrenciye geçmeden önce bir satır boşluk bırak
    }
    file.close();
}

// TODO => KURS İLE İLGİLİ FONKSİYONLAR

void CourseType::setCourseInfo(string cName, string cNo, char grade, int credits)
{
    courseName = cName;
    courseCode = cNo;
    courseGrade = grade;
    courseCredits = credits;
}

string CourseType::getCourseName() const
{
    return courseName;
}
string CourseType::getCourseCode() const
{
    return courseCode;
}

char CourseType::getCourseGrade() const
{
    return courseCredits;
}

int CourseType::getCourseCredits() const
{
    return courseGrade;
}
