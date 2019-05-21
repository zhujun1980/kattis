#include <iostream>
#include <string>
#include <stack>

// =============== solution 1 ===============
// size_t _CountInversions1(const std::string& str) {
//     size_t num = 0, numOfOne = 0;
//     size_t length = str.size();
//     const char *left = str.c_str();
//     const char *right = str.c_str() + length;
//     const char *leftmostOne = nullptr, *rightmostZero = nullptr;
//     const char *walk = nullptr;

//     for(auto p = left; p != right; ++p) {
//         if(*p == '1' && leftmostOne == nullptr)
//             leftmostOne = p;
//         else if (*p == '0')
//             rightmostZero = p;
//     }
//     if(!rightmostZero || !leftmostOne || rightmostZero < leftmostOne)
//         return 0L;
//     walk = leftmostOne;
//     while(walk <= rightmostZero) {
//         if(*walk == '1') {
//             numOfOne += 1;
//         }
//         else {
//             num += numOfOne;
//         }
//         walk++;
//     }
//     return num;
// }

size_t _CountInversions1(const std::string& str) {
    size_t zeros = 0L;
    size_t num = 0L;
    for(auto i = str.rbegin(); i != str.rend(); ++i) {
        if(*i == '0') ++zeros;
        else if(*i == '1') num+=zeros;
    }
    return num;
}

void CountInversions1(std::string& in, size_t pos, size_t& result) {
    while(in[pos] != '?' && pos != in.size()) { pos++; }
    if(pos == in.size()) {
        auto ret = _CountInversions1(in);
        result += ret;
        //std::cout << in << ", " << ret << ", " << result << std::endl;
        return;
    }
    in[pos] = '0';
    CountInversions1(in, pos + 1, result);
    in[pos] = '1';
    CountInversions1(in, pos + 1, result);
    in[pos] = '?';
}

// =============== solution 2 ===============
inline static size_t _CountInversions2(const std::string& in, int pos, size_t zeros, size_t total, size_t& count) {
    ++count;
    while(in[pos] != '?' && pos >= 0) {
        if(in[pos] == '0') ++zeros;
        else total += zeros;
        --pos;
    }
    if(pos < 0) return total;
    if(pos == 0) {
        return total + total + zeros;
    }
    return _CountInversions2(in, pos - 1, zeros + 1, total, count) + 
            _CountInversions2(in, pos - 1, zeros, total + zeros, count);
}

size_t CountInversions2(const std::string& in) {
    size_t count = 0;
    auto ret =  _CountInversions2(in, in.size() - 1, 0L, 0L, count);
    return ret;
}

// =============== solution 3 ===============
struct DataPair {
    size_t zeros;
    size_t total;
    int pos;
};

size_t CountInversions3(const std::string& in) {
    size_t K = 0L;
    for(auto i = in.rbegin(); i != in.rend(); ++i) {
        if(*i == '?') ++K;
    }
    size_t k = 0;
    DataPair *data = new DataPair[1<<K];
    auto iter = in.rbegin();
    do {
        if(*iter != '?') {
            for(size_t j = 0; j < (1<<k); ++j) {
                if(*iter == '0') {
                    data[j].zeros += 1;
                }
                else {
                    data[j].total += data[j].zeros;
                }
            }
        }
        else {
            for(size_t j = (1<<k), m = 0; j < (1<<(k+1)); ++j, ++m) {
                data[j].zeros = data[m].zeros;
                data[j].total = data[m].total + data[m].zeros;
            }
            for(size_t j = 0; j < (1<<k); ++j) {
                data[j].zeros += 1;
            }
            ++k;
        }
        ++iter;
    } while(iter != in.rend());
    
    size_t total = 0L;
    for(size_t j = 0; j < (1<<K); ++j) {
        total += data[j].total;
    }
    return total;
}

// =============== solution 4 ===============
inline static size_t _CountInversions4(const std::string& in, int pos, size_t zeros, size_t total) {
    while(in[pos] != '?' && pos >= 0) {
        if(in[pos] == '0') ++zeros;
        else total += zeros;
        --pos;
    }
    if(pos < 0) return total;
    if(pos == 0) {
        return total + total + zeros;
    }
    return _CountInversions4(in, pos - 1, zeros + 1, total) + 
            _CountInversions4(in, pos - 1, zeros, total + zeros);
}

size_t CountInversions4(const std::string& in) {
    size_t total = 0L;
    std::stack<DataPair> data;
    DataPair dp = {0L, 0L, (int)in.size() - 1};
    size_t count = 0;

    while(1) {
        count++;
        while(in[dp.pos] != '?' && dp.pos >= 0) {
            if(in[dp.pos] == '0') ++dp.zeros;
            else dp.total += dp.zeros;
            --dp.pos;
        }
        if(dp.pos <= 0) {
            if(dp.pos == 0) {
                total += dp.total + dp.total + dp.zeros;
            }
            else {
                total += dp.total;
            }
            if(data.empty()) {
                break;
            }
            else {
                dp = data.top();
                data.pop();
                dp.pos--;
                dp.total += dp.zeros;
            }
        }
        else {
            data.push(dp);
            dp.pos--;
            dp.zeros += 1;
        }
    }
    return total;
}

// =============== solution 5 ===============
size_t CountInversions5(const std::string& in) {
    size_t total = 0L;
    size_t zeros = 0L;
    size_t count = 1L;

    for(auto i = in.rbegin(); i != in.rend(); ++i) {
        if(*i == '0') zeros += count;
        else if(*i == '1') total += zeros;
        else {
            total = total + total + zeros;
            zeros = zeros + zeros + count;
            count += count;
        }
        total %= 1000000007L;
        zeros %= 1000000007L;
        count %= 1000000007L;
    }
    return total;
}

int main(void) {
    std::string input;
    size_t result = 0L;
    size_t mod = 1000000007L;
    std::ios::sync_with_stdio(false);

    std::cin >> input;
    // CountInversions1(input, 0L, result);
    // result = CountInversions2(input);
    // std::cout << result << std::endl;
    // result = CountInversions3(input);
    // result = CountInversions4(input);
    // result %= mod;

    result = CountInversions5(input);
    std::cout << result << std::endl;
    return 0;
}

/*
1??10?00

    10000 4
    10100 3
1?
    010000 5
    010100 4
    110000 4
    110100 3

10010000, 10
    a 100     2 2
    b 10000   4 4
              a.total + b.zeros + b.total

10010100, 10
10110100, 12
10110000, 13

11010100, 13
11010000, 14
11110100, 14
11110000, 16
*/
