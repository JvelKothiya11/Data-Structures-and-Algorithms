#include <cmath>

class Solution {
public:
    double power(double x, long long n) {
        if (n == 0) return 1.0;

        double half = power(x, n / 2);
        double result = half * half;

        return (n % 2 == 0) ? result : result * x;
    }

    double myPow(double x, int n) {
        long long exp = llabs(static_cast<long long>(n));

        double result = power(x, exp);

        return (n < 0) ? 1.0 / result : result;
    }
};