#include <iostream>
#include <string>

using std::endl;
using std::cin;
using std::cout;
using std::string;

/*
暴力查找
找出所有的操作符组合，然后计算出所得，与结果比较
难点在于如何计算表达式，使用 https://en.wikipedia.org/wiki/Recursive_descent_parser
* 和 /具有比 +-更高优先级，在Term(terminate 终止符)函数中计算。这里简单的地方在于数值是固定的，都是 4.
Example: 
4 + 4 - 4 * 4 = -8
这里不必一定先计算4 * 4， 可以先计算前面的 4 + 4 ，然后计算  4 * 4 ,最后相减，结果一样
不必纠结于先算4 * 4

优化的地方在于，4个4能组成的最大值是256(4*4*4*4)，最小值是-60(4-4*4*4)，所以对于超出范围的值都返回no solution
另外3个操作符，最多只能构成64个表达式(4*4*4)，还可以构造一张表，把所有值都存进去，进行查找.
*/

int Term(char ops[3], int& p) {
    int result = 4;
    while(ops[p] == '*' || ops[p] == '/') {
        if(ops[p] == '*') {
            result *= 4;
        }
        else {
            result /= 4;
        }
        ++p;
    }
    // cout << "T. r=" << result << ", p=" << p << endl;
    return result;
};

int Eval(char op1, char op2, char op3) {
    int result;
    char ops[3] = {op1, op2, op3};
    int p;

    p = 0;
    result = Term(ops, p);
    // cout << "E1. r=" << result << ", p=" << p << endl;
    while(p < sizeof ops) {
        if(ops[p] == '+') {
            result += Term(ops, ++p);
        }
        else {
            result -= Term(ops, ++p);
        }
        // cout << "E. r=" << result << ", p=" << p << endl;
    }
    return result;
}

void Force(int result) {
    const char op[4] = {'+', '-', '*', '/'};

    for(size_t i = 0; i < 4; ++i) {
        for(size_t j = 0; j < 4; ++j) {
            for(size_t m = 0; m < 4; ++m) {
                if(result == Eval(op[i], op[j], op[m])) {
                    cout <<  "4 " << op[i] 
                         << " 4 " << op[j]
                         << " 4 " << op[m] 
                         << " 4 = " << result << endl;
                    return;
                }
            }
        }
    }
    cout << "no solution" << endl;
};

void Expression(int result) {
    if(result > 256 || result < -60) {
        cout << "no solution" << endl;
        return;
    }
    Force(result);
}

int main() {
    std::ios::sync_with_stdio(false);
    size_t num;

    // Expression(100);
    // cout << Eval('+', '-', '*') << endl;
    // return 0;

    cin >> num;
    while(num-- > 0) {
        int result;
        cin >> result;
        Expression(result);
    }
    return 0;
}
