#include <stdio.h>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <sstream>

#include "../include/LongNumber.hpp"

using namespace std;

string LDToString(long double value, long divdig)
{
	std::stringstream stream;
	stream << value;
	return stream.str();
}

LongNumberDouble::LongNumberDouble()
{
	is_negative_ = false;
	exp_ = 1;
	digits_ = vector<int>(1, 0);
}

LongNumberDouble::LongNumberDouble(const LongNumberDouble& lnd)
{
	is_negative_ = lnd.is_negative_;
	exp_ = lnd.exp_;
	digits_ = vector<int>(lnd.digits_);
	div_dig_ = lnd.div_dig_;
}

LongNumberDouble::LongNumberDouble(const char* str)
{
	size_t idx;
	if (str[0] == '-')
	{
		is_negative_ = true;
		idx = 1;
	}
	else
	{
		is_negative_ = false;
		idx = 0;
	}

	exp_ = strlen(str) - idx;
	while (idx < strlen(str))
	{
		if (str[idx] == '.')
		{
			exp_ = is_negative_ ? idx - 1 : idx;
		}
		else
		{
			digits_.push_back(str[idx] - '0');
		}
		idx++;
	}
}

LongNumberDouble::LongNumberDouble(long double val, long divDig) : LongNumberDouble(LDToString(val, divDig)) {}

LongNumberDouble::LongNumberDouble(long long int lli) : LongNumberDouble(to_string(lli)) {}

LongNumberDouble::LongNumberDouble(const string& str) : LongNumberDouble(str.c_str()) {}

ostream& operator<<(ostream& os, const LongNumberDouble& lnd)
{
	if (lnd.GetIsNegative())
	{
		os << '-';
	}

	if (lnd.GetExponent() > 0)
	{
		size_t idx = 0;
		long int exp = lnd.GetExponent();

		while (idx < lnd.GetDigits().size() && idx < exp)
		{
			os << lnd.GetDigits()[idx++];
		}

		if (idx < lnd.GetDigits().size())
		{
			os << '.';
			while (idx < lnd.GetDigits().size())
			{
				os << lnd.GetDigits()[idx++];
			}
		}
	}
	else
	{
		os << '0.';
		for (size_t i = 0; i < lnd.GetExponent(); i++)
		{
			os << '0';
		}
		for (size_t i = 0; i < lnd.GetDigits().size(); i++)
		{
			os << lnd.GetDigits()[i];
		}
	}

	return os;
}


string LongNumberDouble::ToStr()
{
	string res;

	if (this->GetIsNegative())
	{
		res.push_back('-');
	}

	if (this->GetExponent() > 0)
	{
		size_t idx = 0;
		long int exp = this->GetExponent();

		while (idx < this->GetDigits().size() && idx < exp)
		{
			res.push_back((char)(this->GetDigits()[idx++] + '0'));
		}

		if (idx < this->GetDigits().size())
		{
			res.push_back('.');
			while (idx < this->GetDigits().size())
			{
				res.push_back((char)(this->GetDigits()[idx++] + '0'));
			}
		}
	}
	else
	{
		res.push_back('0');
		res.push_back('.');
		for (size_t i = 0; i < this->GetExponent(); i++)
		{
			res.push_back('0');
		}
		for (size_t i = 0; i < this->GetDigits().size(); i++)
		{
			res.push_back((char)(this->GetDigits()[i] + '0'));
		}
	}

	return res;
}


LongNumberDouble LongNumberDouble::operator-() const
{
	LongNumberDouble res;
	res.SetIsNegative(!is_negative_);
	res.SetDigits(digits_);
	res.SetExponent(exp_);
	res.SetDivDigits(div_dig_);
	return res;
}

LongNumberDouble& LongNumberDouble::operator=(const LongNumberDouble& lnd)
{
	is_negative_ = lnd.is_negative_;
	digits_ = lnd.digits_;
	exp_ = lnd.exp_;
	div_dig_ = lnd.div_dig_;
	return *this;
}

LongNumberDouble operator""_lnd(const char* str)
{
	return LongNumberDouble(str);
}

LongNumberDouble operator+(const LongNumberDouble& rl, const LongNumberDouble& rr)
{
	if (rl.GetIsNegative() == rr.GetIsNegative())
	{
		long int new_exp = max(rl.GetExponent(), rr.GetExponent());
		long int exp_rl = rl.GetExponent();
		long int exp_rr = rr.GetExponent();
		vector<int> drl(rl.GetDigits());
		vector<int> drr(rr.GetDigits());

		while (exp_rl != new_exp)
		{
			drl.insert(drl.begin(), 0);
			exp_rl++;
		}
		while (exp_rr != new_exp)
		{
			drr.insert(drr.begin(), 0);
			exp_rr++;
		}

		size_t new_size = max(drl.size(), drr.size());
		while (drl.size() != new_size)
		{
			drl.push_back(0);
		}
		while (drr.size() != new_size)
		{
			drr.push_back(0);
		}

		vector<int> new_digits(1 + new_size, 0);
		for (size_t i = 0; i < new_size; i++)
		{
			new_digits[i + 1] = drl[i] + drr[i];
		}
		for (size_t i = new_size; i > 0; i--)
		{
			new_digits[i - 1] += new_digits[i] / 10;
			new_digits[i] %= 10;
		}

		LongNumberDouble res;
		res.SetIsNegative(rl.GetIsNegative());
		res.SetExponent(new_exp + 1);
		res.SetDigits(new_digits);
		res.SetDivDigits(max(rl.GetDivDigits(), rr.GetDivDigits()));
		res.removeZeros();

		return res;
	}

	if (rl.GetIsNegative())
	{
		return rr - (-rl);
	}

	return rl - (-rr);
}

LongNumberDouble operator-(const LongNumberDouble& rl, const LongNumberDouble& rr)
{
	if (!rl.is_negative_ && !rr.is_negative_)
	{
		bool isRlGreater = rl > rr;
		long int expMax = isRlGreater ? rl.GetExponent() : rr.GetExponent();
		long int expMin = isRlGreater ? rr.GetExponent() : rl.GetExponent();
		long int new_exp = max(expMin, expMax);
		vector<int> digitsMax(isRlGreater ? rl.GetDigits() : rr.GetDigits());
		vector<int> digitsMin(isRlGreater ? rr.GetDigits() : rl.GetDigits());

		while (expMax != new_exp)
		{
			digitsMax.insert(digitsMax.begin(), 0);
			expMax++;
		}
		while (expMin != new_exp)
		{
			digitsMin.insert(digitsMin.begin(), 0);
			expMin++;
		}

		size_t new_size = max(digitsMax.size(), digitsMin.size());
		while (digitsMax.size() != new_size)
		{
			digitsMax.push_back(0);
		}
		while (digitsMin.size() != new_size)
		{
			digitsMin.push_back(0);
		}

		vector<int> new_digits(new_size + 1, 0);
		for (size_t i = 0; i < new_size; i++)
		{
			new_digits[i + 1] = digitsMax[i] - digitsMin[i];
		}
		for (size_t i = new_size; i > 0; i--)
		{
			if (new_digits[i] < 0)
			{
				new_digits[i] += 10;
				new_digits[i - 1]--;
			}
		}

		LongNumberDouble res;
		res.SetIsNegative(isRlGreater ? false : true);
		res.SetExponent(new_exp + 1);
		res.SetDigits(new_digits);
		res.SetDivDigits(max(rl.GetDivDigits(), rr.GetDivDigits()));
		res.removeZeros();

		return res;
	}

	if (rl.GetIsNegative() && rr.GetIsNegative())
	{
		return (-rr) + (-rl);
	}

	return rl + (-rr);
}

LongNumberDouble operator*(const LongNumberDouble& rl, const LongNumberDouble& rr)
{
	size_t new_size_max = rl.GetDigits().size() + rr.GetDigits().size();
	bool new_is_neg = rl.GetIsNegative() ^ rr.GetIsNegative();
	long int new_exp = rl.GetExponent() + rr.GetExponent();

	vector<int> new_digits(new_size_max, 0);

	for (size_t i = 0; i < rl.GetDigits().size(); i++)
	{
		for (size_t j = 0; j < rr.GetDigits().size(); j++)
		{
			new_digits[i + j + 1] += rl.GetDigits()[i] * rr.GetDigits()[j];
		}
	}

	for (size_t i = new_size_max - 1; i > 0; i--)
	{
		new_digits[i - 1] += new_digits[i] / 10;
		new_digits[i] %= 10;
	}

	LongNumberDouble res;
	res.SetExponent(new_exp);
	res.SetIsNegative(new_is_neg);
	res.SetDigits(new_digits);
	res.SetDivDigits(max(rl.GetDivDigits(), rr.GetDivDigits()));
	res.removeZeros();

	return res;
}

LongNumberDouble operator/(const LongNumberDouble& rl, const LongNumberDouble& rr)
{
	LongNumberDouble res = rl * rr.inverse();
	size_t totalnums = (rl.GetDivDigits(), rr.GetDivDigits()) + res.exp_;

	if (res.exp_ < 0 && res.digits_.size() > 3)
	{
		while (res.digits_.size() > totalnums)
		{

			if (res.digits_[res.digits_.size() - 1] >= 5 && res.digits_[res.digits_.size() - 1] < 9)
			{
				res.digits_[res.digits_.size() - 2] += 1;
			}

			res.digits_.pop_back();
		}
	}

	return res;
}

bool operator==(const LongNumberDouble& rl, const LongNumberDouble& rr)
{
	if (rl.GetIsNegative() != rr.GetIsNegative() || rl.GetExponent() != rr.GetExponent() || \
		rl.GetDigits().size() != rr.GetDigits().size() || rl.GetDigits() != rr.GetDigits())
	{
		return false;
	}

	return  true;
}

bool operator!=(const LongNumberDouble& rl, const LongNumberDouble& rr)
{
	return !(rl == rr);
}

bool operator>(const LongNumberDouble& rl, const LongNumberDouble& rr)
{
	if (rl.GetIsNegative() != rr.GetIsNegative())
	{
		return rl.GetIsNegative() < rr.GetIsNegative();
	}

	if (rl.GetExponent() != rr.GetExponent())
	{
		return (rl.GetExponent() > rr.GetExponent()) ^ (rl.GetIsNegative());
	}

	vector<int> drl(rl.GetDigits());
	vector<int> drr(rr.GetDigits());
	size_t size = max(drl.size(), drr.size());

	while (drl.size() != size)
	{
		drl.push_back(0);
	}
	while (drr.size() != size)
	{
		drr.push_back(0);
	}

	for (size_t i = 0; i < size; i++)
	{
		if (drl[i] != drr[i])
		{
			return (drl[i] > drr[i]) ^ rl.GetIsNegative();
		}
	}

	return false;
}

bool operator<(const LongNumberDouble& rl, const LongNumberDouble& rr)
{
	return (rl != rr) && !(rl > rr);
}

bool operator>=(const LongNumberDouble& rl, const LongNumberDouble& rr)
{
	return !(rl < rr);
}

bool operator<=(const LongNumberDouble& rl, const LongNumberDouble& rr)
{
	return !(rl > rr);
}

void LongNumberDouble::removeZeros()
{
	size_t n = max((long)1, exp_);
	while (digits_.size() > n && digits_[digits_.size() - 1] == 0)
	{
		digits_.erase(digits_.end() - 1);
	}

	while (digits_.size() > 1 && digits_[0] == 0)
	{
		digits_.erase(digits_.begin());
		exp_--;
	}

	while (digits_.size() > 1 && digits_[digits_.size() - 1] == 0)
	{
		digits_.erase(digits_.end() - 1);
	}

	if (digits_.size() == 1 && digits_[0] == 0)
	{
		exp_ = 1;
		is_negative_ = false;
	}
}

LongNumberDouble LongNumberDouble::inverse() const
{
	if (digits_.size() == 1 && digits_[0] == 0)
	{
		throw runtime_error("division by zero");
	}

	if (*this == LongNumberDouble("1"))
	{
		return LongNumberDouble("1");
	}

	LongNumberDouble x(*this);
	x.is_negative_ = false;

	LongNumberDouble d("1");
	LongNumberDouble o("0");

	LongNumberDouble res;
	res.is_negative_ = is_negative_;
	res.exp_ = 1;
	res.digits_ = vector<int>();
	res.div_dig_ = div_dig_;

	while (x < d)
	{
		x.exp_++;
		res.exp_++;
	}

	while (d < x)
	{
		d.exp_++;
	}

	res.exp_ -= d.exp_ - 1;

	size_t calc_nums = 0;
	size_t total_nums = res.exp_ < 0 ? div_dig_ : div_dig_ + res.exp_;

	do {
		int div = 0;

		while (d >= x) {
			div++;
			d = d - x;
		}
		d.exp_++;
		d.removeZeros();
		res.digits_.push_back(div);
		calc_nums++;
	} while (d != o && calc_nums < total_nums + 1);

	if (res.exp_ < 0 && res.digits_.size() > 2)
	{
		if (res.digits_[res.digits_.size() - 1] >= 5 && res.digits_[res.digits_.size() - 1] < 9)
		{
			res.digits_[res.digits_.size() - 2] += 1;
		}
	}

	res.digits_.pop_back();


	return res;
}