#include "pch.h"
#include "CppUnitTest.h"
#include "fstream"
#include "../imageAnnotation/WidgetComponents/Buffer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BufferUnitTest
{
	void deleteMockFiles(std::string target)
	{
		auto dir = WCMP::fs::directory_iterator(target);
		for (auto& entry : dir)
			remove(entry.path());
	}

	void createMockFiles(std::string target, std::string suffix, UINT n)
	{
		for (int i = 0; i < n; i++) {
			std::ofstream outfile(target + "test" + std::to_string(i) + suffix);
			outfile << i;
			outfile.close();
		}
	}

	class stringBuffer : public WCMP::Buffer<std::string>
	{
	public:
		stringBuffer(std::string target, std::string suffix, USHORT bufferSize)
			: Buffer(target, suffix, bufferSize, &loadTextFile, &copyString) {}

	private:
		static std::string* loadTextFile(std::wstring* path)
		{
			static int i = 0;
			return new std::string(std::to_string(i++));
		}

		static std::string* copyString(std::string* pStr)
		{
			return new std::string(*pStr);
		}
	};

	TEST_CLASS(BufferUnitTest)
	{
	public:
		
		TEST_METHOD(StandardInit)
		{
			std::string testTarget = "C:/testTarget/";
			std::string testSuffix = "";
			USHORT testSize = 5;

			deleteMockFiles(testTarget);
			createMockFiles(testTarget, ".txt", 20);

			stringBuffer test = stringBuffer(testTarget, testSuffix, testSize);
		}

		TEST_METHOD(SmallTargetInit)
		{
			std::string testTarget = "C:/testTarget/";
			std::string testSuffix = "";
			USHORT testSize = 20;

			deleteMockFiles(testTarget);
			createMockFiles(testTarget, ".txt", 10);

			stringBuffer test = stringBuffer(testTarget, testSuffix, testSize);
		}

		TEST_METHOD(Iteration)
		{
			std::string testTarget = "C:/testTarget/";
			std::string testSuffix = "";
			USHORT testSize = 2;

			deleteMockFiles(testTarget);
			createMockFiles(testTarget, ".txt", 25);

			stringBuffer test = stringBuffer(testTarget, testSuffix, testSize);

			for (int i = 0; i < 10; i++)
				test.next();
		}

		TEST_METHOD(MaxIteration)
		{
			std::string testTarget = "C:/testTarget/";
			std::string testSuffix = "";
			USHORT testSize = 2;

			deleteMockFiles(testTarget);
			createMockFiles(testTarget, ".txt", 10);

			stringBuffer test = stringBuffer(testTarget, testSuffix, testSize);

			for (int i = 0; i < 25; i++)
				test.next();
		}

	};
}
