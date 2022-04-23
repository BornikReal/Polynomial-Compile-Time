#include <iostream>
#include <array>
#include <gtest/gtest.h>
#include <cmath>

using namespace std;

template<int x, int deg>
struct degree {
    static const int value = x * degree<x, deg - 1>::value;
};

template<int x>
struct degree<x, 0> {
    static const int value = 1;
};

template<int x, array coef, int pos>
struct polynomial {
    static const int value = coef[pos] * degree<x, pos>::value + polynomial<x, coef, pos - 1>::value;

    friend std::ostream &operator<<(std::ostream &out, const polynomial<x, coef, pos> &rhs) {
        if (pos == 0) {
            out << coef[0];
            return out;
        }
        double t;
        if (coef[pos] < 0)
            out << "-";
        for (int i = pos; i >= 1; i--) {
            if (coef[i] == 0)
                continue;
            else if (i != (pos)) {
                if (coef[i] > 0)
                    out << " + ";
                else
                    out << " - ";
            }
            t = abs(coef[i]);
            if (t != 1)
                out << t << "*(" << x << ")";
            else
                out << "(" << x << ")";
            if (i != 1)
                out << "^" << i;
        }
        if (coef[0] > 0)
            out << " + " << abs(coef[0]);
        else if (coef[0] != 0)
            out << " - " << abs(coef[0]);
        out << " = " << value;
        return out;
    }
};

template<int x, array coef>
struct polynomial<x, coef, 0> {
    static const int value = coef[0];
};

TEST(PolynomialChecking, ZeroDegree) {
    static constexpr array<int, 1> test = {1};
    polynomial<0, test, 0> test_poly;
    int a = test_poly.value;
    EXPECT_EQ(a, 1);
}

TEST(PolynomialChecking, FullPoly) {
    static constexpr array<int, 5> test = {3, 7, -2, 8, 9};
    polynomial<9, test, 4> test_poly;
    int x = (int)pow(9, 4);
    int s = 0;
    for (int i = 4; i >= 0; --i) {
        s += x * test[i];
        x /= 9;
    }
    int a = test_poly.value;
    EXPECT_EQ(a, s);
}

int main() {
    static constexpr array<int, 3> test = {3, 7, -2};
    polynomial<-6, test, 2> test_poly;
    cout << test_poly << endl;
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
