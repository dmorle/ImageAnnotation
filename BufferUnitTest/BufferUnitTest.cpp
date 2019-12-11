#include "pch.h"
#include "CppUnitTest.h"
#include "fstream"
#include "../imageAnnotation/WidgetComponents/WidgetCmp.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BufferUnitTest
{
	void createMockFiles(std::string target, std::string suffix, UINT n)
	{
		for (int i = 0; i < n; i++) {
			std::ofstream outfile("test" + i + suffix);
			outfile.close();
		}
	}

	class stringBuffer : Buffer<std::string>
	{
	public:
		stringBuffer(std::string target, std::string suffix, USHORT bufferSize)
			: Buffer(target, suffix, bufferSize) {}

	protected:
		std::string* loadElem(std::wstring*)
		{
			return new std::string("");
		}
	};

	TEST_CLASS(BufferUnitTest)
	{
	public:
		
		TEST_METHOD(TestBufferInit)
		{
			std::string testTarget = "./testTarget/";
			std::string testSuffix = "";
			USHORT testSize = 5;

			createMockFiles(testTarget, ".txt", 20);
		}
	};
}
