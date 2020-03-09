#include "pch.h"
#include "CppUnitTest.h"
#include "../intersect/line.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:	
		TEST_METHOD(TestMethod1)
		{
			Line* line = new Line();
			Line* line2 = new Line();
			line->SetLine(1, 1, 2, 2);
			line2->SetLine(3, 4, 5, 7);
			Assert::AreEqual(line->isParallel(*line2), false);
		}
		TEST_METHOD(TestMethod2)
		{
			Line* line = new Line();
			Line* line2 = new Line();
			line->SetLine(1, 1, 2, 2);
			line2->SetLine(-3, -3, -4, -4);
			Assert::AreEqual(line->isParallel(*line2), true);
		}
		TEST_METHOD(TestMethod3)
		{
			Line* line = new Line();
			line->SetLine(1, 1, 98807, 54);
			double x_x = (double)98807 - 1;
			double y_y = (double)54 - 1;
			Assert::AreEqual(line->getSlope(), y_y / x_x);
		}
		TEST_METHOD(TestMethod4)
		{
			Line* line = new Line();
			line->SetLine(1, 1, 1, 54);
			Assert::AreEqual(line->getSlope(), MAXSLOPE);
		}
		TEST_METHOD(TestMethod5)
		{
			Line* line = new Line();
			line->SetLine(1, 54, 2, 54);
			Assert::AreEqual(line->getSlope(), 0.0);
		}
		TEST_METHOD(TestMethod6)
		{
			Line* line = new Line();
			Line* line2 = new Line();
			line->SetLine(1, 4, -1, 7);
			line2->SetLine(2, 4, -1, 7);
			pair<double, double> point;
			point.first = (double)(-1);
			point.second = (double)(7);
			Assert::AreEqual(line->getInterSect(*line2).first,point.first);
			Assert::AreEqual(line->getInterSect(*line2).second, point.second);
		}
		TEST_METHOD(TestMethod7)
		{
			Line* line = new Line();
			Line* line2 = new Line();
			line->SetLine(3, 4, -5, 8);
			line2->SetLine(7, 2, -3, 9);
			pair<double, double> point;
			point.first = (double)(7);
			point.second = (double)(2);
			Assert::AreEqual(line->isParallel(*line2), false);
			Assert::AreEqual(line->getInterSect(*line2).first, point.first);
			Assert::AreEqual(line->getInterSect(*line2).second, point.second);
		}
		TEST_METHOD(TestMethod8)
		{
			Line* line = new Line();
			Line* line2 = new Line();
			line->SetLine(-99999, 99999, -7, 7);
			line2->SetLine(99999, -99999, 7, -7);
			Assert::AreEqual(line->getSlope(), double(-1));
			Assert::AreEqual(line2->getSlope(), double(-1));
			Assert::AreEqual(line->isParallel(*line2), true);
		}
		TEST_METHOD(TestMethod9)
		{
			Line* line = new Line();
			line->SetLine(-2, 1, 3, 2);
			Assert::AreEqual(line->getFunc(), string("1x+-5y+7=0"));
		}
		TEST_METHOD(TestMethod10)
		{
			Line* line = new Line();
			Line* line2 = new Line();
			line->SetLine(-350,100,-250,200);
			line2->SetLine(-200, 100, -140, 200);
			pair<double, double> point;
			point.first = (double)(25);
			point.second = (double)(475);
			Assert::AreEqual(line->isParallel(*line2), false);
			Assert::AreEqual(line->getInterSect(*line2).first, point.first);
			Assert::AreEqual(line->getInterSect(*line2).second, point.second);
		}
		TEST_METHOD(TestMethod11)
		{
			Line* line = new Line();
			Line* line2 = new Line();
			line->SetLine(-2,2,3,7);
			line2->SetLine(5,8,10,9);
			pair<double, double> point;
			point.first = (double)(15)/4;
			point.second = (double)(31)/4;
			Assert::AreEqual(line->isParallel(*line2), false);
			Assert::AreEqual(line->getInterSect(*line2).first, point.first);
			Assert::AreEqual(line->getInterSect(*line2).second, point.second);
		}
	};
}
