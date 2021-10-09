//
// Created by Tou Lau on 2021/10/6.
//
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

#define MAXSIZE 100000000
unsigned long mask;
unsigned cnrs[MAXSIZE];
int number;
int p_size;

unsigned long power(unsigned long n, unsigned long m)
{
    unsigned long temp;

    if (m == 1)
        temp = n;
    else if (m & 0x01 != 0)
        temp = n * power(n, m - 1);
    else
    {
        temp = power(n, m >> 1);
        temp *= temp;
        cnrs[number++] = (temp >> ((m >> 1) * p_size)) & mask;
    }

    return temp;
}

unsigned factor(unsigned long n)
{
    unsigned long temp;

    if (n == 1)
        return 1;
    else if (n & 0x01 == 1)
        return n * factor(n - 1);
    else
    {
        temp = factor(n >> 1);
        return cnrs[number++] * temp * temp;
    }
}

unsigned long factorial(unsigned long n)
{
    unsigned long x = (1 << n) + 1;

    number = 0;
    mask = (1 << n) - 1;
    p_size = n;
    power(x, n);
    number = 0;

    return factor(n);
}

int main()
{
    int number = 30;
    unsigned long result = factorial(number);
    cout << "result = " << result << endl;
    copy(cnrs, cnrs + 10, ostream_iterator<int>(cout, " "));
}