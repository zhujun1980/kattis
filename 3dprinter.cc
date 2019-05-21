#include <iostream>
#include <string>

using std::endl;
using std::cin;
using std::cout;
using std::string;

int main() {
    std::ios::sync_with_stdio(false);
    size_t status, days, pointers;

    cin >> status;
    days = 0L;
    pointers = 1L;

    for(int i = 1; pointers < status; ++i, ++days) {
        pointers = 1 << i;
    }
    cout << days + 1 << endl;
    return 0;
}
