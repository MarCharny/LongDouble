#include "LongNumber.hpp"
#include <iostream>
#include <ctime>

using namespace std;

LongNumberDouble CalcPi(int p)
{
    LongNumberDouble C = LongNumberDouble("426880");
    C = C * LongNumberDouble((long double)sqrt(10005), p);
    LongNumberDouble S = LongNumberDouble("0");
    LongNumberDouble Mq = LongNumberDouble("1");
    LongNumberDouble Lq = LongNumberDouble("13591409");
    LongNumberDouble Xq = LongNumberDouble("1");

    C.SetDivDigits(p);
    S.SetDivDigits(p);
    Mq.SetDivDigits(p);
    Lq.SetDivDigits(p);
    Xq.SetDivDigits(p);

    for (size_t q = 0; q < p / 14 + 1; q++) 
    {
        LongNumberDouble t1 = Mq * Lq;
        LongNumberDouble t2 = t1 / Xq;
        S = S + t2;
        Mq = Mq * LongNumberDouble(8 * (6 * q + 1) * (6 * q + 3) * (6 * q + 5));
        LongNumberDouble t3 = LongNumberDouble((q + 1) * (q + 1) * (q + 1));
        t3.SetDivDigits(p);
        Mq = Mq / LongNumberDouble((q + 1) * (q + 1) * (q + 1));
        Lq = Lq / LongNumberDouble("545140134");
        Xq = Xq * LongNumberDouble("-262537412640768000");
    }

    return C / S;
}

int main()
{
	cout << "Enter precision : ";
	int p;
	cin >> p;

	clock_t start = clock();
	LongNumberDouble pi = CalcPi(p);
	clock_t end = clock();
	clock_t dur = (double)(end - start) / CLOCKS_PER_SEC;

	cout << "Result Pi: " << pi << '\n';
	cout << "Duration: " << dur << '\n';

	return 0;
}

