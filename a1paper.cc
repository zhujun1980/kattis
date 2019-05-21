#include <iostream>

using std::endl;
using std::cin;
using std::cout;

/*
这个方法比较麻烦，容易出错，调试了半天才通过了所有的case
思路就是，边长是 2^(-5/4)，边宽2^(-3/4)(=1/2^(3/4))，边长可以转换为2^(3/4)/4，所以A2的面积是1/4，那么A1的面积是1/2(=0.5)
A3的面积是1/8 ... 以此类推，Find函数就是从最大的size开始递归：查找当前size的paper是否可以填满所剩下的空间，存在就返回true，
否则就找下一个size（面积要减去当前size已经填充的空间），如果该size为0张则继续向后查，如果到达最后一个都没有返回false，表示没有solution
当前size的paper的面积是可以计算的(1/2^2, 1/2^3, 1/2^4 ....)，用当前所余空间除以当前面积，得到所需的张数，如果满足则成功，如果不够，则向后面寻找更小的size进行拼接。
在递归的过程中计算所需的distance，就是从当前paper进行两两组合，直到上一次有值的paper为止。
pi参数是当前paper要拼接的上一个size paper，比如已经有一个A2了，假设没有A3，有若干A4，那么pi就表示A2的意思，此时要计算这些A4组成A2需要的distance，然后返回，而不是从A4直接计算到A1的distance（在这里看了很久才发现这个问题，还是没有设计好这个算法）
*/

const long double kA2LengthSide = 0.59460355750136053335874998528;
const long double  kA2WidthSide = 0.42044820762685727151556273812;

bool Find(long double an, size_t *nums, int p, int length, long double ll, long double ww, int pi, long double &distance) {
    if(p == length) {
        return false;
    }
    if(nums[p] == 0) {
        return Find(an, nums, p + 1, length, ww, ll / 2, pi, distance);
    }
    long double area = 1.0 / (1 << (p + 2));
    long long i = an / area;
    // cout << an << ", A" << p + 2 << ", pi " << pi << ", " << area << ", " << an/area << ", need " << i << ", has " << nums[p] << endl;
    if(i <= nums[p]) {
        // cout << endl;
        goto succ;
    }
    an -= area * nums[p];
    if(!Find(an, nums, p + 1, length, ww, ll / 2, p, distance)) {
        return false;
    }

succ:
    while(p != pi) {
        i = i >> 1;
        --p;
        // cout << "ll " << ll << ", ww " << ww << ", p " << p << ", pi " << pi << ", i " << i << ", " << (ll * i) << endl;
        distance += ll * i;
        long double oldll = ll;
        ll = ww * 2;
        ww = oldll;
    }
    return true;
}

void Tape(size_t *nums, size_t smallest) {
    size_t length = smallest - 1;
    long double distance = 0.0;
    if(Find(0.5, nums, 0, length, kA2LengthSide, kA2WidthSide, -1, distance)) {
        cout << distance << endl;
    }
    else {
        cout << "impossible" << endl;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cout.precision(20);
    size_t i = 0;
    size_t smallest;

    cin >> smallest;
    size_t length = smallest - 1;
    size_t *num = new size_t[length];
    while(i < length) {
        cin >> num[i];
        ++i;
    }
    Tape(num, smallest);
    return 0;
}
