#include <iostream>
#include "Class.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

studentType::studentType() // constructor
{
    sID = 0;
    numberOfCourses = 0;
    isTuitionPaid = 'N';
    coursesEnrolled = [];
}
void studentType::readFromTxt(const string &fileName)
{
    ifstream file(fileName);
    string line;
    studentType students[30];
    int student_count = 0;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            stringstream ss(line);
            string firstName, lastName, coursesEnrolled;
            int sID, numberOfCourses;
            char isTuitionPaid;

            if (line.find(" ") != string::npos)
            {
                ss >> firstName >> lastName >> sID >> isTuitionPaid >> numberOfCourses;
                studentType student;
                student.firstName = firstName;
                student.lastName = lastName;
                student.sID = sID;
                student.isTuitionPaid = isTuitionPaid;
                student.numberOfCourses = numberOfCourses;

                while (getline(file, line) && !line.empty())
                {
                    stringstream course_stream(line);
                    course_stream >> courseName >> courseNumber >> courseCredits >> courseGrade;
                    student.coursesEnrolled[student.course_count++] = courseName + " " + courseNumber " " + courseCredits + " " + courseGrade;
                }

                students[student_count++] = student;
            }
        }
        file.close();

        for (int i = 0; i < student_count; ++i)
        {
            cout << "Student: " << students[i].firstName << " " << students[i].lastName << ", ID: " << students[i].sID << ", Tuition Paid: " << students[i].isTuitionPaid << ", Number of Courses: " << students[i].numberOfCourses << endl;
            for (int j = 0; j < students[i].numberOfCourses; ++j)
            {
                cout << "Course: " << students[i].coursesEnrolled[j] << endl;
            }
            cout << "--------------------------" << endl;
        }
    }
    else
    {
        cout << "File could not be opened." << endl;
    }
}
void studentType::print()
{
}
void studentType::print(int arg)
{
}
void studentType::print(int arg, const string &outputFileName)
{
}
void studentType::setName()
{
}
void studentType::getName()
{
}
void studentType::setInfo()
{
}
void studentType::getHoursEnrolled()
{
}
void studentType::getGpa()
{
}
void studentType::billingAmount()
{
}
studentType::~studentType() // destructor
{
}

courseType::courseType(string = "", string = "", char = '*', int = 0) // constructor
{
    courseName = "";
    courseNumber = "";
    courseGrade = '*';
    courseCredits = 0;
}
void courseType::setCourseInfo()
{
}
void courseType::print(/*1 parameter*/)
{
}
void courseType::print(/*2 parameter*/)
{
}
void courseType::getCredits()
{
}
void courseType::getCourseNumber()
{
}
void courseType::getGrade()
{
}
courseType::~courseType() // destructor
{
}