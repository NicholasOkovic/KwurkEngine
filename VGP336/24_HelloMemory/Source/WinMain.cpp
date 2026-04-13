#include <KwurkEngine/Inc/KwurkEngine.h>

using namespace kwurkEngine;
using namespace kwurkEngine::Core;

static int sUniqueId = 0;

class Student
{
public:
	Student()
	{
		mId = ++sUniqueId;
		mMark = 60 + (rand() % 41);
		mName = "Noname" + std::to_string(mId);
	}
	Student()///////////////////////////////////
	{
		mId = ++sUniqueId;
		mMark = 60 + (rand() % 41);
		mName = "Noname" + std::to_string(mId);
	}
	Student()
	{
		mId = ++sUniqueId;
		mMark = 60 + (rand() % 41);
		mName = "Noname" + std::to_string(mId);
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
	int mId = 0;
	int mMark = 0;
	std::string mName;

};

int WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{

	TypedAllocator studentPool = TypedAllocator<Student>("StudentPool", 100);


	std::vector<Student*> students;

	//test new
	for (uint32_t i = 0; i < 50; i++)
	{
		std::string newStudentName = "NewStudent" + std::to_string(i);
		Student* newStudent = studentPool.New(newStudentName, 75);
		newStudent->Log();
		students.push_back(newStudent);
	}

	//test deleete
	for (uint32_t i = 0; i < 20; i++)
	{
		Student* student = students.back();
		studentPool.Delete(students.back());
		students.pop_back();
	}
	// test add more
	for (uint32_t i = 0; i < 20; i++)
	{
		Student* newStudent = studentPool.New();
		newStudent->Log();
		students.push_back(newStudent);
	}

	//clean up
	for (Student* student : students)
	{
		student->Log();
		studentPool.Delete(student);
	}
	students.clear();

}
