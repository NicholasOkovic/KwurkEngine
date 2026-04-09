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
		mName = "Noname" + std::to_string(mId);
	}
	

	void SetName(const std::string& name)
	{
		mName = name;
	}

private:
	int mId = 0;
	std::string mName;

};

int WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{

	TypedAllocator studentPool = TypedAllocator<Student>("StudentPool", 100);

	std::vector<Student*> students;


}
