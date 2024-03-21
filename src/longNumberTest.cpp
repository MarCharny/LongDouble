#include "googletest/googletest/include/gtest/gtest.h"
#include "LongNumber/include/LongNumber.hpp"


void Equal(const std::vector<int>& real, const std::vector<int>& required) {
	ASSERT_EQ(real.size(), required.size());
	for (size_t i = 0; i < real.size(); ++i) {
		ASSERT_EQ(real[i], required[i]);
	}
}

TEST(LongNumberDouble, DefaultConstructor) {
	LongNumberDouble x;
	ASSERT_EQ(x.GetExponent(), 1);
	Equal(x.GetDigits(), { 0 });
}


TEST(LongNumberDouble, IsNegative) {
	LongNumberDouble x;
	ASSERT_EQ(x.GetIsNegative(), false);

	x.SetIsNegative(true);

	ASSERT_EQ(x.GetIsNegative(), true);
}

TEST(LongNumberDouble, DivDigits) {
	LongNumberDouble x;
	ASSERT_EQ(x.GetIsNegative(), false);

	x.SetIsNegative(true);

	ASSERT_EQ(x.GetIsNegative(), true);
}

TEST(LongNumberDouble, Exponent) {
	LongNumberDouble x;
	ASSERT_EQ(x.GetExponent(), 1);

	x.SetExponent(5);

	ASSERT_EQ(x.GetExponent(), 5);
}

TEST(LongNumberDouble, Digits) {
	LongNumberDouble x;
	
	Equal(x.GetDigits(), { 0 });

	const vector<int> tst = { 1,2,3 };

	x.SetDigits(tst);

	ASSERT_EQ(x.GetDigits(), tst);
}


TEST(LongNumberDouble, CopyConstructor) {

	const vector<int> tst = { 1,2,3 };

	LongNumberDouble src;
	src.SetExponent(5);
	src.SetIsNegative(true);
	src.SetDivDigits(110);
	src.SetDigits(tst);

	LongNumberDouble x(src);

	ASSERT_EQ(x.GetExponent(), 5);
	ASSERT_EQ(x.GetIsNegative(), true);
	ASSERT_EQ(x.GetDivDigits(), 110);
	Equal(x.GetDigits(), tst);
}

TEST(LongNumberDouble, ConstCharConstructor) {

	LongNumberDouble x("123.55");

	ASSERT_EQ(x.GetExponent(), 3);
	ASSERT_EQ(x.GetIsNegative(), false);
	Equal(x.GetDigits(), {1,2,3,5,5});

	LongNumberDouble y("0.4343");

	ASSERT_EQ(y.GetExponent(), 1);
}

TEST(LongNumberDouble, StringConstructor) {

	const string s = "123.55";
	LongNumberDouble x(s);

	ASSERT_EQ(x.GetExponent(), 3);
	ASSERT_EQ(x.GetIsNegative(), false);
	Equal(x.GetDigits(), { 1,2,3,5,5 });
}

TEST(LongNumberDouble, ToString) {

	LongNumberDouble x("123.55");

	ASSERT_EQ(x.ToStr(), "123.55");
}

TEST(LongNumberDouble, opEquality) {

	LongNumberDouble src("123.55");
	LongNumberDouble x = src;

	ASSERT_EQ(x.GetExponent(), 3);
	ASSERT_EQ(x.GetIsNegative(), false);
	Equal(x.GetDigits(), { 1,2,3,5,5 });
}

TEST(LongNumberDouble, opUnaryNegative) {

	LongNumberDouble x("123.55");
	ASSERT_EQ(x.GetIsNegative(), false);

	x = -x;

	ASSERT_EQ(x.GetIsNegative(), true);
}

TEST(LongNumberDouble, opCompare) {

	LongNumberDouble x("123.55");
	LongNumberDouble y("123.55");

	ASSERT_EQ(x == y, true);
	ASSERT_EQ(x >= y, true);
	ASSERT_EQ(x <= y, true);

	x = LongNumberDouble("555.66");
	ASSERT_EQ(x != y, true);
	ASSERT_EQ(x > y, true);
	ASSERT_EQ(y < x, true);

	x = LongNumberDouble("99999.7743");
	ASSERT_EQ(x != y, true);
	ASSERT_EQ(x > y, true);
	ASSERT_EQ(y < x, true);
}

TEST(LongNumberDouble, opAryth) {

	LongNumberDouble x("123.55");
	LongNumberDouble y("345.66");

	LongNumberDouble result = x + y;
	ASSERT_EQ(result.ToStr(), "469.21");

	result = x - y;
	ASSERT_EQ(result.ToStr(), "-222.11");

	result = x * y;
	ASSERT_EQ(result.ToStr(), "42706.293");

	result = x / y;
	ASSERT_EQ(result.ToStr(), "0.3574321639");
}

TEST(LongNumberDouble, stream) {

	LongNumberDouble x("123.55");
	std::ostringstream oss;

	oss << x;

	ASSERT_EQ(oss.str(), "123.55");
}

TEST(LongNumberDouble, Linteral)
{
	LongNumberDouble lnd = 1543.7_lnd;
	Equal(lnd.GetDigits(), { 1, 5, 4, 3, 7 });
	ASSERT_EQ(lnd.GetExponent(), 4);
	ASSERT_FALSE(lnd.GetIsNegative());

}