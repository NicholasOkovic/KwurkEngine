#include <KwurkEngine/Inc/KwurkEngine.h>

using namespace KwurkEngine;
using namespace KwurkEngine::Core;

static int studentUniqueId = 0;
static int schoolUniqueId = 0;
static int teacherUniqueId = 0;

class Student
{
public:
	Student()
	{
		mId = ++studentUniqueId;
		mMark = 60 + (rand() % 41);
		mName = "Noname_" + std::to_string(mId);
	}
	Student(const std::string& name)
		: mName(name)
	{
		mId = ++studentUniqueId;
		mMark = 60 + (rand() % 41);
	}
	Student(const std::string& name, int mark)
		: mName(name)
		, mMark(mark)

	{
		mId = ++studentUniqueId;
	}
	
	void Log()
	{
		LOG("Name: %s -ID: %d - Mark: %d", mName.c_str(), mId, mMark);
	}

	void SetName(const std::string& name)
	{
		mName = name;
	}

private:
	int mMark = 0;
	std::string mName;
	int mId = 0;

};
class School
{
public:
	School()
	{
		mId = ++schoolUniqueId;
		mName = "Noname_" + std::to_string(mId);
	}

	void Log()
	{
		LOG("Name: %s -ID: %d", mName.c_str(), mId);
	}

	void SetName(const std::string& name)
	{
		mName = name;
	}

private:
	int mId = 0;
	std::string mName;

};
class Teacher
{
public:
	Teacher()
	{
		mId = ++teacherUniqueId;
		mName = "Noname_" + std::to_string(mId);
		mYearsTaught = 0 + (rand() % 20);
	}
	Teacher(const std::string& name)
		: mName(name)
	{
		mId = ++teacherUniqueId;
		mYearsTaught = 0 + (rand() % 20);
	}
	Teacher(const std::string& name, int yearsTaught)
		: mName(name)
		, mYearsTaught(yearsTaught)

	{
		mId = ++teacherUniqueId;
	}

	void Log()
	{
		LOG("Name: %s -ID: %d -Years Taught: %d", mName.c_str(), mId, mYearsTaught);
	}

	void SetName(const std::string& name)
	{
		mName = name;
	}

private:
	int mId = 0;
	std::string mName;
	int mYearsTaught = 0;

};

int WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{

	TypedAllocator studentPool = TypedAllocator<Student>("StudentPool", 100);
	TypedAllocator schoolPool = TypedAllocator<School>("SchoolPool", 70);
	TypedAllocator teacherPool = TypedAllocator<Teacher>("TeacherPool", 70);

	std::vector<Student*> students;
	std::vector<School*> schools;
	std::vector<Teacher*> teachers;



	//add 70
	for (uint32_t i = 0; i < 70; i++)
	{
		std::string newStudentName = "Student" + std::to_string(i+1);
		Student* newStudent = studentPool.New(newStudentName, 75);
		newStudent->Log();
		students.push_back(newStudent);

		School* newSchool = schoolPool.New();
		newSchool->Log();
		schools.push_back(newSchool);

		std::string newTeacherName = "Teacher" + std::to_string(i+1);
		Teacher* newTeacher = teacherPool.New(newTeacherName);
		newTeacher->Log();
		teachers.push_back(newTeacher);
	}

	//delete 40
	for (uint32_t i = 0; i < 40; i++)
	{
		Student* student = students.back();
		studentPool.Delete(students.back());
		students.pop_back();

		School* school = schools.back();
		schoolPool.Delete(schools.back());
		schools.pop_back();

		Teacher* teacher = teachers.back();
		teacherPool.Delete(teachers.back());
		teachers.pop_back();
	}

	// add up to capacity
	for (uint32_t i = 0; i < 100; i++)
	{
		std::string newStudentName = "Student" + std::to_string(i + 1);
		Student* newStudent = studentPool.New();
		if (newStudent == nullptr)
		{
			break;
		}
		newStudent->Log();
		students.push_back(newStudent);
	}

	for (uint32_t i = 0; i < 70; i++)
	{
		School* newSchool = schoolPool.New();
		if (newSchool == nullptr)
		{
			break;
		}
		newSchool->Log();
		schools.push_back(newSchool);
	}

	for (uint32_t i = 0; i < 70; i++)
	{
		std::string newTeacherName = "Teacher" + std::to_string(i + 1);
		Teacher* newTeacher = teacherPool.New(newTeacherName);
		if (newTeacher == nullptr)
		{
			break;
		}
		newTeacher->Log();
		teachers.push_back(newTeacher);
	}


	//clean up
	for (Student* student : students)
	{
		student->Log();
		studentPool.Delete(student);
	}
	students.clear();

	for (School* school : schools)
	{
		school->Log();
		schoolPool.Delete(school);
	}
	schools.clear();

	for (Teacher* teacher : teachers)
	{
		teacher->Log();
		teacherPool.Delete(teacher);
	}
	teachers.clear();

}
