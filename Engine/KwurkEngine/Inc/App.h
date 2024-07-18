#pragma once

namespace KwurkEngine
{
	class App final
	{
	public:
		void Run();
		void Quit();

	private:
		bool mRunning = false;

	};
}



