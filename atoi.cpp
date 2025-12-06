#include <string>
#include <utility>
#include <iostream>
#include <limits>

namespace {
    std::pair<bool, int> atoi(const std::string& in) {
        auto start = in.begin(), last = in.end();
        int sign = 1;
        long long limit = std::numeric_limits<int>::max();
        if (start != last && *start == '-') {
            sign = -1;
            ++start;
            ++limit;
        }
        long long val = 0;
        while (start != last && '0' <= *start && *start <='9') {
            val = val * 10 + *start - '0';
            if (val > limit) break;
            ++start;
        }
        return {start == last, sign * val};
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: atoi num_string\n";
        return 1;
    }
    auto res = atoi(std::string(argv[1]));
    std::cout << (res.first ? "valid" : "invalid") << " " << res.second << "\n";
    return 0;
}
