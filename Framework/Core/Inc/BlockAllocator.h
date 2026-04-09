#pragma once


namespace KwurkEngine::Core
{
	class BlockAllocator
	{
	public:
		BlockAllocator(const char* name, size_t blockSize, size_t capacity);
		virtual ~BlockAllocator();

		BlockAllocator(const BlockAllocator&) = delete;
		BlockAllocator(const BlockAllocator&&) = delete;
		BlockAllocator& operator=(const BlockAllocator&) = delete;
		BlockAllocator&& operator=(const BlockAllocator&&) = delete;

		void* Allocate();
		void Free(void* ptr);

	
	private:
		std::string mName;
		std::vector<void*>

	};

	
}