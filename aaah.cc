#include <iostream>
#include <string>

using std::endl;
using std::cin;
using std::cout;
using std::string;

/*
https://open.kattis.com/problems/aaah

这是个很奇怪的题目，没有难度，主要就是审题，看懂了就能做对
*/
int main() {
    std::ios::sync_with_stdio(false);
    string sound, needed;
    cin >> sound;
    cin >> needed;
    size_t n = sound.rfind(needed);
    if(n == std::string::npos) {
        cout << "no" << endl;
    }
    else {
        cout << "go" << endl;
    }
    return 0;
}
