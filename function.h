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
    ifstream inFile;
    inFile.open(fileName);
    if (!inFile)
    {
        cout << "File not found" << endl;
        return;
    }

    studentCount = 0; // Öğrenci sayısını sıfırla

    string fName, lName, cName, cCode;
    int sId, credits, numberOfCourses;
    char tempIsPaid; //? 'y' veya 'n' değerini tutacak
    char grade;

    while (inFile >> fName >> lName >> sId >> tempIsPaid >> numberOfCourses)
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

        for (int i = 0; i < numberOfCourses; ++i)
        {
            inFile >> cName >> cCode >> credits >> grade;

            CourseType newCourse(cName, cCode, credits, grade);
            students[studentCount].addNewCourse(i, newCourse);
        }

        studentCount++;
        inFile.ignore(); //! Alt satıra geç
    }

    inFile.close();
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
    for (int i = 0; i < numberOfCourses; ++i)
    {
        totalHours += courseEnrolled[i].getCourseCredits();
    }
    return totalHours;
}

int StudentType::billingAmount() //! Toplam ödenen harç parası (Ders Başı 345 TL)
{
    int totalAmount = 0;
    for (int i = 0; i < numberOfCourses; ++i)
    {
        totalAmount += courseEnrolled[i].getCourseCredits() * 345;
    }
    return totalAmount;
}
bool StudentType::getIsTuitionPaid() //! Harç ödendi mi
{
    return isTuitionPaid;
}

int StudentType::getGpa() //! Not ortalaması
{
    int totalCredits = 0;
    int totalPoints = 0;
    for (int i = 0; i < numberOfCourses; ++i)
    {
        totalCredits += courseEnrolled[i].getCourseCredits();
        totalPoints += courseEnrolled[i].getCourseCredits() * courseEnrolled[i].getCourseGrade();
    }
    return totalPoints / totalCredits;
}

void StudentType::print() //! Tüm öğrencileri yazdır
{
    cout << left; //? Soldan hizalama
    cout << "First Name:       " << setw(20) << firstName << endl;
    cout << "Last Name:        " << setw(20) << lastName << endl;
    cout << "Student ID:       " << setw(20) << studentId << endl;
    cout << "Tuition Paid:     " << setw(20) << (isTuitionPaid ? "Yes" : "No") << endl;
    cout << "Number of Courses:" << setw(20) << numberOfCourses << endl;

    //? Ders bilgilerini yazdırma
    cout << "Courses Enrolled:" << endl;
    for (int i = 0; i < numberOfCourses; ++i)
    {
        cout << "  Course Name:    " << setw(20) << courseEnrolled[i].getCourseName() << endl;
        cout << "  Course Code:    " << setw(20) << courseEnrolled[i].getCourseCode() << endl;
        cout << "  Course Grade:   " << setw(20) << courseEnrolled[i].getCourseGrade() << endl;
        cout << "  Course Credits: " << setw(20) << courseEnrolled[i].getCourseCredits() << endl;
        cout << "---------------------------" << endl;
    }
    cout << endl; //! Diğer öğrenciye geçmeden önce bir satır boşluk bırak
}

void StudentType::print(int arg) //! Yalnızca istuitionpaid yes olanları yazdır
{
    if (isTuitionPaid)
    {
        cout << left; //? Soldan hizalama
        cout << "First Name:       " << setw(20) << firstName << endl;
        cout << "Last Name:        " << setw(20) << lastName << endl;
        cout << "Student ID:       " << setw(20) << studentId << endl;
        cout << "Tuition Paid:     " << setw(20) << (isTuitionPaid ? "Yes" : "No") << endl;
        cout << "Number of Courses:" << setw(20) << numberOfCourses << endl;

        //? Ders bilgilerini yazdırma
        cout << "Courses Enrolled:" << endl;
        for (int i = 0; i < numberOfCourses; ++i)
        {
            cout << "  Course Name:    " << setw(20) << courseEnrolled[i].getCourseName() << endl;
            cout << "  Course Code:    " << setw(20) << courseEnrolled[i].getCourseCode() << endl;
            cout << "  Course Grade:   " << setw(20) << courseEnrolled[i].getCourseGrade() << endl;
            cout << "  Course Credits: " << setw(20) << courseEnrolled[i].getCourseCredits() << endl;
            cout << "---------------------------" << endl;
        }
        cout << endl; //! Diğer öğrenciye geçmeden önce bir satır boşluk bırak
    }
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
    return courseGrade;
}

int CourseType::getCourseCredits() const
{
    return courseCredits;
}
