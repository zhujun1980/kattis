#include <iostream>
#include <string>

using std::endl;
using std::cin;
using std::cout;
using std::string;

/*
我的整体思路是

[x, y, z] [a b c] = [p1, p2, p3]
          [d e f]
          [g h i]

x,y,z 是选择 3个dice 的概率，a,b,c是第一个dice的概率，以此类推。
p1,p2,p3是希望模拟的概率，本质上是求如下这个 linear equation system
x * a + y * d + z * g = p1
x * b + y * e + z * h = p2
x * c + y * f + z * i = p3

使用
XA=B
X=BA^-1 求解，需要找出A的逆矩阵
但是这个方法只在A是平方矩阵，而且是full rank时可行，这时存在一个且只有一个的solution
然后检查这个解是否符合概率要求(概率必须是>=0且小于等于1的)
https://www.wikihow.com/Find-the-Inverse-of-a-3x3-Matrix
https://www.wikihow.com/Find-the-Determinant-of-a-3X3-Matrix

对于其他情况，我不太明白，需要更多的数学: Systems of Linear Equations
https://www.mathsisfun.com/algebra/systems-linear-equations.html
https://en.wikipedia.org/wiki/System_of_linear_equations
*/
void Simulate(int dice[3][3], int p1, int p2, int p3) {
    long double a = dice[0][0];
    long double b = dice[1][0];
    long double c = dice[2][0];

    long double d = dice[0][1];
    long double e = dice[1][1];
    long double f = dice[2][1];

    long double g = dice[0][2];
    long double h = dice[1][2];
    long double i = dice[2][2];

    long double l1 =      a * ((e * i) - (f * h));
    long double l2 = -1 * d * ((b * i) - (h * c));
    long double l3 =      g * ((b * f) - (e * c));
    long double determinant = l1 + l2 + l3;
    // cout << l1 << endl;
    // cout << l2 << endl;
    // cout << l3 << endl;
    // cout << determinant << endl;
    if(determinant == 0.0) {
        cout << "NO" << endl;
        return;
    }
    determinant = 1 / determinant;
    long double j = determinant *      ((e * i) - (f * h));
    long double k = determinant * -1 * ((d * i) - (f * g));
    long double l = determinant *      ((d * h) - (g * e));
    long double m = determinant * -1 * ((b * i) - (c * h));
    long double n = determinant *      ((a * i) - (g * c));
    long double o = determinant * -1 * ((a * h) - (b * g));
    long double p = determinant *      ((b * f) - (c * e));
    long double q = determinant * -1 * ((a * f) - (c * d));
    long double r = determinant *      ((e * a) - (d * b));

    long double x = j * p1 + m * p2 + p * p3;
    long double y = k * p1 + n * p2 + q * p3;
    long double z = l * p1 + o * p2 + r * p3;

    // cout << j << ", " << k << ", " << l << endl;
    // cout << m << ", " << n << ", " << o << endl;
    // cout << p << ", " << q << ", " << r << endl;
    // cout << x << ", " << y << ", " << z << endl;

    if(x < 0.0 || y < 0.0 || z < 0.0) {
        cout << "NO" << endl;
        return;
    }
    if((x + y + z) == 1.0) {
        cout << "YES" << endl;
        return;
    }
    cout << "NO" << endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    while(1) {
        int dice[3][3];
        int p1, p2, p3;
        cin >> dice[0][0] >> dice[0][1] >> dice[0][2];
        if (dice[0][0] == 0 && dice[0][1] == 0 && dice[0][2] == 0) {
            break;
        }
        cin >> dice[1][0] >> dice[1][1] >> dice[1][2];
        cin >> dice[2][0] >> dice[2][1] >> dice[2][2];
        cin >> p1 >> p2 >> p3;

        if((dice[0][0]==p1 && dice[0][1]==p2 && dice[0][2]==p3) &&
           (dice[1][0]==p1 && dice[1][1]==p2 && dice[1][2]==p3) &&
           (dice[2][0]==p1 && dice[2][1]==p2 && dice[2][2]==p3)) {
            cout << "YES" << endl;
        }
        else {
            Simulate(dice, p1, p2, p3);
        }
    }
    return 0;
}
