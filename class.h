#include <iostream>
using namespace std;

class personType
{
protected:
    string firstName;
    string lastName;
}

class studentType : protected personType
{
private:
    int sID;
    int numberOfCourses;
    char isTuitionPaid = "N";
    string coursesEnrolled[5];

public:
    studentType();
    ~studentType();
    void readFromTxt(const string &fileName);
    void print();
    void print(int arg);
    void print(int arg, const string &outputFileName);
    void setName();
    void getName();
    void setInfo();
    void getHoursEnrolled();
    void getGpa();
    void billingAmount();
}

class courseType
{
public:
    courseType(string = "", string = "", char = '*', int = 0);
    ~courseType();
    void setCourseInfo();
    void print(/*1 parameter*/);
    void print(/*2 parameter*/);
    void getCredits();
    void getCourseNumber();
    void getGrade();

private:
    string courseName;
    string courseNumber;
    char courseGrade;
    int courseCredits;
};