#include "pch.h"
#include "CppUnitTest.h"
#include "fstream"
#include "../imageAnnotation/WidgetComponents/Buffer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BufferUnitTest
{
	void deleteMockFiles(std::string target)
	{
		auto dir = fs::directory_iterator(target);
		for (auto& entry : dir)
			remove(entry.path());
	}

	void createMockFiles(std::string target, std::string suffix, UINT n)
	{
		for (int i = 0; i < n; i++) {
			std::ofstream outfile(target + "test" + std::to_string(i) + suffix);
			outfile.close();
		}
	}

	class stringBuffer : Buffer<std::string>
	{
	public:
		stringBuffer(std::string target, std::string suffix, USHORT bufferSize)
			: Buffer(target, suffix, bufferSize, &loadTextFile) {}

	private:
		static std::string* loadTextFile(std::wstring* path)
		{
			return new std::string("");
		}
	};

	TEST_CLASS(BufferUnitTest)
	{
	public:
		
		TEST_METHOD(TestInitStandard)
		{
			std::string testTarget = "C:/testTarget/";
			std::string testSuffix = "";
			USHORT testSize = 5;

			deleteMockFiles(testTarget);
			createMockFiles(testTarget, ".txt", 20);

			stringBuffer test = stringBuffer(testTarget, testSuffix, testSize);

			return;
		}

		TEST_METHOD(TestInitSmallTarget)
		{
			std::string testTarget = "C:/testTarget/";
			std::string testSuffix = "";
			USHORT testSize = 20;

			deleteMockFiles(testTarget);
			createMockFiles(testTarget, ".txt", 10);

			stringBuffer test = stringBuffer(testTarget, testSuffix, testSize);

			return;
		}


	};
}
