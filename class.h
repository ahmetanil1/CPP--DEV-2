#include <iostream>
using namespace std;

const int MAX_COURSES = 10;
const int MAX_STUDENTS = 30;

class PersonType
{
protected:
    string firstName;
    string lastName;

public:
    PersonType(string fName = "", string lName = "")
    {
        firstName = fName;
        lastName = lName;
    }

    string getFirstName() const
    {
        return firstName;
    }
    string getLastName() const
    {
        return lastName;
    }
};

class CourseType
{
private:
    string courseName;
    string courseCode;
    char courseGrade;
    int courseCredits;

public:
    CourseType(string cName, string cCode, char grade, int credits)
    {
        courseName = cName;
        courseCode = cCode;
        courseGrade = grade;
        courseCredits = credits;
    }
    CourseType()
        : courseName(""), courseCode(""), courseGrade('F'), courseCredits(0) {}
    void setCourseInfo(string cName, string cNo, char grade, int credits);
    string getCourseName() const;
    string getCourseCode() const;
    char getCourseGrade() const;
    int getCourseCredits() const;
    void print(int arg);
    void print(int arg, const string &outputFileName);
};

class StudentType : protected PersonType
{
private:
    CourseType courseEnrolled[MAX_COURSES];
    int studentId;
    int numberOfCourses;
    bool isTuitionPaid = false;

public:
    // Parametreli constructor
    StudentType(string fName, string lName, int sId, bool isPaid, int noOfCourses)
        : PersonType(fName, lName), studentId(sId), numberOfCourses(noOfCourses), isTuitionPaid(isPaid)
    {
        // Bu satırı kaldırdık, çünkü zaten initializer listesi ile başlatılıyor
        // PersonType(fName, lName);
        // studentId = sId;
        // isTuitionPaid = isPaid;
        // numberOfCourses = noOfCourses;
    }

    // Varsayılan constructor
    StudentType() //! LAST VE FİRST NAME EKSİK
        : studentId(0), numberOfCourses(0), isTuitionPaid(false)
    {
    }

    void setStudentInfo(string fName, string lName, int sId, bool isPaid, int noOfCourses);
    void addNewCourse(int index, const CourseType &course);
    void readFromTxt(StudentType students[], int &studentCount, const string &fileName);
    int getHoursEnrolled();
    int billingAmount();
    bool getIsTuitionPaid();
    float getGpa();
    void print(int arg);
    void print(int arg, const string &outputFileName);
    float getCourseGradeAsNumber(char grade);
};
