#ifndef LONGNUMBER_LONGNUMBER_H
#define LONGNUMBER_LONGNUMBER_H

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <math.h>

using namespace std;

class LongNumberDouble
{
private:
	bool is_negative_ = false;
	vector<int> digits_;
	long int exp_ = 0;
	int div_dig_ = 10;

	void removeZeros();
	LongNumberDouble inverse() const;

	friend LongNumberDouble operator""_lnd(const char* str);

	friend LongNumberDouble operator+(const LongNumberDouble& rl, const LongNumberDouble& rr);
	friend LongNumberDouble operator-(const LongNumberDouble& rl, const LongNumberDouble& rr);
	friend LongNumberDouble operator*(const LongNumberDouble& rl, const LongNumberDouble& rr);
	friend LongNumberDouble operator/(const LongNumberDouble& rl, const LongNumberDouble& rr);

	friend bool operator==(const LongNumberDouble& rl, const LongNumberDouble& rr);
	friend bool operator!=(const LongNumberDouble& rl, const LongNumberDouble& rr);
	friend bool operator<(const LongNumberDouble& rl, const LongNumberDouble& rr);
	friend bool operator>(const LongNumberDouble& rl, const LongNumberDouble& rr);
	friend bool operator<=(const LongNumberDouble& rl, const LongNumberDouble& rr);
	friend bool operator>=(const LongNumberDouble& rl, const LongNumberDouble& rr);

	friend std::ostream& operator<<(std::ostream& out, const LongNumberDouble& rat);


public:
	LongNumberDouble();
	LongNumberDouble(const LongNumberDouble& lnd);
	explicit LongNumberDouble(const char* str);
	explicit LongNumberDouble(const string& str);
	explicit LongNumberDouble(const long double lld, long div_dig);
	explicit LongNumberDouble(long long int lli);

	bool GetIsNegative() const { return is_negative_; }
	long int GetExponent() const { return exp_; }
	vector<int> GetDigits() const { return digits_; }

	void SetDivDigits(int divDig) { div_dig_ = divDig; }
	int GetDivDigits() const { return div_dig_; }

	void SetIsNegative(bool isNegative) { is_negative_ = isNegative; }
	void SetDigits(vector<int> digits) { digits_ = vector<int>(digits); }
	void SetExponent(long int exp) { exp_ = exp; }


	string ToStr();
	LongNumberDouble& operator=(const LongNumberDouble& lnd);
	LongNumberDouble operator-() const;
};
#endif