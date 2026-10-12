#include "pch.h"
#include "CppUnitTest.h"
#include "../lab_1_8/Set.h"
#include "../lab_1_8/Set.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Set::BitString bs;
			bs.Init(0, 1);
			Set::BitString shifted = bs.ShiftLeft(33);
			Assert::AreEqual(2UL, shifted.GetHigh());
			Assert::AreEqual(0UL, shifted.GetLow());
		}
	};
}
